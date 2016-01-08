#pragma once

/* DEFINITIONS ------------------ */
#ifndef SIZE_OF_BAG
#define SIZE_OF_BAG 50
#endif

#ifndef NUMBER_OF_ITEMS
#define NUMBER_OF_ITEMS 10
#endif

#define MAX_SIZE 20
#define MAX_VALUE 15

#define ITEMS_FILE "items.db"

//#define DEBUG

//sturcture to store info about single item
struct item_t {
   int size;
   int value;
};

//generate items and save them to a file
void generate_items(int max_s, int max_v, int n);
//wczytuje do pliku
int load_items(int n, struct item_t *tab);

void malloc_array(int*** arr, int n, int m);

void print_matrix(int *matrix[], int n, int max);

//wyswietla na ekranie elementy z tab (rozmiar i waga)
void print_items(int n, struct item_t *tab) ;

//wypisuje elementy oznaczone na bitach w subset jako 1
void print_subset(int n, int subset);

//Add chosen item to subset
void add_result(int id, int *subset);

////wykonuje algorytm optymalny
//void dynamic(int n, int max, struct item *tab, int *suma, int *subset);
////wykonuje algorytm zachlanny
//void greedy(int n, int max, struct item *tab, int *suma, int *subset);
//
