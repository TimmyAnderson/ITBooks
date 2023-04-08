//-------------------------------------------------------------------------------------------------------
#include "Base2.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CBase2::CBase2(wstring SharedName)
	: MSharedName(SharedName), CBase(L"CBase - " + SharedName)
{
}
//-------------------------------------------------------------------------------------------------------
CBase2::~CBase2(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CBase2::NotOverrided(void)
{
	wprintf_s(L"CBase2 - NotOverrided() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CBase2::Overrided(void)
{
	wprintf_s(L"CBase2 - Overrided() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CBase2::Ambiguity1(double Value)
{
	wprintf_s(L"CBase2 DOUBLE - Ambiguity1() with PARAM [%f] CALLED !\n",Value);
}
//-------------------------------------------------------------------------------------------------------
void CBase2::Ambiguity2(double Value)
{
	wprintf_s(L"CBase2 DOUBLE - Ambiguity2() with PARAM [%f] CALLED !\n",Value);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CBase2::Virtual1(void)
{
	wprintf_s(L"CBase2 - Virtual1() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CBase2::Virtual2(void)
{
	wprintf_s(L"CBase2 - Virtual2() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CBase2::Virtual3(void)
{
	wprintf_s(L"CBase2 - Virtual3() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------