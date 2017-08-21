/**
 * Author: Dominik Egger
 * Copyright: Distributed Organisms B.V. (DoBots)
 * Date: 9 Mar., 2016
 * License: LGPLv3+, Apache, and/or MIT, your choice
 */

#include "drivers/cs_PWM.h"
#include "util/cs_BleError.h"
#include "drivers/cs_Serial.h"
#include "cfg/cs_Strings.h"
#include "protocol/cs_ErrorCodes.h"

#include <nrf.h>
#include <app_util_platform.h>

/**********************************************************************************************************************
 * Pulse Width Modulation class
 *********************************************************************************************************************/

// Timer channel that determines the period is set to the last channel available.
#define PERIOD_CHANNEL_IDX          5
#define PERIOD_SHORT_CLEAR_MASK     NRF_TIMER_SHORT_COMPARE5_CLEAR_MASK
#define PERIOD_SHORT_STOP_MASK      NRF_TIMER_SHORT_COMPARE5_STOP_MASK

// Timer channel that is used when duty cycle is changed.
#define SECONDARY_CHANNEL_IDX       4
#define SECONDARY_CAPTURE_TASK      NRF_TIMER_TASK_CAPTURE4


// Timer channel to capture the timer counter at the zero crossing.
#define ZERO_CROSSING_CHANNEL_IDX   3
#define ZERO_CROSSING_CAPTURE_TASK  NRF_TIMER_TASK_CAPTURE3


//#define PWM_DISABLE_BY_PPI_ENABLE
//#define PWM_DISABLE_BY_GPIOTE_ENABLE
#define PWM_DISABLE_BY_GPIOTE_CONFIG

PWM::PWM() :
		_initialized(false)
		{
#if PWM_ENABLE==1

#endif
}

uint32_t PWM::init(pwm_config_t & config) {
//#if PWM_ENABLE==1
	LOGi(FMT_INIT, "PWM");
	_config = config;

	uint32_t err_code;

	// Setup timer
	nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_CLEAR);
	nrf_timer_bit_width_set(CS_PWM_TIMER, NRF_TIMER_BIT_WIDTH_32);
	nrf_timer_frequency_set(CS_PWM_TIMER, CS_PWM_TIMER_FREQ);
	_maxTickVal = nrf_timer_us_to_ticks(_config.period_us, CS_PWM_TIMER_FREQ);
	LOGd("maxTicks=%u", _maxTickVal);
	nrf_timer_cc_write(CS_PWM_TIMER, getTimerChannel(PERIOD_CHANNEL_IDX), _maxTickVal);
	nrf_timer_mode_set(CS_PWM_TIMER, NRF_TIMER_MODE_TIMER);
	nrf_timer_shorts_enable(CS_PWM_TIMER, PERIOD_SHORT_CLEAR_MASK);
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(0));
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(1));
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(2));
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(3));
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(4));
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(5));


	// Init gpiote and ppi for each channel
	for (uint8_t i=0; i<_config.channelCount; ++i) {
		initChannel(i, _config.channels[i]);
	}

	_ppiTransitionChannels[0] = getPpiChannel(CS_PWM_PPI_CHANNEL_START + _config.channelCount*2);
	_ppiTransitionChannels[1] = getPpiChannel(CS_PWM_PPI_CHANNEL_START + _config.channelCount*2 + 1);
	_ppiGroup = getPpiGroup(CS_PWM_PPI_GROUP_START);

	// Enable timer interrupt
	err_code = sd_nvic_SetPriority(CS_PWM_IRQn, CS_PWM_TIMER_PRIORITY);
	APP_ERROR_CHECK(err_code);
	err_code = sd_nvic_EnableIRQ(CS_PWM_IRQn);
	APP_ERROR_CHECK(err_code);

	// Start the timer
	nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_START);

	_zeroCrossingCounter = 0;
	_newMaxTickVal = _maxTickVal;

    _initialized = true;
    return ERR_SUCCESS;
//#endif

    return ERR_PWM_NOT_ENABLED;
}

uint32_t PWM::initChannel(uint8_t channel, pwm_channel_config_t& config) {
	LOGd("Configure channel %u as pin %u", channel, _config.channels[channel].pin);

	// Start off
//	nrf_gpio_cfg_output(_config.channels[i].pin);
	nrf_gpio_pin_write(_config.channels[channel].pin, _config.channels[channel].inverted ? 1 : 0);
	_values[channel] = 0;

	// Configure gpiote
	_gpioteInitStatesOn[channel] = config.inverted ? NRF_GPIOTE_INITIAL_VALUE_LOW : NRF_GPIOTE_INITIAL_VALUE_HIGH;
	_gpioteInitStatesOff[channel] = config.inverted ? NRF_GPIOTE_INITIAL_VALUE_HIGH : NRF_GPIOTE_INITIAL_VALUE_LOW;

	nrf_gpiote_task_configure(CS_PWM_GPIOTE_CHANNEL_START + channel, config.pin, NRF_GPIOTE_POLARITY_TOGGLE, _gpioteInitStatesOn[channel]);

	// Cache ppi channels and gpiote tasks
	_ppiChannels[channel*2] = getPpiChannel(CS_PWM_PPI_CHANNEL_START + channel*2);
	_ppiChannels[channel*2 + 1] = getPpiChannel(CS_PWM_PPI_CHANNEL_START + channel*2 + 1);

	// Make the timer compare event trigger the gpiote task
	nrf_ppi_channel_endpoint_setup(
			_ppiChannels[channel*2],
			(uint32_t)nrf_timer_event_address_get(CS_PWM_TIMER, nrf_timer_compare_event_get(channel)),
			nrf_gpiote_task_addr_get(getGpioteTaskOut(CS_PWM_GPIOTE_CHANNEL_START + channel))
	);
	nrf_ppi_channel_endpoint_setup(
			_ppiChannels[channel*2 + 1],
			(uint32_t)nrf_timer_event_address_get(CS_PWM_TIMER, nrf_timer_compare_event_get(PERIOD_CHANNEL_IDX)),
			nrf_gpiote_task_addr_get(getGpioteTaskOut(CS_PWM_GPIOTE_CHANNEL_START + channel))
	);

//	// Enable ppi
//	nrf_ppi_channel_enable(_ppiChannels[channel*2]);
//	nrf_ppi_channel_enable(_ppiChannels[channel*2 + 1]);

	// Enable gpiote
	nrf_gpiote_task_force(CS_PWM_GPIOTE_CHANNEL_START + channel, _gpioteInitStatesOff[channel]);
	nrf_gpiote_task_enable(CS_PWM_GPIOTE_CHANNEL_START + channel);

	return 0;
}


uint32_t PWM::deinit() {

#if PWM_ENABLE==1

	LOGi("DeInit PWM");

	_initialized = false;
	return ERR_SUCCESS;
#endif

	return ERR_PWM_NOT_ENABLED;
}

void PWM::setValue(uint8_t channel, uint16_t newValue) {
	if (!_initialized) {
		LOGe(FMT_NOT_INITIALIZED, "PWM");
		return;
	}
	if (newValue > 100) {
		newValue = 100;
	}
	LOGd("Set PWM channel %d to %d", channel, newValue);
	uint32_t oldValue = _values[channel];

	switch (_values[channel]) {
	case 100:
	case 0: {
		if (newValue == 0 || newValue == 100) {
			// 0/100 --> 0/100
			gpioteForce(channel, newValue == 100);
		}
		else {
			// 0/100 --> N
			_tickValues[channel] = _maxTickVal * newValue / 100;

			nrf_ppi_channel_disable(_ppiTransitionChannels[0]);
			nrf_ppi_channel_disable(_ppiTransitionChannels[1]);
			writeCC(channel, _tickValues[channel]);

			// Turn on PPI channels at end of period (when currently on) or at trailing edge (when currently off).
			// This makes a difference, because of the initial state of the pin.
			nrf_ppi_channel_group_clear(_ppiGroup);
			nrf_ppi_channel_include_in_group(_ppiChannels[channel*2],     _ppiGroup);
			nrf_ppi_channel_include_in_group(_ppiChannels[channel*2 + 1], _ppiGroup);

			nrf_ppi_channel_endpoint_setup(
					_ppiTransitionChannels[0],
					(uint32_t)nrf_timer_event_address_get(CS_PWM_TIMER, nrf_timer_compare_event_get(oldValue == 0 ? channel : PERIOD_CHANNEL_IDX)),
					(uint32_t)nrf_ppi_task_address_get(getPpiTaskEnable(CS_PWM_PPI_GROUP_START))
			);

			nrf_ppi_channel_enable(_ppiTransitionChannels[0]);
		}
		break;
	}
	default: {
		if (newValue == 0 || newValue == 100) {
			// N --> 0/100

			nrf_ppi_channel_disable(_ppiTransitionChannels[0]);
			nrf_ppi_channel_disable(_ppiTransitionChannels[1]);
			writeCC(channel, _tickValues[channel]);

			// Turn off PPI channels at end of period (when turning on) or at trailing edge (when turning off).
			// This makes a difference, because of the initial state of the pin.
			nrf_ppi_channel_group_clear(_ppiGroup);
			nrf_ppi_channel_include_in_group(_ppiChannels[channel*2],     _ppiGroup);
			nrf_ppi_channel_include_in_group(_ppiChannels[channel*2 + 1], _ppiGroup);

			nrf_ppi_channel_endpoint_setup(
					_ppiTransitionChannels[0],
					(uint32_t)nrf_timer_event_address_get(CS_PWM_TIMER, nrf_timer_compare_event_get(newValue == 0 ? channel : PERIOD_CHANNEL_IDX)),
					(uint32_t)nrf_ppi_task_address_get(getPpiTaskDisable(CS_PWM_PPI_GROUP_START))
			);

			nrf_ppi_channel_enable(_ppiTransitionChannels[0]);
		}
		else {
			// N --> M
			_tickValues[channel] = _maxTickVal * newValue / 100;

			nrf_ppi_channel_disable(_ppiTransitionChannels[0]);
			nrf_ppi_channel_disable(_ppiTransitionChannels[1]);
			nrf_ppi_channel_group_clear(_ppiGroup);
			nrf_ppi_channel_include_in_group(_ppiTransitionChannels[0]);

			// Next time the secondary channel triggers (at the new tick value), it will write this tick value to the channel CC.
			nrf_ppi_channel_endpoint_setup(
					_ppiTransitionChannels[0],
					(uint32_t)nrf_timer_event_address_get(CS_PWM_TIMER, nrf_timer_compare_event_get(SECONDARY_CHANNEL_IDX)),
					(uint32_t)nrf_timer_task_address_get(CS_PWM_TIMER, nrf_timer_capture_task_get(channel))
			);

			if (newValue < oldValue) {
				// If the new value is lower, an extra gpio task has to be setup, as the old one will be skipped.
				nrf_ppi_channel_endpoint_setup(
						_ppiTransitionChannels[1],
						(uint32_t)nrf_timer_event_address_get(CS_PWM_TIMER, nrf_timer_compare_event_get(SECONDARY_CHANNEL_IDX)),
						nrf_gpiote_task_addr_get(getGpioteTaskOut(CS_PWM_GPIOTE_CHANNEL_START + channel))
				);
				nrf_ppi_channel_include_in_group(_ppiTransitionChannels[1]);
			}

			writeCC(SECONDARY_CHANNEL_IDX, _tickValues[channel]);
			nrf_ppi_group_enable(_ppiGroup);
		}
	}
	}
	_values[channel] = newValue;
}

uint16_t PWM::getValue(uint8_t channel) {
	if (!_initialized) {
		LOGe(FMT_NOT_INITIALIZED, "PWM");
		return 0;
	}
	if (channel >= _config.channelCount) {
		LOGe("Invalid channel");
		return 0;
	}
	return _values[channel];
}

void PWM::onZeroCrossing() {
	if (!_initialized) {
		LOGe(FMT_NOT_INITIALIZED, "PWM");
		return;
	}

#ifndef PWM_SYNC_IMMEDIATELY
	nrf_timer_task_trigger(CS_PWM_TIMER, ZERO_CROSSING_CAPTURE_TASK);
	uint32_t ticks = nrf_timer_cc_read(CS_PWM_TIMER, getTimerChannel(ZERO_CROSSING_CHANNEL_IDX));

	// Exponential moving average
	uint32_t alpha = 1000; // Discount factor
	_zeroCrossingTicksAvg = ((1000-alpha) * _zeroCrossingTicksAvg + alpha * ticks) / 1000;

//	_zeroCrossingCounter = (_zeroCrossingCounter + 1) % 5;
	_zeroCrossingCounter++;

	if (_zeroCrossingCounter % 10 == 0) {
		int64_t maxTickVal = _maxTickVal;
	//	int64_t targetTicks = _maxTickVal / 2;
		int64_t targetTicks = 0;
		int64_t errTicks = targetTicks - _zeroCrossingTicksAvg;
	//	errTicks = (errTicks + maxTickVal/2) % maxTickVal - maxTickVal/2; // Correct for wrap around

		if (errTicks > maxTickVal / 2) {
			errTicks -= maxTickVal;
		}
		else if (errTicks < -maxTickVal / 2) {
			errTicks += maxTickVal;
		}

		int32_t delta = -errTicks / 50; // Gain

		// Limit the output
		if (delta > maxTickVal / 500) {
			delta = maxTickVal / 500;
		}
		if (delta < -maxTickVal / 500) {
			delta = -maxTickVal / 500;
		}
		uint32_t newMaxTicks = maxTickVal + delta;

//		nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_STOP);
//		nrf_timer_task_trigger(CS_PWM_TIMER, ZERO_CROSSING_CAPTURE_TASK);
//		ticks = nrf_timer_cc_read(CS_PWM_TIMER, getTimerChannel(CAPTURE_CHANNEL_IDX));
//		// Make sure that the new period compare value is not set lower than the current counter value.
//		if (newMaxTicks <= ticks) {
//			newMaxTicks = ticks+1;
//		}
//		nrf_timer_cc_write(CS_PWM_TIMER, getTimerChannel(PERIOD_CHANNEL_IDX), newMaxTicks);
//		nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_START);

		// Set the new period time at the end of the current period.
//		_newMaxTickVal = newMaxTicks;
//		enableInterrupt();

		if (_zeroCrossingCounter % 50 == 0) {
//			write("%u %u\r\n", ticks, _zeroCrossingTicksAvg);
			write("%u  %u  %lli  %u\r\n", ticks, _zeroCrossingTicksAvg, errTicks, newMaxTicks);
//			write("%u %u\r\n", ticks, newMaxTicks);
		}
	}

#else
	// Start a new period
	// Need to stop the timer, else the gpio state at start is not consistent.
	// I guess this is because the gpiote toggle sometimes happens before, sometimes after the nrf_gpiote_task_force()
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(PERIOD_CHANNEL_IDX));
	nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_STOP);

	for (uint8_t i=0; i<_config.channelCount; ++i) {
		if (_isPwmEnabled[i]) {
#ifdef PWM_CENTERED
			gpioteForce(i, false);
#else
			gpioteForce(i, true);
#endif
		}
	}
	// Set the counter back to 0, and start the timer again.
	nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_CLEAR);
	nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_START);
#endif // ndef PWM_SYNC_IMMEDIATELY
}


/////////////////////////////////////////
//          Private functions          //
/////////////////////////////////////////



void PWM::enableInterrupt() {
	// Make the timer stop on end of period
	nrf_timer_shorts_enable(CS_PWM_TIMER, PERIOD_SHORT_STOP_MASK);
	// Enable interrupt, set the value in there (at the end/start of the period).
	nrf_timer_int_enable(CS_PWM_TIMER, nrf_timer_compare_int_get(PERIOD_CHANNEL_IDX));
}

void PWM::_handleInterrupt() {
	// At the interrupt (end of period), set all channels.
	for (uint8_t i=0; i<_config.channelCount; ++i) {
		if (_tickValues[i] == 0) {
//			turnOff(i);
		}
		else if (_tickValues[i] == _maxTickVal) {
//			turnOn(i);
		}
		else {
#ifdef PWM_CENTERED
			nrf_timer_cc_write(CS_PWM_TIMER, getTimerChannel(2*i),   _maxTickVal/2 - _tickValues[i]/2);
			nrf_timer_cc_write(CS_PWM_TIMER, getTimerChannel(2*i+1), _maxTickVal/2 + _tickValues[i]/2);
#else
			nrf_timer_cc_write(CS_PWM_TIMER, getTimerChannel(i), _tickValues[i]);
#endif
			if (!_isPwmEnabled[i]) {
//				gpioOn(i);
				enablePwm(i);
//				gpioteForce(i, true);
//				nrf_ppi_channel_enable(_ppiChannels[i*2]);
//				nrf_ppi_channel_enable(_ppiChannels[i*2 + 1]);
			}
		}
	}
	nrf_timer_cc_write(CS_PWM_TIMER, getTimerChannel(PERIOD_CHANNEL_IDX), _newMaxTickVal);

	// Don't stop timer on end of period anymore, and start the timer again
	nrf_timer_shorts_disable(CS_PWM_TIMER, PERIOD_SHORT_STOP_MASK);
	nrf_timer_task_trigger(CS_PWM_TIMER, NRF_TIMER_TASK_START);
}




void PWM::gpioteConfig(uint8_t channel, bool initOn) {
	nrf_gpiote_task_configure(
			CS_PWM_GPIOTE_CHANNEL_START + channel,
			_config.channels[channel].pin,
			NRF_GPIOTE_POLARITY_TOGGLE,
			initOn ? _gpioteInitStatesOn[channel] : _gpioteInitStatesOff[channel]
	);
}

void PWM::gpioteUnconfig(uint8_t channel) {
	nrf_gpiote_te_default(CS_PWM_GPIOTE_CHANNEL_START + channel);
}

void PWM::gpioteEnable(uint8_t channel) {
	nrf_gpiote_task_enable(CS_PWM_GPIOTE_CHANNEL_START + channel);
}

void PWM::gpioteDisable(uint8_t channel) {
	nrf_gpiote_task_disable(CS_PWM_GPIOTE_CHANNEL_START + channel);
}

void PWM::gpioteForce(uint8_t channel, bool initOn) {
	nrf_gpiote_task_force(CS_PWM_GPIOTE_CHANNEL_START + channel, initOn ? _gpioteInitStatesOn[channel] : _gpioteInitStatesOff[channel]);
}

void PWM::gpioOn(uint8_t channel) {
	nrf_gpio_pin_write(_config.channels[channel].pin, _config.channels[channel].inverted ? 0 : 1);
}

void PWM::gpioOff(uint8_t channel) {
	nrf_gpio_pin_write(_config.channels[channel].pin, _config.channels[channel].inverted ? 1 : 0);
}

void PWM::writeCC(uint8_t channelIdx, uint32_t ticks) {
	nrf_timer_cc_write(CS_PWM_TIMER, getTimerChannel(channelIdx), ticks);
}

uint32_t PWM::readCC(uint8_t channelIdx) {
	return nrf_timer_cc_read(CS_PWM_TIMER, getTimerChannel(channelIdx));
}

nrf_timer_cc_channel_t PWM::getTimerChannel(uint8_t index) {
	assert(index < 6, "invalid timer channel index");
	switch(index) {
	case 0:
		return NRF_TIMER_CC_CHANNEL0;
	case 1:
		return NRF_TIMER_CC_CHANNEL1;
	case 2:
		return NRF_TIMER_CC_CHANNEL2;
	case 3:
		return NRF_TIMER_CC_CHANNEL3;
	case 4:
		return NRF_TIMER_CC_CHANNEL4;
	case 5:
		return NRF_TIMER_CC_CHANNEL5;
	}
	APP_ERROR_CHECK(NRF_ERROR_INVALID_PARAM);
	return NRF_TIMER_CC_CHANNEL0;
}

nrf_gpiote_tasks_t PWM::getGpioteTaskOut(uint8_t index) {
	assert(index < 8, "invalid gpiote task index");
	switch(index) {
	case 0:
		return NRF_GPIOTE_TASKS_OUT_0;
	case 1:
		return NRF_GPIOTE_TASKS_OUT_1;
	case 2:
		return NRF_GPIOTE_TASKS_OUT_2;
	case 3:
		return NRF_GPIOTE_TASKS_OUT_3;
	case 4:
		return NRF_GPIOTE_TASKS_OUT_4;
	case 5:
		return NRF_GPIOTE_TASKS_OUT_5;
	case 6:
		return NRF_GPIOTE_TASKS_OUT_6;
	case 7:
		return NRF_GPIOTE_TASKS_OUT_7;
	}
	APP_ERROR_CHECK(NRF_ERROR_INVALID_PARAM);
	return NRF_GPIOTE_TASKS_OUT_0;
}

nrf_ppi_channel_t PWM::getPpiChannel(uint8_t index) {
	assert(index < 16, "invalid ppi channel index");
	switch(index) {
	case 0:
		return NRF_PPI_CHANNEL0;
	case 1:
		return NRF_PPI_CHANNEL1;
	case 2:
		return NRF_PPI_CHANNEL2;
	case 3:
		return NRF_PPI_CHANNEL3;
	case 4:
		return NRF_PPI_CHANNEL4;
	case 5:
		return NRF_PPI_CHANNEL5;
	case 6:
		return NRF_PPI_CHANNEL6;
	case 7:
		return NRF_PPI_CHANNEL7;
	case 8:
		return NRF_PPI_CHANNEL8;
	case 9:
		return NRF_PPI_CHANNEL9;
	case 10:
		return NRF_PPI_CHANNEL10;
	case 11:
		return NRF_PPI_CHANNEL11;
	case 12:
		return NRF_PPI_CHANNEL12;
	case 13:
		return NRF_PPI_CHANNEL13;
	case 14:
		return NRF_PPI_CHANNEL14;
	case 15:
		return NRF_PPI_CHANNEL15;
	}
	return NRF_PPI_CHANNEL0;
}

nrf_ppi_channel_group_t PWM::getPpiGroup(uint8_t index) {
	assert(index < 6, "invalid ppi group index");
	switch(index) {
	case 0:
		return NRF_PPI_CHANNEL_GROUP0;
	case 1:
		return NRF_PPI_CHANNEL_GROUP1;
	case 2:
		return NRF_PPI_CHANNEL_GROUP2;
	case 3:
		return NRF_PPI_CHANNEL_GROUP3;
	case 4:
		return NRF_PPI_CHANNEL_GROUP4;
	case 5:
		return NRF_PPI_CHANNEL_GROUP5;
	}
	return NRF_PPI_CHANNEL_GROUP0;
}

nrf_ppi_task_t PWM::getPpiTaskEnable(uint8_t index) {
	assert(index < 6, "invalid ppi group index");
	switch(index) {
	case 0:
		return NRF_PPI_TASK_CHG0_EN;
	case 1:
		return NRF_PPI_TASK_CHG1_EN;
	case 2:
		return NRF_PPI_TASK_CHG2_EN;
	case 3:
		return NRF_PPI_TASK_CHG3_EN;
	case 4:
		return NRF_PPI_TASK_CHG4_EN;
	case 5:
		return NRF_PPI_TASK_CHG5_EN;
	}
	return NRF_PPI_TASK_CHG0_EN;
}

nrf_ppi_task_t PWM::getPpiTaskDisable(uint8_t index) {
	assert(index < 6, "invalid ppi group index");
	switch(index) {
	case 0:
		return NRF_PPI_TASK_CHG0_DIS;
	case 1:
		return NRF_PPI_TASK_CHG1_DIS;
	case 2:
		return NRF_PPI_TASK_CHG2_DIS;
	case 3:
		return NRF_PPI_TASK_CHG3_DIS;
	case 4:
		return NRF_PPI_TASK_CHG4_DIS;
	case 5:
		return NRF_PPI_TASK_CHG5_DIS;
	}
	return NRF_PPI_TASK_CHG0_DIS;
}


// Interrupt handler
extern "C" void CS_PWM_TIMER_IRQ(void) {
//	if (nrf_timer_event_check(CS_PWM_TIMER, nrf_timer_compare_event_get(PERIOD_CHANNEL_IDX))) {
	// Clear and disable interrupt until next change.
	nrf_timer_event_clear(CS_PWM_TIMER, nrf_timer_compare_event_get(PERIOD_CHANNEL_IDX));
	nrf_timer_int_disable(CS_PWM_TIMER, nrf_timer_compare_int_get(PERIOD_CHANNEL_IDX));
	PWM::getInstance()._handleInterrupt();
//	}
}
