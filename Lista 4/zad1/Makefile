CC = g++
FLAGS = -std=c++17 

all: main

main: main.o bs_tree.o rb_tree.o hash_table.o parser.o functions.o linked_list.o tests.o bloom_filter.o
	$(CC) $(FLAGS) -o main main.o bs_tree.o rb_tree.o hash_table.o parser.o functions.o linked_list.o tests.o bloom_filter.o

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp

bs_tree.o: bs_tree.cpp
	$(CC) $(FLAGS) -c bs_tree.cpp

rb_tree.o: rb_tree.cpp
	$(CC) $(FLAGS) -c rb_tree.cpp

hash_table.o: hash_table.cpp
	$(CC) $(FLAGS) -c hash_table.cpp

functions.o: functions.cpp
	$(CC) $(FLAGS) -c functions.cpp

parser.o: parser.cpp
	$(CC) $(FLAGS) -c parser.cpp

linked_list.o: linked_list.cpp
	$(CC) $(FLAGS) -c linked_list.cpp	

tests.o: tests.cpp
	$(CC) $(FLAGS) -c tests.cpp

bloom_filter.o: bloom_filter.cpp
	$(CC) $(FLAGS) -c bloom_filter.cpp

clean:
	rm -f *.o *~
	rm -f main
	