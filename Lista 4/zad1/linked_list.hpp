#pragma once

#include <iostream>

#include "data_structure.hpp"

struct ll_node : ds_node {
    //std::string key;
    ll_node *next;

    ll_node (std::string key, ll_node *next) {
        this->key = key;
        this->next = next;
    }
};

class linked_list : public data_structure {
private:
    ll_node *tail;

public:
    linked_list ();
    ~linked_list ();
    ll_node* ll_search (std::string key);
    ll_node* ll_minimum ();
    ll_node* ll_maximum ();
    void ll_insert (std::string key);
    void ll_delete (std::string key);
    ll_node* get_tail();

    void check_max_size();
    stats* get_stats();
    unsigned int get_max_size();
    unsigned int get_size ();
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
