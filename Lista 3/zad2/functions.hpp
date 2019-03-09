typedef struct stats stats;

struct stats {
    int compares;
    int swaps;
    double time;
};

bool parse_args (int argc, char** argv, char* param);
void generate_data (int* array, char param, int n);
void insertion_sort (stats* s, int* array, int p, int q);
int max (int a, int b);
int* copy_array (int* array, int length);
void print_results (stats* s, int* array, int length, int i);

void statistics ();

void swap (int* array, int i, int j);

int randomized_select (stats* s, int* array, int p, int q, int i);
int randomized_partition (stats* s, int* array, int p, int q);
int partition (stats* s, int* array, int p, int q);

int select (stats* s, int* array, int p, int q, int i);
int select_partition (stats* s, int* array, int p, int q, int pivot);
int median (stats* s, int* array, int p, int q);