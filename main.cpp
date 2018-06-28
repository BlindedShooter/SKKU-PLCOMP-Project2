#include <cstdio>

#include "scanner.h"
#include "parser.h"
#include "parse_tree.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please input file name to compile.\n");
		return 0;
	}

	scanner(argv[1]);
	parser();
	build_parse_tree();

    delete GLOBAL;
	return 0;
}