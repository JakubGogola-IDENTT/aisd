struct stats {
    int compares;
    double time;
};

typedef struct stats stats;

int binary_search (stats* s, int* array, int p, int q, int v);
void statistics ();
bool is_sorted (int* array, int length);