#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

#include "edge.hpp"
#include "vertex.hpp"
#include "weight_walk.hpp"

weight_walk::weight_walk() {

}

weight_walk::~weight_walk() {

}

void weight_walk::add_edge (unsigned int u, unsigned int v, double weight) {
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

double weight_walk::find_edge(unsigned int u, unsigned int v) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);

        if ((e.u == u && e.v == v) || (e.u == v && e.v == u)) {
            return e.weight;
        }
    }
}

void weight_walk::walk() {

    unsigned int steps = 0;
    double total_weight = 0.0;
    unsigned int mem = 0;

    for (unsigned int i = 1; i <= max_vertex; i++) {
        std::shared_ptr<graph_vertex> v = std::make_shared<graph_vertex>(i, false);
        vertices.push_back(v);
        mem += sizeof(v);
    }

    std::vector<std::vector<std::shared_ptr<next_vertex>>> adj(max_vertex);

    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        adj.at(e.u - 1).push_back(std::make_shared<next_vertex>(vertices.at(e.v - 1), e.weight));
        adj.at(e.v - 1).push_back(std::make_shared<next_vertex>(vertices.at(e.u - 1), e.weight));
    }

    mem += sizeof(adj);

    srand(time(nullptr));
    unsigned int visited_vertices = 0;
    unsigned int start = rand() % max_vertex;

    std::vector<std::shared_ptr<next_vertex>> curr_adj = adj.at(start);
    std::shared_ptr<graph_vertex> curr = vertices.at(start);

    mem += sizeof (curr);
    mem += sizeof (curr_adj);

    while (visited_vertices < max_vertex) {
        if (!curr->visited) {
            visited_vertices++;
            curr->visited = true;
        }
        steps++;

        double min_weight = curr_adj.at(0)->weight;
        unsigned int next = curr_adj.at(0)->next->key - 1;
        for (unsigned int i = 0; i < curr_adj.size(); i++) {
            if (curr_adj.at(i)->weight < min_weight && !curr_adj.at(i)->next->visited) {
                next = i;
            }
        }

        total_weight += find_edge(curr->key, curr_adj.at(next)->next->key);

        std::cerr << curr->key << " -> ";

        curr = vertices.at(curr_adj.at(next)->next->key - 1);
        curr_adj = adj.at(curr_adj.at(next)->next->key - 1);

        std::cerr << curr->key << std::endl;
    }

    std::cout << steps << " " << total_weight << " " << mem << " "; 
}

void weight_walk::set_max_vertex (unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}