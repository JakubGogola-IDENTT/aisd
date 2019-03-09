#include <iostream>
#include <sstream>

#include "priority_queue.hpp"
#include "parser.hpp"
#include "mst.hpp"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "***Error: Invalid number of arguments!" << std::endl;
        return 0;
    }

    parser *p = new parser();
    p->parse_args(argc, argv);

    mst *mst = p->get_algorithm();
    p->handle_input(mst);

    std::vector<edge> T = mst->mst_find_mst();

    double weight = 0;
    for (unsigned int i = 0; i < T.size(); i++) {
        edge e = T.at(i);
        weight += e.weight;

        std::cout << e.u << " " << e.v << " " << e.weight << std::endl;
    }
    
    std::cout << weight << std::endl;

    delete p;
    delete mst;
    return 0;
}