#
# This is a Makefile for the program.
# Typing 'make' or 'make knapsack' will create the executable file.
#

CC = gcc
CFLAGS  = -Wall -g
INCLUDES = -Iinc
INC_MAIN = src/knapsack.o src/genetic.o src/dynamic.o src/bruteforce.o src/greedy.o

# Targets:
default: app

app: $(INC_MAIN) src/main.c
	$(CC) $(CFLAGS) $(INCLUDES) $(INC_MAIN) -g src/main.c -o knapsack

src/knapsack.o: src/knapsack.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/knapsack.c -o src/knapsack.o

src/genetic.o: src/genetic.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/genetic.c -o src/genetic.o 

src/dynamic.o: src/dynamic.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/dynamic.c -o src/dynamic.o

src/bruteforce.o: src/bruteforce.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/bruteforce.c -o src/bruteforce.o

src/greedy.o: src/greedy.c
	$(CC) $(CFLAGS) $(INCLUDES) -c src/greedy.c -o src/greedy.o

clean:
	find . -name "*.o" -exec rm {} \;
