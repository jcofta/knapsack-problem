/*
	The main file for knapsack-problem project.

    Authors:
        jcofta
        ksniatala
*/

/* INCLUDES --------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "knapsack.h"

// Algorithms
#include "bruteforce.h"
#include "greedy.h"
#include "dynamic.h"
#include "genetic.h"

struct item_t items[NUMBER_OF_ITEMS];

int main() {

    struct timespec tdyn1,tdyn2;
    struct timespec tbrut1,tbrut2;
    struct timespec tgen1,tgen2;
    struct timespec tgred1,tgred2;
    int sum_bf=0, subset_bf=0;
    int sum_dyn = 0, subset_dyn = 0;
    int sum_gen = 0, subset_gen = 0;
    int sum_gred=0, subset_gred=0;

	srand(time(0));

    //Generate and load array of items
    if ( load_items(NUMBER_OF_ITEMS, items) < 0) {
        printf("Generate items\n");
        generate_items(MAX_SIZE, MAX_VALUE, NUMBER_OF_ITEMS);
        printf("Load items\n");
        load_items(NUMBER_OF_ITEMS, items);
    } else {
        printf("Loaded items from file\n");
    }

    //Initial info
    print_items(NUMBER_OF_ITEMS, items);
    printf("Size of bag: %d\n", SIZE_OF_BAG);
    printf("Number of items: %d\n", NUMBER_OF_ITEMS);

    /* -- Algorithms --*/
    // Dynamic Algorithm
    printf("\nDynamic algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tdyn1);
    dynamic(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_dyn, &subset_dyn);
    clock_gettime(CLOCK_MONOTONIC, &tdyn2);

    double tdyn = 1000.0*tdyn2.tv_sec + 1e-6*tdyn2.tv_nsec
	                       - (1000.0*tdyn1.tv_sec + 1e-6*tdyn1.tv_nsec);

    double tdyn3 = (tdyn2.tv_sec - tdyn1.tv_sec) + (double) (tdyn2.tv_nsec - tdyn1.tv_nsec) * 1e-9;

    printf("Dynamic time: %.6f ms, %.6f s\n", tdyn, tdyn3);

    printf("Sum dynamic: %d\n", sum_dyn);
    printf("Subset dynamic: %d\n", subset_dyn);
    print_subset(NUMBER_OF_ITEMS,subset_dyn);

    // BruteForce Algorithm
    printf("\nBruteForce algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tbrut1);
    bruteforce(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_bf, &subset_bf);
    clock_gettime(CLOCK_MONOTONIC, &tbrut2);

    double tbrut = 1000.0*tbrut2.tv_sec + 1e-6*tbrut2.tv_nsec
	                       - (1000.0*tbrut1.tv_sec + 1e-6*tbrut1.tv_nsec);

    double tbrut3 = (tbrut2.tv_sec - tbrut1.tv_sec) + (double) (tbrut2.tv_nsec - tbrut1.tv_nsec) * 1e-9;

    printf("Brut time: %.6f ms, %.6f s\n", tbrut, tbrut3);

    printf("Sum bruteforce: %d\n", sum_bf);
    //printf("Subset brutforce: %d\n", subset_bf);
    print_subset(NUMBER_OF_ITEMS,subset_bf);

    // Genetic Algorithm
    printf("\nGenetic algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tgen1);
    genetic(NUMBER_OF_ITEMS, items, &sum_gen, &subset_gen);
    clock_gettime(CLOCK_MONOTONIC, &tgen2);

    double tgen = 1000.0*tgen2.tv_sec + 1e-6*tgen2.tv_nsec
	                       - (1000.0*tgen1.tv_sec + 1e-6*tgen1.tv_nsec);
    double tgen3 = (tgen2.tv_sec - tgen1.tv_sec) + (double) (tgen2.tv_nsec - tgen1.tv_nsec) * 1e-9;

    printf("Genetic time: %.6f ms, %.6f s\n", tgen, tgen3);

    printf("Sum genetic: %d\n", sum_gen);
    print_subset(NUMBER_OF_ITEMS,subset_gen);

    // Greedy Algorithm
    printf("\nGreedy algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tgred1);
    greedy(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_gred, &subset_gred);
    clock_gettime(CLOCK_MONOTONIC, &tgred2);

    double tgred = 1000.0*tgred2.tv_sec + 1e-6*tgred2.tv_nsec
	                       - (1000.0*tgred1.tv_sec + 1e-6*tgred1.tv_nsec);
    double tgred3 = (tgred2.tv_sec - tgred1.tv_sec) + (double) (tgred2.tv_nsec - tgred1.tv_nsec) * 1e-9;

    printf("Greedy time: %.6f ms, %.6f s\n", tgred, tgred3);
    printf("Sum genetic: %d\n", sum_gred);
    print_subset(NUMBER_OF_ITEMS,subset_gred);

    return 0;
}
