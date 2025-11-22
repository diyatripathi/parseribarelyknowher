#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PIBKH_PA3.h"

/* =========================================================
 * 1. Global variables
 * =======================================================*/

SymbolTable *globalST   = NULL;
SymbolTable *currentST  = NULL;

int temp_counter = 0;

const int SIZE_INT = 4;
const int SIZE_STR = 4;

Quad *quad_array    = NULL;
int   quad_count    = 0;
int   quad_capacity = 0;

/* =========================================================
 * 2. Internal helpers
 * =======================================================*/

static char *strdup_safe(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *p = (char *)malloc(len + 1);
    if (!p) {
        fprintf(stderr, "Out of memory in strdup_safe\n");
        exit(1);
    }
    memcpy(p, s, len + 1);
    return p;
}

static void ensure_symbol_capacity(SymbolTable *st) {
    if (st->capacity == 0) {
        st->capacity = 8;
        st->symbols = (Symbol **)malloc(st->capacity * sizeof(Symbol *));
        if (!st->symbols) {
            fprintf(stderr, "Out of memory in ensure_symbol_capacity\n");
            exit(1);
        }
    } else if (st->count >= st->capacity) {
        st->capacity *= 2;
        st->symbols = (Symbol **)realloc(st->symbols,
                                         st->capacity * sizeof(Symbol *));
        if (!st->symbols) {
            fprintf(stderr, "Out of memory in ensure_symbol_capacity (realloc)\n");
            exit(1);
        }
    }
}

static void ensure_quad_capacity(void) {
    if (quad_capacity == 0) {
        quad_capacity = 16;
        quad_array = (Quad *)malloc(quad_capacity * sizeof(Quad));
        if (!quad_array) {
            fprintf(stderr, "Out of memory in ensure_quad_capacity\n");
            exit(1);
        }
    } else if (quad_count >= quad_capacity) {
        quad_capacity *= 2;
        quad_array = (Quad *)realloc(quad_array,
                                     quad_capacity * sizeof(Quad));
        if (!quad_array) {
            fprintf(stderr, "Out of memory in ensure_quad_capacity (realloc)\n");
            exit(1);
        }
    }
}

static int type_size(TypeKind t) {
    switch (t) {
        case TYPE_INT:    return SIZE_INT;
        case TYPE_STRING: return SIZE_STR;
        default:          return SIZE_INT;
    }
}

/* =========================================================
 * 3. Symbol table functions
 * =======================================================*/

SymbolTable *symtab_create(const char *name, SymbolTable *parent) {
    SymbolTable *st = (SymbolTable *)malloc(sizeof(SymbolTable));
    if (!st) {
        fprintf(stderr, "Out of memory creating SymbolTable\n");
        exit(1);
    }
    st->name     = strdup_safe(name);
    st->parent   = parent;
    st->symbols  = NULL;
    st->count    = 0;
    st->capacity = 0;
    st->offset   = 0;
    return st;
}

Symbol *symtab_lookup(SymbolTable *st, const char *name) {
    SymbolTable *cur = st;
    while (cur) {
        for (int i = 0; i < cur->count; ++i) {
            if (strcmp(cur->symbols[i]->name, name) == 0)
                return cur->symbols[i];
        }
        cur = cur->parent;
    }
    return NULL;
}

Symbol *symtab_insert(SymbolTable *st,
                      const char *name,
                      TypeKind type,
                      SymbolKind kind,
                      int size)
{
    /* 1. Check only this table for an existing symbol with the same name */
    for (int i = 0; i < st->count; ++i) {
        if (strcmp(st->symbols[i]->name, name) == 0) {
            /* Optional: update its type/kind/size if you want
               but for PA3 it's fine to just return it. */
            return st->symbols[i];
        }
    }

    /* 2. Not found locally: create a new symbol */
    Symbol *sym = (Symbol *)malloc(sizeof(Symbol));
    if (!sym) {
        fprintf(stderr, "Out of memory in symtab_insert\n");
        exit(1);
    }

    sym->name   = strdup_safe(name);
    sym->type   = type;
    sym->kind   = kind;
    sym->size   = size;
    sym->offset = st->offset;
    sym->nested = NULL;

    /* 3. Grow the symbol array if needed */
    if (st->count == st->capacity) {
        int newCap = (st->capacity == 0) ? 8 : 2 * st->capacity;
        st->symbols = (Symbol **)realloc(st->symbols,
                                         newCap * sizeof(Symbol *));
        if (!st->symbols) {
            fprintf(stderr, "Out of memory growing symbol table\n");
            exit(1);
        }
        st->capacity = newCap;
    }

    st->symbols[st->count++] = sym;
    st->offset += size;

    return sym;
}


SymbolTable *symtab_create_nested(Symbol *funcSym, const char *name) {
    if (!funcSym) return NULL;
    SymbolTable *nested = symtab_create(name, currentST);
    funcSym->nested = nested;
    return nested;
}

Symbol *new_temp(TypeKind type) {
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", temp_counter++);
    /* temps are int-sized in this assignment */
    return symtab_insert(currentST, buf, type, SYM_TEMP, SIZE_INT);
}

static const char *type_to_string(TypeKind t) {
    switch (t) {
        case TYPE_INT:    return "int";
        case TYPE_STRING: return "string";
        default:          return "unknown";
    }
}

static const char *kind_to_string(SymbolKind k) {
    switch (k) {
        case SYM_VAR:   return "var";
        case SYM_FUNC:  return "func";
        case SYM_TEMP:  return "temp";
        case SYM_PARAM: return "param";
        default:        return "sym";
    }
}

/* Helper: map a symbol to the "scope" string for printing */
static const char *scope_string(Symbol *sym, SymbolTable *st) {
    if (sym->kind == SYM_FUNC)  return "func";
    if (sym->kind == SYM_PARAM) return "param";
    if (st == globalST)         return "global";
    return "local";
}

void symtab_print(SymbolTable *st) {
    if (!st) return;

    printf("--------------------\n");
    printf("ST: %s, Parent: %s\n",
           st->name,
           (st->parent ? st->parent->name : "null"));
    printf("--------------------\n");

    for (int i = 0; i < st->count; ++i) {
        Symbol *sym = st->symbols[i];

        /* Hide temporaries from printed table */
        if (sym->kind == SYM_TEMP) continue;

        const char *scope;

        if (sym->kind == SYM_FUNC) {
            scope = "func";
        } else if (sym->kind == SYM_PARAM) {
            scope = "param";
        } else if (st == globalST) {
            scope = "global";
        } else {
            scope = "local";
        }

        printf("%s, %s, %s, %s\n",
               sym->name,
               type_to_string(sym->type),
               scope,
               (sym->nested ? sym->nested->name : "null"));
    }
    printf("\n");

    /* Recursively print nested symbol tables (functions) */
    for (int i = 0; i < st->count; ++i) {
        if (st->symbols[i]->nested) {
            symtab_print(st->symbols[i]->nested);
        }
    }
}


/* =========================================================
 * 3.x  Compatibility wrappers for PA3 grammar
 * =======================================================*/

Symbol *st_insert(SymbolTable *st, const char *name, TypeKind type) {
    int size = type_size(type);
    return symtab_insert(st, name, type, SYM_VAR, size);
}

Symbol *st_lookup(SymbolTable *st, const char *name) {
    return symtab_lookup(st, name);
}

/* NameList wrappers used by the grammar */

NameList *make_namelist(const char *name) {
    NameList *n = (NameList *)malloc(sizeof(NameList));
    if (!n) {
        fprintf(stderr, "Out of memory in make_namelist\n");
        exit(1);
    }
    n->name = strdup_safe(name);
    n->next = NULL;
    return n;
}

NameList *append_namelist(NameList *list, const char *name) {
    NameList *n = make_namelist(name);
    if (!list) return n;
    NameList *p = list;
    while (p->next) p = p->next;
    p->next = n;
    return list;
}

/* =========================================================
 * 4. NameList helper functions
 * =======================================================*/

NameList *namelist_single(const char *name) {
    NameList *n = (NameList *)malloc(sizeof(NameList));
    if (!n) {
        fprintf(stderr, "Out of memory in namelist_single\n");
        exit(1);
    }
    n->name = strdup_safe(name);
    n->next = NULL;
    return n;
}

NameList *namelist_append(NameList *list, const char *name) {
    if (!list) return namelist_single(name);
    NameList *cur = list;
    while (cur->next) cur = cur->next;
    cur->next = namelist_single(name);
    return list;
}

void namelist_free(NameList *list) {
    NameList *cur = list;
    while (cur) {
        NameList *next = cur->next;
        free(cur->name);
        free(cur);
        cur = next;
    }
}

/* =========================================================
 * 5. Quad / TAC functions
 * =======================================================*/

void emit(const char *op,
          const char *arg1,
          const char *arg2,
          const char *result) {
    ensure_quad_capacity();

    Quad *q = &quad_array[quad_count++];
    q->op     = strdup_safe(op);
    q->arg1   = strdup_safe(arg1);
    q->arg2   = strdup_safe(arg2);
    q->result = strdup_safe(result);
}

int nextinstr(void) {
    return quad_count;
}

void print_quads(void) {
    for (int i = 0; i < quad_count; ++i) {
        Quad *q = &quad_array[i];

        const char *op  = q->op     ? q->op     : "";
        const char *a1  = q->arg1   ? q->arg1   : "";
        const char *a2  = q->arg2   ? q->arg2   : "";
        const char *res = q->result ? q->result : "";

        /* Spec: "<index>:\t<TAC>\n" */
        printf("%d:\t", i);

        if (strcmp(op, "goto") == 0) {
            printf("goto %s", res);
        } else if (strcmp(op, "ifFalse") == 0) {
            printf("ifFalse %s goto %s", a1, res);
        } else if (strncmp(op, "if", 2) == 0) {
            /* For any future comparison-based conditionals */
            printf("%s %s, %s goto %s", op, a1, a2, res);
        } else if (strcmp(op, "param") == 0) {
            printf("param %s", a1);
        } else if (strcmp(op, "call") == 0) {
            if (res[0] == '\0') {
                /* procedure call, e.g., writeln */
                printf("call %s, %s", a1, a2);
            } else {
                /* function call with return */
                printf("%s = call %s, %s", res, a1, a2);
            }
        } else if (strcmp(op, "return") == 0) {
            if (a1[0] == '\0') {
                printf("return");
            } else {
                printf("return %s", a1);
            }
        } else if (strcmp(op, "=[]") == 0) {
            printf("%s = %s[%s]", res, a1, a2);
        } else if (strcmp(op, "[]=") == 0) {
            printf("%s[%s] = %s", res, a1, a2);
        } else if (op[0] == '\0' || strcmp(op, "=") == 0 || a2[0] == '\0') {
            /* copy or unary op */
            if (op[0] == '\0' || strcmp(op, "=") == 0) {
                printf("%s = %s", res, a1);
            } else {
                printf("%s = %s %s", res, op, a1);
            }
        } else {
            /* binary op: res = a1 op a2 */
            printf("%s = %s %s %s", res, a1, op, a2);
        }

        printf("\n");
    }
}

/* =========================================================
 * 6. Backpatching
 * =======================================================*/

IntList *makelist(int index) {
    IntList *node = (IntList *)malloc(sizeof(IntList));
    if (!node) {
        fprintf(stderr, "Out of memory in makelist\n");
        exit(1);
    }
    node->index = index;
    node->next  = NULL;
    return node;
}

IntList *merge(IntList *a, IntList *b) {
    if (!a) return b;
    if (!b) return a;
    IntList *cur = a;
    while (cur->next) cur = cur->next;
    cur->next = b;
    return a;
}

void backpatch(IntList *list, int target) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", target);
    for (IntList *cur = list; cur; cur = cur->next) {
        int idx = cur->index;
        if (idx >= 0 && idx < quad_count) {
            if (quad_array[idx].result) free(quad_array[idx].result);
            quad_array[idx].result = strdup_safe(buf);
        }
    }
}

/* =========================================================
 * 7. Init / finalize & main
 * =======================================================*/

void translator_init(void) {
    globalST  = symtab_create("global", NULL);
    currentST = globalST;
    temp_counter = 0;

    quad_array    = NULL;
    quad_count    = 0;
    quad_capacity = 0;
}

void translator_finalize(void) {
    /* Free quads */
    for (int i = 0; i < quad_count; ++i) {
        free(quad_array[i].op);
        free(quad_array[i].arg1);
        free(quad_array[i].arg2);
        free(quad_array[i].result);
    }
    free(quad_array);

    /* Minimal ST cleanup: only global for now */
    if (globalST) {
        for (int i = 0; i < globalST->count; ++i) {
            Symbol *sym = globalST->symbols[i];
            free(sym->name);
            /* not recursively freeing nested tables (ok for PA3) */
            free(sym);
        }
        free(globalST->symbols);
        free(globalST->name);
        free(globalST);
    }

    globalST  = NULL;
    currentST = NULL;
}

/* Bison parser entry point */
extern int yyparse(void);

int main(void) {
    translator_init();

    if (yyparse() == 0) {
        /* Only print on successful parse */
        symtab_print(globalST);
        print_quads();
    }

    translator_finalize();
    return 0;
}
