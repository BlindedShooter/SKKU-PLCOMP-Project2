#include "parser.h"

void parser() {
    vector<Token> stack;
    Token temp_token, stack_token, input_token;
    bool error_check = false;
	int previous_state;

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
					printf("SHIFT  %5d (%5d, %10s)\n", ptable[i].next, stack_token.type, get_type_name((type_t)(input_token.type)));

					stack.push_back(input_token);
					temp_token.type = ptable[i].next;
					stack.push_back(temp_token);
					token_list.pop_back();
					break;
				case REDUCE:
					printf("REDUCE %5d (%5d, %10s)\n", ptable[i].next, stack_token.type, get_type_name((type_t)(input_token.type)));

					for (int j = 1; j <= rtable[ptable[i].next].pop_count * 2; j++) {
						stack.pop_back();
					}

					previous_state = stack.back().type;

					temp_token.type = rtable[ptable[i].next].push;
					stack.push_back(temp_token);

					for (int j = 0; j < ptable_n; j++) {
						if (ptable[j].state == previous_state && ptable[j].token == rtable[ptable[i].next].push) {
							printf("GOTO   %5d (%5d, %10s)\n", ptable[j].next, previous_state, get_type_name((type_t)(rtable[ptable[i].next].push)));

							temp_token.type = ptable[j].next;
							stack.push_back(temp_token);
							break;
						}
					}
					break;
				case ACCEPT:
					printf("ACCEPT!\n");
					return;
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

