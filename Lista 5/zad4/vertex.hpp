#pragma once
#include <memory>

enum state {
    NOT_VISITED = 0,
    VISITED_ONCE = 1,
    VISITED_TWICE = 2
};

struct graph_vertex {
    unsigned int key;
    bool visited;

    graph_vertex(unsigned int key, bool visited) {
        this->key = key;
        this->visited = visited;
    }
};

struct next_vertex {
    std::shared_ptr<graph_vertex> next;
    double weight;

    next_vertex (std::shared_ptr<graph_vertex> next, double weight)  {
        this->next = next;
        this->weight = weight;
    }
};

struct euler_vertex {
    unsigned int key;
    enum state visit;

    euler_vertex (unsigned int key, enum state visit) {
        this->key = key;
        this->visit = visit;
    }
};

