OUTPUT_FORMAT(elf32-i386)
ENTRY(main)
OUTPUT(Test)

SECTIONS
{
	.text : { *(.text) }
	. = ALIGN(0x10);
	.data : { *(.data) }
	. = ALIGN(0x10);
	.bss : { *(.bss)} 
	. = ALIGN(0X10);
}

/*
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
*/
