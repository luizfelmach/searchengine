all: trab3

trab3: src/main.c
	gcc -o trab3 src/*.c

clean:
	rm -rf *.o trab3
