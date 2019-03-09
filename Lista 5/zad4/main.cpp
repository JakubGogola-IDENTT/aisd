#include <iostream>
#include <sstream>

#include "priority_queue.hpp"
#include "parser.hpp"
#include "mst.hpp"

int main(int argc, char **argv) {
  
    parser *p = new parser();
    p->handle_input();
    p->run_tests();

    delete p;
    return 0;
}