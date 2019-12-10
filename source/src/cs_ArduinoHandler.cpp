#include<stdio.h>
#include<iostream>

#include"cs_ArduinoHandler.h"

// Initialize the variable in the arduino_handler section with address, 
static unsigned char jumpToCallback __attribute__((section("arduino_handler"))) = '4'; // Variable in the section that functions as a pointer
extern unsigned char __start_arduino_handler;
extern unsigned char __stop_arduino_handler;

// Pointers to start and stop
static unsigned char * p_arduino_handler_start = &__start_arduino_handler;
static unsigned char * p_arduino_handler_end = &__stop_arduino_handler;

static size_t func; //variable to store function address into

// function to be put in section
void callback(void){
	printf("Go to arduino firmware\n"); // will be replaced with a addresss or pointer to address
}


int main(){
	printf("section `arduino_handler` starts at %p, ends at %p, and the 1st byte is %c\n",
			p_arduino_handler_start, p_arduino_handler_end, p_arduino_handler_start[0]);

	void (*func)(); // declare function pointer
	func = &callback; // assign address to pointer
	(*func)(); // call function indirectly

	void (*jumpToCallback)();
	jumpToCallback = func;
	(*jumpToCallback)();

	if(jumpToCallback == func){
		printf("Jump To Callback Address: %p\n", jumpToCallback);
	}
	else{
		printf("jumpToCallback: %p | func: %p\n",jumpToCallback,func);
	}

	return 0;
}
