# TESTING
## Project Sudoku — The C Crew 
### CS50, Fall 2021 
### Authors : Brody T., Saksham A., Sayuri M. 

All the testing is done in `testing.sh` which is called by typing `make test` on the command line. The test results can be found in `testing.out`.

The following wrong test cases are used to test the program:

* **Validating arguments** : Testing the program with different types and number of invalid arguments. For example : 
  * testing with the wrong number of command line arguments. 
  * testing with an invalid mode types, i.e. different from `create` and `solve`.
  * testing with an invalid difficulty types, i.e. different from `easy` and `hard`.

* **Integration testing** : Assemble all the modules and test the program as a whole using testing.sh. We provide different input files to test the solver. 
* **Unit testing** : For `create`, `solve` and `common` modules.
* **Fuzzy testing** : Implemented fuzzsudoku.c to test the `solve`. Our fuzzsudoku.c takes a number as argument and generates that many random puzzles, passes them to the solver, and prints the number of sudoku puzzles that were successfully solved.

 