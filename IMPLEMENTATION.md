# CS50 Fall 2021, Final Project - Sudoku 2.0
## The C Crew 
### Brody T., Saksham A., Sayuri M.

### TSE Indexer Implementation Spec

### Structs

* *sudoku_board* represents a 9x9 sudoku board as a 2D array of integers ranging from 1-9 with 0 denoting an empty cell. 

### Create Module 

The *create* functionality parses the difficulty passed in by the user through the command line and uses the following functions to create a valid, incomplete sudoku board. 

```c
/* Takes a difficulty value (easy or hard) and returns how many numbers to remove from the specific board (44 for easy, 56 for hard) */
int parseDifficulty(sudoku_board *board, int d);

/* Takes a sudoku board and fills it in completely using the solver functionality */
bool populateBoard(sudoku_board *b);

/* Removes n numbers (based on difficulty rating) from a valid sudoku board and checks if board is still unique */
bool removeNumbers(sudoku_board *board, int n);

/* Prints a given board to stdout */
void printBoard(sudoku_board *board, FILE *fp);

/* takes a `sudoku_board` module and frees all associated memory */
bool deleteBoard(sudoku_board *board);
```

The *solve* functionality solves the passed sudoku_board, and also supports some *create* functionality using the following functions: 

```c 
/* Loads board from stdin and validates loaded baord for structural validity */
sudoku_t *loadBoard(FILE *fp);

/* Solves a passed board and returns whether or not the solution is unique */
int solveBoard(sudoku_t *b);
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
3. 
4. If the board is unique with one solution, print the solved puzzle to stdout, else print error and exit.
5. Delete the board. 


### Error Handling
We implement the following error checks: 

1. In `generateEmptyBoard`, whether the `sudoku_board` structure was initialized successfully. 
2. Whether a difficulty setting was entered. 
3. Whether a `sudoku_board` structure was properly initalized to store the loaded board. 
4. Whether a board has no solutions. 
5. Whether a board has a unique solution

### Assumptions
All relevant assumptions can be found in the README.md. 



