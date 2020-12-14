#include <stdio.h>
#include "Strings.h"

int main()
{
	String abc = newString();
	__setWord(abc, L"안녕하세요 저는 최진원입니다. \n 만나서 방가워요");

	wprintf(L"%S\n", __getWord(abc));

	__addWord(abc, L"\n안녕하세요 저는 누군가입니다. \n 만나서 너무 싫었어요");
	__addWord(abc, L"\n나는 안들리오..!");
	wprintf(L"\nAAAA\n%SAAAA\n", __getWord(abc));

	delString(abc);

	return 0;
}