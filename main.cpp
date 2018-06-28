#include <cstdio>

#include "scanner.h"
#include "parser.h"
#include "parse_tree.h"
#include "pseudo_code.h"
#include "asm_translator.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please input file name to compile.\n");
		return 0;
	}

	scanner(argv[1]);

	printf("<Parsing>\n");
	parser();

	printf("\n<Parse Tree>\n");
	build_parse_tree();

	make_pseudo_code(argv[1]);

	printf("\nUsed memory: %d\n", memory_address);
	printf("Used Register: %d\n", used_register + 1);

	print_symbol_table(argv[1]);

	translate_to_asm(argv[1]);



	delete GLOBAL;
	return 0;
}