#include <cstdio>

#include "scanner.h"
#include "parser.h"

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please input file name to compile.\n");
		return 0;
	}

	scanner(argv[1]);
  parser();

	return 0;
}