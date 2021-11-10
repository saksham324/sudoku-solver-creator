#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

typedef struct sudoku_board {
    int **boardArray; // pointer to 2D array
    int size; // how long each row and column will be (e.g. 9 for 9x9 grid)
} sudoku_board_t; 

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

/********* isValid *************/ 

/*
 * Checks if a number trying to be inserted is already in the current row, column, or 3x3 grid
 * 
 * Caller provides:
 *  A valid sudoku_board_t, row and column number, value to be inserted
 * Function guarantee:
 *  Returns true if value is already seen by cell, else return false if value can be inserted
 * Caller is responsible for:
 *  Freeing memory
 */

bool isValid(int row, int col, sudoku_board_t *b, int val); 



/************ printBoard ************/
/*
 * Prints a given sudoku_board_t to stdout
 * 
 * Caller provides:
 *  A valid pointer to a sudoku_board_t struct
 * Function guarantee:
 *  sudoku_board_t is printed to stdout
 * Caller is responsible for:
 *  
 */
void printBoard(sudoku_board_t *b, FILE *fp);


/************ deleteBoard ***********/
/*
 * takes a `sudoku_board_t` struct and frees all associated memory
 * 
 * Caller provides:
 *  A valid pointer to a sudoku_board_t struct
 * Function guarantee:
 *  All relevant memory is freed
 * Caller is responsible for:
 *  Nothing
 */
bool deleteBoard(sudoku_board_t *b);