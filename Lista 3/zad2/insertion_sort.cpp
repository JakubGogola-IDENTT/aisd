#include <iostream>
#include "functions.hpp"

void insertion_sort (stats* s, int* array, int p, int q) {
    int j; 

    //Loop for all elements in array;
    for (int i = p; i <= q; i++) {
        j = i; //Index of next. element to insert;
        
        while (j >= p && array[j] <= array[j - 1]) {
            s -> compares++;
            //std::cerr << "Comp: " << array[j] << " <= " << array[j - 1] << std::endl;

            if (array[j - 1] != array[j]) {
                s -> swaps++;
                //std::cerr << "Swap: " << array[j - 1] << " <-> " << array[j] << std::endl;

                swap (array, j - 1, j); // Swaping element until it isn't first in array or it is <= (>=) from next element.
            }

            j--; //Current index of inserting element.
        }

        s -> compares++;
    }

} 

