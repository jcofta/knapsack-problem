#!/bin/bash

#stala poj plecaka i stala ilosc elem,
#zmienna wielkosc populacji

rm time.txt
for i in {10..1000..10}
do
    make clean && make NITEM=20 SBAG=50 POP=$i && ./knapsack
done

