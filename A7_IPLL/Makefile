# Makefile for compiling the Yacc and Lex files for micro C

CC=gcc
CFLAGS=-Wall
ROLL = 220101113

all: parser

parser: lex.yy.c y.tab.c y.tab.h
	$(CC) $(CFLAGS) -o parser y.tab.c lex.yy.c -ll

y.tab.c y.tab.h: a7_$(ROLL).y
	yacc -d a7_$(ROLL).y

lex.yy.c: a7_$(ROLL).l
	lex a7_$(ROLL).l
clean:
	rm -f parser lex.yy.c y.tab.c y.tab.h