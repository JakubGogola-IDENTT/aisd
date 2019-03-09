#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <fstream>

#include "bloom_filter.hpp"
#include "functions.hpp"

bloom_filter::bloom_filter() {
    m = 1000;
    k = 10;

    this->n = 0;
    
    s = new stats ();
    size = 0;

    filter = new unsigned int[m];

    for (int i = 0; i < m; i++) {
        filter[i] = 0;
    }

}

bloom_filter::~bloom_filter() {
    delete s;
    delete filter;
}

std::vector<int>* bloom_filter::get_hashes(std::string key) {
    std::hash<std::string> h;
    std::vector<int> *indeces = new std::vector<int>;
    int index;

    unsigned int hash_value = h(key);

    std::mt19937 generator(hash_value); //hash_value is seed;

    for (int i = 0; i < k; i++) {
        index = generator() % m;
        indeces->push_back(index);
    }

    return indeces;
}

void bloom_filter::bf_insert(std::string key) {
    key = remove_char (key);
    std::vector<int> *indeces = get_hashes(key);
    int index;

    for (int i = 0; i < indeces->size(); i++) {
        index = indeces->at(i);

        if (filter[index] == 0) {
            size++;
        }

        filter[index] = 1;
    }

    delete indeces;
}

bool bloom_filter::bf_search (std::string key) {
    key = remove_char (key);
    std::vector<int> *indeces = get_hashes(key);
    int index;

    for (int i = 0; i < indeces->size(); i++) {
        index = indeces->at(i);

        if (filter[index] == 0) {
            return false;
        }
    }
    return true;
}

void bloom_filter::bf_load (std::string file_name) {
    std::string key;
    std::fstream fin;
    std::istringstream iss;

    fin.open(file_name);
    while (fin >> key) {
        key = remove_char (key);
        bf_insert(key);
    }
    fin.close();
}

void bloom_filter::check_max_size() {
    return;
}
stats* bloom_filter::get_stats(){
    return s;
}
unsigned int bloom_filter::get_max_size() {
    return m;
}

void bloom_filter::reset_comps() {
    s->comps = 0;
}

unsigned int bloom_filter::get_size() {
    return size;
}

ds_node* bloom_filter::get_main() {
    return nullptr;
}


void bloom_filter::ds_inorder() {
    std::cout << "\n";
}

void bloom_filter::ds_search (std::string key) {
    std::cout << bf_search(key) << std::endl;
}

void bloom_filter::ds_minimum () {
    std::cout << "\n";
}

void bloom_filter::ds_maximum () {
    std::cout << "\n";
}

void bloom_filter::ds_succssor (std::string key) {
    std::cout << "\n";
}

void bloom_filter::ds_insert (std::string key) {
    bf_insert (key);
}

void bloom_filter::ds_delete (std::string key) {
    return;
}

void bloom_filter::ds_load (std::string file_name) {
    bf_load (file_name);
}