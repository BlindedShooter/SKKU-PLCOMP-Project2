#include "pseudo_code.h"
#include "parse_tree.h"
#include "symbol_table.h"
#include <iostream>

vector<std::string> pseudo_code;

vector<std::string> inorder(ParseNode *current_node) {
	vector<std::string> variables;
	vector<std::string> value;
	type_t type = INT;

	switch (current_node->value.type) {
	case BLOCK:
		enter_scope();
		break;

	case DECL:
		if (current_node->child.size() == 3) {
			if (inorder(current_node->child[0])[0] == "CHAR") type = CHAR;
			variables = inorder(current_node->child[1]);
		}
		if (current_node->child.size() == 2) {
			variables = inorder(current_node->child[0]);
		}
		for (int i = 0; i < variables.size(); i++) {
			insert_symbol(variables[i], type);
		}
		variables.clear();
		break;

	case STAT:
		if (current_node->child[1]->value.type == EQUAL) {
			variables = inorder(current_node->child[0]);
			value = inorder(current_node->child[2]);
			pseudo_code.push_back("LD " + variables[0] + ", $" + value[0]);
		}
		variables.clear();
		break;

	case INT:
	case CHAR:
		variables.push_back(get_type_name((type_t)current_node->value.type));
		return variables;

	case WORD:
	case NUM:
		variables.push_back(current_node->value.value);
		return variables;

	default:
		break;
	}

	for (int i = 0; i < current_node->child.size(); i++) {
		value = inorder(current_node->child[i]);
		for (int j = 0; j < value.size(); j++) {
			variables.push_back(value[j]);
		}
	}

	if (current_node->value.type == BLOCK) exit_scope();
	return variables;
}

void make_pseudo_code() {
	inorder(parse_tree.root);

	for (int i = 0; i < pseudo_code.size(); i++) {
		cout << pseudo_code[i] << endl;
	}
}