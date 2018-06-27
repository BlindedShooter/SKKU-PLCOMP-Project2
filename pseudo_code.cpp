#include "pseudo_code.h"
#include "parse_tree.h"
#include "symbol_table.h"
#include <iostream>

vector<std::string> pseudo_code;
int register_num = 1;
int label_num = 1;

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

	case STAT:  // BLOCK, EQUAL, RETURN, while, if-then 
		if (current_node->child[1]->value.type == EQUAL) {
			variables = inorder(current_node->child[0]);
			value = inorder(current_node->child[2]); 
			//pseudo_code.push_back("LD " + variables[0] + ", $" + value[0]); 
			pseudo_code.push_back("LD Reg#" + registor_num + ", " + variables[0]); 	// Register 로 바꿔야되는데		
		}
		
		if (current_node->child[0]->value.type == IF) { 
			// JUMPF -> make branch
			value = inorder(current_node->child[1]); 
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
		//value = inorder(current_node->child[0]);
		value = inorder(current_node->child[0]); 
		pseudo_code.push_back("LD Reg#" + registor_num + ", " + value);
		
		if (current_node->child[1]->value.type == GREATER){
		value = inorder(current_node->child[1]); 
		pseudo_code.push_back("LD Reg#" + (registor_num+1) + ", " + value);
		pseudo_code.push_back("LT Reg#" + registor_num + ", Reg#" + (registor_num+1) + ", Reg#" + registor_num);
			
		}else if (current_node->child[1]->value.type == LESS){			
		value = inorder(current_node->child[1]); 
		pseudo_code.push_back("LD Reg#" + (registor_num+1) + ", " + value);
		pseudo_code.push_back("LT Reg#" + registor_num + ", Reg#" + registor_num + ", Reg#" + (registor_num+1));
		}else{}
		break;		 
			
	case EXPR: // TERM, TERM + TERM
		value = inorder(current_node->child[0]); 
		pseudo_code.push_back("LD Reg#" + registor_num + ", " + value);
		if (current_node->child[1]->value.type == PLUS){			
			value = inorder(current_node->child[1]); 
			pseudo_code.push_back("LD Reg#" + (registor_num+1) + ", " + value);
			pseudo_code.push_back("PLUS Reg#" + registor_num + ", Reg#" + (registor_num+1) + ", Reg#" + registor_num );
		}else{	}			
		break;		
			
	case TERM: // FACT, FACT * FACT 
		value = inorder(current_node->child[0]); 
		pseudo_code.push_back("LD Reg#" + registor_num + ", " + value);
		if (current_node->child[1]->value.type == MUL){			
			value = inorder(current_node->child[1]); 
			pseudo_code.push_back("LD Reg#" + (registor_num+1) + ", " + value);
			pseudo_code.push_back("MUL Reg#" + registor_num + ", Reg#" + (registor_num+1) + ", Reg#" + registor_num );
		}else{	}
		break;	
			
	case FACT: // num, word
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
