#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "parser.hpp"
#include "priority_queue.hpp"

parser::parser(dijkstra *d) {
    this->d = d;
}

parser::~parser() {

}

void parser::parse_args(std::string line) {
    unsigned int start, end;
    double weight;

    std::istringstream iss(line);
    std::string str;
    std::vector<std::string> subs;

    do {
        iss >> str;
        subs.push_back(str);
    } while (iss);
    iss.clear();

    iss.str(subs.at(0));
    iss >> start;
    iss.clear();

    iss.str(subs.at(1));
    iss >> end;
    iss.clear();

    iss.str(subs.at(2));
    iss >> weight;
    iss.clear();

    d->add_edge(start, end, weight);
}

void parser::handle_input() {
    unsigned int m, n;

    unsigned int start, end;
    double weight;

    std::string line;

    std::cin >> n;
    d->set_max_vertex(n);
    //d = new dijkstra(n);

    std::cin >> m;

    for (int i = 0; i < m; i++) {
        //std::getline (std::cin, line);
        //parse_args(line);
        std::cin >> start >> end >> weight;
        d->add_edge(start, end, weight);
    }

    std::cin >> starting_vertex;
}

unsigned int parser::get_starting_vertex() {
    return starting_vertex;
}