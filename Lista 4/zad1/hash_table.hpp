#pragma once

#include <iostream>

#include "data_structure.hpp"

enum type {
    RBT = 'r',
    LL = 'l'
};

class hash_table : public data_structure {
private:
    data_structure **ht;
    unsigned int switch_point;
    enum type *types;
    unsigned long get_hash(std::string key);
    void switch_ds (unsigned long index);

public:
    hash_table();
    ~hash_table();

    void check_max_size();
    stats* get_stats();
    unsigned int get_max_size();
    unsigned int get_size();
    void reset_comps();
    
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