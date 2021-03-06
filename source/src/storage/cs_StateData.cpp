/**
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: Oct 9, 2019
 * License: LGPLv3+, Apache License 2.0, and/or MIT (triple-licensed)
 */

#include <cfg/cs_Config.h>
#include <common/cs_Types.h>
#include <storage/cs_StateData.h>

cs_ret_code_t getDefault(cs_state_data_t & data, const boards_config_t& boardsConfig)  {

	// for all non-string types we already know the to-be expected size
	data.size = TypeSize(data.type);

	switch(data.type) {
	case CS_TYPE::CONFIG_NAME: {
		data.size = MIN(data.size, sizeof(STRINGIFY(BLUETOOTH_NAME)));
		memcpy(data.value, STRINGIFY(BLUETOOTH_NAME), data.size);
		return ERR_SUCCESS;
	}
	case CS_TYPE::CONFIG_MESH_ENABLED:
		*(TYPIFY(CONFIG_MESH_ENABLED)*)data.value = CONFIG_MESH_ENABLED_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_ENCRYPTION_ENABLED:
		*(TYPIFY(CONFIG_ENCRYPTION_ENABLED)*)data.value = CONFIG_ENCRYPTION_ENABLED_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_IBEACON_ENABLED:
		*(TYPIFY(CONFIG_IBEACON_ENABLED)*)data.value = CONFIG_IBEACON_ENABLED_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SCANNER_ENABLED:
		*(TYPIFY(CONFIG_SCANNER_ENABLED)*)data.value = CONFIG_SCANNER_ENABLED_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_PWM_ALLOWED:
		*(TYPIFY(CONFIG_PWM_ALLOWED)*)data.value = CONFIG_PWM_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_START_DIMMER_ON_ZERO_CROSSING:
		*(TYPIFY(CONFIG_START_DIMMER_ON_ZERO_CROSSING)*)data.value = CONFIG_START_DIMMER_ON_ZERO_CROSSING_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SWITCH_LOCKED:
		*(TYPIFY(CONFIG_SWITCH_LOCKED)*)data.value = CONFIG_SWITCH_LOCK_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SWITCHCRAFT_ENABLED:
		*(TYPIFY(CONFIG_SWITCHCRAFT_ENABLED)*)data.value = CONFIG_SWITCHCRAFT_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_TAP_TO_TOGGLE_ENABLED:
		*(TYPIFY(CONFIG_TAP_TO_TOGGLE_ENABLED)*)data.value = CONFIG_TAP_TO_TOGGLE_ENABLED_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_TAP_TO_TOGGLE_RSSI_THRESHOLD_OFFSET:
		*(TYPIFY(CONFIG_TAP_TO_TOGGLE_RSSI_THRESHOLD_OFFSET)*)data.value = CONFIG_TAP_TO_TOGGLE_RSSI_THRESHOLD_OFFSET_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_IBEACON_MAJOR:
		*(TYPIFY(CONFIG_IBEACON_MAJOR)*)data.value = BEACON_MAJOR;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_IBEACON_MINOR:
		*(TYPIFY(CONFIG_IBEACON_MINOR)*)data.value = BEACON_MINOR;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_IBEACON_UUID: {
		BLEutil::parseUuid(STRINGIFY(BEACON_UUID), sizeof(STRINGIFY(BEACON_UUID)), data.value);
		return ERR_SUCCESS;
	}
	case CS_TYPE::CONFIG_IBEACON_TXPOWER:
		*(TYPIFY(CONFIG_IBEACON_TXPOWER)*)data.value = BEACON_RSSI;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_TX_POWER:
		*(TYPIFY(CONFIG_TX_POWER)*)data.value = TX_POWER;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_ADV_INTERVAL:
		*(TYPIFY(CONFIG_ADV_INTERVAL)*)data.value = ADVERTISEMENT_INTERVAL;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SCAN_DURATION:
		*(TYPIFY(CONFIG_SCAN_DURATION)*)data.value = SCAN_DURATION;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SCAN_BREAK_DURATION:
		*(TYPIFY(CONFIG_SCAN_BREAK_DURATION)*)data.value = SCAN_BREAK_DURATION;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_BOOT_DELAY:
		*(TYPIFY(CONFIG_BOOT_DELAY)*)data.value = CONFIG_BOOT_DELAY_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_MAX_CHIP_TEMP:
		*(TYPIFY(CONFIG_MAX_CHIP_TEMP)*)data.value = MAX_CHIP_TEMP;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SPHERE_ID:
		*(TYPIFY(CONFIG_SPHERE_ID)*)data.value = CONFIG_SPHERE_ID_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_CROWNSTONE_ID:
		*(TYPIFY(CONFIG_CROWNSTONE_ID)*)data.value = CONFIG_CROWNSTONE_ID_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_KEY_ADMIN:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_KEY_MEMBER:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_KEY_BASIC:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_KEY_SERVICE_DATA:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_MESH_DEVICE_KEY:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_MESH_APP_KEY:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_MESH_NET_KEY:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_KEY_LOCALIZATION:
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SCAN_INTERVAL:
		*(TYPIFY(CONFIG_SCAN_INTERVAL)*)data.value = SCAN_INTERVAL;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SCAN_WINDOW:
		*(TYPIFY(CONFIG_SCAN_WINDOW)*)data.value = SCAN_WINDOW;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_RELAY_HIGH_DURATION:
		*(TYPIFY(CONFIG_RELAY_HIGH_DURATION)*)data.value = RELAY_HIGH_DURATION;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_LOW_TX_POWER:
//		*(TYPIFY(CONFIG_LOW_TX_POWER)*)data.value = CONFIG_LOW_TX_POWER_DEFAULT;
		*(TYPIFY(CONFIG_LOW_TX_POWER)*)data.value = boardsConfig.minTxPower;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_VOLTAGE_MULTIPLIER:
//		*(TYPIFY(CONFIG_VOLTAGE_MULTIPLIER)*)data.value = CONFIG_VOLTAGE_MULTIPLIER_DEFAULT;
		*(TYPIFY(CONFIG_VOLTAGE_MULTIPLIER)*)data.value = boardsConfig.voltageMultiplier;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_CURRENT_MULTIPLIER:
//		*(TYPIFY(CONFIG_CURRENT_MULTIPLIER)*)data.value = CONFIG_CURRENT_MULTIPLIER_DEFAULT;
		*(TYPIFY(CONFIG_CURRENT_MULTIPLIER)*)data.value = boardsConfig.currentMultiplier;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_VOLTAGE_ADC_ZERO:
//		*(TYPIFY(CONFIG_VOLTAGE_ADC_ZERO)*)data.value = CONFIG_VOLTAGE_ZERO_DEFAULT;
		*(TYPIFY(CONFIG_VOLTAGE_ADC_ZERO)*)data.value = boardsConfig.voltageZero;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_CURRENT_ADC_ZERO:
//		*(TYPIFY(CONFIG_CURRENT_ADC_ZERO)*)data.value = CONFIG_CURRENT_ZERO_DEFAULT;
		*(TYPIFY(CONFIG_CURRENT_ADC_ZERO)*)data.value = boardsConfig.currentZero;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_POWER_ZERO:
//		*(TYPIFY(CONFIG_POWER_ZERO)*)data.value = CONFIG_POWER_ZERO_DEFAULT;
//		*(TYPIFY(CONFIG_POWER_ZERO)*)data.value = boardsConfig.powerZero;
		*(TYPIFY(CONFIG_POWER_ZERO)*)data.value = CONFIG_POWER_ZERO_INVALID;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_PWM_PERIOD: {
		LOGd("Got PWM period: %u", PWM_PERIOD);
		LOGd("Data value ptr: %p", data.value);
		*((uint32_t*)data.value) = 1;
		LOGd("data.value: %u", *((uint32_t*)data.value));
		*(TYPIFY(CONFIG_PWM_PERIOD)*)data.value = (TYPIFY(CONFIG_PWM_PERIOD))PWM_PERIOD;
		LOGd("data.value: %u", *((uint32_t*)data.value));
		return ERR_SUCCESS;
	}
	case CS_TYPE::CONFIG_SOFT_FUSE_CURRENT_THRESHOLD:
		*(TYPIFY(CONFIG_SOFT_FUSE_CURRENT_THRESHOLD)*)data.value = CURRENT_USAGE_THRESHOLD;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SOFT_FUSE_CURRENT_THRESHOLD_PWM:
		*(TYPIFY(CONFIG_SOFT_FUSE_CURRENT_THRESHOLD_PWM)*)data.value = CURRENT_USAGE_THRESHOLD_PWM;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_UP:
//		*(TYPIFY(CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_UP)*)data.value = CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_UP_DEFAULT;
		*(TYPIFY(CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_UP)*)data.value = boardsConfig.pwmTempVoltageThreshold;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_DOWN:
//		*(TYPIFY(CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_DOWN)*)data.value = CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_DOWN_DEFAULT;
		*(TYPIFY(CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_DOWN)*)data.value = boardsConfig.pwmTempVoltageThresholdDown;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_SWITCHCRAFT_THRESHOLD:
		*(TYPIFY(CONFIG_SWITCHCRAFT_THRESHOLD)*)data.value = SWITCHCRAFT_THRESHOLD;
		return ERR_SUCCESS;
	case CS_TYPE::CONFIG_UART_ENABLED:
		*(TYPIFY(CONFIG_UART_ENABLED)*)data.value = CS_SERIAL_ENABLED;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_RESET_COUNTER:
		*(TYPIFY(STATE_RESET_COUNTER)*)data.value = STATE_RESET_COUNTER_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_SWITCH_STATE: {
		switch_state_t *state = (TYPIFY(STATE_SWITCH_STATE)*)data.value;
		cs_switch_state_set_default(state);
		return ERR_SUCCESS;
	}
	case CS_TYPE::STATE_ACCUMULATED_ENERGY:
		*(TYPIFY(STATE_ACCUMULATED_ENERGY)*)data.value = STATE_ACCUMULATED_ENERGY_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_POWER_USAGE:
		*(TYPIFY(STATE_POWER_USAGE)*)data.value = STATE_POWER_USAGE_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_SCHEDULE: {
		schedule_list_t *schedule = (TYPIFY(STATE_SCHEDULE)*)data.value;
		cs_schedule_list_set_default(schedule);
		return ERR_SUCCESS;
	}
	case CS_TYPE::STATE_OPERATION_MODE:
		*(TYPIFY(STATE_OPERATION_MODE)*)data.value = STATE_OPERATION_MODE_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_TEMPERATURE:
		*(TYPIFY(STATE_TEMPERATURE)*)data.value = STATE_TEMPERATURE_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_TIME:
		*(TYPIFY(STATE_TIME)*)data.value = STATE_TIME_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_SUN_TIME:
		*reinterpret_cast<TYPIFY(STATE_SUN_TIME)*>(data.value) = set_sun_time_t();
	case CS_TYPE::STATE_FACTORY_RESET:
		*(TYPIFY(STATE_FACTORY_RESET)*)data.value = STATE_FACTORY_RESET_DEFAULT;
		return ERR_SUCCESS;
	case CS_TYPE::STATE_ERRORS: {
		state_errors_t* stateErrors = (TYPIFY(STATE_ERRORS)*)data.value;
		cs_state_errors_set_default(stateErrors);
		return ERR_SUCCESS;
	}
	case CS_TYPE::CONFIG_CURRENT_LIMIT:
		return ERR_NOT_IMPLEMENTED;
	case CS_TYPE::CONFIG_DO_NOT_USE:
		return ERR_NOT_AVAILABLE;
	case CS_TYPE::CMD_CONTROL_CMD:
	case CS_TYPE::CMD_DEC_CURRENT_RANGE:
	case CS_TYPE::CMD_DEC_VOLTAGE_RANGE:
	case CS_TYPE::CMD_ENABLE_ADC_DIFFERENTIAL_CURRENT:
	case CS_TYPE::CMD_ENABLE_ADC_DIFFERENTIAL_VOLTAGE:
	case CS_TYPE::CMD_ENABLE_ADVERTISEMENT:
	case CS_TYPE::CMD_ENABLE_LOG_CURRENT:
	case CS_TYPE::CMD_ENABLE_LOG_FILTERED_CURRENT:
	case CS_TYPE::CMD_ENABLE_LOG_POWER:
	case CS_TYPE::CMD_ENABLE_LOG_VOLTAGE:
	case CS_TYPE::CMD_ENABLE_MESH:
	case CS_TYPE::CMD_FACTORY_RESET:
	case CS_TYPE::CMD_INC_CURRENT_RANGE:
	case CS_TYPE::CMD_INC_VOLTAGE_RANGE:
	case CS_TYPE::CMD_RESET_DELAYED:
	case CS_TYPE::CMD_SEND_MESH_MSG:
	case CS_TYPE::CMD_SEND_MESH_MSG_KEEP_ALIVE:
	case CS_TYPE::CMD_SEND_MESH_MSG_MULTI_SWITCH:
	case CS_TYPE::CMD_SET_OPERATION_MODE:
	case CS_TYPE::CMD_SET_TIME:
	case CS_TYPE::CMD_SWITCH_OFF:
	case CS_TYPE::CMD_SWITCH_ON:
	case CS_TYPE::CMD_SWITCH_TOGGLE:
	case CS_TYPE::CMD_SWITCH:
	case CS_TYPE::CMD_MULTI_SWITCH:
	case CS_TYPE::CMD_TOGGLE_ADC_VOLTAGE_VDD_REFERENCE_PIN:
	case CS_TYPE::EVT_ADC_RESTARTED:
	case CS_TYPE::EVT_ADV_BACKGROUND:
	case CS_TYPE::EVT_ADV_BACKGROUND_PARSED:
	case CS_TYPE::EVT_ADVERTISEMENT_UPDATED:
	case CS_TYPE::EVT_BLE_CONNECT:
	case CS_TYPE::EVT_BLE_DISCONNECT:
	case CS_TYPE::EVT_BROWNOUT_IMPENDING:
	case CS_TYPE::EVT_CHIP_TEMP_ABOVE_THRESHOLD:
	case CS_TYPE::EVT_CHIP_TEMP_OK:
	case CS_TYPE::EVT_CURRENT_USAGE_ABOVE_THRESHOLD_DIMMER:
	case CS_TYPE::EVT_CURRENT_USAGE_ABOVE_THRESHOLD:
	case CS_TYPE::EVT_DEVICE_SCANNED:
	case CS_TYPE::EVT_DIMMER_FORCED_OFF:
	case CS_TYPE::EVT_DIMMER_OFF_FAILURE_DETECTED:
	case CS_TYPE::EVT_DIMMER_ON_FAILURE_DETECTED:
	case CS_TYPE::EVT_DIMMER_POWERED:
	case CS_TYPE::EVT_DIMMER_TEMP_ABOVE_THRESHOLD:
	case CS_TYPE::EVT_DIMMER_TEMP_OK:
	case CS_TYPE::CMD_DIMMING_ALLOWED:
	case CS_TYPE::EVT_KEEP_ALIVE:
	case CS_TYPE::EVT_KEEP_ALIVE_STATE:
	case CS_TYPE::EVT_MESH_TIME:
	case CS_TYPE::EVT_RELAY_FORCED_ON:
	case CS_TYPE::EVT_SCAN_STARTED:
	case CS_TYPE::EVT_SCAN_STOPPED:
	case CS_TYPE::EVT_SCHEDULE_ENTRIES_UPDATED:
	case CS_TYPE::EVT_SESSION_NONCE_SET:
	case CS_TYPE::EVT_SETUP_DONE:
	case CS_TYPE::EVT_STATE_EXTERNAL_STONE:
	case CS_TYPE::EVT_STORAGE_INITIALIZED:
	case CS_TYPE::EVT_STORAGE_WRITE_DONE:
	case CS_TYPE::EVT_STORAGE_REMOVE_DONE:
	case CS_TYPE::EVT_STORAGE_REMOVE_FILE_DONE:
	case CS_TYPE::EVT_STORAGE_GC_DONE:
	case CS_TYPE::EVT_STORAGE_FACTORY_RESET:
	case CS_TYPE::EVT_STORAGE_PAGES_ERASED:
	case CS_TYPE::EVT_MESH_FACTORY_RESET:
	case CS_TYPE::EVT_SWITCH_FORCED_OFF:
	case CS_TYPE::CMD_SWITCH_LOCKED:
	case CS_TYPE::EVT_TICK:
	case CS_TYPE::EVT_TIME_SET:
	case CS_TYPE::EVT_SAVE_BEHAVIOUR:
	case CS_TYPE::EVT_REPLACE_BEHAVIOUR:
	case CS_TYPE::EVT_REMOVE_BEHAVIOUR:
	case CS_TYPE::EVT_GET_BEHAVIOUR:
	case CS_TYPE::EVT_GET_BEHAVIOUR_INDICES:
	case CS_TYPE::EVT_BEHAVIOURSTORE_MUTATION:
	case CS_TYPE::EVT_PRESENCE_MUTATION:
	case CS_TYPE::EVT_BEHAVIOUR_SWITCH_STATE:
	case CS_TYPE::CMD_SET_RELAY:
	case CS_TYPE::CMD_SET_DIMMER:
	case CS_TYPE::EVT_PROFILE_LOCATION:
		return ERR_NOT_FOUND;
	}
	return ERR_NOT_FOUND;
}

PersistenceMode DefaultLocation(CS_TYPE const & type) {
	switch(type) {
	case CS_TYPE::CONFIG_NAME:
	case CS_TYPE::CONFIG_PWM_PERIOD:
	case CS_TYPE::CONFIG_IBEACON_MAJOR:
	case CS_TYPE::CONFIG_IBEACON_MINOR:
	case CS_TYPE::CONFIG_IBEACON_UUID:
	case CS_TYPE::CONFIG_IBEACON_TXPOWER:
	case CS_TYPE::CONFIG_TX_POWER:
	case CS_TYPE::CONFIG_ADV_INTERVAL:
	case CS_TYPE::CONFIG_SCAN_DURATION:
	case CS_TYPE::CONFIG_SCAN_BREAK_DURATION:
	case CS_TYPE::CONFIG_BOOT_DELAY:
	case CS_TYPE::CONFIG_MAX_CHIP_TEMP:
	case CS_TYPE::CONFIG_CURRENT_LIMIT:
	case CS_TYPE::CONFIG_MESH_ENABLED:
	case CS_TYPE::CONFIG_ENCRYPTION_ENABLED:
	case CS_TYPE::CONFIG_IBEACON_ENABLED:
	case CS_TYPE::CONFIG_SCANNER_ENABLED:
	case CS_TYPE::CONFIG_SPHERE_ID:
	case CS_TYPE::CONFIG_CROWNSTONE_ID:
	case CS_TYPE::CONFIG_KEY_ADMIN:
	case CS_TYPE::CONFIG_KEY_MEMBER:
	case CS_TYPE::CONFIG_KEY_BASIC:
	case CS_TYPE::CONFIG_KEY_SERVICE_DATA:
	case CS_TYPE::CONFIG_MESH_DEVICE_KEY:
	case CS_TYPE::CONFIG_MESH_APP_KEY:
	case CS_TYPE::CONFIG_MESH_NET_KEY:
	case CS_TYPE::CONFIG_KEY_LOCALIZATION:
	case CS_TYPE::CONFIG_SCAN_INTERVAL:
	case CS_TYPE::CONFIG_SCAN_WINDOW:
	case CS_TYPE::CONFIG_RELAY_HIGH_DURATION:
	case CS_TYPE::CONFIG_LOW_TX_POWER:
	case CS_TYPE::CONFIG_VOLTAGE_MULTIPLIER:
	case CS_TYPE::CONFIG_CURRENT_MULTIPLIER:
	case CS_TYPE::CONFIG_VOLTAGE_ADC_ZERO:
	case CS_TYPE::CONFIG_CURRENT_ADC_ZERO:
	case CS_TYPE::CONFIG_POWER_ZERO:
	case CS_TYPE::CONFIG_SOFT_FUSE_CURRENT_THRESHOLD:
	case CS_TYPE::CONFIG_SOFT_FUSE_CURRENT_THRESHOLD_PWM:
	case CS_TYPE::CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_UP:
	case CS_TYPE::CONFIG_PWM_TEMP_VOLTAGE_THRESHOLD_DOWN:
	case CS_TYPE::CONFIG_PWM_ALLOWED:
	case CS_TYPE::CONFIG_START_DIMMER_ON_ZERO_CROSSING:
	case CS_TYPE::CONFIG_SWITCH_LOCKED:
	case CS_TYPE::CONFIG_SWITCHCRAFT_ENABLED:
	case CS_TYPE::CONFIG_SWITCHCRAFT_THRESHOLD:
	case CS_TYPE::CONFIG_TAP_TO_TOGGLE_ENABLED:
	case CS_TYPE::CONFIG_TAP_TO_TOGGLE_RSSI_THRESHOLD_OFFSET:
	case CS_TYPE::CONFIG_UART_ENABLED:
	case CS_TYPE::STATE_RESET_COUNTER:
	case CS_TYPE::STATE_OPERATION_MODE:
	case CS_TYPE::STATE_SWITCH_STATE:
	case CS_TYPE::STATE_SCHEDULE:
		return PersistenceMode::FLASH;
	case CS_TYPE::CONFIG_DO_NOT_USE:
	case CS_TYPE::STATE_ACCUMULATED_ENERGY:
	case CS_TYPE::STATE_POWER_USAGE:
	case CS_TYPE::STATE_TEMPERATURE:
	case CS_TYPE::STATE_TIME:
	case CS_TYPE::STATE_SUN_TIME:
	case CS_TYPE::STATE_FACTORY_RESET:
	case CS_TYPE::STATE_ERRORS:
	case CS_TYPE::CMD_SWITCH_OFF:
	case CS_TYPE::CMD_SWITCH_ON:
	case CS_TYPE::CMD_SWITCH_TOGGLE:
	case CS_TYPE::CMD_SWITCH:
	case CS_TYPE::CMD_MULTI_SWITCH:
	case CS_TYPE::EVT_ADV_BACKGROUND:
	case CS_TYPE::EVT_ADV_BACKGROUND_PARSED:
	case CS_TYPE::EVT_ADVERTISEMENT_UPDATED:
	case CS_TYPE::EVT_SCAN_STARTED:
	case CS_TYPE::EVT_SCAN_STOPPED:
	case CS_TYPE::EVT_DEVICE_SCANNED:
	case CS_TYPE::EVT_CURRENT_USAGE_ABOVE_THRESHOLD_DIMMER:
	case CS_TYPE::EVT_CURRENT_USAGE_ABOVE_THRESHOLD:
	case CS_TYPE::EVT_DIMMER_ON_FAILURE_DETECTED:
	case CS_TYPE::EVT_DIMMER_OFF_FAILURE_DETECTED:
	case CS_TYPE::EVT_MESH_TIME:
	case CS_TYPE::EVT_SCHEDULE_ENTRIES_UPDATED:
	case CS_TYPE::EVT_BLE_CONNECT:
	case CS_TYPE::EVT_BLE_DISCONNECT:
	case CS_TYPE::EVT_BROWNOUT_IMPENDING:
	case CS_TYPE::EVT_SESSION_NONCE_SET:
	case CS_TYPE::EVT_KEEP_ALIVE:
	case CS_TYPE::EVT_KEEP_ALIVE_STATE:
	case CS_TYPE::EVT_DIMMER_FORCED_OFF:
	case CS_TYPE::EVT_SWITCH_FORCED_OFF:
	case CS_TYPE::EVT_RELAY_FORCED_ON:
	case CS_TYPE::EVT_CHIP_TEMP_ABOVE_THRESHOLD:
	case CS_TYPE::EVT_CHIP_TEMP_OK:
	case CS_TYPE::EVT_DIMMER_TEMP_ABOVE_THRESHOLD:
	case CS_TYPE::EVT_DIMMER_TEMP_OK:
	case CS_TYPE::EVT_TICK:
	case CS_TYPE::EVT_TIME_SET:
	case CS_TYPE::EVT_DIMMER_POWERED:
	case CS_TYPE::CMD_DIMMING_ALLOWED:
	case CS_TYPE::CMD_SWITCH_LOCKED:
	case CS_TYPE::EVT_STATE_EXTERNAL_STONE:
	case CS_TYPE::EVT_STORAGE_INITIALIZED:
	case CS_TYPE::EVT_STORAGE_WRITE_DONE:
	case CS_TYPE::EVT_STORAGE_REMOVE_DONE:
	case CS_TYPE::EVT_STORAGE_REMOVE_FILE_DONE:
	case CS_TYPE::EVT_STORAGE_GC_DONE:
	case CS_TYPE::EVT_STORAGE_FACTORY_RESET:
	case CS_TYPE::EVT_STORAGE_PAGES_ERASED:
	case CS_TYPE::EVT_MESH_FACTORY_RESET:
	case CS_TYPE::EVT_SETUP_DONE:
	case CS_TYPE::EVT_ADC_RESTARTED:
	case CS_TYPE::CMD_ENABLE_LOG_POWER:
	case CS_TYPE::CMD_ENABLE_LOG_CURRENT:
	case CS_TYPE::CMD_ENABLE_LOG_VOLTAGE:
	case CS_TYPE::CMD_ENABLE_LOG_FILTERED_CURRENT:
	case CS_TYPE::CMD_RESET_DELAYED:
	case CS_TYPE::CMD_ENABLE_ADVERTISEMENT:
	case CS_TYPE::CMD_ENABLE_MESH:
	case CS_TYPE::CMD_TOGGLE_ADC_VOLTAGE_VDD_REFERENCE_PIN:
	case CS_TYPE::CMD_ENABLE_ADC_DIFFERENTIAL_CURRENT:
	case CS_TYPE::CMD_ENABLE_ADC_DIFFERENTIAL_VOLTAGE:
	case CS_TYPE::CMD_INC_VOLTAGE_RANGE:
	case CS_TYPE::CMD_DEC_VOLTAGE_RANGE:
	case CS_TYPE::CMD_INC_CURRENT_RANGE:
	case CS_TYPE::CMD_DEC_CURRENT_RANGE:
	case CS_TYPE::CMD_CONTROL_CMD:
	case CS_TYPE::CMD_SET_OPERATION_MODE:
	case CS_TYPE::CMD_SEND_MESH_MSG:
	case CS_TYPE::CMD_SEND_MESH_MSG_KEEP_ALIVE:
	case CS_TYPE::CMD_SEND_MESH_MSG_MULTI_SWITCH:
	case CS_TYPE::CMD_SET_TIME:
	case CS_TYPE::CMD_FACTORY_RESET:
	case CS_TYPE::EVT_SAVE_BEHAVIOUR:
	case CS_TYPE::EVT_REPLACE_BEHAVIOUR:
	case CS_TYPE::EVT_REMOVE_BEHAVIOUR:
	case CS_TYPE::EVT_GET_BEHAVIOUR:
	case CS_TYPE::EVT_GET_BEHAVIOUR_INDICES:
	case CS_TYPE::EVT_BEHAVIOURSTORE_MUTATION:
	case CS_TYPE::EVT_PRESENCE_MUTATION:
	case CS_TYPE::EVT_BEHAVIOUR_SWITCH_STATE:
	case CS_TYPE::CMD_SET_RELAY:
	case CS_TYPE::CMD_SET_DIMMER:
	case CS_TYPE::EVT_PROFILE_LOCATION:
		return PersistenceMode::RAM;
	}
	// should not reach this
	return PersistenceMode::RAM;
}
