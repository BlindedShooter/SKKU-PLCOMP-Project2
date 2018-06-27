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
	{	24,	 END,	REDUCE,	16	},
	{	25,	 WORD,	REDUCE,	6	},
	{	25,	 INT,	REDUCE,	6	},
	{	25,	 CHAR,	REDUCE,	6	},
	{	25,	 MPHL,	REDUCE,	6	},
	{	25,	 MPHR,	REDUCE,	6	},
	{	25,	 IF,	REDUCE,	6	},
	{	25,	 WHILE,	REDUCE,	6	},
	{	25,	 RETURN,REDUCE,	6	},	
	{	26,	 WORD,	REDUCE,	18	},
	{	26,	 MPHL,	REDUCE,	18	},
	{	26,	 MPHR,	REDUCE,	18	},
	{	26,	 IF,	REDUCE,	18	},
	{	26,	 WHILE,	REDUCE,	18	},
	{	26,	 RETURN,REDUCE,	18	},	
	{	27,	 WORD,	SHIFT,	43	},
	{	27,	 WORDS,	GOTO,	42	},
	{	28,	 SEMICOLON,	SHIFT,	44	},
	{	28,	 COMMA,	SHIFT,	45	},
	{	29,	 WORD,	REDUCE,	19	},
	{	29,	 MPHL,	REDUCE,	19	},
	{	29,	 MPHR,	REDUCE,	19	},
	{	29,	 IF,	REDUCE,	19	},
	{	29,	 WHILE,	REDUCE,	19	},
	{	29,	 RETURN,REDUCE,	19	},	
	
	{	30,	 WORD,	SHIFT,	51	},
	{	30,	 NUM,	SHIFT,	50	},
	{	30,	 COND,	GOTO,	46	},
	{	30,	 EXPR,	GOTO,	47	},
	{	30,	 TERM,	GOTO,	48	},
	{	30,	 FACT,	GOTO,	49	},

	{	31,	 WORD,	SHIFT,	57	},
	{	31,	 NUM,	SHIFT,	56	},
	{	31,	 COND,	GOTO,	52	},
	{	31,	 EXPR,	GOTO,	53	},
	{	31,	 TERM,	GOTO,	54	},
	{	31,	 FACT,	GOTO,	55	},
	
	{	32,	 SEMICOLON,	REDUCE,	10	},
	{	32,	 COMMA,	REDUCE,	10	},
	{	32,	 EQUAL,	SHIFT,	58	},
	
	{	33,	 WORD,	SHIFT,	64	},
	{	33,	 NUM,	SHIFT,	63	},
	{	33,	 COND,	GOTO,	59	},
	{	33,	 EXPR,	GOTO,	60	},
	{	33,	 TERM,	GOTO,	61	},
	{	33,	 FACT,	GOTO,	62	},
	
	{	34,	 WORD,	SHIFT,	32	},
	{	34,	 INT,	SHIFT,	4	},
	{	34,	 CHAR,	SHIFT,	5	},
	{	34,	 MPHL,	SHIFT,	34	},
	{	34,	 MPHR,	SHIFT,	67	},
	{	34,	 IF,	SHIFT,	30	},
	{	34,	 WHILE,	SHIFT,	31	},
	{	34,	 RETURN,SHIFT,	33	},
	{	34,	 DECLS,	GOTO,	65	},
	{	34,	 DECL,	GOTO,	25	},
	{	34,	 WORDS,	GOTO,	28	},
	{	34,	 VTYPE,	GOTO,	27	},
	{	34,	 BLOCK,	GOTO,	29	},
	{	34,	 SLIST,	GOTO,	66	},
	{	34,	 STAT,	GOTO,	26	},
	{	35,	 END,	REDUCE,	1	},
	
	{	36,	 WORD,	SHIFT,	41	},
	{	36,	 MPHL,	SHIFT,	34	},
	{	36,	 MPHR,	SHIFT,	68	},
	{	36,	 IF,	SHIFT,	30	},
	{	36,	 WHILE,	SHIFT,	31	},
	{	36,	 RETURN,SHIFT,	33	},
	{	36,	 BLOCK,	GOTO,	29	},
	{	36,	 STAT,	GOTO,	40	},
	
	{	37,	 END,	REDUCE,	15	},
	{	38,	 WORD,	REDUCE,	5	},
	{	38,	 INT,	REDUCE,	5	},
	{	38,	 CHAR,	REDUCE,	5	},
	{	38, 	 MPHL,	REDUCE,	5	},
	{	38,	 MPHR,	REDUCE,	5	},
	{	38,	 IF,	REDUCE,	5	},
	{	38, 	 WHILE,	REDUCE,	5	},
	{	38,	 RETURN,REDUCE,	5	},
	
	{	39,	 END,	REDUCE,	14	},		
	{	40,	 WORD,	REDUCE,	17	},
	{	40, 	 MPHL,	REDUCE,	17	},
	{	40,	 MPHR,	REDUCE,	17	},
	{	40,	 IF,	REDUCE,	17	},
	{	40, 	 WHILE,	REDUCE,	17	},
	{	40,	 RETURN,REDUCE,	17	},
	
	{	41,	 EQUAL,	SHIFT,	58	},
	
	{	42,	 SEMICOLON,	SHIFT,	69	},
	{	42,	 COMMA,	SHIFT,	45	},
	{	43,	 SEMICOLON,	REDUCE,	10	},
	{	43,	 COMMA,	REDUCE,	10	},
	
	{	44,	 WORD,	REDUCE,	8	},
	{	44,	 INT,	REDUCE,	8	},
	{	44,	 CHAR,	REDUCE,	8	},
	{	44, 	 MPHL,	REDUCE,	8	},
	{	44,	 MPHR,	REDUCE,	8	},
	{	44,	 IF,	REDUCE,	8	},
	{	44, 	 WHILE,	REDUCE,	8	},
	{	44,	 RETURN,REDUCE,	8	},
	{	45,	 WORD,	SHIFT,	70	},
	
	{	46,	 THEN,	SHIFT,	71	},

	{	47,	 THEN,	REDUCE,	26	},
	{	47,	 GREATER,	SHIFT,	72	},
	{	47,	 LESS,	SHIFT,	73	},
	
	{	48,	 THEN,	REDUCE,	27	},
	{	48,	 GREATER,	REDUCE,	27	},
	{	48,	 LESS,	REDUCE,	27	},
	{	48,	 PLUS,	SHIFT,	74	},
	
	{	49,	 THEN,	REDUCE,	29	},
	{	49,	 GREATER,	REDUCE,	29	},
	{	49,	 LESS,	REDUCE,	29	},
	{	49,	 PLUS,	REDUCE,	29	},
	{	49,	 MUL,	SHIFT,	75	},
	
	{	50,	 THEN,	REDUCE,	31	},
	{	50,	 GREATER,	REDUCE,	31	},
	{	50,	 LESS,	REDUCE,	31	},
	{	50,	 PLUS,	REDUCE,	31	},
	{	50,	 MUL,	REDUCE,	31	},
	
	{	51,	 THEN,	REDUCE,	32	},
	{	51,	 GREATER,	REDUCE,	32	},
	{	51,	 LESS,	REDUCE,	32	},
	{	51,	 PLUS,	REDUCE,	32	},
	{	51,	 MUL,	REDUCE,	32	},
	
	{	52,	 MPHL,	SHIFT,	34	},
	{	52,	 BLOCK,	GOTO,	76	},

	{	53,	 MPHL,	REDUCE,	26	},
	{	53,	 GREATER,	SHIFT,	77	},
	{	53,	 LESS,	SHIFT,	78	},
	
	{	54,	 MPHL,	REDUCE,	27	},
	{	54,	 GREATER,	REDUCE,	27	},
	{	54,	 LESS,	REDUCE,	27	},
	{	54,	 PLUS,	SHIFT,	79	},
	
	{	55,	 MPHL,	REDUCE,	29	},
	{	55,	 GREATER,	REDUCE,	29	},
	{	55,	 LESS,	REDUCE,	29	},
	{	55,	 PLUS,	REDUCE,	29	},
	{	55,	 MUL,	SHIFT,	80	},
	
	{	56,	 MPHL,	REDUCE,	31	},
	{	56,	 GREATER,	REDUCE,	31	},
	{	56,	 LESS,	REDUCE,	31	},
	{	56,	 PLUS,	REDUCE,	31	},
	{	56,	 MUL,	REDUCE,	31	},

	{	57,	 MPHL,	REDUCE,	32	},
	{	57,	 GREATER,	REDUCE,	32	},
	{	57,	 LESS,	REDUCE,	32	},
	{	57,	 PLUS,	REDUCE,	32	},
	{	57,	 MUL,	REDUCE,	32	},
	
	{	58,	 WORD,	SHIFT,	64	},
	{	58,	 NUM,	SHIFT,	63	},
	{	58,	 COND,	GOTO,	81	},
	{	58,	 EXPR,	GOTO,	60	},
	{	58,	 TERM,	GOTO,	61	},
	{	58,	 FACT,	GOTO,	62	},
	
	{	59,	 SEMICOLON,	SHIFT,	82	},

	{	60,	 SEMICOLON,	REDUCE,	26	},
	{	60,	 GREATER,	SHIFT,	83	},
	{	60,	 LESS,	SHIFT,	84	},

	{	61,	 SEMICOLON,	REDUCE,	27	},
	{	61,	 GREATER,	REDUCE,	27	},
	{	61,	 LESS,	REDUCE,	27	},
	{	61,	 PLUS,	SHIFT,	85	},
	
	{	62,	 SEMICOLON,	REDUCE,	29	},
	{	62,	 GREATER,	REDUCE,	29	},
	{	62,	 LESS,	REDUCE,	29	},
	{	62,	 PLUS,	REDUCE,	29	},
	{	26,	 MUL,	SHIFT,	86	},
	
	{	63,	 SEMICOLON,	REDUCE,	31	},
	{	63,	 GREATER,	REDUCE,	31	},
	{	63,	 LESS,	REDUCE,	31	},
	{	63,	 PLUS,	REDUCE,	31	},
	{	63,	 MUL,	REDUCE,	31	},

	{	64,	 SEMICOLON,	REDUCE,	32	},
	{	64,	 GREATER,	REDUCE,	32	},
	{	64,	 LESS,	REDUCE,	32	},
	{	64,	 PLUS,	REDUCE,	32	},
	{	64,	 MUL,	REDUCE,	32	},
	
	{	65,	 WORD,	SHIFT,	32	},
	{	65,	 INT,	SHIFT,	4	},
	{	65,	 CHAR,	SHIFT,	5	},
	{	65,	 MPHL,	SHIFT,	34	},
	{	65,	 MPHR,	SHIFT,	88	},
	{	65,	 IF,	SHIFT,	30	},
	{	65,	 WHILE,	SHIFT,	31	},
	{	65,	 RETURN,SHIFT,	33	},
	{	65,	 DECL,	GOTO,	38	},
	{	65,	 WORDS,	GOTO,	28	},
	{	65,	 VTYPE,	GOTO,	27	},
	{	65,	 BLOCK,	GOTO,	29	},
	{	65,	 SLIST,	GOTO,	87	},
	{	65,	 STAT,	GOTO,	26	},
	
	{	66,	 WORD,	SHIFT,	41	},
	{	66,	 MPHL,	SHIFT,	34	},
	{	66,	 MPHR,	SHIFT,	89	},
	{	66,	 IF,	SHIFT,	30	},
	{	66,	 WHILE,	SHIFT,	31	},
	{	66,	 RETURN,SHIFT,	33	},
	{	66,	 BLOCK,	GOTO,	29	},
	{	66,	 STAT,	GOTO,	40	},
	
	{	67,	 WORD,	REDUCE,	16	},
	{	67,	 MPHL,	REDUCE,	16	},
	{	67,	 MPHR,	REDUCE,	16	},
	{	67,	 IF,	REDUCE,	16	},
	{	67,	 WHILE,	REDUCE,	16	},
	{	67,	 RETURN,REDUCE,	16	},
	
	{	68,	 END,	REDUCE,	13	},
	
	{	69,	 WORD,	REDUCE,	7	},
	{	69,	 MPHL,	REDUCE,	7	},
	{	69,	 MPHR,	REDUCE,	7	},
	{	69,	 MPHL,	REDUCE,	7	},
	{	69,	 MPHR,	REDUCE,	7	},
	{	69,	 IF,	REDUCE,	7	},
	{	69,	 WHILE,	REDUCE,	7	},
	{	69,	 RETURN,REDUCE,	7	},
	


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
