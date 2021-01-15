/*
	만들면서 배우는 인터프리터를 보고 참고하여 제작하게 된 프로그램입니다.
	그래서 대부분의 사양을 이 책의 사양으로 잡아서 개발되었습니다.

*/
#include "Qi.h"
#include "Qi_prot.h"

int main(int argc, char *argv[])
{
	if (argc == 1) { cout << "프로그램 사용법 : Source filename\n"; exit(1); }
	convert_to_internalCode(argv[1]);
	syntaxChk();
	execute();
	return 0;
}

