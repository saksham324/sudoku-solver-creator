# CS50 Fall 2021, Final Project - Sudoku 2.0
## The C Crew 
### Brody T., Saksham A., Sayuri M.

### TSE Indexer Implementation Spec

### Structs

* *sudoku_board* represents a 9x9 sudoku board as a 2D array of integers ranging from 1-9 with 0 denoting an empty cell. 

### Create Module 

The *create* functionality uses the following functions to create a valid, incomplete sudoku board. 

```c
/************ generateEmptyBoard ************/
/* Create a new board structure
 *
 * Caller provides:
 *   Size of the sudoku board (e.g. 9 for a 9x9)  
 * We return:
 *   Pointer to a new board, or NULL if error.
 * We guarantee:
 *   The board struct has an empty 2D array determined 
 *   by the inputSize and it will store the inputSize in board->size.
 * Caller is responsible for:
 *   Later calling board_delete.
 */
/* see common.h for description */

sudoku_board *generateEmptyBoard(int inputSize); 

/************ fillBoard ************/
/*
 * Takes a sudoku_board as input and fills it completely using the solver functionality
 * 
 * Caller provides:
 *  An empty sudoku_board
 * Function guarantees:
 *  A board with one solution is returned
 * Caller is responsible for:
 *  Nothing
 */

bool fillBoard(sudoku_board *b); 


/********* removeNumbers *************/ 
/* 
 * Removes n numbers from the filled board, and checks if board is still unique. 
 *  
 * Caller provides : 
 *  A valid, filled sudoku_board and a number `n` to remove. 
 * Function guarantees : 
 *  Incomplete board with a unique solution 
 * Return: 
 *  True if successful, False if solution non-unique 
 * Caller is responsible for : 
 *  Nothing
 * 
*/

bool removeNumbers(sudoku_board *b, int n); 
```

The *common* subdirectory contains the following functions to assist in implementing both *create* and *solver* functionalities. 
```c 
typedef struct sudoku_board {
    int **boardArray; // pointer to 2D array
    int size; // how long each row and column will be (e.g. 9 for 9x9 grid)
} sudoku_board; 

/********* isUnique *************/ 

/* 
 * Returns whether sudoku_board has a unique solution
 * 
 * Caller provides: 
 *  A valid, unfilled sudoku board, a start position (0, 0) originally, the number of solutions
 * Function guarantees: 
 *  Returns 0 if no solutions, 1 if board has a unique solution, 2 if board 
 *  has multiple solutions
 * Caller is responsible for:
 *  Calling deleteBoard
 * 
 */

int isUnique(int i, int j, sudoku_board *b, int count); 

/********* isValid *************/ 

/*
 * Checks if a number trying to be inserted is already in the current row, column, or 3x3 grid
 * 
 * Caller provides:
 *  A valid sudoku_board, row and column number, value to be inserted
 * Function guarantee:
 *  Returns true if value is already seen by cell, else return false if value can be inserted
 * Caller is responsible for:
 *  Freeing memory
 */

bool isValid(int row, int col, sudoku_board *b, int val); 


/************ printBoard ************/
/*
 * Prints a given sudoku_board to stdout
 * 
 * Caller provides:
 *  A valid pointer to a sudoku_board struct
 * Function guarantee:
 *  sudoku_board is printed to stdout
 * Caller is responsible for:
 *  
 */
void printBoard(sudoku_board *b);


/************ deleteBoard ***********/
/*
 * takes a `sudoku_board` struct and frees all associated memory
 * 
 * Caller provides:
 *  A valid pointer to a sudoku_board struct
 * Function guarantee:
 *  All relevant memory is freed
 * Caller is responsible for:
 *  Nothing
 */
bool deleteBoard(sudoku_board *b);
```

The *solve* functionality solves the passed sudoku_board, and also supports some *create* functionality using the following functions: 

```c 
/************ solveBoard ************/
/*
 * Solves a passed board and returns whether or not the solution is unique
 * Caller provides:
 *  A valid sudoku_board
 * We guarantee:
 *  The passed board is solved with one solution or false is returned
 * Caller is responsible for:
 *  Nothing
 */

int *solveBoard(sudoku_board *board); 

/************ loadBoard ************/

/*
 * Loads board from stdin and validates loaded board
 * 
 * Caller provides:
 *  Valid file pointer to read from
 * Function guarantee:
 *  Returned board is valid or return NULL
 * Caller is responsible for:
 *  Calling deleteBoard on the returned sudoku_board
 */
sudoku_board *loadBoard(FILE *fp);
```

### Implementation

We implement the *creator* functionality by executing ```./sudoku create [difficulty]``` from the command line where difficulty indicates the desired difficulty of the generated, incomplete sudoku puzzle, either **easy** or **hard**. 

**Create** is implemented by initializing an empty sudoku_board structure with all 0s, populating the 9x9 grid, then removing the number of random cells necessary to generate a sudoku puzzle with a unique solution.

1. We initialize a structure **sudoku_board** to represent the sudoku grid. The structure contains two parameters: a 2D array, which is a double-pointer array of integers, and the other an integer that specifies the size of the board.
The board is initialized with zeros everywhere to represent the empty cells. 
2. Populate the board by using **solveBoard** to recursively fill in the empty cells. 
3. Call **removeNumbers** to remove the number of cells from the completed board based on difficulty inputed by the user.  
4. While there are still cells to be removed, choose a random non-empty cell to remove. Temporarily store the value of that cell and set the cell to empty. Check if the grid has a unique solution, if not replace the emptied cell with its original value. Otherwise, increment the count of cells that have been removed. 
5. Print the board to stdin for the user. 
6. Free all memory. 

<hr>

**Solve** is implemented by passing in an incomplete **sudoku_board** struct, then solving the board by filling in empty cells and backtracking whenever an inserted value is not valid, done recursively until the board is fully populated. The board is then printed for the user. 

1. Load in a board. 
2. Pass the board to the solver. First check whether the board has a unique solution. If the board has a unique solution, return 1. Else, return 0 for no solutions or for more than one solution. 
3. Go through the board one cell at a time and fill in empty ones recursively. Use recursive helper `solveBoardHelper` which, starting from a value of 1, inserts a value into a empty cell. If the value added is already seen board's its row, column, or 3x3 grid, or if a recursive call of solveBoardHelper from the next empty cell does not yield a solved board, change the value of the number inserted and try again. 
4. If the board is unique with one solution, print the solved puzzle to stdout, else print error and exit.
5. Delete the board. 


### Error Handling
We implement the following error checks: 

1. In `generateEmptyBoard`, whether the `sudoku_board` structure was initialized successfully. 
2. Whether a difficulty setting was entered. 
3. Whether a `sudoku_board` structure was properly initalized to store the loaded board. 
4. Whether a board has no solutions. 
5. Whether a board has a unique solution. 

### Assumptions
All relevant assumptions can be found in the README.md. 



