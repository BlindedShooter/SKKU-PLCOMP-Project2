#ifndef SKKU_PLCOMP_PROJECT2_MAIN_DECLS_H
#define SKKU_PLCOMP_PROJECT2_MAIN_DECLS_H

#include <cstring>
#include <algorithm>
#include <vector>

#define PTABLE_SIZE 2048

using namespace std;

typedef enum {
    SHIFT = 1000,
    REDUCE,
    GOTO,
    ACCEPT,

    PROGS,        // prog'
    PROG,        // prog
    DECLS,        // decls
    DECL,        // decl
    WORDS,        // words
    VTYPE,        // vtype
    BLOCK,        // block
    SLIST,        // slist
    STAT,        // stat
    COND,        // cond
    EXPR,        // expr
    TERM,        // term
    FACT,        // fact

    PHL,        // (
    PHR,        // )
    SEMICOLON,    // ;
    COMMA,        // ,
    INT,        // INT
    CHAR,        // CHAR
    MPHL,        // {
    MPHR,        // }
    IF,            // IF
    THEN,        // THEN
    ELSE,        // ELSE
    WHILE,        // WHILE
    EQUAL,        // =
    RETURN,        // RETURN
    GREATER,    // >
    LESS,        // <
    PLUS,        // +
    MUL,        // *
    WORD,        // word
    NUM,        // num
    END,        // $
    NONE
} type_t;

typedef struct _Token {
    int type;
    char *value;

    _Token() : type(NONE), value(nullptr) {}

    _Token(int type_, char *value_) : type(type_), value(value_) {}
} Token;

typedef struct _Ptable {
    int state;
    int token;
    int action;
    int next;
} Ptable;

typedef struct _Rtable {
	int pop_count;
	int push;
} Rtable;

extern vector<Token> token_list;
extern const int ptable_n;
extern Ptable ptable[];
extern Rtable rtable[];

const char *get_type_name(type_t type);

#endif //SKKU_PLCOMP_PROJECT2_MAIN_DECLS_H
