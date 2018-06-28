#include "decls.h"
#include "symbol_table.h"
#include <iostream>
#include <fstream>

int scope_number = 0;

symbol_info::symbol_info(type_t type, size_t addr) {
	this->type = type;
	this->addr = addr;
}

Scope::Scope() {
	parent = nullptr;
	level = 0;
}

Scope::Scope(Scope *parent_) : parent(parent_), name(std::to_string(scope_number++)) {
	parent_->child.push_back(this);
	level = parent_->level + 1;
}

Scope::Scope(Scope *parent_, const std::string &name_) : parent(parent_), name(name_) {
	parent_->child.push_back(this);
	level = parent_->level + 1;
}

Scope::~Scope() {
	while (!child.empty()) {
		delete child.back();
		child.pop_back();
	}
	child.~vector();
	name.~basic_string();
}


Scope *GLOBAL = new Scope();
Scope *current_scope = GLOBAL;

void enter_scope() {
	auto new_scope = new Scope(current_scope);
	current_scope = new_scope;
}

void enter_scope(const std::string &scope_name) {
	auto new_scope = new Scope(current_scope, scope_name);
	current_scope = new_scope;
}

void exit_scope() {
	current_scope = current_scope->parent;
}

int insert_symbol(const std::string &name, symbol_info info) {
	int result = 0;
	if (current_scope->symbol_table.find(name) != current_scope->symbol_table.end()) {
		result = 1;
	}
	else {
		current_scope->symbol_table.insert({ name, info });
	}
	return result;
}

symbol_info local_lookup(const std::string &name) {
	auto finding = current_scope->symbol_table.find(name);
	symbol_info result(NONE, 0);

	if (finding == current_scope->symbol_table.end()) {  // should be tested if it works well...
		result.type = NONE;
	}
	else {
		result.type = finding->second.type;
		result.addr = finding->second.addr;
	}
	return result;
}

symbol_info lookup(const std::string &name) {
	symbol_info result(NONE, 0);

	Scope *finding_scope = current_scope;
	for (; finding_scope->level > 0; finding_scope = finding_scope->parent) {
		auto finding = finding_scope->symbol_table.find(name);

		if (finding == finding_scope->symbol_table.end()) {  // should be tested if it works well...
			continue;
		}
		else {
			result.type = finding->second.type;
			result.addr = finding->second.addr;
			break;
		}
	}
	return result;
}

void print_reculsively(ofstream &out, Scope *finding_scope) {
	symbol_table_t::iterator iter;

	if (finding_scope->symbol_table.size() != 0) {
		for (int i = 1; i < finding_scope->level; i++) out << "    ";
		out << "{" << endl;
		for (iter = finding_scope->symbol_table.begin();iter != finding_scope->symbol_table.end(); iter++) {
			for (int i = 1; i < finding_scope->level; i++) out << "    ";
			out << "Name: " << iter->first << " Type: " << get_type_name((type_t)iter->second.type) << " Address: " << iter->second.addr << endl;
		}
	}

	for (int i = 0; i < finding_scope->child.size(); i++) {
		print_reculsively(out, finding_scope->child[i]);
	}

	if (finding_scope->symbol_table.size() != 0) {
		for (int i = 1; i < finding_scope->level; i++) out << "    ";
		out << "}" << endl;
	}
}

void print_symbol_table(char *file_name) {
	string result_file_name = file_name;
	ofstream out(result_file_name + ".symbol");

	print_reculsively(out, current_scope);
}