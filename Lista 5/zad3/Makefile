CC = g++
FLAGS = -std=c++17 

all: main

main: main.o priority_queue.o parser.o disjoint_sets.o kruskal.o prim.o
	$(CC) $(FLAGS) -o main main.o priority_queue.o parser.o disjoint_sets.o kruskal.o prim.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

priority_queue.o: priority_queue.cpp
	$(CC) $(FLAGS) -c priority_queue.cpp

parser.o: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

disjoint_sets.o: disjoint_sets.cpp
	$(CC) $(FLAGS) -c disjoint_sets.cpp

kruskal.o: kruskal.cpp
	$(CC) $(FLAGS) -c kruskal.cpp

prim.o: prim.cpp
	$(CC) $(FLAGS) -c prim.cpp

clean:
	rm -f *.o *~
	rm -f main
	