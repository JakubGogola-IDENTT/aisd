CC = g++
FLAGS = -std=c++17 -Wall --pedantic -lm

all: main

main: main.o statistics.o binary_search.o
	$(CC) $(FLAGS) -o main main.o statistics.o binary_search.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

statistics.o : statistics.cpp
	$(CC) $(FLAGS) -c statistics.cpp

binary_search.o : binary_search.cpp
	$(CC) $(FLAGS) -c binary_search.cpp

clean:
	rm -f *.o *~
	rm -f main
	