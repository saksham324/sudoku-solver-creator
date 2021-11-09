/* sudoku.c - 
* 
* Authors: The C Crew - Brody T., Saksham A., Sayuri M. 
* CS50 Fall 2021, Final Project 
* November 5th, 2021
*
*/ 

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <common/common.h>
#include <common/validateInput.h>

/***************** Local global variables ***************/
static const int BOARD_SIZE = 9;  // how long each row and column will be (e.g. 9 for 9x9 grid)

/**************** Local function prototypes **************/

/***********************  Main  **************************/

int main(const int argc, char *argv[]){
    char *mode;          // string input set to `create` or `solve`
    char *difficulty;    // string input set to `easy` or `hard`

    // Validate arguments:
    // If number of input arguments is wrong
    if (argc != 3){  
        fprintf(stderr, "Usage: ./sudoku mode difficulty\n\n");
		exit(1);
    }
    // Checks if the input mode is a valid one 
    if (!isValidMode(argv[1])) {
        fprintf(stderr, "Error: invalid mode option. You can pick between 'create' or 'solve'\n\n");
        exit(2);
    }
    // Checks if the input difficulty is a valid one (easy/hard)
    if (!isValidDifficulty(argv[2])) {
        fprintf(stderr, "Error: invalid difficulty option. You can pick between 'easy' or 'hard'\n\n");
        exit(3);
    }

    // Since the inputs are correct, we can assign them into variables:
    mode = argv[1];
    difficulty = argv[2];

    sudoku_board_t board = generateEmptyBoard(BOARD_SIZE);

    exit 0;
}