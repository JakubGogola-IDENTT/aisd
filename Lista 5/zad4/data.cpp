#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <set>
#include <vector>
#include <cmath>

double rand_num (double a, double b) {
    double r = (double) rand() / RAND_MAX;
    return a + r * (b - a);
}

void generate_data (int n) {
    std::ofstream fout; 
    std::string file_name, num;

    std::stringstream ss;
    ss << n;
    num = ss.str();
    file_name = "tsp";
    file_name += num;
    file_name += ".in";

    //Generate points;
    srand(time(nullptr));

    fout.open(file_name);
    fout << n << "\n";

    double a = 2.6787854;
    double b = 2 * a;
    double weight;

    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int j = i + 1; j <= n; j++) {
            weight = rand_num(a,b);
            fout << i << " " << j << " " << weight << "\n";
        }
    }
    fout.close();
}


int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Invalid number of arguments!" << std::endl;
        exit(1);
    }

    int num;
    std::istringstream iss(argv[1]);
    iss >> num;

    generate_data(num);
}