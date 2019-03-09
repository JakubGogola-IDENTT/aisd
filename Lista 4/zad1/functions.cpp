#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "functions.hpp"
#include "tests.hpp"

data_structure* parse_args (int argc, char** argv) {
    if (argc != 3 || strcmp(argv[1], "--type") != 0) {
        std::cerr << "*** Erorr: Invalid number of arguments!" << std::endl;
        exit(1);
    }

    if (strcmp (argv[2], "bst") == 0) {
        return new bs_tree();
    } else if (strcmp (argv[2], "rbt") == 0) {
        return new rb_tree();
    } else if (strcmp (argv[2], "hmap") == 0) {
        return new hash_table();
    } else if (strcmp (argv[2], "bloom") == 0) {
        return new bloom_filter();
    } else if (strcmp (argv[2], "nt") == 0) {
        test_switch_point();
        exit(1);
    } else if (strcmp (argv[2], "ot") == 0) {
        test_oprations_time();
        exit(1);
    } else if (strcmp (argv[2], "on") == 0) {
        test_operations_num();
        exit(1);
    } else {
        std::cerr << "*** Error: Invalid argument!" << std::endl;
        exit(1);
    }
}

std::string remove_char (std::string str) {
    str.erase(std::remove_if(str.begin(), str.end(), &ispunct), str.end());
    str.erase(std::remove_if(str.begin(), str.end(), &isspace), str.end());
    return str;
}