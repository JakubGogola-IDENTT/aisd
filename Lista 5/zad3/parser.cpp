#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "parser.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include "priority_queue.hpp"

parser::parser() {

}

parser::~parser() {

}

void parser::parse_args(int argc, char **argv) {
    if (strcmp(argv[1], "-k") == 0) {
        type = KRUSKAL;
    } else if (strcmp(argv[1], "-p") == 0) {
        type = PRIM;
    } else {
        std::cerr << "***Error: Invalid argument" << std::endl;
        exit(0);
    }
}

mst* parser::get_algorithm() {
    if (type == KRUSKAL) {
        return new kruskal(0);
    } else if (type == PRIM) {
        return new prim(0);
    } 
}

void parser::handle_input(mst *mst) {
    if (mst == nullptr) {
        std::cerr << "***Error: Algorithm object doesn't exist!" << std::endl;
        exit(0);
    }

    unsigned int m, n;
    unsigned int u, v;
    double weight;
    
    std::cin >> n;
    mst->mst_set_max_vertex(n);
    std::cin >> m;
    
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> weight;
        mst->mst_add_edge(u, v, weight);
    }
}