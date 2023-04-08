//-------------------------------------------------------------------------------------------------------
#include "Name.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// !!! Definicia STATICKEJ premennej.
CName															CName::JENNY(L"Jenny",L"Thompson",13);
//-------------------------------------------------------------------------------------------------------
CName::CName(void)
	: MFirstName(L""), MLastName(L""), MAge(0)
{
}
//-------------------------------------------------------------------------------------------------------
CName::CName(wstring FirstName, wstring LastName, int Age)
	: MFirstName(FirstName), MLastName(LastName), MAge(Age)
{
}
//-------------------------------------------------------------------------------------------------------
CName::~CName(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
bool CName::operator==(CName& O)
{
	wprintf_s(L"MEMBER operator== CALLED !\n");

	if (MFirstName!=O.MFirstName)
	{
		return(false);
	}

	if (MLastName!=O.MLastName)
	{
		return(false);
	}

	if (MAge!=O.MAge)
	{
		return(false);
	}

	return(true);
}
//-------------------------------------------------------------------------------------------------------
/*
bool CName::operator==(CName& O1, CName& O2)
{
	wprintf_s(L"STATIC operator== CALLED !\n");

	if (O1.MFirstName!=O2.MFirstName)
	{
		return(false);
	}

	if (O1.MLastName!=O2.MLastName)
	{
		return(false);
	}

	if (O1.MAge!=O2.MAge)
	{
		return(false);
	}

	return(true);
}
*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CName::StaticPrintNameToConsole(CName& Name)
{
	wprintf_s(L"Name: [%s %s], Age: [%d] !\n",Name.MFirstName.c_str(),Name.MLastName.c_str(),Name.MAge);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
wstring CName::GetFirstName(void) const
{
	return(MFirstName);
}
//-------------------------------------------------------------------------------------------------------
void CName::SetFirstName(wstring FirstName)
{
	MFirstName=FirstName;
}
//-------------------------------------------------------------------------------------------------------
wstring CName::GetLastName(void) const
{
	return(MLastName);
}
//-------------------------------------------------------------------------------------------------------
void CName::SetLastName(wstring LastName)
{
	MLastName=LastName;
}
//-------------------------------------------------------------------------------------------------------
int CName::GetAge(void) const
{
	return(MAge);
}
//-------------------------------------------------------------------------------------------------------
void CName::SetAge(int Age)
{
	MAge=Age;
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CName::PrintNameToConsole(void) const
{
	wprintf_s(L"Name: [%s %s], Age: [%d] !\n",MFirstName.c_str(),MLastName.c_str(),MAge);
}
//-------------------------------------------------------------------------------------------------------
/*
void CName::SetAllFields(std::wstring FirstName, std::wstring LastName, int Age) const
{
	// !!! CONST metoda NEMOZE volat NON-CONST METODY.
	SetFirstName(FirstName);
	SetLastName(LastName);
	SetAge(Age);
}
*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CName::SetAllFields(std::wstring FirstName, std::wstring LastName, int Age)
{
	// !!! CONST metoda NEMOZE volat NON-CONST METODY.
	SetFirstName(FirstName);
	SetLastName(LastName);
	SetAge(Age);
}
//-------------------------------------------------------------------------------------------------------
CName& CName::ChainMethod1(void)
{
	wprintf(L"ChainMethod1() CALLED !\n");

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
CName& CName::ChainMethod2(void)
{
	wprintf(L"ChainMethod2() CALLED !\n");

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
const CName& CName::ConstChainMethod1(void) const
{
	wprintf(L"ConstChainMethod1() CALLED !\n");

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
const CName& CName::ConstChainMethod2(void) const
{
	wprintf(L"ConstChainMethod2() CALLED !\n");

	return(*this);
}
//-------------------------------------------------------------------------------------------------------
/*
// !!! Objekt 'this' je v CONST metodach typu 'const CName*'.
CName& CName::ConstChainMethodError(void) const
{
	wprintf(L"ConstChainMethodError() CALLED !\n");

	// !!! Toto NEFUNGUJE, pretoze 'this' je v CONST metodach 'const CName*' a NIE 'CName*'.
	return(*this);
}
*/
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CName::NonConstSetMutableText(wstring Text)
{
	MMutableText=Text;
	MNonMutableText=Text;
}
//-------------------------------------------------------------------------------------------------------
void CName::ConstSetMutableText(wstring Text) const
{
	// !!! Do MUTABLE premennej JE MOZNE zapisat hodnotu v CONST metode.
	MMutableText=Text;

	// !!! Do NON-MUTABLE premennej NIE JE MOZNE zapisat hodnotu v CONST metode.
	//MNonMutableText=Text;
}
//-------------------------------------------------------------------------------------------------------
void CName::PrintMutableNonMutableTexts(wstring Prefix) const
{
	wprintf_s(L"%s - MMutableText: [%s] !\n",Prefix.c_str(),MMutableText.c_str());
	wprintf_s(L"%s - MNonMutableText: [%s] !\n",Prefix.c_str(),MNonMutableText.c_str());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! LINKER ERROR. INLINE metoda NEMOZE byt definovana v CPP subore, pretoze KOMPILATOR by nemal pristupne v INYCH CPP FILES jej TELO a NEMOHOL by ho NAHRADIT na mieste volania INLINE METODY.
inline void CName::Inline3(void)
{
	wprintf_s(L"Inline3() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------