//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdarg>
#include "MyDebug.h"
#include "CClass.h"
#include "CTemplateClass.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClasses(void)
{
	PrintLineSeparator();

	CClass														Class(100);

	wcout << L"VARIABLE [" << MACRO_TO_STRING(Class) << L"] has VALUE [" << Class.GetField() << L"] !" << endl;

	PrintLineSeparator();

	CTemplateClass<wstring>										TemplateClass(L"Timmy Anderson");

	wcout << L"VARIABLE [" << MACRO_TO_STRING(TemplateClass) << L"] has VALUE [" << TemplateClass.GetField() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	TestClasses();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------