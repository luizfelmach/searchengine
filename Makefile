all: trab3

trab3: main.c
	gcc -o trab3 *.c

clean:
	rm -rf *.o trab3
