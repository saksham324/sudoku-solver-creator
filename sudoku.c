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
    if (argc < 2){  
        fprintf(stderr, "Usage: ./sudoku mode difficulty\n\n");
		exit(1);
    }

    // Since the inputs are correct, we can assign them into variables:
    mode = argv[1];

    if (strcmp(mode, "create") == 0) { // if in create mode, create empty board
        if (argc != 3) {
            fprintf(stderr, "Usage: ./sudoku create difficulty\n\n");
            exit(2); 
        }

        difficulty = argv[2]; 
        int numRemove; 

        if (!isValidDifficulty(difficulty)) {
            fprintf(stderr, "Usage: ./sudoku create difficulty\n\n");
            exit(2); 
        }
        else {
            numRemove = strcmp(difficulty, "easy") == 0 ? 44 : 56; 
        }

        board = generateEmptyBoard(BOARD_SIZE); 
        if(!board) {
            exit(4); // error if board could not be created 
        }
        
        int fillTries = 0; // tracker of iterations
        
        
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

        printBoard(board, stdout); // write created board into stdout
        FILE *fp = fopen("saveUnfilledBoard.out", "w"); // save unfilled board into file
        if (!fp) exit(5); 
        else printBoard(board, fp); 
        fclose(fp); 
        deleteBoard(board); // delete board 

    } else if (strcmp(mode, "solve") == 0) {
        FILE *loadFp = stdin;  
        board = loadBoard(loadFp); // load board in from stdin

        if(!board) {
            fprintf(stderr, "Invalid board, could not load board. \n"); 
            exit(4); // exit if board couldn't be loaded 
        }
        int solutions = solveBoard(board); // solve board and save the number of solutions it has
        if (!solutions) {
            fprintf(stderr, "Could not find solutions to given board\n"); 
        } else if (solutions == 1) {
            fprintf(stdout, "%s", "\n"); 
            FILE *fp = fopen("saveFilledBoard.out", "w"); 
            printBoard(board, stdout); // print unique solution
            printBoard(board, fp); // save solved board to file
            fclose(fp); 

        } else {
            fprintf(stderr, "Board does not have unique solution\n"); 
        }

        deleteBoard(board); // delete board 
    } else {
        fprintf(stderr, "Command must be either `solve` or `create`\n"); 
        exit(3); 
    }
    exit(0);
}