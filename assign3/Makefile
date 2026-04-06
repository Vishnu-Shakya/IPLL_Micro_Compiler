CC = gcc
FLEX = flex
CFLAGS = -Wall

all: lexer

lexer: lex.yy.o prac.o
	$(CC) $(CFLAGS) -o lexer lex.yy.o prac.o

lex.yy.c: prac.l
	$(FLEX) prac.l

lex.yy.o: lex.yy.c prac.h
	$(CC) $(CFLAGS) -c lex.yy.c

prac.o: prac.c prac.h
	$(CC) $(CFLAGS) -c prac.c

clean:
	rm -f lexer lex.yy.c *.o