#ifndef PIBKH_PA3_TRANSLATOR_H
#define PIBKH_PA3_TRANSLATOR_H

#include <stdio.h>

/* ====== Type and symbol definitions ==================================== */

typedef enum {
    TYPE_INT,
    TYPE_STRING
} TypeKind;

typedef enum {
    SYM_VAR,
    SYM_FUNC,
    SYM_TEMP,
    SYM_PARAM
} SymbolKind;

typedef struct Symbol Symbol;
typedef struct SymbolTable SymbolTable;
typedef struct NameList NameList;
typedef struct IntList IntList;
typedef struct Quad Quad;

/* Symbol for identifiers, temporaries, functions, parameters */
struct Symbol {
    char       *name;
    TypeKind    type;
    SymbolKind  kind;
    int         size;      /* in bytes */
    int         offset;    /* offset within AR or static area */
    SymbolTable *nested;   /* nested symbol table for functions */
};

/* A symbol table represents one scope */
struct SymbolTable {
    char        *name;
    SymbolTable *parent;
    Symbol     **symbols;
    int          count;
    int          capacity;
    int          offset;   /* running offset for locals/temps */
};

/* Simple linked list of names used during declarations */
struct NameList {
    char      *name;
    NameList  *next;
};

/* List of integer indices used for backpatching */
struct IntList {
    int       index;
    IntList  *next;
};

/* Quadruple for TAC */
struct Quad {
    char *op;
    char *arg1;
    char *arg2;
    char *result;
};

/* ====== Global state ==================================================== */

extern SymbolTable *globalST;
extern SymbolTable *currentST;

extern Quad *quad_array;
extern int   quad_count;
extern int   quad_capacity;

/* ====== Symbol table API =============================================== */

SymbolTable *symtab_create(const char *name, SymbolTable *parent);
Symbol *symtab_lookup(SymbolTable *st, const char *name);
Symbol *symtab_insert(SymbolTable *st,
                      const char *name,
                      TypeKind type,
                      SymbolKind kind,
                      int size);

/* Wrappers used in the grammar */
Symbol *st_insert(SymbolTable *st, const char *name, TypeKind type);
Symbol *st_lookup(SymbolTable *st, const char *name);

/* Temporary creation */
Symbol *new_temp(TypeKind type);

/* ====== Name list helpers ============================================== */

NameList *make_namelist(const char *name);
NameList *append_namelist(NameList *list, const char *name);

/* ====== Quad / TAC interface =========================================== */

void emit(const char *op,
          const char *arg1,
          const char *arg2,
          const char *result);

int nextinstr(void);
void print_quads(void);

/* ====== Backpatching helpers =========================================== */

IntList *makelist(int index);
IntList *merge(IntList *a, IntList *b);
void backpatch(IntList *list, int target);

/* ====== Translator lifecycle =========================================== */

void translator_init(void);
void translator_finalize(void);

/* ====== PA4: target code generation (x86) ============================== */

/* Called from the parser when a function header is seen. */
void register_function(Symbol *f, SymbolTable *st, int start_quad);
/* Called from the parser at the end of a function declaration. */
void function_set_end(Symbol *f, int end_quad);

/* Generate x86 / IA-32 assembly for the current quad array and symbol
 * tables and write it to 'out' (typically stdout).  */
void generate_x86(FILE *out);

#endif /* PIBKH_PA3_TRANSLATOR_H */
