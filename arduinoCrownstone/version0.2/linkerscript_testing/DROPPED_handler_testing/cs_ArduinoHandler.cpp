/*
* Author: Crownstone Team
* Copyright: Crownstone (https://crownstone.rocks)
* Date: 16 Dec., 2019
* License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed)
*
* All files in this directory belong to the Crownstone Team
*/

#include<stdio.h>
#include<iostream>

#include<cs_ArduinoHandler.h>

// Initialize the variable in the arduino_handler section with address, 
static void (*jumpToCallback)() __attribute__((section("arduino_handler"))); // = '4'; // Variable in the section that functions as a pointer
extern unsigned char __start_arduino_handler;
extern unsigned char __stop_arduino_handler;

// Pointers to start and stop
static unsigned char * p_arduino_handler_start = &__start_arduino_handler;
static unsigned char * p_arduino_handler_end = &__stop_arduino_handler;

static void (*func)(); //variable to store function address into

// function to be put in section
void callback(void){
	printf("Go to arduino firmware\n"); // will be replaced with a addresss or pointer to address
}
//void (*jumpToCallback)();
//void (*func)();
/*
//Created a new function to use the variables because the bluenet compiler gives errors if they are not explicitly used
void variableCheck(unsigned char jumpvar, size_t funcvar){

	if(jumpvar == funcvar){
		printf("Jump To Callback Address: %u\n", jumpvar);
	}
	else{
		printf("jumpToCallback: %u | func: %u\n",jumpvar,funcvar);
	}
}
*/
// Can't call it main() since cs_Crownstone.cpp already has the main. This has to be called by the main.
int jumpMain(){
	printf("section `arduino_handler` starts at %p, ends at %p, and the 1st byte is %c\n",
			p_arduino_handler_start, p_arduino_handler_end, p_arduino_handler_start[0]);

//	void (*func)(); // declare function pointer
	func = &callback; // assign address to pointer
	(*func)(); // call function indirectly

//	void (*jumpToCallback)();
	jumpToCallback = func;
	(*jumpToCallback)();
//	variableCheck(jumpToCallback, func); //function to use the variables to satisfy the compiler

	if(jumpToCallback == func){
		printf("Jump To Callback Address: %p\n", jumpToCallback);
	}
	else{
		printf("jumpToCallback: %p | func: %p\n",jumpToCallback,func);
	}

	return 0;
}
