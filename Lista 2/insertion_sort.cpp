#include <iostream>
#include "ex1.hpp"

//Insertion sort in increasing order order.
void insertion_sort_old (data* d, stats* s) {

    int length = d -> length; //Length of array to sort.
    int* array = d -> array; //Pointer to array to sort.
    std::string comparator = d -> comparator;

    int key, j; //Key is current value to compare, j is helping index.

    for (int i = 1; i < length; i++) {
        key = array[i]; //Key is current element from array.
        j = i - 1; //Start comparing from element next to the current element.

        while (j >= 0 && !  compare (comparator, array[j], key)) {

            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }

}

void insertion_sort (data* d, stats* s) {

    int length = d -> length; //Length of array to sort.
    int* array = d -> array; //Pointer to array to sort.
    std::string comparator = d -> comparator;

    int j; 

    //Loop for all elements in array;
    for (int i = 0; i < length; i++) {
        j = i; //Index of next. element to insert;
        
        while (j > 0 && compare (comparator, array[j], array[j - 1])) {
            std::cerr << "Compare : " << array[j] << comparator << array[j - 1] << std::endl;
            s -> compares++;

            std::cerr << "Swap : " << array[j - 1] << " <-> " << array[j] << std::endl;
            s -> swaps++;
            swap (array, j - 1, j); // Swaping element until it isn't first in array or it is <= (>=) from next element.

            j--; //Current index of inserting element.
        }

        std::cerr << "Compare : " << array[j] << comparator << array[j - 1] << std::endl; //End comparsion in while.
        s -> compares++;
    }

}