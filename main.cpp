#include <stdio.h>

enum {
	PHL,		// (
	PHR,		// )
	SEMICOLON,	// ;
	COMMA,		// ,
	INT,		// INT
	CHAR,		// CHAR
	MPHL,		// {
	MPHR,		// }
	IF,			// IF
	THEN,		// THEN
	ELSE,		// ELSE
	WHILE,		// WHILE
	EQUAL,		// =
	RETURN,		// RETURN
	GREATER,	// >
	LESS,		// <
	PLUS,		// +
	MUL,		// *
	WORD,		// word
	NUM			// num
};

typedef struct _Token
{
	int type;
	int value;
}Token;

void get_token(char *str);
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

void get_token(char *str)
{
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