#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>
#include <cstdlib>

#include "parser.hpp"
#include "kruskal.hpp"
#include "prim.hpp"
#include "priority_queue.hpp"
#include "random_walk.hpp"
#include "weight_walk.hpp"
#include "euler_walk.hpp"

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

void parser::add_edge (unsigned int u, unsigned int v, double weight) {    
    edges.push_back(edge(u, v, weight));
}

void parser::handle_input() {
    

    unsigned int m, n;
    unsigned int u, v;
    double weight;
    
    std::cin >> n;
    max_vertex = n;
    m = n * (n - 1) / 2;
    
    for (int i = 0; i < m; i++) {
        std::cin >> u >> v >> weight;
        add_edge(u, v, weight);
    }
    
    
}

void parser::run_tests() {
    time_t start, stop;

    start = clock();
    //Random walk
    random_walk *rw = new random_walk();
    rw->set_max_vertex(max_vertex);

    for (int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        rw->add_edge(e.u, e.v, e.weight);
    }

    rw->walk();
    stop = clock();
    std::cout << (double) (stop - start) / CLOCKS_PER_SEC  << std::endl;

    delete rw;
    
    //Walk by weights.
    start = clock();
    weight_walk *ww = new weight_walk();
    ww->set_max_vertex(max_vertex);
    for (int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        ww->add_edge(e.u, e.v, e.weight);
    }

    ww->walk();
    stop = clock();
    std::cout << (double) (stop - start) / CLOCKS_PER_SEC  << std::endl;
    delete ww;

    //Euler walk;
    start = clock();
    euler_walk *ew = new euler_walk();
    ew->set_max_vertex(max_vertex);

    mst *mst;
    mst = new kruskal(max_vertex);
    for (int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        mst->mst_add_edge(e.u, e.v, e.weight);
    }

    ew->add_edges(mst->mst_find_mst());
    ew->walk();
    stop = clock();
    std::cout << (double) (stop - start) / CLOCKS_PER_SEC  << std::endl;
    
    delete mst;
    delete ew;

    start = clock();
    ew = new euler_walk();
    ew->set_max_vertex(max_vertex);
    mst = new prim(max_vertex);
    for (int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        mst->mst_add_edge(e.u, e.v, e.weight);
    }

    ew->add_edges(mst->mst_find_mst());
    ew->walk();
    stop = clock();
    std::cout << (double) (stop - start) / CLOCKS_PER_SEC << std::endl;

    delete mst;
    delete ew;
}