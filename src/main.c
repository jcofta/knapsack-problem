/*
	The main file for knapsack-problem project.
*/

/* INCLUDES --------------------- */
#include <stdio.h>
#include "knapsack.h"

// ALgorithms
//TODO
#include "bruteforce.h"
//#include "greedy.h"
#include "dynamic.h"
#include "genetic.h"

struct item_t items[NUMBER_OF_ITEMS];

int main() {
    int sum_bf=0, subset_bf=0;
    int sum_dyn = 0, subset_dyn = 0;

    //Generate and load array of items
    printf("Generate Items\n");
    generate_items(MAX_SIZE, MAX_VALUE, NUMBER_OF_ITEMS);
    printf("Load items\n");
    load_items(NUMBER_OF_ITEMS, items);
    
    //Initial info
    print_items(NUMBER_OF_ITEMS, items);
    printf("Size of bag: %d\n", SIZE_OF_BAG);
    printf("Number of items: %d\n", NUMBER_OF_ITEMS);

    //Do the algorithms
    // Dynamic Algorithm
    printf("Dynamic algorithm\n");
    dynamic(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_dyn, &subset_dyn);
    printf("Sum dynamic: %d\n", sum_dyn);
    print_subset(NUMBER_OF_ITEMS,subset_dyn);

    // BruteForce Algorithm
    printf("BruteForce algorithm\n");
    bruteforce(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_bf, &subset_bf);
    printf("Sum bruteforce: %d\n", sum_bf);
    print_subset(NUMBER_OF_ITEMS,subset_bf);


    // Genetic Algorithm
    printf("Genetic algorithm\n");
    genetic(NUMBER_OF_ITEMS, items);

    return 0;
}