#include "parser.h"

void compile_error() {
	printf("Compile error.\n");
	exit(0);
}

int get_parse_table_index(int row, int col) {
	int i;
	for (i = 0; i < ptable_n; i++) {
		if (ptable[i].state == row && ptable[i].token == col) {
			return i;
		}
	}

	compile_error();

	return 0;
}

void parser() {
    vector<Token> stack;
    Token temp_token, stack_token, input_token;
	int previous_state = 0;
	int index = 0, jndex = 0;

    temp_token.type = 0;
    stack.push_back(temp_token);

    while (true) {
        stack_token = stack.back();
        input_token = token_list.back();

		index = get_parse_table_index(stack_token.type, input_token.type);
		switch (ptable[index].action) {
		case SHIFT:
			printf("SHIFT  %5d (%5d, %10s)\n", ptable[index].next, stack_token.type, get_type_name((type_t)(input_token.type)));

			stack.push_back(input_token);
			temp_token.type = ptable[index].next;
			stack.push_back(temp_token);
			token_list.pop_back();
			break;
		case REDUCE:
			printf("REDUCE %5d (%5d, %10s)\n", ptable[index].next, stack_token.type, get_type_name((type_t)(input_token.type)));

			for (int i = 1; i <= rtable[ptable[index].next].pop_count * 2; i++) {
				stack.pop_back();
			}

			previous_state = stack.back().type;

			temp_token.type = rtable[ptable[index].next].push;
			stack.push_back(temp_token);

			jndex = get_parse_table_index(previous_state, rtable[ptable[index].next].push);
			printf("GOTO   %5d (%5d, %10s)\n", ptable[jndex].next, previous_state, get_type_name((type_t)(rtable[ptable[index].next].push)));

			temp_token.type = ptable[jndex].next;
			stack.push_back(temp_token);
			break;
		case ACCEPT:
			printf("ACCEPT!\n");
			return;
		}
    }
}

