#include <iostream>
#include <cstring>
#include <ctime>

#include "ex1.hpp"

std::string* parse_args (int argc, char** argv) {
    int len;

    if (argc == 5) {
        len = 2;
    } else {
        len = 4;
    }

    std::string* params = new std::string[len];
    
    for (int i = 1; i < argc; i++) {
        if (strcmp (argv[i], "--comp") == 0) {
            params[0] = argv[i + 1];
        } else if (strcmp (argv[i], "--type") == 0) {
            params[1] = argv[i + 1];
        } else if (strcmp (argv[i], "--stat") == 0) {
            params[2] = argv[i + 1];
            params[3] = argv[i + 2];
        }
    }

    return params;
}

bool compare (std::string comparator, int a, int b) {
    if (comparator.compare("<=") == 0) {
        return a <= b;
    } else {
        return a >= b;
    }
}


bool is_sorted (data* d) {
    int* array = d -> array;
    int length = d ->length;
    std::string comparator = d -> comparator;

    for (int i = 0; i < length - 1; i++) {
        if (!compare (comparator, array[i], array[i + 1])) {
            return false;
        }
    }

    return true;
}