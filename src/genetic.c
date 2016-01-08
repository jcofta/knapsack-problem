/*
    Genetic Algorithm implementation
*/

#include "knapsack.h"
#include "genetic.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifndef SIZE_OF_POPULATION
#define SIZE_OF_POPULATION  100
#endif

#define MUTATION_RATE       0.01f

extern struct item_t items[NUMBER_OF_ITEMS];

void generate_population(int** population, int n_popul, int n_items) {
    int i,j;

    for(i=0; i<n_popul; i++)
    for(j=0; j<n_items; j++) {
    	(population)[i][j] = rand()%2;
    	// printf("pop[%d][%d] = %d\n_items", i, j, population[i][j]);
    }
}

/* This function measure how 'good' is our genotype */
int result_function(int* genotype) {
    int i;
    int weight = 0;
    int value = 0;

    for(i=0; i<NUMBER_OF_ITEMS; i++) {
        if (genotype[i] == 1) {
            weight += items[i].size;
            value += items[i].value;
        }
    }

    if (weight > SIZE_OF_BAG) {
        return 1;
    } else {
        return value;
    }
}

void best_genotype(int** population, int* best_id, int* best_result, int* best_genotype) {
    int i, j, id;
    int best = 0;
    for(i=0; i<SIZE_OF_POPULATION; i++) {
        int curr_result = result_function(population[i]);
        
        if (curr_result > best) {
            best = curr_result;
            id = i;
            for(j=0; j<NUMBER_OF_ITEMS; j++) {
                best_genotype[j] = population[i][j];
            }
        }
    }

    *best_id = id;
    *best_result = best;
}

void mov_genom(int** population, int source, int dest) {
    int i;
    for(i = 0; i<NUMBER_OF_ITEMS; i++) {
        population[dest][i] = population[source][i];
    }
}

void selection(int** population) {
    int i,j;
    int sum = 0;
    int result[SIZE_OF_POPULATION];

    //Check how good is every genotype of the population
    for(i=0; i<SIZE_OF_POPULATION; i++) {
        result[i] = result_function(population[i]);
        sum += result[i];
    }

    //Define probability to be in the next population
    float prob[SIZE_OF_POPULATION];
    float curr_prob = 0;
    for(i=0; i<SIZE_OF_POPULATION; i++) {
        float prob_i = result[i]/(float)sum;
        curr_prob += prob_i;
        prob[i] = curr_prob;
    }

    //TODO Is it really needed?
    int is_chosen[SIZE_OF_POPULATION];
    for(i=0; i<SIZE_OF_POPULATION; i++)
        is_chosen[i] = 0;
    
    //Select new population
    for(i=0; i<SIZE_OF_POPULATION; i++) {
        float key = (float)(rand()%sum);
        key /= (float)sum;

        for(j=0; j<SIZE_OF_POPULATION; j++) {
            if(key <= prob[j]) {
                is_chosen[j]++;
                break;
            }
        }
    }

    //Clone chosen genotype
    int pos_last_dead = 0;
    int k;
    for(i=0; i<SIZE_OF_POPULATION; i++) {
        if (is_chosen[i] > 0) {
            for(j=0; j<is_chosen[i]; j++) {
                for(k = pos_last_dead; k < SIZE_OF_POPULATION; ++k){
                    if (is_chosen[k] == 0) {
                        pos_last_dead = k + 1;
                        mov_genom(population, i, k);    
                        break;
                    }
                }
            }
        }
    }

}

void crossover(int** population) {
    int i,j;
    

    for(i=0; i<SIZE_OF_POPULATION; i++) {
        for(j=i+1; j<SIZE_OF_POPULATION; j++) {
            int cross_probability = 20 + rand() % 31;
            if (rand()%100 <= cross_probability) {
                //Crossover operation
                #ifdef DEBUG
                printf("Cross %d %d\n", i,j);
                #endif
                int cut = rand() % (NUMBER_OF_ITEMS - 1);
                int k, temp;
                for(k=0; k<cut; k++) {
                    temp = population[i][k];
                    population[i][k] = population[j][k];
                    population[j][k] = temp;
                }
                //for( ; k<NUMBER_OF_ITEMS; k++) {
                //    temp = population[j][k];
                //    population[j][k] = population[i][k];
                //    population[i][k] = temp;                    
                //}
            }

        }
    }
}

void mutation(int** population) {
    int mod = MUTATION_RATE * NUMBER_OF_ITEMS * SIZE_OF_POPULATION;
    #ifdef DEBUG
    printf("Mutation %d\n", mod);
    #endif
    
    
    int i;
    for(i=0; i<mod; i++) {
        int x = rand()%SIZE_OF_POPULATION;
        int y = rand()%NUMBER_OF_ITEMS;

        population[x][y] = population[x][y] ? 0 : 1;
    }
}

void print_genotype(int* genotype) {
    int i;
        for(i=0; i<NUMBER_OF_ITEMS+1; i++) {
        if(genotype[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void genetic(int n, struct item_t* items, int* sum, int* subset) {
    //subfunction
    void update_best_genotype(int **population, int *id, int *sum, int *genotype) {
        int i;
        int curr_id, curr_sum, curr_genotype[NUMBER_OF_ITEMS];
        best_genotype(population, &curr_id, &curr_sum, curr_genotype);
        if(curr_sum > *sum) {
            *sum = curr_sum;
            for(i=0; i<NUMBER_OF_ITEMS; i++){
                genotype[i] = curr_genotype[i];
            }
            *id = curr_id;
        }
    }

    int** population;
    int i, counter = 40; //for the main loop
    int b_id, b_sum = 0, b_genotype[NUMBER_OF_ITEMS];

    malloc_array(&population, SIZE_OF_POPULATION, n);

    generate_population(population, SIZE_OF_POPULATION, n);
    //print_matrix(population, SIZE_OF_POPULATION, n);

    while(counter--) {
        selection(population);
        update_best_genotype(population, &b_id, &b_sum, b_genotype);
        crossover(population);
        mutation(population);
    }
    update_best_genotype(population, &b_id, &b_sum, b_genotype);

    //Return results
    *sum = b_sum;
    for(i=0; i<NUMBER_OF_ITEMS; i++) {
        if(b_genotype[i] == 1) {
            add_result(i, subset);
        }
    }
}
