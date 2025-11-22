%{
#include <stdio.h>
#include "PIBKH_PA3.h"    /* add this line */
#include "parser.tab.h"
%}

%option noyywrap
%option nounput noinput
%option yylineno

KW_PROGRAM    PROGRAM
KW_FUNCTION   FUNCTION
KW_VAR        VAR
KW_INTEGER    INTEGER
KW_STRING     STRING
KW_WHILE      WHILE
KW_DO         DO
KW_IF         IF
KW_THEN       THEN
KW_ELSE       ELSE
KW_BEGIN      BEGIN
KW_END        END

ID            [a-z]+

ZERO          0
NZDIGIT       [1-9]
DIGIT         [0-9]
INT           {NZDIGIT}{DIGIT}*

STRING        \'[^'\n]*\'

COMMENT       \{[^}\n]*\}

P_LE          <=
P_GE          >=
P_NE          <>
P_ASSIGN      :=

P_SINGLE      [\*\+\/\-\<\>\=\(\)\,\;\.\:]

WS            [ \t\r\n\xA0]+

%%

"\xEF\xBB\xBF"     { /* UTF-8 BOM: ignore */ }
{COMMENT}          { /* ignore comments */ }
{WS}               { /* ignore whitespace */ }

{KW_PROGRAM}       { return PROGRAM; }
{KW_FUNCTION}      { return FUNCTION; }
{KW_VAR}           { return VAR; }
{KW_INTEGER}       { return INTEGER; }
{KW_STRING}        { return STRING; }
{KW_WHILE}         { return WHILE; }
{KW_DO}            { return DO; }
{KW_IF}            { return IF; }
{KW_THEN}          { return THEN; }
{KW_ELSE}          { return ELSE; }
{KW_BEGIN}         { return KW_BEGIN; }
{KW_END}           { return KW_END; }

{ID} {
    yylval.sval = strdup(yytext);
    return ID;
}

{ZERO} {
    yylval.ival = 0;
    return NUM;
}

{INT} {
    yylval.ival = atoi(yytext);
    return NUM;
}

{STRING} {
    /* keep the quotes for now; parser/translator can handle them as-is */
    yylval.sval = strdup(yytext);
    return STR;
}

{P_LE}             { return LE; }
{P_GE}             { return GE; }
"=="               { return EQ; }
"="                { return EQ; }
{P_NE}             { return NEQ; }
{P_ASSIGN}         { return ASSIGN; }

{P_SINGLE} {
    switch (yytext[0]) {
        case '<': return LT;
        case '>': return GT;
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return STAR;
        case '/': return SLASH;
        case '(': return LPAREN;
        case ')': return RPAREN;
        case ',': return COMMA;
        case ';': return SEMI;
        case '.': return DOT;
        case ':': return COLON;
        case '=': return EQ;
        default:  return yytext[0];
    }
}

. {
    /* Unknown single char: hand it to the parser, which will likely error */
    return yytext[0];
}

%%
