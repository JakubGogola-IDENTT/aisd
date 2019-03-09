#pragma once
#include <iostream>
#include <sstream>
#include <vector>

#include "priority_queue.hpp"
#include "mst.hpp"
#include "edge.hpp"

enum type {
    KRUSKAL = 'k',
    PRIM ='p'
};

class parser {
private:
    unsigned int max_vertex;
    enum type type;
    std::vector<edge> edges;
    void add_edge (unsigned int u, unsigned int v, double weight);

public:
    parser();
    ~parser();

    void parse_args(int argc, char **argv);
    mst* get_algorithm();
    void handle_input();
    void run_tests();
};