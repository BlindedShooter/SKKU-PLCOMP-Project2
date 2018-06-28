#ifndef SKKU_PLCOMP_PROJECT2_MAIN_SCANNER_H
#define SKKU_PLCOMP_PROJECT2_MAIN_SCANNER_H

#include "symbol_table.h"

bool is_terminal(char key);

void get_token(char *str);

void scanner(char *file_name);


#endif //SKKU_PLCOMP_PROJECT2_MAIN_SCANNER_H
