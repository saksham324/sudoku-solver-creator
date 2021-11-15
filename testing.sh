#!/bin/bash
# testing.sh
# usage: bash -v testing.sh

### invalid arguments

# incorrect number of arguments
./sudoku

./sudoku sovle creator yoyoyo

# invalid arguments
./sudoku badbadnotgood

./sudoku the c crew

### testing create

# create easy
./sudoku create easy

# create at level 2
./sudoku create hard

# create outside easy or hard
./sudoku create beginner

### testing solve

# test with custom visual / from a file
./sudoku solve < test.out 

# test with provided visual
./sudoku solve < test2.out 

# test from an already solved board
./sudoku solve < test3.out

# test with non-unique board
./sudoku solve < test4.out

# test with a non-existing file
./sudoku solve < test6.out

### fuzz testing

# fuzz testing solve with 250 boards
./fuzztest 250

# valgrind for memory leak check
valgrind --leak-check=full --show-leak-kinds=all ./sudoku create easy 
valgrind --leak-check=full --show-leak-kinds=all ./sudoku create hard 
valgrind --leak-check=full --show-leak-kinds=all ./sudoku solve < test.out
