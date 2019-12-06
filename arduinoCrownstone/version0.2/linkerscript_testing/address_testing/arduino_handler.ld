OUTPUT_FORMAT(elf64-x86-64)/*elf32-i386)*/
ENTRY(main)
OUTPUT(Test)

SECTIONS
{
	.text : { *(.text) }
	. = ALIGN(0x1000);
	.data : { *(.data) }
	. = ALIGN(0x10000);
	.bss : { *(.bss)} 
	. = ALIGN(0X10000);
	.arduino_handler :
	{
	arduino_handler_size = 0x10;
	arduino_handler_start = .;
	. = . + arduino_handler_size;
	arduino_handler_end = .;
	}
} 

