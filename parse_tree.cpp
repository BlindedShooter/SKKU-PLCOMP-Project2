#include "parse_tree.h"

ParseTree::ParseTree() {
	root = NULL;
}

ParseNode::ParseNode(ParseNode *parent, Token value) {
	this->parent = parent;
	this->value = value;
}

ParseTree parse_tree;

bool is_non_terminal(type_t type) {
	if (PROGS <= type && type <= FACT) {
		return true;
	}
	return false;
}

bool is_my_child(type_t token, type_t right_child, type_t next) {
	int i;

	for (i = 0; i < stable_n; i++) {
		if (stable[i].token == token && stable[i].right_child == right_child && stable[i].next == next) {
			return true;
		}
	}

	return false;
}

void build_parse_node(ParseNode *current_node, int level) {
	Token current_token;

	for (int i = 1; i <= level * 4; i++) printf("-");
	printf("%s\n", get_type_name((type_t)current_node->value.type));

	while (!parsed_list.empty()) {
		current_token = parsed_list.back();

		if (!current_node->child.empty()) {
			if (!is_my_child((type_t)current_node->value.type, (type_t)current_node->child.front()->value.type, (type_t)current_token.type)) {
				return;
			}
		}

		parsed_list.pop_back();

		ParseNode *child_node = new ParseNode(current_node, current_token);
		current_node->child.insert(current_node->child.begin(), child_node);

		if (is_non_terminal((type_t)current_token.type)) {
			build_parse_node(child_node, level + 1);
		}
		else {
			for (int i = 1; i <= (level+1) * 4; i++) printf("-");
			printf("%s", get_type_name((type_t)child_node->value.type));
			if (child_node->value.type == NUM || child_node->value.type == WORD) {
				printf(" %s", child_node->value.value);
			}
			printf("\n");
		}
	}
}

void build_parse_tree() {
	ParseNode *root_node;
	root_node = new ParseNode(NULL, parsed_list.back());
	parsed_list.pop_back();

	parse_tree.root = root_node;

	build_parse_node(root_node, 0);
}