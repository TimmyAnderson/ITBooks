//-------------------------------------------------------------------------------------------------------
#include "NameWithCopyConstructor.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CNameWithCopyConstructor::CNameWithCopyConstructor(void)
{
}
//-------------------------------------------------------------------------------------------------------
CNameWithCopyConstructor::CNameWithCopyConstructor(wstring FirstName, wstring LastName, int Age)
	: MFirstName(FirstName), MLastName(LastName), MAge(Age)
{
}
//-------------------------------------------------------------------------------------------------------
CNameWithCopyConstructor::CNameWithCopyConstructor(const CNameWithCopyConstructor& Original)
	: MFirstName(Original.MFirstName), MLastName(Original.MLastName), MAge(Original.MAge)
{
	wprintf_s(L"COPY CONSTUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CNameWithCopyConstructor::~CNameWithCopyConstructor(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CNameWithCopyConstructor::PrintNameToConsole(void)
{
	wprintf_s(L"Name: [%s %s], Age: [%d] !\n",MFirstName.c_str(),MLastName.c_str(),MAge);
}
//-------------------------------------------------------------------------------------------------------