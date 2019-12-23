/*
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: 13 Dec., 2019
 * License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed)
 */

#include <arduino/cs_Arduino.h>

#include <drivers/cs_Serial.h>

/** 
 * Arduino command.
 */
static void arduinoCommand(const char value) {
	LOGd("Arduino command %i", value);
}

REGISTER_ARDUINO_HANDLER(arduinoCommand);
