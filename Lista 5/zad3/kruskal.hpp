#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "priority_queue.hpp"
#include "disjoint_sets.hpp"
#include "edge.hpp"
#include "mst.hpp"

class kruskal : public mst {
private:
    unsigned int max_vertex;
    std::vector<edge> edges;
    std::vector<std::shared_ptr<vertex>> vertices;

public:
    kruskal(unsigned int max_vertex);
    ~kruskal();

    void add_edge (unsigned int u, unsigned int v, double weight);
    void set_max_vertex(unsigned int n);

    std::vector<edge> find_mst();

    void mst_add_edge(unsigned int u, unsigned int v, double weight);
    std::vector<edge> mst_find_mst();
    void mst_set_max_vertex (unsigned int max_vertex);

};