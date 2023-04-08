//-------------------------------------------------------------------------------------------------------
#include "AccessControlDerivedProtected.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CAccessControlDerivedProtected::CAccessControlDerivedProtected(void)
{
}
//-------------------------------------------------------------------------------------------------------
CAccessControlDerivedProtected::~CAccessControlDerivedProtected(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedProtected::DerivedProtectedPrivate(void)
{
	wprintf_s(L"CAccessControlDerivedProtected::DerivedProtectedPrivate() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedProtected::DerivedProtectedProtected(void)
{
	wprintf_s(L"CAccessControlDerivedProtected::DerivedProtectedProtected() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedProtected::DerivedProtectedPublic(void)
{
	wprintf_s(L"CAccessControlDerivedProtected::DerivedProtectedPublic() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedProtected::TestDerivedProtected(void)
{
	wprintf_s(L"CAccessControlDerivedProtected::TestDerivedProtected() CALLED !\n");

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	this->BaseProtected();

	this->BasePublic();

	CAccessControlDerivedProtected								Object;
	CAccessControlBase*											Pointer;

	Pointer=&Object;

	Pointer->MemberConversionSucceeded(L"CAccessControlDerivedProtected ---> CAccessControlBase");
}
//-------------------------------------------------------------------------------------------------------