#include <stdio.h>

static size_t func; //variable to store function address into

void callback() {
    printf("This is the arduino callback function! \n");
}

void functionAdress(){
}


int main(int argc, const char* argv[]) {
   
   int var1;
   int *p;

   p = &var1;

   printf("Address of the variable: %p\n", &var1); //Prints the address of the variable
   printf("Value of the target of the pointer: %d\n",*p); //Prints the value of the pointer
   
   var1 = 20;

   printf("Value of the target of the pointer: %d\n",*p); //Prints the value of the pointer

   callback();
   printf("Address of callback function: %p\n", &callback);

   func = &callback;

   // call function indirectly
   // size_t (*func)(unsigned int, unsigned int); //declaring a function pointer
   
   // I need to print the type of the &callback

   return 0;
}
