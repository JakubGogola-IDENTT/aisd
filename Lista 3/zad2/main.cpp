#include <iostream>
#include <cstdlib>

#include "functions.hpp"

int main (int argc, char** argv) {

    if (argc != 2) {
        std::cerr << "Invalid number of arguments!" << std::endl;
        return 0;
    }

    char param; //r - random set of values, p - random permutation 

    if (!parse_args(argc, argv, &param)) {
        std::cerr << "Invalid argument!" << std::endl;
        return 0;
    }

    if (param == 's') {
        statistics();
        return 0;
    }

    int n; //Length of data.
    int k; //Number of order statistic.
    int i; //Order statistic.
    
    int* array;
    int* copy;
    stats* s;
    clock_t start, stop;

    std::cin >> n;

    if (n < 0) {
        std::cerr << "Negative size!" << std::endl;
        return 0;
    }

    std::cin >> k;

    if (k < 1 || k > n) {
        std::cerr << "Index out of bound!" << std::endl;
        return 0;
    }

    s = new stats;

    array = new int[n];
    generate_data (array, param, n);

    s -> compares = 0;
    s -> swaps = 0;
    s -> time = 0;

    copy = copy_array(array, n);

    std::cerr << "\nSelect" << std::endl;
    start = clock();
    i = select (s, array, 0, n - 1, k);
    stop = clock();

    std::cerr << "i = " << i << std::endl;

    s -> time = (double) (stop - start) / CLOCKS_PER_SEC;
    print_results (s, array, n, k);

    delete [] array;
    array = copy;

    s -> compares = 0;
    s -> swaps = 0;
    s -> time = 0;

    std::cerr << "\nRandomized select" << std::endl;
    start = clock();
    i = randomized_select (s, array, 0, n - 1, k);
    stop = clock();

    std::cerr << "i = " << i << std::endl;

    s -> time = (double) (stop - start) / CLOCKS_PER_SEC;
    print_results (s, array, n, k);

    delete [] array;
    delete s;

    return 0;
}

void swap (int* array, int i, int j) {
    int tmp = array[i]; //Remember first element.
    array[i] = array[j]; //Swap.
    array[j] = tmp;
}

int max (int a, int b) {
    if (a <= b) {
        return b;
    } else {
        return a;
    }
}

int* copy_array (int* array, int length) {
    int* copy = new int[length];

    for (int i = 0; i < length; i++) {
        copy[i] = array[i];
    }
    
    return copy;
}

void print_results (stats* s, int* array, int length, int i) {
    for (int j = 0; j < length; j++) {
        if (j == i - 1) {
            std::cout << "[" << array[j] <<"] ";
        } else {
            std::cout << array[j] << " ";
        }
    }
    std::cout << "\n";
    std::cerr << "Swaps: " << s -> swaps << std::endl;
    std::cerr << "Compares: " << s -> compares << std::endl;
    std::cerr << "Time: " << s -> time << std::endl;
}