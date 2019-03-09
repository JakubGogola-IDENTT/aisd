#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "functions.hpp"

void statistics () {
    std::ofstream fout;

    int* array;
    stats* s;

    int n = 1000;
    int v;

    clock_t start, stop;

    fout.open ("statistics.csv");
    fout << "n;compares;time;\n";

    srand(time(nullptr));

    while (n <= 100000) {

        array = new int[n];
        s = new stats;
        
        s -> compares = 0;
        s -> time = 0;

        for (int i = 0; i < n; i++) {
            array[i] = i + 1;
        }

        v = 1 + rand() % n;

        start = clock();
        binary_search (s, array, 0, n - 1, v);
        stop = clock();

        s -> time = (double) (stop - start) / CLOCKS_PER_SEC;

        fout << n << ";" << s -> compares << ";" << s -> time << ";\n";

        delete [] array;
        delete s;
        n += 1000;
    }

    fout.close();
}