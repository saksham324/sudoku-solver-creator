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
#include <dirent.h>
#include <ctype.h>
#include "../common/common.h"
#include "../creator/creator.h"

const int BOARD_SIZE = 9; 

/******************** File-local functions *******************/
/* not visible outside this file */
bool solveBoardHelper(sudoku_board_t* b, int pos);


/********************* Global functions *********************/
/* that is, visible outside this file */

/************ solveBoard ************/
/* see solver.h for more details*/
int 
solveBoard(sudoku_board_t *board)
{
    int solutions = isUnique(0, 0, board, 0); 
    solveBoardHelper(board, 0); 
    return solutions; 
}

/************ loadBoard ************/
/* see solver.h for more details*/
sudoku_board_t *loadBoard(FILE *fp) 
{
  if (!fp) return NULL;

  sudoku_board_t *lBoard = generateEmptyBoard(BOARD_SIZE); // generate Empty Board to be filled out 
  if (!lBoard) return NULL;
  
  // make sure number of rows is valid, iterate through each row
  int rowCount = 0;
  while (rowCount < lBoard->size) {

    // Iterate through each column
    int colCount = 0;
    while (colCount < lBoard->size) {

      // Get each character from fp, check if char is a digit, if yes insert
      char ch = fgetc(fp);
     
      if (!isdigit(ch)) { 
          continue; 
          }

      // Convert char to int value (ASCII)
      if (isdigit(ch)) lBoard->boardArray[rowCount][colCount] = (int)ch - 48;
      if (isdigit(ch)) colCount++;
      
      if (colCount == 9) { 
        rowCount++; 
        break; 
      }
    }
  }

  return lBoard;
}

/*
 * Recursive helper function for solveBoard, tries plugging in all possible values 
 * and backtracks with recursion until solved
 * 
 * Caller provides:
 *  A unique, unsolved board 
 *  A starting cell position of 0
 * Function guarantees: 
 *  Return true if board is solved, false if the board remains unsolved 
 *  Board is solved after function returns 
 * Caller is responsible for:
 *  Freeing all memory
 */
bool 
solveBoardHelper(sudoku_board_t* b, int pos) 
{
    int numZeros = 0; // count number of zeros
    for (int i = 0; i < b->size; i++) {
        for (int j = 0; j < b->size; j++) {
            if (!b->boardArray[i][j]) {
                numZeros++;
            }
        }
    }

    // Base case of recursion
    if (!numZeros) return true;

    // Find row and column from position
    int r = (int) (pos / b->size); 
    int c = (int) (pos % b->size); 

    // Step over filled numbers
    if (b->boardArray[r][c]) return solveBoardHelper(b, pos + 1);

    // Number to place
    int currentVal = 1;
    b->boardArray[r][c] = currentVal;

    while (isValid(b, r, c, currentVal) || !solveBoardHelper(b, pos + 1)) { // while the Number is present, iterate to next cell position 
        b->boardArray[r][c] = ++currentVal;

        if (currentVal > b->size) {
            b->boardArray[r][c] = 0;
            return false;
        }
    }

    return true;
}