# Variables
M = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I $M
PROG = creator
OBJS = creator.o
LLIBS = $M/common.a

# Rules
creator.o: creator.c $M/common.h ../solver/solver.h
	$(CC) $(CFLAGS) -c -o $@ creator.c

.PHONY: clean 

clean: 
	rm -f *~ *.o *.dSYM