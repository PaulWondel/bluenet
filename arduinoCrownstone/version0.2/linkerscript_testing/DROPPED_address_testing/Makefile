#########################################################################
# Author: Crownstone Team						#
# Copyright: Crownstone (https://crownstone.rocks) 			#
# Date: 16 Dec., 2019							#
# License: LGPLv3, Apache License 2.0, and/or MIT (triple-licensed) 	#
#									#
# All files in this directory belong to the Crownstone Team		#
#########################################################################

#This keeps the echo for every command silent that is executed in this makefile
ifndef VERBOSE
.SILENT:
endif

IDIR = /include #Input directory
CC = gcc #Compiler
DEPS = stdio.h main.h #Dependency
OBJ = main.o #Object files
CFLAGS = -I. # Compiler flags

#This is the command for suppressing the echo per command.
#.SILENT: main link_main link_test readelf_main readelf_test symbols_test clean compile

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

compile:
	$(CC) -c *.c #-I$(IDIR)

compile_link:
	gcc -T arduino_handler -N add.c

link_main:
	ld main.o -e main -T arduino_handler.ld

link_test:
	ld -T arduino_handler.ld add.o

readelf_test:
	readelf -Sh Test

readelf_main:
	readelf -Sh main

symbols_test:
	nm Test

clean:
	rm -f *.o *.out Test main
