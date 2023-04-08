//-------------------------------------------------------------------------------------------------------
#include "AccessControlBase.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CAccessControlBase::CAccessControlBase(void)
{
}
//-------------------------------------------------------------------------------------------------------
CAccessControlBase::~CAccessControlBase(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::BasePrivate(void)
{
	wprintf_s(L"CAccessControlBase::BasePrivate() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::DummyPrivate(void)
{
	wprintf_s(L"CAccessControlBase::DummyPrivate() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::BaseProtected(void)
{
	wprintf_s(L"CAccessControlBase::BaseProtected() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::DummyProtected(void)
{
	wprintf_s(L"CAccessControlBase::DummyProtected() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::BasePublic(void)
{
	wprintf_s(L"CAccessControlBase::BasePublic() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::DummyPublic(void)
{
	wprintf_s(L"CAccessControlBase::DummyPublic() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::MemberConversionSucceeded(wstring Text)
{
	wprintf_s(L"MEMBER CONVERSION [%s] SUCCEEDED !\n",Text.c_str());
}
//-------------------------------------------------------------------------------------------------------
void CAccessControlBase::ExternalConversionSucceeded(wstring Text)
{
	wprintf_s(L"EXTERNAL CONVERSION [%s] SUCCEEDED !\n",Text.c_str());
}
//-------------------------------------------------------------------------------------------------------