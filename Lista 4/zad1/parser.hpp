#include <iostream>

#include "bs_tree.hpp"
#include "rb_tree.hpp"
#include "hash_table.hpp"

class parser {
private:
    data_structure *ds;
    void execute_cmd (std::string str);
    void parse_cmd (std::string cmd);

public:
    parser (data_structure *ds);
    void handle_input();
};