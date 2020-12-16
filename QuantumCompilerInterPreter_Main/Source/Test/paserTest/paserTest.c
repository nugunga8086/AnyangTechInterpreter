/*
	작품을 만들기 위한 사전 테스트 V.0.1

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef enum TokenKindTag
{
	_Import = 1,
	_Ident,
	_Dot,
	_Obj,
	_Lparen,
	_Rparen,
	_Var,
	_Pointer,
	_SemiColon,
	_Func,
	_LLparen,
	_RRparen,
	_Return,
	_Digit,
	_Letter,
	_String,
	_Int,
	_Others,
	_IF,
	_Else,
	_Print,
	_Plus,
	_Minus,
	_Multi,
	_Divi,
	_Equals,
	_Not_Equals,
	_Small,
	_SEquals,
	_Big,
	_BEquals,
	_Comma,
	_DbIQ,
	_SetEquals,
	_EOF,
	_END_Table

} TokenKind;

typedef struct TokenTag
{
	TokenKind Kind;
	char* text;
	int intVal;
} Token;

Token setToken();
Token setDataToken(TokenKind, const char*, int);
void setCharArraryTo(char*, const char*);
static int _strlen(const char*);
void initCharType();
void TokenManager();

Token setToken()
{
	Token token;
	token.Kind = _Others;
	token.text = NULL;
	token.text = (char*)malloc(sizeof(char) * 128);
	if(token.text == NULL)
	{
		printf("Error >= 메모리를 할당할 수 없음, 메모리 공간 부족");
		exit(-1);
	}
	token.intVal = 0;
	return token;
}

Token setDataToken(TokenKind TKind, const char* IText, int Ival)
{
	Token token;
	token.Kind = TKind;
	token.text = NULL;
	token.text = (char*)malloc(sizeof(char) * 128);
	if(token.text == NULL)
	{
		printf("Error >= 메모리를 할당할 수 없음, 메모리 공간 부족");
		exit(-1);
	}
	setCharArraryTo(token.text, IText);
	token.intVal = 0;
	return token;
}

void setCharArraryTo(char* replaceResult, const char* replaceData)
{
	int i;
	for (i = 0; i < _strlen(replaceData); ++i)
		replaceResult[i] = replaceData[i];
}

static int _strlen(const char* word)
{
	int i = 0;
	while(word[i++] != '\0');
	return i;
} 

TokenKind ctyp[256];
Token token;
FILE* TFile = NULL;

typedef struct KeyWordTag
{
	const char* keyName;
	TokenKind keyKind;
} KeyWord;

KeyWord KeyWordTable[] = 
{
	{ "import", _Import }, { ".", _Dot },
	{ "obj", _Obj }, { "(", _Lparen },
	{ ")", _Rparen }, { "var", _Var },
	{ "pointer", _Pointer }, { ";", _SemiColon },
	{ "func", _Func }, { "{", _LLparen },
	{ "}", _RRparen }, { "return", _Return },
	{ "if", _IF }, { "else", _Else },
	{ "print", _Print }, { "+", _Plus },
	{ "-", _Minus }, { "*", _Multi },
	{ "/", _Divi }, { "=", _Equals },
	{ "==", _Equals }, { "!=", _Not_Equals },
	{ "<", _Small }, { "<=", _SEquals },
	{ ">", _Big }, { ">=", _BEquals },
	{ ",", _Comma }, { "<-", _SetEquals },
	{ "", _END_Table}
};

void initCharType()
{
	int i;
	for (i = 0; i < 256; i++) { ctyp[i] = _Others; }
	for (i = '0'; i < '9'; i++) { ctyp[i] = _Digit; }
	for (i = 'a'; i < 'z'; i++) { ctyp[i] = _Letter; }
	for (i = 'A'; i < 'Z'; i++) { ctyp[i] = _Letter; }
	ctyp['('] = _Lparen; ctyp[')'] = _Rparen;
	ctyp['{'] = _LLparen; ctyp['}'] = _RRparen;
	ctyp['<'] = _Small; ctyp['>'] = _Big;
	ctyp['+'] = _Plus; ctyp['-'] = _Minus;
	ctyp['*'] = _Multi; ctyp['/'] = _Divi;
	ctyp['_'] = _Letter; ctyp['='] = _Equals;
	ctyp[','] = _Comma; ctyp['"'] = _DbIQ;
	ctyp['.'] = _Dot;
}

int nextCh()
{
	static int c = 0;
	if (c == EOF) return c;
	if ((c = fgetc(TFile)) == EOF) fclose(TFile);
	return c;
}

int is_ope2(int c1, int c2)
{
	char s[] = "  ";
	if(c1 == '\0' || c2 == '\0') return false;
	s[0] = c1; s[1] = c2;
	return strstr(" <= >= == != <- ", s) != NULL;
}

TokenKind get_kind(const char* s)
{
	for(int i = 0; KeyWordTable[i].keyKind != _END_Table; i++)
		if(strcmp(s, KeyWordTable[i].keyName) == 0) return KeyWordTable[i].keyKind;
	if(ctyp[s[0]] == _Letter) return _Ident;
	if(ctyp[s[0]] == _Digit) return _Int;
	return _Others;
}

char* txt = NULL;

Token nextToken()
{
	TokenKind kd;
	int ch0, num = 0, i = 0;
	static int ch = ' ';

	while(isspace(ch)) { ch = nextCh(); }
	if(ch == EOF) return setDataToken(_EOF, "", 0);

	switch(ctyp[ch])
	{
		case _Letter:
			for (; ctyp[ch] == _Letter || ctyp[ch] == _Digit; ch = nextCh())
			{
				txt[i++] = ch;
			}
			txt[i] = '\0';
			break;
		case _Digit:
			for(num = 0; ctyp[ch] == _Digit; ch = nextCh())
			{
				txt[i++] = ch;
				num = num*10 + (ch-'0');
			}
			txt[i] = '\0';
			return setDataToken(_Int, txt, num);
		case _DbIQ:
			for(ch=nextCh(); ch != EOF && ch != '\n' && ch != '"'; ch = nextCh())
			{
				txt[i++] = ch;
			}
			txt[i] = '\0';
			if(ch == '"') 
			{
				printf("Error >= 문자열 리터널을 닫지 않음\n");
				exit(-1);
			}
			ch = nextCh();
			return setDataToken(_String, txt, 0);
		default:
			txt[i++] = ch; txt[i] = '\0'; ch0 = ch; ch = nextCh();
			if(is_ope2(ch0, ch)) { txt[i++] = ch; ch = nextCh(); }
	}
	kd = get_kind(txt);
	if(kd == _Others)
	{
		printf("Error >= %s : %s\n", "잘못된 토큰", txt);
		exit(-1);
	}
	return setDataToken(kd, txt, 0);
}



int main(int argc, char const *argv[])
{
	if(argc < 2)
	{
		printf("사용법 : <paserTest.out> <대상 파일>");
		exit(-1);
	}

	txt = (char*)malloc(sizeof(char) * 128);
	if(txt == NULL)
	{
		printf("Error >= 파일 이름이 잘못됨");
		exit(-1);
	}

	TFile = fopen(argv[1], "r");
	if(TFile == NULL)
	{
		printf("Error >= 파일 이름이 잘못됨");
		exit(-1);
	}

	initCharType();
	printf("토큰\t번호\t문자열 정수값\n");
	for (token = nextToken(); token.Kind != _EOF; token = nextToken())
	{
		printf("%d\t%s\t%d\n", token.Kind, token.text, token.intVal);
	}
	return 0;
}