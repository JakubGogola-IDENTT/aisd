#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <memory>

#include "priority_queue.hpp"

struct edge {
    unsigned int start;
    unsigned int end;

    double weight;

    edge(unsigned int start, unsigned int end, double weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;
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

class dijkstra {
private:
    unsigned int max_vertex;
    std::vector<edge> edges;
    std::vector<std::shared_ptr<element>> vertices;

    void initialize_single_source (priority_queue *pq);
   
public:
    dijkstra(int max_vertex);
    ~dijkstra();

    std::vector<std::shared_ptr<element>> shortest_path(unsigned int source);
    void add_edge(unsigned int start, unsigned int end, double weight);
    void set_max_vertex(unsigned int max_vertex);
    unsigned int get_max_vertex();
};