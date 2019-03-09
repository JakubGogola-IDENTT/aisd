#pragma once

#include <iostream>

struct ds_node {
public:
    std::string key;
};

struct stats {
public:
    unsigned int comps;
    unsigned int inserts;
    unsigned int loads;
    unsigned int deletes;
    unsigned int finds;
    unsigned int mins;
    unsigned int maxs;
    unsigned int successors;
    unsigned int inorders;

    stats() {
        comps = 0;
        inserts = 0;
        loads = 0;
        inserts = 0;
        deletes = 0;
        finds = 0;
        mins = 0;
        maxs = 0;
        successors = 0;
        inorders = 0;
    }

};

class data_structure {
    friend class bs_tree;
    friend class rb_tree;
    friend class linked_list;
    friend class hash_table;
    friend class bloom_filter;
protected:
    unsigned int size;
    unsigned int max_size;
    stats *s;

public:
    virtual void check_max_size() = 0;
    virtual stats* get_stats() = 0;
    virtual unsigned int get_max_size()  = 0;
    virtual void reset_comps() = 0;

    virtual unsigned int get_size() = 0;
    virtual ds_node* get_main() = 0;
    virtual void ds_inorder() = 0;
    virtual void ds_search (std::string key) = 0;
    virtual void ds_minimum () = 0;
    virtual void ds_maximum () = 0;
    virtual void ds_succssor (std::string key) = 0;
    virtual void ds_insert (std::string key) = 0;
    virtual void ds_delete (std::string key) = 0;
    virtual void ds_load (std::string file_name) = 0;
};