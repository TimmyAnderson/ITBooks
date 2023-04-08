//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <algorithm>
#include <list>
#include "Int.h"
#include "Name.h"
#include "EEnum.h"
#include "Namespace.h"
#include "IntConversions.h"
#include "NamePrivate.h"
#include "NameOperations.h"
#include "IntImplicit.h"
#include "IntExplicit.h"
#include "IntArray.h"
#include "IntAdditionFunction.h"
#include "PrimitiveTypeDereferencing.h"
#include "PointerToClassDereferencing.h"
#include "ClassDereferencing.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
int																MAdd=3;
//-------------------------------------------------------------------------------------------------------
CInt Process(CInt Param)
{
	wprintf(L"Process() CALLED !\n");

	return(Param);
}
//-------------------------------------------------------------------------------------------------------
CIntImplicit Process(CIntImplicit Param)
{
	wprintf(L"Process() CALLED !\n");

	return(Param);
}
//-------------------------------------------------------------------------------------------------------
/*
CIntExplicit Process(CIntExplicit Param)
{
	wprintf(L"Process() CALLED !\n");

	// !!! Kod NIE JE KOMPILOVATELNY, pretoze potrebuje IMPLICTNY COPY CONSTURCTOR.
	return(Param);
}
*/
//-------------------------------------------------------------------------------------------------------
// !!! Kedze COPY CONSTRUCTOR je EXPLICIT, MUSIM pouzit REFERENCES, alebo POINTERS.
CIntExplicit& Process(CIntExplicit& Param)
{
	// !!!!! RETURN VALUE NEBUDE PRENOSITELNA, lebo CALLER potrebuje COPY CONSTRUCTOR.
	return(Param);
}
//-------------------------------------------------------------------------------------------------------
// !!! Tato funkcia sluzi na DEMONSTRACIU preco je pouzitie FUNKCIE v algoritme for_each() MENEJ efektivne, ako pouzitie FUNCTION CLASS.
// !!!!! Problem tejto funkcie je, ze hodnotu o kolko ZVACSIT Param musi byt GLOBALNA PREMENNA. Nie je mozne do funkcie PARAMETROM zaslat hodnotu o KOLKO ma ZVACSIT Param, kedze for_each() ocakava funkci s 1 PARAMETROM.
void GlobalFunctionAdd(CInt& Param)
{
	// VARIABLE 'MAdd' je GLOBALNA PREMENNA.
	int															NewValue=Param.GetValue()+MAdd;

	Param.SetValue(NewValue);

	wprintf_s(L"GLOBAL FUNCTION Add() for [%d] CALLED !\n",Param.GetValue());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CInt														Value1(12);
	CInt														Value2(4);

	// Pouzijem OVERLOADED OPERATOR.
	CInt														Result=Value1+Value2;

	Result.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	CInt														Value1(12);
	CInt														Value2(4);

	// !!! Pouzijem OVERLOADED OPERATOR so FUNCTION CALL SYNTAXOU.
	CInt														Result=Value1.operator+(Value2);

	Result.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	CName														Name1(L"Timmy",L"Anderson",12);
	CName														Name2(L"Jenny",L"Thompson",13);
	CName*														PName1=new CName(L"Timmy",L"Anderson",12);
	CName*														PName2=new CName(L"Jenny",L"Thompson",13);

	// Definujem MEMBER REFERENCE premenne.
	wstring														CName::*FirstName;
	wstring														CName::*LastName;
	int															CName::*Age;
	// Funkcia.
	wstring														(CName::*Print)();

	// Inicializujem MEMBER REFERENCE premenne na jednotlive MEMBERS.
	FirstName=&CName::MFirstName;
	LastName=&CName::MLastName;
	Age=&CName::MAge;
	Print=&CName::GetFullName;

	// Volam MEMBER REFERENCE premenne pre rozlicne ROZLICNE objekty.
	wprintf_s(L"Name1.*FirstName: [%s] !\n",(Name1.*FirstName).c_str());
	wprintf_s(L"Name1.*LastName: [%s] !\n",(Name1.*LastName).c_str());
	wprintf_s(L"Name1.*Age: [%d] !\n",(Name1.*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(Name1.*Print)(): [%s] !\n",((Name1.*Print)().c_str()));

	wprintf_s(L"\n");

	// Volam MEMBER REFERENCE premenne pre rozlicne ROZLICNE objekty.
	wprintf_s(L"Name2.*FirstName: [%s] !\n",(Name2.*FirstName).c_str());
	wprintf_s(L"Name2.*LastName: [%s] !\n",(Name2.*LastName).c_str());
	wprintf_s(L"Name2.*Age: [%d] !\n",(Name2.*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(Name2.*Print)(): [%s] !\n",((Name2.*Print)().c_str()));
	
	wprintf_s(L"\n");

	// Volam MEMBER REFERENCE premenne CEZ POINTER pre rozlicne ROZLICNE objekty.
	wprintf_s(L"PName1->*FirstName: [%s] !\n",(PName1->*FirstName).c_str());
	wprintf_s(L"PName1->*LastName: [%s] !\n",(PName1->*LastName).c_str());
	wprintf_s(L"PName1->*Age: [%d] !\n",(PName1->*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(PName1->*Print)(): [%s] !\n",((PName1->*Print)().c_str()));

	wprintf_s(L"\n");

	// Volam MEMBER REFERENCE premenne CEZ POINTER pre rozlicne ROZLICNE objekty.
	wprintf_s(L"PName2->*FirstName: [%s] !\n",(PName2->*FirstName).c_str());
	wprintf_s(L"PName2->*LastName: [%s] !\n",(PName2->*LastName).c_str());
	wprintf_s(L"PName2->*Age: [%d] !\n",(PName2->*Age));
	// Vola sa FUNKCIA.
	wprintf_s(L"(PName2->*Print)(): [%s] !\n",((PName2->*Print)().c_str()));

	delete(PName1);
	delete(PName2);
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	CInt														Value1(12);
	CInt														Value2(4);

	// !!! KOMPILATOR hodi CHYBU, pretoze nevie, ci ma volat MEMBER OPERATOR, alebo GLOBALNY OPERATOR.
	//CInt														Result=Value1-Value2;

	// !!! Vola sa MEMBER OPERATOR.
	CInt														Result1=Value1.operator-(Value2);

	Result1.Print();

	// !!! Vola sa GLOBALNY OPERATOR.
	CInt														Result2=::operator-(Value1,Value2);

	Result2.Print();

	// !!! Vola sa GLOBALNY OPERATOR. Tu NIE JE KONFLIKT, lebo existuje IBA GLOBALNY OPERATOR s INT ako RIGHT OPERAND.
	CInt														Result3=Value1-10;

	Result3.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	CInt														Value1(12);
	CInt														Value2(4);

	Value1.Print();
	Value2.Print();
	
	Value1=Value2;

	Value1.Print();
	Value2.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	CInt														Value(12);
	CInt														Result=4*Value;

	Result.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	CInt														Value1(12);

	Value1.Print();

	// Vola sa PREFIX MEMBER OPERATOR.
	++Value1;

	Value1.Print();

	// Vola sa POSTFIX MEMBER OPERATOR.
	Value1++;

	Value1.Print();

	CInt														Value2(12);

	Value2.Print();

	// Vola sa PREFIX GLOBAL OPERATOR.
	--Value2;

	Value2.Print();

	// Vola sa POSTFIX GLOBAL OPERATOR.
	Value2--;

	Value2.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	EEnum														Value=E_ONE;

	wprintf_s(L"Value: [%d] !\n",Value);

	Value++;

	wprintf_s(L"Value: [%d] !\n",Value);

	Value++;

	wprintf_s(L"Value: [%d] !\n",Value);
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	MyNamespace::CNamespace										Namespace1(10);
	MyNamespace::CNamespace										Namespace2(3);

	Namespace1.Print();
	Namespace2.Print();

	MyNamespace::CNamespace										Result1=Namespace1+Namespace2;

	Result1.Print();

	// !!! Aj napriek tomu, ze GLOBALNY OPERATOR je definovany v NAMESPACE a CPP NEBOL pouzity 'using', tak ho C++ NAJDE.
	MyNamespace::CNamespace										Result2=Namespace1-Namespace2;

	Result2.Print();

	// !!!!! Dokonca aj GLOBALNE FUNKCIE, pokial maju parameter typu CLASS definovany v NAMESPACE, tak su VIDITELNE aj BEZ PLNE KVALIFIKOVANEHO MENA.
	PrintGlobalFunction(Result2);

	// !!!!! Teraz vsak uz kompilator hodi CHYBU, pretoze metoda NEMA PARAMETER typu CLASS definovany v NAMESPACE.
	//PrintGlobalFunctionEmpty(10);

	// !!! Tu je NUTNE pouzit PLNE KVALIFIKOVANE MENO.
	MyNamespace::PrintGlobalFunctionEmpty(10);
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	CIntConversions												Value1=5;
	CIntConversions												Value2=6;

	Value1.Print(L"Value1");
	Value2.Print(L"Value2");

	// !!! Value1 aj Value2 konvertuje na INT a potom INT na CIntConversions.
	CIntConversions												Value3=Value2-Value1;

	Value3.Print(L"Value3");

	// !!! Value1 aj Value2 konvertuje na INT.
	int															Value4=Value1+Value2;

	wprintf_s(L"Value4: [%d] !\n",Value4);

	// !!! Hodnota Value1 sa konvertuje na INT a po scitani dvoch INT sa vysledok konvertuje na CIntConversions.
	CIntConversions												Value5=Value1+12;

	Value5.Print(L"Value5");

	// Obe hodnoty sa konvertuju na INT a vysledok scitania na sa konvertuje na CIntConversions.
	CIntConversions												Value6=Value1+CIntConversions(12);

	Value6.Print(L"Value6");
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	CNamePrivate												Name(L"Timmy",L"Anderson",12);
	CNameOperations												NameOperations;

	Name.PrintFullName();
	
	// !!! Pomocou FRIEND metody modifikujem Name.
	NameOperations.MofifyName(Name,L"TIMMY",L"ANDERSON",13);

	Name.PrintFullName();

	// !!! Pomocou GLOBALNEJ funkcie modifikujem Name.
	ClearName(Name);

	Name.PrintFullName();
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	CInt														Value(13);

	// !!! Do aj z funkcie sa prenasa CInt HODNOTOU, a preto sa prenho vola COPY CONSTRUCTOR 2 krat (pri prenose PARAMETRA i RETURN VALUE).
	CInt														Result=Process(Value);

	Result.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	// !!! Kedze VSETKY konstruktory su IMPLICITNE tento kod je KOMPILOVATELNY.
	CIntImplicit												IntImplicitParam(10);
	CIntImplicit												IntImplicitReturnValue=Process(IntImplicitParam);

	IntImplicitReturnValue.Print();

	wprintf_s(L"\n");

	// Kod je kompilovatelny, lebo CONSTRUCTOR s parametrom INT je IMPLICITNY.
	CIntImplicit												IntImplicitValue(15);

	IntImplicitValue.Print();

	wprintf_s(L"\n");

	CIntExplicit												IntExplicitParam(20);

	// !!! Kod NIE JE KOMPILOVATELNY, pretoze COPY CONSTRUCTOR je EXPLICIT.
	//CIntExplicit												IntExplicitReturnValue=Process(IntExplicitParam);

	// !!!!! Kod JE KOMPILOVATELNY, ale MUSEL som pouzit REFERENCE ako RETURN VALUE.
	CIntExplicit&												IntExplicitReturnValue=Process(IntExplicitParam);

	IntExplicitReturnValue.Print();

	wprintf_s(L"\n");

	// !!! Kod NIE JE KOMPILOVATELNY, lebo CONSTRUCTOR s parametrom INT je EXPLICIT.
	//CIntExplicit												IntExplicitValue=25;

	// !!! Musim pouzit EXPLICITNE VOLANIE CONSTRUCTOR.
	CIntExplicit												IntExplicitValue(25);

	IntExplicitValue.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	CIntArray													Array(10);

	for(int i=0;i<Array.GetSize();i++)
	{
		Array.SetValue(i,i*2);
	}

	for(int i=0;i<Array.GetSize();i++)
	{
		// !!! Pristupujem cez OVERRIDED OPERATOR.
		wprintf_s(L"Array[%d]: [%d] !\n",i,Array[i]);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	list<CInt>													Ints;

	Ints.push_back(CInt(1));
	Ints.push_back(CInt(2));
	Ints.push_back(CInt(3));

	// !!! Demonstrujem, ze for_each() dokaze pouzit KLASICKE FUNKCIE, kedze tie IMPLICITNE podporuju OPERATOR().
	for_each(Ints.begin(),Ints.end(),GlobalFunctionAdd);

	// !!!!! Definujem objekt pre FUNCTION CLASS. Tento CLASS umoznuje definovat CONTEXT PARAMETRE, ktore sa v GlobalFunctionAdd() museli definovat v GLOBALNEJ PREMENNEJ.
	CIntAdditionFunction										IAF(true,6);

	// !!!!! ALGORITHM for_each() vola OVERRIDED OPERATOR().
	for_each(Ints.begin(),Ints.end(),IAF);
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	int															Value=11;
	CPrimitiveTypeDereferencing									PrimitiveTypeDereferencing(&Value);

	int*														Pointer=PrimitiveTypeDereferencing.operator->();

	// !!! Takato syntax NEFUNGUJE, pretoze na RETURN VALUE OPERATOR->() sa C++ snazi ZNOVA APLIKOVAT OPERATOR->().
	//int*														Pointer=PrimitiveTypeDereferencing->;

	wprintf_s(L"Value: [%d] !\n",*Pointer);

	wprintf_s(L"\n");

	CInt														IntClass(22);
	CPointerToClassDereferencing								PointerToClassDereferencing(&IntClass);

	// !!! Kedze OPERATOR->() vracia POINTER na CInt, tak MOZEM pouzit KLASICKU SYNTAX.
	wprintf_s(L"PointerToClassDereferencing->GetValue(): [%d] !\n",PointerToClassDereferencing->GetValue());

	wprintf_s(L"\n");

	CInt														AnotherIntClass(33);
	CPointerToClassDereferencing								AnotherPointerToClassDereferencing(&AnotherIntClass);
	CClassDereferencing											ClassDereferencing(AnotherPointerToClassDereferencing);

	// !!!!! Kedze OPERATOR->() vracia OBJEKT typu ClassDereferencing a ten MA PRETAZENY OPERATOR->(), tak mozem pouzit KLASICKU SYNTAX.
	// !!!!! Toto volanie vola 2 PRETAZENE OPERATOR->().
	wprintf_s(L"PointerToClassDereferencing->GetValue(): [%d] !\n",ClassDereferencing->GetValue());

	wprintf_s(L"\n");
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
	Test16();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------