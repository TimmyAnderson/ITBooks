//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include "Unit1.h"
#include "Unit2.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
namespace Test
{
//-------------------------------------------------------------------------------------------------------
	void MyFunction1(void)
	{
		wcout << L"MyFunction1() !\n";
	}
//-------------------------------------------------------------------------------------------------------
	// !!! Iba DEKLARACIA. Implementacia je MIMO NAMESPACE.
	void MyFunction2(void);
//-------------------------------------------------------------------------------------------------------
	namespace XXX
	{
//-------------------------------------------------------------------------------------------------------
		void MyFunction3(void)
		{
			wcout << L"MyFunction3() !\n";
		}
//-------------------------------------------------------------------------------------------------------
	}
//-------------------------------------------------------------------------------------------------------
	void Overloaded(int Param)
	{
		wcout << L"Overloaded(int Param) !\n";
	}
//-------------------------------------------------------------------------------------------------------
	void Overloaded(double Param)
	{
		wcout << L"Overloaded(double Param) !\n";
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
// Znova definuje TEN ISTY NAMESPACE 'Test'.
namespace Test
{
//-------------------------------------------------------------------------------------------------------
	void MyFunction4(void)
	{
		wcout << L"MyFunction4() !\n";
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
namespace Strange
{
//-------------------------------------------------------------------------------------------------------
	class CStrange
	{
	};
//-------------------------------------------------------------------------------------------------------
	void DoNothing1(void)
	{
		wcout << L"DoNothing1() !\n";
	}
//-------------------------------------------------------------------------------------------------------
	void DoNothing2(CStrange Value)
	{
		wcout << L"DoNothing2() !\n";
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------
// !!! Funkcia je IMPLEMENTOVANA MIMO NAMESPACE. Tato funkci MUSI BYT DEKLAROVANA v NAMESPACE, inak C++ hodi KOMPILACNU CHYBU.
void Test::MyFunction2(void)
{
	wcout << L"MyFunction2() !\n";
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	Test::MyFunction1();
	Test::MyFunction2();
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	// USING DECLARATION.
	// !!! V SCOPE FUNKCIE mozem cez 'using' deklarovat KONSTRUKTY, ktore NEBUDE POTREBNE zapisovat cez PLNE KVALIFIKOVANE MENA.
	using Test::MyFunction1;

	MyFunction1();

	// !!! Musim pouzit PLNE KVALIFIKOVANE MENO, kedze MyFunction2() som NEDEKLAROVAL v 'using'.
	Test::MyFunction2();

	// !!! Toto sa NESKOMPILUJE.
	//MyFunction2();
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	// USING DIRECTIVE.
	// !!! V SCOPE FUNKCIE mozem cez 'using namespace' deklarovat NAMESPACE, ktoreho VSETKY konstrukty NEBUDE POTREBNE zapisovat cez PLNE KVALIFIKOVANE MENA.
	using namespace Test;

	MyFunction1();
	MyFunction2();
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	// Funkcia BEZ NAMESPACE z Unit1.
	Unit1_NoNamespace_Function();

	wcout << L"\n";

	// Funkcia BEZ NAMESPACE z Unit2.
	Unit2_NoNamespace_Function();

	wcout << L"\n";

	/*
	// Funkcia s NONAME NAMESPACE z Unit1.
	// !!! Toto sa NEPRELOZI, lebo KAZDY UNNAMED NAMESPACE ma UNIKATNE MENO pre MODULE v ktorom je definovany.
	Unit1_UnnamedNamespace_Function();

	wcout << L"\n";

	// Funkcia s NONAME NAMESPACE z Unit2.
	// !!! Toto sa NEPRELOZI, lebo KAZDY UNNAMED NAMESPACE ma UNIKATNE MENO pre MODULE v ktorom je definovany.
	Unit2_UnnamedNamespace_Function();

	wcout << L"\n";
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	// ALIAS.
	namespace T=Test;

	T::MyFunction1();
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	// Vnorene NAMESPACES.
	Test::XXX::MyFunction3();
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	// !!! Tato syntax umoznuje pomocou USING vlozit do SCOPE VSETKY PRETAZENE VERZIE funkcie Overloaded.
	using Test::Overloaded;

	Overloaded(10);
	Overloaded(10.0);
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	Test::MyFunction1();
	Test::MyFunction2();
	Test::MyFunction4();
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	try
	{
		int				Value=0;

		if (Value==0)
		{
			throw(wstring(L"Value is ZERO !"));
		}
		else
		{
			wcout << L"Value is NON ZERO !\n";
		}
	}
	catch(wstring &Error)
	{
		wcout << L"EXCEPTION: [" << Error << L"] !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	Strange::CStrange											Object;

	// !!! Kedze som NEPOUZIL 'using' KOMPILATOR SPRAVNE urcil, ze GLOBALNA FUNKCIA DoNothing1() je NEVIDITELNA.
	//DoNothing1();

	// !!!!! Tato GLOBALNA FUNKCIA definovana v NAMESPACE je vsak PRISTUPNA i NAPRIEK TOMU, ze som NEPOUZIL ani 'using', ani PLNE KVALIFIKOVANE MENO. Stacilo, aby mala ako parameter CStrange, ktory je definovany v tom istom NAMESPACE.
	DoNothing2(Object);
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
	//Test7();
	//Test8();
	//Test9();
	Test10();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------