#ifndef __QCI_G_Struct
#define __QCI_G_Struct

typedef enum TokenKindTag
{
	_KIND_Others,
	_KIND_Letter,
	_Kind_Digit,
	_KIND_Var,						// 변수 var
	_KIND_IDent,					// 변수 또는 함수의 이름
	_KIND_Gvar,						// 전역 변수의 이름
	_Kind_Lvar,						// 지역 변수의 이름
	_KIND_Fcall,					// 함수 호출
	_KIND_Func,						// 함수 func
	_KIND_Equal,					// = or ==
	_KIND_NotEqual,					// !=
	_KIND_Small,					// <
	_KIND_SmallEqual,				// <=
	_KIND_Big,						// >
	_KIND_BigEqual,					// >=
	_KIND_Pointer,					// 포인터 pointer
	_KIND_LParen,					// (
	_KIND_RParen,					// )
	_KIND_LBrace,					// {
	_KIND_RBrace,					// }
	_KIND_LBrack,					// [
	_KIND_RBrack,					// ]
	_KIND_Colon,					// :
	_KIND_Plus,						// Plus +
	_Kind_Minus,					// Minus -
	_KIND_Multi,					// Multi *
	_KIND_Divi,						// Divi /
	_Kind_Percent,					// modu % or 백분율
	_KIND_EOF						// EOF
} TokenKind;

typedef struct TokenTag
{
	TokenKind kind;
	char* Text;
	double Ivalue;
} Token;




#endif