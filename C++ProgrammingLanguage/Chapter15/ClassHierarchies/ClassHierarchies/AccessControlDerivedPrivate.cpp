//-------------------------------------------------------------------------------------------------------
#include "AccessControlDerivedPrivate.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
CAccessControlDerivedPrivate::CAccessControlDerivedPrivate(void)
{
}
//-------------------------------------------------------------------------------------------------------
CAccessControlDerivedPrivate::~CAccessControlDerivedPrivate(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedPrivate::DerivedPrivatePrivate(void)
{
	wprintf_s(L"CAccessControlDerivedPrivate::DerivedPrivatePrivate() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedPrivate::DerivedPrivateProtected(void)
{
	wprintf_s(L"CAccessControlDerivedPrivate::DerivedPrivateProtected() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedPrivate::DerivedPrivatePublic(void)
{
	wprintf_s(L"CAccessControlDerivedPrivate::DerivedPrivatePublic() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlDerivedPrivate::TestDerivedPrivate(void)
{
	wprintf_s(L"CAccessControlDerivedPrivate::TestDerivedPrivate() CALLED !\n");

	// Je to PRIVATE METHOD.
	//this->BasePrivate();

	this->BaseProtected();

	this->BasePublic();

	CAccessControlDerivedPrivate								Object;
	CAccessControlBase*											Pointer;

	Pointer=&Object;

	Pointer->MemberConversionSucceeded(L"CAccessControlDerivedPrivate ---> CAccessControlBase");
}
//-------------------------------------------------------------------------------------------------------