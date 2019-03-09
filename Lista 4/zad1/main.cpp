#include <iostream>
#include <functional>

#include "bs_tree.hpp"
#include "rb_tree.hpp"
#include "hash_table.hpp"
#include "functions.hpp"
#include "parser.hpp"
#include "tests.hpp"
#include "bloom_filter.hpp"


int main (int argc, char** argv) {
    data_structure *ds = parse_args(argc, argv);

    time_t start, stop;

    parser *p = new parser (ds);

    start = clock();
    p->handle_input();
    stop = clock();

    stats *s = ds->get_stats();
    std::cerr << "Inserts: " << s->inserts << std::endl;
    std::cerr << "Loads: " << s->loads << std::endl;
    std::cerr << "Deletes: " << s->deletes << std::endl;
    std::cerr << "Finds: " << s->finds << std::endl;
    std::cerr << "Mins: " << s->mins << std::endl;
    std::cerr << "Maxs: " << s->maxs << std::endl;
    std::cerr << "Successors: " << s->successors << std::endl;
    std::cerr << "Inorders: " << s->inorders << std::endl;
    std::cerr << "Max size: " << ds->get_max_size() << std::endl;
    std::cerr << "End size: " << ds->get_size() << std::endl;

    std::cerr << "Total time: " << (double) (stop - start) / CLOCKS_PER_SEC << " sec" << std::endl;

    delete ds;
    return 0;
}