#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <cmath>

#include "ex1.hpp"


void radix_sort (data* d, stats* s, int base) {
    

    int* array = d -> array;
    int length = d -> length;

    int max = array[0];
    for (int i  = 1; i < length; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    if (base == 1) {
        int bit_length = sizeof (int) * 8 - __builtin_clrsbl(length);
        if (bit_length < log2(length)) {
            base = bit_length;
        } else {
            base = log2 (length);
        }
    }

    for (int e = 1; max / e > 0; e = e * base) {
        counting_sort (d, s, base, e);
    }
}

void counting_sort (data* d, stats* s, int base, int e) {
    int n = d -> length;
    int k = base; //k - upper bound of numbers to sort.
    std::string comparator = d -> comparator;
    
    int* a = d -> array; 
    int* b = new int[n]; //Results array.
    int* c = new int[k]; //Array with counts.

    int i;

    for (i = 0; i < k; i++) {
        c[i] = 0; //Put 0 in every index of C.
    }

    for (i = 0; i < n; i++) {
        c[(a[i] / e) % base]++;
    }

    for (i = 1; i < k; i++) {
        c[i] += c[i - 1];
    }

    for (i = n - 1; i >= 0; i--) {
        s -> swaps++;

        b[c[(a[i] / e) % base] - 1] = a[i];
        c[(a[i] / e) % base]--;
    }

    for (i = 0; i < n; i++) {
        a[i] = b[i];
    }

    delete [] c;
    delete [] b;
}