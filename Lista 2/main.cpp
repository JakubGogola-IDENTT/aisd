#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include "ex1.hpp"

int main (int argc, char* argv[]) {

    /*if (argc != 8) {
        std::cout << "Invalid number of arguments!" << std::endl;
        return 0;
    }*/

    std::string* params; //Array with type of sorting and type of comparator.
    std::string type; //Type of sorting algorithm.
    data* d; //Struct with array and size of it.
    stats* s; //struct withs statistics of sorting.
    clock_t start, stop; //Variables to measure time.
    
    params = parse_args (argc, argv);

    if (argc == 8) {
        statistics (params);
        return 0;
    }

    int n; //Size of an array.
    int* array; //Array with numbers to sort.

    //Read size of array from stdin.
    std::cin >> n;

    array = new int[n];

    for (int i = 0; i < n; i++) {
        //Read elements of array.
        std::cin >> array[i];
    }

    d = new data;
    d -> length = n;
    d -> array = array;
    d -> comparator = params[0];

    s = new stats;
    s -> compares = 0;
    s -> swaps = 0;
    s -> time = 0;

    type = params[1];

    if (type.compare ("insert") == 0) {
        start = clock();
        insertion_sort (d, s);
        stop = clock();
    } else if (type.compare("merge") == 0) {
        start = clock();
        merge_sort (d, s, 0, n - 1);
        stop = clock();
    } else if (type.compare("quick") == 0) {
        start = clock();    
        quick_sort (d, s, 0, n - 1);
        stop = clock();
    } else if (type.compare("dual") == 0) {
        start = clock();
        dual_pivot_quick_sort (d, s, 0, n - 1);
        stop = clock();
    } else {
        std::cout << "Invalid name of algorithm!" << std::endl;
    }

    s -> time = (double) (stop - start) / CLOCKS_PER_SEC;
    
    std::cout << "Num of compares: " << s ->compares << std::endl;
    std::cout << "Num of swaps: " << s -> swaps << std::endl;
    std::cout << "Time of execution: " << s -> time << " sec" << std::endl;

    if (is_sorted (d)) {
       for (int i = 0;  i < n; i++) {
            std::cout << array[i] << std::endl;
        }
    } else {
        std::cout << "Array is not correctly sorted!" << std::endl;
    }

    delete d;
    delete s;
    delete [] array;
    delete [] params;
    return 0;
}
