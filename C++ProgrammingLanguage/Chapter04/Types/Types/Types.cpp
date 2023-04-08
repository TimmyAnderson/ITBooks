//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include "EBool.h"
#include "MyTemplate.h"
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable:4800)
#pragma warning(disable:4066)
#pragma warning(disable:4700)
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
wstring				ScopeVariable=L"Global";
// Bude inicializovana na 0.
int					GlobalVariableInt;
// Bude inicializovana na 0.0.
double				GlobalVariableDouble;
//-------------------------------------------------------------------------------------------------------
void BoolTest(void)
{
	bool			Value1=true;
	bool			Value2=false;

	wcout << L"TRUE: [" << Value1 << L"] !\n";
	wcout << L"FALSE: [" << Value2 << L"] !\n";

	bool			Result1=Value1+Value2;

	wcout << L"Result1: [" << Result1 << L"] !\n";

	bool			Result2=(Value1+Value2+true);

	wcout << L"Result2: [" << Result2 << L"] !\n";

	bool			Result3=Value1+Value2+true-true;

	wcout << L"Result3: [" << Result3 << L"] !\n";

	// Vrati uz FALSE.
	bool			Result4=Value1+Value2+true-true-true;

	wcout << L"Result4: [" << Result4 << L"] !\n";

	// Vrati TRUE, lebo vysledok matematickej operacie je -1 a teda je to NON-ZERO hodnota.
	bool			Result5=Value1+Value2+true-true-true-true;

	wcout << L"Result5: [" << Result5 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void CharTest(void)
{
	wcout << L"SIZEOF - CHAR: [" << sizeof(char) << L"] !\n";
	wcout << L"SIZEOF - WCHAR_T: [" << sizeof(wchar_t) << L"] !\n";
	wcout << L"SIZEOF - 'a': [" << sizeof('a') << L"] !\n";
	wcout << L"SIZEOF - L'a': [" << sizeof(L'a') << L"] !\n";
	wcout << L"SIZEOF - L'ab': [" << sizeof(L'ab') << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void IntTest(void)
{
	wcout << L"SIZEOF - SHORT: [" << sizeof(short) << L"] !\n";
	wcout << L"SIZEOF - INT: [" << sizeof(int) << L"] !\n";
	wcout << L"SIZEOF - LONG: [" << sizeof(long int) << L"] !\n";
	wcout << L"SIZEOF - LONG LONG: [" << sizeof(long long) << L"] !\n";
	wcout << L"SIZEOF - 10: [" << sizeof(10) << L"] !\n";
	wcout << L"SIZEOF - 10L: [" << sizeof(10L) << L"] !\n";
	wcout << L"SIZEOF - 10LL: [" << sizeof(10LL) << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void DoubleTest(void)
{
	wcout << L"SIZEOF - FLOAT: [" << sizeof(float) << L"] !\n";
	wcout << L"SIZEOF - DOUBLE: [" << sizeof(double) << L"] !\n";
	wcout << L"SIZEOF - LONG DOUBLE: [" << sizeof(long double) << L"] !\n";
	wcout << L"SIZEOF - 10.0F: [" << sizeof(10.0F) << L"] !\n";
	wcout << L"SIZEOF - 10.0: [" << sizeof(10.0) << L"] !\n";
	wcout << L"SIZEOF - 10.0L: [" << sizeof(10.0L) << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void EnumTest(void)
{
	wcout << L"SIZEOF - EBool: [" << sizeof(EBool) << L"] !\n";

	EBool			Bool=E_B_FALSE;

	wcout << L"EBool: [" << Bool << L"] !\n";

	++Bool;

	wcout << L"EBool: [" << Bool << L"] !\n";

	++Bool;

	wcout << L"EBool: [" << Bool << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void NameTest(void)
{
	int			_StrangeName=100;
	int			_____=200;

	wcout << L"Variable - '_StrangeName': [" << _StrangeName << L"] !\n";
	wcout << L"Variable - '_____': [" << _____ << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void ScopeTest(void)
{
	// HIDING VARIABLE definovanek ako GLOBALNA VARIABLE.
	wstring			ScopeVariable=L"Local LEVEL 1";

	wcout << L"INSIDE FUNCTION - 'ScopeVariable': [" << ScopeVariable << L"] !\n";
	wcout << L"INSIDE FUNCTION - '::ScopeVariable': [" << ::ScopeVariable << L"] !\n";

	while(true)
	{
		// HIDING VARIABLES definovanych ako GLOBALNA VARIABLE ako VARIABLE definovana na urovni FUNKCIE.
		wstring		ScopeVariable=L"Local LEVEL 2";

		wcout << L"INSIDE BLOCK - 'ScopeVariable': [" << ScopeVariable << L"] !\n";
		wcout << L"INSIDE BLOCK - '::ScopeVariable': [" << ::ScopeVariable << L"] !\n";

		break;
	}
}
//-------------------------------------------------------------------------------------------------------
// Program musi byt skompilovany v RELEASE BUILD, lebo v DEBUG BUILD hadze ASSERT.
void InitializationTest(void)
{
	// Bude inicializovana na 0.
	static int			StaticVariableInt;
	// Bude inicializovana na 0.0.
	static double		StaticVariableDouble;

	// Bude mat NEDEFINOVANU HODNOTU.
	int					LocalVariableInt;
	// Bude mat NEDEFINOVANU HODNOTU.
	double				LocalVariableDouble;

	wcout << L"GlobalVariableInt: [" << GlobalVariableInt << L"] !\n";
	wcout << L"GlobalVariableDouble: [" << GlobalVariableDouble << L"] !\n";

	wcout << L"StaticVariableInt: [" << StaticVariableInt << L"] !\n";
	wcout << L"StaticVariableDouble: [" << StaticVariableDouble << L"] !\n";

	wcout << L"LocalVariableInt: [" << LocalVariableInt << L"] !\n";
	wcout << L"LocalVariableDouble: [" << LocalVariableDouble << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//BoolTest();
	//CharTest();
	//IntTest();
	//DoubleTest();
	//EnumTest();
	//NameTest();
	ScopeTest();
	//InitializationTest();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------