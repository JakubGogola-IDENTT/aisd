#pragma once 
#include <iostream>
#include <vector>
#include <memory>

#include "mst.hpp"
#include "edge.hpp"
#include "priority_queue.hpp"

class prim : public mst {
private: 
    unsigned int max_vertex;
    std::vector<edge> edges;
    std::vector<std::shared_ptr<element>> vertices;

    void initialize_single_source (priority_queue *pq);
    edge find_edge(unsigned int u, unsigned int v);

public:
    prim (unsigned int max_vertex);
    ~prim ();

    void set_max_vertex (unsigned int max_vertex);
    void add_edge(unsigned int u, unsigned int v, double weight);
    std::vector<edge> find_mst();

    void mst_add_edge(unsigned int u, unsigned int v, double weight);
    std::vector<edge> mst_find_mst();
    void mst_set_max_vertex (unsigned int max_vertex);
};