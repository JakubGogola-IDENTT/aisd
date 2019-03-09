#include <iostream>
#include <vector>
#include <list>
#include <limits>

#include "dijsktra.hpp"

dijkstra::dijkstra(int max_vertex) {
    this->max_vertex = max_vertex;
}

dijkstra::~dijkstra() {
    vertices.clear();
    edges.clear();
}

void dijkstra::add_edge(unsigned int start, unsigned int end, double weight) {
    //TODO: Comparing to double!!!!
    if (start > max_vertex || end > max_vertex || weight < 0.0) {
        return;
    }

    edges.push_back(edge(start, end, weight));
}

void dijkstra::initialize_single_source (priority_queue *pq) {
    for (int i = 1; i <= max_vertex; i++) {
        std::shared_ptr<element> e = pq->insert(i, 0, std::numeric_limits<double>::max());
        vertices.push_back(e);
    }
}

void dijkstra::set_max_vertex(unsigned int max_vertex) {
    this->max_vertex = max_vertex;
}

unsigned int dijkstra::get_max_vertex() {
    return max_vertex;
}

std::vector<std::shared_ptr<element>> dijkstra::shortest_path(unsigned int source) {
    //Shortest paths.
    std::vector<std::shared_ptr<element>> S;
    priority_queue *pq = new priority_queue();

    //Initialice vertices.
    initialize_single_source(pq);
    std::shared_ptr<element> src = pq->find(source);
    src->dist = 0.0;

    //Creating adjacency lists.
    std::vector<std::vector<neighbour>> adj(max_vertex);
    for (unsigned int i = 0; i < edges.size(); i++) {
        edge e = edges.at(i);
        adj.at(e.start - 1).push_back(neighbour(pq->find(e.end), e.weight));
    }

    while (!pq->empty()) {
        double dist = pq->get_queue().at(0)->dist;
        S.push_back(pq->get_queue().at(0));
        unsigned int u = pq->pop();

        std::vector<neighbour> *l = &adj.at(u - 1);
        for (unsigned int i = 0; i < l->size(); i++) {
            neighbour *v = &l->at(i);
            if (v->vertex->dist > dist + v->weight) {
                v->vertex->dist = dist + v->weight;
                v->vertex->parent = u;
                pq->priority(v->vertex->key, dist + v->weight);
            }
        }
    }

    return S;
}

