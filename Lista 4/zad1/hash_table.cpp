#include <iostream>
#include <functional>
#include <sstream>
#include <fstream>
#include <unistd.h>

#include "hash_table.hpp"
#include "linked_list.hpp"
#include "functions.hpp"

hash_table::hash_table () {
    ht = new data_structure* [128];
    types = new enum type[128];
    switch_point = 300;
    
    for (int i = 0;i < 128; i++) {
        ht[i] = new linked_list();
        types[i] = LL;
    }
    s = new stats();
}

hash_table::~hash_table () {
    for (int i = 0;i < 128; i++) {
        delete ht[i];
    }

    delete s;
    delete ht;
    delete types;
}

unsigned long hash_table::get_hash(std::string key) {
    std::hash<std::string> h;
    return h(key) / (std::numeric_limits<size_t>::max() / 128);
}


void hash_table::switch_ds (unsigned long index) {
    unsigned int hash_size = ht[index]->get_size();
    data_structure *pos = ht[index];
    data_structure *ds;
    
    if (hash_size > switch_point && types[index] == LL ) {
        ds = new rb_tree();

        while (pos->get_main() != nullptr) {
            ds->ds_insert(pos->get_main()->key);
            pos->ds_delete(pos->get_main()->key);
        }

        types[index] = RBT;
    } else if (hash_size  <= switch_point && types[index] == RBT) {
        ds = new linked_list();

        while (pos->get_main() != nullptr) {
            ds->ds_insert(pos->get_main()->key);
            pos->ds_delete(pos->get_main()->key);
        }

        types[index] = LL;
    } else {
        return;
    }

    delete pos;
    ht[index] = ds;
}

ds_node* hash_table::get_main() {
    return nullptr;
}

unsigned int hash_table::get_size () {
    int sum_size = 0;

    for (int i = 0;i < 128; i++) {
        sum_size += ht[i]->get_size();
    }

    return sum_size;
}

void hash_table::check_max_size() {
    unsigned int ms;
    for (int i = 0; i < 128; i++) {
        ms = ht[i]->get_max_size();
        if (ms > max_size) {
            max_size = ms;
        }
    }
}

stats* hash_table::get_stats() {
    return s;
}

unsigned int hash_table::get_max_size() {
    return max_size;
}

void hash_table::reset_comps() {
    s->comps = 0;
}

void hash_table::ds_inorder() {
    std::cout << "\n";
    s->inorders++;
}

void hash_table::ds_search (std::string key) {
    unsigned long hash = get_hash (key);
    ht[hash]->ds_search(key);
    s->comps = ht[hash]->get_stats()->comps;
    ht[hash]->reset_comps();
}

void hash_table::ds_minimum () {
    std::cout << "\n";
    s->mins++;
}

void hash_table::ds_maximum () {
    std::cout << "\n";
    s->maxs++;
}

void hash_table::ds_succssor (std::string key) {
    unsigned long hash = get_hash (key);
    ht[hash]->ds_succssor(key);
    s->successors++;
}

void hash_table::ds_insert (std::string key) {
    unsigned long hash = get_hash (key);
    key = remove_char (key);
    switch_ds (hash);
    ht[hash]->ds_insert(key);
    check_max_size();
    s->inserts++;
}

void hash_table::ds_delete (std::string key) {
    unsigned long hash = get_hash (key);
    ht[hash]->ds_delete(key);
    switch_ds (hash);
    s->deletes++;
}

void hash_table::ds_load (std::string file_name) {
    std::string line;   
    std::string key;
    std::ifstream fin;
    std::istringstream iss;

    unsigned long hash;
    fin.open(file_name);
    while (fin >> key) {
        ds_insert(key);
    }
    fin.close();
    s->loads++;
}
