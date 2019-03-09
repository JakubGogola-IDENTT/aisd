#pragma once
#include <iostream>
#include <sstream>

#include "priority_queue.hpp"
#include "dijsktra.hpp"

class parser {
private:
    dijkstra *d;
    void parse_args(std::string line);
    unsigned int starting_vertex;

public:
    parser(dijkstra *d);
    ~parser();

    void handle_input();
    unsigned int get_starting_vertex();
};