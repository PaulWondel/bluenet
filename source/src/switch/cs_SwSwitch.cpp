/**
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: Sep 26, 2019
 * License: LGPLv3+, Apache License 2.0, and/or MIT (triple-licensed)
 */

#include <switch/cs_SwSwitch.h>
#include <common/cs_Types.h>
#include <drivers/cs_Serial.h>
#include <storage/cs_State.h>

#include <events/cs_EventListener.h>
#include <events/cs_EventDispatcher.h>

#define SWSWITCH_LOG() LOGd("SwSwitch::%s",__func__)
#define SWSWITCH_LOCKED_LOG() LOGd("refused because of lock: %s",__func__)

#define SWSWITCH_LOG_STATE(s) LOGd("state: {relay=%d, dim=%x}", s.state.relay,s.state.dimmer)
#define SWSWITCH_LOG_CURRENT_STATE() LOGd("current state: {relay=%d, dim=%x}", currentState.state.relay,currentState.state.dimmer)

// =========================================================================
// ================================ Private ================================
// =========================================================================

// hardware validation 

void SwSwitch::startDimmerPowerCheck(){
    SWSWITCH_LOG();

    if(checkedDimmerPowerUsage || dimmerCheckCountDown != 0){
        return;
    }
    dimmerCheckCountDown = dimmerCheckCountDown_initvalue;
}

void SwSwitch::checkDimmerPower() {

    SWSWITCH_LOG();
    LOGd("checkDimmerPower: allowDimming: %d - currentState.state.dimmer: %d", allowDimming, currentState.state.dimmer);
	if (!allowDimming || currentState.state.dimmer == 0) {
        // doesn't make sense to measure anything when the dimmer is turned off
		return;
	}

	// Check if dimmer is on, but power usage is low.
	// In that case, assume the dimmer isn't working due to a cold boot.
	// So turn dimmer off and relay on.

	TYPIFY(STATE_POWER_USAGE) powerUsage;
	State::getInstance().get(CS_TYPE::STATE_POWER_USAGE, &powerUsage, sizeof(powerUsage));
	TYPIFY(CONFIG_POWER_ZERO) powerZero;
	State::getInstance().get(CS_TYPE::CONFIG_POWER_ZERO, &powerZero, sizeof(powerZero));

	LOGd("powerUsage=%i powerZero=%i", powerUsage, powerZero);

	if (powerUsage < DIMMER_BOOT_CHECK_POWER_MW 
		|| (powerUsage < DIMMER_BOOT_CHECK_POWER_MW_UNCALIBRATED 
			&& powerZero == CONFIG_POWER_ZERO_INVALID)
		) {

        if (measuredDimmerPowerUsage){
            // uh oh.. what do we do when dimmer circuit lost power?
            // strange, this would be a second call to checkDimmerPower,
            // which shouldn't occur in the first place.
        }
		measuredDimmerPowerUsage = false;
        forceDimmerOff();
	} else {
        if (!measuredDimmerPowerUsage){
            //Dimmer has finished powering
            TYPIFY(EVT_DIMMER_POWERED) powered = true;
		    event_t event(CS_TYPE::EVT_DIMMER_POWERED, &powered, sizeof(powered));
		    EventDispatcher::getInstance().dispatch(event);

            measuredDimmerPowerUsage = true;
        } else {
            // confirmed that the dimmer circuit is still powered. Yay.
        }
    }
}

bool SwSwitch::isDimmerCircuitPowered(){
    return dimmerPowerUpCountDown == 0 || measuredDimmerPowerUsage;
}

// error state semantics

TYPIFY(STATE_ERRORS) SwSwitch::getErrorState(){
    TYPIFY(STATE_ERRORS) stateErrors;
	State::getInstance().get(CS_TYPE::STATE_ERRORS, &stateErrors, sizeof(stateErrors));

    return stateErrors;
}

bool SwSwitch::errorStateOK(){
    return getErrorState().asInt == 0;
}

bool SwSwitch::isSwitchFried(){
    TYPIFY(STATE_ERRORS) stateErrors = getErrorState();

    return stateErrors.errors.chipTemp 
        || stateErrors.errors.overCurrent;
}

bool SwSwitch::hasDimmingFailed(){
    TYPIFY(STATE_ERRORS) stateErrors = getErrorState();

    return stateErrors.errors.overCurrentDimmer 
		|| stateErrors.errors.dimmerTemp 
		|| stateErrors.errors.dimmerOn;
}

// functional semantics (derrived from error state)

bool SwSwitch::isSafeToTurnRelayOn() {
	return hasDimmingFailed() || !isSwitchFried();
}

bool SwSwitch::isSafeToTurnRelayOff(){
    return !hasDimmingFailed();
}

bool SwSwitch::isSafeToDim(){
    return !hasDimmingFailed() && !isSwitchFried();
}

// storage functionality

/**
 * Store the state immediately when relay value changed, 
 * as the dim value often changes a lot in bursts.
 * Compare it against given oldVal, instead of switch state 
 * stored in State, as that is always changed immediately
 * 
 * (just not the value on flash).
 */
void SwSwitch::store(switch_state_t nextState) {
    SWSWITCH_LOG();

	bool persistNow = false;
    // TODO(Arend): handle persistNow/later...

	if (nextState.asInt != currentState.asInt) {
		persistNow = (nextState.state.relay != currentState.state.relay);
	}

	cs_state_data_t stateData (CS_TYPE::STATE_SWITCH_STATE, 
        reinterpret_cast<uint8_t*>(&nextState), sizeof(nextState));

	if (persistNow) {
		State::getInstance().set(stateData);
	} else {
		State::getInstance().setDelayed(stateData, SWITCH_DELAYED_STORE_MS / 1000);
	}

    currentState = nextState;
    SWSWITCH_LOG_CURRENT_STATE();
}


void SwSwitch::storeRelayStateUpdate(bool is_on){
    SWSWITCH_LOG();
    switch_state_t nextState = currentState;
    nextState.state.relay = is_on;
    store(nextState);
}

void SwSwitch::storeIntensityStateUpdate(uint8_t intensity){
    SWSWITCH_LOG();
    switch_state_t nextState = currentState;
    nextState.state.dimmer = intensity;
    store(nextState);
}

// forcing hardwareSwitch

void SwSwitch::forceRelayOn() {
    SWSWITCH_LOG();
    hwSwitch.setRelay(true);
    storeRelayStateUpdate(true);
	
	event_t event(CS_TYPE::EVT_RELAY_FORCED_ON);
	EventDispatcher::getInstance().dispatch(event);
	
    // Try again later, in case the first one didn't work..
    // Todo(Arend 01-10-2019) do we really need this? it would be better if 
    // calling scope decides if another forceSwitchOn() call is necessary.
	// delayedSwitch(100, 5);
}

void SwSwitch::forceSwitchOff() {
    SWSWITCH_LOG();
	hwSwitch.setIntensity(0);
	hwSwitch.setRelay(false);
    // hwSwitch.setDimmerPower(false);

    switch_state_t nextState;
    nextState.state.dimmer = 0;
    nextState.state.relay = 0;
    store(nextState);

	event_t event(CS_TYPE::EVT_SWITCH_FORCED_OFF);
	EventDispatcher::getInstance().dispatch(event);
	
    // Try again later, in case the first one didn't work..
    // Todo(Arend 01-10-2019) do we really need this? it would be better if 
    // calling scope decides if another forceSwitchOff() call is necessary.
	// delayedSwitch(0, 5);
}

void SwSwitch::forceDimmerOff() {
    SWSWITCH_LOG();
	hwSwitch.setIntensity(0);

    // as there is no mechanism to turn it back on this isn't done yet, 
    // but it would be safer to cut power to the dimmer if in error I suppose.
    // hwSwitch.setDimmerPower(false);

    storeIntensityStateUpdate(0);

	event_t event(CS_TYPE::EVT_DIMMER_FORCED_OFF);
	EventDispatcher::getInstance().dispatch(event);
}

void SwSwitch::resetToCurrentState(){
    SWSWITCH_LOG();
    switch_state_t actualNextState = {0};

    if(currentState.state.dimmer){
        if(isDimmerCircuitPowered() && isSafeToDim()){
            hwSwitch.setIntensity(currentState.state.dimmer);
            hwSwitch.setRelay(false);

            actualNextState.state.dimmer = currentState.state.dimmer;
            actualNextState.state.relay = currentState.state.relay;
        }
    } else {
        if(currentState.state.relay){
            if(isSafeToTurnRelayOn()){
                hwSwitch.setRelay(true);
                hwSwitch.setIntensity(0);
                
                actualNextState.state.relay = true;
                actualNextState.state.dimmer = 0;
            }
        } else {
            if(isSafeToTurnRelayOff()){
                hwSwitch.setRelay(false);
                hwSwitch.setIntensity(0);

                actualNextState.state.relay = false;
                actualNextState.state.dimmer = 0;
            }
        }
    }

    store(actualNextState);
}

void SwSwitch::setIntensity_unchecked(uint8_t intensity_value){
    hwSwitch.setIntensity(intensity_value);
    storeIntensityStateUpdate(intensity_value);
}

void SwSwitch::setRelay_unchecked(bool relay_state){
    hwSwitch.setRelay(relay_state);
    storeRelayStateUpdate(relay_state);
}

// ========================================================================
// ================================ Public ================================
// ========================================================================

// ================== SwSwitch ================

SwSwitch::SwSwitch(HwSwitch hw_switch): hwSwitch(hw_switch){
    SWSWITCH_LOG();
    // load currentState from State. 
    State::getInstance().get(CS_TYPE::STATE_SWITCH_STATE, &currentState, sizeof(currentState));

    // ensure the dimmer gets power as the rest of the SwSwitch code assumes 
    // that setIntensity calls will have visible effect.
    // note: dimmer power is not persisted, so we don't need to store this anywhere.
    hwSwitch.setDimmerPower(true);

    resetToCurrentState();
}

void SwSwitch::setAllowSwitching(bool allowed) {
    allowSwitching = allowed;
    bool switch_locked = !allowed;
    State::getInstance().set(CS_TYPE::CONFIG_SWITCH_LOCKED, &switch_locked, sizeof(switch_locked));
}

void SwSwitch::setAllowDimming(bool allowed) {
    if(!allowSwitching){
        SWSWITCH_LOCKED_LOG();
        return;
    }

    SWSWITCH_LOG();
    allowDimming = allowed;
    State::getInstance().set(CS_TYPE::CONFIG_PWM_ALLOWED, &allowed, sizeof(allowed));

    if(!allowDimming || hasDimmingFailed()){
        // fix state on disallow
        setIntensity(0);

        if(currentState.state.dimmer != 0){
            // turn on to full power if we were dimmed to some
            // percentage, but aren't allowed to.
            setRelay(true);
        }
    }
}

void SwSwitch::toggle(){
    if(!allowSwitching){
        SWSWITCH_LOCKED_LOG();
        return;
    }

    // TODO(Arend, 08-10-2019): toggle should be upgraded when twilight is implemented
    if(currentState.state.relay == 1 || currentState.state.dimmer > 0){
        setIntensity(0);
    } else {
        setIntensity(100);
    }
}

void SwSwitch::setDimmer(uint8_t value){
    if(!allowSwitching){
        SWSWITCH_LOCKED_LOG();
        return;
    }

    SWSWITCH_LOG();
    LOGd("intensity: %d",value);

    if( value > 0 && (!allowDimming || !isSafeToDim()) ){
        // can't turn dimming on when it has failed or disallowed.
        // let's clamp the value to 'on' or 'off' if the value
        // clearly is one or the other.
        // Todo(Arend): double check if this is desired.

        LOGw("setIntensity called but not %s to dim - attempting to resolve command",
            !allowDimming? "allowed" : "safe");

        constexpr uint8_t threshold = 25; // must be <50
        
        if (value > 50 + threshold){
            LOGw("setIntensity resolved: on");
            // bypass dimmer to turn on
            setRelay_unchecked(true);
            setIntensity_unchecked(0);

        } else if(value < 50 - threshold){
            LOGw("setIntensity resolved: off");
            setIntensity(0); // (1-level recursion at most.)
        } else {
            LOGd("setIntensity can't use dimmer but parameter too ambiguous to make a guess")
        }

        return;
    }

    if( !checkedDimmerPowerUsage 
            && !isDimmerCircuitPowered()
            && value > 0) {
        // TODO(Arend): maybe round value up to a minimal test intensity?
        LOGw("early call to setIntensity, setting timer for DimmerPower");
        
        // briefly set the dimmer intensity to [value] if this wasn't tried
        // before
        setIntensity_unchecked(value);
        setRelay_unchecked(false);

        // Ensure that if the dimmer circuit isn't powered yet
        // the dimmer will be switched off eventually.
        // (Which will revert the intensity to 0 if unsuccessful)
        startDimmerPowerCheck();

        return;
    }

    if( isDimmerCircuitPowered() ){
        LOGw("setIntensity: normal operation mode, calling setState_unchecked");
        // OK to set the intended value since it is safe to dim (or value is 0),
        // and dimmer circuit is powered.
        setIntensity_unchecked(value);
        setRelay_unchecked(false);
    }
}

// ================== ISwitch ==============

void SwSwitch::setRelay(bool is_on){
    if(!allowSwitching){
        SWSWITCH_LOCKED_LOG();
        return;
    }

    SWSWITCH_LOG();

    if(is_on && !isSafeToTurnRelayOn()){
        // intent to turn on, but not safe
        return;
    }
    if(!is_on && !isSafeToTurnRelayOff()){
        // intent to turn off, but not safe
        return;
    }

    setRelay_unchecked(is_on);
}

void SwSwitch::setIntensity(uint8_t value){
    if(!allowSwitching){
        SWSWITCH_LOCKED_LOG()
        return;
    }

    SWSWITCH_LOG();

    if( value > 0 
        &&( !allowDimming 
            || !isSafeToDim()
            || !isDimmerCircuitPowered()) ){
        return;
    }

    setIntensity_unchecked(value); 
}

void SwSwitch::setDimmerPower(bool is_on){
    if(!allowSwitching){
        SWSWITCH_LOCKED_LOG();
        return;
    }

    hwSwitch.setDimmerPower(is_on);
}

// ================== EventListener =============

void SwSwitch::handleEvent(event_t& evt){
    switch(evt.type){
        case CS_TYPE::EVT_CURRENT_USAGE_ABOVE_THRESHOLD_DIMMER:
        case CS_TYPE::EVT_DIMMER_TEMP_ABOVE_THRESHOLD:
        case CS_TYPE::EVT_DIMMER_ON_FAILURE_DETECTED:
            SWSWITCH_LOG();
            // First set relay on, so that the switch doesn't first turn off, and later on again.
            // The relay protects the dimmer, because the current will flow through the relay.
            forceRelayOn();
            forceDimmerOff();
            break;
        case CS_TYPE::EVT_CURRENT_USAGE_ABOVE_THRESHOLD:
        case CS_TYPE::EVT_CHIP_TEMP_ABOVE_THRESHOLD:
            SWSWITCH_LOG();
            forceSwitchOff();
            break;
        case CS_TYPE::CMD_DIMMING_ALLOWED: {
            SWSWITCH_LOG();
            auto typd = reinterpret_cast<TYPIFY(CMD_DIMMING_ALLOWED)*>(evt.data);
            setAllowDimming(*typd);
            break;
        }
        case CS_TYPE::CMD_SWITCH_LOCKED: {
            SWSWITCH_LOG();
            auto typd = reinterpret_cast<TYPIFY(CMD_SWITCH_LOCKED)*>(evt.data);
            setAllowSwitching(*typd);
            break;
        }
        case CS_TYPE::STATE_SWITCH_STATE: {
            switch_state_t* typd = reinterpret_cast<TYPIFY(STATE_SWITCH_STATE)*>(evt.data);
            LOGd("switch state update: relay(%d) dim(%d)", typd->state.relay, typd->state.dimmer);
            break;
        }
        case CS_TYPE::EVT_TICK: {
            if (dimmerPowerUpCountDown && --dimmerPowerUpCountDown == 0){
                LOGw("dimmerPowerUpCountDown timed out");
            }
            if(dimmerCheckCountDown && --dimmerCheckCountDown == 0){
                LOGw("dimmerCheckCountDown timed out");
                checkDimmerPower();
                checkedDimmerPowerUsage = true;
            }
            break;
        }
        default: break;
    }
}

