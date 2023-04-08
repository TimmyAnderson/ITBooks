//-----------------------------------------------------------------------------
#include "MyDebug.h"
#include <iostream>
#include <locale>
#include <codecvt>
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t)
{
	wcout << L"\n\n\nInvalid parameter detected in FUNCTION [" << Function << L"] ! FILE [" << File << L"] LINE [" << Line << L"] !" << endl;
	wcout << L"EXPRESSION: [" << Expression << L"] !\n\n\n";
}
//-----------------------------------------------------------------------------
void SafeMain(void)
{
#ifdef _MSC_VER
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, 0);
#endif
}
//-----------------------------------------------------------------------------
void ShowExitLine(void)
{
#ifdef _MSC_VER
	wcout << L"\nPress any key to EXIT !" << endl;
	_getch();
#endif
}
//-----------------------------------------------------------------------------
void PrintLineSeparator(bool UseWideChar)
{
	if (UseWideChar==true)
	{
		wcout << L"-------------------------------------------------------------------------------" << endl;
	}
	else
	{
		cout << "-------------------------------------------------------------------------------" << endl;
	}
}
//-----------------------------------------------------------------------------
string ConvertWideStringToString(const wstring& Value)
{
	const ctype<wchar_t>&										FacetCType=use_facet<ctype<wchar_t>>(locale::classic());
	string														Result;

	for(wchar_t WideChar : Value)
	{
		// !!! Konvertuje WIDE CHARACTER na CHARACTER, pricom sa pouzije CHARACTER '?', ake CONVERSION ZLYHA.
		char													Char=FacetCType.narrow(WideChar,'?');

		Result.push_back(Char);
	}

	return(Result);
}
//-----------------------------------------------------------------------------
wstring ConvertStringToWideString(const string& Value)
{
	const ctype<wchar_t>&										FacetCType=use_facet<ctype<wchar_t>>(locale::classic());
	wstring														Result;

	for(char Char : Value)
	{
		// !!! Konvertuje CHARACTER na WIDE CHARACTER.
		wchar_t													WideChar=FacetCType.widen(Char);

		Result.push_back(WideChar);
	}

	return(Result);
}
//-----------------------------------------------------------------------------
string GetTypeInfoName(const type_info& Value)
{
#ifdef _MSC_VER
	return(Value.name());
#else
	int															Status=0;
	char*														Name=abi::__cxa_demangle(Value.name(),0,0,&Status);

	if (Name!=nullptr)
	{
		try
		{
			string												TypeName(Name);

			free(Name);
			Name=nullptr;

			return(TypeName);
		}
		catch(...)
		{
			free(Name);
			Name=nullptr;

			return(Value.name());
		}
	}
	else
	{
		return(Value.name());
	}
#endif
}
//-----------------------------------------------------------------------------