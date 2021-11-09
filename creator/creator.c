#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../common/common.h"


static int getRandNumber(int min, int max) {
  return (rand() % (max - min + 1) + min);
}

bool removeNumbers(sudoku_board *b, int n) {
  int numRemoved = 0; // set numbers removed to 0 initially 
  int numIterations = 0; // set numIterations to 0 initially
  long int maxChecks = 20000; 

  int row = getRandNumber(0, b->size - 1); // generate random row number
  int col = getRandNumber(0, b->size - 1); // generate random col number

  while (numRemoved < n) {
    if (numIterations++ > maxChecks) return false; // surpassed maxIterations allowed

    if (!(b->boardArray[row][col])) continue;   // skip if it is already removed

    int num = b->boardArray[row][col]; // save value removed in case removal is invalid
    b->boardArray[row][col] = 0; // remove the value in the board
    
    if (isUnique(0, 0, b, 0) == 1) {
      numRemoved++; 
    } else {
      b->boardArray[row][col] = num; 
    }
  }
  return true; 

}

