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

