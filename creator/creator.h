/* 
* Header file for creator module
*
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../common/common.h"


/************ generateEmptyBoard ************/
/*
 * Generates a blank 9x9 board filled with 0s
 * Caller provides:
 * Nothing
 * Function guarantees:
 *  Board is initialized empty
 * Caller is responsible for:
 *  Calling deleteBoard on the returned sudoku_board
 */

sudoku_board *generateEmptyBoard(); 

/************ fillBoard ************/
/*
 * Takes a sudoku_board as input and fills it completely using the solver functionality
 * 
 * Caller provides:
 *  An empty sudoku_board
 * Function guarantees:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */

bool *fillBoard(sudoku_board *b); 


/********* removeNumbers *************/ 
/* 
 * Removes n numbers from the filled board, and checks if board is still unique. 
 *  
 * Caller provides : 
 *  A valid, filled sudoku_board and a number `n` to remove. 
 * Function guarantees : 
 *  Incomplete board with a unique solution 
 * Return: 
 *  True if successful, False if solution non-unique 
 * Caller is responsible for : 
 *  Nothing
 * 
*/

bool removeNumbers(sudoku_board *b, int n); 



