#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

enum {
	SHIFT,
	REDUCE,
	GOTO,
	ACCEPT,

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
	NUM,		// num
	END,		// $
};

typedef struct _Token
{
	int type;
	int value_num;
	char value_word[255];
}Token;

typedef struct _Ptable
{
	int state;
	int token;
	int action;
	int next;
}Ptable;

Ptable ptable[] = {
	{	0,	 WORD,	SHIFT,	3	},
	{	0,	 INT,	SHIFT,	4	},
	{	0,	 CHAR,	SHIFT,	5	},
	{	0,	 PROG,	GOTO,	1	},
	{	0,	 VTYPE,	GOTO,	2	},
	{	1,	 END,	ACCEPT,	0	},
	{	2,	 WORD,	SHIFT,	6	},
	{	3,	 PHL,	SHIFT,	7	},
	{	4,	 WORD,	REDUCE,	11	},
	{	5,	 WORD,	REDUCE,	12	},
	{	6,	 PHL,	SHIFT,	8	},
	{	7,	 WORD,	SHIFT,	11	},
	{	7,	 PHR,	SHIFT,	10	},
	{	7,	 WORDS,	GOTO,	9	},
	{	8,	 WORD,	SHIFT,	11	},
	{	8,	 PHR,	SHIFT,	13	},
	{	8,	 WORDS,	GOTO,	12	},
	{	9,	 PHR,	SHIFT,	14	},
	{	9,	 COMMA,	SHIFT,	15	},
	{	10,	 MPHL,	SHIFT,	17	},
	{	10,  	 BLOCK,	GOTO,	16	}
	{	11,	 PHR,	REDUCE, 10	},
	{	11,	 COMMA,	REDUCE, 10	},
	{	12,	 PHR,	SHIFT,	18	},
	{	12,	 COMMA,	SHIFT, 	15	},
	{	13,	 MPHL,	SHIFT, 	17	},
	{	13,	 BLOCK,	GOTO, 	19	},
	{	14,	 MPHL,	SHIFT, 	17	},
	{	14,	 BLOCK,	GOTO, 	20	},
	{	15,	 WORD,	SHIFT,	21	},
	{	16,	 END,	REDUCE,	4	},
	{	17,	 WORD,	SHIFT,	32	},
	{	17,	 INT,	SHIFT,	4	},
	{	17,	 CHAR,	SHIFT,	5	},
	{	17,	 MPHL,	SHIFT,	34	},
	{	17,	 MPHR,	SHIFT,	24	},
	{	17,	 IF,	SHIFT,	30	},
	{	17,	 WHILE,	SHIFT,	31	},
	{	17,	 RETURN,SHIFT,	33	},
	{	17,	 DECLS,	GOTO,	22	},
	{	17,	 DECL,	GOTO,	25	},
	{	17,	 WORDS,	GOTO,	28	},
	{	17,	 VTYPE,	GOTO,	27	},
	{	17,	 BLOCK,	GOTO,	29	},
	{	17,	 SLIST,	GOTO,	23	},
	{	17,	 STAT,	GOTO,	26	},
	{	18,	 MPHL,	SHIFT,	17	},
	{	18,	 BLOCK,	GOTO,	35	},
	{	19,	 END,	REDUCE,	3	},
	{	20,	 END,	REDUCE,	2	},
	{	21,	 PHR,	REDUCE,	9	},
	{	21,	 COMMA,	REDUCE,	9	},
	{	22,	 WORD,	SHIFT,	32	},
	{	22,	 INT,	SHIFT,	4	},
	{	22,	 CHAR,	SHIFT,	5	},
	{	22,	 MPHL,	SHIFT,	34	},
	{	22,	 MPHR,	SHIFT,	37	},
	{	22,	 IF,	SHIFT,	30	},
	{	22,	 WHILE,	SHIFT,	31	},
	{	22,	 RETURN,SHIFT,	33	},
	{	22,	 DECL,	GOTO,	38	},
	{	22,	 WORDS,	GOTO,	28	},
	{	22,	 VTYPE,	GOTO,	27	},
	{	22,	 BLOCK,	GOTO,	29	},
	{	22,	 SLIST,	GOTO,	36	},
	{	22,	 STAT,	GOTO,	26	},
	{	23,	 WORD,	SHIFT,	41	},
	{	23,	 MPHL,	SHIFT,	34	},
	{	23,	 MPHR,	SHIFT,	39	},
	{	23,	 IF,	SHIFT,	30	},
	{	23,	 WHILE,	SHIFT,	31	},
	{	23,	 RETURN,SHIFT,	33	},
	{	23,	 BLOCK,	GOTO,	29	},
	{	23,	 STAT,	GOTO,	40	},
	
	{}
	
	
};

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
