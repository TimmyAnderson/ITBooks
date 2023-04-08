//-------------------------------------------------------------------------------------------------------
#include "DerivedPolymorphism.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CDerivedPolymorphism::CDerivedPolymorphism(wstring BaseText1, wstring BaseText2, wstring DerivedText)
	: CBasePolymorphism(BaseText1,BaseText2), MDerivedText(DerivedText)
{
}
//-------------------------------------------------------------------------------------------------------
CDerivedPolymorphism::~CDerivedPolymorphism(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CDerivedPolymorphism::Print(void)
{
	wprintf_s(L"CDerivedPolymorphism - DerivedText: [%s] !\n",MDerivedText.c_str());
}
//-------------------------------------------------------------------------------------------------------
const wstring& CDerivedPolymorphism::GetDerivedText(void) const
{
	return(MDerivedText);
}
//-------------------------------------------------------------------------------------------------------