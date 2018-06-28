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
	printf("\n<Parsing>\n");
	parser();
	printf("\n<Parse Tree>\n");
	build_parse_tree();
	printf("\n<Pseudo Code>\n");
	make_pseudo_code(argv[1]);
	printf("\nUsed memory: %d\n", memory_address);

    delete GLOBAL;
	return 0;
}