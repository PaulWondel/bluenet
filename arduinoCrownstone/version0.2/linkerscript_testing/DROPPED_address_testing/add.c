/*
* Author: Crownstone Team
* Copyright: Crownstone (https://crownstone.rocks)
* Date: 16 Dec., 2019
* License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed)
*
* All files in this directory belong to the Crownstone Team
*/

#include <stdio.h>

extern unsigned char arduino_handler_size[];

int main(){
	printf("Welcome\n");
//	printf("section `.arduino_handler` starts at %p and the 1st byte is %x\n",
//	arduino_handler_size, (unsigned int)arduino_handler_size[0]);
	return 0;
}
