#include <iostream>
#include <sstream>
#include <fstream>

#include "linked_list.hpp"
#include "functions.hpp"

linked_list::linked_list () {
    tail = nullptr;
    size = 0;
    s = new stats();
}

linked_list::~linked_list () {
    std::string key;
    
    while (tail != nullptr) {
        key = tail->key;
        ll_delete (key);
    }

    delete s;
}

void linked_list::ll_insert (std::string key) {
    if (tail == nullptr) {
        tail = new ll_node (key, nullptr);
        return;
    }
    
    ll_node *node = new ll_node (key, tail);
    tail = node;
    size++;
}

void linked_list::ll_delete (std::string key) {
    ll_node *tmp = tail;
    ll_node *prev = nullptr;

    if (tail == nullptr) {
        return;
    }

    if (key == tail->key) {
        tail = tail->next;
    } else {
        while (tmp->key != key && tmp != nullptr) {
            prev = tmp;
            tmp = tmp->next;
        }
        prev->next = tmp->next;
    }

    size--;
    delete tmp;
}

ll_node* linked_list::ll_minimum () {
    if (tail == nullptr) {
        return tail;
    }

    ll_node *tmp = tail;
    ll_node *min_node = tail;

    while (tmp != nullptr) {
        if (tmp->key < min_node->key) {
            min_node = tmp;
        }

        tmp = tmp->next;
    }

    return min_node;
}

ll_node* linked_list::ll_maximum () {
    if (tail == nullptr) {
        return tail;
    }

    ll_node *tmp = tail->next;
    ll_node *max_node = tail;

    while (tmp != nullptr) {
        if (tmp->key > max_node->key) {
            max_node = tmp;
        }

        tmp = tmp->next;
    }

    return max_node;
}

ll_node* linked_list::ll_search (std::string key) {
    if (tail == nullptr) {
        return tail;
    }

    ll_node *tmp = tail;

    while (tmp != nullptr) {
        s->comps++;
        if (tmp->key == key) {
            return tmp;
        }

        tmp = tmp->next;
    }

    return nullptr;
}

ll_node* linked_list::get_tail () {
    return tail;
}


unsigned int linked_list::get_size () {
    return size;
}

void linked_list::check_max_size() {
    if (size > max_size) {
        max_size = size;
    }
}

stats* linked_list::get_stats() {
    return s;
}

unsigned int linked_list::get_max_size() {
    return max_size;
}

void linked_list::reset_comps() {
    s->comps = 0;
}

ds_node* linked_list::get_main () {
    return tail;
}

void linked_list::ds_inorder() {
    std::cout << "\n";
    s->inorders++;
}

void linked_list::ds_search (std::string key) {
    if (ll_search(key) != nullptr) {
        std::cout << "1" << std::endl;
    } else {
        std::cout << "0" << std::endl;
    }
    s->finds++;
}

void linked_list::ds_minimum () {
    ll_node *min_node = ll_minimum();

    if (min_node != nullptr) {
        std::cout << min_node->key << std::endl;
    } else {
        std::cout << "\n";
    }
    s->mins++;
}

void linked_list::ds_maximum () {
    ll_node *max_node = ll_maximum();

    if (max_node != nullptr) {
        std::cout << max_node->key << std::endl;
    } else {
        std::cout << "\n";
    }
    s->maxs++;
}

void linked_list::ds_succssor (std::string key) {
    std::cout << "\n";
    s->successors++;
}
void linked_list::ds_insert (std::string key){
    ll_insert (key);
    check_max_size();
    s->inserts++;
}
void linked_list::ds_delete (std::string key){
    ll_delete (key);
    s->deletes++;
}
void linked_list::ds_load (std::string file_name){
    std::string line;   
    std::string key;
    std::ifstream fin;
    std::istringstream iss;

    std::regex expr ("");

    fin.open(file_name, std::ifstream::in);
    while (fin >> key) {
        key = remove_char (key);
        ll_insert (key);
    }
    fin.close();
    s->loads++;
}

