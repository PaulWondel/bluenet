compile:
	gcc -c main.c -I /usr/include/

link:
	ld -T arduino_handler.ld main.o

readelf:
	readelf -Sh Test

clean:
	rm -f *.o
