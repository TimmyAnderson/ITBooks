//-------------------------------------------------------------------------------------------------------
#include "AccessControlMostDerivedProtected.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CAccessControlMostDerivedProtected::CAccessControlMostDerivedProtected(void)
{
}
//-------------------------------------------------------------------------------------------------------
CAccessControlMostDerivedProtected::~CAccessControlMostDerivedProtected(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::MostDerivedProtectedPrivate(void)
{
	wprintf_s(L"CAccessControlMostDerivedProtected::MostDerivedProtectedPrivate() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::MostDerivedProtectedProtected(void)
{
	wprintf_s(L"CAccessControlMostDerivedProtected::MostDerivedProtectedProtected() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::MostDerivedProtectedPublic(void)
{
	wprintf_s(L"CAccessControlMostDerivedProtected::MostDerivedProtectedPublic() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::TestMostDerivedProtected(void)
{
	wprintf_s(L"CAccessControlMostDerivedProtected::TestMostDerivedProtected() CALLED !\n");

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	// !!!!! Je pristupna kedze sa pouzila PROTECTED INHERITANCE. V PRIVATE INHERITANCE NIE JE PRISTUPNA.
	this->BaseProtected();

	// !!!!! Je pristupna kedze sa pouzila PROTECTED INHERITANCE. V PRIVATE INHERITANCE NIE JE PRISTUPNA.
	this->BasePublic();

	CAccessControlMostDerivedProtected							Object;
	CAccessControlBase*											Pointer;

	// !!!!! KONVERZIA je MOZNA kvoli PROTECTED INHERITANCE. V PRIVATE INHERITANCE NIE JE KONVERZIA MOZNA.
	Pointer=&Object;

	Pointer->MemberConversionSucceeded(L"CAccessControlMostDerivedProtected ---> CAccessControlBase");
}
//-------------------------------------------------------------------------------------------------------