/* common.c - module with common functions to be used in the Sudoku Project
*             1. Creates the sudoku board
*             2. Deltes the sudoku board
*             3. Printing the board
*             4. Checks if a number to be inserted is valid
* 
* Author: Sayuri Tais Miyamoto Magnabosco
* November 5th, 2021
* CS50 Fall 2021, Final Project
*
*/ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"
#include "../libcs50/mem.h"

/***************** File-local global variables ***************/

/****************** Global data structures *******************/
typedef struct sudoku_board {
    int **boardArray;  // pointer to 2D array 
    int size;          // dimension of the board: size x size (e.g. 9x9)
} sudoku_board_t;

/******************** File-local functions *******************/
/* not visible outside this file */
bool is_in_row(sudoku_board_t *board, int row, int value);
bool is_in_col(sudoku_board_t *board, int column, int value);
bool is_in_square (sudoku_board_t *board, int row, int column, int value);

/********************* Global functions *********************/
/* that is, visible outside this file */

/***************** generateEmptyBoard() *********************/
/* see common.h for description */
sudoku_board_t*
generateEmptyBoard(int inputSize){
    sudoku_board_t* board = mem_malloc(sizeof(sudoku_board_t));
    if(board == NULL){
        return NULL;
    } else{
        // allocating space to the 2D array based on the input size:
        int **newArray = mem_calloc(inputSize, sizeof(int*));
        for(int i=0; i< inputSize; i++){
            int *temp = mem_calloc(inputSize, sizeof(int));
            if (temp != NULL) {
                newArray[i] = temp; 
            }
        }
        //assingning values and variables into our board structure:
        board->size = inputSize;
        board->boardArray = newArray;
        return board;
    }
}

/********************** delete_board() **********************/
/* see common.h for description */
bool
delete_board(sudoku_board_t *board)
{
    if (board == NULL){
        return false;
    } else{
        for (int i=0; i < (board->size); i++){ // frees the size x size array
            mem_free(board->boardArray[i]);
        }
        mem_free(board); // frees the board
    }
    return true;
}

/*********************** print_board() **********************/
/* see common.h for description */
void
print_board(sudoku_board_t *board)
{   
    if (board == NULL){
        fprintf (stdout,"NULL board. We cannot print it!");
    } else{
        int numCells = (board->size)*(board->size); // will store how many cells we have in the board. For a 9x9 grid, we will have 81 cells
        int width = board->size;                    // will store the lenght of the board
        int lenght = board->size;                   // will store the width of the board
        int i=0;                                    // will hold count of how many numbers we have printed
        while (i<numCells){ // loop through all numbers
        // fill up each row first, then move to the following row:
            for (int j=0; j<width;j++){ // prints the horizontal delimiter lines of the board
                if (width == 0 || width == 3 || width == 6){
                    fprintf(stdout, "-------------------------\n");
                } 
                for (int k = 0; k<(lenght/3); k++){
                    if(k!=2){ // will print the first 6 numbers of the row, three at a time
                        fprintf(stdout, "| %d %d %d", board->boardArray[width][3*k],board->boardArray[width][(3*k)+1],board->boardArray[width][(3*k)+2]);
                        i = i+3; // increase the counter 
                    } else{ // will print the last 3 numbers and go to a new line
                        fprintf(stdout, "| %d %d %d |\n", board->boardArray[width][3*k],board->boardArray[width][(3*k)+1],board->boardArray[width][(3*k)+2]);
                        i = i+3; // increase the counter
                    }
                    if(width == 8){ // print out the last delimiter line of the board
                        fprintf(stdout, "-------------------------\n\n");
                    }
                }
            }
        }
    }
}

/************************* is_valid() ***********************/
/* see common.h for description */
bool
isValid(sudoku_board_t *board, int row, int column, int value)
{
    if (is_in_row (board, row, value)== false ){ // checks if its valid in that row
        if (is_in_col (board, column, value) == false){ // cheks if its valid in thar column
            if (is_in_square (board, row, column, value)== false){ // checks if its valid in that small 3x3 sub-square
                return true;
            } else {
                return false;
            }
        } else{
            return false;
        }
    }
    return false;
}

/* 
* Helper function to check if a value is already in a given row
*
* Caller provides:
*    A valid sudoku board, the row we want to check, the value we are looking for
* We return:
*   TRUE if the value is present in the row, FALSE otherwise
* We guarantee:
*   The numbers stored in the board remain the same; aka: we do not
*   add the value into it.  
*/
bool
is_in_row(sudoku_board_t *board, int row, int value)
{
    int *rowArray = board->boardArray[row-1]; // gets the array of the row we are checking
    for (int i = 0; i< board->size; i++){ // checks if each item in the row matched the value we are trying to insert
        if (rowArray[i] == value){
            return true;
        }
    }
    return false;
}

/* 
* Helper function to check if a value is already in a given column
*
* Caller provides:
*    A valid sudoku board, the rcolumn we want to check, the value we are looking for
* We return:
*   TRUE if the value is present in the column, FALSE otherwise
* We guarantee:
*   The numbers stored in the board remain the same; aka: we do not
*   add the value into it.  
*/
bool
is_in_col(sudoku_board_t *board, int column, int value)
{
    for (int i = 0; i< board->size; i++){ // will loop thrugh all the board
        if (board->boardArray[i][column]== value){ // in the column we want to check, loop through all the cells(rows)
            return true;
        }
    }
    return false;
}

/* 
* Helper function to check if a value is already in a given 3x3 sub-qare of the grid, 
* based on the [row,col] position.
*
* Caller provides:
*    A valid sudoku board, the row and column we want to check, the value we are looking for
* We return:
*   TRUE if the value is present in the square, FALSE otherwise
* We guarantee:
*   The numbers stored in the board remain the same; aka: we do not
*   add the value into it.  
*/
bool
is_in_square (sudoku_board_t *board, int row, int column, int value)
{
    // Defines the range of rows and columns we will check. 
    // For example, for the position [2,3], our row indexers are 0-2, and column indexers are 0-2:
    int rowLowerBound = 3*((row-1)/3);
    int rowUpperBound = (3*((row-1)/3)+3);
    int columnLowerBound = 3*((column-1)/3);
    int columnUpperBound = (3*((column-1)/3)+3);
    for (int i = rowLowerBound; i <rowUpperBound; i++){ // will check the rows that belong to the square we are at
        int* curArray = board->boardArray[i]; // gets the array for one row at a time
        for (int j = columnLowerBound; j< columnUpperBound; j++){ // will check the collumns that belong to the square we are at
            if (curArray[j] == value){ // looks for the value 
                return true;
            }
        }
    }
    return false;
}
