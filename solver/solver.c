
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include "../common/common.h"
#include "../creator/creator.h"

const int BOARD_SIZE = 9; 

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
sudoku_board_t *loadBoard(FILE *fp) {
  if (!fp) return NULL;

  sudoku_board_t *lBoard = generateEmptyBoard(BOARD_SIZE); // generate Empty Board to be filled out 
  if (!lBoard) return NULL;
  
  // make sure number of rows is valid, iterate through each row
  int rowCount = 0;
  while (rowCount < lBoard->size) {

    // Iterate through each column
    int colCount = 0;
    while (colCount < lBoard->size) {

      // Get each character from fp, check if char is a digit, if yes insert
      char ch = fgetc(fp);
     
      if (!isdigit(ch)) { 
          continue; 
          }

      // Convert char to int value (ASCII)
      if (isdigit(ch)) lBoard->boardArray[rowCount][colCount] = (int)ch - 48;
      if (isdigit(ch)) colCount++;
      
      if (colCount == 9) { 
        rowCount++; 
        break; 
      }
    }
  }

  fprintf(stdout, "%s ", "load board succeeded! \n"); 
  printBoard(lBoard); 
  return lBoard;
}


// int solver(sudoku_board_t *board, int *row, int *column, int *solutions){ //may need to be a 

//     if(row == 9){
//         // int numOfSolutions = solutions;
//         // numOfSolutions += 1;
//         return solutions + 1;
//     }
    
//     // int nextColumn = 0;
//     // int nextRow = 0;

//     if(++column >= 9){
//         *column = 0; 
//         *row += 1; 
//     }
//     // } else {
//     //     nextColumn = column + 1;
//     //     nextRow = row + 1;
//     // }

//     if(board->boardArray[*row][*column] == 0){
//         for (int i = 1; i <= 9; i++){
//             if(isValid(board, &row, &column, i)){
//                 board->boardArray[*row][*column] = i;
//                 return solver(board, row, column, solutions);
//             }
//             else{
//                 if(i == 9){
//                     return solutions;
//                 }
//                 else{
//                     continue;
//                 }
//             }
//         }
//     }
    
//     return solver(board, row, column, solutions);
   
// }

bool solveBoardHelper(sudoku_board_t* b, int pos) {
    int numZeros = 0;
    for (int i = 0; i < b->size; i++) {
        for (int j = 0; j < b->size; j++) {
            if (!b->boardArray[i][j]) {
                numZeros++;
            }
        }
    }

    // Base case of recursion
    if (!numZeros) return true;

    // Find row and column from position
    int r = (int) (pos / b->size); 
    int c = (int) (pos % b->size); 

    // Step over filled numbers
    if (b->boardArray[r][c]) return solveBoardHelper(b, pos + 1);

    // Number to place
    int currentVal = 1;
    b->boardArray[r][c] = currentVal;

    while (isValid(b, r, c, currentVal) || !solveBoardHelper(b, pos + 1)) {
        b->boardArray[r][c] = ++currentVal;

        if (currentVal > b->size) {
            b->boardArray[r][c] = 0;
            return false;
        }
    }

    return true;
}

int solveBoard(sudoku_board_t *board){
    int solutions = isUnique(0, 0, board, 0); 
    solveBoardHelper(board, 0); 
    return solutions; 
}

