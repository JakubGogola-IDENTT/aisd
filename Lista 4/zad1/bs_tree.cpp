#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <regex>

#include "bs_tree.hpp"
#include "functions.hpp"


bs_tree::bs_tree () {
    root = nullptr;
    size = 0;
    max_size = 0;
    s = new stats();
}

bs_tree::~bs_tree () {
    while (root != nullptr) {
        bs_delete (root);
    }
    delete s;
}

void bs_tree::bs_inorder (bs_node *node) {
    if (node != nullptr) {
        bs_inorder(node->left); //First show left subtree.

        std::cout << node->key << " ";
    
        bs_inorder(node->right); //Secondly show right subtree.
    }
}


bs_node* bs_tree::bs_search (bs_node *node, std::string key) {
    s->comps++;
    if (node == nullptr || key == node->key) { //If key isn't in tree or key was found.
        return node;
    }

    s->comps++;
    if (key < node->key) { //If key is smaller than key in current node - search in left tree.
        return bs_search(node->left, key);
    } else { //Oth. search in right tree.
        return bs_search (node->right, key);
    }
}


bs_node* bs_tree::bs_minimum (bs_node *node) {
    if (node == nullptr) {
        return node;
    }

    //Search last element in left subtree of node.
    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}


bs_node* bs_tree::bs_maximum (bs_node *node) {
    if (node == nullptr) {
        return node;
    }

    //Search right element in right subtree of node.
    while (node->right != nullptr) {
        node = node->right;
    }

    return node;
}

//First greater value than node.
bs_node* bs_tree::bs_successor (bs_node *node) {
    s->successors++;

    //If node has right subtree, search succesor in right subtree.
    if (node->right != nullptr) {
        return bs_minimum (node->right);
    }

    //Oth. successor is lowest ancestor of node which left son is ancestor of node too.
    bs_node *tmp = node->parent;
    while (tmp != nullptr && node == tmp->right) {
        node = tmp;
        tmp = tmp->parent;
    }

    return tmp;
}


void bs_tree::bs_insert (std::string key) {
    bs_node *new_node = new bs_node(key);
    new_node->key = key;

    bs_node *n = nullptr;
    bs_node *m = root;

    while (m != nullptr) {
        n = m;
        if (new_node->key < m->key) { //If key is greater than current node go to left subtree.
            m = m->left;
        } else {
            m = m->right; //Oth. go to right subtree.
        }
    } 

    //Parent of new node is first greater node than it.
    new_node->parent = n;

    if (n == nullptr) { //When tree is empty, new node is root.
        root = new_node;
    } else if (new_node->key < n->key) { //Oth. put new node into parent's pointer to left or right subtree.
        n->left = new_node;
    } else {
        n->right = new_node;
    }

    size++;
}


void bs_tree::bs_delete (bs_node *node) {
    bs_node *m, *n;

    //If node is only leaf or has only one subtree - delete this.
    if (node->left == nullptr || node->right == nullptr) {
        n = node;
    } else { //Oth. Find successor of it.
        n = bs_successor(node);
    }

    //Oth. cut node, cut succesor and put successor on node's place.
    if (n->left != nullptr) {
        m = n->left;
    } else {
        m = n->right;
    }

    if (m != nullptr) {
       m->parent = n->parent;
    }

    if (n->parent == nullptr) {
        root = m;
    } else if (n == n->parent->left) {
        n->parent->left = m;
    } else {
        n->parent->right = m;
    }

    if (n != node) {
        node->key = n->key;
        //node->parent = n->parent;
        //node->left = n->left;
        //node->right = n->right;
    }

    size--;
    delete n;
}


bs_node* bs_tree::get_root () {
    return root;
}

ds_node* bs_tree::get_main() {
    return root;
}

unsigned int bs_tree::get_size () {
    return size;
}

void bs_tree::check_max_size() {
    if (size > max_size) {
        max_size = size;
    }
}

stats* bs_tree::get_stats() {
    return s;
}
unsigned int bs_tree::get_max_size() {
    return max_size;
}

void bs_tree::reset_comps() {
    s->comps = 0;
}

void bs_tree::ds_inorder() {
    bs_inorder(root);
    std::cout << "\n";
    s->inorders++;
}

void bs_tree::ds_search (std::string key) {
    if (bs_search(root, key) != nullptr) {
        std::cout << "1" << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }
    s->finds++;
}

void bs_tree::ds_minimum () {
    bs_node *min_node = bs_minimum(root);

    if (min_node != nullptr) {
        std::cout << min_node->key << std::endl;
    } else {
        std::cout << "\n";
    }
    s->mins++;
}

void bs_tree::ds_maximum () {
    bs_node *max_node =bs_maximum(root);

    if (max_node != nullptr) {
        std::cout << max_node->key << std::endl;
    } else {
        std::cout << "\n";
    }
    s->maxs++;
}

void bs_tree::ds_succssor (std::string key){
    bs_node *node = bs_search (root, key);
    
    if (node == nullptr) {
        std::cout << "\n";
        return;
    }

    bs_node *successor = bs_successor(node);

    if (successor != nullptr) {
        std::cout << successor->key << std::endl;
    } else {
        std::cout << "\n";
    }
    s->successors++;
}

void bs_tree::ds_insert (std::string key) {
    bs_insert(key);
    check_max_size();
    s->inserts++;
}

void bs_tree::ds_delete (std::string key) {
    if (root == nullptr) {
       return;
    }

    bs_node *node = bs_search(root, key);
    if (node == nullptr) {
        return;
    }

    bs_delete (node);
    s->deletes++;
}

void bs_tree::ds_load (std::string file_name) {
    std::string line;   
    std::string key;
    std::ifstream fin;
    std::istringstream iss;

    fin.open(file_name, std::ifstream::in);
    while (fin >> key) {
        key = remove_char (key);
        bs_insert (key);
    }
    fin.close();
    s->loads++;
}