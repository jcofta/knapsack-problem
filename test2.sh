#!/bin/bash

#zmienna pojemnosc plecaka ze stala iloscia elementow

rm time.txt
for i in {1..100..5}
do
    make clean
    make NITEM=20 SBAG=$i POP=100
    ./knapsack
done

