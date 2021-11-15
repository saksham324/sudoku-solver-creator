# Makefile for the sudoku game
#
# Authors: The C Crew - Brody T., Saksham A., Sayuri M. 
# CS50 Fall 2021, Final Project 
# November 13th, 2021

C = common
R = creator
S = solver

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(DEBUG) -I$C -I$R -I$S
PROG = sudoku sudokuTopping fuzztest
OBJS = sudoku.o $S/solver.o $R/creator.o $C/common.o
OBJSTOPPING = sudokuTopping.o
OBJSTEST = fuzztest.o

MAKE = make
.PHONY: all clean test valgrind

all: 
	$(MAKE) -C $C
	$(MAKE) -C $R
	$(MAKE) -C $S
	$(MAKE) $(PROG)

sudoku: $C/common.h $R/creator.h $S/solver.h $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $C/common.h $R/creator.h $S/solver.h -o $@ -lm

fuzztest: $S/solver.o $R/creator.o $C/common.o $(OBJSTEST)
	$(CC) $(CFLAGS) $(OBJSTEST) $S/solver.o $R/creator.o $C/common.o -o $@ -lm

sudokuTopping: $S/solver.o $R/creator.o $C/common.o $(OBJSTOPPING)
	$(CC) $(CFLAGS) $(OBJSTOPPING) $S/solver.o $R/creator.o $C/common.o -o $@ -lm

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
	$(MAKE) -C $C clean
	$(MAKE) -C $R clean
	$(MAKE) -C $S clean

test:
	bash -v testing.sh

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) create easy 
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) create hard 
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) solve < test.out