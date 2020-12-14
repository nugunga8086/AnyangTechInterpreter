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


String newString();
void delString(String);
int __charlen(const char*);
int __strlen(String);
int __getlen(String);
wchar_t* __setWord(String, const wchar_t*);
wchar_t* __getWord(String);
wchar_t* __addWord(String, const wchar_t*);


#endif