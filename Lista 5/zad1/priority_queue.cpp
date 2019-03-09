#include <iostream>
#include <vector>

#include "priority_queue.hpp"

priority_queue::priority_queue() {
    heap_size = 0;
}

priority_queue::~priority_queue() {
    queue.clear();
}

int priority_queue::parent(int i) {
    return (i + 1) / 2 - 1;
}

int priority_queue::left(int i) {
    return 2 * (i + 1) - 1;
}

int priority_queue::right(int i) {
    return 2 * (i + 1);
}

void priority_queue::empty() {
    if (heap_size == 0) {
        std::cout << "1" << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }
}

void priority_queue::top () {
    if (heap_size > 0) {
        std::cout << queue.at(0).key << std::endl;
    } else {
        std::cout << "\n";
    }
}

void priority_queue::pop() {
    if (heap_size < 1) {
        std::cout << "\n";
        return;
    }

    element max = queue.at(0);
    queue.at(0) = queue.at(heap_size - 1);
    heap_size--;
    heapify(0);

    std::cout << max.key << std::endl;
}

void priority_queue::heapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest;

    if (l < heap_size && queue.at(l).p < queue.at(i).p) {
        largest = l;
    } else {
        largest = i;
    }

    if (r < heap_size && queue.at(r).p < queue.at(largest).p) {
        largest = r;
    }

    if (largest != i) {
        std::swap(queue.at(i), queue.at(largest));
        heapify(largest);
    }
}


void priority_queue::insert(int key, unsigned int p) {
    element e = element (key, p);
    heap_size++;
    queue.push_back(e);

    int i = heap_size - 1;
    while (i > 0 && queue.at(parent(i)).p > p) {
        std::swap(queue.at(i), queue.at(parent(i)));
        i = parent(i);
    }
}

void priority_queue::priority(int key, unsigned int p) {
    for (int i = 0; i < heap_size; i++) {
        if (queue.at(i).key == key) {
            if (queue.at(i).p < p) {
                continue;
            }

            unsigned int j = i;
            queue.at(i).p = p;
            while (j > 0 && queue.at(parent(j)).p > queue.at(j).p) {
                std::swap(queue.at(j), queue.at(parent(j)));
                j = parent(j);
            }

        }
    }
}

void priority_queue::print() {
    element e;
    for (int i = 0;i < heap_size; i++) {
        e = queue.at(i);
        std::cout << "(" << e.key << "," << e.p << ") ";
    }
    std::cout << "\n";
}

