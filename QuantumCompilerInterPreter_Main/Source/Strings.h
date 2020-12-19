#ifndef __USRStrings__
#define __USRStrings__

#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>

typedef struct StringTag
{
	wchar_t *value;

	int size;
	int length;

} *String;

/*
	String abc = newString();
	__setWord(abc, L"안녕하세요 저는 관종입니다. \n 만나서 방가워요");

	wprintf(L"%d\n", abc->length);

	__addWord(abc, L"\n안녕하세요 저는 누군가입니다. \n 만나서 너무 싫었어요");
	__addWord(abc, L"\n나는 안들리오..!");
	__addChar(abc, L'가');
	wprintf(L"\nAAAA\n%SAAAA\n", __getWord(abc));
	wprintf(L"length : %d, size : %d, Str : %S\n", abc->length, abc->size, __getWord(abc));

	delString(abc);
*/

String newString();
void delString(String);
int __charlen(const char*);
int __charfindlen(const char*, char);
int __strlen(String);
int __getlen(String);
int __findlen(String, wchar_t);
wchar_t* __setWord(String, const wchar_t*);
wchar_t* __getWord(String);
wchar_t* __addWord(String, const wchar_t*);
wchar_t* __addChar(String, const wchar_t);

#endif