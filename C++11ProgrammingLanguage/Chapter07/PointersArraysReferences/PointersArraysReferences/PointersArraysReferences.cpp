//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdarg>
#include "CString.h"
#include "MyDebug.h"
#include "CPointerToMembers.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#else
// IGNORUJE WARNING, ktory hadze GCC pri konverzii POINTERS na FUNCTIONS.
#pragma GCC diagnostic ignored "-Wcast-function-type"
#endif
//-----------------------------------------------------------------------------
template<typename TType, size_t SIZE>
void PrintArray(const std::wstring& Text, TType (&Array)[SIZE])
{
	wcout << Text;
	wcout << L" [";

	for(size_t Index=0;Index<SIZE;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Array[Index];
	}

	wcout << L"]";
	wcout << endl;
}
//-----------------------------------------------------------------------------
template<typename TType, size_t SIZE>
void PrintArrayFromPointer(const std::wstring& Text, TType* Array)
{
	wcout << Text;
	wcout << L" [";

	for(size_t Index=0;Index<SIZE;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Array[Index];
	}

	wcout << L"]";
	wcout << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AllocateValue1(int** Value)
{
	*Value=new int(300);
}
//-----------------------------------------------------------------------------
void AllocateValue2(int** Value)
{
	*Value=new int(400);
}
//-----------------------------------------------------------------------------
void TestPointersToVariables(void)
{
	PrintLineSeparator();

	int															Value1=100;
	int															Value2=200;

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	int*														PointerToVariable=&Value1;

	wcout << L"POINTER to VARIABLE [" << PointerToVariable << L"] has VALUE [" << *PointerToVariable << L"] !" << endl;

	PointerToVariable=&Value2;

	wcout << L"POINTER to VARIABLE [" << PointerToVariable << L"] has VALUE [" << *PointerToVariable << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! COMPILER hodi ERROR, pretoze CONVERSION na INY POINTER TYPE je NEBEZPECNA.
	//short*														ShortPointer=static_cast<short*>(PointerToVariable);

	// !!!!! COMPILER akceptuje tuto NEBEZPECNU CONVERSION, pretoze sa pouzil prikaz [reinterpret_cast<TYPE*>()].
	short*														ShortPointer=reinterpret_cast<short*>(PointerToVariable);

	wcout << L"POINTER to SHORT VARIABLE [" << ShortPointer << L"] has VALUE [" << *ShortPointer << L"] !" << endl;

	// !!!!! COMPILER hodi ERROR, pretoze CONVERSION na INY POINTER TYPE je NEBEZPECNA.
	//long*														LongPointer=static_cast<long*>(PointerToVariable);

	// !!!!! COMPILER akceptuje tuto NEBEZPECNU CONVERSION, pretoze sa pouzil prikaz [reinterpret_cast<TYPE*>()].
	long*														LongPointer=reinterpret_cast<long*>(PointerToVariable);

	wcout << L"POINTER to LONG VARIABLE [" << LongPointer << L"] has VALUE [" << *LongPointer << L"] !" << endl;

	PrintLineSeparator();

	int**														PointerToPointer=&PointerToVariable;

	wcout << L"POINTER to POINTER [" << PointerToPointer << L"]  POINTER to VARIABLE [" << *PointerToPointer << L"] has VALUE [" << **PointerToPointer << L"] !" << endl;

	AllocateValue1(PointerToPointer);

	wcout << L"POINTER to POINTER [" << PointerToPointer << L"]  POINTER to VARIABLE [" << *PointerToPointer << L"] has VALUE [" << **PointerToPointer << L"] !" << endl;

	delete(*PointerToPointer);

	AllocateValue2(PointerToPointer);

	wcout << L"POINTER to POINTER [" << PointerToPointer << L"]  POINTER to VARIABLE [" << *PointerToPointer << L"] has VALUE [" << **PointerToPointer << L"] !" << endl;

	delete(*PointerToPointer);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int Operation1(int Value1, int Value2)
{
	return(Value1+Value2);
}
//-----------------------------------------------------------------------------
int Operation2(int Value1, int Value2)
{
	return(Value1-Value2);
}
//-----------------------------------------------------------------------------
void ReturnPointerToFunction1(int (**PointerToFunction)(int,int))
{
	*PointerToFunction=&Operation1;
}
//-----------------------------------------------------------------------------
void ReturnPointerToFunction2(int (**PointerToFunction)(int,int))
{
	*PointerToFunction=&Operation2;
}
//-----------------------------------------------------------------------------
void TestPointersToFunctions1(void)
{
	PrintLineSeparator();

	int															Value1=100;
	int															Value2=200;

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	int															(*PointerToFunction)(int,int)=&Operation1;

	wcout << L"POINTER to FUNCTION [" << (*PointerToFunction)(Value1,Value2) << L"] !" << endl;

	PointerToFunction=&Operation2;

	wcout << L"POINTER to FUNCTION [" << (*PointerToFunction)(Value1,Value2) << L"] !" << endl;

	PrintLineSeparator();

	ReturnPointerToFunction1(&PointerToFunction);

	wcout << L"POINTER to POINTER to FUNCTION [" << (*PointerToFunction)(Value1,Value2) << L"] !" << endl;

	ReturnPointerToFunction2(&PointerToFunction);

	wcout << L"POINTER to POINTER to FUNCTION [" << (*PointerToFunction)(Value1,Value2) << L"] !" << endl;

	int															(**PointerToPointerToFunction)(int,int)=&PointerToFunction;

	wcout << L"POINTER to POINTER to FUNCTION [" << (**PointerToPointerToFunction)(Value1,Value2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
size_t SomeFunction1(wstring Parameter)
{
	wcout << L"FUNCTION SomeFunction1(WSTRING) CALLED with PARAMETER [" << Parameter << L"] !" << endl;

	return(Parameter.size());
}
//-----------------------------------------------------------------------------
size_t SomeFunction2(wstring Parameter)
{
	wcout << L"FUNCTION SomeFunction2(WSTRING) CALLED with PARAMETER [" << Parameter << L"] !" << endl;

	return(Parameter.size());
}
//-----------------------------------------------------------------------------
void SomeFunction3(wstring Parameter)
{
	wcout << L"FUNCTION SomeFunction3(WSTRING) CALLED with PARAMETER [" << Parameter << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TwoParametersOverloaded(int Value1, int Value2)
{
	wcout << L"FUNCTION TwoParametersOverloaded(INT,INT) CALLED with PARAMETER 1 [" << Value1 << L"] and PARAMETER 2 [" << Value2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TwoParametersOverloaded(int Value1, long Value2)
{
	wcout << L"FUNCTION TwoParametersOverloaded(INT,LONG) CALLED with PARAMETER 1 [" << Value1 << L"] and PARAMETER 2 [" << Value2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void ReinterpretCast(char Value1, char Value2)
{
	wcout << L"FUNCTION ReinterpretCast(CHAR,CHAR) CALLED with PARAMETER 1 [" << Value1 << L"] and PARAMETER 2 [" << Value2 << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void ExceptFunction(int Value)
{
	try
	{
		wcout << L"FUNCTION ExceptFunction(INT) CALLED with PARAMETER [" << Value << L"] !" << endl;
	}
	catch(...)
	{
	}
}
//-----------------------------------------------------------------------------
void NoExceptFunction(int Value) noexcept
{
	try
	{
		wcout << L"FUNCTION NoExceptFunction(INT) CALLED with PARAMETER [" << Value << L"] !" << endl;
	}
	catch(...)
	{
	}
}
//-----------------------------------------------------------------------------
void TestPointersToFunctions2(void)
{
	PrintLineSeparator();

	// Definuje sa POINTER na FUNCTION.
	size_t														(*PointerToFunction1)(wstring)=nullptr;

	// !!! Do POINTER na FUNCTION sa prideli ADDRESS na FUNCTION.
	PointerToFunction1=&SomeFunction1;

	// !!! FUNCTION sa vola pomocou POINTER na FUNCTION.
	size_t														Length1=(*PointerToFunction1)(L"ABCDEF");

	wcout << L"LENGTH 1 [" << Length1 << L"] !" << endl;

	PrintLineSeparator();

	size_t														(*PointerToFunction2)(wstring)=nullptr;

	// !!! Do POINTER na FUNCTION sa prideli ADDRESS na FUNCTION.
	// !!!!! NEPOUZIVA sa OPERATOR&, pretoze C++ to NEVYZADUJE.
	PointerToFunction2=SomeFunction2;

	// !!! FUNCTION sa vola pomocou POINTER na FUNCTION.
	// !!!!! NEPOUZIVA sa OPERATOR*, pretoze to C++ NEVYZADUJE.
	size_t														Length2=PointerToFunction2(L"Delta MK3");

	wcout << L"LENGTH 2 [" << Length2 << L"] !" << endl;

	/*
	// !!!!! COMPILER hodi ERROR, pretoze FUNCTION SomeFunction3() ma RETURN VALUE TYPE VOID, zatial co POINTER na FUNCTION 'PointerToFunction2' ocakava RETURN VALUE TYPE [size_t].
	PointerToFunction2=SomeFunction3;

	size_t														Length3=PointerToFunction2(L"Delta MK3");

	wcout << L"LENGTH 3 [" << Length3 << L"] !" << endl;
	*/

	PrintLineSeparator();

	// !!! Priradi sa FUNCTION TwoParametersOverloaded(INT,INT).
	void														(*PointerToFunction3)(int,int)=&TwoParametersOverloaded;

	PointerToFunction3(100,200);

	// !!! Priradi sa FUNCTION TwoParametersOverloaded(INT,LONG).
	void														(*PointerToFunction4)(int,long)=&TwoParametersOverloaded;

	PointerToFunction4(100,200);

	/*
	// !!! COMPILER hodi ERROR, pretoze FUNCTION TwoParametersOverloaded(INT,SHORT) NEEXISTUJE.
	void														(*PointerToFunction5)(int,short)=&TwoParametersOverloaded;

	PointerToFunction5(100,200);
	*/

	PrintLineSeparator();

	using														NormalFunction=void (*)(char,char);
	using														RCFunction=void (*)(int,int);

	NormalFunction												PointerToFunctionRC1=&ReinterpretCast;

	PointerToFunctionRC1('A','Z');

	// !!!!! EXTREMNE NEBEZPECNA CONVERSION na INY TYPE POINTER TO FUNCTION.
	RCFunction													PointerToFunctionTemp=reinterpret_cast<RCFunction>(PointerToFunctionRC1);

	// !!!!! Tento CODE moze sposobit PROGRAM CRASH, pretoze STACK NEZODPOVEDA tomu co FUNCTION OCAKAVA.
	//PointerToFunctionTemp(100,200);

	// !!!!! Spatna CONVERSION na povodny TYPE POINTER to FUNCTION.
	NormalFunction												PointerToFunctionRC2=reinterpret_cast<NormalFunction>(PointerToFunctionTemp);

	// !!!!! FUNCTION sa NORMALNE zavola, pretoze FUNCTION PROTOTYPE a POINTER na FUNCTION PROTOTYPE su ZHODNE.
	PointerToFunctionRC2('B','Y');

	PrintLineSeparator();

	void														(*ExceptPointerToFunction)(int);
	void														(*NoExceptPointerToFunction)(int) noexcept;

	ExceptPointerToFunction=&ExceptFunction;

	ExceptPointerToFunction(100);

	// !!!!! C++ UMOZNUJE do POINTER na FUNCTION, ktoreho PROTOTYPE NEOBSAHUJE KEYWORD [noexcept] priradit FUNCTION, ktorej PROTOTYPE OBSAHUJE KEYWORD [noexcept].
	// !!!!! GCC hodi WARNING.
	ExceptPointerToFunction=&NoExceptFunction;

	ExceptPointerToFunction(100);

	// !!!!! C++ NEUMOZNUJE do POINTER na FUNCTION, ktoreho PROTOTYPE OBSAHUJE KEYWORD [noexcept] priradit FUNCTION, ktorej PROTOTYPE NEOBSAHUJE KEYWORD [noexcept].
	/*
	NoExceptPointerToFunction=&ExceptFunction;

	NoExceptPointerToFunction(100);
	*/

	NoExceptPointerToFunction=&NoExceptFunction;

	NoExceptPointerToFunction(100);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointerToMemberVariables(void)
{
	PrintLineSeparator();

	CPointerToMembers											Value1(L"Timmy",L"Anderson",12,22);
	CPointerToMembers											TempValue(L"Jenny",L"Thompson",13,23);
	CPointerToMembers&											Value2=TempValue;
	CPointerToMembers*											PointerToValue1=&Value1;
	CPointerToMembers*											PointerToValue2=&Value2;

	// !!! Pristup k MEMBERS sa realizuje pomocou OPERATOR.() ak je VARIABLE definovana BY-VALUE.
	wcout << L"VALUE 1 - STRING VALUE 1 [" << Value1.GetStringValue1() << L"] STRING VALUE 2 [" << Value1.GetStringValue2() << L"] INT VALUE 1 [" << Value1.GetIntValue1() << L"] INT VALUE 2 [" << Value1.GetIntValue2() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pristup k MEMBERS sa realizuje pomocou OPERATOR.() ak je VARIABLE definovana BY-VALUE.
	wcout << L"VALUE 2 - STRING VALUE 1 [" << Value2.GetStringValue1() << L"] STRING VALUE 2 [" << Value2.GetStringValue2() << L"] INT VALUE 1 [" << Value2.GetIntValue1() << L"] INT VALUE 2 [" << Value2.GetIntValue2() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pristup k MEMBERS sa realizuje pomocou OPERATOR->() ak je VARIABLE definovana BY-VALUE.
	wcout << L"POINTER VALUE 1 - STRING VALUE 1 [" << PointerToValue1->GetStringValue1() << L"] STRING VALUE 2 [" << PointerToValue1->GetStringValue2() << L"] INT VALUE 1 [" << PointerToValue1->GetIntValue1() << L"] INT VALUE 2 [" << PointerToValue1->GetIntValue2() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pristup k MEMBERS sa realizuje pomocou OPERATOR->() ak je VARIABLE definovana BY-VALUE.
	wcout << L"POINTER VALUE 2 - STRING VALUE 1 [" << PointerToValue2->GetStringValue1() << L"] STRING VALUE 2 [" << PointerToValue2->GetStringValue2() << L"] INT VALUE 1 [" << PointerToValue2->GetIntValue1() << L"] INT VALUE 2 [" << PointerToValue2->GetIntValue2() << L"] !" << endl;

	PrintLineSeparator();

	wstring														CPointerToMembers::*PointerToString;
	int															CPointerToMembers::*PointerToInt;

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	PointerToString=&CPointerToMembers::MStringValue1;

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	PointerToInt=&CPointerToMembers::MIntValue1;

	wcout << L"Value1.*PointerToString [" << (Value1.*PointerToString) << L"] !" << endl;
	wcout << L"Value1.*PointerToInt [" << (Value1.*PointerToInt) << L"] !" << endl;
	wcout << L"Value2.*PointerToString [" << (Value2.*PointerToString) << L"] !" << endl;
	wcout << L"Value2.*PointerToInt [" << (Value2.*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"PointerToValue1->*PointerToString [" << (PointerToValue1->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue1->*PointerToInt [" << (PointerToValue1->*PointerToInt) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToString [" << (PointerToValue2->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToInt [" << (PointerToValue2->*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	PointerToString=&CPointerToMembers::MStringValue2;

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	PointerToInt=&CPointerToMembers::MIntValue2;

	wcout << L"Value1.*PointerToString [" << (Value1.*PointerToString) << L"] !" << endl;
	wcout << L"Value1.*PointerToInt [" << (Value1.*PointerToInt) << L"] !" << endl;
	wcout << L"Value2.*PointerToString [" << (Value2.*PointerToString) << L"] !" << endl;
	wcout << L"Value2.*PointerToInt [" << (Value2.*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"PointerToValue1->*PointerToString [" << (PointerToValue1->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue1->*PointerToInt [" << (PointerToValue1->*PointerToInt) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToString [" << (PointerToValue2->*PointerToString) << L"] !" << endl;
	wcout << L"PointerToValue2->*PointerToInt [" << (PointerToValue2->*PointerToInt) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointerToMemberFunctions(void)
{
	PrintLineSeparator();

	CPointerToMembers											Value1(L"Timmy",L"Anderson",12,22);
	CPointerToMembers											TempValue(L"Jenny",L"Thompson",13,23);
	CPointerToMembers&											Value2=TempValue;
	CPointerToMembers*											PointerToValue1=&Value1;
	CPointerToMembers*											PointerToValue2=&Value2;

	const wstring&												(CPointerToMembers::*MethodGettingString)(void) const noexcept;
	int															(CPointerToMembers::*MethodGettingInt)(void) const noexcept;

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	MethodGettingString=&CPointerToMembers::GetStringValue1;

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	MethodGettingInt=&CPointerToMembers::GetIntValue1;

	wcout << L"Value1.*MethodGettingString() [" << ((Value1.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value1.*MethodGettingInt() [" << ((Value1.*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingString() [" << ((Value2.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingInt() [" << ((Value2.*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"PointerToValue1->*MethodGettingString() [" << ((PointerToValue1->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue1->*MethodGettingInt() [" << ((PointerToValue1->*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingString() [" << ((PointerToValue2->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingInt() [" << ((PointerToValue2->*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	MethodGettingString=&CPointerToMembers::GetStringValue2;

	// !!! Pristup k MEMBERS, ktore nie su viazane na konkretny OBJECT sa realizuje pomocou OPERATOR::.
	MethodGettingInt=&CPointerToMembers::GetIntValue2;

	wcout << L"Value1.*MethodGettingString() [" << ((Value1.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value1.*MethodGettingInt() [" << ((Value1.*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingString() [" << ((Value2.*MethodGettingString)()) << L"] !" << endl;
	wcout << L"Value2.*MethodGettingInt() [" << ((Value2.*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"PointerToValue1->*MethodGettingString() [" << ((PointerToValue1->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue1->*MethodGettingInt() [" << ((PointerToValue1->*MethodGettingInt)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingString() [" << ((PointerToValue2->*MethodGettingString)()) << L"] !" << endl;
	wcout << L"PointerToValue2->*MethodGettingInt() [" << ((PointerToValue2->*MethodGettingInt)()) << L"] !" << endl;

	PrintLineSeparator();

	// !!! POINTER na OPERATOR je identicky ako POINTER na FUNCTION.
	int															(CPointerToMembers::*OperatorPlus)(int) const noexcept;

	OperatorPlus=&CPointerToMembers::operator+;

	wcout << L"Value1.*OperatorPlus(500) [" << ((Value1.*OperatorPlus)(500)) << L"] !" << endl;
	wcout << L"Value2.*OperatorPlus(500) [" << ((Value2.*OperatorPlus)(500)) << L"] !" << endl;
	wcout << L"PointerToValue1->*OperatorPlus(500) [" << ((PointerToValue1->*OperatorPlus)(500)) << L"] !" << endl;
	wcout << L"PointerToValue2->*OperatorPlus(500) [" << ((PointerToValue2->*OperatorPlus)(500)) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointerToVoid(void)
{
	PrintLineSeparator();

	int															Value=50000;

	wcout << L"VALUE [" << Value << L"] !" << endl;

	void*														PointerToVoidVariable=&Value;

	wcout << L"POINTER to VOID VARIABLE [" << PointerToVoidVariable << L"] !" << endl;

	// !!! COMPILER hodi ERROR, pretoze OPERATOR* NEMOZE byt aplikovany na POINTER na VOID.
	//wcout << L"DEREFERENCING POINTER to VOID VARIABLE [" << *PointerToVoidVariable << L"] !" << endl;

	// !!! Konverzia z POINTER na VOID na iny POINTER je nutna cez volanie prikazu [static_cast<TYPE*>(EXPRESSION)].
	int*														PointerToIntVariable=static_cast<int*>(PointerToVoidVariable);

	wcout << L"POINTER to INT VARIABLE [" << PointerToIntVariable << L"] has VALUE [" << *PointerToIntVariable << L"] !" << endl;

	// !!! Konverzia z POINTER na VOID na iny POINTER je nutna cez volanie prikazu [static_cast<TYPE*>(EXPRESSION)].
	// !!!!! Tato konverzia je NEBEZPECNA, pretoze sa pri nej meni POINTER TYPE z INT na SHORT.
	short*														PointerToShortVariable=static_cast<short*>(PointerToVoidVariable);

	wcout << L"POINTER to SHORT VARIABLE [" << PointerToShortVariable << L"] has VALUE [" << *PointerToShortVariable << L"] !" << endl;

	// !!! Konverzia z POINTER na VOID na iny POINTER je nutna cez volanie prikazu [static_cast<TYPE*>(EXPRESSION)].
	// !!!!! Tato konverzia je NEBEZPECNA, pretoze sa pri nej meni POINTER TYPE z INT na LONG.
	long*														PointerToLongVariable=static_cast<long*>(PointerToVoidVariable);

	wcout << L"POINTER to LONG VARIABLE [" << PointerToLongVariable << L"] has VALUE [" << *PointerToLongVariable << L"] !" << endl;

#ifdef _MSC_VER
	// !!!!! POINTER na FUNCTION NIE JE MOZNE IMPLICITNE konvertovat na POINTER na VOID. No VC++ takuto konverziu umoznuje. GCC hodi ERROR.

	PrintLineSeparator();

	int															(*PointerToFunction1)(int,int)=&Operation1;

	wcout << L"POINTER to FUNCTION 1 [" << PointerToFunction1 << L"] !" << endl;
	wcout << L"POINTER to FUNCTION 1 CALL [" << (*PointerToFunction1)(100,200) << L"] !" << endl;

	void*														PointerFunctionVoid=PointerToFunction1;

	wcout << L"POINTER to FUNCTION VOID [" << PointerFunctionVoid << L"] !" << endl;

	int															(*PointerToFunction2)(int,int)=static_cast<int (*)(int,int)>(PointerFunctionVoid);

	wcout << L"POINTER to FUNCTION 2 [" << PointerToFunction2 << L"] !" << endl;
	wcout << L"POINTER to FUNCTION 2 CALL [" << (*PointerToFunction2)(100,200) << L"] !" << endl;
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrays(void)
{
	PrintLineSeparator();

	int															Array1[5]{10,20,30,40,50};

	PrintArray(L"ARRAY 1",Array1);

	Array1[2]++;

	PrintArray(L"ARRAY 1",Array1);

	wstring														Array2[]{L"AAA",L"BBBB",L"CCCCC",L"DDDDDD"};

	PrintArray(L"ARRAY 2",Array2);

	// !!! ARRAYS su IMPLICITNE konvertovatelne na POINTER na ARRAYS.
	wstring*													PointerToArray2=Array2;

	{
		wcout << L"POINTER to ARRAY 2 [";

		for(size_t Index=0;Index<(sizeof(Array2)/sizeof(Array2[0]));Index++)
		{
			if (Index>0)
			{
				wcout << L" ";
			}

			wcout << PointerToArray2[Index];
		}

		wcout << L"]";
		wcout << endl;
	}

	wchar_t														Array3[]{L"Timmy Anderson"};

	PrintArray(L"ARRAY 3",Array3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
const wchar_t* ReturnStringLiteral(void)
{
	// !!! Pretoze STRING LITERALS su alokovane STATICKY, je ich mozne vracat ako RETURN VALUES.
	return(L"Timmy Anderson");
}
//-----------------------------------------------------------------------------
void TestStringLiterals(void)
{
	PrintLineSeparator();

	// CODE vytvori ARRAY, ktore naplni CHARACTERS zo STRING LITERAL 'Timmy'.
	// !!! VARIABLE 'Array' vsak NIE JE STRING LITERAL a preto je ju mozne MODIFIKOVAT.
	wchar_t														Array[]{L"Timmy"};

	wcout << L"ARRAY [" << Array << L"] !" << endl;

	// !!! VARIABLE 'Array' vsak NIE JE STRING LITERAL a preto je ju mozne MODIFIKOVAT.
	Array[2]=L'M';

	wcout << L"ARRAY [" << Array << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pocet CHARACTERS je 6, pretoze 6. CHARACTER je NULL CHARACTER.
	wcout << L"LITERAL SIZE [" << (sizeof(L"Timmy")/sizeof(wchar_t)) << L"] !" << endl;
	
	// !!! Pocet CHARACTERS je 15.
	wcout << L"LITERAL SIZE [" << (sizeof(L"Timmy Anderson")/sizeof(wchar_t)) << L"] !" << endl;

	// !!! Pocet CHARACTERS je 15, aj napriek tomu, ze STRING LITERAL vo vnutri STRING LITERAL obsahuje NULL CHARACTER.
	wcout << L"LITERAL SIZE [" << (sizeof(L"Timmy\0Anderson")/sizeof(wchar_t)) << L"] !" << endl;

	PrintLineSeparator();

	const wchar_t*												ConstPointer=L"Timmy";

	wcout << L"CONST POINTER [" << ConstPointer << L"] !" << endl;

	/*
	// !!! COMPILER hodi ERROR, pretoze STRING LITERALS NIE JE mozne priradit do NON CONST POINTERS.
	wchar_t*													NonConstPointer=L"Timmy";

	wcout << L"NON-CONST POINTER [" << NonConstPointer << L"] !" << endl;
	*/

	PrintLineSeparator();

	wcout << L"STRING LITERAL from FUNCTION [" << ReturnStringLiteral() << L"] !" << endl;

	PrintLineSeparator();

	// STRING LITERALS, ktore nasleduju za sebou a su oddelene iba WHITE SPACES, COMPILER ZLUCI uz v COMPILE TIME.
	const wchar_t*												MultiLineStringLiteral=	L"Timmy"
																						L" "
																						L"Anderson";

	wcout << L"MULTILNE STRING LITERAL [" << MultiLineStringLiteral << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRawStringLiterals(void)
{
	PrintLineSeparator();

    const wchar_t*													RawStringLiteral1=LR"(Timmy\n\n\nAnderson)";

	wcout << L"RAW STRING LITERAL 1 [" << RawStringLiteral1 << L"] !" << endl;

	// !!! RAW STRING standardne NEMOZE OBSAHOVAT CHARACTER SEQUENCE [)"].
	// !!!!! Na to, aby CHARACTER SEQUENCE [)"] mohla byt v RAW STRING obsiahnuta, je NUTNE definovat CUSTOM DELIMITER PAIR. V tomto pripade je to SEQUENCE [ABCD].
	// !!!!! CUSTOM DELIMITER PAIR musi byt ZHODNY na ZACIATKU a KONCI RAW STRING LITERAL.
	// !!!!! Prirodzene, nasledujuci TEXT NESMIE obsahovat vo svojom tele CHARACTER SEQUENCE [)ABCD"], pretoze ta indikuje KONIEC RAW STRING LITERAL.
    const wchar_t*													RawStringLiteral2=LR"ABCD(SPECIAL CHARACTER [)"])ABCD";

	wcout << L"RAW STRING LITERAL 2 [" << RawStringLiteral2 << L"] !" << endl;

	// !!! RAW STRING moze obsahovat aj NEW LINES priamo v definicii STRING.
    const wchar_t*													RawStringLiteral3=LR"(Line1

	Line 2

	Line 3

	END !!!)";

	wcout << L"RAW STRING LITERAL 3 [" << RawStringLiteral3 << L"] !" << endl;

    const wchar_t*													RawStringLiteral4=LR"(C:\Dir1\Dir2\File.txt)";

	wcout << L"RAW STRING LITERAL 4 [" << RawStringLiteral4 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLargeStringLiterals(void)
{
	PrintLineSeparator();

    char														StringChar[]="Timmy Anderson";

	wcout << L"STRING CHAR SIZE [" << sizeof(StringChar) << L"] !" << endl;

    char														RawStringChar[]=R"(Timmy\tAnderson)";

	wcout << L"RAW STRING CHAR SIZE [" << sizeof(RawStringChar) << L"] !" << endl;

	PrintLineSeparator();

    wchar_t														StringWideChar[]=L"Timmy Anderson";

	wcout << L"STRING WIDE CHAR SIZE [" << sizeof(StringWideChar) << L"] !" << endl;

    wchar_t														RawStringWideChar[]=LR"(Timmy\tAnderson)";

	wcout << L"RAW STRING WIDE CHAR SIZE [" << sizeof(RawStringWideChar) << L"] !" << endl;

	PrintLineSeparator();

	// !!! STRING je vyjadreny v UTF-8.
    char														StringUTF8[]=u8"Timmy Anderson \u0430";

	wcout << L"STRING UTF8 SIZE [" << sizeof(StringUTF8) << L"] !" << endl;

	// !!! STRING je vyjadreny v UTF-8.
    char														RawStringUTF8[]=u8R"(Timmy\tAnderson \u0430)";

	wcout << L"RAW STRING UTF8 SIZE [" << sizeof(RawStringUTF8) << L"] !" << endl;

	PrintLineSeparator();

	// !!! STRING je vyjadreny v UTF-16.
    char16_t													StringUTF16[]=u"Timmy Anderson \u0430";

	wcout << L"STRING UTF16 SIZE [" << sizeof(StringUTF16) << L"] !" << endl;

	// !!! STRING je vyjadreny v UTF-16.
    char16_t													RawStringUTF16[]=uR"(Timmy\tAnderson \u0430)";

	wcout << L"RAW STRING UTF16 SIZE [" << sizeof(RawStringUTF16) << L"] !" << endl;

	PrintLineSeparator();

	// !!! STRING je vyjadreny v UTF-32.
    char32_t													StringUTF32[]=U"Timmy Anderson \u0430";

	wcout << L"STRING UTF32 SIZE [" << sizeof(StringUTF32) << L"] !" << endl;

	// !!! STRING je vyjadreny v UTF-32.
    char32_t													RawStringUTF32[]=UR"(Timmy\tAnderson \u0430)";

	wcout << L"RAW STRING UTF32 SIZE [" << sizeof(RawStringUTF32) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArraysToPointers(void)
{
	PrintLineSeparator();

	int															Array[]{100,200,300,400};

	PrintArray(L"Array",Array);

	// !!! ARRAYS su IMPLICITNE KONVERTOVATELNE na POINTERS na 1. ITEM.
	int*														ArrayPointer1=Array;

	PrintArrayFromPointer<int,sizeof(Array)/sizeof(Array[0])>(L"ArrayPointer1",ArrayPointer1);

	int*														ArrayPointer2=&Array[0];

	PrintArrayFromPointer<int,sizeof(Array)/sizeof(Array[0])>(L"ArrayPointer2",ArrayPointer2);

	int*														ArrayPointer3=&Array[2];

	PrintArrayFromPointer<int,2>(L"ArrayPointer3",ArrayPointer3);

	PrintLineSeparator();

	// !!! C++ UMOZNUJE ziskat POINTER na 1 ITEM za POSLEDNYM ITEM v ARRAY. Tento POINTER vsak NESMIE BYT DEREFERENCED.
	int*														ArrayPointer4=&Array[4];

	wcout << L"POINTER DIFFERENCE [" << (ArrayPointer4-Array) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"PRINT ARRAY by POINTER to ARRAY using POINTER ARITHMETICS [";

	for(int* Pointer=Array;Pointer!=&Array[4];Pointer++)
	{
		if (Pointer!=Array)
		{
			wcout << L" ";
		}

		wcout << *Pointer;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"PRINT ARRAY by POINTER to ARRAY using POINTER ARITHMETICS REVERSE [";

	for(int* Pointer=&Array[4];;)
	{
		if (Pointer!=&Array[4])
		{
			wcout << L" ";
		}

		Pointer--;

		wcout << *Pointer;

		if (Pointer==Array)
		{
			break;
		}
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"PRINT ARRAY by POINTER to ARRAY using OPERATOR[] [";

	int*														Pointer1=Array;
	int*														Pointer2=Array;

	for(;Pointer1!=&Array[4];Pointer1++)
	{
		size_t													Index=(Pointer1-Pointer2);

		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Pointer2[Index];
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ARRAY[2] [" << (Array[2]) << L"] !" << endl;

	wcout << L"ARRAY+2 [" << (*(Array+2)) << L"] !" << endl;

	wcout << L"2+ARRAY [" << (*(2+Array)) << L"] !" << endl;

	// !!!!! C++ umoznuje aj takuto ZVRATENU SYNTAX, ktora sa interpretuje ako (*(2+Array)).
	wcout << L"2[ARRAY] [" << (2[Array]) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void Print2DArray(int Array[][5], size_t Size)
{
	wcout << L"ARRAY 2 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<Size;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<5;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" ";
			}

			wcout << L"[" << Array[Index1][Index2] << L"]";
		}

		wcout << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void Print3DArray1(int Array[][4][5], size_t Size)
{
	wcout << L"ARRAY 3 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<Size;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<4;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" - ";
			}

			for(size_t Index3=0;Index3<5;Index3++)
			{
				if (Index3>0)
				{
					wcout << L" ";
				}

				wcout << L"[" << Array[Index1][Index2][Index3] << L"]";
			}
		}

		wcout << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void Print3DArray2(int Array[3][4][5])
{
	wcout << L"ARRAY 3 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<3;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<4;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" - ";
			}

			for(size_t Index3=0;Index3<5;Index3++)
			{
				if (Index3>0)
				{
					wcout << L" ";
				}

				wcout << L"[" << Array[Index1][Index2][Index3] << L"]";
			}
		}

		wcout << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void Print3DArray3(int* Array, size_t Size1, size_t Size2, size_t Size3)
{
	wcout << L"ARRAY 3 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<Size1;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<Size2;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" - ";
			}

			for(size_t Index3=0;Index3<Size3;Index3++)
			{
				if (Index3>0)
				{
					wcout << L" ";
				}

				wcout << L"[" << *(Array+(Index1*(Size2*Size3))+(Index2*Size3)+Index3) << L"]";
			}
		}

		wcout << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestMultidimensionalArrays(void)
{
	PrintLineSeparator();

	int															Array2Dimensions[3][5]={{11,12,13,14,15},{21,22,23,24,25},{31,32,33,34,35}};

	wcout << L"ARRAY 2 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<3;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<5;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" ";
			}

			wcout << L"[" << Array2Dimensions[Index1][Index2] << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	int															Array3Dimensions[3][4][5]={{{111,112,113,114,115},{121,122,123,124,125},{131,132,133,134,135},{141,142,143,144,145}},{{211,212,213,214,215},{221,222,223,224,225},{231,232,233,234,235},{241,242,243,244,245}},{{311,312,313,314,315},{321,322,323,324,325},{331,332,333,334,335},{341,342,343,344,345}}};

	wcout << L"ARRAY 3 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<3;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<4;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" - ";
			}

			for(size_t Index3=0;Index3<5;Index3++)
			{
				if (Index3>0)
				{
					wcout << L" ";
				}

				wcout << L"[" << Array3Dimensions[Index1][Index2][Index3] << L"]";
			}
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	Print2DArray(Array2Dimensions,3);

	PrintLineSeparator();

	Print3DArray1(Array3Dimensions,3);

	PrintLineSeparator();

	Print3DArray2(Array3Dimensions);

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze NEDOKAZE IMPLICITNE konvertovat TYPE [int[3][4][5]] na TYPE [int*].
	//Print3DArray3(Array3Dimensions,3,4,5);

	// !!! Tento CODE uz C++ AKCEPTUJE.
	Print3DArray3(&Array3Dimensions[0][0][0],3,4,5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ChangeArray(int Array[5])
{
	for(size_t Index=0;Index<5;Index++)
	{
		Array[Index]*=2;
	}
}
//-----------------------------------------------------------------------------
void ChangeArray(int Array[3][5])
{
	for(size_t Index1=0;Index1<3;Index1++)
	{
		for(size_t Index2=0;Index2<5;Index2++)
		{
			Array[Index1][Index2]*=2;
		}
	}
}
//-----------------------------------------------------------------------------
void TestPassingArrays(void)
{
	PrintLineSeparator();

	int															Array1Dimension[5]={100,200,300,400,500};

	PrintArray(L"Array1Dimension",Array1Dimension);

	ChangeArray(Array1Dimension);

	PrintLineSeparator();

	PrintArray(L"Array1Dimension",Array1Dimension);

	PrintLineSeparator();

	int															Array2Dimensions[3][5]={{11,12,13,14,15},{21,22,23,24,25},{31,32,33,34,35}};

	wcout << L"ARRAY 2 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<3;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<5;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" ";
			}

			wcout << L"[" << Array2Dimensions[Index1][Index2] << L"]";
		}

		wcout << L"] !" << endl;
	}

	ChangeArray(Array2Dimensions);

	PrintLineSeparator();

	wcout << L"ARRAY 2 DIMENSIONS:\n";

	for(size_t Index1=0;Index1<3;Index1++)
	{
		wcout << L"[";

		for(size_t Index2=0;Index2<5;Index2++)
		{
			if (Index2>0)
			{
				wcout << L" ";
			}

			wcout << L"[" << Array2Dimensions[Index1][Index2] << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstPointers(void)
{
	PrintLineSeparator();

	int															Value1=100;
	int															Value2=200;

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	const int*													PointerToConst=&Value1;

	wcout << L"POINTER to CONST [" << PointerToConst << L"] POINTS to VALUE [" << *PointerToConst << L"] !" << endl;

	// !!! COMPILER hodi ERROR, pretoze POINTER na CONST NEMOZE modifikovat VALUE na ktoru referuje.
	//*PointerToConst=300;

	// !!! COMPILER AKCPETUJE CODE, pretoze POINTER na CONST JE mozne PRESMEROVAT na INU VARIABLE.
	PointerToConst=&Value2;

	wcout << L"POINTER to CONST [" << PointerToConst << L"] POINTS to VALUE [" << *PointerToConst << L"] !" << endl;

	PrintLineSeparator();

	int* const													ConstPointer=&Value1;

	wcout << L"CONST POINTER [" << ConstPointer << L"] POINTS to VALUE [" << *ConstPointer << L"] !" << endl;

	// !!! COMPILER AKCPETUJE CODE, pretoze CONST POINTER MOZE modifikovat VALUE na ktoru referuje.
	*ConstPointer=300;

	// !!! COMPILER hodi ERROR, pretoze CONST POINTER NEMOZE byt presmerovany na INU VARIABLE.
	//ConstPointer=&Value2;

	wcout << L"CONST POINTER [" << ConstPointer << L"] POINTS to VALUE [" << *ConstPointer << L"] !" << endl;

	PrintLineSeparator();

	const int* const											ConstPointerToConst=&Value1;

	wcout << L"CONST POINTER to CONST [" << ConstPointerToConst << L"] POINTS to VALUE [" << *ConstPointerToConst << L"] !" << endl;

	// !!! COMPILER hodi ERROR, pretoze CONST POINTER na CONST NEMOZE modifikovat VALUE na ktoru referuje.
	//*ConstPointerToConst=400;

	// !!! COMPILER hodi ERROR, pretoze CONST POINTER na CONST NEMOZE byt presmerovany na INU VARIABLE.
	//ConstPointerToConst=&Value2;

	wcout << L"CONST POINTER to CONST [" << ConstPointerToConst << L"] POINTS to VALUE [" << *ConstPointerToConst << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ModifyValue(int& Value)
{
	Value+=33;
}
//-----------------------------------------------------------------------------
void TestLValueReferences(void)
{
	PrintLineSeparator();

	int															Value1=100;
	int															Value2=200;

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	// !!! INICIALIZACIA REFERENCE na VARIABLE 'Value1'.
	// !!!!! REFERENCES MUSIA byt VZDY INICIALIZOVANE.
	int&														Reference=Value1;

	wcout << L"REFERENCE [" << Reference << L"] !" << endl;

	// !!! Meni sa hodnota REFERENCE aj POVODNEJ VARIABLE na ktoru REFERENCE ODKAZUJE.
	Reference+=5;

	wcout << L"REFERENCE [" << Reference << L"] !" << endl;
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Tento CODE NESPOSOBI presmerovanie REFERENCE, ale iba PRIRADENIE VALUE VARIABLE 'Value2' do REFERENCE 'Reference' a VARIABLE 'Value1' na ktoru REFERENCE odkazuje.
	Reference=Value2;

	wcout << L"REFERENCE [" << Reference << L"] !" << endl;
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	// !!! Meni sa hodnota REFERENCE aj POVODNEJ VARIABLE na ktoru REFERENCE ODKAZUJE co je VARIABLE 'Value1'.
	Reference+=5;

	wcout << L"REFERENCE [" << Reference << L"] !" << endl;
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Do CONST REFERENCES je mozne ukladat aj RVALUES. COMPILER vygeneruje TEMPORARY VARIABLE, ktora ma platnost az do skoncenia platnosti REFERENCE.
	const double&												Value3=123.456;

	// !!!!! Do CONST REFERENCES je mozne ukladat aj RVALUES, ktore maju ODLISNY TYPE. COMPILER vygeneruje TEMPORARY VARIABLE, ktora ma platnost az do skoncenia platnosti REFERENCE.
	const double&												Value4=static_cast<int>(123);

	wcout << L"VALUE 3 [" << Value3 << L"] !" << endl;
	wcout << L"VALUE 4 [" << Value4 << L"] !" << endl;

	PrintLineSeparator();

	// NON-CONST REFERENCES mozu FUNCTIONS MODIFIKOVAT.
	ModifyValue(Value2);

	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void PerfectSwap(TType& Value1, TType& Value2)
{
	TType														Temp=static_cast<TType&&>(Value1);

	Value1=static_cast<TType&&>(Value2);
	Value2=static_cast<TType&&>(Temp);
}
//-----------------------------------------------------------------------------
void TestRValueReferences(void)
{
	PrintLineSeparator();

	wstring														LValue=L"Timmy Anderson";
	wstring&													LValueReference=LValue;

	wcout << L"LValue [" << LValue << L"] !" << endl;
	wcout << L"LValueReference [" << LValueReference << L"] !" << endl;

	/*
	// !!! C++ NEUMOZNUJE vytvarat NON-CONST LVALUE REFERENCES na RVALUES.
	wstring&													BadLValueReference=wstring(L"Timmy Anderson");

	wcout << L"BadLValueReference [" << BadLValueReference << L"] !" << endl;
	*/

	// !!! C++ UMOZNUJE vytvarat CONST LVALUE REFERENCES na RVALUES.
	const wstring&												ConstLValueReference=wstring(L"Timmy Anderson");

	wcout << L"ConstLValueReference [" << ConstLValueReference << L"] !" << endl;

	PrintLineSeparator();

	// !!! RVALUE REFERENCE moze ukazovat IBA na RVALUES. RVALUES su TEMPORARY OBJECTS.
	wstring&&													RValueReference=wstring(L"Timmy Anderson");

	wcout << L"RValueReference [" << RValueReference << L"] !" << endl;

	/*
	// !!! C++ NEUMOZNUJE vytvarat RVALUE REFERENCES na LVALUES.
	wstring&&													BadRValueReference=LValue;

	wcout << L"BadRValueReference [" << BadRValueReference << L"] !" << endl;
	*/

	PrintLineSeparator();

	wstring														Value1=L"Timmy Anderson";
	wstring														Value2=L"Jenny Thompson";
	
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	PerfectSwap(Value1,Value2);

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	CString														CustomValue1(L"Timmy Anderson");
	CString														CustomValue2(L"Jenny Thompson");
	
	wcout << L"CUSTOM VALUE 1 [" << CustomValue1.GetValue() << L"] !" << endl;
	wcout << L"CUSTOM VALUE 2 [" << CustomValue2.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	PerfectSwap(CustomValue1,CustomValue2);

	wcout << L"CUSTOM VALUE 1 [" << CustomValue1.GetValue() << L"] !" << endl;
	wcout << L"CUSTOM VALUE 2 [" << CustomValue2.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CString														LValueForMove(L"Timmy Anderson");

	wcout << L"LValueForMove [" << LValueForMove.GetValue() << L"] !" << endl;

	// !!! NEROBI MOVE, iba vytvori RVALUE REFERENCE.
	CString&&													RValueReferenceByMove(move(LValueForMove));

	wcout << L"RValueReferenceByMove [" << RValueReferenceByMove.GetValue() << L"] !" << endl;
	wcout << L"LValueForMove [" << LValueForMove.GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! VALUE je MOVED.
	CString														MovedVariable(move(LValueForMove));

	wcout << L"MovedVariable [" << MovedVariable.GetValue() << L"] !" << endl;
	wcout << L"LValueForMove [" << LValueForMove.GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReferencesCollapse(void)
{
	PrintLineSeparator();

	using														LValueReferenceType=wstring&;
	using														RValueReferenceType=wstring&&;

	wstring														LValue(L"Timmy Anderson");

	wcout << L"LValue [" << LValue << L"] !" << endl;

	PrintLineSeparator();

	// !!! TYPE [LValueReferenceType&] sa transformuje na TYPE [wstring& &] a ten sa transformuje na TYPE [wstring&].
	LValueReferenceType&										LValueReferenceToLValueReference(LValue);

	wcout << L"LValueReferenceToLValueReference [" << LValueReferenceToLValueReference << L"] !" << endl;

	PrintLineSeparator();

	// !!! TYPE [LValueReferenceType&&] sa transformuje na TYPE [wstring& &&] a ten sa transformuje na TYPE [wstring&].
	LValueReferenceType&&										LValueReferenceToRValueReference(LValue);

	wcout << L"LValueReferenceToRValueReference [" << LValueReferenceToRValueReference << L"] !" << endl;

	PrintLineSeparator();

	// !!! TYPE [RValueReferenceType&] sa transformuje na TYPE [wstring&& &] a ten sa transformuje na TYPE [wstring&].
	RValueReferenceType&										RValueReferenceToLValueReference(LValue);

	wcout << L"RValueReferenceToLValueReference [" << RValueReferenceToLValueReference << L"] !" << endl;

	PrintLineSeparator();

	// !!! TYPE [RValueReferenceType&&] sa transformuje na TYPE [wstring&& &&] a ten sa transformuje na TYPE [wstring&&].
	// !!!!! Vysledkom je RVALUE REFERENCE.
	RValueReferenceType&&										RValueReferenceToRValueReference(wstring(L"Timmy Anderson"));

	wcout << L"RValueReferenceToRValueReference [" << RValueReferenceToRValueReference << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestPointersToVariables();
	//TestPointersToFunctions1();
	//TestPointersToFunctions2();
	//TestPointerToMemberVariables();
	//TestPointerToMemberFunctions();
	//TestPointerToVoid();
	//TestArrays();
	//TestStringLiterals();
	//TestRawStringLiterals();
	//TestLargeStringLiterals();
	//TestArraysToPointers();
	//TestMultidimensionalArrays();
	//TestPassingArrays();
	//TestConstPointers();
	//TestLValueReferences();
	//TestRValueReferences();
	TestReferencesCollapse();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------