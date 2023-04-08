//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include "NamespaceTest.h"
#include "MyTemplate.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void ExceptionFunction(void)
{
	throw(wstring(L"Some EXCEPTION was thrown !"));
}
//-------------------------------------------------------------------------------------------------------
void CinTest(void)
{
	wcout << L"Enter one character !\n";

	wchar_t			Char;

	wcin >> Char;

	wcout << L"You entered: [" << Char << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void NamespaceTest(void)
{
	MyNamespace::SetValue(100);

	int				Value=MyNamespace::GetValue();

	wcout << L"Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void ExceptionTest(void)
{
	try
	{
		ExceptionFunction();
	}
	catch(wstring& E)
	{
		wcout << L"EXCEPTION: [" << E.c_str() << L"] !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void TemplateTest(void)
{
	CMyTemplate<int>		TemplateClass;

	TemplateClass.SetValue(100);

	int				Value=TemplateClass.GetValue();

	wcout << L"Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//CinTest();
	//NamespaceTest();
	//ExceptionTest();
	TemplateTest();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------