#pragma once

#include "data_structure.hpp"

enum rb_color {
    RED = 'r',
    BLACK = 'b'
};

struct rb_node : ds_node {
    //std::string key;
    enum rb_color color;

    rb_node *parent;
    rb_node *left;
    rb_node *right;

    rb_node (std::string key, enum rb_color color, rb_node *ptr) {
        this->key = key;
        this->color = color;
        this->parent = ptr;
        this->left = ptr;
        this->right = ptr;
    }
};

class rb_tree : public data_structure {
private:

    rb_node *root;
    rb_node *nil;
    void rb_left_rotate(rb_node *node);
    void rb_right_rotate(rb_node *node);
    void rb_delete_fixup(rb_node *node);
    void rb_bst_insert (rb_node *new_node);

public:
    rb_tree();
    ~rb_tree();
    void rb_inorder (rb_node *node);
    rb_node* rb_search (rb_node *node, std::string key);
    rb_node* rb_minimum (rb_node *node);
    rb_node* rb_maximum (rb_node *node);
    rb_node* rb_successor (rb_node *node);
    void rb_insert(std::string key);
    void rb_delete(rb_node *node);
    rb_node* get_root();

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