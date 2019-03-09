#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <memory>
#include <algorithm>

#include "priority_queue.hpp"
#include "parser.hpp"


int main() {
    clock_t start, stop;
    unsigned int starting_vertex;
    std::vector<std::shared_ptr<element>> S;

    dijkstra *d = new dijkstra(0); 
    parser *p = new parser(d);
    p->handle_input();
    starting_vertex = p->get_starting_vertex();
 
    start = clock();

    S = d->shortest_path(starting_vertex);
    std::sort(S.begin(), S.end(), comp);

    for (unsigned int i = 0; i < S.size(); i++) {
        std::cout << S.at(i)->key << " " << S.at(i)->dist << std::endl;

        double sum = 0.0;
        std::vector<std::shared_ptr<element>> path;
        std::shared_ptr<element> next = S.at(i);
        while (next->key != starting_vertex) {
            path.push_back(next);
            next = S.at(S.at(next->key - 1)->parent - 1);
        }

        path.push_back(next);

        for (unsigned int j = path.size(); j > 0; j--) {
            std::cerr << " |" << path.at(j-1)->key << " -> w: " << path.at(j-1)->dist - sum;
            sum += path.at(j-1)->dist - sum;
        }
        std::cerr << "\n";
    }
    stop = clock();

    double diff = (double) (stop - start) / CLOCKS_PER_SEC;
    std::cerr << "Time (in ms): " << diff / 1000.0 << std::endl;

    delete d;
    delete p;
}