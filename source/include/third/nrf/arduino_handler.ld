SECTIONS
{
  .arduino_handler :
  {
  __arduino_handler_size = 0x04;
  __arduino_handler_start = .;
  . = . + __arduino_handler_size;
  __arduino_handler_end = .;
  } > FLASH
} INSERT AFTER .text;

