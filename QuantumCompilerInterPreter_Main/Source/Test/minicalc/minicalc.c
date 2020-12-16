#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum TokenKindTag{
	_Print = 1,
	_Lparen,
	_Rparen,
	_Plus,
	_Minus,
	_Multi,
	_Divi,
	_Set_Equals,
	_Var_Name,
	_IntNum,
	_EOF_Token,
	_Others
} TokenKind;

typedef struct TokenTag
{
	TokenKind kind;
	int intval;
} Token;

Token setToken()
{
	Token token;
	token.kind = _Others;
	token.intval = 0;
	return token;
}

Token setDataToken(TokenKind Tkind, int in)
{
	Token token;
	token.kind = Tkind;
	token.intval = in;
	return token;
}

void input();
void statment();
void expression();
void term();
void factor();
Token nextToken();
int nextCh();
void operate(TokenKind);
void push(int n);
int pop();
void CheckToken(TokenKind);

#define STK_SIZ 20
int stack[STK_SIZ + 1];
int stackPointer;
Token token;
char buf[80], *bufp;
int ch;
int var[26];
int errF;

int main()
{
	while(true)
	{
		input();
		token = nextToken();
		if(token.kind == _EOF_Token)
			exit(1);
		statment();
		if(errF)
			printf("Error 발생");
	}
	return 0;
}

void input()
{
	errF = false;
	stackPointer = 0;
	scanf("%s", buf);
	bufp = buf;
	ch = nextCh();
}

void statment()
{
	int vNbr;

	switch(token.kind)
	{
		case _Var_Name:
			vNbr = token.intval;
			token = nextToken();
			CheckToken(_Set_Equals);
			if(errF)
				break;
			token = nextToken();
			expression();
			var[vNbr] = pop();
			break;
		case _Print:
			token = nextToken();
			expression();
			CheckToken(_EOF_Token);
			if(errF)
				break;
			printf("%d\n", pop());
			return;
		default:
			errF = true;
	}
	CheckToken(_EOF_Token);
}

void expression()
{
	TokenKind op;

	term();
	while(token.kind == _Plus || token.kind == _Minus)
	{
		op = token.kind;
		token = nextToken();
		term();
		operate(op);
	}
}

void term()
{
	TokenKind op;

	factor();
	while(token.kind == _Multi || token.kind == _Divi)
	{
		op = token.kind;
		token = nextToken();
		factor();
		operate(op);
	}
}

void factor()
{
	switch(token.kind)
	{
		case _Var_Name:
			push(var[token.intval]);
			break;
		case _IntNum:
			push(token.intval);
			break;
		case _Lparen:
			token = nextToken();
			expression();
			CheckToken(_Rparen);
			break;
		default:
			errF = true;
	}
	token = nextToken();
}

Token nextToken()
{
	TokenKind kd = _Others;
	int num;

	while(isspace(ch))
		ch = nextCh();


	if(isdigit(ch))
	{
		for(num = 0; isdigit(ch); ch = nextCh())
			num = num*10 + (ch-'0');
		return setDataToken(_IntNum, num);
	}
	else if(islower(ch))
	{
		num = ch - 'a';
		ch = nextCh();
		return setDataToken(_Var_Name, num);
	}
	else
	{
		switch(ch)
		{
			case '(':
				kd = _Lparen;
				break;
			case ')':
				kd = _Rparen;
				break;
			case '+':
				kd = _Plus;
				break;
			case '-':
				kd = _Minus;
				break;
			case '*':
				kd = _Multi;
				break;
			case '/':
				kd = _Divi;
				break;
			case '=':
				kd = _Set_Equals;
				break;
			case '?':
				kd = _Print;
				break;
			case '\0':
				kd = _EOF_Token;
				break;
		}
		ch = nextCh();
		return setDataToken(kd, 0);
	}
}

int nextCh()
{
	if(*bufp == '\0')
		return '\0';
	else
		return *bufp++;
}

void operate(TokenKind op)
{
	int d2 = pop(), d1 = pop();

	if(op==_Divi && d2 == 0)
	{
		printf("0으로 나눌 수 없음\n");
		errF = true;
	}

	if(errF)
		return;

	switch(op)
	{
		case _Plus:
			push(d1 + d2);
			break;
		case _Minus:
			push(d1 - d2);
			break;
		case _Multi:
			push(d1 * d2);
			break;
		case _Divi:
			push(d1 / d2);
			break;
	}
}

void push(int n)
{
	if(errF) return;
	if(stackPointer+1 > STK_SIZ)
	{
		printf("%s\n", "스택 오버플로우 발생");
		exit(1);
	}
	stack[++stackPointer] = n;
}

int pop()
{
	if(errF) return 1;
	if(stackPointer < 1)
	{
		printf("%s\n", "스택 언더플로우 발생");
		exit(1);
	}
	return stack[stackPointer--];
}

void CheckToken(TokenKind kd)
{
	if(token.kind != kd) 
		errF = true;
}