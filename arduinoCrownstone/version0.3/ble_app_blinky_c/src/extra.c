/*
* Author: Crownstone Team
* Copyright: Crownstone (https://crownstone.rocks)
* Date: 16 Dec., 2019
* License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed)
*/

#include <extra.h>
#include <nrf_log.h>


static void arduinoCommand(const char value){
	NRF_LOG_INFO("Arduino Command %i", value);
}

/*
static void crownstoneCommand(const char value) {
	NRF_LOG_INFO("Crownstone command %i", value);
}*/

REGISTER_ARDUINO_HANDLER(arduinoCommand);

