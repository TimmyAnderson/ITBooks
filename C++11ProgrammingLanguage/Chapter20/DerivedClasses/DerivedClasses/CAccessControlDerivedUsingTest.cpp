//-----------------------------------------------------------------------------
#include "CAccessControlDerivedUsingTest.h"
#include <iostream>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CAccessControlDerivedUsingTest::CAccessControlDerivedUsingTest(void)
{
}
//-----------------------------------------------------------------------------
CAccessControlDerivedUsingTest::~CAccessControlDerivedUsingTest(void)
{
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CAccessControlDerivedUsingTest::Test(void)
{
	wcout << L"CAccessControlDerivedUsingTest::Test() CALLED !" << endl;

	// Nepripustna, lebo je to PRIVATE MEMBER.
	//this->BasePrivate();

	// Metoda BaseProtected() kedze je PROTECTED je pristupna a to aj BEZ nutnosti pouzit USING DECLARATION.
	this->BaseProtected();

	this->BasePublic();

	// Nepripustna, lebo je to PRIVATE MEMBER.
	//this->DummyPrivate();

	// Metoda DummyProtected() kedze je PROTECTED je pristupna.
	this->DummyProtected();

	this->DummyPublic();
}
//-----------------------------------------------------------------------------