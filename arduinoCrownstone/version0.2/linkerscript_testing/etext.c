#include<stdio.h>

// Initialize the variable in the arduino_handler section with address, 
static unsigned char pling __attribute__((section("arduino_handler"))) = '!'; // variable in the section
extern unsigned char __start_arduino_handler;
extern unsigned char __stop_arduino_handler;
static unsigned char jumpToCallback __attribute__((section("arduino_handler"))) = '4'; // Variable in the section that functions as a pointer

// Pointers to start and stop
static char * p_arduino_handler_start = &__start_arduino_handler;
static char * p_arduino_handler_end = &__stop_arduino_handler;
//static char * p_arduino_handler_size;

static size_t func; //variable to store function address into

// function to be put in section
void callback(void){
	printf("Test function\n");
}


int main(){
	printf("section `arduino_handler` starts at %p, ends at %p, and the 1st byte is %c, and the 2nd byte is %c\n",
			p_arduino_handler_start, p_arduino_handler_end, p_arduino_handler_start[0], p_arduino_handler_start[1]);

	void (*func)(); // declare function pointer
	func = &callback; // assign address to pointer
	(*func)(); // call function indirectly
	printf("&callback output: %p\n", &callback);
	printf("Callback function address: %p\n", func); // I need to print the type of the &callback
	printf("Address to func pointer: %p\n", &func);

	//p_arduino_handler_mid = *func;
	//printf("%p\n", p_arduino_handler_size);

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
