.RECIPEPREFIX := >
NAME    ?= PIBKH
LEXERL  := $(NAME)_PA2.l
PARSERY := $(NAME)_PA2.y

LEX     ?= flex
YACC    ?= bison
CC      ?= gcc
CFLAGS  ?= -O2 -Wall

all: parser

parser: parser.tab.o lex.yy.o PIBKH_PA3.o
> $(CC) $(CFLAGS) -o $@ $^

parser.tab.c parser.tab.h: $(PARSERY)
> $(YACC) -d -o parser.tab.c --defines=parser.tab.h $<

lex.yy.c: $(LEXERL) parser.tab.h
> $(LEX) -o $@ $<

parser.tab.o: parser.tab.c
> $(CC) $(CFLAGS) -c $<

lex.yy.o: lex.yy.c parser.tab.h
> $(CC) $(CFLAGS) -c $<

PIBKH_PA3.o: PIBKH_PA3.c PIBKH_PA3.h
> $(CC) $(CFLAGS) -c PIBKH_PA3.c

run: parser
> ./parser < $(NAME)_PA2.np

clean:
> rm -f parser parser.tab.c parser.tab.h lex.yy.c *.o

.PHONY: all run clean
