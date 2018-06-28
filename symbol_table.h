#ifndef PROJECT_SYMBOL_TABLE_H
#define PROJECT_SYMBOL_TABLE_H

#include "decls.h"
#include <unordered_map>  // hash table

struct symbol_info {
    type_t type;
    size_t addr;
};
typedef unordered_map<std::string, symbol_info> symbol_table_t;

struct Scope {
    vector<Scope *> child;
    std::string name;
    Scope *parent;
    symbol_table_t symbol_table;
    size_t level;

    Scope();

    explicit Scope(Scope *parent_);

    Scope(Scope *parent_, const std::string &name_);

    ~Scope();
};

extern Scope *GLOBAL;
extern Scope *current_scope;

void enter_scope();

void exit_scope();

void enter_scope(const std::string &scope_name);

int insert_symbol(const std::string &name, type_t type);

/* Lookups Return NONE if there is no such symbol. */
symbol_info local_lookup(const std::string &name);

symbol_info lookup(const std::string &name);

#endif //PROJECT_SYMBOL_TABLE_H
