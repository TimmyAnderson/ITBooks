//-------------------------------------------------------------------------------------------------------
#include "MyStatic.h"
#include <stdio.h>
#include <string>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
const CMyText													CMyStatic::MStaticConstName(L"Timmy Anderson");
CMyText															CMyStatic::MStaticName(L"Jenny Thompson");
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CMyStatic::CMyStatic(void)
{
}
//-------------------------------------------------------------------------------------------------------
CMyStatic::~CMyStatic(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CMyStatic::PrintStatic(void)
{
	wprintf_s(L"MStaticConstName [%s], MStaticName [%s] !\n",MStaticConstName.GetText().c_str(),MStaticName.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------
void CMyStatic::PrintNonStatic(void)
{
	wprintf_s(L"MStaticConstName [%s], MStaticName [%s] !\n",MStaticConstName.GetText().c_str(),MStaticName.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------