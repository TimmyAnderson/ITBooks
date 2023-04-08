//-----------------------------------------------------------------------------
#include "CAccessControlDerivedProtected.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAccessControlDerivedProtected::CAccessControlDerivedProtected(void)
{
}
//-----------------------------------------------------------------------------
CAccessControlDerivedProtected::~CAccessControlDerivedProtected(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedProtected::DerivedProtectedPrivate(void)
{
	wcout << L"CAccessControlDerivedProtected::DerivedProtectedPrivate() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedProtected::DerivedProtectedProtected(void)
{
	wcout << L"CAccessControlDerivedProtected::DerivedProtectedProtected() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedProtected::DerivedProtectedPublic(void)
{
	wcout << L"CAccessControlDerivedProtected::DerivedProtectedPublic() CALLED !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedProtected::TestDerivedProtected(void)
{
	wcout << L"CAccessControlDerivedProtected::TestDerivedProtected() CALLED !" << endl;

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	this->BaseProtected();

	this->BasePublic();

	CAccessControlDerivedProtected								Object;
	CAccessControlBase&											Reference=Object;

	Reference.MemberConversionSucceeded(L"CAccessControlDerivedProtected ---> CAccessControlBase");
}
//-----------------------------------------------------------------------------