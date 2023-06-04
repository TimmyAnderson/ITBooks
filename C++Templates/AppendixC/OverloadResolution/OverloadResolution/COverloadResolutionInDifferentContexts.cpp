//----------------------------------------------------------------------------------------------------------------------
#include "COverloadResolutionInDifferentContexts.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
COverloadResolutionInDifferentContexts::COverloadResolutionInDifferentContexts(long Value)
	: MValue1(Value), MValue2(), MValue3()
{
	wcout << L"CONSTRUCTOR [COverloadResolutionInDifferentContexts(long Value)] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
COverloadResolutionInDifferentContexts::COverloadResolutionInDifferentContexts(double Value)
	: MValue1(), MValue2(Value), MValue3()
{
	wcout << L"CONSTRUCTOR [COverloadResolutionInDifferentContexts(double Value)] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
COverloadResolutionInDifferentContexts::COverloadResolutionInDifferentContexts(const wstring& Value)
	: MValue1(), MValue2(), MValue3(Value)
{
	wcout << L"CONSTRUCTOR [COverloadResolutionInDifferentContexts(const wstring& Value)] CALLED !" << endl;
}
//----------------------------------------------------------------------------------------------------------------------
COverloadResolutionInDifferentContexts::~COverloadResolutionInDifferentContexts(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
COverloadResolutionInDifferentContexts::operator long(void) const
{
	wcout << L"OPERATOR [operator long(void) const] CALLED !" << endl;

	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
COverloadResolutionInDifferentContexts::operator double(void) const
{
	wcout << L"OPERATOR [operator double(void) const] CALLED !" << endl;

	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
long COverloadResolutionInDifferentContexts::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
double COverloadResolutionInDifferentContexts::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
const wstring& COverloadResolutionInDifferentContexts::GetValue3(void) const noexcept
{
	return(MValue3);
}
//----------------------------------------------------------------------------------------------------------------------