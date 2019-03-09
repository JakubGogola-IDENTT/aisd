#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

#include "kruskal.hpp"
#include "disjoint_sets.hpp"
#include "edge.hpp"

kruskal::kruskal(unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}

kruskal::~kruskal () {
    vertices.clear();
    edges.clear();
}

void kruskal::add_edge (unsigned int u, unsigned int v, double weight) {
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

void kruskal::set_max_vertex(unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}

std::vector<edge> kruskal::find_mst() {
    std::vector<edge> T;

    disjoint_sets *ds = new disjoint_sets();

    for (unsigned int i = 1; i <= max_vertex; i++) {
        std::shared_ptr<vertex> v = std::make_shared<vertex>(i);
        ds->make_set(v.get());
        vertices.push_back(v);
    }

    std::sort(edges.begin(), edges.end(), edge_comp);

    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        if (ds->find_set(vertices.at(e.u - 1).get()) != ds->find_set(vertices.at(e.v - 1).get())) {
            T.push_back(edges.at(i));
            ds->set_union(vertices.at(e.u - 1).get(), vertices.at(e.v - 1).get());
        }
    }

    return T;
}

void kruskal::mst_add_edge(unsigned int u, unsigned int v, double weight) {
    add_edge(u, v, weight);
}

std::vector<edge> kruskal::mst_find_mst() {
    return find_mst();
}

void kruskal::mst_set_max_vertex (unsigned int max_vertex) {
    set_max_vertex(max_vertex);
}