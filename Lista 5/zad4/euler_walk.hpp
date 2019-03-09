#pragma once
#include<iostream>
#include <vector>
#include <memory>

#include "edge.hpp"
#include "vertex.hpp"

class euler_walk {
private:
    unsigned int max_vertex;
    std::vector<edge> edges;
    std::vector<std::shared_ptr<euler_vertex>> vertices;
    double find_edge(unsigned int u, unsigned int v);

public:
    euler_walk();
    ~euler_walk();

    void set_max_vertex (unsigned int max_vertex);
    void add_edges (std::vector<edge>edges);

    void walk();

};