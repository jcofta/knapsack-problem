#pragma once

/* DEFINITIONS ------------------ */
#define SIZE_OF_BAG 200
#define NUMBER_OF_ITEMS 10

//#define DEBUG

//struktura do przechowywania w³aœciwoœci pojedynczego elementu
struct item_t {
   int size;  //rozmiar
   int value; //wartoœæ
};

//struct to_sort {
//    int id;
//    float f;
//    int size;
//    int value;
//    struct to_sort* Next;
//};

//generuje i zapisuje do pliku
void generate_items(int max_s, int max_v, int n);
//wczytuje do pliku
void load_items(int n, struct item_t *tab);

void malloc_array(int*** arr, int n, int m);

void print_matrix(int *matrix[], int n, int max);

//wyswietla na ekranie elementy z tab (rozmiar i waga)
void print_items(int n, struct item_t *tab) ;

////wykonuje algorytm optymalny
//void dynamic(int n, int max, struct item *tab, int *suma, int *subset);
////wykonuje algorytm zachlanny
//void greedy(int n, int max, struct item *tab, int *suma, int *subset);
//
////wypisuje elementy oznaczone na bitach w subset jako 1
//void print_subset ( int n, int subset);
