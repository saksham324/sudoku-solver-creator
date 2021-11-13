C = common
R = creator
S = solver

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(DEBUG) -I$C -I$R -I$S
PROG = sudoku
OBJS = sudoku.o $S/solver.o $R/creator.o $C/common.o 

MAKE = make
.PHONY: all clean test valgrind

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

# test:
# 	./testing.sh

# valgrind:
# 	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) create
# 	valgrind --leak-check=full --show-leak-kinds=all ./$(PROG) solve < tests/test2/test2