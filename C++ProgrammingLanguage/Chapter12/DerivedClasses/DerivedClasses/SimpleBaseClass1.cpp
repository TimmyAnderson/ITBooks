//-------------------------------------------------------------------------------------------------------
#include "SimpleBaseClass1.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CSimpleBaseClass1::CSimpleBaseClass1(wstring Text)
	: MSimpleBaseClass1Name(Text)
{
}
//-------------------------------------------------------------------------------------------------------
CSimpleBaseClass1::~CSimpleBaseClass1(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CSimpleBaseClass1::PrintAbstractWithImplementation(void)
{
	wprintf(L"CSimpleBaseClass1 - MSimpleBaseClass1Name: [%s] !\n",MSimpleBaseClass1Name.c_str());
}
//-------------------------------------------------------------------------------------------------------
void CSimpleBaseClass1::PrintNonVirtual(void)
{
	wprintf(L"CSimpleBaseClass1 - MSimpleBaseClass1Name: [%s] !\n",MSimpleBaseClass1Name.c_str());
}
//-------------------------------------------------------------------------------------------------------