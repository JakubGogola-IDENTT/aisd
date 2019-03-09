#include <iostream>

#include "disjoint_sets.hpp"

disjoint_sets::disjoint_sets() {

}

disjoint_sets::~disjoint_sets() {

}

void disjoint_sets::make_set (vertex *x) {
    x->parent = x;
    x->rank = 0;
}

vertex* disjoint_sets::find_set(vertex *x) {
    if (x != x->parent) {
        x->parent = find_set(x->parent);
    }

    return x->parent;
}

void disjoint_sets::link(vertex *x, vertex *y) {
    if (x->rank > y->rank) {
        y->parent = x;
    } else {
        x->parent = y;
        if (x->rank == y->rank) {
            y->rank++;
        }
    }
}

void disjoint_sets::set_union(vertex *x, vertex *y) {
    link(find_set(x), find_set(y));
}