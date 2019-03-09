typedef struct data data;
typedef struct stats stats;

struct data {
    std::string comparator;
    int length;
    int* array;
};

struct stats {
    int compares;
    int swaps;
    double time;
};

std::string* parse_args (int argc, char** argv);

bool compare (std::string comparator, int a, int b);

bool is_sorted (data* d);

void merge_sort (data* d, stats* s, int p, int q);
void merge (data* d, stats* s, int p, int index, int q);

void insertion_sort (data* d, stats* s);

void quick_sort (data* d, stats* s, int p, int q);
int partition (data*d, stats* s, int p, int q);
void swap (int* array, int i, int j);

void statistics (std::string* params);
void new_array (int* array, int n);
void copy_array (int* array, int* copy, int n);

void dual_pivot_quick_sort (data* d, stats* s, int left, int right);
void dual_pivot_partition (data* d, stats* s);

void radix_sort (data* d, stats* s, int base);
void counting_sort (data* d, stats* s, int base, int exp);