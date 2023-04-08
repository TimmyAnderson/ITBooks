//-------------------------------------------------------------------------------------------------------
#include <utility>
#include <vector>
#include <iostream>
#include "MyDebug.h"
#include "CType1.h"
#include "CType2.h"
#include "CType3.h"
#include "CType4.h"
#include "CType5.h"
#include "CCopyAndMoveConstructor.h"
#include "CItem.h"
#include "CTypeWithMoveSemantics.h"
//-------------------------------------------------------------------------------------------------------
int																CItem::MCounter=0;
//-------------------------------------------------------------------------------------------------------
void TestLValuesAndRValues1(void)
{
	PrintLineSeparator();

	int															A;
	int															B=10;

	// !!! V tejto EXPRESSION su [A] aj [B] LVALUES, pretoze ich platnost trva za hranice tejto EXPRESSION.
	A=B;

	wcout << L"A=[" << A << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestLValuesAndRValues2(void)
{
	PrintLineSeparator();

	int															A=10;
	int															B=20;
	int															C;

	// !!! V tejto EXPRESSION je [C] LVALUE, pretoze jej platnost trva za hranice tejto EXPRESSION.
	// !!!!! V tejto EXPRESSION je [A+B] RVALUE, pretoze je vysledok je ulozeny do TEMPORARY VARIABLE, ktorej platnost trva iba do skoncenia tejto EXPRESSION.
	C=A+B;

	wcout << L"C=[" << C << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestLValuesAndRValues3(void)
{
	PrintLineSeparator();

	int															A=10;
	int															B;

	// !!! V tejto EXPRESSION je [B] LVALUE, pretoze jej platnost trva za hranice tejto EXPRESSION.
	// !!!!! V tejto EXPRESSION je [A+2] RVALUE, pretoze je vysledok je ulozeny do TEMPORARY VARIABLE, ktorej platnost trva iba do skoncenia tejto EXPRESSION.
	B=A+2;

	wcout << L"B=[" << B << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestLValuesAndRValues4(void)
{
	PrintLineSeparator();

	int															A;

	// !!! V tejto EXPRESSION je [A] LVALUE, pretoze jej platnost trva za hranice tejto EXPRESSION.
	// !!! V tejto EXPRESSION je [2] RVALUE pretoze jeho platnost trva iba do skoncenia tejto EXPRESSION.
	A=2;

	wcout << L"A=[" << A << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int& SomeFunction(int& Variable)
{
	return(Variable);
}
//-------------------------------------------------------------------------------------------------------
void TestLValuesAndRValues5(void)
{
	PrintLineSeparator();

	int															A;

	SomeFunction(A)=10;

	int*														PA;

	PA=&SomeFunction(A);

	wcout << L"A=[" << A << L"] !" << endl;
	wcout << L"PA=[" << *PA << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! TENTO CODE UMYSELNE sposobuje ERROR.
void TestRValuesTypeWithNoCopyAndMoveConstructor1(void)
{
	PrintLineSeparator();

	{
		CType1													Variable1{1,2,3};
		// !!! Kedze CType1 NEMA EXPLICITNY COPY CONSTRUCTOR, ani MOVE CONSTRUCTOR, C++ vykona kopirovanie FIELDS, cim vznikne SHALLOW COPY objektu.
		// !!!!! Tento CODE SPOSOBI ERROR, pretoze obe instancie obsahuju POINTER na ten isty BUFFER a pri volani DESTRUCTORS pre OBE INSTANCIE, druhe volanie DESTRUCTOR sa pokusi uvolenit uz uvolnenu MEMORY cim dojde k RUNTIME ERROR.
		CType1													Variable2=Variable1;

		wcout << L"Variable1.MData=[" << Variable1.MData << L"] !" << endl;
		wcout << L"Variable2.MData=[" << Variable2.MData << L"] !" << endl;

		// !!!!! Na konci SCOPE sa volaju DESTRUCTOR. Zatial co 1. volanie DESTRUCTOR korekne odstrani MEMORY, 2. volanie DESTRUCTOR sa pokusi uvolnit UZ UVOLNENU MEMORY a dojde k RUNTIME ERROR.
		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithNoCopyAndMoveConstructor2(void)
{
	PrintLineSeparator();

	{
		CType1													Variable1{1,2,3};
		// !!! Kedze CType1 NEMA EXPLICITNY COPY CONSTRUCTOR, ani MOVE CONSTRUCTOR, C++ vykona kopirovanie FIELDS, cim vznikne SHALLOW COPY objektu.
		// !!!!! Tento CODE SPOSOBI ERROR, pretoze obe instancie obsahuju POINTER na ten isty BUFFER a pri volani DESTRUCTORS pre OBE INSTANCIE, druhe volanie DESTRUCTOR sa pokusi uvolenit uz uvolnenu MEMORY cim dojde k RUNTIME ERROR.
		CType1													Variable2=Variable1;

		wcout << L"Variable1.MData=[" << Variable1.MData << L"] !" << endl;
		wcout << L"Variable2.MData=[" << Variable2.MData << L"] !" << endl;

		// !!!!! Na to aby CODE NESPOSOBIL ERROR je NUTNE nastavit [Variable1.MData], alebo [Variable2.MData] na [nullptr].
		Variable2.MData=nullptr;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CType2 CreateCType2(void)
{
	CType2														Variable{9,8,7};

	return(Variable);
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyButNoMoveConstructor1(void)
{
	PrintLineSeparator();

	{
		CType2													Variable1{1,2,3};
		// !!!!! Kedze TYPE [CType2] ma COPY CONSTRUCTOR aj MOVE CONSTRUCTOR, C++ musi vybrat, ktory CONSTRUCTOR ma pouzit. Kedze v EXPRESSION [Variable2=Variable1] je [Variable1] LVALUE, pouzije sa COPY CONSTRUCTOR.
		CType2													Variable2=Variable1;

		wcout << L"Variable1.MData=[" << Variable1.MData << L"] !" << endl;
		wcout << L"Variable2.MData=[" << Variable2.MData << L"] !" << endl;

		PrintLineSeparator();

		// !!!!! Kedze TYPE [CType2] ma COPY CONSTRUCTOR aj MOVE CONSTRUCTOR, C++ musi vybrat, ktory CONSTRUCTOR ma pouzit. Kedze v EXPRESSION [Variable3=CreateCType2()] je [CreateCType2()] RVALUE, pouzije sa MOVE CONSTRUCTOR.
		CType2													Variable3=CreateCType2();

		PrintLineSeparator();

		wcout << L"Variable3.MData=[" << Variable3.MData << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType2ByValue(CType2)
{
	wcout << L"----- void ProcessCType2ByValue() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyButNoMoveConstructor2(void)
{
	PrintLineSeparator();

	{
		CType2													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Vola sa COPY CONSTRUCTOR.
		ProcessCType2ByValue(Variable);

		PrintLineSeparator();

		// !!! Vola sa COPY CONSTRUCTOR.
		ProcessCType2ByValue(CreateCType2());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType2ByReference(const CType2&)
{
	wcout << L"----- void ProcessCType2ByReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyButNoMoveConstructor3(void)
{
	PrintLineSeparator();

	{
		CType2													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Nevola sa CONSTRUCTOR, pretoze EXPRESSION [Variable] je LVALUE a FUNCTION ocakava PARAMETER typu REFERENCE.
		ProcessCType2ByReference(Variable);

		PrintLineSeparator();

		// !!!!! Vola sa COPY CONSTRUCTOR, pretoze EXPRESSION [CreateCType2()] je RVALUE a [CType2] NEMA MOVE CONSTRUCTOR.
		ProcessCType2ByReference(CreateCType2());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType2ByConstReference(const CType2&)
{
	wcout << L"void ProcessCType2ByConstReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyButNoMoveConstructor4(void)
{
	PrintLineSeparator();

	{
		CType2													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Nevola sa CONSTRUCTOR, pretoze EXPRESSION [Variable] je LVALUE a FUNCTION ocakava PARAMETER typu CONST REFERENCE.
		ProcessCType2ByConstReference(Variable);

		PrintLineSeparator();

		// !!!!! Vola sa COPY CONSTRUCTOR, pretoze EXPRESSION [CreateCType2()] je RVALUE a [CType2] NEMA MOVE CONSTRUCTOR.
		ProcessCType2ByConstReference(CreateCType2());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType2ByRValueReference(CType2&&)
{
	wcout << L"void ProcessCType2ByRValueReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyButNoMoveConstructor5(void)
{
	PrintLineSeparator();

	{
		CType2													Variable={1,2,3};

		PrintLineSeparator();

		/*
		// !!!!! COMPILER hodi ERROR, pretoze EXPRESSION [Variable] je LVALUE zatial co FUNCTION ocakava PARAMETER typu RVALUE REFERENCE.
		ProcessCType2ByRValueReference(Variable);

		PrintLineSeparator();
		*/

		// !!!!! Nevola sa COPY CONSTRUCTOR, pretoze EXPRESSION [(CType2&&) Variable] je RVALUE, TYPE [CType2] NEMA MOVE CONSTRUCTOR a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType2ByRValueReference((CType2&&) Variable);

		PrintLineSeparator();

		// !!!!! Nevola sa COPY CONSTRUCTOR, pretoze EXPRESSION [move(Variable)] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType2ByRValueReference(move(Variable));

		PrintLineSeparator();

		// !!!!! Vola sa COPY CONSTRUCTOR, pretoze EXPRESSION [CreateCType2()] je RVALUE a [CType2] NEMA MOVE CONSTRUCTOR.
		ProcessCType2ByRValueReference(CreateCType2());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType2ByRValueConstReference(const CType2&&)
{
	wcout << L"void ProcessCType2ByRValueConstReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyButNoMoveConstructor6(void)
{
	PrintLineSeparator();

	{
		CType2													Variable={1,2,3};

		PrintLineSeparator();

		/*
		// !!!!! COMPILER hodi ERROR, pretoze EXPRESSION [Variable] je LVALUE zatial co FUNCTION ocakava PARAMETER typu RVALUE CONST REFERENCE.
		ProcessCType2ByRValueConstReference(Variable);

		PrintLineSeparator();
		*/

		// !!!!! Nevola sa COPY CONSTRUCTOR, pretoze EXPRESSION [(CType2&&) Variable] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE CONST REFERENCE.
		ProcessCType2ByRValueConstReference((CType2&&) Variable);

		PrintLineSeparator();

		// !!!!! Nevola sa COPY CONSTRUCTOR, pretoze EXPRESSION [move(Variable)] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE CONST REFERENCE.
		ProcessCType2ByRValueConstReference(move(Variable));

		PrintLineSeparator();

		// !!!!! Aj tu sa VOLA COPY CONSTRUCTOR, pretoze EXPRESSION [CreateCType2()] je RVALUE a CType2 NEIMPLEMENTUJE MOVE CONSTRUCTOR.
		ProcessCType2ByRValueConstReference(CreateCType2());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CType3 CreateCType3(void)
{
	CType3														Variable{9,8,7};

	return(Variable);
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithMoveButNoCopyConstructor1(void)
{
	PrintLineSeparator();

	{
		CType3													Variable1{1,2,3};
		// !!! Kedze CType3 NEMA EXPLICITNY COPY CONSTRUCTOR, C++ vykona kopirovanie FIELDS, cim vznikne SHALLOW COPY objektu.
		// !!!!! Tento CODE SPOSOBI ERROR, pretoze obe instancie obsahuju POINTER na ten isty BUFFER a pri volani DESTRUCTORS pre OBE INSTANCIE, druhe volanie DESTRUCTOR sa pokusi uvolenit uz uvolnenu MEMORY cim dojde k RUNTIME ERROR.
		//CType3												Variable2=Variable1;

		wcout << L"Variable1.MData=[" << Variable1.MData << L"] !" << endl;
		//wcout << L"Variable2.MData=[" << Variable2.MData << L"] !" << endl;

		PrintLineSeparator();

		// !!!!! Kedze TYPE [CType3] ma iba MOVE CONSTRUCTOR, C++ ho zavola.
		CType3													Variable3=CreateCType3();

		PrintLineSeparator();

		wcout << L"Variable3.MData=[" << Variable3.MData << L"] !" << endl;

		//Variable2.MData=nullptr;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType3ByValue(CType3)
{
	wcout << L"----- void ProcessCType3ByValue() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithMoveButNoCopyConstructor2(void)
{
	PrintLineSeparator();

	{
		CType3													Variable={1,2,3};

		PrintLineSeparator();

		/*
		// !!!!! Tento CODE SPOSOBI ERROR, pretoze CType3 NEMA COPY CONSTRUCTOR a pri prenose VARIABLE BY VALUE sa vytvori TEMPORARY kopia objektu iba kopirovanim FIELDS, vdaka comu budu 2 INSTANCIE CType3 odkazovat na ten isty BUFFER. Nasledne sa 2 krat vola DESTRUCTOR, pricom druhe volanie sa pokusi odstranit UZ ODSTRANENY BUFFER co sposobi RUNTIME ERROR.
		ProcessCType3ByValue(Variable);

		PrintLineSeparator();
		*/

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType3()] je RVALUE.
		ProcessCType3ByValue(CreateCType3());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType3ByReference(const CType3&)
{
	wcout << L"----- void ProcessCType3ByReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithMoveButNoCopyConstructor3(void)
{
	PrintLineSeparator();

	{
		CType3													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Nevola sa CONSTRUCTOR, pretoze EXPRESSION [Variable] je LVALUE a FUNCTION ocakava PARAMETER typu REFERENCE.
		ProcessCType3ByReference(Variable);

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType3()] je RVALUE a [CType3] ma MOVE CONSTRUCTOR.
		ProcessCType3ByReference(CreateCType3());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType3ByConstReference(const CType3&)
{
	wcout << L"void ProcessCType3ByConstReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithMoveButNoCopyConstructor4(void)
{
	PrintLineSeparator();

	{
		CType3													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Nevola sa CONSTRUCTOR, pretoze EXPRESSION [Variable] je LVALUE a FUNCTION ocakava PARAMETER typu CONST REFERENCE.
		ProcessCType3ByConstReference(Variable);

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType3()] je RVALUE a [CType3] ma MOVE CONSTRUCTOR.
		ProcessCType3ByConstReference(CreateCType3());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType3ByRValueReference(CType3&&)
{
	wcout << L"void ProcessCType3ByRValueReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithMoveButNoCopyConstructor5(void)
{
	PrintLineSeparator();

	{
		CType3													Variable={1,2,3};

		PrintLineSeparator();

		/*
		// !!!!! COMPILER hodi ERROR, pretoze EXPRESSION [Variable] je LVALUE zatial co FUNCTION ocakava PARAMETER typu RVALUE REFERENCE.
		ProcessCType3ByRValueReference(Variable);

		PrintLineSeparator();
		*/

		// !!!!! Nevola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [(CType3&&) Variable] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType3ByRValueReference((CType3&&) Variable);

		PrintLineSeparator();

		// !!!!! Nevola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [move(Variable)] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType3ByRValueReference(move(Variable));

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType3()] je RVALUE a [CType3] ma MOVE CONSTRUCTOR.
		ProcessCType3ByRValueReference(CreateCType3());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType3ByRValueConstReference(const CType3&&)
{
	wcout << L"void ProcessCType3ByRValueConstReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithMoveButNoCopyConstructor6(void)
{
	PrintLineSeparator();

	{
		CType3													Variable={1,2,3};

		PrintLineSeparator();

		/*
		// !!!!! COMPILER hodi ERROR, pretoze EXPRESSION [Variable] je LVALUE zatial co FUNCTION ocakava PARAMETER typu RVALUE CONST REFERENCE.
		ProcessCType3ByRValueConstReference(Variable);

		PrintLineSeparator();
		*/

		// !!!!! Nevola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [(CType3&&) Variable] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType3ByRValueConstReference((CType3&&) Variable);

		PrintLineSeparator();

		// !!!!! Nevola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [move(Variable)] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType3ByRValueConstReference(move(Variable));

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType3()] je RVALUE a [CType3] ma MOVE CONSTRUCTOR.
		ProcessCType3ByRValueConstReference(CreateCType3());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CType4 CreateCType4(void)
{
	CType4														Variable{9,8,7};

	return(Variable);
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyAndMoveConstructor1(void)
{
	PrintLineSeparator();

	{
		CType4													Variable1{1,2,3};
		// !!!!! Kedze TYPE [CType4] ma COPY CONSTRUCTOR aj MOVE CONSTRUCTOR, C++ musi vybrat, ktory CONSTRUCTOR ma pouzit. Kedze v EXPRESSION [Variable2=Variable1] je [Variable1] LVALUE, pouzije sa COPY CONSTRUCTOR.
		CType4													Variable2=Variable1;

		wcout << L"Variable1.MData=[" << Variable1.MData << L"] !" << endl;
		wcout << L"Variable2.MData=[" << Variable2.MData << L"] !" << endl;

		PrintLineSeparator();

		// !!!!! Kedze TYPE [CType4] ma COPY CONSTRUCTOR aj MOVE CONSTRUCTOR, C++ musi vybrat, ktory CONSTRUCTOR ma pouzit. Kedze v EXPRESSION [Variable3=CreateCType4()] je [CreateCType4()] RVALUE, pouzije sa MOVE CONSTRUCTOR.
		CType4													Variable3=CreateCType4();

		PrintLineSeparator();

		wcout << L"Variable3.MData=[" << Variable3.MData << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType4ByValue(CType4)
{
	wcout << L"----- void ProcessCType4ByValue() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyAndMoveConstructor2(void)
{
	PrintLineSeparator();

	{
		CType4													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Vola sa COPY CONSTRUCTOR, pretoze EXPRESSION [Variable] je LVALUE.
		ProcessCType4ByValue(Variable);

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType4()] je RVALUE.
		ProcessCType4ByValue(CreateCType4());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType4ByReference(const CType4&)
{
	wcout << L"----- void ProcessCType4ByReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyAndMoveConstructor3(void)
{
	PrintLineSeparator();

	{
		CType4													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Nevola sa CONSTRUCTOR, pretoze EXPRESSION [Variable] je LVALUE a FUNCTION ocakava PARAMETER typu REFERENCE.
		ProcessCType4ByReference(Variable);

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType4()] je RVALUE a [CType4] ma MOVE CONSTRUCTOR.
		ProcessCType4ByReference(CreateCType4());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType4ByConstReference(const CType4&)
{
	wcout << L"void ProcessCType4ByConstReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyAndMoveConstructor4(void)
{
	PrintLineSeparator();

	{
		CType4													Variable={1,2,3};

		PrintLineSeparator();

		// !!! Nevola sa CONSTRUCTOR, pretoze EXPRESSION [Variable] je LVALUE a FUNCTION ocakava PARAMETER typu CONST REFERENCE.
		ProcessCType4ByConstReference(Variable);

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType4()] je RVALUE a [CType4] ma MOVE CONSTRUCTOR.
		ProcessCType4ByConstReference(CreateCType4());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType4ByRValueReference(CType4&&)
{
	wcout << L"void ProcessCType4ByRValueReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyAndMoveConstructor5(void)
{
	PrintLineSeparator();

	{
		CType4													Variable={1,2,3};

		PrintLineSeparator();

		/*
		// !!!!! COMPILER hodi ERROR, pretoze EXPRESSION [Variable] je LVALUE zatial co FUNCTION ocakava PARAMETER typu RVALUE REFERENCE.
		ProcessCType4ByRValueReference(Variable);

		PrintLineSeparator();
		*/

		// !!!!! Nevola sa COPY ani MOVE CONSTRUCTOR, pretoze EXPRESSION [(CType4&&) Variable] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType4ByRValueReference((CType4&&) Variable);

		PrintLineSeparator();

		// !!!!! Nevola sa COPY ani MOVE CONSTRUCTOR, pretoze EXPRESSION [move(Variable)] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType4ByRValueReference(move(Variable));

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType4()] je RVALUE a [CType4] ma MOVE CONSTRUCTOR.
		ProcessCType4ByRValueReference(CreateCType4());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ProcessCType4ByRValueConstReference(const CType4&&)
{
	wcout << L"void ProcessCType4ByRValueConstReference() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesTypeWithCopyAndMoveConstructor6(void)
{
	PrintLineSeparator();

	{
		CType4													Variable={1,2,3};

		PrintLineSeparator();

		/*
		// !!!!! COMPILER hodi ERROR, pretoze EXPRESSION [Variable] je LVALUE zatial co FUNCTION ocakava PARAMETER typu RVALUE CONST REFERENCE.
		ProcessCType4ByRValueConstReference(Variable);

		PrintLineSeparator();
		*/

		// !!!!! Nevola sa COPY ani MOVE CONSTRUCTOR, pretoze EXPRESSION [(CType4&&) Variable] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType4ByRValueConstReference((CType4&&) Variable);

		PrintLineSeparator();

		// !!!!! Nevola sa COPY ani MOVE CONSTRUCTOR, pretoze EXPRESSION [move(Variable)] je RVALUE a FUNCTION prebera ako PARAMETER RVALUE REFERENCE.
		ProcessCType4ByRValueConstReference(move(Variable));

		PrintLineSeparator();

		// !!!!! Vola sa MOVE CONSTRUCTOR, pretoze EXPRESSION [CreateCType4()] je RVALUE a [CType4] ma MOVE CONSTRUCTOR.
		ProcessCType4ByRValueConstReference(CreateCType4());

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int ReturnValue1(void)
{
	return(100);
}
//-------------------------------------------------------------------------------------------------------
int& ReturnValue2(int& Value)
{
	return(Value);
}
//-------------------------------------------------------------------------------------------------------
int&& ReturnValue3(int&& Value)
{
	return(move(Value));
}
//-------------------------------------------------------------------------------------------------------
void FunctionOverloading(int&)
{
	wcout << L"REFERENCE FUNCTION CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void FunctionOverloading(int&&)
{
	wcout << L"RVALUE REFERENCE FUNCTION CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesOverloading1(void)
{
	PrintLineSeparator();

	// !!! Kedze EXPRESSION [100] je RVALUE, vola sa FUNCTION s PARAMETROM typu RVALUE REFERENCE.
	FunctionOverloading(100);

	PrintLineSeparator();

	int															Variable=100;

	// !!! Kedze EXPRESSION [Value] je LVALUE, vola sa FUNCTION s PARAMETROM typu REFERENCE.
	FunctionOverloading(Variable);

	PrintLineSeparator();

	// !!! Kedze EXPRESSION [Variable] je RVALUE, vola sa FUNCTION s PARAMETROM typu RVALUE REFERENCE.
	FunctionOverloading(Variable+5);

	PrintLineSeparator();

	// !!! Kedze EXPRESSION [move(Variable)] je RVALUE, vola sa FUNCTION s PARAMETROM typu RVALUE REFERENCE.
	FunctionOverloading(move(Variable));

	PrintLineSeparator();

	// !!! Kedze EXPRESSION [(int&&) Variable] je RVALUE, vola sa FUNCTION s PARAMETROM typu RVALUE REFERENCE.
	FunctionOverloading((int&&) Variable);

	PrintLineSeparator();

	// !!! Kedze EXPRESSION [ReturnValue1()] je RVALUE, vola sa FUNCTION s PARAMETROM typu RVALUE REFERENCE.
	FunctionOverloading(ReturnValue1());

	PrintLineSeparator();

	// !!! Kedze EXPRESSION [int& ReturnValue2(Variable)] je LVALUE, vola sa FUNCTION s PARAMETROM typu REFERENCE.
	FunctionOverloading(ReturnValue2(Variable));

	PrintLineSeparator();

	// !!! Kedze EXPRESSION [int&& ReturnValue3(100)] je RVALUE, vola sa FUNCTION s PARAMETROM typu RVALUE REFERENCE.
	FunctionOverloading(ReturnValue3(100));

	PrintLineSeparator();

	// !!! Kedze EXPRESSION [int& ReturnValue3(move(Variable))] je RVALUE, vola sa FUNCTION s PARAMETROM typu RVALUE REFERENCE.
	FunctionOverloading(ReturnValue3(move(Variable)));

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Function1(int&)
{
	wcout << L"FUNCTION void Function1(int& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void Function2(const int&)
{
	wcout << L"FUNCTION void Function2(const int& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void Function3(int&&)
{
	wcout << L"FUNCTION void Function3(int&& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void Function4(const int&&)
{
	wcout << L"FUNCTION void Function4(const int&& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void FunctionOverloadingA(int&)
{
	wcout << L"FUNCTION void FunctionOverloadingA(int& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void FunctionOverloadingA(int&&)
{
	wcout << L"FUNCTION void FunctionOverloadingA(int&& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void FunctionOverloadingB(const int&)
{
	wcout << L"FUNCTION void FunctionOverloadingB(const int& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void FunctionOverloadingB(const int&&)
{
	wcout << L"FUNCTION void FunctionOverloadingB(const int&& Value) CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void TestRValuesOverloading2(void)
{
	PrintLineSeparator();

	int															Variable=100;

	// FUNCTION Function1() pre LVALUES moze byt volana.
	Function1(Variable);

	// !!! FUNCTION Function1() pre RVALUES NEMOZE byt VOLANA a COMPILER hodi ERROR.
	//Function1(100);

	PrintLineSeparator();

	// FUNCTION Function2() pre LVALUES moze byt volana.
	Function2(Variable);

	// !!! FUNCTION Function2() pre RVALUES moze byt volana.
	Function2(100);

	PrintLineSeparator();

	// FUNCTION Function3() pre LVALUES NEMOZE byt volana a COMPILER hodi ERROR.
	//Function3(Variable);

	// !!! FUNCTION Function3() pre RVALUES moze byt volana.
	Function3(100);

	PrintLineSeparator();

	// FUNCTION Function4() pre LVALUES NEMOZE byt volana a COMPILER hodi ERROR.
	//Function4(Variable);

	// !!! FUNCTION Function4() pre RVALUES moze byt volana.
	Function4(100);

	PrintLineSeparator();

	// !!! Kedze [Variable] je LVALUE, vola sa verzia FUNCTION s REFERENCE TYPE.
	FunctionOverloadingA(Variable);

	// !!! Kedze [100] je RVALUE, vola sa verzia FUNCTION s RVALUE REFERENCE TYPE.
	FunctionOverloadingA(100);

	PrintLineSeparator();

	// !!! Kedze [Variable] je LVALUE, vola sa verzia FUNCTION s CONST REFERENCE TYPE.
	FunctionOverloadingB(Variable);

	// !!! Kedze [100] je RVALUE, vola sa verzia FUNCTION s RVALUE CONST REFERENCE TYPE.
	FunctionOverloadingB(100);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestOperatorAssignment(void)
{
	PrintLineSeparator();

	{
		CType5													Variable1{1,2,3};
		CType5													Variable2;
		CType5													Variable3;

		wcout << L"Variable1.MData=[" << Variable1.MData << L"] !" << endl;

		PrintLineSeparator();

		// !!! Kedze EXPRESSION [Variable1] je LVALUE, vola sa COPY verzia OPERATOR=.
		Variable2=Variable1;

		PrintLineSeparator();

		wcout << L"Variable2.MData=[" << Variable2.MData << L"] !" << endl;

		// !!! Kedze EXPRESSION [{9,8,7}] je RVALUE, vola sa MOVE verzia OPERATOR=.
		Variable3={9,8,7};

		PrintLineSeparator();

		wcout << L"Variable3.MData=[" << Variable3.MData << L"] !" << endl;

		PrintLineSeparator();

		wcout << L"Variable1.IsEmpty() [" << Variable1.IsEmpty() << L"] !" << endl;
		wcout << L"Variable2.IsEmpty() [" << Variable2.IsEmpty() << L"] !" << endl;
		wcout << L"Variable3.IsEmpty() [" << Variable3.IsEmpty() << L"] !" << endl;

		PrintLineSeparator();

		// !!! Kedze EXPRESSION [move(Variable1)] je RVALUE, vola sa COPY verzia OPERATOR=.
		// !!!!! Zaroven MOVE OPERATOR= nastavi [Variable1] do EMPTY STATE.
		Variable2=move(Variable1);

		// !!!!! Kedze sa aplikovala MOVE SEMANTICS, [Variable1] bude EMPTY.
		wcout << L"Variable1.IsEmpty() [" << Variable1.IsEmpty() << L"] !" << endl;
		wcout << L"Variable2.IsEmpty() [" << Variable2.IsEmpty() << L"] !" << endl;

		PrintLineSeparator();

		CType5&&												Variable4={1,2,3};
		CType5													Variable5;

		PrintLineSeparator();

		// !!!!! Vola sa COPY OPERATOR= a NIE MOVE OPERATOR=, aj ked [Variable4] je TYPE [CType5&&]. Je to preto, lebo [Variable4] je VARIABLE, ktorej platnost je za hranicou EXPRESSION [Variable5=Variable4] a tym padom je povazovana za LVALUE.
		Variable5=Variable4;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CCopyAndMoveConstructor&& ReturnRValueReferenceType1(CCopyAndMoveConstructor& Value)
{
	wcout << L"FUNCTION CCopyAndMoveConstructor&& ReturnRValueReferenceType1(CCopyAndMoveConstructor& Value) CALLED !" << endl;

	return((CCopyAndMoveConstructor&&) Value);
}
//-------------------------------------------------------------------------------------------------------
CCopyAndMoveConstructor&& ReturnRValueReferenceType2(CCopyAndMoveConstructor&& Value)
{
	wcout << L"FUNCTION CCopyAndMoveConstructor&& ReturnRValueReferenceType2(CCopyAndMoveConstructor&& Value) CALLED !" << endl;

	return((CCopyAndMoveConstructor&&) Value);
}
//-------------------------------------------------------------------------------------------------------
CCopyAndMoveConstructor ReturnRValueReferenceType3(void)
{
	wcout << L"FUNCTION CCopyAndMoveConstructor ReturnRValueReferenceType3(void) CALLED !" << endl;

	CCopyAndMoveConstructor										Value={1,2,3};

	wcout << L"VARIABLE Value CONSTRUCTED !" << endl;

	// !!! Vola sa MOVE CONSTRUCTOR.
	return(Value);
}
//-------------------------------------------------------------------------------------------------------
void TestReturnValues(void)
{
	PrintLineSeparator();

	{
		CCopyAndMoveConstructor									Variable{1,2,3};

		PrintLineSeparator();

		// !!! Nevola sa COPY ani MOVE CONSTRUCTOR, pretoze RETURN VALUE je RVALUE REFERENCE.
		CCopyAndMoveConstructor&&								ReturnValue1=ReturnRValueReferenceType1(Variable);

		wcout << L"ReturnValue1.MSize [" << ReturnValue1.MSize << L"] !" << endl;

		PrintLineSeparator();

		// !!! Nevola sa COPY ani MOVE CONSTRUCTOR, pretoze RETURN VALUE je RVALUE REFERENCE.
		CCopyAndMoveConstructor&&								ReturnValue2=ReturnRValueReferenceType2({9,8,7});

		wcout << L"ReturnValue2.MSize [" << ReturnValue2.MSize << L"] !" << endl;

		PrintLineSeparator();

		// !!! Nevola sa COPY ani MOVE CONSTRUCTOR.
		CCopyAndMoveConstructor									ReturnValue3=ReturnRValueReferenceType3();

		wcout << L"ReturnValue3.MSize [" << ReturnValue3.MSize << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestCollection(void)
{
	PrintLineSeparator();

	vector<CItem>												Items;

	for(size_t Index=0;Index<20;Index++)
	{
		// Vola sa MOVE CONSTRUCTOR.
		// !!!!! Pri REALOKACII VECTOR BUFFER sa vola MOVE CONSTRUCTOR pre KAZDYM ITEM v COLLECTION. Kedze sa vola MOVE CONSTRUCTOR, NEDOCHADZA k casovo narocnemu vytvaraniu DEEP COPIES.
		Items.push_back({1,2,3});

		wcout << L"ITEM [" << Index << L"] ADDED to COLLECTION ! Items.capacity [" << Items.capacity() << L"] !" << endl;
	}

	wcout << L"Items.size [" << Items.size() << L"] !" << endl;
	wcout << L"CItem::MCounter [" << CItem::MCounter << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
CTypeWithMoveSemantics CreateType(wstring Text)
{
	return(CTypeWithMoveSemantics(Text));
}
//-------------------------------------------------------------------------------------------------------
void Process1(CTypeWithMoveSemantics)
{
	wcout << L"METHOD Process1() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
void Process2(wstring, CTypeWithMoveSemantics, wstring)
{
	wcout << L"METHOD Process2() CALLED !" << endl;
}
//-------------------------------------------------------------------------------------------------------
CTypeWithMoveSemantics Process3(CTypeWithMoveSemantics Value)
{
	wcout << L"METHOD Process3() CALLED !" << endl;

	// !!!!! VOLA sa MOVE CONTRUCTOR.
	return(Value);
}
//-------------------------------------------------------------------------------------------------------
void TestTypeWithMoveSemantics(void)
{
	PrintLineSeparator();

	// !!! NEVOLA sa ANI COPY ani MOVE CONSTRUCTOR. RETURN VALUE je PRIAMO prenesena do FUNCTION Process1() BEZ vykonania COPY ci MOVE SEMANTICS.
	// !!!!! Je to optimalizacia C++, ktory dokaze vyuzit PAMATOVE MIESTO na STACK urcene na ulozenie RETURN VALUE pouzit ako PARAMETER FUNCTION. V podstate COMPILER ani NEMUSI NIC ROBIT, lebo RETURN VALE je PRIAMO ULOZENA na STACK uz na IDENTICKEJ POZICII ako je pozicia PARAMETRA volanej FUNCTION.
	Process1(CreateType(L"TEST 1"));

	PrintLineSeparator();

	// !!! NEVOLA sa ANI COPY ani MOVE CONSTRUCTOR. RETURN VALUE je PRIAMO prenesena do FUNCTION Process1() BEZ vykonania COPY ci MOVE SEMANTICS.
	Process2(L"",CreateType(L"TEST 2"),L"");

	PrintLineSeparator();

	// !!!!! VOLA sa MOVE CONTRUCTOR pri vracani instancie CLASS [CTypeWithMoveSemantics] z FUNCTION Process3().
	Process3(CreateType(L"TEST 3"));

	PrintLineSeparator();

	// !!!!! VOLA sa MOVE CONTRUCTOR pri vracani instancie CLASS [CTypeWithMoveSemantics] z FUNCTION Process3().
	wcout << L"MESSAGE [" << Process3(CreateType(L"TEST 4")).GetMessage() << L"] !" << endl;

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestLValuesAndRValues1();
	//TestLValuesAndRValues2();
	//TestLValuesAndRValues3();
	//TestLValuesAndRValues4();
	//TestLValuesAndRValues5();
	//TestRValuesTypeWithNoCopyAndMoveConstructor1();
	//TestRValuesTypeWithNoCopyAndMoveConstructor2();
	//TestRValuesTypeWithCopyButNoMoveConstructor1();
	//TestRValuesTypeWithCopyButNoMoveConstructor2();
	//TestRValuesTypeWithCopyButNoMoveConstructor3();
	//TestRValuesTypeWithCopyButNoMoveConstructor4();
	//TestRValuesTypeWithCopyButNoMoveConstructor5();
	//TestRValuesTypeWithCopyButNoMoveConstructor6();
	//TestRValuesTypeWithMoveButNoCopyConstructor1();
	//TestRValuesTypeWithMoveButNoCopyConstructor2();
	//TestRValuesTypeWithMoveButNoCopyConstructor3();
	//TestRValuesTypeWithMoveButNoCopyConstructor4();
	//TestRValuesTypeWithMoveButNoCopyConstructor5();
	//TestRValuesTypeWithMoveButNoCopyConstructor6();
	//TestRValuesTypeWithCopyAndMoveConstructor1();
	//TestRValuesTypeWithCopyAndMoveConstructor2();
	//TestRValuesTypeWithCopyAndMoveConstructor3();
	//TestRValuesTypeWithCopyAndMoveConstructor4();
	//TestRValuesTypeWithCopyAndMoveConstructor5();
	//TestRValuesTypeWithCopyAndMoveConstructor6();
	//TestRValuesOverloading1();
	//TestRValuesOverloading2();
	//TestOperatorAssignment();
	//TestReturnValues();
	//TestCollection();
	TestTypeWithMoveSemantics();

	ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------