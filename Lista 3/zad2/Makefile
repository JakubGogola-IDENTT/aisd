CC = g++
FLAGS = -std=c++17 -Wall --pedantic -lm

all: main

main: main.o parser.o randomized_select.o select.o data_generator.o insertion_sort.o statistics.o 
	$(CC) $(FLAGS) -o main main.o parser.o randomized_select.o select.o data_generator.o insertion_sort.o statistics.o 

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

parser.o : parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

randomized_select.o : randomized_select.cpp
	$(CC) $(FLAGS) -c randomized_select.cpp

select.o : select.cpp
	$(CC) $(FLAGS) -c select.cpp

data_generator.o : data_generator.cpp
	$(CC) $(FLAGS) -c data_generator.cpp

insertion_sort.o : insertion_sort.cpp
	$(CC) $(FLAGS) -c insertion_sort.cpp

statistics.o : statistics.cpp
	$(CC) $(FLAGS) -c statistics.cpp

clean:
	rm -f *.o *~
	rm -f main
	