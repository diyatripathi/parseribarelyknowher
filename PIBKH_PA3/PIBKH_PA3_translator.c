#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "PIBKH_PA3_translator.h"

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
            /* For PA3/PA4 it's fine to just return the existing symbol. */
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

    /* 3. Ensure capacity and insert */
    ensure_symbol_capacity(st);
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
    /* Match the spec: ST:<name-of-ST>, Parent:<null or name-of-parent> */
    printf("ST:%s, Parent:%s\n",
           st->name,
           (st->parent ? st->parent->name : "null"));
    printf("--------------------\n");

    for (int i = 0; i < st->count; ++i) {
        Symbol *sym = st->symbols[i];

        /* Hide temporaries from printed table */
        if (sym->kind == SYM_TEMP) continue;

        const char *scope = scope_string(sym, st);

        printf("%s, %s, %s, %s\n",
               sym->name,
               type_to_string(sym->type),
               scope,
               (sym->nested ? sym->nested->name : "null"));
    }

    /* Closing line as shown in the assignment's Output Format */
    printf("--------------------\n\n");

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

/* helper: is result a numeric label (all digits)? */
static int is_numeric_label(const char *s) {
    if (!s || !*s) return 0;
    for (const char *p = s; *p; ++p) {
        if (*p < '0' || *p > '9') return 0;
    }
    return 1;
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

        /* Completely empty quad: just a label / no-op line (e.g., the final label). */
        if (op[0] == '\0' && a1[0] == '\0' &&
            a2[0] == '\0' && res[0] == '\0') {
            /* Print nothing after the index. */
        }
        else if (strcmp(op, "goto") == 0) {
            printf("goto %s", res);
        }
        else if (strcmp(op, "ifFalse") == 0) {
            /* Value-based conditional jump: ifFalse x goto L */
            printf("ifFalse %s goto %s", a1, res);
        }
        else if (strcmp(op, "if") == 0 && a2[0] == '\0') {
            /* Value-based conditional jump: if x goto L */
            printf("if %s goto %s", a1, res);
        }
        else if (strncmp(op, "if", 2) == 0 && strlen(op) > 2) {
            /* Ops like "if<=", "if>", etc.: if x relop y goto L */
            const char *rel = op + 2;
            printf("if %s %s %s goto %s", a1, rel, a2, res);
        }
        else if ((strcmp(op, "<")  == 0 || strcmp(op, "<=") == 0 ||
                  strcmp(op, ">")  == 0 || strcmp(op, ">=") == 0 ||
                  strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) &&
                 is_numeric_label(res)) {
            /* Comparison-based conditional jump: if x relop y goto L */
            printf("if %s %s %s goto %s", a1, op, a2, res);
        }
        else if (strcmp(op, "param") == 0) {
            printf("param %s", a1);
        }
        else if (strcmp(op, "call") == 0) {
            if (res[0] == '\0') {
                /* procedure call */
                printf("call %s, %s", a1, a2);
            } else {
                /* function call with return */
                printf("%s = call %s, %s", res, a1, a2);
            }
        }
        else if (strcmp(op, "return") == 0) {
            if (a1[0] == '\0') {
                printf("return");
            } else {
                printf("return %s", a1);
            }
        }
        else if (strcmp(op, "read") == 0) {
            printf("read %s", a1);
        }
        else if (strcmp(op, "print") == 0) {
            printf("print %s", a1);
        }
        else if (strcmp(op, "stop") == 0) {
            printf("stop");
        }
        else if (strcmp(op, "=[]") == 0) {
            printf("%s = %s[%s]", res, a1, a2);
        }
        else if (strcmp(op, "[]=") == 0) {
            printf("%s[%s] = %s", res, a1, a2);
        }
        else if (op[0] == '\0' || strcmp(op, "=") == 0) {
            printf("%s = %s", res, a1);
        }
        else if (a2[0] == '\0') {
            printf("%s = %s %s", res, op, a1);
        }
        else {
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
 * 8. Target code generation: x86 / IA-32 (AT&T syntax)
 * =======================================================*/

/* ---------- Function + string-constant metadata ---------- */

typedef struct {
    char *lit;    /* literal as seen in TAC, including single quotes */
    char *label;  /* assembly label, e.g., .LC_str_0 */
} StringConst;

typedef struct {
    Symbol      *sym;        /* function symbol in globalST */
    SymbolTable *st;         /* nested symbol table */
    int          start_quad; /* inclusive */
    int          end_quad;   /* exclusive */
    int          frame_size; /* bytes of locals + temps */
} FuncInfo;

static StringConst *str_consts   = NULL;
static int          str_count    = 0;
static int          str_capacity = 0;

static FuncInfo    *funcs        = NULL;
static int          func_count   = 0;
static int          func_cap     = 0;

/* main's quad range (the program body after functions) */
static int main_start = 0;
static int main_end   = 0;

/* Labels for I/O format strings */
static const char *fmt_read_int_label     = "_fmt_read_int";
static const char *fmt_print_int_label    = "_fmt_print_int";
static const char *fmt_print_string_label = "_fmt_print_string";

/* ---------- Small helpers ---------- */

static void ensure_str_capacity(void) {
    if (str_capacity == 0) {
        str_capacity = 8;
        str_consts   = (StringConst *)malloc(str_capacity * sizeof(StringConst));
    } else if (str_count >= str_capacity) {
        str_capacity *= 2;
        str_consts = (StringConst *)realloc(str_consts,
                                            str_capacity * sizeof(StringConst));
    }
    if (!str_consts) {
        fprintf(stderr, "Out of memory in ensure_str_capacity\n");
        exit(1);
    }
}

static void ensure_func_capacity(void) {
    if (func_cap == 0) {
        func_cap = 4;
        funcs    = (FuncInfo *)malloc(func_cap * sizeof(FuncInfo));
    } else if (func_count >= func_cap) {
        func_cap *= 2;
        funcs = (FuncInfo *)realloc(funcs, func_cap * sizeof(FuncInfo));
    }
    if (!funcs) {
        fprintf(stderr, "Out of memory in ensure_func_capacity\n");
        exit(1);
    }
}

/* numeric literal? (simple signed integer) */
static int is_number_lit(const char *s) {
    if (!s || !*s) return 0;
    const char *p = s;
    if (*p == '+' || *p == '-') ++p;
    if (!isdigit((unsigned char)*p)) return 0;
    for (; *p; ++p) {
        if (!isdigit((unsigned char)*p)) return 0;
    }
    return 1;
}

/* string literal in nanoPascal: '...' (no embedded newlines) */
static int is_string_lit(const char *s) {
    if (!s) return 0;
    size_t len = strlen(s);
    return (len >= 2 && s[0] == '\'' && s[len-1] == '\'');
}

/* Intern a string literal and return its label (e.g. .LC_str_0) */
static const char *intern_string_literal(const char *lit) {
    if (!is_string_lit(lit)) return NULL;
    for (int i = 0; i < str_count; ++i) {
        if (strcmp(str_consts[i].lit, lit) == 0)
            return str_consts[i].label;
    }
    ensure_str_capacity();
    str_consts[str_count].lit   = strdup_safe(lit);
    char buf[32];
    snprintf(buf, sizeof(buf), ".LC_str_%d", str_count);
    str_consts[str_count].label = strdup_safe(buf);
    ++str_count;
    return str_consts[str_count - 1].label;
}

/* Find symbol like symtab_lookup, but also tell which table it came from */
static Symbol *lookup_with_owner(SymbolTable *start,
                                 const char *name,
                                 SymbolTable **owner_out) {
    SymbolTable *cur = start;
    while (cur) {
        for (int i = 0; i < cur->count; ++i) {
            Symbol *sym = cur->symbols[i];
            if (strcmp(sym->name, name) == 0) {
                if (owner_out) *owner_out = cur;
                return sym;
            }
        }
        cur = cur->parent;
    }
    if (owner_out) *owner_out = NULL;
    return NULL;
}

/* Convert string to int, -1 on failure */
static int str_to_int(const char *s) {
    if (!s || !*s) return -1;
    char *endp = NULL;
    long v = strtol(s, &endp, 10);
    if (*endp != '\0') return -1;
    return (int)v;
}

/* ---------- Frame layout & function registration ---------- */

/* Called from .y: function_header */
void register_function(Symbol *f, SymbolTable *st, int start_quad) {
    ensure_func_capacity();
    funcs[func_count].sym        = f;
    funcs[func_count].st         = st;
    funcs[func_count].start_quad = start_quad;
    funcs[func_count].end_quad   = -1;
    funcs[func_count].frame_size = 0;
    ++func_count;
}

/* Called from .y: function_declaration */
void function_set_end(Symbol *f, int end_quad) {
    for (int i = 0; i < func_count; ++i) {
        if (funcs[i].sym == f) {
            funcs[i].end_quad = end_quad;
            return;
        }
    }
}

/* Lay out parameters and locals for one function */
static void assign_frame_offsets(FuncInfo *fn) {
    SymbolTable *st = fn->st;
    int local_offset = 0; /* grows positively, used as -local_offset */
    int param_offset = 8; /* first param at 8(%ebp) */

    /* Parameters in order of appearance */
    for (int i = 0; i < st->count; ++i) {
        Symbol *sym = st->symbols[i];
        if (sym->kind == SYM_PARAM) {
            sym->offset = param_offset;
            param_offset += type_size(sym->type);
        }
    }

    /* Locals and temps at negative offsets */
    for (int i = 0; i < st->count; ++i) {
        Symbol *sym = st->symbols[i];
        if (sym->kind == SYM_VAR || sym->kind == SYM_TEMP) {
            local_offset += type_size(sym->type);
            sym->offset = -local_offset;
        }
    }

    fn->frame_size = local_offset;
}

/* ---------- Label analysis within a quad range ---------- */

static void compute_labels_for_range(int start, int end, unsigned char *is_label) {
    for (int i = start; i < end; ++i) {
        Quad *q = &quad_array[i];
        const char *op  = q->op     ? q->op     : "";
        const char *res = q->result ? q->result : "";

        int L = -1;

        if (strcmp(op, "goto") == 0 ||
            strcmp(op, "ifFalse") == 0 ||
            strcmp(op, "if") == 0 ||
            (strncmp(op, "if", 2) == 0 && strlen(op) > 2)) {
            L = str_to_int(res);
        }
        else if ((strcmp(op, "<")  == 0 || strcmp(op, "<=") == 0 ||
                  strcmp(op, ">")  == 0 || strcmp(op, ">=") == 0 ||
                  strcmp(op, "==") == 0 || strcmp(op, "!=") == 0) &&
                 is_numeric_label(res)) {
            L = str_to_int(res);
        }

        if (L >= start && L < end) {
            is_label[L - start] = 1;
        }
    }
}

/* ---------- Operand load/store helpers ---------- */

/* Load an operand (var / temp / const / string literal) into a register */
static void gen_load_operand(FILE *out,
                             SymbolTable *scope,
                             const char *operand,
                             const char *reg) {
    if (!operand || operand[0] == '\0') {
        fprintf(out, "    movl $0, %%%s    # empty operand\n", reg);
        return;
    }

    if (is_number_lit(operand)) {
        fprintf(out, "    movl $%s, %%%s\n", operand, reg);
        return;
    }

    if (is_string_lit(operand)) {
        const char *lab = intern_string_literal(operand);
        fprintf(out, "    movl $%s, %%%s\n", lab, reg);
        return;
    }

    /* Look up the symbol */
    SymbolTable *owner = NULL;
    Symbol *sym = lookup_with_owner(scope, operand, &owner);
    if (!sym) {
        fprintf(out, "    movl $0, %%%s    # ERROR: unknown symbol '%s'\n", reg, operand);
        return;
    }

    /* FIXED: Check if it's a global VAR (not temp) */
    if (owner == globalST && sym->kind == SYM_VAR) {
        fprintf(out, "    movl %s, %%%s\n", sym->name, reg);
    } else if (sym->kind == SYM_PARAM || sym->kind == SYM_VAR || sym->kind == SYM_TEMP) {
        /* Local variable, parameter, or temp - use offset from %ebp */
        fprintf(out, "    movl %d(%%ebp), %%%s\n", sym->offset, reg);
    } else {
        fprintf(out, "    movl $0, %%%s    # ERROR: unknown symbol kind '%s'\n", reg, operand);
    }
}

/* Store a register into a variable/temporary */
static void gen_store_result(FILE *out,
                             SymbolTable *scope,
                             const char *reg,
                             const char *dest) {
    if (!dest || dest[0] == '\0') return;
    if (is_string_lit(dest) || is_number_lit(dest)) {
        return;
    }

    SymbolTable *owner = NULL;
    Symbol *sym = lookup_with_owner(scope, dest, &owner);
    if (!sym) return;

    /* FIXED: Check if it's a global VAR (not temp) */
    if (owner == globalST && sym->kind == SYM_VAR) {
        fprintf(out, "    movl %%%s, %s\n", reg, sym->name);
    } else if (sym->kind == SYM_PARAM || sym->kind == SYM_VAR || sym->kind == SYM_TEMP) {
        /* Local variable, parameter, or temp - use offset */
        fprintf(out, "    movl %%%s, %d(%%ebp)\n", reg, sym->offset);
    }
}


/* Relational operation producing 0/1 in dest (x < y, etc.) */
static void gen_rel_to_bool(FILE *out,
                            SymbolTable *scope,
                            const char *rel,
                            const char *a1,
                            const char *a2,
                            const char *dest) {
    gen_load_operand(out, scope, a1, "eax");
    gen_load_operand(out, scope, a2, "ecx");
    fprintf(out, "    cmpl %%ecx, %%eax\n");

    const char *set_inst = "sete";
    if      (strcmp(rel, "<")  == 0) set_inst = "setl";
    else if (strcmp(rel, "<=") == 0) set_inst = "setle";
    else if (strcmp(rel, ">")  == 0) set_inst = "setg";
    else if (strcmp(rel, ">=") == 0) set_inst = "setge";
    else if (strcmp(rel, "==") == 0) set_inst = "sete";
    else if (strcmp(rel, "!=") == 0 || strcmp(rel, "<>") == 0) set_inst = "setne";

    fprintf(out, "    %s %%al\n", set_inst);
    fprintf(out, "    movzbl %%al, %%eax\n");
    gen_store_result(out, scope, "eax", dest);
}

/* Conditional jump based on relational test (no boolean temp) */
static void gen_if_rel_jump(FILE *out,
                            SymbolTable *scope,
                            const char *rel,
                            const char *a1,
                            const char *a2,
                            int target_label) {
    gen_load_operand(out, scope, a1, "eax");
    gen_load_operand(out, scope, a2, "ecx");
    fprintf(out, "    cmpl %%ecx, %%eax\n");

    const char *jmp = "je";
    if      (strcmp(rel, "<")  == 0) jmp = "jl";
    else if (strcmp(rel, "<=") == 0) jmp = "jle";
    else if (strcmp(rel, ">")  == 0) jmp = "jg";
    else if (strcmp(rel, ">=") == 0) jmp = "jge";
    else if (strcmp(rel, "==") == 0) jmp = "je";
    else if (strcmp(rel, "!=") == 0 || strcmp(rel, "<>") == 0) jmp = "jne";

    fprintf(out, "    %s .L%d\n", jmp, target_label);;  // FIXED: Added dot prefix
}


/* ---------- I/O helpers (read/print) ---------- */

static void gen_read(FILE *out, SymbolTable *scope, const char *name) {
    SymbolTable *owner = NULL;
    Symbol *sym = lookup_with_owner(scope, name, &owner);
    if (!sym) return;

    /* Only INTEGER supported here */
    if (sym->type != TYPE_INT) {
        fprintf(out, "    # read for non-int not implemented\n");
        return;
    }

    if (owner == globalST) {
        fprintf(out, "    leal %s, %%eax\n", sym->name);
    } else {
        fprintf(out, "    leal %d(%%ebp), %%eax\n", sym->offset);
    }
    fprintf(out, "    pushl %%eax\n");
    fprintf(out, "    pushl $%s\n", fmt_read_int_label);
    fprintf(out, "    call scanf\n");
    fprintf(out, "    addl $8, %%esp\n");
}

static void gen_print(FILE *out, SymbolTable *scope, const char *name) {
    SymbolTable *owner = NULL;
    Symbol *sym = lookup_with_owner(scope, name, &owner);
    if (!sym) {
        /* Might be a temp or constant folded away; fall back to int load */
        gen_load_operand(out, scope, name, "eax");
        fprintf(out, "    pushl %%eax\n");
        fprintf(out, "    pushl $%s\n", fmt_print_int_label);
        fprintf(out, "    call printf\n");
        fprintf(out, "    addl $8, %%esp\n");
        return;
    }

    if (sym->type == TYPE_INT) {
        gen_load_operand(out, scope, name, "eax");
        fprintf(out, "    pushl %%eax\n");
        fprintf(out, "    pushl $%s\n", fmt_print_int_label);
        fprintf(out, "    call printf\n");
        fprintf(out, "    addl $8, %%esp\n");
    } else if (sym->type == TYPE_STRING) {
        gen_load_operand(out, scope, name, "eax");
        fprintf(out, "    pushl %%eax\n");
        fprintf(out, "    pushl $%s\n", fmt_print_string_label);
        fprintf(out, "    call printf\n");
        fprintf(out, "    addl $8, %%esp\n");
    } else {
        fprintf(out, "    # print: unsupported type for %s\n", name);
    }
}

/* ---------- Translation of a single quad (except param/call) ---------- */

static void translate_quad_core(FILE *out,
                                SymbolTable *scope,
                                const char  *func_name,
                                Quad        *q) {
    const char *op  = q->op     ? q->op     : "";
    const char *a1  = q->arg1   ? q->arg1   : "";
    const char *a2  = q->arg2   ? q->arg2   : "";
    const char *res = q->result ? q->result : "";

    /* Copy assignment: x = y or temp = const */
    if (op[0] == '\0' || strcmp(op, "=") == 0) {
        gen_load_operand(out, scope, a1, "eax");
        gen_store_result(out, scope, "eax", res);
    }
    /* Unary minus: t = uminus x */
    else if (strcmp(op, "uminus") == 0) {
        gen_load_operand(out, scope, a1, "eax");
        fprintf(out, "    negl %%eax\n");
        gen_store_result(out, scope, "eax", res);
    }
    /* Binary arithmetic: +, -, *, / */
    else if (strcmp(op, "+") == 0 ||
             strcmp(op, "-") == 0 ||
             strcmp(op, "*") == 0 ||
             strcmp(op, "/") == 0) {

        gen_load_operand(out, scope, a1, "eax");

        if (strcmp(op, "+") == 0) {
            if (is_number_lit(a2)) {
                fprintf(out, "    addl $%s, %%eax\n", a2);
            } else {
                gen_load_operand(out, scope, a2, "ecx");
                fprintf(out, "    addl %%ecx, %%eax\n");
            }
        } else if (strcmp(op, "-") == 0) {
            if (is_number_lit(a2)) {
                fprintf(out, "    subl $%s, %%eax\n", a2);
            } else {
                gen_load_operand(out, scope, a2, "ecx");
                fprintf(out, "    subl %%ecx, %%eax\n");
            }
        } else if (strcmp(op, "*") == 0) {
            if (is_number_lit(a2)) {
                fprintf(out, "    imull $%s, %%eax\n", a2);
            } else {
                gen_load_operand(out, scope, a2, "ecx");
                fprintf(out, "    imull %%ecx, %%eax\n");
            }
        } else { /* division */
            gen_load_operand(out, scope, a2, "ecx");
            fprintf(out, "    cltd\n");
            fprintf(out, "    idivl %%ecx\n");
        }

        gen_store_result(out, scope, "eax", res);
    }
    /* FIXED: Relational operations - check if it's a conditional jump or boolean assignment */
    else if (strcmp(op, "<")  == 0 || strcmp(op, "<=") == 0 ||
             strcmp(op, ">")  == 0 || strcmp(op, ">=") == 0 ||
             strcmp(op, "==") == 0 || strcmp(op, "!=") == 0 ||
             strcmp(op, "<>") == 0) {

        /* Check if this is a conditional jump (result is a numeric label) */
        if (is_numeric_label(res)) {
            int L = str_to_int(res);
            gen_if_rel_jump(out, scope, op, a1, a2, L);
        } else {
            /* Boolean assignment: t = (a < b) */
            gen_rel_to_bool(out, scope, op, a1, a2, res);
        }
    }
    /* Goto */
    else if (strcmp(op, "goto") == 0) {
        int L = str_to_int(res);
        fprintf(out, "    jmp .L%d\n", L);  // FIXED: Added dot prefix
    }
    /* Value-based conditionals */
    else if (strcmp(op, "ifFalse") == 0) {
        int L = str_to_int(res);
        gen_load_operand(out, scope, a1, "eax");
        fprintf(out, "    cmpl $0, %%eax\n");
        fprintf(out, "    je .L%d\n", L);  // FIXED: Added dot prefix
    }
    else if (strcmp(op, "if") == 0 && a2[0] == '\0') {
        int L = str_to_int(res);
        gen_load_operand(out, scope, a1, "eax");
        fprintf(out, "    cmpl $0, %%eax\n");
        fprintf(out, "    jne .L%d\n", L);  // FIXED: Added dot prefix
    }
    /* Relational conditionals encoded as op == "if<", "if<=", etc. */
    else if (strncmp(op, "if", 2) == 0 && strlen(op) > 2) {
        const char *rel = op + 2; /* e.g. "<=", "==" */
        int L = str_to_int(res);
        gen_if_rel_jump(out, scope, rel, a1, a2, L);
    }
    /* I/O and stop */
    else if (strcmp(op, "read") == 0) {
        gen_read(out, scope, a1);
    }
    else if (strcmp(op, "print") == 0) {
        gen_print(out, scope, a1);
    }
    else if (strcmp(op, "stop") == 0) {
        /* Only meaningful in main; just jump to epilogue */
        fprintf(out, "    jmp .Lret_%s\n", func_name);
    }
    /* Return */
    else if (strcmp(op, "return") == 0) {
        if (a1[0] != '\0') {
            gen_load_operand(out, scope, a1, "eax");
        }
        fprintf(out, "    jmp .Lret_%s\n", func_name);
    }
    else {
        fprintf(out, "    # unhandled quad op '%s'\n", op);
    }
}

/* ---------- Translation of a function's quad range ---------- */

static void translate_function(FILE *out, FuncInfo *fn) {
    SymbolTable *scope = fn->st;
    const char *fname  = fn->sym->name;
    int start = fn->start_quad;
    int end   = fn->end_quad;

    /* Mark label positions */
    int n = end - start;
    unsigned char *is_label = (unsigned char *)calloc(n, sizeof(unsigned char));
    if (!is_label) {
        fprintf(stderr, "Out of memory in translate_function\n");
        exit(1);
    }
    compute_labels_for_range(start, end, is_label);

    /* Prologue */
    fprintf(out, "\n    .globl %s\n", fname);
    fprintf(out, "%s:\n", fname);
    fprintf(out, "    pushl %%ebp\n");
    fprintf(out, "    movl %%esp, %%ebp\n");
    if (fn->frame_size > 0) {
        fprintf(out, "    subl $%d, %%esp\n", fn->frame_size);
    }
    /* Default return value = 0 (overwritten on return v) */
    fprintf(out, "    movl $0, %%eax\n");

    /* Body */
    for (int i = start; i < end; ++i) {
        // FIXED: Emit label with dot prefix
        if (is_label[i - start]) {
            fprintf(out, ".L%d:\n", i);
        }

        Quad *q = &quad_array[i];
        const char *op = q->op ? q->op : "";

        /* param/call pair: handle params at call time */
        if (strcmp(op, "param") == 0) {
            /* Handled by the subsequent call quad; nothing here */
            continue;
        }

        if (strcmp(op, "call") == 0) {
            /* The number of params is in arg2 */
            int nparams = str_to_int(q->arg2 ? q->arg2 : "0");
            int first_param = i - nparams;

            /* Push args right-to-left */
            for (int k = i - 1; k >= first_param; --k) {
                Quad *pq = &quad_array[k];
                if (!pq->op || strcmp(pq->op, "param") != 0) continue;
                gen_load_operand(out, scope, pq->arg1, "eax");
                fprintf(out, "    pushl %%eax\n");
            }

            fprintf(out, "    call %s\n", q->arg1 ? q->arg1 : "");
            if (nparams > 0) {
                fprintf(out, "    addl $%d, %%esp\n", 4 * nparams);
            }

            /* Store return value if any */
            if (q->result && q->result[0] != '\0') {
                gen_store_result(out, scope, "eax", q->result);
            }
            continue;
        }

        /* Everything else is handled by the core translator */
        translate_quad_core(out, scope, fname, q);
    }

    /* Epilogue */
    fprintf(out, ".Lret_%s:\n", fname);
    fprintf(out, "    leave\n");
    fprintf(out, "    ret\n");

    free(is_label);
}


/* ---------- Translation of main (program body) ---------- */
static void translate_main(FILE *out) {
    /* Calculate frame size for main's locals/temps */
    int local_offset = 0;
    for (int i = 0; i < globalST->count; ++i) {
        Symbol *sym = globalST->symbols[i];
        if (sym->kind == SYM_TEMP) {
            local_offset += type_size(sym->type);
            sym->offset = -local_offset;
        }
    }

    FuncInfo mainFn;
    Symbol   dummy;
    dummy.name   = "main";
    dummy.type   = TYPE_INT;
    dummy.kind   = SYM_FUNC;
    dummy.size   = 0;
    dummy.offset = 0;
    dummy.nested = NULL;

    mainFn.sym        = &dummy;
    mainFn.st         = globalST;
    mainFn.start_quad = main_start;
    mainFn.end_quad   = main_end;
    mainFn.frame_size = local_offset;  // FIXED: Use calculated size

    translate_function(out, &mainFn);
}


/* ---------- Top-level driver: generate_x86 ---------- */

void generate_x86(FILE *out) {
    /* 1. Layout frames for all user-defined functions */
    for (int i = 0; i < func_count; ++i) {
        if (funcs[i].end_quad < 0) {
            funcs[i].end_quad = funcs[i].start_quad; /* empty body fallback */
        }
        assign_frame_offsets(&funcs[i]);
    }

    /* 2. Determine main() quad range: quads after the last function body */
    int max_end = 0;
    for (int i = 0; i < func_count; ++i) {
        if (funcs[i].end_quad > max_end) max_end = funcs[i].end_quad;
    }
    main_start = max_end;
    main_end   = quad_count; /* include final 'stop' quad */

    /* 3. Pre-scan quads to collect string literals */
    for (int i = 0; i < quad_count; ++i) {
        Quad *q = &quad_array[i];
        if (q->arg1 && is_string_lit(q->arg1)) intern_string_literal(q->arg1);
        if (q->arg2 && is_string_lit(q->arg2)) intern_string_literal(q->arg2);
        if (q->result && is_string_lit(q->result)) intern_string_literal(q->result);
    }

    /* 4. Emit data section: globals + string constants + I/O formats */
    fprintf(out, "    .data\n");

    /* Global (static) variables ONLY (no temps) */
    for (int i = 0; i < globalST->count; ++i) {
        Symbol *sym = globalST->symbols[i];
        if (sym->kind == SYM_VAR) {  // FIXED: Only VAR, not TEMP
            fprintf(out, "    .globl %s\n", sym->name);
            fprintf(out, "%s:\n", sym->name);
            fprintf(out, "    .long 0\n");
        }
    }

    /* String literals */
    for (int i = 0; i < str_count; ++i) {
        const char *lab = str_consts[i].label;
        const char *lit = str_consts[i].lit; /* '... ' */

        fprintf(out, "%s:\n", lab);
        fputs("    .string \"", out);
        size_t len = strlen(lit);
        for (size_t j = 1; j + 1 < len; ++j) {
            char c = lit[j];
            if (c == '"' || c == '\\') fputc('\\', out);
            if (c == '\n') {
                fputs("\\n", out);
            } else {
                fputc(c, out);
            }
        }
        fputs("\"\n", out);
    }

    /* I/O format strings */
    fprintf(out, "%s:\n", fmt_read_int_label);
    fprintf(out, "    .string \"%%d\"\n");
    fprintf(out, "%s:\n", fmt_print_int_label);
    fprintf(out, "    .string \"%%d\"\n");
    fprintf(out, "%s:\n", fmt_print_string_label);
    fprintf(out, "    .string \"%%s\"\n");

    /* 5. Text section and externs */
    fprintf(out, "\n    .text\n");
    fprintf(out, "    .extern printf\n");
    fprintf(out, "    .extern scanf\n");

    /* 6. Emit all user-defined functions */
    for (int i = 0; i < func_count; ++i) {
        translate_function(out, &funcs[i]);
    }

    /* 7. Emit main (program body) */
    translate_main(out);
}

/* =========================================================
 * 9. Init / finalize & main
 * =======================================================*/

void translator_init(void) {
    globalST  = symtab_create("global", NULL);
    currentST = globalST;
    temp_counter = 0;

    quad_array    = NULL;
    quad_count    = 0;
    quad_capacity = 0;

    /* reset PA4 metadata */
    str_consts   = NULL;
    str_count    = 0;
    str_capacity = 0;
    funcs        = NULL;
    func_count   = 0;
    func_cap     = 0;
    main_start   = 0;
    main_end     = 0;
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

    /* Free PA4 metadata */
    for (int i = 0; i < str_count; ++i) {
        free(str_consts[i].lit);
        free(str_consts[i].label);
    }
    free(str_consts);
    free(funcs);

    /* Minimal ST cleanup: only global for now */
    if (globalST) {
        for (int i = 0; i < globalST->count; ++i) {
            Symbol *sym = globalST->symbols[i];
            free(sym->name);
            /* not recursively freeing nested tables (ok for this assignment) */
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
        /* End-of-program marker in TAC */
        emit("stop", "", "", "");

        /* Optional debugging:
        symtab_print(globalST);
        print_quads();
        */

        /* Generate x86 / IA-32 assembly to stdout */
        generate_x86(stdout);
    }

    translator_finalize();
    return 0;
}
