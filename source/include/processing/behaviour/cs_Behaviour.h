/*
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: Dec 20, 2019
 * License: LGPLv3+, Apache License 2.0, and/or MIT (triple-licensed)
 */

#pragma once

#include <stdint.h>

/**
 * Object that defines when a state transition should occur.
 * 
 * It abstracts predicates such as:
 * "fade to 100% in 10 minutes, starting 30 minutes before sunrise, if anyone is in this room"
 */
class Behaviour {
    // TODO(Arend, 23-09-2019): datatypes and implementation still susceptible to change.
    public:
    typedef uint32_t time_t; // let's say, seconds since midnight (00:00)
    typedef uint8_t presence_data_t;

    Behaviour() = default;
    Behaviour(time_t from, time_t until, 
      presence_data_t presencemask,
      bool intendedStateWhenBehaviourIsValid);

    /**
     * Returns the intended state when this behaviour is valid.
     */
    bool value() const;

    inline time_t from() const {return behaviourappliesfrom; }
    inline time_t until() const { return behaviourappliesuntil; }

    /**
     * Does the behaviour apply to the current situation?
     */
    bool isValid(time_t currenttime, presence_data_t currentpresence) const;

    private:
    bool isValid(time_t currenttime) const;
    bool isValid(presence_data_t currentpresence) const;

    time_t behaviourappliesfrom = 0x0000;
    time_t behaviourappliesuntil = 0x0000;
    presence_data_t requiredpresencebitmask = 0x00;

    // true if on, false if off.
    bool intendedStateWhenBehaviourIsValid = false;
};