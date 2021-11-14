#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "./common/common.h"
#include "./creator/creator.h"
#include "./solver/solver.h"

bool compareBoards(sudoku_board_t *b, sudoku_board_t *solved); 

int main (int argc, char *argv[])
{
    if (argc < 2) {                 
        fprintf(stderr, "ERROR: invalid number of arguments\n");
        return 1;
    }

    srand(time(0)); // randomize 

    int nPuzzles = atoi(argv[1]);  // get number of random puzzles to generate from command-line
    int testsPassed = 0;

    int created = 0;                 // puzzles created so far 
    sudoku_board_t *b, *unsolved;
    while (created < nPuzzles) {
        created++;
        b = generateEmptyBoard(9);         // generate the board structure
        if (!b) exit(2); 
        fillBoard(b);            // populate the board until it is full

        int numToRemove = 44;    // Only make on difficulty level hard
        
        if (!(removeNumbers(b, numToRemove))) break;   // break test if too many iterations or a non-unique puzzle
        unsolved = b;
        int numSols = solveBoard(b);
        if (numSols != 1) break;                       // break if no unique solution
        if (compareBoards(b, unsolved)) break;        // break if already filled cells are changed by solver

        deleteBoard(b);
        testsPassed++;
    }
    printf("Passed %d/%d tests!\n", testsPassed, nPuzzles);
    return 0;
}

/* 
 * Checks whether sudoku solver changes filled cells in the grid
 * 
 * Caller provides:
 *  valid sudoku puzzle with unique solution
 *  valid solved sudoku puzzle
 * Function guarantee: 
 *  Returns false if already filled cells in grid remained unaltered after calling solver
 * Caller is responsible for:
 *  Freeing memory
 */
bool compareBoards(sudoku_board_t *b, sudoku_board_t *solved) {
    for (int i = 0; i < b->size; i++) {                // loop
        for (int j = 0; j < b->size; j++) {
            int cell = b->boardArray[i][j];
            if ((cell != 0) && (cell != solved->boardArray[i][j])) return true;
        }
    }
    return false;
}