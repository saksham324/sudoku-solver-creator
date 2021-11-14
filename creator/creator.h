/* create.h - header file for CS50 'create' module
* Author: Sayuri Tais Miyamoto Magnabosco, Saksham Arora, Brody Thompson
* November 5th, 2021
* CS50 Fall 2021, Final Project
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
 *  Calling deleteBoard on the returned sudoku_board_t
 */

sudoku_board_t *generateEmptyBoard(); 

/************ fillBoard ************/
/*
 * Takes a sudoku_board_t as input and fills it completely using the solver functionality
 * 
 * Caller provides:
 *  An empty sudoku_board_t
 * Function guarantees:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */

bool *fillBoard(sudoku_board_t *b); 


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

bool removeNumbers(sudoku_board_t *b, int n); 



