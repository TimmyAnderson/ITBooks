//-------------------------------------------------------------------------------------------------------
#include "Base.h"
#include <iostream>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CBase::CBase(wstring BaseValue)
{
	MBaseValue=BaseValue;
}
//-------------------------------------------------------------------------------------------------------
CBase::~CBase(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CBase::Print(void)
{
	wcout << L"BASE CLASS - BaseValue: [" << MBaseValue << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------