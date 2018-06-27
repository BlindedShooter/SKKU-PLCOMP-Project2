
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

void get_token(char *str, vector<Token> *token_list) {
    int i, n, tn;
    char token[255] = {0};
    Token new_token;
    n = strlen(str);

    tn = 0;
    for (i = 0; i <= n; i++) {
        if (is_terminal(str[i]) && tn > 0) {
            token[tn] = '\0';

            if (strcmp(token, "INT") == 0) new_token.type = INT;
            else if (strcmp(token, "CHAR") == 0) new_token.type = CHAR;
            else if (strcmp(token, "IF") == 0) new_token.type = IF;
            else if (strcmp(token, "THEN") == 0) new_token.type = THEN;
            else if (strcmp(token, "ELSE") == 0) new_token.type = ELSE;
            else if (strcmp(token, "WHILE") == 0) new_token.type = WHILE;
            else if (strcmp(token, "RETURN") == 0) new_token.type = RETURN;
            else if (isdigit(token[0])) {
                new_token.type = NUM;
                new_token.value_num = atoi(token);  // can be hazardous; what if 12abc?
            } else {
                new_token.type = WORD;
                strcpy_s(new_token.value_word, token);
            }

            token_list->push_back(new_token);
            tn = 0;
        }

        switch (str[i]) {
            case '(':
                new_token.type = PHL;
                token_list->push_back(new_token);
                break;
            case ')':
                new_token.type = PHR;
                token_list->push_back(new_token);
                break;
            case ';':
                new_token.type = SEMICOLON;
                token_list->push_back(new_token);
                break;
            case ',':
                new_token.type = COMMA;
                token_list->push_back(new_token);
                break;
            case '{':
                new_token.type = MPHL;
                token_list->push_back(new_token);
                break;
            case '}':
                new_token.type = MPHR;
                token_list->push_back(new_token);
                break;
            case '=':
                new_token.type = EQUAL;
                token_list->push_back(new_token);
                break;
            case '>':
                new_token.type = GREATER;
                token_list->push_back(new_token);
                break;
            case '<':
                new_token.type = LESS;
                token_list->push_back(new_token);
                break;
            case '+':
                new_token.type = PLUS;
                token_list->push_back(new_token);
                break;
            case '*':
                new_token.type = MUL;
                token_list->push_back(new_token);
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
    vector<Token> token_list;
    FILE *in;
    fopen_s(&in, file_name, "r");

    if (in != nullptr) {
        char line[255];

        while (!feof(in)) {
            fgets(line, sizeof(line), in);
            get_token(line, &token_list);
        }

        fclose(in);
    } else {
        printf("Input file error.\n");
    }

    for (auto &i : token_list) {
        if (i.type == WORD) {
            printf("%d %s\n", i.type, i.value_word);
        } else if (i.type == NUM) {
            printf("%d %d\n", i.type, i.value_num);
        } else {
            printf("%d\n", i.type);
        }
    }
}
