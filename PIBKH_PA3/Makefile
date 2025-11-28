.RECIPEPREFIX := >
NAME    ?= PIBKH

# PA4 lexer / parser files
LEXERL  := $(NAME)_PA3.l
PARSERY := $(NAME)_PA3.y

LEX     ?= flex
YACC    ?= bison
CC      ?= gcc
CFLAGS  ?= -O2 -Wall

all: compiler

compiler: parser.tab.o lex.yy.o PIBKH_PA3_translator.o
> $(CC) $(CFLAGS) -o $@ $^

parser.tab.c parser.tab.h: $(PARSERY)
> $(YACC) -d -o parser.tab.c --defines=parser.tab.h $<

lex.yy.c: $(LEXERL) parser.tab.h
> $(LEX) -o $@ $<

parser.tab.o: parser.tab.c
> $(CC) $(CFLAGS) -c $<

lex.yy.o: lex.yy.c parser.tab.h
> $(CC) $(CFLAGS) -c $<

PIBKH_PA3_translator.o: PIBKH_PA3_translator.c PIBKH_PA3_translator.h
> $(CC) $(CFLAGS) -c $< -o $@

run: compiler
> ./compiler < p1.np > PIBKH_PA4_quads1.asm

test: compiler
> ./compiler < p1.np > PIBKH_PA4_quads1.asm

clean:
> rm -f compiler parser.tab.c parser.tab.h lex.yy.c *.o

.PHONY: all run clean test