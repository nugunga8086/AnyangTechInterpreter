#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


void polish(char* s);
int execute();
int getvalue(int ch);
int order(int ch);
void push();
int pop();

#define STK_SIZ 20
int stack[STK_SIZ + 1];
int stackPointer;
char polish_out[80];

int main()
{
	char siki[80];
	int ans, i;
	
	for (i = 0; i < 3; ++i)
	{
		printf("입력> ");
		scanf("%s", siki);
		
		polish(siki);
		if(polish_out[0] == '\0')
			exit(1);
		
		ans = execute();
		printf("변환: %s\n", polish_out);
		printf("결과: %d\n\n", ans);
	}

	return 0;
}

void polish(char *s)
{
	int wk;
	char *out = polish_out;
	stackPointer = 0;

	while(true)
	{
		while(isspace(*s)) { ++s; }
		if(*s == '\0')
		{
			while(stackPointer > 0)
				if((*out++ = pop()) == '(')
				{	
					printf("'('가 올바르지 못함\n");
					exit(1);
				}
			break;
		}
		if(islower(*s) || isdigit(*s))
		{
			*out++ = *s++;
			continue;
		}
		switch(*s)
		{
			case '(':
				push(*s);
				break;
			case ')':
				while((wk = pop()) != '(')
				{
					*out++ = wk;
					if(stackPointer == 0)
					{
						printf("'('가 올바르지 못함\n");
						exit(1);
					}
				}
				break;
			default:
				if(order(*s) == -1)
				{
					printf("바르지 않은 문자 : %c\n", *s);
					exit(1);
				}
				while(stackPointer > 0 && (order(stack[stackPointer]) >= order(*s)))
					*out++ = pop();
				push(*s);
		}
		s++;
	}
	*out = '\0';
}

int execute()
{
	int d1, d2;
	char* s;

	stackPointer = 0;
	for (s=polish_out; *s; s++)
	{
		if(islower(*s))
			push(getvalue(*s));
		else if(isdigit(*s))
			push(*s - '0');
		else
		{
			d2 = pop(); d1 = pop();
			switch(*s) 
			{
				case '+': push(d1 + d2); break;
				case '-': push(d1 - d2); break;
				case '*': push(d1 * d2); break; 
				case '/': 
					if(d2 == 0) 
					{
						printf("0으로 나눔\n");
						exit(1);
					}
					push(d1 / d2);
					break;
			}
		}
	}
	if(stackPointer != 1)
	{
		printf("Error\n");
		exit(1);
	}
	return pop();
}

int getvalue(int ch)
{
	if(islower(ch)) return ch-'a' + 1;
	return 0;
}

int order(int ch)
{
	switch (ch)
	{
		case '*': case '/': return 3;
		case '+': case '-': return 2;
		case '(': return 1;
	}
	return -1;
}

void push(int n)
{
	if(stackPointer+1 > STK_SIZ)
	{
		printf("스택 오버플로우 발생");
		exit(1);
	}
	stack[++stackPointer] = n;
}

int pop()
{
	if(stackPointer < 1) 
	{
		printf("%s\n", "스택 언더플로우 발생");
		exit(1);
	}
	return stack[stackPointer--];
}