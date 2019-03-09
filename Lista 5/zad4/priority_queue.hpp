#pragma once
#include <vector>
#include <memory>
#include <limits>

struct element {
    unsigned int key;
    unsigned int parent;

    double dist;

public:
    element() {
        key = 0;
        parent = 0;
        dist = std::numeric_limits<double>::max();
    }

    element(unsigned int key, unsigned int parent, double dist) {
        this->key = key;
        this->parent = parent;
        this->dist = dist;
    }
};

struct neighbour {
    std::shared_ptr<element> vertex;
    double weight;

    neighbour (std::shared_ptr<element> vertex, double weight) {
        this->vertex = vertex;
        this->weight = weight;
    }
};

struct {
    bool operator() (std::shared_ptr<element> e1, std::shared_ptr<element> e2) {
        return e1->key < e2->key;
    }
} comp;

class priority_queue {
private:
    unsigned int heap_size;
    std::vector<std::shared_ptr<element>> queue;
    
    void heapify(int i);
    int parent(int i);
    int left (int i);
    int right (int i);

public:
    priority_queue();
    ~priority_queue();
    std::shared_ptr<element> insert (unsigned int key, unsigned int vertex_parent, double dist);
    bool empty();
    unsigned int top();
    unsigned int pop();
    void priority(unsigned int key, double dist);
    void print();
    std::shared_ptr<element> find(unsigned int key);
    std::vector<std::shared_ptr<element>> get_queue();
};