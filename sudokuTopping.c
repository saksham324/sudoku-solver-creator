/* sudokuExtraCredit.c - implements an UI with the funcitonalities of sudoku.c
* 
* Authors: The C Crew - Brody T., Saksham A., Sayuri M. 
* CS50 Fall 2021, Final Project 
* November 13th, 2021
*/ 

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./common/common.h"
#include "./creator/creator.h"
#include "./solver/solver.h"


/***************** Local global variables ***************/
static const int BOARD_SIZE = 9;  // how long each row and column will be (e.g. 9 for 9x9 grid)
static const int MAX_ITERATIONS = 40; 

/**************** Local function prototypes **************/
void printWelcome(); // will print general information about the program and instructions of the game 
void createBoard(sudoku_board_t *board, int numRemove); // create the board based on the level (easy/hard)
void solveBoardRecent(sudoku_board_t *board); // solves the most recently created sudoku board
void solveBoardFile(sudoku_board_t *board); // solves the most a sudoku board from an input file

/***********************  Main  **************************/
int main(){
    int choice;                   // menu selection from user input
    int again = 1;                // variable to keep printing the menu until user decides to quit the program, when again will become '2'
    int numRemove = 0;            // variable to indicate how many numbers we are missing from the board, to indicate easy/hard difficulty
    sudoku_board_t *board = NULL; // set to NULL originally 

    printWelcome(); // tells the user about the program

    // Menu: print the manu options avaliable and wait for a user input
	do {
        fprintf(stdout, "\033[0;32m"); // prints in green color
		fprintf(stdout,"                      MAIN MENU                      \n");
        fprintf(stdout, "\033[0;35m"); // prints in purple color
		fprintf(stdout,"------------------------------------------------------\n");
        fprintf(stdout, "\033[0m"); //Resets the text to default color
		fprintf(stdout,"Press [1] to create a new Sudoku board \n"); // will print option numbers in red
		fprintf(stdout,"Press [2] to solve the Sudoku board \n");
        fprintf(stdout, "\033[0;35m"); // prints in purple color
		fprintf(stdout,"------------------------------------------------------\n\n");
        fprintf(stdout, "\033[0m"); //Resets the text to default color
		
		fprintf(stdout,"Enter your choice (1,2): ");
		scanf("%d", &choice);
		fprintf(stdout,"You selected option %d\n", choice);
		switch (choice){
			case 1: // create sudoku
				fprintf(stdout,"\nPress [1] to create an EASY sudoku board\n");
				fprintf(stdout,"Press [2] to create a HARD sudoku board\n");
				fprintf(stdout,"Enter your choice (1,2): "); 
				scanf ("%d", &choice);
				if (choice == 1){ // wants an easy sudoku board
                    numRemove = 44;
                    createBoard(board, numRemove);
				}
				else{ // wants a hard sudoku board
                    numRemove = 56;
                    createBoard(board, numRemove);
				}
				break;
			
			case 2: //solve sudoku
                fprintf(stdout,"\033[0;31m"); // prints in red
                fprintf(stdout,"You MUST have either created a sudoku board first in option [1] of the Main Menu, or have made a file with an unsolved sudoku board to proceed.\n\n");
                fprintf(stdout, "\033[0m"); //Resets the text to default color
                fprintf(stdout,"Did you make any of the above?\n");
                fprintf(stdout,"Press [1] if YES\n");
                fprintf(stdout,"Press [2] if NO\n");
                fprintf(stdout,"Enter your choice (1,2): "); 
                scanf ("%d", &choice);
                if (choice == 1){ // can proceed
                    fprintf(stdout,"\nPress [1] to solve the most recently created sudoku board\n");
                    fprintf(stdout,"Press [2] to solve a sudoku board from another file\n");
                    fprintf(stdout,"Enter your choice (1,2): "); 
                    scanf ("%d", &choice);
                    if (choice == 1){ // wants to solve most recenlty sudoku board
                        solveBoardRecent(board);
                    }
                    else { // wants to solve a sudoku board from another file
                        solveBoardFile(board);
                    }
				} else{ // cannot proceed; goes back to main menu
                    break;
                }
				break;
		}
		fprintf(stdout,"\n\nWould you like to select another option from the Main Menu?\nPress '1' or any other number to come back.\nPress '2' to quit the program.\n");
        scanf("%d", &again);
	} while (again != 2);
    return 0;
}

/*
* This function will print a welcoming message to the user
*/
void 
printWelcome(){
    fprintf(stdout, "\033[0;32m"); // prints in green color
    fprintf(stdout,"\n\n\nWELCOME TO SUDOKU @ DARMOUTH CS50\n");
    fprintf(stdout,"Developed by The C Crew: Brody T., Saksham A., Sayuri M.\n\n");
    fprintf(stdout, "\033[0m"); //Resets the text to default color

    fprintf(stdout, "Sudoku is a logic-based, number-placement puzzle. The game first appeared in Japan in 1984 where it was given the name “Sudoku,” which is short for a longer expression in Japanese that means, “the digits are limited to one occurrence”.\n\n");
    fprintf(stdout, "This program implements a classic sudoku.The objective is to fill a 9×9 grid with digits so that each column, each row, and each of the nine 3×3 subgrids that compose the grid contain all of the digits from 1 to 9.\n\n\n");
}

/*
* This fuction will create a sudoku board based on the difficulty.
* Caller provides: 
*   a valid pointer to board fully solved and the number of squares 
*   to be removed form the solution.
*/
void
createBoard(sudoku_board_t *board, int numRemove)
{
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
    fprintf(stdout, "The unsolved board was saved into the file 'saveUnfilledBoard.out'\n");
    fclose(fp); 
    deleteBoard(board); // delete board 

}


/*
* This function will solve the most recently created sudoku board
* Caller provides: 
*   a board pointer
*/
void
solveBoardRecent(sudoku_board_t *board)
{
    FILE *loadFp = fopen("saveUnfilledBoard.out", "r"); // gets the board we just made
    if (!loadFp){
        fprintf(stdout, "Cannot open the file\n");
        exit(5); 
    } else{
        board = loadBoard(loadFp); // load board in from file
        fprintf(stdout, "\nUnsolved board:");
        printBoard(board, stdout);
    }

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
        fprintf(stdout, "Solved board:");
        printBoard(board, stdout); // print unique solution
        printBoard(board, fp); // save solved board to file
        fprintf(stdout, "The solution was saved into the file 'saveFilledBoard.out'\n");
        fclose(fp); 

    } else {
        fprintf(stderr, "Board does not have unique solution\n"); 
    }
    fclose(loadFp); 
    deleteBoard(board); // delete board 
}

/*
* This function will solve a sudoku board from a filename provided in stdin
* Caller provides: 
*   a board pointer
*/
void 
solveBoardFile(sudoku_board_t *board)
{
    char fileName[50] = ""; // maximum size of the name of the file 
    fprintf (stdout, "Enter a file name. It cannot have more than 100 characters\n");
    scanf("%s", fileName);

    FILE *loadFp = fopen (fileName, "r"); //opening the file
	
	while (loadFp == NULL) { //checking if the file exists
        strcpy(fileName, "");
        fprintf(stdout,"\nThis file was not found. Please enter another file name with less than 100 charcaters.\n");
        fprintf(stdout,"Alternatively, you can solve the most recenlty generated board by typing 'saveUnfilledBoard.out'\n");
		scanf("%s", fileName);
		loadFp = fopen (fileName, "r"); //opening the file
	}
    board = loadBoard(loadFp); // load board in from file
    fprintf(stdout, "\nUnsolved board:");
    printBoard(board, stdout);
    
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
        fprintf(stdout, "Solved board:");
        printBoard(board, stdout); // print unique solution
        printBoard(board, fp); // save solved board to file
        fprintf(stdout, "The solution was saved into the file 'saveFilledBoard.out'\n");
        fclose(fp); 

    } else {
        fprintf(stderr, "Board does not have unique solution\n"); 
    }
    fclose(loadFp); 
    deleteBoard(board); // delete board 
}