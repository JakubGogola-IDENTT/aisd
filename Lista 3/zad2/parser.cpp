#include <iostream>
#include <cstring>

#include "functions.hpp"

bool parse_args (int argc, char** argv, char* param) {
    if (strcmp (argv[1], "-p") == 0) {
        *param = 'p';
    } else if (strcmp (argv[1], "-r") == 0) {
        *param = 'r';
    } else if (strcmp (argv[1], "-s") == 0) {
        *param = 's';
    } else {
        return false;
    }
    return true;
}