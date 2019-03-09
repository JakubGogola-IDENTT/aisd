CC = g++
FLAGS = -std=c++17 

all: main

main: main.o priority_queue.o parser.o dijkstra.o
	$(CC) $(FLAGS) -o main main.o priority_queue.o parser.o dijkstra.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

priority_queue.o: priority_queue.cpp
	$(CC) $(FLAGS) -c priority_queue.cpp

parser.o: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

dijkstra.o: dijkstra.cpp
	$(CC) $(FLAGS) -c dijkstra.cpp

clean:
	rm -f *.o *~
	rm -f main
	