#include <stdio.h>

extern unsigned char arduino_handler_size[];

int main(){
	printf("section `.arduino_handler` starts at %p and the 1st byte is %x\n",
	arduino_handler_size, (unsigned int)arduino_handler_size[0]);
	return 0;
}
