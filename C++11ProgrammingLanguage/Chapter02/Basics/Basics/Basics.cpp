//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <complex>
#include <vector>
#include "MyDebug.h"
#include "CInt.h"
#include "SStructure.h"
#include "CClass.h"
#include "EEnum.h"
#include "EEnumClass.h"
#include "CNamespace.h"
#include "CBaseExceptionType.h"
#include "CDerivedExceptionType.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypesVariablesArithmetics(void)
{
	PrintLineSeparator();

	wcout << L"SIZEOF(int) [" << sizeof(int) << L"] !" << endl;
	wcout << L"SIZEOF(float) [" << sizeof(float) << L"] !" << endl;
	wcout << L"SIZEOF(double) [" << sizeof(double) << L"] !" << endl;

	PrintLineSeparator();

	double														X=100;
	// Pouziva sa UNIFORM INITIALIZATION.
	double														Y{33.456};

	wcout << L"X+Y [" << (X+Y) << L"] !" << endl;
	wcout << L"X-Y [" << (X-Y) << L"] !" << endl;
	wcout << L"X*Y [" << (X*Y) << L"] !" << endl;
	wcout << L"X/Y [" << (X/Y) << L"] !" << endl;

	wcout << L"X>Y [" << (X>Y) << L"] !" << endl;
	wcout << L"X>=Y [" << (X>=Y) << L"] !" << endl;
	wcout << L"X<Y [" << (X<Y) << L"] !" << endl;
	wcout << L"X<=Y [" << (X<=Y) << L"] !" << endl;
	wcout << L"X==Y [" << (X==Y) << L"] !" << endl;
	wcout << L"X!=Y [" << (X!=Y) << L"] !" << endl;

	PrintLineSeparator();

	complex<double>												Complex1{3.3,5.4};
	complex<double>												Complex2{8.1,1.7};

	wcout << L"COMPLEX1 [" << (Complex1.real()) << "," << (Complex1.imag()) << L"] !" << endl;
	wcout << L"COMPLEX2 [" << (Complex2.real()) << "," << (Complex2.imag()) << L"] !" << endl;

	wcout << L"COMPLEX1+COMPLEX2 [" << ((Complex1+Complex2).real()) << "," << ((Complex1+Complex2).imag()) << L"] !" << endl;
	wcout << L"COMPLEX1-COMPLEX2 [" << ((Complex1-Complex2).real()) << "," << ((Complex1-Complex2).imag()) << L"] !" << endl;
	wcout << L"COMPLEX1*COMPLEX2 [" << ((Complex1*Complex2).real()) << "," << ((Complex1*Complex2).imag()) << L"] !" << endl;
	wcout << L"COMPLEX1/COMPLEX2 [" << ((Complex1/Complex2).real()) << "," << ((Complex1/Complex2).imag()) << L"] !" << endl;

	PrintLineSeparator();

	vector<double>												Collection{1.2,3.4,5.6,7.8};
	bool														AddSpace=false;

	wcout << L"COLLECTION [";

	for(double Value : Collection)
	{
		if (AddSpace==false)
		{
			AddSpace=true;
		}
		else
		{
			wcout << L" ";
		}

		wcout << Value;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
constexpr int Calculate(int Value1, int Value2)
{
	return(Value1*Value2);
}
//-----------------------------------------------------------------------------
constexpr int CalculateConst(int Value1, int Value2)
{
	return(Value1*Value2);
}
//-----------------------------------------------------------------------------
void TestConstantsAndConstantExpressions(void)
{
	PrintLineSeparator();

	int															Variable=5;
	const int													RunTimeConstant1=Variable;

	wcout << L"Variable [" << Variable << L"] !" << endl;
	wcout << L"RunTimeConstant1 [" << RunTimeConstant1 << L"] !" << endl;

	// !!! COMPILER hodi ERROR, lebo CONST VARIABLE 'RunTimeConstant1' je RUN TIME CONSTANT.
	/*
	int															RunTimeArray1[RunTimeConstant1];

	wcout << L"SIZEOF(RunTimeArray1) [" << sizeof(RunTimeArray1) << L"] !" << endl;
	*/

	const int													CompileTimeConstant1=5;

	wcout << L"CompileTimeConstant1 [" << CompileTimeConstant1 << L"] !" << endl;

	// !!! COMPILER AKCEPTUJE VARIABLE 'CompileTimeConstant1', pretoze sa jedna o COMPILE TIME VARIABLE.
	int															CompileTimeArray[CompileTimeConstant1];

	wcout << L"SIZEOF(CompileTimeArray) [" << sizeof(CompileTimeArray) << L"] !" << endl;

	int															Variable1=5;
	int															Variable2=10;

	wcout << L"Variable1 [" << Variable1 << L"] !" << endl;
	wcout << L"Variable2 [" << Variable2 << L"] !" << endl;

	const int													RunTimeConstant2=Calculate(Variable1,Variable2);
	const int													RunTimeConstant3=CalculateConst(Variable1,Variable2);

	wcout << L"RunTimeConstant2 [" << RunTimeConstant2 << L"] !" << endl;
	wcout << L"RunTimeConstant3 [" << RunTimeConstant3 << L"] !" << endl;

	// !!! COMPILER hodi ERROR, lebo CONST VARIABLE 'RunTimeConstant2' je RUN TIME CONSTANT.
	/*
	int															RunTimeArray2[RunTimeConstant2];

	wcout << L"SIZEOF(RunTimeArray2) [" << sizeof(RunTimeArray2) << L"] !" << endl;
	*/

	// !!! COMPILER hodi ERROR, lebo CONST VARIABLE 'RunTimeConstant3' je RUN TIME CONSTANT.
	/*
	int															RunTimeArray2[RunTimeConstant3];

	wcout << L"SIZEOF(RunTimeArray3) [" << sizeof(RunTimeArray3) << L"] !" << endl;
	*/

	const int													CompileTimeConstant2=5;
	const int													CompileTimeConstant3=6;

	// !!! COMPILER hodi ERROR, pretoze CONSTEXPR FUNCTION NEMOZE mat ako PARAMETER NON-CONST VALUES a generovat CONSTEXPR VARIABLES.
	//constexpr int												NonCompileTimeTimeConstant=CalculateConst(Variable1,Variable2);
	constexpr int												CompileTimeTimeConstant=CalculateConst(CompileTimeConstant2,CompileTimeConstant3);

	wcout << L"CompileTimeTimeConstant [" << CompileTimeTimeConstant << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStatements(void)
{
	PrintLineSeparator();

	bool														ConditionTrue=true;

	if (ConditionTrue==true)
	{
		wcout << L"IF STATEMENT TRUE !" << endl;
	}
	else
	{
		wcout << L"IF STATEMENT FALSE !" << endl;
	}

	bool														ConditionFalse=false;

	if (ConditionFalse==true)
	{
		wcout << L"IF STATEMENT TRUE !" << endl;
	}
	else
	{
		wcout << L"IF STATEMENT FALSE !" << endl;
	}

	PrintLineSeparator();

	int															SwitchValue1=1;

	switch(SwitchValue1)
	{
		case 1:
		{
			wcout << L"SWITCH STATEMENT 1 !" << endl;
		}
		break;

		case 2:
		{
			wcout << L"SWITCH STATEMENT 2 !" << endl;
		}
		break;

		default:
		{
			wcout << L"SWITCH STATEMENT DEFAULT !" << endl;
		}
	}

	int															SwitchValue2=2;

	switch(SwitchValue2)
	{
		case 1:
		{
			wcout << L"SWITCH STATEMENT 1 !" << endl;
		}
		break;

		case 2:
		{
			wcout << L"SWITCH STATEMENT 2 !" << endl;
		}
		break;

		default:
		{
			wcout << L"SWITCH STATEMENT DEFAULT !" << endl;
		}
	}

	int															SwitchValueN=3;

	switch(SwitchValueN)
	{
		case 1:
		{
			wcout << L"SWITCH STATEMENT 1 !" << endl;
		}
		break;

		case 2:
		{
			wcout << L"SWITCH STATEMENT 2 !" << endl;
		}
		break;

		default:
		{
			wcout << L"SWITCH STATEMENT DEFAULT !" << endl;
		}
	}

	PrintLineSeparator();

	for(int Index=0;Index<3;Index++)
	{
		wcout << L"FOR STATEMENT VALUE [" << Index << L"] !" << endl;
	}

	PrintLineSeparator();

	int															WhileIndex=0;

	while(++WhileIndex<3)
	{
		wcout << L"WHILE STATEMENT VALUE [" << WhileIndex << L"] !" << endl;
	}

	PrintLineSeparator();

	int															DoWhileIndex=0;

	do
	{
		wcout << L"DO WHILE STATEMENT VALUE [" << DoWhileIndex << L"] !" << endl;
	}
	while(++DoWhileIndex<3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPointers(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=10;
	int															Array[ARRAY_SIZE];

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		Array[Index]=(Index+1)*10;
	}

	{
		bool													AddSpace=false;

		wcout << L"ARRAY [";

		for(int Value : Array)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << Value;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	int*														Pointer=nullptr;

	wcout << L"POINTER [" << Pointer << L"] !" << endl;

	PrintLineSeparator();

	// !!! Do POINTER sa priradi ADDRESS pomocou OPERATOR&.
	Pointer=&Array[3];

	wcout << L"POINTER [" << Pointer << L"] !" << endl;
	wcout << L"POINTER DIFFERENCE [" << (Pointer-Array) << L"] !" << endl;
	wcout << L"POINTER VALUE [" << *Pointer << L"] !" << endl;

	PrintLineSeparator();

	// Na POINTERS je mozne aplikovat POINTER ARITHMETICS.
	Pointer+=2;

	wcout << L"POINTER [" << Pointer << L"] !" << endl;
	wcout << L"POINTER DIFFERENCE [" << (Pointer-Array) << L"] !" << endl;
	wcout << L"POINTER VALUE [" << *Pointer << L"] !" << endl;

	PrintLineSeparator();

	*Pointer*=2;

	wcout << L"POINTER [" << Pointer << L"] !" << endl;
	wcout << L"POINTER DIFFERENCE [" << (Pointer-Array) << L"] !" << endl;
	wcout << L"POINTER VALUE [" << *Pointer << L"] !" << endl;

	PrintLineSeparator();

	{
		bool													AddSpace=false;

		wcout << L"ARRAY [";

		for(int Value : Array)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << Value;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	CInt														Object(100);
	CInt*														PointerToObject=&Object;

	// !!! K MEMBERS daneho OBJECT POINTER pristupuje pomocou OPERATOR->.
	wcout << L"POINTER to OBJECT [" << PointerToObject->GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReferences(void)
{
	PrintLineSeparator();

	int															Value=100;

	// !!! REFERENCES MUSIA byt VZDY INITIALIZED.
	int&														Reference=Value;

	wcout << L"VALUE [" << Value << L"] !" << endl;
	wcout << L"REFERENCE [" << Reference << L"] !" << endl;

	PrintLineSeparator();

	Reference+=20;

	wcout << L"VALUE [" << Value << L"] !" << endl;
	wcout << L"REFERENCE [" << Reference << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrays(void)
{
	PrintLineSeparator();

	const int													ARRAY_SIZE=10;
	int															Array[ARRAY_SIZE];

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		Array[Index]=(Index+1)*10;
	}

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		wcout << L"ARRAY[" << Index << L"] [" << Array[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		Array[Index]=Array[Index]+Index;
	}

	for(int Index=0;Index<ARRAY_SIZE;Index++)
	{
		wcout << L"ARRAY[" << Index << L"] [" << Array[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStructures(void)
{
	PrintLineSeparator();

	{
		SStructure												Structure(100);
		SStructure*												PointerToStructure=&Structure;
		SStructure&												ReferenceToStructure=Structure;

		wcout << L"STRUCTURE [" << Structure.GetValue() << L"] !" << endl;
		wcout << L"POINTER to STRUCTURE [" << PointerToStructure->GetValue() << L"] !" << endl;
		wcout << L"REFERENCE to STRUCTURE [" << ReferenceToStructure.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClasses(void)
{
	PrintLineSeparator();

	{
		CClass													Class(100);
		CClass*													PointerToClass=&Class;
		CClass&													ReferenceToClass=Class;

		wcout << L"CLASS [" << Class.GetValue() << L"] !" << endl;
		wcout << L"POINTER to CLASS [" << PointerToClass->GetValue() << L"] !" << endl;
		wcout << L"REFERENCE to CLASS [" << ReferenceToClass.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEnumerations(void)
{
	PrintLineSeparator();

	// !!! V C ENUMERATIONS su MEMBERS sucastou GLOBAL SCOPE.
	wcout << L"ENUM EEnum E_MEMBER_1 [" << E_MEMBER_1 << L"] !" << endl;
	wcout << L"ENUM EEnum E_MEMBER_2 [" << E_MEMBER_2 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"ENUM EEnum E_MEMBER_1 [" << EEnum::E_MEMBER_1 << L"] !" << endl;
	wcout << L"ENUM EEnum E_MEMBER_2 [" << EEnum::E_MEMBER_2 << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pri C++ ENUMERATIONS je konverziu na NUMERIC TYPE NUTNE robit EXPLICITNE.
	wcout << L"ENUM EEnumClass E_MEMBER_1 [" << static_cast<int>(EEnumClass::E_MEMBER_1) << L"] !" << endl;
	wcout << L"ENUM EEnumClass E_MEMBER_2 [" << static_cast<int>(EEnumClass::E_MEMBER_2) << L"] !" << endl;

	PrintLineSeparator();

	// ENUMERATIONS maju IMPLICITNE definovane COMPARISON OPERATORS.
	wcout << L"ENUM EEnumClass E_MEMBER_1<E_MEMBER_2 [" << (EEnumClass::E_MEMBER_1<EEnumClass::E_MEMBER_2) << L"] !" << endl;
	wcout << L"ENUM EEnumClass E_MEMBER_1<=E_MEMBER_2 [" << (EEnumClass::E_MEMBER_1<=EEnumClass::E_MEMBER_2) << L"] !" << endl;
	wcout << L"ENUM EEnumClass E_MEMBER_1>E_MEMBER_2 [" << (EEnumClass::E_MEMBER_1>EEnumClass::E_MEMBER_2) << L"] !" << endl;
	wcout << L"ENUM EEnumClass E_MEMBER_1>=E_MEMBER_2 [" << (EEnumClass::E_MEMBER_1>=EEnumClass::E_MEMBER_2) << L"] !" << endl;
	wcout << L"ENUM EEnumClass E_MEMBER_1==E_MEMBER_2 [" << (EEnumClass::E_MEMBER_1==EEnumClass::E_MEMBER_2) << L"] !" << endl;
	wcout << L"ENUM EEnumClass E_MEMBER_1!=E_MEMBER_2 [" << (EEnumClass::E_MEMBER_1!=EEnumClass::E_MEMBER_2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNamespaces(void)
{
	PrintLineSeparator();

	{
		MY::CNamespace											Value(100);

		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		using namespace											MY;

		CNamespace												Value(100);

		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThrowCIntException(void)
{
	try
	{
		throw(CInt(100));
	}
	// !!! Kedze CATCH BLOCK ma INY TYPE, NIE JE ZACHYTENY v CATCH BLOCK.
	catch(const CBaseExceptionType& E)
	{
		wcout << L"BASE EXCEPTION - BASE VALUE [" << E.GetBaseValue() << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestExceptions(void)
{
	PrintLineSeparator();

	try
	{
		throw(CDerivedExceptionType(100,200));
	}
	catch(const CDerivedExceptionType& E)
	{
		wcout << L"DERIVED EXCEPTION - BASE VALUE [" << E.GetBaseValue() << L"] DERIVED VALUE [" << E.GetDerivedValue() << L"] !" << endl;
	}
	catch(const CBaseExceptionType& E)
	{
		wcout << L"BASE EXCEPTION - BASE VALUE [" << E.GetBaseValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		throw(CBaseExceptionType(100));
	}
	catch(const CDerivedExceptionType& E)
	{
		wcout << L"DERIVED EXCEPTION - BASE VALUE [" << E.GetBaseValue() << L"] DERIVED VALUE [" << E.GetDerivedValue() << L"] !" << endl;
	}
	catch(const CBaseExceptionType& E)
	{
		wcout << L"BASE EXCEPTION - BASE VALUE [" << E.GetBaseValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		throw(CInt(100));
	}
	catch(const CDerivedExceptionType& E)
	{
		wcout << L"DERIVED EXCEPTION - BASE VALUE [" << E.GetBaseValue() << L"] DERIVED VALUE [" << E.GetDerivedValue() << L"] !" << endl;
	}
	catch(const CBaseExceptionType& E)
	{
		wcout << L"BASE EXCEPTION - BASE VALUE [" << E.GetBaseValue() << L"] !" << endl;
	}
	catch(...)
	{
		wcout << L"UNKNOWN EXCEPTION !" << endl;
	}

	PrintLineSeparator();

	try
	{
		ThrowCIntException();
	}
	catch(const CInt& E)
	{
		wcout << L"INT EXCEPTION - VALUE [" << E.GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStaticAsserts(void)
{
	PrintLineSeparator();

	wcout << L"STATIC ASSERT TEST !" << endl;

	static_assert(true,"There is SOME ERROR !");

	// !!! Hodi COMPILATION ERROR.
	//static_assert(false,"There is SOME ERROR !");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestTypesVariablesArithmetics();
	//TestConstantsAndConstantExpressions();
	//TestStatements();
	//TestPointers();
	//TestReferences();
	//TestArrays();
	//TestStructures();
	//TestClasses();
	//TestEnumerations();
	//TestNamespaces();
	//TestExceptions();
	TestStaticAsserts();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------