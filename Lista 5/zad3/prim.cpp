#include <iostream>
#include <vector>
#include <memory>

#include "priority_queue.hpp"
#include "prim.hpp"
#include "edge.hpp"
#include "mst.hpp"

prim::prim (unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}

prim::~prim() {
    vertices.clear();
    edges.clear();
}

void prim::initialize_single_source (priority_queue *pq) {
    for (int i = 1; i <= max_vertex; i++) {
        std::shared_ptr<element> e = pq->insert(i, 0, std::numeric_limits<double>::max());
        vertices.push_back(e);
    }
}

void prim::add_edge(unsigned int u, unsigned int v, double weight) {
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

edge prim::find_edge(unsigned int u, unsigned int v) {
    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);

        if ((e.u == u && e.v ==v) || (e.u == v && e.v == u)) {
            return e;
        }
    }
}

std::vector<edge> prim::find_mst() {
    std::vector<edge> T;
    priority_queue *pq = new priority_queue();

    initialize_single_source(pq);
    pq->priority(1, 0.0);

    std::vector<std::vector<neighbour>> adj(max_vertex);
    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        adj.at(e.u - 1).push_back(neighbour(pq->find(e.v), e.weight));
        adj.at(e.v - 1).push_back(neighbour(pq->find(e.u), e.weight));
    }

    unsigned int parent;
    unsigned int u;
    double weight;
    while (!pq->empty()) {
        weight = pq->get_queue().at(0)->dist;
        parent = pq->get_queue().at(0)->parent;
        u = pq->pop();

        if (parent > 0) {
            edge e = find_edge(u, parent);
            e.weight = weight;
            T.push_back(e);
        }

        std::vector<neighbour> *l = &adj.at(u - 1);
        for (unsigned int i = 0; i < l->size(); i++) {
            neighbour *v = &l->at(i);

            if (pq->find(v->vertex->key) == v->vertex && v->weight < v->vertex->dist) {
                v->vertex->parent = u;
                v->vertex->dist = v->weight;
                pq->priority(v->vertex->key, v->weight);
            }
        }

    }

    return T;
}

void prim::set_max_vertex (unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}

std::vector<edge> prim::mst_find_mst() {
    return find_mst();
}

void prim::mst_add_edge (unsigned int u, unsigned int v, double weight) {
    add_edge(u, v, weight);
}

void prim::mst_set_max_vertex (unsigned int max_vertex) {
    set_max_vertex(max_vertex);
}