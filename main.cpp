#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

enum {
	PROGS,		// prog'
	PROG,		// prog
	DECLS,		// decls
	DECL,		// decl
	WORDS,		// words
	VTYPE,		// vtype
	BLOCK,		// block
	SLIST,		// slist
	STAT,		// stat
	COND,		// cond
	EXPR,		// expr
	TERM,		// term
	FACT,		// fact

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
	int value_num;
	char value_word[255];
}Token;

bool is_terminal(char key);
void get_token(char *str, vector<Token> *token_list);
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

bool is_terminal(char key)
{
	switch (key) {
	case '(':
	case ')':
	case ';':
	case ',':
	case '{':
	case '}':
	case '=':
	case '>':
	case '<':
	case '+':
	case '*':
	case ' ':
	case '\n':
	case '\t':
	case '\0':
		return true;
	}
	return false;
}

void get_token(char *str, vector<Token> *token_list)
{
	int i, n, tn;
	char token[255] = { 0 };
	Token new_token;
	n = strlen(str);

	tn = 0;
	for (i = 0; i <= n; i++) {
		if (is_terminal(str[i]) && tn > 0) {
			token[tn] = '\0';

			if (strcmp(token, "INT") == 0) new_token.type = INT;
			else if (strcmp(token, "CHAR") == 0) new_token.type = CHAR;
			else if (strcmp(token, "IF") == 0) new_token.type = IF;
			else if (strcmp(token, "THEN") == 0) new_token.type = THEN;
			else if (strcmp(token, "ELSE") == 0) new_token.type = ELSE;
			else if (strcmp(token, "WHILE") == 0) new_token.type = WHILE;
			else if (strcmp(token, "RETURN") == 0) new_token.type = RETURN;
			else if ('0' <= token[0] && token[0] <= '9') {
				new_token.type = NUM;
				new_token.value_num = atoi(token);
			}
			else {
				new_token.type = WORD;
				strcpy_s(new_token.value_word, token);
			}

			token_list->push_back(new_token);
			tn = 0;
		}

		switch (str[i]) {
		case '(':
			new_token.type = PHL;
			token_list->push_back(new_token);
			break;
		case ')':
			new_token.type = PHR;
			token_list->push_back(new_token);
			break;
		case ';':
			new_token.type = SEMICOLON;
			token_list->push_back(new_token);
			break;
		case ',':
			new_token.type = COMMA;
			token_list->push_back(new_token);
			break;
		case '{':
			new_token.type = MPHL;
			token_list->push_back(new_token);
			break;
		case '}':
			new_token.type = MPHR;
			token_list->push_back(new_token);
			break;
		case '=':
			new_token.type = EQUAL;
			token_list->push_back(new_token);
			break;
		case '>':
			new_token.type = GREATER;
			token_list->push_back(new_token);
			break;
		case '<':
			new_token.type = LESS;
			token_list->push_back(new_token);
			break;
		case '+':
			new_token.type = PLUS;
			token_list->push_back(new_token);
			break;
		case '*':
			new_token.type = MUL;
			token_list->push_back(new_token);
			break;

		case ' ':
		case '\n':
		case '\0':
		case '\t':
			break;

		default:
			token[tn++] = str[i];
			break;
		}
	}
}

void scanner(char *file_name)
{
	vector<Token> token_list;
	FILE *in;
	fopen_s(&in, file_name, "r");

	if (in != NULL) {
		char line[255];

		while (!feof(in))
		{
			fgets(line, sizeof(line), in);
			get_token(line, &token_list);
		}

		fclose(in);
	}
	else {
		printf("Input file error.\n");
	}

	for (int i = 0; i < token_list.size(); i++) {
		if (token_list[i].type == WORD) {
			printf("%d %s\n", token_list[i].type, token_list[i].value_word);
		}
		else if (token_list[i].type == NUM) {
			printf("%d %d\n", token_list[i].type, token_list[i].value_num);
		}
		else {
			printf("%d\n", token_list[i].type);
		}
	}
}