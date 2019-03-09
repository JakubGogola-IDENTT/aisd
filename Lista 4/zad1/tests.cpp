#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <numeric>
#include <ctime>
#include <cstdlib>

#include "tests.hpp"
#include "bs_tree.hpp"
#include "rb_tree.hpp"
#include "hash_table.hpp"
#include "linked_list.hpp"
#include "functions.hpp"
#include "data_structure.hpp"

std::string gen_file(std::string file_name, int num_to_find) {
    std::ifstream fin;
    std::ofstream fout;
    std::string str;
    std::string out_file = "to_find.txt";
    int inserted = 0;

    fin.open(file_name);
    fout.open(out_file, std::ostream::out);

    while (fin >> str && inserted <= num_to_find) {
        if (inserted % 2 != 0) {
            continue;
        }

        str = remove_char (str);
        fout << str << std::endl;
        inserted++;
    }

    fin.close();
    fout.close();

    return out_file;
}

void test_switch_point() {
    data_structure *ll;
    data_structure *rbt;
    time_t start, stop;
    double diff;
    int to_insert;
    std::ifstream fin;
    std::string str;

    std::vector<double> *ll_insert_time;
    std::vector<double> *rbt_insert_time;

    std::vector<double> *ll_find_time;
    std::vector<double> *rbt_find_time;

    double avg;

    std::string data_file = "bible.txt";
    std::vector<std::string> *inserted = new std::vector<std::string>;
    ll_insert_time = new std::vector<double>;
    rbt_insert_time = new std::vector<double>;
    ll_find_time = new std::vector<double>;
    rbt_find_time = new std::vector<double>;

     srand(time(nullptr));

    for (int i = 20;i <= 900; i += 20) {
        ll = new linked_list();
        rbt = new rb_tree();

        to_insert = i;

        fin.open(data_file);
        while (fin >> str && to_insert > 0) {
            str = remove_char (str);
            
            start = clock();
            ll->ds_insert (str);
            stop = clock();
            diff = compute_time(start, stop);
            ll_insert_time->push_back(diff);

            start = clock();
            rbt->ds_insert (str);
            stop = clock();
            diff = compute_time(start, stop);
            rbt_insert_time->push_back(diff);

            inserted->push_back(str);

            to_insert--;
        }
        fin.close();

        int r;

        for (int i = 0; i < inserted->size() / 2; i++) {
            r = rand() % inserted->size();
            str = inserted->at(r);

            start = clock();
            ll->ds_search(str);
            stop = clock();
            diff = compute_time(start, stop);
            ll_find_time->push_back(diff);

            start = clock();
            rbt->ds_search(str);
            stop = clock();
            diff = compute_time(start, stop);
            rbt_find_time->push_back(diff);

        }

        std::cerr << "Switch point: " << i << std::endl;

        avg = compute_avg (ll_insert_time);
        std::cerr << "Linked list - avg insert: " << avg << " sec" << std::endl;

        avg = compute_avg (rbt_insert_time);
        std::cerr << "RB-Tree - avg insert: " << avg << " sec" << std::endl;

        avg = compute_avg (ll_find_time);
        std::cerr << "Linked list - avg find: " << avg << " sec" << std::endl;

        avg = compute_avg (rbt_find_time);
        std::cerr << "RB-Tree - avg find: " << avg << " sec" << std::endl;
        
        std::cerr << "\n";
        ll_insert_time->clear();
        ll_find_time->clear();
        rbt_insert_time->clear();
        rbt_find_time->clear();
        inserted->clear();

        delete ll;
        delete rbt;
    }

    delete ll_insert_time;
    delete ll_find_time;
    delete rbt_insert_time;
    delete rbt_find_time;
}

void test_oprations_time() {
    data_structure *bst;
    data_structure *rbt;
    data_structure *ht;

    time_t start, stop;
    std::vector<double> *bst_time;
    std::vector<double> *rbt_time;
    std::vector<double> *ht_time;

    std::ifstream fin;
    std::string input_file = "sample.txt";
    std::string str;

    fin.open(input_file);

    bst_time = new std::vector<double>;
    rbt_time = new std::vector<double>;
    ht_time = new std::vector<double>;

    bst = new bs_tree();
    rbt = new rb_tree();
    ht = new hash_table();

    //inserts
    while (fin >> str) {
        str = remove_char (str);
        start = clock();
        bst->ds_insert(str);
        stop = clock();
        bst_time->push_back(compute_time(start, stop));

        start = clock();
        rbt->ds_insert(str);
        stop = clock();
        rbt_time->push_back(compute_time(start, stop));

        start = clock();
        ht->ds_insert(str);
        stop = clock();
        ht_time->push_back(compute_time(start, stop));
    }
    fin.close();

    std::cerr << "BST avg insert time: " << compute_avg (bst_time) << " sec" << std::endl;
    std::cerr << "RBT avg insert time: " << compute_avg (rbt_time) << " sec" << std::endl;
    std::cerr << "HT avg insert time: " << compute_avg (ht_time) << " sec" << std::endl;

    bst_time->clear();
    rbt_time->clear();
    ht_time->clear();

    fin.open (input_file);
    //searches
    while (fin >> str) {
        str = remove_char (str);
        start = clock();
        bst->ds_search(str);
        stop = clock();
        bst_time->push_back(compute_time(start, stop));

        start = clock();
        rbt->ds_search(str);
        stop = clock();
        rbt_time->push_back(compute_time(start, stop));

        start = clock();
        ht->ds_search(str);
        stop = clock();
        ht_time->push_back(compute_time(start, stop));
    }
    fin.close();

    std::cerr << "\n";
    std::cerr << "BST avg search time: " << compute_avg (bst_time) << " sec" << std::endl;
    std::cerr << "RBT avg search time: " << compute_avg (rbt_time) << " sec" << std::endl;
    std::cerr << "HT avg search time: " << compute_avg (ht_time) << " sec" << std::endl;

    bst_time->clear();
    rbt_time->clear();
    ht_time->clear();

    fin.open(input_file);
    //deletes
    while (fin >> str) {
        str = remove_char (str);
        start = clock();
        bst->ds_delete(str);
        stop = clock();
        bst_time->push_back(compute_time(start, stop));

        start = clock();
        
        rbt->ds_delete(str);
        stop = clock();
        rbt_time->push_back(compute_time(start, stop));

        start = clock();
        ht->ds_delete(str);
        stop = clock();
        ht_time->push_back(compute_time(start, stop));
    }
    fin.close();
    std::cerr << "\n";
    std::cerr << "BST avg delete time: " << compute_avg (bst_time) << " sec" << std::endl;
    std::cerr << "RBT avg delete time: " << compute_avg (rbt_time) << " sec" << std::endl;
    std::cerr << "HT avg delete time: " << compute_avg (ht_time) << " sec" << std::endl;

    bst_time->clear();
    rbt_time->clear();
    ht_time->clear();

    delete bst;
    delete rbt;
    delete ht;

    delete bst_time;
    delete rbt_time;
    delete ht_time;
}

void test_operations_num() {
    data_structure *bst;
    data_structure *rbt;
    data_structure *ht;

    time_t start, stop;
    std::vector<int> *bst_comps;
    std::vector<int> *rbt_comps;
    std::vector<int> *ht_comps;

    std::vector<std::string> *inserted;

    int inserts = 20000;

    std::ifstream fin;
    std::string repeats = "bible.txt";
    std::string without_repeats = "aspell_wordlist.txt";
    std::string str;

    bst = new bs_tree();
    rbt = new rb_tree();
    ht = new hash_table();

    bst_comps = new std::vector<int>;
    rbt_comps = new std::vector<int>;
    ht_comps = new std::vector<int>;

    inserted = new std::vector<std::string>;

    fin.open(repeats);
    while (fin >> str && inserts > 0) {
        str = remove_char(str);
        inserted->push_back(str);

        bst->ds_insert(str);
        rbt->ds_insert(str);
        ht->ds_insert(str);
        inserts--;
    }
    fin.close();

    srand(time(nullptr));
    int r;

    for (int i = 0; i < 20; i++) {
        r = rand() % inserted->size();
        bst->ds_search(inserted->at(r));
        bst_comps->push_back(bst->get_stats()->comps);
        bst->reset_comps();

        rbt->ds_search(inserted->at(r));
        rbt_comps->push_back(rbt->get_stats()->comps);
        rbt->reset_comps();

        ht->ds_search(inserted->at(r));
        ht_comps->push_back(ht->get_stats()->comps);
        ht->reset_comps();
    }
    std::cerr << "With repeats -> " << repeats << std::endl;
    std::cerr << "BST: " << std::endl;
    std::cerr << "~~~Min: " << get_min(bst_comps) << std::endl;
    std::cerr << "~~~Avg: " << get_avg(bst_comps) << std::endl;
    std::cerr << "~~~Max: " << get_max(bst_comps) << std::endl;

    std::cerr << "RBT: " << std::endl;
    std::cerr << "~~~Min: " << get_min(rbt_comps) << std::endl;
    std::cerr << "~~~Avg: " << get_avg(rbt_comps) << std::endl;
    std::cerr << "~~~Max: " << get_max(rbt_comps) << std::endl;

    std::cerr << "HT: " << std::endl;
    std::cerr << "~~~Min: " << get_min(ht_comps) << std::endl;
    std::cerr << "~~~Avg: " << get_avg(ht_comps) << std::endl;
    std::cerr << "~~~Max: " << get_max(ht_comps) << std::endl;

    delete bst;
    delete rbt;
    delete ht;

    bst_comps->clear();
    rbt_comps->clear();
    ht_comps->clear();
    inserted->clear();

    bst = new bs_tree();
    rbt = new rb_tree();
    ht = new hash_table();

    inserted = new std::vector<std::string>;

    inserts = 20000;

    fin.open(without_repeats);
    while (fin >> str && inserts > 0) {
        str = remove_char(str);
        inserted->push_back(str);

        bst->ds_insert(str);
        rbt->ds_insert(str);
        ht->ds_insert(str);
        inserts--;
    }
    fin.close();

    for (int i = 0; i < 20; i++) {
        r = rand() % inserted->size();
        bst->ds_search(inserted->at(r));
        bst_comps->push_back(bst->get_stats()->comps);
        bst->reset_comps();

        rbt->ds_search(inserted->at(r));
        rbt_comps->push_back(rbt->get_stats()->comps);
        rbt->reset_comps();

        ht->ds_search(inserted->at(r));
        ht_comps->push_back(ht->get_stats()->comps);
        ht->reset_comps();
    }

    std::cerr << "\nWithout repeats -> " << without_repeats << std::endl;
    std::cerr << "BST: " << std::endl;
    std::cerr << "~~~Min: " << get_min(bst_comps) << std::endl;
    std::cerr << "~~~Avg: " << get_avg(bst_comps) << std::endl;
    std::cerr << "~~~Max: " << get_max(bst_comps) << std::endl;

    std::cerr << "RBT: " << std::endl;
    std::cerr << "~~~Min: " << get_min(rbt_comps) << std::endl;
    std::cerr << "~~~Avg: " << get_avg(rbt_comps) << std::endl;
    std::cerr << "~~~Max: " << get_max(rbt_comps) << std::endl;

    std::cerr << "HT: " << std::endl;
    std::cerr << "~~~Min: " << get_min(ht_comps) << std::endl;
    std::cerr << "~~~Avg: " << get_avg(ht_comps) << std::endl;
    std::cerr << "~~~Max: " << get_max(ht_comps) << std::endl;

    delete bst;
    delete rbt;
    delete ht;

    bst_comps->clear();
    rbt_comps->clear();
    ht_comps->clear();

    delete bst_comps;
    delete rbt_comps;
    delete ht_comps;
}

double compute_time (time_t start, time_t stop) {
    return (double) (stop - start) / CLOCKS_PER_SEC;
}

double compute_avg (std::vector<double> *v) {
    return std::accumulate (v->begin(), v->end(), 0.0) / v->size();
}

int get_min (std::vector<int> *v) {
    int min = v->at(0);
    for (int i = 1;i < v->size(); i++) {
        if (v->at(i) < min) {
            min = v->at(i);
        }
    }

    return min;
}

int get_max (std::vector<int> *v) {
    int max = v->at(0);
    for (int i = 1;i < v->size(); i++) {
        if (v->at(i) > max) {
            max = v->at(i);
        }
    }
    return max;
}

int get_avg (std::vector<int> *v) {
    return std::accumulate(v->begin(), v->end(), 0.0) / v->size();
}