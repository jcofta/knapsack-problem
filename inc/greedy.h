#include "knapsack.h"

struct sort_t {
    int id;
    float f;
    int size;
    int value;
    struct sort_t* Next;
};

void greedy(int n, int w, struct item_t *tab, int *sum, int *subset);