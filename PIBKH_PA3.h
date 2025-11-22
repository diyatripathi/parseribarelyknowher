#ifndef PIBKH_PA3_H
#define PIBKH_PA3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
 * 1. Basic type & category enums
 * =======================================================*/

/* nanoPascal types */
typedef enum {
    TYPE_INT,
    TYPE_STRING
} TypeKind;

/* What kind of symbol this is (for debugging / printing) */
typedef enum {
    SYM_VAR,    /* normal variable (global/local) */
    SYM_FUNC,   /* function name */
    SYM_TEMP,   /* compiler-generated temporary */
    SYM_PARAM   /* function parameter */
} SymbolKind;

/* Forward declarations */
typedef struct Symbol Symbol;
typedef struct SymbolTable SymbolTable;
typedef struct NameList NameList;

/* =========================================================
 * 2. Symbol table data structures
 * =======================================================*/

struct Symbol {
    char        *name;       /* identifier name */
    TypeKind     type;       /* TYPE_INT / TYPE_STRING */
    SymbolKind   kind;       /* SYM_VAR / SYM_FUNC / SYM_TEMP / SYM_PARAM */
    int          size;       /* size in bytes (e.g. 4) */
    int          offset;     /* offset in activation record / global area */
    SymbolTable *nested;     /* nested table for functions (NULL otherwise) */
};

struct SymbolTable {
    char         *name;      /* e.g. "global", "add", "factorial" */
    SymbolTable  *parent;    /* enclosing scope (NULL for global) */

    Symbol      **symbols;   /* dynamic array of Symbol* */
    int           count;     /* number of entries used */
    int           capacity;  /* capacity of symbols[] */

    int           offset;    /* running offset for new variables */
};

/* A linked list of names (for VAR x, y, z: INTEGER; etc.) */
struct NameList {
    char      *name;
    NameList  *next;
};

/* =========================================================
 * 3. Globals for current compilation
 * =======================================================*/

/* Global (root) symbol table and the currently active table */
extern SymbolTable *globalST;
extern SymbolTable *currentST;

/* Counter for compiler-generated temporaries (t0, t1, ...) */
extern int temp_counter;

/* Convenient machine-independent "sizes" (you can adjust in .c) */
extern const int SIZE_INT;
extern const int SIZE_STR;

/* =========================================================
 * 4. Symbol table API
 * =======================================================*/

SymbolTable *symtab_create(const char *name, SymbolTable *parent);
Symbol *symtab_insert(SymbolTable *st,
                      const char *name,
                      TypeKind type,
                      SymbolKind kind,
                      int size);
Symbol *symtab_lookup(SymbolTable *st, const char *name);

/* Compatibility wrappers for PA3 .y file */
Symbol *st_insert(SymbolTable *st, const char *name, TypeKind type);
Symbol *st_lookup(SymbolTable *st, const char *name);

/* Create or reuse nested table for a function symbol */
SymbolTable *symtab_create_nested(Symbol *funcSym, const char *name);

/* Create a new temporary (t0, t1, ...) in currentST */
Symbol *new_temp(TypeKind type);

/* Print the symbol table... */
// void symtab_print(SymbolTable *st) {
//     printf("ST: %s, Parent: %s\n",
//            st->name,
//            st->parent ? st->parent->name : "null");

//     for (int i = 0; i < st->count; ++i) {
//         Symbol *sym = st->symbols[i];


//         if (sym->kind == SYM_TEMP) continue;   /* skip temps in ST print */

//         const char *catStr;
//         if (sym->kind == SYM_FUNC) {
//             catStr = "func";
//         } else if (sym->kind == SYM_PARAM) {
//             catStr = "param";
//         } else {  /* SYM_VAR */
//             /* global vs local decided by which table the symbol lives in */
//             catStr = (st == globalST) ? "global" : "local";
//         }

//         const char *typeStr = (sym->type == TYPE_INT) ? "int" : "string";

//         printf("%s, %s, %s, %s\n",
//                sym->name,
//                typeStr,
//                catStr,
//                sym->nested ? sym->nested->name : "null");
//     }

//     printf("\n");

//     /* recursively print nested tables if you want */
//     for (int i = 0; i < st->count; ++i) {
//         Symbol *sym = st->symbols[i];
//         if (sym->nested) symtab_print(sym->nested);
//     }
// }
void symtab_print(SymbolTable *st);




/* =========================================================
 * 5. NameList helpers (for declarations)
 * =======================================================*/

NameList *namelist_single(const char *name);
NameList *namelist_append(NameList *list, const char *name);
void namelist_free(NameList *list);

/* Compatibility wrappers for PA3 .y file */
NameList *make_namelist(const char *name);
NameList *append_namelist(NameList *list, const char *name);

/* =========================================================
 * 6. Quad / TAC representation
 * =======================================================*/

typedef struct Quad {
    char *op;       /* operator: "+", "=", "ifgoto", "goto", "call", etc. */
    char *arg1;     /* first argument (or condition left side) */
    char *arg2;     /* second argument (or condition right side) */
    char *result;   /* destination (or target label for gotos) */
} Quad;

/* Dynamic array of quads */
extern Quad *quad_array;
extern int   quad_count;
extern int   quad_capacity;

/* Emit a quad: result = arg1 op arg2 (you are free to interpret fields) */
void emit(const char *op,
          const char *arg1,
          const char *arg2,
          const char *result);

/* Returns index (0-based) of next instruction to be emitted */
int nextinstr(void);

/* Print all quads in whatever format PA3 expects */
void print_quads(void);

/* =========================================================
 * 7. Backpatching structures & API (for control flow)
 * =======================================================*/

typedef struct IntList {
    int              index;  /* index into quad_array */
    struct IntList  *next;
} IntList;

/* Create a singleton list containing one index */
IntList *makelist(int index);

/* Merge two lists; returns head of merged list */
IntList *merge(IntList *a, IntList *b);

/* For every index in list, patch quad_array[index].result with target label */
void backpatch(IntList *list, int target);

/* =========================================================
 * 8. Initialization helpers
 * =======================================================*/

/* Initialize globalST, currentST, quad array, etc. */
void translator_init(void);

/* Cleanup (free tables, quads, etc.) — optional but nice */
void translator_finalize(void);

#endif /* PIBKH_PA3_H */
