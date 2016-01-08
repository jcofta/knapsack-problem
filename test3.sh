#!/bin/bash

#stala poj plceaka i stala ilosc elem, badamy jakosc otrzymanych rozwiazan alg gred i genetic

rm time.txt
for i in {1..100}
do
    make clean && make NITEM=20 SBAG=50 POP=100 && ./knapsack
    sleep 0.5
done

