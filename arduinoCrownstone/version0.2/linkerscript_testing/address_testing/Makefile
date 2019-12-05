IDIR = /include #Input directory
CC = gcc #Compiler
DEPS = stdio.h main.h #Dependency
OBJ = main.o #Object files
CFLAGS = -I. # Compiler flags

.SILENT: main link readelf clean

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#compile1:
#	@$(CC) -c main.c -I$(IDIR)

link:
	ld main.o -e main -T arduino_handler.ld

readelf:
	readelf -Sh Test

clean:
	rm -f *.o Test main
