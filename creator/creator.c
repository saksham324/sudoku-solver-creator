/* creator.c - module with creator functions to be used in the Sudoku Project
*             1. Fills the sudoku board
*             2. Removes numbers from sudoku board
* Authors: The C Crew - Brody T., Saksham A., Sayuri M.
* November 5th, 2021
* CS50 Fall 2021, Final Project
*/ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../common/common.h"
#include "../solver/solver.h"
#include <time.h>



/******************** File-local functions *******************/
/* not visible outside this file */
static int getRandNumber(int min, int max);
static int generateRandomNum(sudoku_board_t *b, int row, int column);
void generateRandomGrid(sudoku_board_t *b, int rowStart, int colStart);

/********************* Global functions *********************/
/* that is, visible outside this file */

/************ fillBoard ************/
/* see creator.h for more details*/
bool 
fillBoard(sudoku_board_t *b) 
{
  // fill diagonal 3x3 grids first, then leverage solveBoard to return a solvedBoard
  generateRandomGrid(b, 0, 0); 
  generateRandomGrid(b, 3, 3); 
  generateRandomGrid(b, 6, 6); 

  return solveBoard(b); 
}

/********* removeNumbers *************/ 
/* see creator.h for more details*/
bool 
removeNumbers(sudoku_board_t *b, int n) 
{
  int numRemoved = 0; // set numbers removed to 0 initially 
  long int numIterations = 0; // set numIterations to 0 initially
  long int maxChecks = 30000; // maximum number of iterations of checks 

  while (numRemoved < n) {
    if (++numIterations > maxChecks) return false; // surpassed maxIterations allowed

    int row = getRandNumber(0, b->size - 1); // generate random row number
    int col = getRandNumber(0, b->size - 1); // generate random col number

    if (!(b->boardArray[row][col])) continue;   // skip if it is already removed

    int num = b->boardArray[row][col]; // save value removed in case removal is invalid
    b->boardArray[row][col] = 0; // remove the value in the board

    if (isUnique(0, 0, b, 0) == 1) { // if there is a unique solution 
      numRemoved += 1; // increment numbers removed
    } else {
      b->boardArray[row][col] = num; // 
    }
  }
  return true; 
}



/*
* Helper function. Generate a random number, between a min and max
*/
static int 
getRandNumber(int min, int max) 
{
  return (rand() % (max - min + 1) + min);
}

/* Helper function. Generates a number and checks if it's already in the row/column/grid
*
 * Caller provides : 
 *  A valid sudoku_board_t and a number `n` to remove. 
 * Function guarantees : 
 *  Incomplete board with a unique solution 
 * Return: 
 *  True if successful, False if solution non-unique 
 * Caller is responsible for : 
 *  Nothing
 * 
*/
static int 
generateRandomNum(sudoku_board_t *b, int row, int column) 
{
  int insert;
  while(1) {
    // Generates a random number between 1 and 9
    insert = getRandNumber(1, 9);

    // Check if that number is in the current row, column, and cell
    if (!(isValid(b, row, column, insert))) {
      return insert;
    }
  }
  return 0;
}

/*
 * Helper functioin. Generates random valid 3x3 grid with non-repeating numbers 
 * Caller provides: 
 *  A valid sudoku_board, starting row and column position 
 * Function guarantees: 
 *  Incomplete board with filled 3x3 grid with respective position 
 * Caller is responsible for 
 *  Nothing 
*/
void 
generateRandomGrid(sudoku_board_t *b, int rowStart, int colStart) 
{
  if (rowStart < 0 || colStart < 0 || b->size < rowStart + 3 || b->size < colStart + 3) return; // make sure rowStart and colStart values are valid
  for (int i = rowStart; i < rowStart + 3; i++) { 
    for (int j = colStart; j < colStart + 3; j++) {
      int num = generateRandomNum(b, i, j); // generate random number to be added
      if(!isValid(b, i, j, num)) { // check if it is valid
        b->boardArray[i][j] = num; // if valid add it 
      }
    }
  }
  return; 
}