
#include "Strings.h"

String newString()
{
	String temp = NULL;
	temp = (String)malloc(sizeof(struct StringTag));
	if(temp != NULL)
	{

	// 지역 설정
#define LC_S_Korean
#	ifdef LC_S_Korean
		setlocale(LC_ALL, "ko_KR.UTF-8");
#endif
#ifdef LC_S_English
		setlocale(LC_ALL, "UTF-8");
#endif
		temp->value = NULL;
		temp->value = (wchar_t*) malloc(sizeof(wchar_t) * 128);
		if(temp->value != NULL)
		{
			temp->size = 128;
			temp->length = 0;
			return temp;
		}
		else
		{
			printf("wchar_t 배열 메모리 확보 실패\n");
			exit(-1);
		}
	}
	else
	{
		printf("String 구조체 메모리 확보 실패\n");
		exit(-1);
	}
	return NULL;
}

void delString(String str)
{
	if(str->value != NULL && str != NULL)
	{
		free(str->value);
		str->value = NULL;

		free(str);
		str = NULL;
	}
	else
	{
		printf("메모리 해제 실패, 초기화 되지 않은 메모리 사용\n");
		exit(-1);
	}

}

int __charlen(const char* word)
{
	return __charfindlen(word, '\0');
}

int __charfindlen(const char* word, char ch)
{
	int i, wordsize = __charlen(word);
	for (i = 0; i < wordsize; i++)
	{
		if(word[i] == ch)
			return i;
		else
			continue;
	}
	return false;
}

// String의 길이 구하기
int __strlen(String str) // \0까지의 길이를 구하는 함수
{
	return __findlen(str, '\0');
}

int __getlen(String str) // length를 반환해주는 함수
{
	return str->length;
}

int __findlen(String str, wchar_t ch)
{
	int i, isbool=false;
	for (i = 0; i < str->size; i++)
	{
		isbool = str->value[i] == ch ? true : false;
		if(isbool)
			return i;
		else
			continue;
	}
	return false;
}

// 저장
wchar_t* __setWord(String str, const wchar_t* word)
{
	wchar_t* cacheCh = str->value;
	int i, sizeWord = wcslen(word);
	for (i = 0; i < sizeWord; i++)
	{
		cacheCh[i] = word[i];
	}

	str->length = sizeWord;

	return (wchar_t*)word;
}

wchar_t* __getWord(String str)
{
	return str->value;
}

wchar_t* __addWord(String str, const wchar_t* word)
{
	wchar_t* cacheCh = str->value;
	int i, sizeWord = wcslen(word);
	for (i = 0; i < sizeWord; ++i)
	{
		cacheCh[i + str->length] = word[i];
	}
	str->length += sizeWord;
	return str->value;
}

wchar_t* __addChar(String str, const wchar_t ch)
{
	str->value[str->length++] = ch;
	return str->value;
}