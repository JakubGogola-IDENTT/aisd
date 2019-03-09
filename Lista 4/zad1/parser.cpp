#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>

#include "functions.hpp"
#include "parser.hpp"
#include "data_structure.hpp"

parser::parser(data_structure *ds) {
    this->ds = ds;
}

void parser::parse_cmd (std::string key) {
    std::istringstream iss(key);
    std::vector<std::string> *subs_cmd = new std::vector<std::string>;

    std::string str;
    do {
        iss >> str;
        subs_cmd->push_back(str);
    } while (iss);

    
    if (subs_cmd->at(0).compare("insert") == 0) {
        ds->ds_insert(subs_cmd->at(1));
    } else if (subs_cmd->at(0).compare("delete") == 0) {
        ds->ds_delete(subs_cmd->at(1));
    } else if (subs_cmd->at(0).compare("load") == 0) {
        ds->ds_load(subs_cmd->at(1));
    } else if (subs_cmd->at(0).compare("insert") == 0) {
        ds->ds_insert(subs_cmd->at(1));
    } else if (subs_cmd->at(0).compare("find") == 0) {
        ds->ds_search(subs_cmd->at(1));
    } else if (subs_cmd->at(0).compare("min") == 0) {
        ds->ds_minimum();
    } else if (subs_cmd->at(0).compare("max") == 0) {
        ds->ds_maximum();
    } else if (subs_cmd->at(0).compare("successor") == 0) {
        ds->ds_succssor(subs_cmd->at(1));
    } else if (subs_cmd->at(0).compare("inorder") == 0) {
        ds->ds_inorder();
    } else {
        std::cerr << "*** Warning: Invalid command!" << std::endl;
        std::cout << "\n";
    }

    
    delete subs_cmd;
}

void parser::handle_input() {
    int cmd_num; //Number of comands.
    std::string line; //Line from input.
    std::istringstream iss;

    std::getline (std::cin, line);

    iss.str(line);
    iss >> cmd_num;

    for (int i = 0; i < cmd_num; i++) {
        std::getline(std::cin, line);
        parse_cmd (line);
    }

}