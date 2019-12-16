+ Have an ARDUINO configuration option.
+ Create .arduino_handlers section in linker script
+ Create arduinoCommand function that will be in this section.
+ This function just logs something.
+ Call this function (for now) from cs_Crownstone

What needs to be done next:

+ Create a separate binary that uses the same named section.
+ Call the function from that binary.
+ Add parameter to the function.
+ Create large switch statement to pass through any arduino call.
+ Create second function to call Arduino code from Crownstone.
