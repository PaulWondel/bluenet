/*
 * Author: Crownstone Team
 * Copyright: Crownstone (https://crownstone.rocks)
 * Date: 16 Dec., 2019
 * License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed)
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Create Section type for functions
#define ARDUINO_HANDLER __attribute__ (( section(".arduino_handlers"))) 

// Test function that will be used to call arduino
void ARDUINO_HANDLER arduinoCommand();

extern struct arduino_handler __start_arduino_handlers;
extern struct arduino_handler __stop_arduino_handlers;

#ifdef __cplusplus
}
#endif
