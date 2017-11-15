all: example

example: example.o
	gcc example.o -o example -lwiringPi -g

example.o: example.c
	gcc example.c -c  -I/root/wiringPi -g

clean:
	rm example.o
