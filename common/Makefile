# Makefile for the common library of the Sudoku Project
#   Builds and compiles all the utility functions into a library called 'common.a'
#
# Author: Sayuri Tais Miyamoto Magnabosco
# November 5th, 2021
# CS50 Fall 2021, Final Project


# object files, and the target library
OBJS = common.o
LIB = common.a

# (and run `make clean; make` whenever you change this)
FLAGS = -DMEMTEST  # -DNOSLEEP

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(FLAGS) 
CC = gcc
MAKE = make

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
common.o: common.h

.PHONY: clean sourcelist

# list all the sources and docs in this directory.
# (this rule is used only by the Professor in preparing the starter kit)
sourcelist: Makefile *.md *.c *.h
	@echo $^

# clean up after our compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o