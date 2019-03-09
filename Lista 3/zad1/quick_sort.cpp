#include <iostream>
#include <cstdbool>
#include "ex1.hpp"

//Quick sort procedure.
void quick_sort (data* d, stats* s, int p, int q) {
    //Helping index.
    int i;

    //When p < q, we partited every half of array.
    if (p < q) {
        i = partition(d, s, p, q); //Make partition.
        quick_sort (d, s, p, i - 1); //Recursive call on left half of array.
        quick_sort (d, s, i + 1, q); //Recursive call on right half of array.  
    }
}

//Swap two elements in array.
void swap (int* array, int i, int j) {
    int tmp = array[i]; //Remember first element.
    array[i] = array[j]; //Swap.
    array[j] = tmp; 
}


//Make partition.
int partition (data* d, stats* s, int p, int q) {
    int* array = d -> array; //Pointer to array.
    int pivot = array[p]; //Pivot - first element from array.
    std::string comparator = d -> comparator; //Comparator: <= or >=.

    int i = p; //Starting index.
    
    //Checking elements in array.
    for (int j = p + 1; j <= q; j++) {
 
        s -> compares++;
        if (compare (comparator, array[j], pivot)) { //Checking if element on j position <= (or >=) pivot.
            i++;

            s -> swaps++;
            swap (array, i, j); //When array[j] <= (>=) pivot, swap.
        }
    }

    s-> swaps++;
    swap (array, i, p); // Put pivot on middle of array.
   

    return i; //Return index of pivot.
}
