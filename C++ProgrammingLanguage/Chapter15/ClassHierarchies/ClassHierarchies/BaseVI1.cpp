//-------------------------------------------------------------------------------------------------------
#include "BaseVI1.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// !!!!! Kedze CBaseVI1 dedi VIRTUALNE z CBaseVI, tak CONSTRUCTOR CBaseVI sa NEVOLA z tohto CONSTRUCTOR, ale z CONSTRUCTOR CVirtualDerivedVI.
CBaseVI1::CBaseVI1(wstring SharedName)
	: CBaseVI(L"CBaseVI1 - " + SharedName)
{
	wprintf_s(L"CBaseVI1 CONSTRUCTOR CALLED with PARAMETER [%s] and MSharedName [%s] !\n",SharedName.c_str(),MSharedName.c_str());
}
//-------------------------------------------------------------------------------------------------------
CBaseVI1::~CBaseVI1(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CBaseVI1::Virtual1(void)
{
	wprintf_s(L"CBaseVI1 - Virtual1() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CBaseVI1::Virtual2(void)
{
	wprintf_s(L"CBaseVI1 - Virtual2() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CBaseVI1::Virtual3(void)
{
	wprintf_s(L"CBaseVI1 - Virtual3() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------