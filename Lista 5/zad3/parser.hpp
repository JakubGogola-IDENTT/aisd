#pragma once
#include <iostream>
#include <sstream>

#include "priority_queue.hpp"
#include "mst.hpp"

enum type {
    KRUSKAL = 'k',
    PRIM ='p'
};

class parser {
private:
    unsigned int max_vertex;
    enum type type;

public:
    parser();
    ~parser();

    void parse_args(int argc, char **argv);
    mst* get_algorithm();
    void handle_input(mst *mst);
};