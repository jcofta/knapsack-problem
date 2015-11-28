/*
    Brute Force Algorithm implementation
*/
    
#include "knapsack.h"
#include "bruteforce.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void bruteforce(int n, int max, struct item_t *tab, int *suma, int *subset)
{
  int i, b, smax=-1;
  for(i=0; i<(1<<n) ; i++)
  { 
    int sum = 0;
     int size = 0;

     for(b=0; b<n; b++) {
        if((i>>b)&1) {
           sum += tab[b].value;
           size += tab[b].size;
        }
     }
     if ((sum>smax) && (size<=max)) {
           smax=sum;
           *subset=i;}
     else {
     }
  }
  *suma=smax;
}
