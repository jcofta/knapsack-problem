/*
	The main file for knapsack-problem project.
*/

/* INCLUDES --------------------- */
#include <stdio.h>
#include "knapsack.h"

// ALgorithms
//TODO
//#include "bruteforce.h"
//#include "greedy.h"
//#include "dynamic.h"
#include "genetic.h"

/* DEFINITIONS ------------------ */
#define MAX_SIZE 50
#define MAX_VALUE 100

struct item_t items[NUMBER_OF_ITEMS];

int main() {
    //Generate and load array of items
    printf("Generate Items\n");
    generate_items(MAX_SIZE, MAX_VALUE, NUMBER_OF_ITEMS);
    printf("Load items\n");
    load_items(NUMBER_OF_ITEMS, items);

    print_items(NUMBER_OF_ITEMS, items);

    printf("Genetic algorithm\n");
    genetic(NUMBER_OF_ITEMS, items);

    return 0;
}
