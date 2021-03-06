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

    FILE *tmp;
    FILE *ft;

    //Check if file exist and add a header at the beginning
    if( (tmp = fopen("time.txt", "r")) != NULL ) {
        fclose(tmp);
        ft = fopen("time.txt", "a");
    } else {
        ft = fopen("time.txt", "a");
        fprintf(ft, "NITEM\tSBAG\tPOP\ttdyn\t\ttbrut\t\ttgen\t\ttgred\t\tsum_dyn\tsum_gen\tsum_gred\n");
    }

    srand(time(0));

/*
    if ( load_items(NUMBER_OF_ITEMS, items) < 0) {
        printf("Generate items\n");
        generate_items(MAX_SIZE, MAX_VALUE, NUMBER_OF_ITEMS);
        printf("Load items\n");
        load_items(NUMBER_OF_ITEMS, items);
    } else {
        printf("Loaded items from file\n");
    }
*/
    //Generate and load array of items
    generate_items(MAX_SIZE, MAX_VALUE, NUMBER_OF_ITEMS);
    load_items(NUMBER_OF_ITEMS, items);

    //Initial info
    printf("Loaded items:\n");
    print_items(NUMBER_OF_ITEMS, items);
    printf("Size of bag: %d\n", SIZE_OF_BAG);
    printf("Number of items: %d\n", NUMBER_OF_ITEMS);
    printf("Population(genetic): %d\n", SIZE_OF_POPULATION);

    /* -- Algorithms -- */
    // Dynamic Algorithm
    printf("\nDynamic algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tdyn1);
    dynamic(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_dyn, &subset_dyn);
    clock_gettime(CLOCK_MONOTONIC, &tdyn2);

    double tdyn = 1000.0*tdyn2.tv_sec + 1e-6*tdyn2.tv_nsec - (1000.0*tdyn1.tv_sec + 1e-6*tdyn1.tv_nsec);
    printf("Dynamic time: %.6f ms\n", tdyn);

    printf("Sum dynamic: %d\n", sum_dyn);
    print_subset(NUMBER_OF_ITEMS,subset_dyn);


    // BruteForce Algorithm
    printf("\nBruteForce algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tbrut1);
    bruteforce(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_bf, &subset_bf);
    clock_gettime(CLOCK_MONOTONIC, &tbrut2);

    double tbrut = 1000.0*tbrut2.tv_sec + 1e-6*tbrut2.tv_nsec - (1000.0*tbrut1.tv_sec + 1e-6*tbrut1.tv_nsec);
    printf("Brute-force time: %.6f ms\n", tbrut);

    printf("Sum bruteforce: %d\n", sum_bf);
    print_subset(NUMBER_OF_ITEMS,subset_bf);


    // Genetic Algorithm
    printf("\nGenetic algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tgen1);
    genetic(NUMBER_OF_ITEMS, items, &sum_gen, &subset_gen);
    clock_gettime(CLOCK_MONOTONIC, &tgen2);

    double tgen = 1000.0*tgen2.tv_sec + 1e-6*tgen2.tv_nsec - (1000.0*tgen1.tv_sec + 1e-6*tgen1.tv_nsec);
    printf("Genetic time: %.6f ms\n", tgen);

    printf("Sum genetic: %d\n", sum_gen);
    print_subset(NUMBER_OF_ITEMS,subset_gen);


    // Greedy Algorithm
    printf("\nGreedy algorithm\n");

    clock_gettime(CLOCK_MONOTONIC, &tgred1);
    greedy(NUMBER_OF_ITEMS, SIZE_OF_BAG, items, &sum_gred, &subset_gred);
    clock_gettime(CLOCK_MONOTONIC, &tgred2);

    double tgred = 1000.0*tgred2.tv_sec + 1e-6*tgred2.tv_nsec - (1000.0*tgred1.tv_sec + 1e-6*tgred1.tv_nsec);
    printf("Greedy time: %.6f ms\n", tgred);

    printf("Sum genetic: %d\n", sum_gred);
    print_subset(NUMBER_OF_ITEMS,subset_gred);


    //Save results into the file
    fprintf(ft, "%d\t%d\t%d\t%.6f\t%.6f\t%.6f\t%.6f\t%.d\t%.d\t%.d\n", NUMBER_OF_ITEMS, SIZE_OF_BAG, SIZE_OF_POPULATION,  tdyn, tbrut, tgen, tgred, sum_dyn, sum_gen, sum_gred);

    fclose(ft);

    return 0;
}
