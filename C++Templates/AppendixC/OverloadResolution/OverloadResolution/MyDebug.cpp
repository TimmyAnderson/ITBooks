//----------------------------------------------------------------------------------------------------------------------
#include "MyDebug.h"
#include <iostream>
#include <locale>
#include <codecvt>
#include <tuple> 
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t)
{
	wcout << L"\n\n\nInvalid parameter detected in FUNCTION [" << Function << L"] ! FILE [" << File << L"] LINE [" << Line << L"] !" << endl;
	wcout << L"EXPRESSION: [" << Expression << L"] !\n\n\n";
}
//----------------------------------------------------------------------------------------------------------------------
void SafeMain(void)
{
#ifdef _MSC_VER
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, 0);
#endif
}
//----------------------------------------------------------------------------------------------------------------------
void ShowExitLine(void)
{
#ifdef _MSC_VER
	wcout << L"\nPress any key to EXIT !" << endl;
	std::ignore=_getch();
#endif
}
//----------------------------------------------------------------------------------------------------------------------
void PrintLineSeparator(bool UseWideChar)
{
	if (UseWideChar==true)
	{
		wcout << L"---------------------------------------------------------------------------------------------------" << endl;
	}
	else
	{
		cout << "---------------------------------------------------------------------------------------------------" << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
char ConvertWideCharToChar(wchar_t WideChar)
{
	const ctype<wchar_t>&										FacetCType=use_facet<ctype<wchar_t>>(locale::classic());

	// !!! Konvertuje WIDE CHARACTER na CHARACTER, pricom sa pouzije CHARACTER '?', ake CONVERSION ZLYHA.
	char														Char=FacetCType.narrow(WideChar,'?');

	return(Char);
}
//----------------------------------------------------------------------------------------------------------------------
wchar_t ConvertCharToWideChar(char Char)
{
	const ctype<wchar_t>&										FacetCType=use_facet<ctype<wchar_t>>(locale::classic());

	// !!! Konvertuje CHARACTER na WIDE CHARACTER.
	wchar_t														WideChar=FacetCType.widen(Char);

	return(WideChar);
}
//----------------------------------------------------------------------------------------------------------------------
string ConvertWideStringToString(const wstring& Value)
{
	string														Result;

	for(wchar_t WideChar : Value)
	{
		char													Char=ConvertWideCharToChar(WideChar);

		Result.push_back(Char);
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
wstring ConvertStringToWideString(const string& Value)
{
	wstring														Result;

	for(char Char : Value)
	{
		wchar_t													WideChar=ConvertCharToWideChar(Char);

		Result.push_back(WideChar);
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
wstring GetTypeInfoName(const type_info& Value)
{
#ifdef _MSC_VER
	string														TypeName(Value.name());
	wstring														WideTypeName=ConvertStringToWideString(TypeName);

	return(WideTypeName);
#else
	int															Status=0;
	char*														Name=abi::__cxa_demangle(Value.name(),0,0,&Status);

	if (Name!=nullptr)
	{
		try
		{
			string												TypeName(Name);
			wstring												WideTypeName=ConvertStringToWideString(TypeName);

			free(Name);
			Name=nullptr;

			return(WideTypeName);
		}
		catch(...)
		{
			free(Name);
			Name=nullptr;

			string												TypeName(Value.name());
			wstring												WideTypeName=ConvertStringToWideString(TypeName);

			return(WideTypeName);
		}
	}
	else
	{
		string													TypeName(Value.name());
		wstring													WideTypeName=ConvertStringToWideString(TypeName);

		return(WideTypeName);
	}
#endif
}
//----------------------------------------------------------------------------------------------------------------------