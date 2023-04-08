//-------------------------------------------------------------------------------------------------------
#include "ComposedClass.h"
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
// Nedefinujem ziadne INITIALIZERS.
CComposedClass::CComposedClass(void)
{
	wprintf_s(L"CComposedClass CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
// !!! Prehodim poradie INITIALIZERS, ale VZDY sa NAJPRV zavola CClass1 CONSTRUCTOR a az po nom CClass2 CONSTRUCTOR.
CComposedClass::CComposedClass(int Dummy)
	: MField2(Dummy), MField1(Dummy)
{
	wprintf_s(L"CComposedClass NON-DEFAULT CONSTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
CComposedClass::~CComposedClass(void)
{
	wprintf_s(L"CComposedClass DESTRUCTOR CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void CComposedClass::DoNothing(void)
{
}
//-------------------------------------------------------------------------------------------------------