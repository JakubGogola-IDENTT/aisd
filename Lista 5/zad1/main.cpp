#include <iostream>
#include <sstream>
#include "priority_queue.hpp"
#include "parser.hpp"

int main() {
    priority_queue *pq = new priority_queue();
    parser *p = new parser(pq);
    p->handle_input();
    delete pq;
    return 0;
}