#include <iostream>
#include <cmath>
#include <climits>

#include "functions.hpp"

int select (stats* s, int* array, int p, int q, int i) {
    int n = q - p + 1; // Length of array.
    
    if (i < 1 || i > n) {
        return INT_MAX;
    }

    int parts = (int) ceil ((double) n / 5);

    /*int parts;

    if (n % 5 == 0) {
        parts = n / 5;
    } else {
        parts = n / 5 + 1;
    }*/

    int* medians = new int[parts];
    int x;

    int l = 0;
    int r = 0;

    for (int j = 0; j < n / 5; j++) {
        l = j * 5;
        r = l + 4;

        medians[j] = median (s, array, l, r);
    }

    if (n % 5 != 0) {
        l = (parts - 1) * 5;
        r = n - 1;
        medians[parts - 1] = median (s, array, l, r);
    }
    
    if (parts == 1) {
        x = medians[0];
    } else {
        x = select (s, medians, 0, parts - 1, parts / 2);
    }

    //std::cerr << "Pivot: " << x << std::endl;
    int k = select_partition (s, array, p, q, x);

    delete [] medians;
    /*
    for (int j = 0; j < n; j++) {
        std::cerr << array[j] << " ";
    }
    std::cerr << "\n";*/

    if (k - p == i - 1) {
        return array[k];
    } else if (i - 1 < k - p) {
        return select (s, array, p, k - 1, i);
    } else {
        return select (s, array, k + 1, q, i - k  + p - 1);
    }
}

int select_partition (stats* s, int* array, int p, int q, int pivot) {
    
    for (int k = p; k <= q; k++) {
        s -> compares++;
        //std::cerr << "Comp: " << array[k] << " = " << pivot << std::endl;

        if (array[k] == pivot) {
            s -> swaps++;
            //std::cerr << "Swap: " << array[p] << " <-> " << array[k] << std::endl;

            swap (array, p, k);
            break;
        }
    }
    
    int i = p; //Starting index.
    
    //Checking elements in array.
    for (int j = p + 1; j <= q; j++) {
        s -> compares++;
        //std::cerr << "Comp: " << array[j] << " <= " << pivot << std::endl;

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

int median (stats* s, int* array, int p, int q) {
    int n = q - p + 1;
    
    insertion_sort (s, array, p, q);

    if (n % 2 == 0) {
        return max (array[n / 2 - 1], array[n / 2]);
    } else {
        return array[n / 2];
    }
}