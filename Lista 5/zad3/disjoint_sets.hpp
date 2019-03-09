#pragma once
#include <iostream>


struct vertex {
public:
    vertex* parent;
    unsigned int key;
    unsigned int rank;

    vertex(unsigned int key) {
        this->key = key;
    }
};

class disjoint_sets {

private:
    void link (vertex *x, vertex *y);

public:
    disjoint_sets();
    ~disjoint_sets();

    void make_set(vertex *x);
    vertex* find_set(vertex *x);
    void set_union(vertex *x, vertex *y);
};