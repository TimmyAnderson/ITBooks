//-----------------------------------------------------------------------------
#include "CAccessControlMostDerivedPrivate.h"
#include "CAccessControlBase.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAccessControlMostDerivedPrivate::CAccessControlMostDerivedPrivate(void)
{
}
//-----------------------------------------------------------------------------
CAccessControlMostDerivedPrivate::~CAccessControlMostDerivedPrivate(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::MostDerivedPrivatePrivate(void)
{
	wcout << L"CAccessControlMostDerivedPrivate::MostDerivedPrivatePrivate() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::MostDerivedPrivateProtected(void)
{
	wcout << L"CAccessControlMostDerivedPrivate::MostDerivedPrivateProtected() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::MostDerivedPrivatePublic(void)
{
	wcout << L"CAccessControlMostDerivedPrivate::MostDerivedPrivatePublic() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedPrivate::TestMostDerivedPrivate(void)
{
	wcout << L"CAccessControlMostDerivedPrivate::TestMostDerivedPrivate() CALLED !" << endl;

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	// !!! Nie je pristupna kvoli PRIVATE INHERITANCE.
	//this->BaseProtected();

	// !!! Nie je pristupna kvoli PRIVATE INHERITANCE.
	//this->BasePublic();

	/*
	CAccessControlMostDerivedPrivate							Object;

	// !!! KONVERZIA NIE je MOZNA kvoli PRIVATE INHERITANCE.
	CAccessControlBase&											Reference=Object;

	Reference.MemberConversionSucceeded(L"CAccessControlMostDerivedPrivate ---> CAccessControlBase");
	*/
}
//-----------------------------------------------------------------------------