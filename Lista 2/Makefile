CC = g++
FLAGS = -std=c++17 -Wall --pedantic -lm

all: main

main: main.o insertion_sort.o quick_sort.o merge_sort.o parser.o statistics.o dual_pivot.o
	$(CC) $(FLAGS) -o main main.o insertion_sort.o quick_sort.o merge_sort.o parser.o statistics.o dual_pivot.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

insertion_sort.o : insertion_sort.cpp
	$(CC) $(FLAGS) -c insertion_sort.cpp

quick_sort.o : quick_sort.cpp
	$(CC) $(FLAGS) -c quick_sort.cpp

merge_sort.o : merge_sort.cpp
	$(CC) $(FLAGS) -c merge_sort.cpp

parser.o : parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

statistics.o : statistics.cpp
	$(CC) $(FLAGS) -c statistics.cpp

dual_pivot.o : dual_pivot.cpp
	$(CC) $(FLAGS) -c dual_pivot.cpp

clean:
	rm -f *.o *~
	rm -f main
	