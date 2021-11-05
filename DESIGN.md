# Project Sudoku — The C Crew 
## CS50, Fall 2021 
## Authors : Brody T., Saksham A., Sayuri M. 
### Sudoku Design Spec 

For this project, we worked as a team to write a set of C programs to create and solve Sudoku puzzles. Sudoku is well known logic puzzle where numbers between 1 and 9 are placed on a 9x9 grid of cells. The placement of numbers has to follow certain rules. There are many variations of Sudoku, but in this version, the 9x9 grid is further divided into 9 square shaped regions of size 3x3.

### User Interface 

The Sudoku interface with the user is on the command-line; it has two modes `create` and `solve`. 

execute from the command line with usage syntax 
``` 
./sudoku mode difficulty
```
, where
* "mode" is a string input set to `create` or `solve`. 
* "difficulty" is a string input set to `easy` or `hard`.

### Visual Representation 
The sudoku puzzle with empty spaces between each cell is displayed in stdout. The sudoku puzzle is represented as 9 numbers seprated by single space in the following format, where zeroes imply empty cells:
```bash
-------------------
|7 8 0|4 0 0|1 2 0|
|6 0 0|0 7 5|0 0 9|
|0 0 0|6 0 1|0 7 8|
-------------------
|0 0 7|0 4 0|2 6 0|
|0 0 1|0 5 0|9 3 0|
|9 0 4|0 6 0|0 0 5|
-------------------
|0 7 0|3 0 0|0 1 2|
|1 2 0|0 0 7|4 0 0|
|0 4 9|2 0 6|0 0 7|
-------------------
```

### Functional decomposition into modules

We plan on implementing the following modules/functions, which is subject to change: 
* **main** : parses, validates arguments inputted by the user, and initializes other modules. 
#### Create Module
* **generateBoard** : initializes empty `sudoku_board` struct, and returns a filled board. 
* **removeNumbers** : takes a filled board as input, removes numbers based on difficulty while making sure the solution is unique for each value removed. 



#### Solve module 
* **loadBoard** : reads from ```stdin``` and loads it into a valid board data structure. 
* **solve** : takes in a passed sudoku board as input, solves and returns an error if the solution is not unique. 

#### Common module 
* **printBoard** : prints a given board to ```stdout```. 
* **deleteBoard** : takes a `sudoku_board` data structure and frees all associated memory. 
* **isValid** : checks values in a given sudoku board, and returns true if a valid solution is possible based on rules of sudoku, false if not. 

### Major data structures
* **sudoku_board** : a modified 2-dimensional array which stores its size and the values in the board. 
  ```c
  typedef struct sudoku_board {
      int **boardArray; // pointer to 2D array
      int size; // how long each row and column will be (e.g. 9 for 9x9 grid)
  }
* **2D array** : a 2-dimensional array to keep track of numbers from 1-9 in each 3x3 grid, row and column. 









