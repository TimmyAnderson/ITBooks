//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateTemplateSpecialMethods2.h"
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CTemplateTemplateSpecialMethods2::~CTemplateTemplateSpecialMethods2(void) noexcept
{
	wcout << L"DESTRUCTOR CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
const wstring& CTemplateTemplateSpecialMethods2::GetValue(void) const noexcept
{
	return(MValue);
}
//----------------------------------------------------------------------------------------------------------------------