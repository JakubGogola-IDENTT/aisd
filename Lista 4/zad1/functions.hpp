#include <iostream>
#include <algorithm>
#include <regex>


#include "bs_tree.hpp"
#include "rb_tree.hpp"
#include "hash_table.hpp"
#include "bloom_filter.hpp"

//Parsing arguments from command line.
data_structure* parse_args (int argc, char** argv);

std::string remove_char (std::string str);
