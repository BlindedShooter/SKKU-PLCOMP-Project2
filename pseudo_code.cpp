#include "pseudo_code.h"
#include "parse_tree.h"
#include "symbol_table.h"
#include <iostream>
#include <fstream>

vector<std::string> pseudo_code;
size_t memory_address;

bool is_number(string value) {
	for (int i = 0; i < value.size(); i++) {
		if (value[i] < '0' || '9' < value[i]) return false;
	}
	return true;
}

vector<std::string> inorder(ParseNode *current_node, int register_num = 0) {
	vector<std::string> variables;
	vector<std::string> value;
	type_t type = INT;

	//printf("%s\n", get_type_name((type_t)current_node->value.type));

	switch (current_node->value.type) {
	case DECL:
		if (current_node->child.size() == 3) {
			if (inorder(current_node->child[0])[0] == "CHAR") type = CHAR;
			variables = inorder(current_node->child[1]);
		}
		if (current_node->child.size() == 2) {
			variables = inorder(current_node->child[0]);
		}
		for (int i = 0; i < variables.size(); i++) {
			insert_symbol(variables[i], symbol_info(type, memory_address));
			memory_address += 4;
		}
		variables.clear();
		break;

	case STAT:  // BLOCK, EQUAL, RETURN, while, if-then 
		if (current_node->child[1]->value.type == EQUAL) {
			value = inorder(current_node->child[0]);
			inorder(current_node->child[2], register_num);
			pseudo_code.push_back("ST " + std::to_string(local_lookup(value[0]).addr) + ", Reg#" + std::to_string(register_num));
		}
		
		if (current_node->child[0]->value.type == IF) { 
			// JUMPF -> make branch
			// pseudo_code.push_back("LD " );
			// pseudo_code.push_back("JUMPT " );
		}
			
		if (current_node->child[0]->value.type == WHILE) { 
			// LABEL ??
		}
			
		if (current_node->child[0]->value.type == RETURN) { 	
			// COND를 Reg#1로 return
		}
		variables.clear();
		break;
		
			
	case COND: // EXPR < EXPR , EXPR > EXPR , EXPR
		if (current_node->child.size() == 1) {
			value = inorder(current_node->child[0], register_num);
			for (int i = 0; i < value.size(); i++) {
				variables.push_back(value[i]);
			}
		}
		else {/*
			value = inorder(current_node->child[0]);
			pseudo_code.push_back("LD Reg#" + to_string(register_num) + ", " + value[0]);
			if (current_node->child[1]->value.type == GREATER) {
				value = inorder(current_node->child[1]);
				pseudo_code.push_back("LD Reg#" + to_string(register_num + 1) + ", " + value[0]);
				pseudo_code.push_back("LT Reg#" + to_string(register_num) + ", Reg#" + to_string(register_num + 1) + ", Reg#" + to_string(register_num));
			}
			else if (current_node->child[1]->value.type == LESS) {
				value = inorder(current_node->child[1]);
				pseudo_code.push_back("LD Reg#" + to_string(register_num + 1) + ", " + value[0]);
				pseudo_code.push_back("LT Reg#" + to_string(register_num) + ", Reg#" + to_string(register_num) + ", Reg#" + to_string(register_num + 1));
			}*/
		}
		break;
			
	case EXPR: // TERM, TERM + TERM
		// TERM
		if (current_node->child.size() == 1) {
			value = inorder(current_node->child[0], register_num);
			for (int i = 0; i < value.size(); i++) {
				variables.push_back(value[i]);
			}
		}
		// TERM + TERM
		else {
			inorder(current_node->child[0], register_num);
			inorder(current_node->child[2], register_num + 1);
			pseudo_code.push_back("ADD Reg#" + to_string(register_num) + ", Reg#" + to_string(register_num) + ", Reg#" + to_string(register_num + 1));
		}
		break;
			
	case TERM: // FACT, FACT * FACT 
		// FACT
		if (current_node->child.size() == 1) {
			value = inorder(current_node->child[0], register_num);
			for (int i = 0; i < value.size(); i++) {
				variables.push_back(value[i]);
			}
		}
		// FACT * FACT
		else {
			inorder(current_node->child[0], register_num);
			inorder(current_node->child[2], register_num + 1);
			pseudo_code.push_back("MUL Reg#" + to_string(register_num) + ", Reg#" + to_string(register_num) + ", Reg#" + to_string(register_num + 1));
		}
		break;	

	case FACT: // num, word
		if (current_node->child.size() == 1) {
			value = inorder(current_node->child[0], register_num);
			if (is_number(value[0])) {
				pseudo_code.push_back("LD Reg#" + to_string(register_num) + ", $" + value[0]);
			}
			else {
				pseudo_code.push_back("LD Reg#" + to_string(register_num) + ", " + to_string(local_lookup(value[0]).addr));
			}
		}
		break;

	case INT:
	case CHAR:
		variables.push_back(get_type_name((type_t)current_node->value.type));
		return variables;
			
	case WORD:
	case NUM:
		variables.push_back(current_node->value.value);
		return variables;

	case BLOCK:
		enter_scope();
	case PROG:
	case DECLS:
	case SLIST:
	default:
		for (int i = 0; i < current_node->child.size(); i++) {
			value = inorder(current_node->child[i]);
			for (int j = 0; j < value.size(); j++) {
				variables.push_back(value[j]);
			}
		}
		break;
	}

	if (current_node->value.type == BLOCK) exit_scope();
	return variables;
}

void make_pseudo_code(char *file_name) {
	inorder(parse_tree.root);

	string result_file_name = file_name;
	result_file_name += ".code";

	ofstream out(result_file_name);
	for (int i = 0; i < pseudo_code.size(); i++) {
		cout << pseudo_code[i] << endl;
		out << pseudo_code[i] << endl;
	}
}
