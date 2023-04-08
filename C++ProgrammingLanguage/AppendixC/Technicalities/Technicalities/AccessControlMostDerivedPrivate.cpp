//-------------------------------------------------------------------------------------------------------
#include "AccessControlMostDerivedPrivate.h"
#include <stdio.h>
#include "AccessControlBase.h"
//-------------------------------------------------------------------------------------------------------
CAccessControlMostDerivedPrivate::CAccessControlMostDerivedPrivate(void)
{
}
//-------------------------------------------------------------------------------------------------------
CAccessControlMostDerivedPrivate::~CAccessControlMostDerivedPrivate(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::MostDerivedPrivatePrivate(void)
{
	wprintf_s(L"CAccessControlMostDerivedPrivate::MostDerivedPrivatePrivate() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::MostDerivedPrivateProtected(void)
{
	wprintf_s(L"CAccessControlMostDerivedPrivate::MostDerivedPrivateProtected() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::MostDerivedPrivatePublic(void)
{
	wprintf_s(L"CAccessControlMostDerivedPrivate::MostDerivedPrivatePublic() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::TestMostDerivedPrivate(void)
{
	wprintf_s(L"CAccessControlMostDerivedPrivate::TestMostDerivedPrivate() CALLED !\n");

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	// !!! Nie je pristupna kvoli PRIVATE INHERITANCE.
	//this->BaseProtected();

	// !!! Nie je pristupna kvoli PRIVATE INHERITANCE.
	//this->BasePublic();

	/*
	CAccessControlMostDerivedPrivate							Object;
	// !!!!! Dokonca i DEKLARACIU PREMENNEJ na CAccessControlBase uz prehlasi kompilator ako CHYBU.
	CAccessControlBase*											Pointer;

	// !!! KONVERZIA NIE je MOZNA kvoli PRIVATE INHERITANCE.
	Pointer=&Object;

	Pointer->MemberConversionSucceeded(L"CAccessControlMostDerivedPrivate ---> CAccessControlBase");
	*/
}
//-------------------------------------------------------------------------------------------------------