#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "knapsack.h"

//struct to_sort *head =NULL;

//generate items and save them to file
void generate_items(int max_s, int max_v, int n)
{
   int i,v,s;
   FILE *out_f = fopen(ITEMS_FILE,"w");
   srand(time(NULL));
   for(i=0;i<n;i++)
   {
      s=rand()%max_s+1;
      v=rand()%max_v+1;

      fprintf(out_f, "%d\t%d\n", s, v);
   }
   fclose(out_f);
}

//load items from file
int load_items(int n, struct item_t *tab){
    FILE *in_f = fopen(ITEMS_FILE,"r");
    if (in_f != NULL) {
        int i;
        for(i=0;i<n;i++) {
            fscanf(in_f, "%d %d", &tab[i].size, &tab[i].value);
        }
    } else {
        return -1;
    }

    fclose(in_f);
    return 0;
}

void malloc_array(int*** arr, int n, int m)
{
  int i;
  *arr = (int**)malloc(n*sizeof(int*));
  for(i=0; i<n; i++)
    (*arr)[i] = (int*)malloc(m*sizeof(int));
}

void print_items(int n, struct item_t *tab) {
   int i;
   for(i=0;i<n;i++) {
       fprintf(stdout, "%d\ts=%d\tv=%d\n", i, tab[i].size, tab[i].value);
   }
}

void print_matrix(int *matrix[], int n, int max)
{
   int i,j;
   printf("\n");

  for( i=0;i<n;i++)
  {
      printf("%2d |",i);
      for(j=0;j<max;j++)
      {
          printf("%2d ", matrix[i][j]);
      }
      printf("\n");
  }
}

void print_subset ( int n, int subset)
{
  int b;
  printf("Chosen items: ");
  for(b=0; b<n; b++) {   //przelatuje po bitach
     if((1<<b)&subset) { // jezeli dany element zostal wybrany,
        printf("%d ", b);
     }
  }
  printf("\n");
}

void add_result(int id, int *subset){
   *subset |= (1<<id);
}

//void swap(struct to_sort* l, struct to_sort* p) {
//    struct to_sort temp = *l;
//    *l = *p;
//    *p = temp;
//}
//
//

//
//
//void add_to_list2( struct to_sort *frac)
//{
//   struct to_sort *tmp, *prev, *next;
//   tmp=malloc(sizeof(struct to_sort));
//
//   tmp->f=frac->f;
//   tmp->id=frac->id;
//   tmp->size=frac->size;
//   tmp->value=frac->value;
//   tmp->Next=NULL;
//
//   if(!head)
//   {
//      head=tmp;
//   }else
//   {
//      prev=NULL;
//      next=head;
//
//      while(next && (next->size<=(frac->size)))
//         {
//            prev = next;
//            next = next->Next;
//         }
//
//      if(!next)
//         {
//            prev->Next = tmp;
//         }
//      else{
//         if(prev)
//         {
//                tmp->Next = prev->Next;
//                prev->Next = tmp;
//         } else
//         {
//                tmp->Next = head;
//                head = tmp;
//         }
//        }
//   }
//
//}
//
//
//void add_to_list3( struct to_sort *frac)
//{
//   struct to_sort *tmp, *prev, *next;
//   tmp=malloc(sizeof(struct to_sort));
//
//   tmp->f=frac->f;
//   tmp->id=frac->id;
//   tmp->size=frac->size;
//   tmp->value=frac->value;
//   tmp->Next=NULL;
//
//   if(!head)
//   {
//      head=tmp;
//   }else
//   {
//      prev=NULL;
//      next=head;
//
//      while(next && (next->value>(frac->value)))
//         {
//            prev = next;
//            next = next->Next;
//         }
//
//      if(!next)
//         {
//            prev->Next = tmp;
//         }
//      else{
//         if(prev)
//         {
//                tmp->Next = prev->Next;
//                prev->Next = tmp;
//         } else
//         {
//                tmp->Next = head;
//                head = tmp;
//         }
//        }
//   }
//
//}
//
//void wypisz_liste(struct to_sort *lista)
// {
//   struct to_sort *wsk=lista;
//   printf("-------------------------\n");
//
//    while( wsk != NULL )
//     {
//    printf("Index: %d\n", wsk->id);
//    printf("Stosunek: %f\n", wsk->f);
//    printf("\n");
//    wsk = wsk->Next;
//     }
// }
//
//void greedy(int n, int w, struct item *tab, int *suma, int *subset) {
//
//    head = NULL;
//    struct to_sort *st = malloc(n*sizeof(struct to_sort));
//    int i,j,k,m;
//
//    float x;
//
//    //Liczenie stosunków
//    for(i=0; i<n; i++) {
//        st[i].f = ((float)tab[i].value)/tab[i].size;
//        st[i].id = i;
//        st[i].size = tab[i].size;
//        st[i].value = tab[i].value;
//       // printf("%f ",st[i]);
//    }
//
//    //Sortowanie
//    for(i=0;i<n;i++)
//    {
//        add_to_list(&st[i]);
//    }
//
////    wypisz_liste(head);
//
////    for(i=0; i<n; i++) {
////        printf("%f ", st[i]);
////    }
////    printf("\n");
//
//    int size = 0;
//    int value = 0;
//
//    i = n-1;
//    while(size < w && i>=0)
//    {
//        if(tab[head->id].size + size <= w) {
//            size += tab[head->id].size;
//            value += tab[head->id].value;
//            add_result(head->id, subset);
//
//        }
//        head=head->Next;
//        i--;
//    }
//
//    *suma = value;
//
//}
//
////kryterium rozmiaru, jak najwieksza ilość elementów
//void greedy2(int n, int w, struct item *tab, int *suma, int *subset) {
//
//    head = NULL;
//    struct to_sort *st = malloc(n*sizeof(struct to_sort));
//    int i,j,k,m;
//
//    float x;
//
//    //Liczenie stosunków
//    for(i=0; i<n; i++) {
//        st[i].f = ((float)tab[i].value)/tab[i].size;
//        st[i].id = i;
//        st[i].size = tab[i].size;
//        st[i].value = tab[i].value;
//       // printf("%f ",st[i]);
//    }
//
//    //Sortowanie
//    for(i=0;i<n;i++)
//    {
//        add_to_list2(&st[i]);
//    }
//
////    wypisz_liste(head);
//
////    for(i=0; i<n; i++) {
////        printf("%f ", st[i]);
////    }
////    printf("\n");
//
//    int size = 0;
//    int value = 0;
//
//    i = n-1;
//    while(size < w && i>=0)
//    {
//        if(tab[head->id].size + size <= w) {
//            size += tab[head->id].size;
//            value += tab[head->id].value;
//            add_result(head->id, subset);
////            printf("Dodaje %d : %d\n", tab[head->id].value, head->id);
//        }
//        head=head->Next;
//        i--;
//    }
//
//    *suma = value;
//
//}
//
////kryterium wartosci, jak najwieksza wartosc
//void greedy3(int n, int w, struct item *tab, int *suma, int *subset) {
//
//    head = NULL;
//    struct to_sort *st = malloc(n*sizeof(struct to_sort));
//    int i,j,k,m;
//
//    float x;
//
//    //Liczenie stosunków
//    for(i=0; i<n; i++) {
//        st[i].f = ((float)tab[i].value)/tab[i].size;
//        st[i].id = i;
//        st[i].size = tab[i].size;
//        st[i].value = tab[i].value;
//       // printf("%f ",st[i]);
//    }
//
//    //Sortowanie
//    for(i=0;i<n;i++)
//    {
//        add_to_list3(&st[i]);
//    }
//
////    wypisz_liste(head);
//
////    for(i=0; i<n; i++) {
////        printf("%f ", st[i]);
////    }
////    printf("\n");
//
//    int size = 0;
//    int value = 0;
//
//    i = n-1;
//    while(size < w && i>=0)
//    {
//        if(tab[head->id].size + size <= w) {
//            size += tab[head->id].size;
//            value += tab[head->id].value;
//            add_result(head->id, subset);
////            printf("Dodaje %d : %d\n", tab[head->id].value, head->id);
//        }
//        head=head->Next;
//        i--;
//    }
//
//    *suma = value;
//
//}
