#include "scanner.h"

bool is_terminal(char key) {
    switch (key) {
        case '(':
        case ')':
        case ';':
        case ',':
        case '{':
        case '}':
        case '=':
        case '>':
        case '<':
        case '+':
        case '*':
        case ' ':
        case '\n':
        case '\t':
        case '\0':
            return true;
        default:
            return false;
    }
}

void get_token(char *str) {
    int i, n, tn;
    char token[255] = {0};
    type_t type;
    char *value = nullptr;
    n = strlen(str);

    tn = 0;
    for (i = 0; i <= n; i++) {
        if (is_terminal(str[i]) && tn > 0) {
            token[tn] = '\0';

            if (strcmp(token, "INT") == 0) type = INT;
            else if (strcmp(token, "CHAR") == 0) type = CHAR;
            else if (strcmp(token, "IF") == 0) type = IF;
            else if (strcmp(token, "THEN") == 0) type = THEN;
            else if (strcmp(token, "ELSE") == 0) type = ELSE;
            else if (strcmp(token, "WHILE") == 0) type = WHILE;
            else if (strcmp(token, "RETURN") == 0) type = RETURN;
            else if ('0' <= token[0] && token[0] <= '9') {
                type = NUM;
                value = _strdup(token);
            } else {
                type = WORD;
                value = _strdup(token);
            }

            token_list.emplace_back(type, value);
            tn = 0;
        }

        switch (str[i]) {
            case '(':
                type = PHL;
                token_list.emplace_back(type, nullptr);
                break;
            case ')':
                type = PHR;
                token_list.emplace_back(type, nullptr);
                break;
            case ';':
                type = SEMICOLON;
                token_list.emplace_back(type, nullptr);
                break;
            case ',':
                type = COMMA;
                token_list.emplace_back(type, nullptr);
                break;
            case '{':
                type = MPHL;
                token_list.emplace_back(type, nullptr);
                break;
            case '}':
                type = MPHR;
                token_list.emplace_back(type, nullptr);
                break;
            case '=':
                type = EQUAL;
                token_list.emplace_back(type, nullptr);
                break;
            case '>':
                type = GREATER;
                token_list.emplace_back(type, nullptr);
                break;
            case '<':
                type = LESS;
                token_list.emplace_back(type, nullptr);
                break;
            case '+':
                type = PLUS;
                token_list.emplace_back(type, nullptr);
                break;
            case '*':
                type = MUL;
                token_list.emplace_back(type, nullptr);
                break;

            case ' ':
            case '\n':
            case '\0':
            case '\t':
                break;

            default:
                token[tn++] = str[i];
                break;
        }
    }
}

void scanner(char *file_name) {
    FILE *in;
    fopen_s(&in, file_name, "r");

    if (in != NULL) {
        char line[255];

        while (!feof(in)) {
            fgets(line, sizeof(line), in);
            get_token(line);
        }

        fclose(in);
    } else {
        printf("Input file error.\n");
    }

    int n = token_list.size();
    reverse(token_list.begin(), token_list.end());

    for (int i = 0; i < n; i++) {
        printf("%s ", get_type_name(static_cast<type_t>(token_list[i].type)));
        if (token_list[i].type == WORD) {
            printf("%s\n", token_list[i].value);
        } else if (token_list[i].type == NUM) {
            printf("%s\n", token_list[i].value);
        } else {
            printf("\n");
        }
    }
}
