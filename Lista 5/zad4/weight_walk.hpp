#pragma once 
#include <iostream>

#include <vector>
#include <memory>

#include "edge.hpp"
#include "vertex.hpp"


class weight_walk {
private:
    unsigned int max_vertex;
    std::vector<edge> edges;
    std::vector<std::shared_ptr<graph_vertex>> vertices;
    double find_edge(unsigned int u, unsigned int v);

public:
    weight_walk();
    ~weight_walk();

    void set_max_vertex (unsigned int max_vertex);
    void add_edge (unsigned int u, unsigned int v, double weight);

    void walk();

};