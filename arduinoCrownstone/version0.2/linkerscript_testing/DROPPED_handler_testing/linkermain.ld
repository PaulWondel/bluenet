/*
* Author: Crownstone Team
* Copyright: Crownstone (https://crownstone.rocks)
* Date: 16 Dec., 2019
* License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed)
*
* All files in this directory belong to the Crownstone Team
*/

MEMORY
{
	FLASH (rx) : ORIGIN = 0x0, LENGTH = 128K
	RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 32k
	MY_MEMORY (rx) : ORIGIN = 0x20000, LENGTH = 128k
}

INCLUDE linkertest.ld
