//-------------------------------------------------------------------------------------------------------
#include "BaseClass2.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CBaseClass2::CBaseClass2(CText& Text)
	: MBaseClass2Name(Text)
{
	wprintf(L"CBaseClass2 CONSTRUCTOR with value [%s] CALLED !\n",MBaseClass2Name.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------
CBaseClass2::~CBaseClass2(void)
{
	wprintf(L"CBaseClass2 DESTRUCTOR with value [%s] CALLED !\n",MBaseClass2Name.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CBaseClass2::PrintAbstractWithImplementation(void)
{
	wprintf(L"CBaseClass2 - MBaseClass2Name: [%s] !\n",MBaseClass2Name.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------
void CBaseClass2::PrintNonVirtual(void)
{
	wprintf(L"CBaseClass2 - MBaseClass2Name: [%s] !\n",MBaseClass2Name.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------