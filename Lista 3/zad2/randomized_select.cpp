#include <iostream>
#include <ctime>

#include "functions.hpp"

int randomized_select (stats* s, int* array, int p, int q, int i) {
    
    if (p == q) {
        return array[q];
    }

    int r = randomized_partition (s, array, p, q);
    int k = r - p + 1;

    if (i == k) {
        return array[r];
    } else if (i < k) {
        return randomized_select (s, array, p, r - 1, i);
    } else {
        return randomized_select (s, array, r + 1, q, i - k);
    }
}

int randomized_partition (stats* s, int* array, int p, int q) {
    srand(time(nullptr));

    int index = p + rand() % (q - p);

    s -> swaps++;
    //std::cerr << "Swap: " << array[p] << " <-> " << array[q] << std::endl;

    swap (array, p, index);

    return partition (s, array, p, q);
}

int partition (stats* s, int* array, int p, int q) {
    int pivot = array[p]; //Pivot - first element from array.
    
    int i = p; //Starting index.
    
    //Checking elements in array.
    for (int j = p + 1; j <= q; j++) {  
        s -> compares++;
        //std::cerr << "Comp: " << array[j] << " <-> " << pivot << std::endl;

        if (array[j] <= pivot) { //Checking if element on j position <= pivot.
            i++;

            s -> swaps++;
            //std::cerr << "Swap: " << array[i] << " <-> " << array[j] << std::endl;

            swap (array, i, j); //If array[j] <= pivot: swap.
        }
    }

    s-> swaps++;
    //std::cerr << "Swap: " << array[i] << " <-> " << array[p] << std::endl;

    swap (array, i, p); // Put pivot into middle part of array.
   
    return i; //Return index of pivot.
}
