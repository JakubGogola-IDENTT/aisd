#include <iostream>

#include "functions.hpp"

int binary_search (stats* s, int* array, int p, int q, int v) {
    if (p > q) {
        s -> compares++;
        return 0;
    }

    int m = p + (q - p) / 2;
    
    if (array[m] == v) { //If value equals to middle elment of array we found our element.
        s -> compares++;
        return 1;
    } else if (array[m] > v) { //If v is smaller than middle element we serch it in left part of array.
        s -> compares++;
        return binary_search (s, array, p, m - 1, v);
    } else { //Oth. we search v in right part of array.
        s -> compares++;    
        return binary_search (s, array, m + 1, q, v);
    }
}