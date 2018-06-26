#include <stdio.h>

void scanner(char *file_name);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("Please input file name to compile.\n");
		return 0;
	}

	scanner(argv[1]);

	return 0;
}

void scanner(char *file_name)
{
	FILE *in;
	fopen_s(&in, file_name, "r");

	if (in != NULL) {
		char line[255];

		while (!feof(in))
		{
			fgets(line, sizeof(line), in);
			printf("%s", line);
		}

		fclose(in);
	}
	else {
		printf("Input file error.\n");
	}
}