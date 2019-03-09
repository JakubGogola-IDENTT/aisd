#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "random_walk.hpp"
#include "edge.hpp"
#include "vertex.hpp"

random_walk::random_walk() {

}

random_walk::~random_walk() {

}

void random_walk::add_edge (unsigned int u, unsigned int v, double weight) {
    if (u < 1 || u > max_vertex || v < 1 || v > max_vertex || weight < 0.0) {
        return;
    }

    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            return;
        }
    }

    edges.push_back(edge(u, v, weight));
}

double random_walk::find_edge(unsigned int u, unsigned int v) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);

        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            return e.weight;
        }
    }
}

void random_walk::walk() {

    unsigned int steps = 0;
    double total_weight = 0.0;
    unsigned int mem = 0;

    for (unsigned int i = 1; i <= max_vertex; i++) {
        std::shared_ptr<graph_vertex> v = std::make_shared<graph_vertex>(i, false);
        mem += sizeof (v);
        vertices.push_back(v);
    }

    std::vector<std::vector<std::shared_ptr<graph_vertex>>> adj(max_vertex);

    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        adj.at(e.u - 1).push_back(vertices.at(e.v - 1));
        adj.at(e.v - 1).push_back(vertices.at(e.u - 1));
    }

    mem += sizeof (adj);

    srand(time(nullptr));
    unsigned int visited_vertices = 0;
    unsigned int start = rand() % max_vertex;

    std::vector<std::shared_ptr<graph_vertex>> curr_adj = adj.at(start);
    std::shared_ptr<graph_vertex> curr = vertices.at(start);
    mem += sizeof(curr);
    mem += sizeof(curr_adj);

    while (visited_vertices < max_vertex) {
        if (!curr->visited) {
            visited_vertices++;
            curr->visited = true;
        }
        steps++;
        

        unsigned int next = rand() % curr_adj.size();

        total_weight += find_edge(curr->key, curr_adj.at(next)->key);

        std::cerr << curr->key << " -> ";

        curr = vertices.at(curr_adj.at(next)->key - 1);
        curr_adj = adj.at(curr_adj.at(next)->key - 1);

        std::cerr << curr->key << std::endl;
        
    }
    std::cout << steps << " " << total_weight << " " << mem << " "; 
}

void random_walk::set_max_vertex (unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}