#include <iostream>
#include <vector>
#include <memory>

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

bool priority_queue::empty() {
    if (heap_size == 0) {
        return true;
    } else {
        return false;
    }
}

unsigned int priority_queue::top () {
    if (heap_size > 0) {
        return queue.at(0)->key;
    } else {
        return 0;
    }
}

unsigned int priority_queue::pop() {
    if (heap_size < 1) {
        return 0;
    }

    int max_key = queue.at(0)->key;
    queue.at(0) = queue.at(heap_size - 1);
    heap_size--;
    heapify(0);

    return max_key;
}

void priority_queue::heapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest;

    if (l < heap_size && queue.at(l)->dist < queue.at(i)->dist) {
        largest = l;
    } else {
        largest = i;
    }

    if (r < heap_size && queue.at(r)->dist < queue.at(largest)->dist) {
        largest = r;
    }

    if (largest != i) {
        std::swap(queue.at(i), queue.at(largest));
        heapify(largest);
    }
}


std::shared_ptr<element> priority_queue::insert(unsigned int key, unsigned int vertex_parent, double dist) {
    std::shared_ptr<element> e = std::make_shared<element> (key, vertex_parent, dist);
    heap_size++;
    queue.push_back(e);

    int i = heap_size - 1;
    while (i > 0 && queue.at(parent(i))->dist > dist) {
        std::swap(queue.at(i), queue.at(parent(i)));
        i = parent(i);
    }

    return e;
}

void priority_queue::priority (unsigned int key, double dist) {
    for (int i = 0; i < heap_size; i++) {
        if (queue.at(i)->key == key) {
            if (queue.at(i)->dist < dist) {
                continue;
            }

            unsigned int j = i;
            queue.at(i)->dist = dist;
            while (j > 0 && queue.at(parent(j))->dist > queue.at(j)->dist ) {
                std::swap (queue.at(j), queue.at(parent(j)));
                j = parent(j);
            }

        }
    }
}

void priority_queue::print() {
    std::shared_ptr<element> e;
    for (int i = 0;i < heap_size; i++) {
        e = queue.at(i);
        std::cout << "(" << e->key << "," << e->dist << ") ";
    }
    std::cout << "\n";
}

std::shared_ptr<element> priority_queue::find(unsigned int key) {
    for (unsigned int i = 0; i < heap_size; i++) {
        if (queue.at(i)->key == key) {
            return queue.at(i);
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<element>> priority_queue::get_queue() {
    return queue;
}