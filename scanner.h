#ifndef PROJECT_SCANNER_H
#define PROJECT_SCANNER_H

#include "decls.h"

using namespace std;


bool is_terminal(char key);

void get_token(char *str, vector<Token> *token_list);

void scanner(char *file_name);

#endif //PROJECT_SCANNER_H
