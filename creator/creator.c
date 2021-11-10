#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../common/common.h"
#include "../solver/solver.h"


static int getRandNumber(int min, int max) {
  return (rand() % (max - min + 1) + min);
}

/********* removeNumbers *************/ 
/* 
 * Removes n numbers from the filled board, and checks if board is still unique. 
 *  
 * Caller provides : 
 *  A valid, filled sudoku_board_t and a number `n` to remove. 
 * Function guarantees : 
 *  Incomplete board with a unique solution 
 * Return: 
 *  True if successful, False if solution non-unique 
 * Caller is responsible for : 
 *  Nothing
 * 
*/
bool removeNumbers(sudoku_board_t *b, int n) {
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

// function to generate random 3x3 grids which are valid 
void generateRandomGrid(sudoku_board_t *b, int rowStart, int colStart) {
  if (rowStart < 0 || colStart < 0 || b->size < rowStart + 3 || b->size < colStart + 3) return; // make sure rowStart and colStart values are valid
  for (int i = rowStart; i < rowStart + 3; i++) { 
    for (int j = colStart; i < colStart + 3; j++) {
      int num = getRandNumber(1, 9); // generate random number to be added
      if(!(isValid(i, j, b, num))) { // check if it is valid
        b->boardArray[i][j] = num; // if valid add it 
      }
    }
  }
  return; 
}

/************ fillBoard ************/
/*
 * Takes a sudoku_board_t as input and fills it completely using the solver functionality
 * 
 * Caller provides:
 *  An empty sudoku_board_t
 * Function guarantees:
 *  A board with one solution
 * Caller is responsible for:
 *  Nothing
 */
bool fillBoard(sudoku_board_t *b) {
  // fill diagonal 3x3 grids first, then leverage solveBoard to return a solvedBoard
  generateRandomGrid(b, 0, 0); 
  generateRandomGrid(b, 3, 3); 
  generateRandomGrid(b, 6, 6); 

  return solveBoard(b); 
}

