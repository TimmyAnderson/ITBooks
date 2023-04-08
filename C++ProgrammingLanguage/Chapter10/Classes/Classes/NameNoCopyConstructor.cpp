//-------------------------------------------------------------------------------------------------------
#include "NameNoCopyConstructor.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CNameNoCopyConstructor::CNameNoCopyConstructor(void)
{
}
//-------------------------------------------------------------------------------------------------------
CNameNoCopyConstructor::CNameNoCopyConstructor(wstring FirstName, wstring LastName, int Age)
	: MFirstName(FirstName), MLastName(LastName), MAge(Age)
{
}
//-------------------------------------------------------------------------------------------------------
CNameNoCopyConstructor::~CNameNoCopyConstructor(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CNameNoCopyConstructor::PrintNameToConsole(void)
{
	wprintf_s(L"Name: [%s %s], Age: [%d] !\n",MFirstName.c_str(),MLastName.c_str(),MAge);
}
//-------------------------------------------------------------------------------------------------------