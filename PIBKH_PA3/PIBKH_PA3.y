%{
#include <stdio.h>
#include "PIBKH_PA3_translator.h"

int yylex(void);
void yyerror(const char *s);
%}

%union {
    int       ival;      /* for NUM */
    char     *sval;      /* for ID, STR */
    Symbol   *sym;       /* for expression, term, factor, function_header */
    NameList *namelist;  /* for variable_list */
    TypeKind  type;      /* for type nonterminal */
}


/* tokens with values */
%token PROGRAM FUNCTION VAR INTEGER STRING
%token WHILE DO IF THEN ELSE KW_BEGIN KW_END
%token <sval> ID STR
%token <ival> NUM
%token PLUS MINUS STAR SLASH
%token LT GT LE GE EQ NEQ
%token ASSIGN LPAREN RPAREN COMMA SEMI DOT COLON

/* typed nonterminals */
%type <type> type
%type <namelist> variable_list
%type <sym> expression simple_expression term factor
%type <sym> function_header
%type <ival> expression_list

%nonassoc LT GT LE GE EQ NEQ
%left PLUS MINUS
%left STAR SLASH
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%start program

%%

program
  : PROGRAM ID SEMI declaration_list_opt function_declaration_list_opt compound_statement DOT
  ;

declaration_list_opt
  :
  | declaration_list
  ;

declaration_list
  : declaration_list VAR variable_list COLON type SEMI
    {
        NameList *nl = $3;
        while (nl) {
            SymbolKind kind = SYM_VAR;
            symtab_insert(currentST, nl->name, $5, kind, 4);
            nl = nl->next;
        }
    }
  | VAR variable_list COLON type SEMI
    {
        NameList *nl = $2;
        while (nl) {
            SymbolKind kind = SYM_VAR;
            symtab_insert(currentST, nl->name, $4, kind, 4);
            nl = nl->next;
        }
    }
  ;

variable_list
  : ID
      {
          $$ = make_namelist($1);
      }
  | variable_list COMMA ID
      {
          $$ = append_namelist($1, $3);
      }
  ;

type
  : INTEGER
      { $$ = TYPE_INT; }
  | STRING
      { $$ = TYPE_STRING; }
  ;

function_declaration_list_opt
  :
  | function_declaration_list
  ;

function_declaration_list
  : function_declaration_list function_declaration SEMI
  | function_declaration SEMI
  ;

function_declaration
  : function_header declaration_list_opt compound_statement
    {
        /* Mark end of function's quad range */
        Symbol *f = $1;  /* Get function symbol from function_header */
        function_set_end(f, nextinstr());
        
        if (currentST->parent) currentST = currentST->parent;
    }
  ;

function_header
  : FUNCTION ID
      {
          /* Create the function's symbol table *before* parsing parameters */
          SymbolTable *fnST = symtab_create($2, currentST);
          currentST = fnST;   /* parameter_list now inserts into fnST */
      }
    LPAREN parameter_list RPAREN COLON type SEMI
      {
          /* currentST is the function's ST, whose parent is the global ST */
          SymbolTable *fnST   = currentST;
          SymbolTable *parent = fnST->parent;

          /* Insert function symbol in parent (global) table */
          Symbol *f = symtab_insert(parent,
                                    $2,   /* function name */
                                    $8,   /* return type (type nonterminal) */
                                    SYM_FUNC,
                                    0);
          f->nested = fnST;   /* link function to its symbol table */

          /* Register function for code generation */
          register_function(f, fnST, nextinstr());

          /* Stay in fnST; function_declaration will pop back to parent */
          $$ = f;  /* Pass function symbol to function_declaration */
      }
  ;


parameter_list
  : variable_list COLON type
    {
        NameList *nl = $1;
        while (nl) {
            symtab_insert(currentST, nl->name, $3, SYM_PARAM, 4);
            nl = nl->next;
        }
    }
  | parameter_list SEMI variable_list COLON type
    {
        NameList *nl = $3;
        while (nl) {
            symtab_insert(currentST, nl->name, $5, SYM_PARAM, 4);
            nl = nl->next;
        }
    }
  ;

compound_statement
  : KW_BEGIN statement_list opt_semi KW_END
  ;

opt_semi
  :
  | SEMI
  ;

statement_list
  : statement
  | statement_list SEMI statement
  ;

statement
  : ID ASSIGN expression
      {
          Symbol *lhs = st_lookup(currentST, $1);
          if (lhs && $3) {
              emit("=", $3->name, "", lhs->name);
          }
      }
  | ID LPAREN RPAREN
      {
          emit("call", $1, "0", "");
      }
  | ID LPAREN expression_list RPAREN
      {
          char buf[32];
          sprintf(buf, "%d", $3);
          emit("call", $1, buf, "");
      }
  | compound_statement
  | selection_statement
  | iteration_statement
  ;

selection_statement
  : IF expression THEN statement %prec LOWER_THAN_ELSE
  | IF expression THEN statement ELSE statement
  ;

iteration_statement
  : WHILE expression DO statement
  ;

expression_list
  : expression
      {
          if ($1) emit("param", $1->name, "", "");
          $$ = 1;
      }
  | expression_list COMMA expression
      {
          if ($3) emit("param", $3->name, "", "");
          $$ = $1 + 1;
      }
  ;

expression
  : simple_expression
      { $$ = $1; }
  | simple_expression LT simple_expression
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("<", $1->name, $3->name, t->name);
          $$ = t;
      }
  | simple_expression GT simple_expression
      {
          Symbol *t = new_temp(TYPE_INT);
          emit(">", $1->name, $3->name, t->name);
          $$ = t;
      }
  | simple_expression LE simple_expression
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("<=", $1->name, $3->name, t->name);
          $$ = t;
      }
  | simple_expression GE simple_expression
      {
          Symbol *t = new_temp(TYPE_INT);
          emit(">=", $1->name, $3->name, t->name);
          $$ = t;
      }
  | simple_expression EQ simple_expression
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("==", $1->name, $3->name, t->name);
          $$ = t;
      }
  | simple_expression NEQ simple_expression
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("<>", $1->name, $3->name, t->name);
          $$ = t;
      }
  ;

simple_expression
  : term
      { $$ = $1; }
  | simple_expression PLUS term
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("+", $1->name, $3->name, t->name);
          $$ = t;
      }
  | simple_expression MINUS term
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("-", $1->name, $3->name, t->name);
          $$ = t;
      }
  ;

term
  : factor
      { $$ = $1; }
  | term STAR factor
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("*", $1->name, $3->name, t->name);
          $$ = t;
      }
  | term SLASH factor
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("/", $1->name, $3->name, t->name);
          $$ = t;
      }
  ;

factor
  : ID
      {
          $$ = st_lookup(currentST, $1);
      }
  | NUM
      {
          Symbol *t = new_temp(TYPE_INT);
          char buf[32];
          sprintf(buf, "%d", $1);
          emit("=", buf, "", t->name);
          $$ = t;
      }
  | STR
      {
          Symbol *t = new_temp(TYPE_STRING);
          emit("=", $1, "", t->name);
          $$ = t;
      }
  | LPAREN expression RPAREN
      {
          $$ = $2;
      }
  | ID LPAREN expression_list RPAREN
      {
          Symbol *t = new_temp(TYPE_INT);
          char buf[32];
          sprintf(buf, "%d", $3);
          emit("call", $1, buf, t->name);
          $$ = t;
      }
  | PLUS factor
      {
          $$ = $2;
      }
  | MINUS factor
      {
          Symbol *t = new_temp(TYPE_INT);
          emit("uminus", $2->name, "", t->name);
          $$ = t;
      }
  ;

%%

void yyerror(const char *s) { printf("%s\n", s); }