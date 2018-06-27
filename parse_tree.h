#include "decls.h"

struct ParseNode {
	vector<ParseNode *> child;
	ParseNode *parent;
	Token value;

	ParseNode(ParseNode *parent, Token value);
};

struct ParseTree {
	ParseNode *root;

	ParseTree();
};

extern ParseTree parse_tree;

void build_parse_tree();