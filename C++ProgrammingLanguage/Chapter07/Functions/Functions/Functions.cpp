//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <cstdarg>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
#define MY_MACRO_1(Param1,Param2) L"[Param1: " << Param1 << L", Param2: " << Param2 << L"]"
// Demonstruje pouzitie operatora '##'.
#define MY_MACRO_2(Param1,Param2) L"[Param1: " << Param1 << L", Param2: " << Param2 << L", Param1##Param2: " << Param1##Param2 << L", Param1## << \"-\" << ##Param2: " << Param1## << L"-" << ##Param2 << L"]"
#define MY_MACRO_3(Param1,Param2) L"[Param1: " << Param1 << L", Param2: " << Param2 << L"]"
// !!! Zrusim deklaraciu MY_MACRO_3.
#undef MY_MACRO_3
//-------------------------------------------------------------------------------------------------------
typedef void (*POINTER_TO_FUNCTION)(wstring, wstring, int);
//-------------------------------------------------------------------------------------------------------
// Obsahuje DEFAULT PARAMETER.
void DefaultParameter1(int =99);
//-------------------------------------------------------------------------------------------------------
inline void SimpleInline(void)
{
	// INLINE moze mat i STATIC VARIABLES.
	static int					Value=0;

	Value++;

	wcout << L"Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void ConstReference(const float& Value)
{
	wcout << L"ConstReference() - Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void NonConstReference(float& Value)
{
	wcout << L"NonConstReference() - Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void VoidFunction(int Value)
{
	wcout << L"VoidFunction() - Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void PrintValue(int Value)
{
	wcout << L"PrintValue(INT) - Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void PrintValue(double Value)
{
	wcout << L"PrintValue(DOUBLE) - Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void OverloadingTest1(void)
{
	PrintValue(10);
}
//-------------------------------------------------------------------------------------------------------
void OverloadingTest2(void)
{
	// !!!!! V tele funkcie PREDPISEM, ktora OVELOADED VERZIA FUNCTION sa ma volat.
	void PrintValue(double Value);

	PrintValue(10);
}
//-------------------------------------------------------------------------------------------------------
// !!! DEFAULT HODNOTA parametra 'Value' je deklarovana v DEKLARACII danej FUNCTION.
void DefaultParameter1(int Value)
{
	wcout << L"DefaultParameter1() - Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void DefaultParameter2(int Value=50)
{
	wcout << L"DefaultParameter2() - Value: [" << Value << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void VariableParameters(int Parameter1, int Parameter2...)
{
	wcout << L"VariableParameters() - Parameter1: [" << Parameter1 << L"] !\n";
	wcout << L"VariableParameters() - Parameter2: [" << Parameter2 << L"] !\n";

	// Deklarujem premennu sluziaciu pocas enumeracie PARAMETROV.
	va_list														VA;

	// !!! Druhy AGRUMNET MUSI byt POSLEDNY POMENOVANY PARAMETER.
	va_start(VA,Parameter2);

	while(true)
	{
		// !!! Ziskam PARAMETER. Druhy AGRUMNET musi obsahovat TYP na ktoreho je vyberany PARAMETER.
		wstring													Name=va_arg(VA,wstring);

		// Prazdny retazec pouzijem ako TERMINATOR - indikaciu konca zoznamu PARAMETROV.
		if (Name==L"")
		{
			break;
		}

		wcout << L"Name: [" << Name << L"] !\n";
	}

	// !!!!! Je EXTREMNE DOLEZITE volat toto makro, aby NEDOSLO k NARUSENIU STACK.
	va_end(VA);
}
//-------------------------------------------------------------------------------------------------------
void FunctionWith3Parameters(wstring FirstName, wstring LastName, int Age)
{
	wcout << L"FunctionWith3Parameters() - [FirstName: " << FirstName << L", LastName: " << LastName << L", Age: " << Age << "] !\n";
}
//-------------------------------------------------------------------------------------------------------
int FunctionWith3ParametersAndReturnValue(wstring FirstName, wstring LastName, int Age)
{
	wcout << L"FunctionWith3Parameters() - [FirstName: " << FirstName << L", LastName: " << LastName << L", Age: " << Age << "] !\n";

	return(10);
}
//-------------------------------------------------------------------------------------------------------
void FunctionWith3ParametersOverloaded(wstring FirstName, wstring LastName, int Age)
{
	wcout << L"FunctionWith3Parameters() - [FirstName: " << FirstName << L", LastName: " << LastName << L", Age: " << Age << "] !\n";
}
//-------------------------------------------------------------------------------------------------------
void FunctionWith3ParametersOverloaded(wstring FirstName, wstring LastName, double Age)
{
	wcout << L"FunctionWith3Parameters() - [FirstName: " << FirstName << L", LastName: " << LastName << L", Age: " << Age << "] !\n";
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void InlineTest(void)
{
	SimpleInline();
	SimpleInline();
	SimpleInline();
}
//-------------------------------------------------------------------------------------------------------
void ConstReferenceTest(void)
{
	// !!! Pri volani sa vytvori TEMP PREMENNA, no prenos CONST REFERENCE C++ UMOZNI.
	ConstReference(5.5f);

	// !!! Pri volani sa vytvori TEMP PREMENNA a prenos NON-CONST REFERENCE C++ NEUMOZNI.
	// !!!!! KOMPILATOR hodi CHYBU.
	//NonConstReference(5.5f);
}
//-------------------------------------------------------------------------------------------------------
void VoidFunctionTest(void)
{
	// !!!!! MOZEM POUZIT RETURN, ak volam funkciu, ktora vracia 'VOID'.
	return(VoidFunction(10));
}
//-------------------------------------------------------------------------------------------------------
void OverloadingTest(void)
{
	OverloadingTest1();
	OverloadingTest2();
}
//-------------------------------------------------------------------------------------------------------
void DefaultParameterTest(void)
{
	DefaultParameter1();

	// Vo FUNCTION ZMENIM HODNOTU DEFAULT PARAMETRA.
	void DefaultParameter2(int Value=13);

	DefaultParameter2();
}
//-------------------------------------------------------------------------------------------------------
void VariableParametersTest(void)
{
	wstring				Name1=L"Timmy";
	wstring				Name2=L"Atreyu";
	wstring				Name3=L"Jenny";
	wstring				TERMINATOR=L"";

	VariableParameters(10,20,Name1,Name2,Name3,TERMINATOR);
}
//-------------------------------------------------------------------------------------------------------
void PointerToFunctionTest(void)
{
	void				(*Pointer1)(wstring, wstring, int)=&FunctionWith3Parameters;

	// !!! Pouzitie operatora '&' je NEPOVINNE.
	void				(*Pointer2)(wstring, wstring, int)=FunctionWith3Parameters;

	(*Pointer1)(L"Timmy",L"Anderson",12);

	// !!! Pouzitie operatora '*' je NEPOVINNE.
	Pointer2(L"Timmy",L"Anderson",12);

	// !!! KOMPILATOR hodi CHYBU, lebo RETURN VALUE je ROZDIELNA.
	//void				(*Pointer3)(wstring, wstring, int)=&FunctionWith3ParametersAndReturnValue;

	POINTER_TO_FUNCTION	Pointer4=&FunctionWith3Parameters;

	(*Pointer4)(L"Timmy",L"Anderson",12);

	void				(*Pointer5)(wstring, wstring, int)=&FunctionWith3ParametersOverloaded;
	void				(*Pointer6)(wstring, wstring, double)=&FunctionWith3ParametersOverloaded;

	(*Pointer5)(L"Timmy",L"Anderson",12);
	(*Pointer6)(L"Timmy",L"Anderson",12.0);
}
//-------------------------------------------------------------------------------------------------------
void MacroTest(void)
{
	wcout << L"Text from MY_MACRO_1 - " << MY_MACRO_1(L"Timmy",L"Anderson") << L" !\n";

	wcout << L"Text from MY_MACRO_2 - " << MY_MACRO_2(L"Timmy",L"Anderson") << L" !\n";

	// !!! Pouzil som #undef.
	//wcout << L"Text from MY_MACRO_3 - " << MY_MACRO_3(L"Timmy",L"Anderson") << L" !\n";
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//InlineTest();
	//ConstReferenceTest();
	//VoidFunctionTest();
	//OverloadingTest();
	//DefaultParameterTest();
	//VariableParametersTest();
	//PointerToFunctionTest();
	MacroTest();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------