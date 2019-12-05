/**
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: Sep 23, 2019
 * License: LGPLv3+, Apache License 2.0, and/or MIT (triple-licensed)
 */

#include <processing/behaviour/cs_Behaviour.h>
#include <util/cs_WireFormat.h>
#include <drivers/cs_Serial.h>

#include <algorithm>

Behaviour::Behaviour(
            uint8_t intensity,
            DayOfWeekBitMask activedaysofweek,
            TimeOfDay from, 
            TimeOfDay until, 
            PresenceCondition presencecondition) :
        activeIntensity (intensity),
        activeDays(activedaysofweek),
        behaviourAppliesFrom (from),
        behaviourAppliesUntil (until),
        presenceCondition (presencecondition)
    {
}

Behaviour::Behaviour(std::array<uint8_t, 26> arr) : 
    Behaviour(
        WireFormat::deserialize<uint8_t>(arr.data() + 0, 1),
        // WireFormat::deserialize<uint8_t>(arr.data() + 1, 1), // unused byte, 'options'
        WireFormat::deserialize<uint8_t>(arr.data() + 2, 1),
        WireFormat::deserialize<TimeOfDay>(arr.data() + 3, 5),
        WireFormat::deserialize<TimeOfDay>(arr.data() + 8, 5),
        WireFormat::deserialize<PresenceCondition>(arr.data() + 13, 13) ){
}

Behaviour::SerializedDataFormat Behaviour::serialize() const{
    SerializedDataFormat result;
    std::copy_n(std::begin(WireFormat::serialize(activeIntensity)),       1, std::begin(result) + 0);
    std::copy_n(std::begin(WireFormat::serialize(activeDays)),            1, std::begin(result) + 2);
    std::copy_n(std::begin(WireFormat::serialize(behaviourAppliesFrom)),  5, std::begin(result) + 3);
    std::copy_n(std::begin(WireFormat::serialize(behaviourAppliesUntil)), 5, std::begin(result) + 8);
    std::copy_n(std::begin(WireFormat::serialize(presenceCondition)),     13, std::begin(result) + 13);
    return result;
}

uint8_t Behaviour::value() const {
    return activeIntensity;
}

TimeOfDay Behaviour::from() const {
    return behaviourAppliesFrom; 
}

TimeOfDay Behaviour::until() const {
    return behaviourAppliesUntil; 
}

bool Behaviour::isValid(TimeOfDay currenttime, PresenceStateDescription currentpresence) const{
    return isValid(currenttime) && isValid(currentpresence);
}

bool Behaviour::isValid(TimeOfDay currenttime) const{
    return from() < until() // ensure proper midnight roll-over 
        ? (from() <= currenttime && currenttime < until()) 
        : (from() <= currenttime || currenttime < until());
}

bool Behaviour::isValid(PresenceStateDescription currentpresence) const{
    return presenceCondition(currentpresence);
}

void Behaviour::print() const {
    uint32_t rooms[2] = {
        static_cast<uint32_t>(presenceCondition.pred.RoomsBitMask >> 0 ),
        static_cast<uint32_t>(presenceCondition.pred.RoomsBitMask >> 32)
    };

    LOGd("Behaviour: %02d:%02d:%02d - %02d:%02d:%02d %3d%%, days(%x), presencetype(%d) roommask(%x %x)",
        from().h(),from().m(),from().s(),
        until().h(),until().m(),until().s(),
        activeIntensity,
        activeDays,
        presenceCondition.pred.cond,
        rooms[1],rooms[0]
    );

    // auto ser = presenceCondition.pred.serialize();
    // for(auto b : ser){
    //     LOGd("%02x",b);
    // }

}