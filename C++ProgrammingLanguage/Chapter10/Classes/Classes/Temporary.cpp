//-------------------------------------------------------------------------------------------------------
#include "Temporary.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CTemporary::CTemporary(void)
	: MText(L"")
{
	wprintf_s(L"DEFAULT CONSTRUCTOR - Text: [%s] !\n",MText.c_str());
}
//-------------------------------------------------------------------------------------------------------
CTemporary::CTemporary(std::wstring Text)
	: MText(Text)
{
	wprintf_s(L"CONSTRUCTOR - Text: [%s] !\n",MText.c_str());
}
//-------------------------------------------------------------------------------------------------------
CTemporary::~CTemporary(void)
{
	wprintf_s(L"DESTRUCTOR - Text: [%s] !\n",MText.c_str());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CTemporary CTemporary::operator+(CTemporary& RightOperand)
{
	wstring														NewText=MText + L" " + RightOperand.MText;
	CTemporary													Result(NewText);

	return(Result);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CTemporary::Print(void)
{
	wprintf_s(L"Print() - Text: [%s] !\n",MText.c_str());
}
//-------------------------------------------------------------------------------------------------------