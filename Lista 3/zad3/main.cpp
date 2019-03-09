#include <iostream>

#include "functions.hpp"

int main () {
    statistics();
    return 0;
}

bool is_sorted (int* array, int length) {
    for (int i = 0; i < length - 1; i++) {
        if (!(array[i] <= array[i + 1])) {
            return false;
        }
    }
    return true;
}