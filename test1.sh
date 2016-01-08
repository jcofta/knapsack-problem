#!/bin/bash

#zmienna ilosc elementow ze stalym rozmiarem plecaka

rm time.txt
for i in {5..25}
do
    make clean && make NITEM=$i SBAG=50 POP=100 && ./knapsack
done

