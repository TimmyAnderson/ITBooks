//-------------------------------------------------------------------------------------------------------
// !!!!! Visual C++ 10 GENERUJE WARINING pri pouziti EXCEPTION SPECIFICATIONS, kedze ich NEPODPORUJE.
#pragma warning(disable : 4290)
//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <memory>
#include "Base.h"
#include "Derived.h"
#include "Base1.h"
#include "Base2.h"
#include "DerivedMultiInheritance.h"
#include "ComplexClass.h"
#include "NewDeleteOperators.h"
#include "ExceptionInDestructor.h"
#include "ExceptionBase.h"
#include "ExceptionDerived.h"
#include "ExceptionSpecificationBase.h"
#include "ExceptionSpecificationDerived.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void __cdecl MyNewHandler(void)
{
	wprintf_s(L"MY NEW HANDLER CALLED - now it throws EXCEPTION !\n");

	// !!!!! NEW HANDLER ak NEVIE UVOLNIT PAMAT, tak MUSI hodit EXCEPTION bad_alloc, inak dojde k INFINITE LOOP.
	throw(bad_alloc("Not ENOUGH MEMORY !"));
}
//-------------------------------------------------------------------------------------------------------
// !!! CUSTOM UNEXPECTED HANDLER MUSI but UKONCIT cely program, alebo HODIT EXCEPTION.
void __cdecl MyUnexpectedExceptionHandler(void)
{
	wprintf_s(L"MY UNEXPECTED EXCEPTION HANDLER CALLED - now it throws EXCEPTION !\n");

	// !!!!! UNEXPECTION HANDLER MUSI hodit EXCEPTION, alebo ukoncit program.
	throw(bad_alloc("Some OTHER EXCEPTION !"));
}
//-------------------------------------------------------------------------------------------------------
void __cdecl MyUnhandledExceptionHandler(void)
{
	wprintf_s(L"MY UNHANDLED EXCEPTION HANDLER CALLED - now it will ABORT PROGRAM !\n");

	_getch();

	// !!!!! UNHANDLED EXCEPTION HANDLER MUSI UKONCIT PROGRAM.
	abort();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// Funkcia moze hodit LUBOVOLNU EXCEPTION.
void ThrowEverything1(void)
{
	throw(L"Some EXCEPTION !");
}
//-------------------------------------------------------------------------------------------------------
// Funkcia moze hodit LUBOVOLNU EXCEPTION.
void ThrowEverything2(void) throw(...)
{
	throw(L"Some EXCEPTION !");
}
//-------------------------------------------------------------------------------------------------------
// Funkcia moze hodit CExceptionBase a CExceptionDerived, lebo ta DEDI z CExceptionBase.
void ThrowCExceptionBase(int Value) throw(CExceptionBase, bad_alloc)
{
	if (Value==1)
	{
		throw(CExceptionBase());
	}
	else if (Value==2)
	{
		// !!! Akceptuje, lebo CExceptionDerived DEDI z CExceptionBase.
		throw(CExceptionDerived());
	}
	else if (Value==3)
	{
		throw(bad_alloc());
	}
	else if (Value==4)
	{
		// !!! UKOCNI PROGRAM.
		// !!!!! Bohuzial Visual C++ NEPODPORUJE EXCEPTION SPECIFICATIONS.
		throw(L"Some EXCEPTION !");
	}
}
//-------------------------------------------------------------------------------------------------------
void EmptyExceptionSpecification(void) throw()
{
	wprintf_s(L"EmptyExceptionSpecification() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
void WithExceptionSpecification(void) throw(CExceptionBase, bad_alloc)
{
	wprintf_s(L"WithExceptionSpecification() CALLED !\n");
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Kedze v EXCEPTION SPECIFICATION je pouzita SPECIALNA EXCEPTION typu 'bad_exception', tak C+ by pri vyskyte UNEXPECTED EXCEPTION mal hodit EXCEPTION typu 'bad_exception'.
// !!!!! Toto vo Visual C++ NEFUNGUJE, lebo NEPODPORUJE EXCEPTION SPECIFICATIONS.
void ThrowUnexpectedException(void) throw(bad_exception)
{
	wprintf_s(L"ThrowUnexpectedException() CALLED !\n");

	// !!! C++ HODI 'bad_exception' namiesto 'wchar_t*'.
	throw(L"Some EXCEPTION !");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	try
	{
		CDerived												Derived;

		throw(Derived);
	}
	catch(CDerived&)
	{
		wprintf_s(L"CDerived BLOCK !\n");
	}
	catch(CBase&)
	{
		wprintf_s(L"CBase BLOCK !\n");
	}
	catch(...)
	{
		wprintf_s(L"UNKNOWN EXCEPTION BLOCK !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	try
	{
		throw(L"Some ERROR !");
	}
	catch(CDerived&)
	{
		wprintf_s(L"CDerived BLOCK !\n");
	}
	catch(CBase&)
	{
		wprintf_s(L"CBase BLOCK !\n");
	}
	catch(...)
	{
		wprintf_s(L"UNKNOWN EXCEPTION BLOCK !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	try
	{
		CDerived												Derived;

		throw(Derived);
	}
	// !!!!! Kedze sa pouziva VALUE VARIABLE a NIE REFERENCE VARIABLE dochadza k pouzitiu CBase COPY CONSTRUCTOR a EXCEPTION OBJEKT je typu CBase.
	catch(CBase Value)
	{
		Value.PrintError();
	}

	wprintf_s(L"\n");

	try
	{
		CDerived												Derived;

		throw(Derived);
	}
	// !!! Kedze sa pouziva REFERENCE VARIABLE tak EXCEPTION OBJEKT je typu CDerived.
	catch(CBase& Value)
	{
		Value.PrintError();
	}
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	try
	{
		CDerivedMultiInheritance								DerivedMultiInheritance;

		throw(DerivedMultiInheritance);
	}
	catch(CBase1&)
	{
		wprintf_s(L"CBase1 BLOCK !\n");
	}
	catch(CBase2&)
	{
		wprintf_s(L"CBase2 BLOCK !\n");
	}

	wprintf_s(L"\n");

	try
	{
		CDerivedMultiInheritance								DerivedMultiInheritance;

		throw(DerivedMultiInheritance);
	}
	catch(CBase2&)
	{
		wprintf_s(L"CBase2 BLOCK !\n");
	}
	catch(CBase1&)
	{
		wprintf_s(L"CBase1 BLOCK !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	try
	{
		wstring													Error(L"Some ERROR !");

		throw(Error);
	}
	catch(wstring&)
	{
		wprintf_s(L"BLOCK [wstring&] !\n");
	}

	wprintf_s(L"\n");

	try
	{
		wstring													Error(L"Some ERROR !");

		throw(Error);
	}
	// !!! Medzi [catch(wstring&)] a [catch(wstring&)] NIE JE ZIADEN ROZDIEL.
	catch(const wstring&)
	{
		wprintf_s(L"BLOCK [const wstring&] !\n");
	}
	/*
	// !!! HODI kompilacnu CHYBU.
	catch(wstring&)
	{
		wprintf_s(L"BLOCK [wstring&] !\n");
	}
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	try
	{
		int														Error=100;

		wprintf_s(L"TRY [%p] !\n",&Error);

		throw(Error);
	}
	catch(int& Value)
	{
		// !!! Adresa je ODLISNA, lebo objekt hodeny v THROW sa VZDY KOPIRUJE.
		wprintf_s(L"CATCH [%p] !\n",&Value);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	try
	{
		int														Error=100;
		int*													Pointer=&Error;

		throw(Pointer);
	}
	catch(int*)
	{
		wprintf_s(L"CATCH BLOCK !\n");
	}

	try
	{
		int														Error=100;
		int&													Pointer=Error;

		throw(Pointer);
	}
	catch(int&)
	{
		wprintf_s(L"CATCH BLOCK !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	try
	{
		try
		{
			CDerived												Derived;

			throw(Derived);
		}
		// !!!!! Kedze sa pouziva VALUE VARIABLE a NIE REFERENCE VARIABLE dochadza k pouzitiu CBase COPY CONSTRUCTOR a EXCEPTION OBJEKT je typu CBase.
		catch(CBase Value)
		{
			Value.PrintError();

			// !!!!! RE-THROWN hodi CDerived EXCEPTION a NIE CBase, ktora sa zachytila v tomto CATCH bloku.
			throw;
		}
	}
	// !!! Kedze sa pouziva REFERENCE VARIABLE tak EXCEPTION OBJEKT je typu CDerived.
	catch(CBase& Value)
	{
		Value.PrintError();
	}
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	try
	{
		// !!! EXCEPTION sa hodi v CComplexClass AZ po vytvoreni FIELDS MClassA a MClassB a preto sa pre nich BUDU volat DESTRUCTORS, ale NIE pre CComplexClass.
		CComplexClass											Object(false,false,true);

		Object.DoNothing();
	}
	catch(wchar_t* Exception)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",Exception);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	try
	{
		// !!! EXCEPTION sa hodi pri vytvarani MClassB, teda AZ po vytvoreni FIELD MClassA a preto sa pre nich BUDE volat DESTRUCTOR pre MClassA, ale NIE pre MClassB a CComplexClass.
		CComplexClass											Object(false,true,false);

		Object.DoNothing();
	}
	catch(wchar_t* Exception)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",Exception);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	try
	{
		// !!! EXCEPTION sa hodi uz pri vytvarani MClassA, a teda NEVOLA sa ANI JEDEN DESTRUCTOR.
		CComplexClass											Object(true,false,false);

		Object.DoNothing();
	}
	catch(wchar_t* Exception)
	{
		wprintf_s(L"EXCEPTION [%s] !\n",Exception);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	{
		auto_ptr<CDerived>										Ptr(new CDerived);

		Ptr->PrintError();

		// !!! Automaticky sa vola DELETE.
	}

	wprintf_s(L"END !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	{
		unique_ptr<CDerived>									Ptr(new CDerived);

		Ptr->PrintError();

		// Automaticky sa vola DELETE.
	}

	wprintf_s(L"END !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	CClassA*													Pointer=NULL;

	try
	{
		// CONSTRUCTOR hodi EXCEPTION.
		Pointer=new CClassA(true);

		wprintf_s(L"POINTER [%p] !\n",Pointer);
	}
	catch(...)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"POINTER [%p] !\n",Pointer);
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	CNewDeleteOperators*										Pointer=NULL;

	try
	{
		// CONSTRUCTOR hodi EXCEPTION.
		Pointer=new CNewDeleteOperators();

		wprintf_s(L"POINTER [%p] !\n",Pointer);
	}
	catch(...)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"POINTER [%p] !\n",Pointer);
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	char*														Buffer=new char[10000];

	memset(Buffer,0,sizeof(Buffer));

	CClassA*													Pointer=NULL;

	try
	{
		// !!!!! SPEFICKA SYNTAX (PLACEMENT EXPRESSION) pre OPERATOR NEW, ktora ALOKUJE pamat v Buffer.
		Pointer=new (Buffer) CClassA(L"PLACEMENT SYNTAX for OPERATOR NEW");

		wprintf_s(L"POINTER [%p] !\n",Pointer);

		// !!! Explicitne volanie DESTRUCTOR, ktore je NEVYHNUTNE pri pouziti PLACEMENT EXPRESSION.
		Pointer->~CClassA();
	}
	catch(...)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"POINTER [%p] !\n",Pointer);

	// !!! Kedze pri PLACEMENT SYNTAX sa pamat EXPLICITNE NEDEALOKUJE musim to spravit RUCNE a to AJ PO VZNIKU EXCEPTION.
	delete[](Buffer);
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	set_new_handler(MyNewHandler);

	try
	{
		while (true) 
		{
			// Alokujem velku cast pamate.
			new int[5000000];

			wprintf_s(L"Allocating 5000000 ints !\n");
		}

	}
	catch(bad_alloc& E)
	{
		// !!! MUSI byt printf_s(), lebo bad_alloc.what() je typu CONST CHAR*.
		printf_s("EXCEPTION CAUGHT !\n",E.what());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	try
	{
		// !!!!! Tento CONSTRUCTOR zachytava EXCEPTIONS hodene v INITIALIZERS, avsak C++ AUTOMATICKY spravi RE-THROWN.
		CComplexClass											Object(true,true,true,true);

		Object.DoNothing();
	}
	catch(wchar_t* Exception)
	{
		// !!! Tu ZNOVA ZACHYTIM EXCEPTION, ktora bola AUTOMATICKY RE-THROWN.
		wprintf_s(L"EXCEPTION [%s] !\n",Exception);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	try
	{
		CExceptionInDestructor									Object;

		Object.DoNothing();

		// !!! DESTRUCTOR hodi EXCEPTION.
	}
	catch(wchar_t* Exception)
	{
		// !!! EXCEPTION v DESTRUCTOR sa NORMALNE SPRACUJE.
		wprintf_s(L"EXCEPTION [%s] !\n",Exception);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	try
	{
		try
		{
			CExceptionInDestructor									Object;

			Object.DoNothing();

			// !!! GENERUJEM EXCEPTION.
			throw(L"EXCEPTION THROWN in TEST METHOD !");

			// !!!!! DESTRUCTOR hodi DALSIU EXCEPTION pocas STACK UNWIND.
		}
		catch(wchar_t* Exception)
		{
			// !!!!! EXCEPTION v DESTRUCTOR pri STACK UNWIND vedie k TERMINATE programu. Kod sa tu NEDOSTANE.
			wprintf_s(L"EXCEPTION [%s] !\n",Exception);
		}
	}
	catch(wchar_t* Exception)
	{
		// !!!!! EXCEPTION v DESTRUCTOR pri STACK UNWIND vedie k TERMINATE programu. Kod sa tu NEDOSTANE.
		wprintf_s(L"EXCEPTION [%s] !\n",Exception);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	try
	{
		ThrowEverything1();
	}
	catch(wchar_t*)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		ThrowEverything2();
	}
	catch(wchar_t*)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		ThrowCExceptionBase(1);
	}
	catch(CExceptionBase&)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		ThrowCExceptionBase(2);
	}
	catch(CExceptionDerived&)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		ThrowCExceptionBase(3);
	}
	catch(bad_alloc&)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		// !!! Hodi UNEXPECTED EXCEPTION a program SPADNE.
		// !!!!! Bohuzial Visual C++ NEPODPORUJE EXCEPTION SPECIFICATIONS.
		ThrowCExceptionBase(4);
	}
	catch(...)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test22(void)
{
	// DEKLARACIA POINTER na FUNCTION, ktory obsahuje EXCEPTION SPECIFICATION.
	void														(*EmptyNoSpecification)(void) throw();

	EmptyNoSpecification=EmptyExceptionSpecification;

	EmptyNoSpecification();

	/*
	// !!! HODI INTELI-SENSE CHYBU, lebo NESEDIA EXCEPTION SPECIFICATIONS. KOMPILATOR to vsak AKCEPTUJE.
	EmptyNoSpecification=WithExceptionSpecification;

	EmptyNoSpecification();
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test23(void)
{
	try
	{
		CExceptionSpecificationBase								Object;

		Object.ThrowCExceptionBase();
	}
	catch(CExceptionBase&)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		CExceptionSpecificationBase								Object;

		Object.ThrowCExceptionDerived();
	}
	catch(CExceptionDerived&)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		CExceptionSpecificationDerived							Object;

		Object.ThrowCExceptionBase();
	}
	catch(CExceptionBase&)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}

	wprintf_s(L"\n");

	try
	{
		CExceptionSpecificationDerived							Object;

		Object.ThrowCExceptionDerived();
	}
	catch(CExceptionDerived&)
	{
		wprintf_s(L"EXCEPTION CAUGHT !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test24(void)
{
	try
	{
		// !!! Funkcia by mala hodit bad_exception, ale kvoli tomu, ze C++ NEPODPORUJE EXCEPTION SPECIFICATIONS, tak je hodena EXCEPTION typu 'wchar_t*'.
		ThrowUnexpectedException();
	}
	catch(wchar_t*)
	{
		wprintf_s(L"EXCEPTION [wchar_t*] CAUGHT !\n");
	}
	catch(bad_exception)
	{
		wprintf_s(L"EXCEPTION [bad_exception] CAUGHT !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test25(void)
{
	// !!! Nastavi UNEXPECTED HANDLER.
	// !!! Vo Visual C++ to NEFUNGUJE, lebo Visual C++ NEPODPORUJE EXCEPTION SPECIFICATIONS.
	set_unexpected(MyUnexpectedExceptionHandler);

	try
	{
		// !!! Funkcia by mala hodit bad_exception, ale kvoli tomu, ze C++ NEPODPORUJE EXCEPTION SPECIFICATIONS, tak je hodena EXCEPTION typu 'wchar_t*'.
		ThrowUnexpectedException();
	}
	catch(wchar_t*)
	{
		wprintf_s(L"EXCEPTION [wchar_t*] CAUGHT !\n");
	}
	catch(bad_exception)
	{
		wprintf_s(L"EXCEPTION [bad_exception] CAUGHT !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test26(void)
{
	// !!!!! Funguje IBA MIMO DEBUGGER.

	set_terminate(MyUnhandledExceptionHandler);

	// !!! Umyselne NEZACHYTIM EXCEPTION.
	ThrowEverything1();
}
//-------------------------------------------------------------------------------------------------------
void Test27(void)
{
	CBase1														Value;
	CBase1&														Pointer=Value;

	try
	{
		// !!! Hodi EXCEPTION typu 'bad_cast'.
		dynamic_cast<CDerivedMultiInheritance&>(Pointer);
	}
	catch(bad_cast& E)
	{
		const char*												What=E.what();
		
		printf_s("EXCEPTION - What: [%s] !\n",What);
	}
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
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	//Test17();
	//Test18();
	//Test19();
	//Test20();
	//Test21();
	//Test22();
	//Test23();
	//Test24();
	//Test25();
	//Test26();
	Test27();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------