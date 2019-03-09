#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

#include "functions.hpp"

void statistics () {
    int n = 10;
    int k;
    int i;
    char param = 'r';

    stats* s;
    int* array;
    int* copy;
    clock_t start, stop;

    std::ofstream fout;

    fout.open("statistics.csv");
    fout << "n;k;swaps_select;compares_select;time_select;swaps_rselect;compares_rselect;time_rselect\n";

    //int j = 1;
    while (n < 5000) {
        //n = (int) pow(2, j % 2) * 5 * pow(10, floor ((double) j / 2));
        std::cout << "Testing: " << n << std::endl;
        array = new int[n];
        generate_data (array, param, n);

        s = new stats;
        s -> compares = 0;
        s -> swaps = 0;
        s -> time = 0;

        copy = copy_array (array, n);
        k = 1 + rand () % n;

        fout << n << ";" << k <<";";

        start = clock();
        i = select (s, array, 0, n - 1, k);
        stop = clock();

        s -> time = (double) (stop - start) / CLOCKS_PER_SEC;

        fout << s -> swaps << ";" << s -> compares << ";" << s -> time << ";";

        delete [] array;
        array = copy;

        s -> compares = 0;
        s -> swaps = 0;
        s -> time = 0;

        start = clock();
        i = randomized_select (s, array, 0, n - 1, k);
        stop = clock();

        s -> time = (double) (stop - start) / CLOCKS_PER_SEC;

        fout << s -> swaps << ";" << s -> compares << ";" << s -> time << ";\n";

        delete [] array;
        delete s;

        //j++;
        n += 100;
    }

    fout.close();
}