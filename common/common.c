#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "./common.h"

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
    if (i == 9) {
        i = 0; 
        if (++j == 9){
            return 1 + count; 
        }
    }

    if (b->boardArray[i][j] != 0) { // skip empty cells 
        return isUnique(i + 1, j , b, count); 
    }

    for (int num = 1; num <= 9 && count < 2; ++num) {
        if (isValid(i, j, b, num)) {
            b->boardArray[i][j] = num; // change the value and check if another solution exists
            count = isUnique(i + 1, j, b, count); // find more solutions by moving position to i+1
        } 
    }

    b->boardArray[i][j] = 0; // reset on backtrack 
    return count; 
}