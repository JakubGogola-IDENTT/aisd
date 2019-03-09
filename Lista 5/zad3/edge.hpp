#pragma once

struct edge {
    unsigned int u;
    unsigned int v;
    double weight;

    edge(unsigned int u, unsigned int v, double weight) {
        this->u = u;
        this->v = v;
        this->weight = weight;
    }
};

struct {
    bool operator() (edge e1, edge e2) {
        return e1.weight < e2.weight;
    }
} edge_comp;