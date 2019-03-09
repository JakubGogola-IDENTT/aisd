#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "edge.hpp"
#include "vertex.hpp"
#include "euler_walk.hpp"

euler_walk::euler_walk() {

}

euler_walk::~euler_walk() {
    vertices.clear();
    edges.clear();
}

void euler_walk::add_edges (std::vector<edge> edges) {
    this->edges = edges;
}

double euler_walk::find_edge(unsigned int u, unsigned int v) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);

        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            return e.weight;
        }
    }
}

void euler_walk::walk() {
    unsigned int steps = 0;
    double total_weight = 0.0;
    unsigned int mem = 0;

    for (unsigned int i = 1; i <= max_vertex; i++) {
        std::shared_ptr<euler_vertex> v = std::make_shared<euler_vertex>(i, NOT_VISITED);
        vertices.push_back(v);
        mem += sizeof(v);
    }

    std::vector<std::vector<std::shared_ptr<euler_vertex>>> adj(max_vertex);
    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        adj.at(e.u - 1).push_back(vertices.at(e.v - 1));
        adj.at(e.v - 1).push_back(vertices.at(e.u - 1));
    }

    mem += sizeof(adj);

    srand(time(nullptr));
    unsigned int visited_vertices = 0;
    //unsigned int start = rand() % max_vertex;
    unsigned int start = 0;

    std::vector<std::shared_ptr<euler_vertex>> curr_adj = adj.at(start);
    std::shared_ptr<euler_vertex> curr = vertices.at(start);

    mem += sizeof (curr);
    mem += sizeof (curr_adj);

    while (visited_vertices < max_vertex) {
        unsigned int next = -1;
        enum state state;
        
        steps++;

        for (unsigned int i = 0; i < curr_adj.size(); i++) {
            if (curr_adj.at(i)->visit == NOT_VISITED) {
                next = i;
                break;
            }
        }

        if (next == -1) {
            for (unsigned int i = 0; i < curr_adj.size(); i++) {
                if (curr_adj.at(i)->visit == VISITED_ONCE) {
                    next = i;
                    break;
                }
            }
            state = VISITED_TWICE;

        } else {
            state = VISITED_ONCE;
        }

        if (next == -1) {
            next = start;
        }

        curr->visit = state;
        curr_adj.at(next)->visit = state;

        total_weight += find_edge (curr->key, curr_adj.at(next)->key);

        if (curr->visit == VISITED_TWICE) {
            visited_vertices++;
        }
    
        std::cerr << curr->key << " -> ";

        curr = vertices.at(curr_adj.at(next)->key - 1);
        curr_adj = adj.at(curr_adj.at(next)->key - 1);
        
        std::cerr << curr->key << std::endl;
    }
    std::cout << steps << " " << total_weight << " " << mem << " "; 
}

void euler_walk::set_max_vertex (unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}