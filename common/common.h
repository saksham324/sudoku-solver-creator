/* common.h - header file for CS50 'common' module (this used in the 'sudoku.c' file)
* 
* Author: Sayuri Tais Miyamoto Magnabosco
* November 5th, 2021
* CS50 Fall 2021, Final Project
*
*/ 


#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../libcs50/mem.h"

/**************** Global types ****************/
typedef struct sudoku_board sudoku_board_t; // opaque to users of the module

/**************** Functions ****************/

/*********** generateEmptyBoard() **********/
/* Create a new board structure
*
* Caller provides:
*   Size of the sudoku board (e.g. 9 for a 9x9)  
* We return:
*   Pointer to a new board, or NULL if error.
* We guarantee:
*   The board struct has an empty 2D array determined 
*   by the inputSize and it will store the inputSize in board->size.
* Caller is responsible for:
*   Later calling delete_board.
*/
sudoku_board_t* generateEmptyBoard(int inputSize);

/**************** delete_board() **************/
/* Delete the whole board
*
* Caller provides:
*   a valid board pointer.  
* We guarantee:
*   we ignore NULL board.
*/
bool delete_board(sudoku_board_t *board);

/************** print_board() **************/
/* Prints the 9x9 sudoku board with the values
*
* Caller provides:
*   a valid, non-NULL board strucutre
* We guarantee:
*   the values of the board will not change
* Note:
*   this function is written to print a standard 9x9 grid
*   and will not correclty print boards of a different size
*/
void print_board(sudoku_board_t *board);

/**************** is_valid() ***************/
/* Checks if the number we are trying to input is valid. That is, if it
* does not exist on the row, column, and 3x3 square we are trying to input 
*
* Caller provides:
*   valid board, row, column, and the value attempted to input in the board
* We return:
*   TRUE if the value can be inserted in that row/column/square, false otherwise
* Note:
*   We use three helper functions, one to check the column, one to chek the 
*   row, and one to check the suqare.
*/
bool isValid(sudoku_board_t *board, int row, int column, int value);

#endif // __COMMON_H