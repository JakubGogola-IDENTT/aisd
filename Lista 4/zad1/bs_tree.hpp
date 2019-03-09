#pragma once

#include "data_structure.hpp"

struct bs_node : ds_node {
    //std::string key;
    
    bs_node *parent;
    bs_node *left;
    bs_node *right;

    bs_node (std::string key) {
        this->key = key;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class bs_tree : public data_structure {
private:
    bs_node *root;

protected:


public:
    bs_tree ();
    ~bs_tree();
    void bs_inorder (bs_node *node);
    bs_node* bs_search (bs_node *node, std::string key);
    bs_node* bs_minimum (bs_node *node);
    bs_node* bs_maximum (bs_node *node);
    bs_node* bs_successor (bs_node *node);
    void bs_insert (std::string key);
    void bs_delete (bs_node *node);
    bs_node* get_root ();

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