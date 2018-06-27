#include "parser.h"

void parser() {
    vector<Token> stack;
    Token temp_token, stack_token, input_token;
    bool error_check = false;

    temp_token.type = 0;
    stack.push_back(temp_token);

    while (true) {
        stack_token = stack.back();
        input_token = token_list.back();

        error_check = true;
        for (int i = 0; i < ptable_n; i++) {
            if (ptable[i].state == stack_token.type && ptable[i].token == input_token.type) {
                switch (ptable[i].action) {
                    case SHIFT:
                        stack.push_back(input_token);
                        temp_token.type = ptable[i].next;
                        stack.push_back(temp_token);
                        token_list.pop_back();
                        break;
                    case REDUCE:
                        break;
                    case GOTO:
                        break;
                    case ACCEPT:
                        break;
                }

                error_check = false;
                break;
            }
        }

        if (error_check) {
            printf("Compile error.\n");
            break;
        }
    }
}

