C = common
R = creator
S = solver

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(DEBUG) -I$C -I$R -I$S
PROG = sudoku
OBJS = sudoku.o $S/solver.o $R/creator.o $C/common.o 

MAKE = make
.PHONY: all clean test valgrind fuzztest

all: 
	$(MAKE) -C $C
	$(MAKE) -C $R
	$(MAKE) -C $S
	$(MAKE) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

sudoku.o: $C/common.h $R/creator.h $S/solver.h
	$(CC) $(CFLAGS) -c -o $@ sudoku.c 

clean:
	rm -f $(PROG)
	rm -f *~ *.o
	rm -rf *.dSYM
	$(MAKE) -C $C clean
	$(MAKE) -C $R clean
	$(MAKE) -C $S clean

fuzztest.o: fuzztest.c $C/common.h $R/creator.h $S/solver.h
	$(CC) $(CFLAGS) -c -o $@ fuzztest.c

fuzztest: fuzztest.o $S/solver.o $R/creator.o $C/common.o 
	$(CC) $(CFLAGS) $^ -o $@

test:
	bash -v testing.sh



valgrind:
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) create easy 
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) create hard 
	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) solve < test.out