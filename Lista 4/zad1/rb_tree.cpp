#include <iostream>
#include <sstream>
#include <fstream>

#include "rb_tree.hpp"
#include "functions.hpp"

rb_tree::rb_tree () {
    nil = new rb_node ("", BLACK, this->nil);
    root = nil;
    size = 0;
    s = new stats();
}

rb_tree::~rb_tree () {
    while (root != nil) {
        rb_delete (root);
    }
    delete s;
} 

void rb_tree::rb_inorder (rb_node *node) {
    if (node != nil) {
        rb_inorder(node->left); 
        std::cout << node->key << " ";
        rb_inorder(node->right);
    }
}


rb_node* rb_tree::rb_search (rb_node *node, std::string key) {
    if (node == nil || key == node->key) { //If key isn't in tree or key was found.
        return node;
    }

    s->comps++;
    if (key < node->key) {
        return rb_search(node->left, key);
    } else {
        return rb_search (node->right, key);
    }
}


rb_node* rb_tree::rb_minimum (rb_node *node) {
    if (node == nil) {
        return node;
    }

    while (node->left != nil) {
        node = node->left;
    }
    return node;
}


rb_node* rb_tree::rb_maximum (rb_node *node) {
    if (node == nil) {
        return node;
    }

    while (node->right != nil) {
        node = node->right;
    }

    return node;
}


rb_node* rb_tree::rb_successor (rb_node *node) {
    if (node->right != nil) {
        return rb_minimum (node->right);
    }

    rb_node *tmp = node->parent;
    while (tmp != nil && node == tmp->right) {
        node = tmp;
        tmp = tmp->parent;
    }

    return tmp;
}


void rb_tree::rb_left_rotate(rb_node *node) {
    rb_node *m = node->right;
    node->right = m->left;

    if (m->left != nil) {
        m->left->parent = node;
    }

    m->parent = node->parent;

    if (node->parent == nil) {
        root = m;
    } else if (node == node->parent->left) {
        node->parent->left = m;
    } else {
        node->parent->right = m;
    }

    m->left = node;
    node->parent = m;
}


void rb_tree::rb_right_rotate(rb_node *node) {
    rb_node *m = node->left;
    node->left = m ->right;

    if (m->right != nil) {
        m->right->parent = node;
    }

    m->parent = node->parent;

    if (node->parent == nil) {
        root = m;
    } else if (node == node->parent->left) {
        node->parent->left = m;
    } else {
        node->parent->right = m;
    }
    
    m->right = node;
    node->parent = m;
}


void rb_tree::rb_bst_insert (rb_node *new_node) {

    rb_node *m = root;
    rb_node *n = nil;
    while (m != nil) {
        n = m;
        if (new_node->key < m->key) {
            m = m->left;
        } else {
            m = m->right;
        }
    } 

    new_node->parent = n;

    if (n == nil) {
        root = new_node;
    } else if (new_node->key < n->key) {
        n->left = new_node;
    } else {
        n->right = new_node;
    }

    size++;
}


void rb_tree::rb_insert(std::string key) {  
    rb_node *node = new rb_node (key, RED, this->nil);
    rb_bst_insert (node); //Insert new node like in normal Binary Search Tree.
    rb_node *m; //Helper pointer to node.
    
    //Repeat until current node is'nt root (doesn't have parent) or parent of current node isn't red
    //(Repeat until there is an red node with red son).
    while (node != root && node->parent->color == RED) {
        
        //Node's parent is left son of its granfather.
        if (node->parent == node->parent->parent->left) {
            m = node->parent->parent->right; //Pointer to node's uncle.
            
            //CASE 1
            //Because node's grandfather is black we can color node's parent and uncle on black color
            //and color node's grandfather on red. Next we put to node pointer to node's grandfather.
            //If parent of new node (with red color) is red we must repeat while loop.
            if (m->color == RED) {
                node->parent->color = BLACK;
                m->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;

                //CASE 2
                //If node is right son do left rotation on its parent.
                //After rotation node is left son.
                //Now node's uncle is black.
            } else {
                
                if (node == node->parent->right) {
                    node = node->parent;
                    rb_left_rotate (node);              
                } 
                //CASE 3
                //Node's parent is red and its grandfather is black.
                //Now we color node's parent on black and grandfather on red.
                //Node's uncle is black. We do right rotation on node's grandfather to make RB-Tree correct
                //(we are switching places of node and it's uncle in RB-Tree).
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rb_right_rotate (node->parent->parent);
            }

            //Analogical situtaion, but now node's parent is node's parent is right son of its granfather.
            //"Left" and "right" roles are switched.
        } else {
            m = node->parent->parent->left; //Pointer to node's uncle.
            
            if (m->color == RED) {
                node->parent->color = BLACK;
                m->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else {
            
                if (node == node->parent->left) {
                    node = node->parent;
                    rb_right_rotate (node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rb_left_rotate (node->parent->parent);
            }
        }
    }
    root->parent = nil;
    root->color = BLACK;
}



void rb_tree::rb_delete(rb_node *node){
    rb_node *m, *n;

    //Do BST Delete.
    if (node->left == nil || node->right == nil) {
        n = node;
    } else {
        n = rb_successor (node);
    }

    if (n->left != nil) {
        m = n->left;
    } else {
        m = n->right;
    }

    m->parent = n->parent;

    if (n->parent == nil) {
        root = m;
    } else if (n == n->parent->left) {
        n->parent->left = m;
    } else {
        n->parent->right = m;
    }

    if (n != node) {
        node->key = n->key;
        //node->color = n->color;
        //node->parent = n->parent;
        //node->left = n->left;
        //node->right = n->right;
    }

    //Fix properties of RBT if node to delete is black.
    if (n->color == BLACK) {
        rb_delete_fixup (m);
    }
    
    delete n;
    size--;
}


void rb_tree::rb_delete_fixup(rb_node *node) {
    rb_node *m;
    while (node != root && node->color == BLACK) {
        if (node == node->parent->left) {
            m = node->parent->right;

            //Case 1: node's sibling m is red.
            if (m->color == RED) {
                m->color = BLACK;
                node->parent->color = RED;
                rb_left_rotate (node->parent);
                m = node->parent->right;
            }

            if (m->left->color == BLACK && m->right->color == BLACK) {
                m->color = RED; //Case 2: node's sibling m is black,  and both of m's children are black
                node = node->parent;
            } else { 
                if (m->right->color == BLACK) {
                    m->left->color = BLACK; //Case 3: node's sibling m is black, m's left child is red, and m's right child is black
                    m->color = RED;
                    rb_right_rotate (m);
                    m = node->parent->right;
                }

                m->color = node->parent->color; //node's sibling m is black, and m's right child is red
                node->parent->color = BLACK;
                m->right->color = BLACK;
                rb_left_rotate (node->parent);
                node = root;
            }
        } else {
            m = node->parent->left;

            if (m->color == RED) {
                m->color = BLACK;
                node->parent->color = RED;
                rb_right_rotate (node->parent);
                m = node->parent->left;
            }

            if (m->right->color == BLACK && m->left->color == BLACK) {
                m->color = RED;
                node = node->parent;
            } else {
                if (m->left->color == BLACK) {
                    m->right->color = BLACK;
                    m->color = RED;
                    rb_left_rotate (m);
                    m = node->parent->left;
                }

                m->color = node->parent->color;
                node->parent->color = BLACK;
                m->left->color = BLACK;
                rb_right_rotate (node->parent);
                node = root;
            }
        }
    }
    node->color = BLACK;
}


rb_node* rb_tree::get_root () {
    return root;
}

unsigned int rb_tree::get_size() {
    return size;
}

void rb_tree::check_max_size() {
    if (size > max_size) {
        max_size = size;
    }
}
stats* rb_tree::get_stats() {
    return s;
}

unsigned int rb_tree::get_max_size() {
    return max_size;
}

void rb_tree::reset_comps() {
    s->comps = 0;
}

ds_node* rb_tree::get_main() {
    return root;
}

void rb_tree::ds_inorder() {
    rb_inorder(root);
    std::cout << "\n";
    s->inorders++;
}

void rb_tree::ds_search (std::string key) {
    if (rb_search(root, key) != nil) {
        std::cout << "1" << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }
    s->finds++;
}

void rb_tree::ds_minimum () {
    rb_node *min_node = rb_minimum(root);

    if (min_node != nil) {
        std::cout << min_node->key << std::endl;
    } else {
        std::cout << "\n";
    }
    s->mins++;
}
void rb_tree::ds_maximum () {
    rb_node *max_node = rb_maximum(root);

    if (max_node != nil) {
        std::cout << max_node->key << std::endl;
    } else {
        std::cout << "\n";
    }
    s->maxs++;
}
void rb_tree::ds_succssor (std::string key){
    rb_node *node = rb_search(root, key);
    s->successors++;
    if (node == nil) {
        std::cout << "\n";
        return;
    }

    rb_node *successor = rb_successor(node);

    if (successor != nil) {
        std::cout << successor->key << std::endl;
    } else {
        std::cout << "\n";
    }
}

void rb_tree::ds_insert (std::string key) {
    rb_insert (key);
    check_max_size();
    s->inserts++;
}

void rb_tree::ds_delete (std::string key) {
    if (root == nil) {
        return;
    }

    rb_node *node = rb_search (root, key);

    if (node == nil) {
        return;
    }

    rb_delete (node);
    s->deletes++;
}

void rb_tree::ds_load (std::string file_name) {
    std::string line;   
    std::string key;
    std::ifstream fin;
    std::istringstream iss;

    fin.open(file_name, std::ifstream::in);
    while (fin >> key) {
        key = remove_char (key);
        rb_insert (key);
    }
    fin.close();
    s->loads++;
}