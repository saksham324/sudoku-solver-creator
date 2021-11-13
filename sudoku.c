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
#include "./common/common.h"
#include "./creator/creator.h"
#include "./solver/solver.h"
#include <time.h>


/***************** Local global variables ***************/
static const int BOARD_SIZE = 9;  // how long each row and column will be (e.g. 9 for 9x9 grid)
static const int MAX_ITERATIONS = 40; 


/******************** Data structures *******************/

/**************** Local function prototypes **************/

/***********************  Main  **************************/

int main(const int argc, char *argv[]){
    srand(time(0));
    char *mode;          // string input set to `create` or `solve`
    char *difficulty;    // string input set to `easy` or `hard`
    sudoku_board_t *board = NULL; // set to NULL originally 

    // Validate arguments:
    // If number of input arguments is wrong
    if (argc != 3){  
        fprintf(stderr, "Usage: ./sudoku mode difficulty\n\n");
		exit(1);
    }
    //Checks if the input mode is a valid one 
    // if (isValidMode(argv[1])) {
    //     printf("%s", argv[1]); 
    //     fprintf(stderr, "Error: invalid mode option. You can pick between 'create' or 'solve'\n\n");
    //     exit(2);
    // }
    // // Checks if the input difficulty is a valid one (easy/hard)
    // if (isValidDifficulty(argv[2])) {
    //     fprintf(stderr, "Error: invalid difficulty option. You can pick between 'easy' or 'hard'\n\n");
    //     exit(3);
    // }

    // Since the inputs are correct, we can assign them into variables:
    mode = argv[1];
    difficulty = argv[2];

    if (strcmp(mode, "create") == 0) { // if in create mode, create empty board
        board = generateEmptyBoard(BOARD_SIZE); 
        if(!board) {
            exit(4); // error if board could not be created 
        }
        
        int fillTries = 0; // tracker of iterations
        int numRemove = 0; 
        if(strcmp(difficulty, "easy") == 0){
            numRemove = 44;
        } else {
            numRemove = 56; 
        } 
        
         // numbers to remove from filled board based on difficulty 
        while(!fillBoard(board) && fillTries < MAX_ITERATIONS){
            fprintf(stderr, "Board filling failed, trying again.. \n"); 
            fillTries++; 
        }

        if (fillTries == MAX_ITERATIONS) {
            fprintf(stderr, "Board creation failed."); 
            deleteBoard(board); // delete board if creation failed
            exit(5); 
        }

        int removeTries = 0; 

        while(!removeNumbers(board, numRemove) && removeTries < MAX_ITERATIONS) {
            fprintf(stderr, "Board removing failed, trying again.. \n"); 
            removeTries++; 
        }

        if (removeTries == MAX_ITERATIONS) {
            fprintf(stderr, "Board creation failed."); 
            deleteBoard(board); // delete board if creation failed
            exit(5); 
        }

        // FILE *fp; 
        // fp = fopen("create.out", "w"); 
        // printBoard(board, fp); // write created board into file

        printBoard(board); // write created board into stdout
        deleteBoard(board); // delete board 

    } else if (strcmp(mode, "solve") == 0) {
        FILE *loadFp = stdin;  
        board = loadBoard(loadFp); // load board in from stdin

        if(!board) exit(4); // exit if board couldn't be loaded 

        int solutions = solveBoard(board); // solve board and save the number of solutions it has
        if (!solutions) {
            fprintf(stderr, "Could not find solutions to given board"); 
        } else if (solutions == 1) {
            fprinf(stdout, "%s", "\n"); 
            printBoard(board); // print unique solution
        } else {
            fprintf(stderr, "Board does not have unique solution"); 
        }

        deleteBoard(board); // delete board 
    }
    exit(0);
}