# Makefile for microC 3-Address Code Generator
# Assignment 9: Machine Independent Code Generator for microC

CC = gcc
FLEX = flex
BISON = bison
CFLAGS = -Wall -g

ROLL = 220101113
PROG = a9_$(ROLL)

all: $(PROG)

$(PROG): lex.yy.c y.tab.c quad.c
	$(CC) $(CFLAGS) -o $(PROG) lex.yy.c y.tab.c quad.c -lfl

lex.yy.c: a9_$(ROLL).l y.tab.h
	$(FLEX) a9_$(ROLL).l

y.tab.c y.tab.h: a9_$(ROLL).y
	$(BISON) -dty a9_$(ROLL).y

run_tests: $(PROG)
	@echo "Running tests..."
	./$(PROG) < test1.mc > $(ROLL)_quads1.out
	./$(PROG) < test2.mc > $(ROLL)_quads2.out
	./$(PROG) < test3.mc > $(ROLL)_quads3.out
	@echo "Tests completed. Check output files."

clean:
	rm -f lex.yy.c y.tab.c y.tab.h $(PROG) $(ROLL)_quads*.out