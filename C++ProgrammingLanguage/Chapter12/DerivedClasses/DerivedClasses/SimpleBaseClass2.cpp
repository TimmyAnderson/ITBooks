//-------------------------------------------------------------------------------------------------------
#include "SimpleBaseClass2.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CSimpleBaseClass2::CSimpleBaseClass2(wstring Text)
	: MSimpleBaseClass2Name(Text)
{
}
//-------------------------------------------------------------------------------------------------------
CSimpleBaseClass2::~CSimpleBaseClass2(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CSimpleBaseClass2::PrintAbstractWithImplementation(void)
{
	wprintf(L"CSimpleBaseClass2 - MSimpleBaseClass2Name: [%s] !\n",MSimpleBaseClass2Name.c_str());
}
//-------------------------------------------------------------------------------------------------------
void CSimpleBaseClass2::PrintNonVirtual(void)
{
	wprintf(L"CSimpleBaseClass2 - MSimpleBaseClass2Name: [%s] !\n",MSimpleBaseClass2Name.c_str());
}
//-------------------------------------------------------------------------------------------------------