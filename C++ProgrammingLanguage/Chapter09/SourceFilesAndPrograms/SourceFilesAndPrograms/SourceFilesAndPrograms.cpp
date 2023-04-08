//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <cstdio>
#include "Unit1.h"
#include "Unit2.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
const int														CONST=22;
extern const int												EXTERN_CONST;
//-------------------------------------------------------------------------------------------------------
// Deklaracii TOHO ISTEHO moze byt i VIAC.
void SomeFunc(void);
void SomeFunc(void);
void SomeFunc(void);
void SomeFunc(void);
void SomeFunc(void);
//-------------------------------------------------------------------------------------------------------
void SomeFunc(void)
{
	wcout << L"SomeFunc() !\n";
}
//-------------------------------------------------------------------------------------------------------
class CSomeClass
{
	public:
		wstring													MValue;
};
//-------------------------------------------------------------------------------------------------------
// !!! Kedze sa jedna o DEFINICIU, CLASS moze byt definovana iba RAZ.
/*
class CSomeClass
{
	public:
		wstring													MValue;
};
*/
//-------------------------------------------------------------------------------------------------------
// Deklarujem C konvenciu volania.
extern "C" void FunctionInC(wstring Param)
{
	wcout << L"FunctionInC(): [" << Param << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void Inline2(void)
{
	wcout << L"Inline2() in SourceFilesAndPrograms.cpp !\n";
}
//-------------------------------------------------------------------------------------------------------
// Trieda je definovana v 3 CPP suboroch, pricom v kazdom je definovana TROCHU ODLISNE.
class CStrangeClass
{
	public:
		wstring													TextInSourceFilesAndProgramsCPP;
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	Unit1Print();

	wcout << L"\n";

	Unit2Print();
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	// !!! INLINE MUSI BYT DEFINOVANE v LOKALNOM MODULE.
	Inline2();
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	Print1Const();
	Print2Const();

	wcout << L"Test3(): CONST - " << CONST << L" !\n";
	wcout << L"Test3(): EXTERN_CONST - " << EXTERN_CONST << L" !\n";
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	// !!! Teraz pouzivam wprintf() z kniznice 'cstdio.h'.
	std::wprintf(L"Name: [%s] !\n",L"Timmy Anderson");
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	CStrangeClass												StrangeClass;

	StrangeClass.TextInSourceFilesAndProgramsCPP=L"Timmy Anderson";

	wcout << L"Test5(): " << StrangeClass.TextInSourceFilesAndProgramsCPP << L" !\n";

	Print1CStrangeClass(StrangeClass);
	Print2CStrangeClass(StrangeClass);
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	FunctionInC(L"Timmy Anderson");
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	SomeFunc();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	Test7();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------