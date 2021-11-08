/*
* Brody Thompson, Dartmouth CS50, Fall 2021
*/

#include <stdio.h>
#include <stdlib.h>

int sovleBoard(int** board, int row, int column, int solutions){ //may need to be a 

    if(row == 10){
        int numOfSolutions = solutions;
        numOfSolutions += 1;
        return numOfSolutions;
    }
    int nextRow;
    int nextColumn;

    if(column == 9){
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
                if(i == 9){
                    return solutions;
                }
                else{
                    continue;
                }
            }
        }
    }
    else{

    }

}