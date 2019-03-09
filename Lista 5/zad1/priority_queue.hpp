#pragma once
#include <vector>
#include <limits>

struct element {
    int key;
    unsigned int p;

public:
    element () {
        key = 0;
        p = std::numeric_limits<unsigned int>::max();
    }

    element(int key, unsigned int p) {
        this->key = key;
        this->p = p;
    }
};

class priority_queue {
private:
    int heap_size;
    std::vector<element> queue;
    
    void heapify(int i);
    int parent(int i);
    int left (int i);
    int right (int i);

public:
    priority_queue();
    ~priority_queue();
    void insert (int key, unsigned int p);
    void empty();
    void top();
    void pop();
    void priority(int key, unsigned int p);
    void print();
};