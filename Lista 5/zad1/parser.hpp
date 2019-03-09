#pragma once
#include <iostream>
#include <sstream>

#include "priority_queue.hpp"

class parser {
private:
    priority_queue *pq;
    void parse_cmd(std::string cmd);

public:
    parser(priority_queue *pq);
    ~parser();

    void handle_input();
};