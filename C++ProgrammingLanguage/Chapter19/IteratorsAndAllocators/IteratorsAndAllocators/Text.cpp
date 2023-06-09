//-------------------------------------------------------------------------------------------------------
#include "Text.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CText::CText(wstring Text)
	: MText(Text)
{
	wprintf(L"CText CONSTRUCTOR with value [%s] CALLED !\n",MText.c_str());
}
//-------------------------------------------------------------------------------------------------------
CText::CText(const CText& Text)
	: MText(Text.MText)
{
	wprintf(L"CText COPY-CONSTRUCTOR with value [%s] CALLED !\n",MText.c_str());
}
//-------------------------------------------------------------------------------------------------------
CText::~CText(void)
{
	wprintf(L"CText DESTRUCTOR with value [%s] CALLED !\n",MText.c_str());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
const wstring& CText::GetText(void) const
{
	return(MText);
}
//-------------------------------------------------------------------------------------------------------