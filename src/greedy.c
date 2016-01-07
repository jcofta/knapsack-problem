/*
    Greedy Algorithm implementation
*/

#include "knapsack.h"
#include "greedy.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct sort_t *head =NULL;

void add_to_list(struct sort_t *frac);

void greedy(int n, int w, struct item_t *tab, int *sum, int *subset) {

   head = NULL;
   struct sort_t *st = malloc(n*sizeof(struct sort_t));
   int i;

   //Counting ratios
   for(i=0; i<n; i++) {
      st[i].f = ((float)tab[i].value)/tab[i].size;
      st[i].id = i;
      st[i].size = tab[i].size;
      st[i].value = tab[i].value;
   }

   //Sorting
   for(i=0;i<n;i++)
   {
      add_to_list(&st[i]);
   }

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

   *sum = value;
}

void add_to_list( struct sort_t *frac)
{
  struct sort_t *tmp, *prev, *next;
  tmp=malloc(sizeof(struct sort_t));

  tmp->f=frac->f;
  tmp->id=frac->id;
  tmp->size=frac->size;
  tmp->value=frac->value;
  tmp->Next=NULL;

  if(!head) {
    head=tmp;
  }
  else {
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
    else {
      if(prev)
      {
        tmp->Next = prev->Next;
        prev->Next = tmp;
      }
      else {
        tmp->Next = head;
        head = tmp;
      }
    }
  }
}
