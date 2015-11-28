/*
    Dynamic Algorithm implementation
*/

#include "knapsack.h"
#include "dynamic.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void add_result(int id, int *subset){
   *subset |= (1<<id);
}

void dynamic(int n, int max, struct item_t *tab, int *suma, int *subset)
{
  int i,l;
  int **dynamic_tab = calloc ((n+1), sizeof(int*));
  for (i=0;i<(n+1);i++) dynamic_tab[i] = calloc((max+1),sizeof(int));

  for(i=1;i<(n+1);i++){
     for(l=1;l<(max+1);l++){
           if(l<tab[i-1].size){ dynamic_tab[i][l]=dynamic_tab[i-1][l];}
           else{
              int a1 = dynamic_tab[i-1][l-tab[i-1].size] + tab[i-1].value;
              int a2 = dynamic_tab[i-1][l];
              if(a1 > a2) dynamic_tab[i][l]=a1;
              else{ dynamic_tab[i][l]=a2;}
              //dynamic_tab[i][l] = a1>a2 ? a1 : a2; // Madry if
           }
     }
  }


   i = n;
   l = max;


  while(i) {
    if(dynamic_tab[i][l] == dynamic_tab[i-1][l]) {
    }
    else {
           add_result(i-1, subset);
           l=l-tab[i-1].size;
    }
    i--;
   }

//    print_matrix(dynamic_tab,n,max);

    *suma = dynamic_tab[n][max];
}