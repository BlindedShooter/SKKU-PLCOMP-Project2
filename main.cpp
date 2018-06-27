#include <cstdio>

#include "scanner.h"
#include "parser.h"
#include "parse_tree.h"
#include "pseudo_code.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please input file name to compile.\n");
		return 0;
	}

	scanner(argv[1]);
	parser();
	build_parse_tree();
	make_pseudo_code();

    delete GLOBAL;
	return 0;
}