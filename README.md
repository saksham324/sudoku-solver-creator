## The C Crew
## Brody T., Saksham A., Sayuri M. 
## CS50 Fall 2021, Final Project - Sudoku 2.0

**GitHub username:**  brody9thompson, saksham324, SayuriMagnabosco

*Project submitted for course CS50 (Software Design & Implementation) at Dartmouth College, Fall 2021.*

### The Sudoku Challenge
For this project, we worked as a team to write a set of C programs to create and solve Sudoku puzzles. We also wrote a set of programs (C and/or bash) to test individual parts and the entirety of the software.

### Implementation
The implementation of sudoku*  follows the project [instructions](https://www.cs.dartmouth.edu/~cs50/Project/) prodived. Details of the design and implementation were discussed among the team members and documented in the `DESIGN.md` and `IMPLEMENTATION.md` files in this folder. 

### Usage
After compilation, the *sudoku* should be run as follows:

```bash
Usage: ./sudoku mode difficulty
```
where
* "mode" is a string input set to `create` or `solve`. 
* "difficulty" is a string input set to `easy` or `hard`.

### Extra Credit
For the "topping" requirement of this assigment, we implemented an interactive user interface in the terminal. We implemented a `switch` as a menu and added colorful elements to the printing information. To faciliate grading, the topping was implemented in the file `sudokuTopping.c`. After compilation, the *sudokuTopping* should be run as follows:
```bash
Usage: ./sudokuTopping
```
where the user will interact with the program directly on the terminal, based on the menu options given. The program will only quit when the user chooses to do so, by pressing '2'. 

### Assumptions
1. Our program assumes in both modules that the dimension of the sudoku_board_t structure being used has size of 9. 
2. Our program in the solve module that loadBoard() always receives a pointer to a file produced by create and/or that follows the format of a 9x9 sudoku grid as outlined in the requirements of this project, such as the ones below:

``` bash
# Example 1:
6 0 8 0 2 3 0 0 0 
0 0 9 5 0 0 3 2 8 
0 0 2 0 0 0 0 0 0 
0 1 0 0 3 0 0 0 4 
0 0 6 7 4 5 0 1 2 
0 0 0 0 1 0 5 7 0 
2 7 5 6 9 0 0 3 0 
4 0 1 0 5 0 2 0 0 
0 0 3 0 7 1 0 9 5 

#Example 2:
-------------------------
| 1 8 6 | 3 2 5 | 4 9 7 | 
| 4 2 7 | 1 8 9 | 6 3 5 | 
| 5 9 3 | 6 4 7 | 1 8 2 | 
-------------------------
| 3 7 9 | 2 6 4 | 8 5 1 | 
| 6 1 5 | 9 7 8 | 2 4 3 | 
| 8 4 2 | 5 1 3 | 7 6 9 | 
-------------------------
| 7 5 8 | 4 9 1 | 3 2 6 | 
| 2 3 1 | 8 5 6 | 9 7 4 | 
| 9 6 4 | 7 3 2 | 5 1 8 | 
-------------------------
```

### Compilation
* To compile, simply `make all`.
* To test, type `make test`.
* To check for memory leaks, type `make valgrind`
* To clean, type `make clean`.

### Testing
The `testing.sh` program is a script that contains input errors and edge cases to test the robustness of this module and contains detailed information on how the test cases were build. More information in the test cases run, read the `TESTING.md` file.
* The program passed all the test cases.
* No memory leaks were found using the `valgrind`. 

Disclaimer : This program was made as a class project for COSC 50 : Software Design & Implementation at Dartmouth College during Fall 2021. If you are currently enrolled in this class, or planning to be kindly refrain from using this repository in any way. [Link to the Dartmouth Honor Principle](https://student-affairs.dartmouth.edu/policy/academic-honor-principle)
