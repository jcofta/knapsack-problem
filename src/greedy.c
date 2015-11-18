/*
    Greedy Algorithm implementation
*/

#include "knapsack.h"
#include "greedy.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void add_to_list(struct to_sort *frac);

void greedy(int n, int w, struct item *tab, int *suma, int *subset) {

   head = NULL;
   struct to_sort *st = malloc(n*sizeof(struct to_sort));
   int i,j,k,m;

   float x;

   //Liczenie stosunków
   for(i=0; i<n; i++) {
       st[i].f = ((float)tab[i].value)/tab[i].size;
       st[i].id = i;
       st[i].size = tab[i].size;
       st[i].value = tab[i].value;
      // printf("%f ",st[i]);
   }

   //Sortowanie
   for(i=0;i<n;i++)
   {
       add_to_list(&st[i]);
   }

//    wypisz_liste(head);

//    for(i=0; i<n; i++) {
//        printf("%f ", st[i]);
//    }
//    printf("\n");

   int size = 0;
   int value = 0;

   i = n-1;
   while(size < w && i>=0)
   {
       if(tab[head->id].size + size <= w) {
           size += tab[head->id].size;
           value += tab[head->id].value;
           add_result(head->id, subset);

       }
       head=head->Next;
       i--;
   }

   *suma = value;

}

void add_to_list( struct to_sort *frac)
{
  struct to_sort *tmp, *prev, *next;
  tmp=malloc(sizeof(struct to_sort));

  tmp->f=frac->f;
  tmp->id=frac->id;
  tmp->size=frac->size;
  tmp->value=frac->value;
  tmp->Next=NULL;

  if(!head)
  {
     head=tmp;
  }else
  {
     prev=NULL;
     next=head;

     while(next && (next->f>(frac->f)))
        {
           prev = next;
           next = next->Next;
        }

     if(!next)
        {
           prev->Next = tmp;
        }
     else{
        if(prev)
        {
               tmp->Next = prev->Next;
               prev->Next = tmp;
        } else
        {
               tmp->Next = head;
               head = tmp;
        }
       }
  }

}