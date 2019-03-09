CC = gcc

all: main

main: ex1.o
	$(CC) -o main ex1.o

ex1.o: ex1.c
	$(CC) -c ex1.c

clean:
	rm -f *.o *~
