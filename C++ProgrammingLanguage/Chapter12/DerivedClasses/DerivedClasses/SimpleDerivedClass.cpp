//-------------------------------------------------------------------------------------------------------
#include "SimpleDerivedClass.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
CSimpleDerivedClass::CSimpleDerivedClass(wstring BaseClass1Name, wstring BaseClass2Name, wstring SimpleDerivedClassName)
	: CSimpleBaseClass1(BaseClass1Name), CSimpleBaseClass2(BaseClass2Name), MSimpleDerivedClassName(SimpleDerivedClassName)
{
}
//-------------------------------------------------------------------------------------------------------
CSimpleDerivedClass::~CSimpleDerivedClass(void)
{
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CSimpleDerivedClass::PrintAbstractWithImplementation(void)
{
	// !!! Explicitne zavolam implementovane ABSTRACT METOHDS v BASE CLASSES.
	CSimpleBaseClass1::PrintAbstractWithImplementation();
	CSimpleBaseClass2::PrintAbstractWithImplementation();

	wprintf(L"CSimpleDerivedClass - MSimpleDerivedClassName: [%s] !\n",MSimpleDerivedClassName.c_str());
}
//-------------------------------------------------------------------------------------------------------
void CSimpleDerivedClass::PrintNonVirtual(void)
{
	// !!! Zavolam ROVNAKO POMENOVANE METOHDS v BASE CLASSES.
	CSimpleBaseClass1::PrintNonVirtual();
	CSimpleBaseClass2::PrintNonVirtual();

	wprintf(L"CSimpleDerivedClass - MSimpleDerivedClassName: [%s] !\n",MSimpleDerivedClassName.c_str());
}
//-------------------------------------------------------------------------------------------------------