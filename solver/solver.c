
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "../common/common.h"
#include "../creator/creator.h"

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

  sudoku_board_t *lBoard = generateEmptyBoard(); // generate Empty Board to be filled out 
  if (!lBoard) return NULL;
  
  // make sure number of rows is valid, iterate through each row
  int rowCount = 0;
  while (rowCount < lBoard->size) {

    // Iterate through each column
    int colCount = 0;
    while (colCount < lBoard->size) {

      // Get each character from fp, check if char is a digit, if yes insert
      char ch = fgetc(fp);
      if (ch == '\n') { 
          rowCount++; 
          break; 
        }
      if (!isdigit(ch)) { 
          continue; 
          }

      // Convert char to int value (ASCII)
      lBoard->boardArray[rowCount][colCount] = (int)ch - 48;
      colCount++;
    }
  }

  return lBoard;
}


int solveBoard(int** board){
    return solver(**board, 0, 0, 0);
}

int solver(int** board, int row, int column, int solutions){ //may need to be a 

    if(row == 9){
        int numOfSolutions = solutions;
        numOfSolutions += 1;
        return numOfSolutions;
    }
    int nextRow;
    int nextColumn;

    if(column == 8){
        int nextColumn = 1;
        int nextRow = row + 1;
    }
    else{
        int nextColumn = column + 1;
        int nextRow = row + 1;
    }

    if(board[row][column] == 0){
        for (int i = 1; i <= 9; i ++){
            if(isValid(board, i, row, column)){
                board[row][column] = i;
                return sovleBoard(board, nextRow, nextColumn, solutions);
            }
            else{
                if(i == 8){
                    return solutions;
                }
                else{
                    continue;
                }
            }
        }
    }
    else{
        return sovleBoard(board, nextRow, nextColumn, solutions);
    }
}