/* common.c - module with common functions to be used in the Sudoku Project
*             1. Creates the sudoku board
*             2. Deltes the sudoku board
*             3. Printing the board
*             4. Checks if a number to be inserted is valid
* 
* Author: Sayuri Tais Miyamoto Magnabosco, Saksham Arora, Brody Thompson
* November 5th, 2021
* CS50 Fall 2021, Final Project
*
*/ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/***************** File-local global variables ***************/

/****************** Global data structures *******************/
typedef struct sudoku_board {
    int **boardArray;  // pointer to 2D array 
    int size;          // dimension of the board: size x size (e.g. 9x9)
} sudoku_board_t;

/******************** File-local functions *******************/
/* not visible outside this file */
bool is_in_row(sudoku_board_t *board, int row, int column, int value);
bool is_in_col(sudoku_board_t *board, int row, int column, int value);
bool is_in_square (sudoku_board_t *board, int row, int column, int value);

/********************* Global functions *********************/
/* that is, visible outside this file */

/***************** generateEmptyBoard() *********************/
/* see common.h for description */
sudoku_board_t*
generateEmptyBoard(int inputSize){
    sudoku_board_t* board = malloc(sizeof(sudoku_board_t));
    if (board == NULL) return NULL;

    // allocating space to the 2D array based on the input size:
    int **newArray = calloc(inputSize, sizeof(int*));
    for(int i=0; i < inputSize; i++){
        int *temp = calloc(inputSize, sizeof(int));
        if (temp == NULL) return NULL; 
        newArray[i] = temp; 
    }
    //assingning values and variables into our board structure:
    board->size = inputSize;
    board->boardArray = newArray;
    return board;
}

/* Function called by isValidDifficulty. 
* Converts all the characters of the word into lowercase. 
* 
* Caller provides:
*   a word
* We return:
*   the normalized word
*/
void normalizeWord(char *s) {
    if (s != NULL) {
        int c = 0;
   
        while (s[c] != '\0') {

            // subtracting 32 from the ASCII value
            if (s[c] >= 'A' && s[c] <= 'Z') {
                s[c] = s[c] + 32;
            }
            c++;
        }
    }
}

/********************** deleteBoard() **********************/
/* see common.h for description */
bool
deleteBoard(sudoku_board_t *board)
{
    if (board == NULL){
        return false;
    } else{
        for (int i=0; i < (board->size); i++){ // frees the size x size array
            free(board->boardArray[i]);
        }
        free(board->boardArray); 
        free(board); // frees the board
        board = NULL; 
    }
    return true;
}

/*********************** printBoard() **********************/
/* see common.h for description */
void
printBoard(sudoku_board_t *b, FILE *fp)
{   
    if (!b || !fp) return;
    fprintf(fp, "%s", "\n");
    for (int i = 0; i < b->size; i++) {
        if (i == 0 || (i % 3 == 0)) {
            fprintf(fp, "%s", "-------------------------");
            fprintf(fp, "%s", "\n"); 
        }
        for (int j = 0; j < b->size; j++) {
            if (j == 0) fprintf(stdout, "%s ", "|"); 
            fprintf(fp, "%i ", b->boardArray[i][j]);
            if ((j + 1) % 3 == 0) fprintf(fp, "%s ", "|");
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "%s", "-------------------------\n");
}



/************************* isValid() ***********************/
/* see common.h for description */
bool
isValid(sudoku_board_t *board, int row, int column, int value) {
    if (is_in_row(board, row, column, value)) return true; 
    if (is_in_col(board, row, column, value)) return true; 
    if (is_in_square(board, row, column, value)) return true; 
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
is_in_row(sudoku_board_t *board, int row, int column, int value){
    // int *rowArray = board->boardArray[row-1]; // gets the array of the row we are checking
    for (int i = 0; i< board->size; i++){ // checks if each item in the row matched the value we are trying to insert
        if (i == column) continue; 
        if (board->boardArray[row][i] == value) return true;
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
is_in_col(sudoku_board_t *board, int row, int column, int value)
{
    for (int i = 0; i< board->size; i++){ // will loop thrugh all the board
        if (i == row) continue;
        if (board->boardArray[i][column] == value) return true; // in the column we want to check, loop through all the cells(rows)
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
    int rowLowerBound = (int) (row / 3) * 3; 
    int columnLowerBound = (int) (column / 3) * 3;  

    for (int i = rowLowerBound; i < rowLowerBound + 3; i++){ // will check the rows that belong to the square we are at
        for (int j = columnLowerBound; j < columnLowerBound + 3; j++){ // will check the collumns that belong to the square we are at
            if (i == row && j == column) continue; 
            if (board->boardArray[i][j]== value) return true; // looks for the value    
        }
    }
    return false;
}


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

int isUnique(int i, int j, sudoku_board_t *b, int count) {
    // base case
    if (j == 9) {        // if we have gotten to the end of the first row
        j = 0;
        if (++i == 9)  // if we have gotten to end of the board
            return count + 1;
  }

  if (b->boardArray[i][j] != 0)  // skip filled cells
      return isUnique(i, j + 1, b, count);

  // search for 2 solutions instead of 1
  // return, if 2 solutions are found
  for (int val = 1; val <= 9 && count < 2; ++val) {
      if (!isValid(b, i, j, val)) {
          b->boardArray[i][j] = val;
          // add additional solutions
          count = isUnique(i, j + 1, b, count);
      }
  }
  
  b->boardArray[i][j] = 0; // reset on backtrack
  return count;
}

// /************* File-local functions ************/
// /* not visible outside this file */
// void normalizeWord (char *word);

// /************** Global functions **************/
// /* that is, visible outside this file */

/*************** isValidMode() ****************/
/* validateInput.h for description */
bool 
isValidMode(char *input)
{   printf("%s", input); 
    normalizeWord(input);
    if (strcmp(input, "create" ) != 0 || strcmp(input, "solve" ) != 0 ){
        return false;
    }
    return true;
}

/************** isValidDifficulty() **************/
/* validateInput.h for description */
bool
isValidDifficulty(char *input)
{
    normalizeWord (input);
    if (strcmp(input, "easy" ) != 0 || strcmp(input, "hard" ) != 0 ){
        return false;
    }
    return true;
}

