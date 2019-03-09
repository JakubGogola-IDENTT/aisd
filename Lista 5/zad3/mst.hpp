#pragma once
#include <vector>

#include "edge.hpp"

class mst {
friend class kruskal;

public:
    virtual void mst_add_edge(unsigned int u, unsigned int v, double weight) = 0;
    virtual std::vector<edge> mst_find_mst() = 0;
    virtual void mst_set_max_vertex (unsigned int max_vertex) = 0;
};