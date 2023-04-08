//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <cstddef>
#include "Base.h"
#include "Derived.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable:4700)
//-------------------------------------------------------------------------------------------------------
int Function1(int Param)
{
	wcout << L"Function1() CALLED !\n";

	return(Param);
}
//-------------------------------------------------------------------------------------------------------
int Function2(int Param)
{
	wcout << L"Function2() CALLED !\n";

	return(Param);
}
//-------------------------------------------------------------------------------------------------------
void MyNotEnoughMemoryHandler(void)
{
	wcout << L"!!! NOT ENOUGH MEMORY HANDLER !\n";

	// !!! Hodim CUSTOM EXCEPTION.
	throw(wstring(L"NOT ENOUGH MEMORY to ALLOCATE !!!"));
}
//-------------------------------------------------------------------------------------------------------
bool ReturnTrue()
{
	wcout << L"ReturnTrue() CALLED !\n";

	return(true);
}
//-------------------------------------------------------------------------------------------------------
bool ReturnFalse()
{
	wcout << L"ReturnFalse() CALLED !\n";

	return(false);
}
//-------------------------------------------------------------------------------------------------------
int GetSomeValue(void)
{
	return(100);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void AssociativityTest(void)
{
	int				A=10;
	int				B=6;
	int				C=13;

	// OPERATOR '+' ma ROVNAKU PRIORITU a su LEFT ASSOCIATIVE.
	int				Result1=A+B+C;
	int				Result2=A;

	Result2=Result2+B+C;

	int				Result3=A+B;

	Result3=Result3+C;

	wcout << L"Result1: [" << Result1 << L"] !\n";
	wcout << L"Result2: [" << Result2 << L"] !\n";
	wcout << L"Result3: [" << Result3 << L"] !\n";

	int				Value1=4;
	int				Value2=7;
	int				Value3=2;

	Value1=4;
	Value2=7;
	Value3=2;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";
	wcout << L"Value3: [" << Value3 << L"] !\n";

	// OPERATOR '=' je RIGHT ASSOCIATIVE.
	Value1=Value2=Value3;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";
	wcout << L"Value3: [" << Value3 << L"] !\n";

	Value1=4;
	Value2=7;
	Value3=2;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";
	wcout << L"Value3: [" << Value3 << L"] !\n";

	// OPERATOR '=' je RIGHT ASSOCIATIVE.
	Value2=Value3;

	Value1=Value2;

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";
	wcout << L"Value3: [" << Value3 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void ResultTypesTest(void)
{
	int					Value1=7;
	float				Value2=3.4f;

	// RESULT ma vzdy TYPE NAJVACSIEHO OPERANDU	v OPERACII. V tomto pripade je to FLOAT.
	double				Result=Value1+Value2;

	wcout << L"Result: [" << Result << L"] !\n";

	// Vysledok 'sizeof()' je 'size_t'.
	size_t				Size=sizeof(double);

	wcout << L"Size: [" << Size << L"] !\n";

	int					Array[10];

	// Vysledok odcitania 2 POINTERS je 'ptrdiff_t'.
	// !!! POINTER odkazujuci 1 ITEM za posledny ITEM v ARRAY je v C++ VZDY VALIDNY.
	ptrdiff_t			PointerDiff=&Array[10]-Array;

	wcout << L"PointerDiff: [" << PointerDiff << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void EvaluationOrderTest(void)
{
	// !!!!! Poradie volania funkcii Function1() a Function2() NIE JE GARANTOVANE a Function2() by MOHLA BYT VOLANA SKOR ako Function1().
	int					Result=Function1(3)+Function2(5);

	wcout << L"Result: [" << Result << L"] !\n";

	int					Array[2]={-10,-10};
	int					Counter=0;

	// !!!!! Poradie volania 'Array[Counter]' a 'Counter++' NIE JE DEFINOVANE.
	Array[Counter]=Counter++;

	wcout << L"Array[0]: [" << Array[0] << L"] !\n";
	wcout << L"Array[1]: [" << Array[1] << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void ZeroDeleteTest(void)
{
	int*				Pointer=0;

	// Prebehne BEZ PROBLEMOV.
	delete(Pointer);

	wcout << "All OK !\n";
}
//-------------------------------------------------------------------------------------------------------
void BadAllocTest(void)
{
	int						Counter=0;

	try
	{
		while(true)
		{
			double			*DummyMemory=new double[10*1000*1000];

			Counter++;
		}
	}
	catch(bad_alloc &E)
	{
		wcout << "ERROR - NOT ENOUGH MEMORY !\n";
		wcout << L"Counter: [" << Counter << L"] !\n";
		wcout << L"EXCEPTION: [" << E.what() << L"] !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void BadAllocWithHandlerTest(void)
{
	int						Counter=0;

	try
	{
		set_new_handler(MyNotEnoughMemoryHandler);

		while(true)
		{
			double			*DummyMemory=new double[10*1000*1000];

			Counter++;
		}
	}
	// V CUSTOM HANDLER hodim EXCEPTION TYPU 'wstring'.
	catch(wstring &E)
	{
		wcout << "ERROR - NOT ENOUGH MEMORY !\n";
		wcout << L"Counter: [" << Counter << L"] !\n";
		wcout << L"EXCEPTION: [" << E << L"] !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void ConstructorInitializerTest(void)
{
	int						Value1=100;
	int						Value2=int(100);
	int						Value3=0;
	// Inicializuje hodnotu na 0.
	int						Value4=int();

	wcout << L"Value1: [" << Value1 << L"] !\n";
	wcout << L"Value2: [" << Value2 << L"] !\n";
	wcout << L"Value3: [" << Value3 << L"] !\n";
	wcout << L"Value4: [" << Value4 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void CastTest1(void)
{
	// Klasicka konverzia.
	int						Value=(int) 3.5;

	wcout << L"Value: [" << Value << L"] !\n";

	int						SomeValue=100;

	const int*				ConstPointer=&SomeValue;

	// Umoznuje konverziu aj na NON-CONST HODNOTY.
	int*					NonConstPointer=(int*) ConstPointer;

	wcout << L"*NonConstPointer: [" << *NonConstPointer << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void CastTest2(void)
{
	int						SomeValue=100;

	const int*				ConstPointer=&SomeValue;

	// Konverzia 'const_cast<T>(Value)' umoznuje ODSTRANIT CONST MODIFIKATOR.
	int*					NonConstPointer=const_cast<int*>(ConstPointer);

	// !!! KOMPILATOR HODI CHYBU lebo static_cast<int*>() NEUMOZNUJE robit CAST, pri ktorom by sa odobrali MODIFIKATORY 'const' ci 'volatile'.
	//int*					NonConstPointerStaticCast=static_cast<int*>(ConstPointer);

	// !!! KOMPILATOR HODI CHYBU lebo dynamic_cast<int*>() NEUMOZNUJE robit CAST, pri ktorom by sa odobrali MODIFIKATORY 'const' ci 'volatile'.
	//int*					NonConstPointerDynamicCast=dynamic_cast<int*>(ConstPointer);

	// !!! KOMPILATOR HODI CHYBU lebo reinterpret_cast<int*>() NEUMOZNUJE robit CAST, pri ktorom by sa odobrali MODIFIKATORY 'const' ci 'volatile'.
	//int*					NonConstPointerDynamicCast=reinterpret_cast<int*>(ConstPointer);

	wcout << L"*NonConstPointer: [" << *NonConstPointer << L"] !\n";

	const CDerived			ConstObject(L"Base VALUE",L"Derived VALUE");

	// !!! Kedze Print() NIE JE CONST METODA nasledujuci riadok sa NEPREKOMPILUJE.
	//ConstObject.Print();

	// !!! Musim vykonat CASTING typu 'const_cast<TYPE>()' na ODSTRANENIE CONST MODIFIKATORA.
	// !!! Pouzil som REFERENCIE, kedze pri pouziti HODNOTY sa vola na pozadi COPY-CONSTRUCTOR a tym padom je 'const_cast<TYPE>()' NEPOTREBNY.
	CDerived&				NonConstObject=const_cast<CDerived&>(ConstObject);

	NonConstObject.Print();
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Funguje IBA pri KOMPILACII pre x86. Pri kompilacii pre x64 sposobi RUNTIME ERROR.
void CastTest3(void)
{
	CDerived				DerivedObject(L"Base VALUE",L"Derived VALUE");

	DerivedObject.Print();

	CDerived*				PointerToDerivedObject=&DerivedObject;

	// Urobim NESTANDARDNU KONVERZIU.
	// !!!!! EXTREMNE NEBEZPECNY CAST, ktory predpoklada, ze POINTER ma velkost 'sizeof(int)' co v x64 PLATFORMACH NIE JE PRAVDA, kedze tam ma POINTER az 8 BYTES.
	// !!!!! Na x64 PLATOFRME by TENTO KOD skoncil RUNTIME CHYBOU.
	int						Value=reinterpret_cast<int>(PointerToDerivedObject);

	wcout << L"Value: [" << Value<< L"] !\n";

	// Urobim SPATNU KONVERZIU.
	CDerived*				BackPointerToDerivedObject=reinterpret_cast<CDerived*>(PointerToDerivedObject);

	BackPointerToDerivedObject->Print();
}
//-------------------------------------------------------------------------------------------------------
void CastTest4(void)
{
	CDerived				DerivedObject(L"Base VALUE",L"Derived VALUE");
	CDerived*				PointerToDerivedObject=&DerivedObject;

	PointerToDerivedObject->Print();

	CBase*					PointerToBase=static_cast<CBase*>(PointerToDerivedObject);

	PointerToBase->Print();

	CDerived*				BackPointerToDerived=static_cast<CDerived*>(PointerToBase);

	BackPointerToDerived->Print();

	CBase					BaseObject(L"Base VALUE");
	CBase*					PointerToBaseObject=&BaseObject;

	PointerToBaseObject->Print();

	// !!! Spravi KONVERZIU na CDerived, aj ked v skutocnosti 'PointerToBaseObject' 'obsahuje' CBase OBJEKT.
	CDerived*				PointerToErrorDerivedObject=static_cast<CDerived*>(PointerToBaseObject);

	PointerToErrorDerivedObject->Print();

	int						IntValue=100;

	double					DoubleValue=static_cast<double>(IntValue);

	wcout << L"DoubleValue: [" << DoubleValue << L"] !\n";

	double					AnotherDoubleValue=33.33;

	// Spravim SPATNY, potencialne NEBEZPECNY CAST.
	int						IntValueCastedFromAnotherDoubleValue=static_cast<int>(AnotherDoubleValue);

	wcout << L"AnotherDoubleValue: [" << AnotherDoubleValue << L"] !\n";
	wcout << L"IntValueCastedFromAnotherDoubleValue: [" << IntValueCastedFromAnotherDoubleValue << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void CastTest5(void)
{
	CDerived				DerivedObject(L"Base VALUE",L"Derived VALUE");
	CDerived*				PointerToDerivedObject=&DerivedObject;

	PointerToDerivedObject->Print();

	CBase*					PointerToBase=dynamic_cast<CBase*>(PointerToDerivedObject);

	PointerToBase->Print();

	CDerived*				BackPointerToDerived=dynamic_cast<CDerived*>(PointerToBase);

	BackPointerToDerived->Print();

	CBase					BaseObject(L"Base VALUE");
	CBase*					PointerToBaseObject=&BaseObject;

	PointerToBaseObject->Print();

	// !!! SPRAVNE DETEKUJE, ze 'PointerToBaseObject' 'obsahuje' CBase OBJEKT a vrati NULL.
	CDerived*				PointerToErrorDerivedObject=dynamic_cast<CDerived*>(PointerToBaseObject);

	if (PointerToErrorDerivedObject!=NULL)
	{
		PointerToErrorDerivedObject->Print();
	}
	else
	{
		wcout << L"PointerToErrorDerivedObject has NULL value !\n";
	}

	/*
	int						IntValue=100;

	// !!!!! KOMPILATOR HODI CHYBU, lebo 'dynamic_cast<TYPE>(Value)' NIE JE MOZNE APLIKOVAT na PRIMITIVNE TYPY, kedze tie NEMOZU DEDIT a tento CAST je IBA NA KONVERZIU TYPOV v DEDICSKEJ HIERARCHII.
	double					DoubleValue=dynamic_cast<double>(IntValue);

	wcout << L"DoubleValue: [" << DoubleValue << L"] !\n";
	*/
}
//-------------------------------------------------------------------------------------------------------
void IfTest(void)
{
	int						Value=0;

	// !!! KOMPILATOR generuje IDENTICKY KOD s KODOM 'if (Value!=0)'.
	if (Value)
	{
		wcout << L"Value contains DIFFERENT value than 0 !\n";
	}
	else
	{
		wcout << L"Value contains 0 !\n";
	}

	// !!! KOMPILATOR generuje IDENTICKY KOD s KODOM 'if (Value)'.
	if (Value!=0)
	{
		wcout << L"Value contains DIFFERENT value than 0 !\n";
	}
	else
	{
		wcout << L"Value contains 0 !\n";
	}

	// !!! Funkcia ReturnTrue() sa NEVYKONA, kedze ReturnFalse() vratila 'false'.
	if (ReturnFalse()==true && ReturnTrue()==true)
	{
		wcout << L"IF BLOCK !\n";
	}
	else
	{
		wcout << L"ELSE BLOCK !\n";
	}

	if (int ConditionValue=GetSomeValue())
	{
		wcout << L"IF BLOCK - ConditionValue: [" << ConditionValue << L"] !\n";
	}
	else
	{
		wcout << L"ELSE BLOCK - ConditionValue: [" << ConditionValue << L"] !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
// !!! V Debug BUILD hodi ASSERT.
void GotoTest(void)
{
	for(int i=0;i<1000;i++)
	{
		for(int j=0;j<1000;j++)
		{
			for(int k=0;k<1000;k++)
			{
				if (i==10 && j==10 && k==10)
				{
					// KLASICKE pouzitie 'goto' na OPUSTENIE VNORENEHO CYKLU.
					goto OUT_OF_CYCLE;
				}
			}
		}
	}

	wcout << L"THIS CODE WILL NEVER be REACHED !\n";

	OUT_OF_CYCLE:
	wcout << L"YOU JUMPED OUT OF CYCLE !\n";

	// !!! CHYBNY SKOK, pretoze PRESKAKUJEM INICIALIZACIU PREMENNEJ.
	// !!! KOMPILATOR hodi WARNING, ktory som vsak cez #pragma ZRUSIL.
	goto INVALID_JUMP;

	int						Value=100;

	INVALID_JUMP:
	// Hodi ASSERT, lebo 'Value' NIE JE INICIALIZOVANA.
	wcout << L"Value: [" << Value << L"] !\n";

	goto INVALID_JUMP_IN_CYCLE;

	for(int Counter=0;Counter<1000;Counter++)
	{
		INVALID_JUMP_IN_CYCLE:
		wcout << L"Counter: [" << Counter << L"] !\n";

		// !!! Aby mi nespadol program spravim hned vyskocenie z cyklu.
		break;
	}

	/*
	// !!! Kompilator hodi CHYBU.
	goto INVALID_JUMP_IN_EXCEPTION;

	try
	{
		wcout << L"TRY BLOCK !\n";
	}
	catch(...)
	{
		INVALID_JUMP_IN_EXCEPTION:
		wcout << L"EXCEPTION BLOCK !\n";
	}
	*/
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//AssociativityTest();
	//ResultTypesTest();
	//EvaluationOrderTest();
	//ZeroDeleteTest();
	//BadAllocTest();
	//BadAllocWithHandlerTest();
	//ConstructorInitializerTest();
	//CastTest1();
	//CastTest2();
	//CastTest3();
	//CastTest4();
	CastTest5();
	//IfTest();
	//GotoTest();
	
	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------