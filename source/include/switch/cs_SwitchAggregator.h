/**
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: Sep 26, 2019
 * License: LGPLv3+, Apache License 2.0, and/or MIT (triple-licensed)
 */

#include "switch/cs_SwSwitch.h"
#include "events/cs_EventListener.h"

#include <optional>

/**
 * Handler that aggregates events related to switching such as SwitchCraft,
 * Behaviours, Twilight and App/User side actions. Based on the incoming data
 * this object decides what state to set the SwSwitch to.
 */
class SwitchAggregator : public EventListener {
    public:
    static SwitchAggregator& getInstance();
    
    void init(SwSwitch s);

    virtual void handleEvent(event_t& evt) override;
 
    // ISwitch interface for dev
    void developerSetRelay(bool is_on);
    void developerSetDimmer(bool is_on);
    void developerSetIntensity(uint8_t value);
    
    // ISwitch interface for user/app
    void userSetRelay(bool is_on);
    void userSetDimmer(bool is_on);
    void userSetIntensity(uint8_t value);

    // interface for switchcraft/system

    private:
    SwitchAggregator() = default;
    virtual ~SwitchAggregator() noexcept {};
    SwitchAggregator& operator= (const SwitchAggregator&) = delete;

    typedef uint16_t SwitchState;

    // when the swith aggregator is initialized with a board
    // that can switch, swSwitch contains that value.
    std::optional<SwSwitch> swSwitch;

    SwitchState behaviourState;
    SwitchState userOverrideState;


};