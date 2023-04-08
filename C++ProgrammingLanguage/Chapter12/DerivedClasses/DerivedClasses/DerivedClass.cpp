//-------------------------------------------------------------------------------------------------------
#include "DerivedClass.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CDerivedClass::CDerivedClass(CText& BaseClass1Name, CText& BaseClass2Name, CText& DerivedClassName)
	: CBaseClass1(BaseClass1Name), CBaseClass2(BaseClass2Name), MDerivedClassName(DerivedClassName)
{
	wprintf(L"CDerivedClass CONSTRUCTOR with value [%s] CALLED !\n",MDerivedClassName.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------
CDerivedClass::~CDerivedClass(void)
{
	wprintf(L"CDerivedClass DESTRUCTOR with value [%s] CALLED !\n",MDerivedClassName.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CDerivedClass::PrintAbstractWithImplementation(void)
{
	// !!! Explicitne zavolam implementovane ABSTRACT METOHDS v BASE CLASSES.
	CBaseClass1::PrintAbstractWithImplementation();
	CBaseClass2::PrintAbstractWithImplementation();

	wprintf(L"CDerivedClass - MDerivedClassName: [%s] !\n",MDerivedClassName.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------
void CDerivedClass::PrintNonVirtual(void)
{
	// !!! Zavolam ROVNAKO POMENOVANE METOHDS v BASE CLASSES.
	CBaseClass1::PrintNonVirtual();
	CBaseClass2::PrintNonVirtual();

	wprintf(L"CDerivedClass - MDerivedClassName: [%s] !\n",MDerivedClassName.GetText().c_str());
}
//-------------------------------------------------------------------------------------------------------