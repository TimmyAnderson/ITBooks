//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include "Name.h"
#include "NameNoCopyConstructor.h"
#include "NameWithCopyConstructor.h"
#include "MyArray.h"
#include "LocalVariableClass.h"
#include "NoCustomAssignment.h"
#include "NoCustomAssignmentError.h"
#include "WithCustomAssignment.h"
#include "ComposedClass.h"
#include "Consts.h"
#include "MyStatic.h"
#include "Temporary.h"
#include "NewDelete.h"
#include "Union.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved)
{
   wprintf_s(L"\n\n\nInvalid parameter detected in function %s ! File: %s Line: %d !\n", Function, File, Line);
   wprintf_s(L"Expression: %s !\n\n\n", Expression);
}
//-------------------------------------------------------------------------------------------------------
void DoTest(void)
{
	CMyStatic													Object;

	Object.PrintNonStatic();

	Object.PrintStatic();
}
//-------------------------------------------------------------------------------------------------------
void DoStaticTest(int Value)
{
	// !!! Lokalna STATICKA premenna.
	static CMyText													Object1(L"Static OBJECT 1");

	Object1.GetText();

	if (Value==2)
	{
		// !!! CONSTRUCTOR sa vola AZ ked PRVY KRAT metoda vojde to tohto BLOCKU. To moze byt aj pocas INEHO ako 1. VOLANIA.
		static CMyText												Object2(L"Static OBJECT 2");

		Object2.GetText();
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	CName														Name(L"Timmy",L"Anderson",12);

	Name.PrintNameToConsole();
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	CName														Name1(L"Timmy",L"Anderson",12);
	CName														Name2=CName::JENNY;

	CName::StaticPrintNameToConsole(Name1);
	CName::StaticPrintNameToConsole(Name2);
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	CNameNoCopyConstructor										NameNC1(L"Timmy",L"Anderson",12);
	// !!! Kedze trieda NEMA COPY CONSTRUCTOR, kopiruju sa VSETKY FIELDS.
	CNameNoCopyConstructor										NameNC2=NameNC1;
	CNameNoCopyConstructor										NameNC3;

	wprintf_s(L"----------------------------------------------------------------\n");

	// !!! Kedze trieda NEMA COPY CONSTRUCTOR, kopiruju sa VSETKY FIELDS.
	NameNC3=NameNC1;

	NameNC1.PrintNameToConsole();
	NameNC2.PrintNameToConsole();
	NameNC3.PrintNameToConsole();

	wprintf_s(L"----------------------------------------------------------------\n");
	wprintf_s(L"----------------------------------------------------------------\n");
	wprintf_s(L"----------------------------------------------------------------\n");

	CNameWithCopyConstructor									NameWC1(L"Timmy",L"Anderson",12);
	// !!! Kedze trieda MA COPY CONSTRUCTOR vola sa tento CONSTRUCTOR.
	CNameWithCopyConstructor									NameWC2=NameWC1;
	CNameWithCopyConstructor									NameWC3;

	wprintf_s(L"----------------------------------------------------------------\n");

	// !!!!! Aj ked trieda ma COPY CONSTRUCTOR, kedze sa NEJEDNA o INICIALIZACIU, ale pridadenie NEVOLA SA COPY CONSTRUCTOR, ale kopiruju sa VSETKY FIELDS. Ak by trieda mala OPERATOR PRIRADENIA, tak by sa volal tento OPERATOR.
	NameWC3=NameWC1;

	NameWC1.PrintNameToConsole();
	NameWC2.PrintNameToConsole();
	NameWC3.PrintNameToConsole();

	wprintf_s(L"----------------------------------------------------------------\n");
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	const CName													Name(L"Timmy",L"Anderson",12);

	Name.PrintNameToConsole();

	// !!! Kedze sa jedna o NON-CONST metodu, tak ju NIE JE MOZNE volat pre CONST objekt.
	//Name.SetAge(10);
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	CName														NonConstName(L"Timmy",L"Anderson",12);
	const CName													ConstName(L"Timmy",L"Anderson",12);

	NonConstName.ChainMethod1().ChainMethod2();

	ConstName.ConstChainMethod1().ConstChainMethod2();

	NonConstName.ChainMethod1().ChainMethod2().ConstChainMethod1().ConstChainMethod2();

	// !!! Neprekompiluje pretoze ConstChainMethod2() vracia 'const CName&' a ChainMethod1() je NON-CONST metoda.
	//NonConstName.ChainMethod1().ChainMethod2().ConstChainMethod1().ConstChainMethod2().ChainMethod1();
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	CName														NonConstName(L"Timmy",L"Anderson",12);
	const CName													ConstName(L"Timmy",L"Anderson",12);

	NonConstName.NonConstSetMutableText(L"AAA");

	NonConstName.PrintMutableNonMutableTexts(L"NON CONST object");

	NonConstName.ConstSetMutableText(L"BBB");

	NonConstName.PrintMutableNonMutableTexts(L"NON CONST object");

	wprintf_s(L"\n");

	// !!! NON-CONST metodu NIE JE MOZNE volat pre CONST objekt.
	//ConstName.NonConstSetMutableText(L"AAA");

	ConstName.PrintMutableNonMutableTexts(L"CONST object");

	// !!!!! MUTABLE FIELDS je mozne modifikovat i pre CONST objekty.
	ConstName.ConstSetMutableText(L"BBB");

	ConstName.PrintMutableNonMutableTexts(L"CONST object");
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	CName														Name(L"Timmy",L"Anderson",12);

	Name.Inline1();
	Name.Inline2();

	// !!!!! LINKER ERROR. INLINE metoda NEMOZE byt definovana v CPP subore, pretoze KOMPILATOR by nemal pristupne v INYCH CPP FILES jej TELO a NEMOHOL by ho NAHRADIT na mieste volania INLINE METODY.
	//Name.Inline3();
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	CName														Name1(L"Timmy",L"Anderson",12);
	CName														Name2(L"Jenny",L"Thompson",13);
	CName														Name3(L"Timmy",L"Anderson",12);

	if (Name1==Name2)
	{
		wprintf_s(L"Name1==Name2 !\n");
	}
	else
	{
		wprintf_s(L"Name1!=Name2 !\n");
	}

	if (Name1==Name3)
	{
		wprintf_s(L"Name1==Name3 !\n");
	}
	else
	{
		wprintf_s(L"Name1!=Name3 !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	// Vola sa DEFAULT CONSTUCTOR.
	CMyArray													Array;

	Array.DoNothing();

	// Vola sa DESTUCTOR.
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	// Vola sa DEFAULT CONSTUCTOR.
	CMyArray*													Array=new CMyArray;

	Array->DoNothing();

	// Vola sa DESTUCTOR.
	delete(Array);
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	CLocalVariableClass											Class1(L"1");
	CLocalVariableClass											Class2(L"2");
	CLocalVariableClass											Class3(L"3");

	Class1.PrintValue();
	Class2.PrintValue();
	Class3.PrintValue();

	if (true)
	{
		CLocalVariableClass										Class4(L"4");

		Class4.PrintValue();
	}
	else
	{
		CLocalVariableClass										Class5(L"5");

		Class5.PrintValue();
	}

	CLocalVariableClass											Class6(L"6");

	Class6.PrintValue();

	// DESTRUCTORS sa volaju v OPACNOM poradi ako CONSTRUCTORS.
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	wprintf_s(L"--------------------------------------------------\n");

	CNoCustomAssignment											Object1(L"1",1);

	Object1.PrintValue();

	// Kopiruju sa vsetky FIELDS.
	CNoCustomAssignment											Object2=Object1;

	Object2.PrintValue();

	CNoCustomAssignment											Object3;

	// Kopiruju sa vsetky FIELDS.
	Object3=Object1;

	Object3.PrintValue();

	/*
	CNoCustomAssignmentError									Object4(L"4",4);
	CNoCustomAssignmentError									Object5;

	// !!! Hodi KOMPILACNU CHYBU, lebo CLASS obsahuje CONST FIELD a NEOBSAHUJE CUSTOM OPERATOR=, takze C++ nedokaze generovat OPERATOR=, ktory by prekopiroval vsetky FIELDS, ako to robi ak nie je definovany CONST FIELD v CLASS.
	Object5=Object4;
	*/
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	CWithCustomAssignment										Object1(L"1",1);

	Object1.PrintValue();

	// !!! Kedze je definovany COPY CONSTRUCTOR, vola sa ten.
	CWithCustomAssignment										Object2=Object1;

	Object2.PrintValue();

	CWithCustomAssignment										Object3;

	// !!! Kedze je definovany OPERATOR=, vola sa ten.
	Object3=Object1;

	Object3.PrintValue();
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	// Vola sa DEFAULT CONSTRUCTOR, ktory NEPOUZIVA INITIALIZERS. CONSTRUCTOR FILEDS su volane v poradi v akom su FIELDS DEKLAROVANE v CLASS.
	CComposedClass												Object;

	Object.DoNothing();
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	// !!! Vola sa NON-DEFAULT CONSTRUCTOR, ktory POUZIVA INITIALIZERS v OPACNOM PORADI v akom su FIELDS DEKLAROVANE. CONSTRUCTORS sa vsak VZDY volaju v poradi v akom su FIELDS deklarovane v CLASS.
	CComposedClass												Object(1);

	Object.DoNothing();
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	CConsts														MyObject1;
	CConsts														MyObject2(30);

	MyObject1.Print();
	MyObject2.Print();
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	wprintf_s(L"Test17() CALL 1\n");

	DoTest();

	wprintf_s(L"Test17() CALL 2\n");
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	wprintf_s(L"Test18() CALL 1\n");

	DoStaticTest(1);

	wprintf_s(L"Test18() CALL 2\n");

	DoStaticTest(2);

	wprintf_s(L"Test18() CALL 3\n");
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	wprintf_s(L"----------------------------------------------\n");

	CTemporary													Variable1(L"Timmy");
	CTemporary													Variable2(L"Anderson");

	// !!! Vytvori sa TEMP VARIABLE, ktora sa na KONCI totho prikazu LIKVIDUJE a vola sa DESTRUCTOR.
	(Variable1+Variable2).Print();

	// !!! Tu uz TEMP VARIABLE NEEXISTUJE.
	wprintf_s(L"Test19() END\n");
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	wprintf_s(L"----------------------------------------------\n");

	// !!! Tento BUFFER sa pouzije na 'alokovanie' (presnejsie priradzovanie) pamate OPERATOROM PLACEMENT NEW.
	char*														Buffer=new char[10000];

	memset(Buffer,0,sizeof(Buffer));

	// Pouzitie standardneho NEW.
	CMyText*													Text1=new CMyText(L"STANDARD OPERATOR NEW");

	// !!! Urcim si poziciu, kde NAMAPUJEM cez PLACEMENT NEW novy OBJEKT.
	char*														Pointer=Buffer;

	// !!!!! Pouzitie PLACEMENT NEW. V tomto pripade sa pre OBJEKT 'Text2' NEALOKUJE PAMAT na HEAP, iba sa objekt 'NAMAPUJE' do pozicie POINTERA 'Pointer' (zaciatok BUFFER).
	// !!!!! PLACEMENT NEW aj ked NEALOKUJE ZIADNU PAMAT, tak VOLA CONSTRUCTOR.
	CMyText*													Text2=new (Pointer) CMyText(L"PLACEMENT SYNTAX 1 for OPERATOR NEW");

	// !!!!! Posuniem MAPOVANIE na DALSIU VOLNU POZICIU v BUFFERI.
	Pointer+=sizeof(CMyText);

	CMyText*													Text3=new (Pointer) CMyText(L"PLACEMENT SYNTAX 2 for OPERATOR NEW");

	Text1->GetText();
	Text2->GetText();
	Text3->GetText();

	delete(Text1);

	// !!!!! OPERATOR DELETE NEMA PLACEMENT EXPRESSION.
	// !!!!! Objekt 'alokovany' cez PLACEMENT NEW (kedze v skutocnosti PLACEMENT ZIADNU PAMAT NEALOKUJE, iba MAPUJE EXISATUJUCU PAMAT), ak by nan bol zavolany DELETE, skoncilo by to NARUSENIM PAMATE, kedze PLACEMENT NEW ZIADNU PAMAT na HEAP NEALOKUJE iba MAPUJE PAMAT z BUFFERA zaslaneho ako PARAMETER PLACEMENT NEW.
	//delete(Text2);
	//delete(Text3);

	// !!!!! Pozor toto NEFUNGUJE. C++ ho NEINTEPRETUJE ako DELETE s PLACEMENT EXPRESSION (ktory NEPODPORUJE), ale ako 2 EXPRESSIONS oddelene CIARKOU.
	//delete(Text2,Buffer);

	// !!!!! Dokonca i toto C++ akceptuje, aj ked je to logicky NEZMYSEL.
	//delete(Text2,Buffer,Buffer,Buffer,Buffer,Buffer);

	// !!!!! Kedze [delete(Text2)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text2->~CMyText();

	// !!!!! Kedze [delete(Text3)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text3->~CMyText();

	// Dealokujem BUFFER.
	delete[](Buffer);
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	wprintf_s(L"----------------------------------------------\n");

	// !!! Tento BUFFER sa pouzije na 'alokovanie' (presnejsie priradzovanie) pamate OPERATOROM PLACEMENT NEW.
	char														Buffer[10000];

	memset(Buffer,0,sizeof(Buffer));

	// Pouzitie standardneho NEW.
	CMyText*													Text1=new CMyText(L"STANDARD OPERATOR NEW");

	// !!! Urcim si poziciu, kde NAMAPUJEM cez PLACEMENT NEW novy OBJEKT.
	char*														Pointer=Buffer;

	// !!!!! Pouzitie PLACEMENT NEW. V tomto pripade sa pre OBJEKT 'Text2' NEALOKUJE PAMAT na HEAP, iba sa objekt 'NAMAPUJE' do pozicie POINTERA 'Pointer' (zaciatok BUFFER).
	// !!!!! PLACEMENT NEW aj ked NEALOKUJE ZIADNU PAMAT, tak VOLA CONSTRUCTOR.
	CMyText*													Text2=new (Pointer) CMyText(L"PLACEMENT SYNTAX 1 for OPERATOR NEW");

	// !!!!! Posuniem MAPOVANIE na DALSIU VOLNU POZICIU v BUFFERI.
	Pointer+=sizeof(CMyText);

	CMyText*													Text3=new (Pointer) CMyText(L"PLACEMENT SYNTAX 2 for OPERATOR NEW");

	Text1->GetText();
	Text2->GetText();
	Text3->GetText();

	delete(Text1);

	// !!!!! OPERATOR DELETE NEMA PLACEMENT EXPRESSION.
	// !!!!! Objekt 'alokovany' cez PLACEMENT NEW (kedze v skutocnosti PLACEMENT ZIADNU PAMAT NEALOKUJE, iba MAPUJE EXISATUJUCU PAMAT), ak by nan bol zavolany DELETE, skoncilo by to NARUSENIM PAMATE, kedze PLACEMENT NEW ZIADNU PAMAT na HEAP NEALOKUJE iba MAPUJE PAMAT z BUFFERA zaslaneho ako PARAMETER PLACEMENT NEW.
	//delete(Text2);
	//delete(Text3);

	// !!!!! Pozor toto NEFUNGUJE. C++ ho NEINTEPRETUJE ako DELETE s PLACEMENT EXPRESSION (ktory NEPODPORUJE), ale ako 2 EXPRESSIONS oddelene CIARKOU.
	//delete(Text2,Buffer);

	// !!!!! Dokonca i toto C++ akceptuje, aj ked je to logicky NEZMYSEL.
	//delete(Text2,Buffer,Buffer,Buffer,Buffer,Buffer);

	// !!!!! Kedze [delete(Text2)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text2->~CMyText();

	// !!!!! Kedze [delete(Text3)] NEVOLAM, tak MUSIM EXPLICITNE volat DESTRUCTOR.
	Text3->~CMyText();

	// !!! Kedze BUFFER je v STACK, tak sa uvolni na KONCI FUNKCIE.
}
//-------------------------------------------------------------------------------------------------------
void Test22(void)
{
	wprintf_s(L"----------------------------------------------\n");

	wstring														Param1(L"XXX");
	wstring														Param2(L"YYY");

	CNewDelete*													NewDelete1=new CNewDelete();
	CNewDelete*													NewDelete2=new (Param1) CNewDelete();
	CNewDelete*													NewDelete3=new (Param1,Param2) CNewDelete();

	delete(NewDelete1);
	NewDelete2->operator delete(NewDelete2,Param1);
	NewDelete3->operator delete(NewDelete3,Param1,Param2);
}
//-------------------------------------------------------------------------------------------------------
void Test23(void)
{
	wprintf_s(L"----------------------------------------------\n");

	USomeUnion													Union;

	Union.MIntValue=10;

	Union.Print();

	Union.MDoubleValue=33.33;

	Union.Print();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT,0);

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
	Test21();
	//Test22();
	//Test23();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------