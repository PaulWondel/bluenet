/*
* Author: Crownstone Team
* Copyright: Crownstone (https://crownstone.rocks)
* Date: 16 Dec., 2019
* License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed)
*
* All files in this directory belong to the Crownstone Team
*/

SECTIONS
{
	.arduino_handler :
	{
		__arduino_handler_size = 0x10;
		__arduino_handler_start = .;
		. = . + __arduino_handler_size;
		__arduino_handler_end = .;
	}
}

