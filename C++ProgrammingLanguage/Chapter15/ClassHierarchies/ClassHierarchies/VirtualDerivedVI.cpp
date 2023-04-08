//-------------------------------------------------------------------------------------------------------
#include "VirtualDerivedVI.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// !!! Kedze pouzivam VIRTUAL INHERITANCE, tak MUSIM zavolat i CONSTRUCTOR pre CBaseVI.
CVirtualDerivedVI::CVirtualDerivedVI(wstring SharedNameClass1, wstring SharedNameClass2, wstring SharedNameDerived)
	: CBaseVI1(SharedNameClass1), CBaseVI2(SharedNameClass2), CBaseVI(SharedNameDerived)
{
	wprintf_s(L"CVirtualDerivedVI CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CVirtualDerivedVI::~CVirtualDerivedVI(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CVirtualDerivedVI::Virtual1(void)
{
	wprintf_s(L"CVirtualDerivedVI - Virtual1() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CVirtualDerivedVI::Virtual2(void)
{
	wprintf_s(L"CVirtualDerivedVI - Virtual2() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CVirtualDerivedVI::Virtual3(void)
{
	wprintf_s(L"CVirtualDerivedVI - Virtual3() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------