# Variables
M = ../common

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I $M
PROG = solver
OBJS = solver.o
LLIBS = $M/common.a

# Rules
solver.o: solver.c $M/common.h
	$(CC) $(CFLAGS) -c -o $@ solver.c

.PHONY: clean 

clean: 
	rm -f *~ *.o *.dSYM