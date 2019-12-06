#include <stdio.h>
//#include <main.h>

static size_t func; //variable to store function address into

void callback() {
	printf("This is the arduino callback function! \n");
}

int functionAddress(int x){
	printf("%d\n", x);	
}


//int main(int argc, const char* argv[]) {
int main(){   
	int var1;
	int *p;
	
	p = &var1;
	
	printf("Address of the variable: %p\n", &var1); //Prints the address of the variable
	printf("Value of the target of the pointer: %d\n",*p); //Prints the value of the pointer
	
	var1 = 20;
	
	printf("Value of the target of the pointer: %d\n",*p); //Prints the value of the pointer
	
	callback();
	printf("Address of callback function: %p\n", &callback);
	
	//int *ptr_func = &callback; 
	//func = ptr_func;
	//func = &callback;
	
	int (*foo)(int);
	foo = &functionAddress;
	(*foo)(2);
	
	//typedef void (*func)(); //declaring a function pointer
	
	void (*func)(); // declare function pointer
	func = &callback; // assign address to pointer
	(*func)(); // call function indirectly
	printf("func: %p\n", func); // I need to print the type of the &callback

	return 0;
}
