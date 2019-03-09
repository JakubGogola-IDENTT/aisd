#include <iostream>
#include <ctime>

#include "ex1.hpp"

void dual_pivot_quick_sort (data* d, stats* s, int left, int right){
    int* array = d -> array;
    std::string comparator = d -> comparator;
    int p, q; //Pivots.
    int i, j, k; //Indexes.
    int x; //Difference of 'small' and 'large' elements.
    int temp;
    int index_1, index_2; //Indexes of random pivots.
  
    if (left >= right) {
        return;
    }

    srand (time (nullptr));

    for (int i = 0; i < 5; i++) {
        index_1 = left + rand() % (right - left);
        index_2 = left + rand() % (right - left);

        if (array[index_1] != array[index_2]) {
            break;
        }
    }
 
    if (array[index_1] != array[index_2]) {
        if (compare (comparator, array[index_1], array[index_2])) {
            swap (array, index_1, right);
            p = array[right];
            swap (array, index_2, left);
            q = array[left];
            s -> swaps += 2;
        } else {
            swap (array, index_2, right);
            p = array[right];
            swap (array, index_1, left);
            q = array[left];

            s -> swaps += 2;
        }
    } else {
        if (compare (comparator,array[right], array[left])) {
            p = array[right];
            q = array[left];

        } else {
            p = array[left];
            q = array[right];
        }
    }

    i = left + 1; //It 
    j = i;
    k = right - 1;

    x = 0;

    while (j <= k) {
        if (x >= 0) { // There is more smaller than larger elements.
            s -> compares++;
            if (compare (comparator, array[j], p)) { //If array[j] is smaller than smaller pivot:
                s -> swaps++;
                swap (array, i, j); //Put it to smaller elements.
                
                i++;
                j++;
                x++;
            } else {
                s -> compares++;
                if (compare (comparator, array[j], q)) { //Else check if it is smaller than larger pivot.
                    j++; //Nothing changed if it is smaller - we put it in the middle.
                } else {
                    s -> swaps++; // Else we put it to the larger elements.
                    swap (array, j, k); 

                    k--;
                    x--;
                }
            }
        } else { //There is more larger than smaller elements.
            s -> compares++;
            if (!compare (comparator, array[k], q)) { //If array[j] is larger than larger pivot nothing changed.
                k--;
                x--;
            } else {
                s -> compares++;
                if (compare (comparator, array[k], p)) { //Else if it is smaller than smaller pivot swap k with j and j with i.
                    temp = array[k];
                    array[k] = array[j];
                    array[j] = array[i];
                    array[i] = temp;
                    i++;
                    x++;
                } else { // When it is medium put it in the medium part.
                    s -> swaps++;
                    swap (array, j, k);
                }
                j++;
            }
        }
    } 
    array[left] = array[i - 1];
    array[i - 1] = p;
    array[right] = array[k + 1];
    array[k + 1] = q;

    dual_pivot_quick_sort (d, s, left, i - 2); 
    dual_pivot_quick_sort (d, s, i, k);
    dual_pivot_quick_sort (d, s, k + 2, right);
}
