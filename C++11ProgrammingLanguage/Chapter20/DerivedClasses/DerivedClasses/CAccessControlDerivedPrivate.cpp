//-----------------------------------------------------------------------------
#include "CAccessControlDerivedPrivate.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAccessControlDerivedPrivate::CAccessControlDerivedPrivate(void)
{
}
//-----------------------------------------------------------------------------
CAccessControlDerivedPrivate::~CAccessControlDerivedPrivate(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedPrivate::DerivedPrivatePrivate(void)
{
	wcout << L"CAccessControlDerivedPrivate::DerivedPrivatePrivate() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedPrivate::DerivedPrivateProtected(void)
{
	wcout << L"CAccessControlDerivedPrivate::DerivedPrivateProtected() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedPrivate::DerivedPrivatePublic(void)
{
	wcout << L"CAccessControlDerivedPrivate::DerivedPrivatePublic() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedPrivate::TestDerivedPrivate(void)
{
	wcout << L"CAccessControlDerivedPrivate::TestDerivedPrivate() CALLED !" << endl;

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	this->BaseProtected();

	this->BasePublic();

	CAccessControlDerivedPrivate								Object;
	CAccessControlBase&											Reference=Object;

	Reference.MemberConversionSucceeded(L"CAccessControlDerivedPrivate ---> CAccessControlBase");
}
//-----------------------------------------------------------------------------