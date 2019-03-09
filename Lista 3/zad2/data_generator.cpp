#include <iostream>
#include <ctime>
#include <random>
#include <algorithm>
#include <iterator>

#include "functions.hpp"

void generate_data (int* array, char param, int n) {
    srand(time(nullptr));

    if (param == 'r') { //Put random values into array.
        for (int i = 0; i < n; i++) {
            array[i] = 1 + rand() % 1000; 
        }
    } else { //Param is 'p' - permutation of set [n].
        for (int i = 0; i < n; i++) {
            array[i] = i + 1;
        }

        int num_of_shuffles = rand() % 10; //Number of shuffles.    
        std::random_device rd;
        std::mt19937 g(rd());

        for (int i = 0; i < num_of_shuffles; i++) {
            shuffle(&array[0], &array[n - 1], g);
        }
    }
}