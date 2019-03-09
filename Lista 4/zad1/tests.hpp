#include <iostream>

std::string gen_file(std::string file_name, int num_to_find);
void test_switch_point();
void test_oprations_time();
void test_operations_num();
double compute_time (time_t start, time_t stop);

double compute_avg (std::vector<double> *v);

int get_min (std::vector<int> *v);

int get_max (std::vector<int> *v);
int get_avg (std::vector<int> *v);