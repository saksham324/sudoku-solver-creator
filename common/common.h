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

/**************** Global types ****************/
typedef struct sudoku_board {
    int **boardArray; // pointer to 2D array
    int size; // how long each row and column will be (e.g. 9 for 9x9 grid)
} sudoku_board_t;  // opaque to users of the module

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
bool deleteBoard(sudoku_board_t *board);

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
void printBoard(sudoku_board_t *board);

/**************** isValid() ***************/
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


/********* isUnique *************/ 

/* 
 * Returns whether sudoku_board_t has a unique solution
 * 
 * Caller provides: 
 *  A valid, unfilled sudoku board, a start position (0, 0) originally, the number of solutions
 * Function guarantees: 
 *  Returns 0 if no solutions, 1 if board has a unique solution, 2 if board 
 *  has multiple solutions
 * Caller is responsible for:
 *  Calling deleteBoard
 * 
 * This function is inspired from : 
 *  https://stackoverflow.com/a/24343433
 */

int isUnique(int i, int j, sudoku_board_t *b, int count); 

// /************ printBoard ************/
// /*
//  * Prints a given sudoku_board_t to stdout
//  * 
//  * Caller provides:
//  *  A valid pointer to a sudoku_board_t struct
//  * Function guarantee:
//  *  sudoku_board_t is printed to stdout
//  * Caller is responsible for:
//  *  
//  */
// void printBoard(sudoku_board_t *b, FILE *fp);


// /************ deleteBoard ***********/
// /*
//  * takes a `sudoku_board_t` struct and frees all associated memory
//  * 
//  * Caller provides:
//  *  A valid pointer to a sudoku_board_t struct
//  * Function guarantee:
//  *  All relevant memory is freed
//  * Caller is responsible for:
//  *  Nothing
//  */
// bool deleteBoard(sudoku_board_t *b);

/*************** isValidMode() ****************/
/* Checks if the user input for the mode is a valid
* option, that is "create" or "solve"
*
* Caller provides:
*   the input string of the "mode" 
* We return:
*   TRUE if input is either "create" or "solve", FALSE otherwise
* Notes:
*   We call normalizeWord() to make the input string into lowercase
*/
bool isValidMode(char *input);

/************ isValidDifficulty() ************/
/* Checks if the user input for the difficulty is a valid
* option, that is "easy" or "hard"
*
* Caller provides:
*   the input string of the "difficulty" 
* We return:
*   TRUE if input is either "easy" or "hard", FALSE otherwise
* Notes:
*   We call normalizeWord() to make the input string into lowercase
*/
bool isValidDifficulty(char *input);

#endif //__COMMON_H