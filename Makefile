.RECIPEPREFIX := >
NAME    ?= PIBKH

# PA3 lexer / parser files
LEXERL  := $(NAME)_PA3.l
PARSERY := $(NAME)_PA3.y

LEX     ?= flex
YACC    ?= bison
CC      ?= gcc
CFLAGS  ?= -O2 -Wall

# Build the translator executable (as per PA3 spec)
all: translator

translator: parser.tab.o lex.yy.o PIBKH_PA3.o
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

# Convenience target: run translator on GroupName_PA3.np
# and save TAC output in GroupName_PA3_quads.out
run: translator
> ./translator < $(NAME)_PA3.np > $(NAME)_PA3_quads.out

clean:
> rm -f translator parser.tab.c parser.tab.h lex.yy.c *.o

.PHONY: all run clean
