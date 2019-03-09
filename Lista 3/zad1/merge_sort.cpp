#include <iostream>
#include <cmath>
#include "ex1.hpp"

void merge_sort (data* d, stats* s, int p, int q) {
    int index; //Index of middle element.
    if (p < q) {
        index = p + (q - p) / 2; //Compute index of middle element.
        merge_sort (d, s, p, index); //Resursive merge sort of left half of array.
        merge_sort (d, s, index + 1, q); //Recursive merge sort on right half of array.
        merge (d, s, p, index, q); //Merge sorted halfs of array (when every part of array has length 1).
    }
}

void merge (data* d, stats* s, int p, int index, int q) {
    int* array = d -> array;
    int* temp = new int[d -> length];
    std::string comparator = d -> comparator;

    int i = 0; //First element of temp array.
    int j = p; //First element of 'left' array.
    int k = index + 1; //First element of 'right' array.

    while (j <= index && k <= q) { //Compare elements until 'left' or 'right' array isn't empty.
        s -> compares++;
 
        if (compare (comparator, array[j], array[k])) { //Take smaller element and put it to temp.
            s -> swaps++;

            temp[i] = array[j];
            j++;
        } else {
            s -> swaps++;

            temp[i] = array[k];
            k++;
        }
        i++;
    }

    //Put elements to end of sorted array.
    while (j <= index) {
        temp[i] = array[j];
        i++;
        j++;
    }

    while (k <= q) {
        temp[i] = array[k];
        i++;
        k++;
    }

    i = 0;
    for (int l = p; l <= q; l++) {
        array[l] = temp[i];
        i++;
    }

    delete [] temp;
}

