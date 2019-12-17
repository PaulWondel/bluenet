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

/*
// Create Section type for functions
 #define ARDUINO_HANDLER __attribute__ (( section(".arduino_handlers"))) 

// Test function that will be used to call arduino
void ARDUINO_HANDLER arduinoCommand();
*/

typedef void (*arduino_func_t)(const char);

struct arduino_handler {
	arduino_func_t f;
	char *name;
};

#define REGISTER_ARDUINO_HANDLER(func)                         \
	static struct arduino_handler __arduino_handler__ ## func  \
	__attribute((__section__(".arduino_handlers")))            \
	__attribute((__used__)) = {                                \
	    .f = func,                                             \
	    .name = #func,                                         \
	}

extern struct arduino_handler __start_arduino_handlers;
extern struct arduino_handler __stop_arduino_handlers;

#ifdef __cplusplus
}
#endif
