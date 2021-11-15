/* solver.h - Header file for Solver module
*
* Authors: The C Crew - Brody T., Saksham A., Sayuri M.
* November 5th, 2021
* CS50 Fall 2021, Final Project
*/ 

#include <stdio.h> 
#include "../common/common.h"

/************ solveBoard ************/
/*
 * Solves a passed board and returns whether or not the solution is unique
 * Caller provides:
 *  A valid sudoku_board_t
 * We guarantee:
 *  The passed board is solved with one solution or false is returned
 * Caller is responsible for:
 *  Nothing
 */

int solveBoard(sudoku_board_t *board); 

/************ loadBoard ************/

/*
 * Loads board from stdin and validates loaded board
 * 
 * Caller provides:
 *  Valid file pointer to read from
 * Function guarantee:
 *  Returned board is valid or return NULL
 * Caller is responsible for:
 *  Calling deleteBoard on the returned sudoku_board_t
 */
sudoku_board_t *loadBoard(FILE *fp);







