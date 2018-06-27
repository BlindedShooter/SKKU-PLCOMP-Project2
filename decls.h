#ifndef SKKU_PLCOMP_PROJECT2_MAIN_DECLS_H
#define SKKU_PLCOMP_PROJECT2_MAIN_DECLS_H

#include <cstring>
#include <algorithm>
#include <vector>

#define PTABLE_SIZE 2048

using namespace std;

enum {
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
};

typedef struct _Token {
    int type;
    int value_num;
    char value_word[255];
} Token;


typedef struct _Ptable {
    int state;
    int token;
    int action;
    int next;
} Ptable;

extern vector<Token> token_list;
extern const int ptable_n;
extern Ptable ptable[];

#endif //SKKU_PLCOMP_PROJECT2_MAIN_DECLS_H
