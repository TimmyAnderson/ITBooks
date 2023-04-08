//-----------------------------------------------------------------------------
#include "CAccessControlMostDerivedProtected.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAccessControlMostDerivedProtected::CAccessControlMostDerivedProtected(void)
{
}
//-----------------------------------------------------------------------------
CAccessControlMostDerivedProtected::~CAccessControlMostDerivedProtected(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::MostDerivedProtectedPrivate(void)
{
	wcout << L"CAccessControlMostDerivedProtected::MostDerivedProtectedPrivate() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::MostDerivedProtectedProtected(void)
{
	wcout << L"CAccessControlMostDerivedProtected::MostDerivedProtectedProtected() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::MostDerivedProtectedPublic(void)
{
	wcout << L"CAccessControlMostDerivedProtected::MostDerivedProtectedPublic() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlMostDerivedProtected::TestMostDerivedProtected(void)
{
	wcout << L"CAccessControlMostDerivedProtected::TestMostDerivedProtected() CALLED !" << endl;

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	// !!!!! Je pristupna kedze sa pouzila PROTECTED INHERITANCE. V PRIVATE INHERITANCE NIE JE PRISTUPNA.
	this->BaseProtected();

	// !!!!! Je pristupna kedze sa pouzila PROTECTED INHERITANCE. V PRIVATE INHERITANCE NIE JE PRISTUPNA.
	this->BasePublic();

	CAccessControlMostDerivedProtected							Object;

	// !!!!! KONVERZIA je MOZNA kvoli PROTECTED INHERITANCE. V PRIVATE INHERITANCE NIE JE KONVERZIA MOZNA.
	CAccessControlBase&											Reference=Object;

	Reference.MemberConversionSucceeded(L"CAccessControlMostDerivedProtected ---> CAccessControlBase");
}
//-----------------------------------------------------------------------------