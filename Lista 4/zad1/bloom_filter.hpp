#pragma once

#include <iostream>
#include <vector>
#include <functional>

#include "data_structure.hpp"

class bloom_filter : public data_structure {
private:
    int m;
    int k;
    int n;
    //std::vector<unsigned int> *filter;
    unsigned int *filter;

    std::vector<int>* get_hashes(std::string key);

public:
    bloom_filter ();
    ~bloom_filter ();
    void bf_insert (std::string key);
    bool bf_search (std::string key);
    void bf_load (std::string file_name);

    void check_max_size();
    stats* get_stats();
    unsigned int get_max_size();
    void reset_comps();

    unsigned int get_size();
    ds_node* get_main();
    void ds_inorder();
    void ds_search (std::string key);
    void ds_minimum ();
    void ds_maximum ();
    void ds_succssor (std::string key);
    void ds_insert (std::string key);
    void ds_delete (std::string key);
    void ds_load (std::string file_name);
};