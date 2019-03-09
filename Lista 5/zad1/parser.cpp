#include <iostream>
#include <sstream>
#include <cstring>
#include <vector>

#include "parser.hpp"
#include "priority_queue.hpp"

parser::parser(priority_queue *pq) {
    this->pq = pq;
}

parser::~parser() {
    //Empty destructor.
}

void parser::parse_cmd(std::string cmd) {
    std::istringstream iss;
    std::string str;
    std::vector<std::string> subs_cmd;

        int key;
        unsigned int p;

    iss.str(cmd);
    do {
        iss >> str;
        subs_cmd.push_back(str);
    } while (iss);
    iss.clear();

    std::string sub_str = subs_cmd.at(0);

    if (sub_str == "insert") {
        iss.str(subs_cmd.at(1));
        iss >> key;
        iss.clear();

        iss.str(subs_cmd.at(2));
        iss >> p;

        pq->insert(key, p);
    
    } else if (sub_str == "empty") {
        pq->empty();
    } else if (sub_str == "top") {
        pq->top();
    } else if (sub_str == "pop") {
        pq->pop();
    } else if (sub_str == "priority") {
        iss.str(subs_cmd.at(1));
        iss >> key;
        iss.clear();

        iss.str(subs_cmd.at(2));
        iss >> p;

        pq->priority(key, p);
    } else if (sub_str == "print") {
        pq->print();
    } else {
        std::cerr << "***Error: Invalid command: " << sub_str << std::endl;
    }
}

void parser::handle_input() {
    int m;
    std::string cmd;
    std::istringstream iss;
    std::getline (std::cin, cmd);
    iss.str(cmd);
    iss >> m;

    for(int i = 0; i < m; i++) {
        std::getline(std::cin, cmd);
        parse_cmd(cmd);
    }
}

