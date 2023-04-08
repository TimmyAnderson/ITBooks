//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include "MyDebug.h"
#include "CSimpleClass.h"
#include "CAccessControlDerived.h"
#include "SSimpleStruct.h"
#include "CConstructors.h"
#include "CExplicitConstructors.h"
#include "CInClassInitializers.h"
#include "CInClassMethods.h"
#include "CConstObject.h"
#include "CMutableFields.h"
#include "CConstFieldsPointerReference.h"
#include "CThisPointer.h"
#include "CPointerToMembers.h"
#include "CStaticFieldsAndMethods.h"
#include "COuterNestedClasses.h"
#include "COperatorOverloading.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClass(void)
{
	PrintLineSeparator();

	CSimpleClass												Object(L"Timmy Anderson");
	CSimpleClass&												ReferenceToObejct=Object;
	CSimpleClass*												PointerToObejct=&Object;

	wcout << L"FIELD [" << Object.GetField() << L"] !" << endl;
	wcout << L"FIELD [" << ReferenceToObejct.GetField() << L"] !" << endl;
	wcout << L"FIELD [" << PointerToObejct->GetField() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAccessControl(void)
{
	PrintLineSeparator();

	CAccessControlDerived										Object;

	// !!! PRIVATE METHODS NIE JE MOZNE volat MIMO CLASS, ktora PRIVATE METHOD definovala. Preto COMPILER hodi ERROR.
	//Object.DerivedPrivateMethod();

	// !!! PROTECTED METHODS NIE JE MOZNE volat MIMO CLASS, ktora PROTECTED METHOD definovala, alebo z jej DERIVED CLASSES. Preto COMPILER hodi ERROR.
	//Object.DerivedProtectedMethod();

	// !!! PUBLIC METHODS JE MOZNE volat z lubovolneho CODE.
	Object.DerivedPublicMethod();

	Object.Test();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStructure(void)
{
	PrintLineSeparator();

	SSimpleStruct												Object(L"Timmy Anderson");
	SSimpleStruct&												ReferenceToObejct=Object;
	SSimpleStruct*												PointerToObejct=&Object;

	wcout << L"FIELD [" << Object.GetField() << L"] !" << endl;
	wcout << L"FIELD [" << ReferenceToObejct.GetField() << L"] !" << endl;
	wcout << L"FIELD [" << PointerToObejct->GetField() << L"] !" << endl;

	// !!! PRIAMY pristup k FIELD.
	wcout << L"FIELD [" << Object.MField << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstructors(void)
{
	PrintLineSeparator();

	{
		CConstructors											Object(10);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		CConstructors											Object(L"AAA",10);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		CConstructors											Object(10,20);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		CConstructors											Object(L"AAA",10);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		CConstructors											Object(10,20);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		CConstructors											Object(L"AAA",10);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		CConstructors											Object(10,20);

		PrintLineSeparator();

		Object.Print();

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ExplicitConstructorsFunction(const CExplicitConstructors& Value)
{
	Value.Print();
}
//-----------------------------------------------------------------------------
void TestExplicitConstructors(void)
{
	PrintLineSeparator();

	{
		// Vola sa IMPLICIT CONSTRUCTOR.
		CExplicitConstructors									Object(L"AAA");

		Object.Print();
	}

	PrintLineSeparator();

	{
		// Vola sa EXPLICIT CONSTRUCTOR.
		CExplicitConstructors									Object(10);

		Object.Print();
	}

	PrintLineSeparator();

	{
		// Vola sa IMPLICIT CONSTRUCTOR.
		CExplicitConstructors									Object(L"AAA",10);

		Object.Print();
	}

	PrintLineSeparator();

	{
		// Vola sa EXPLICIT CONSTRUCTOR.
		CExplicitConstructors									Object(10,L"AAA");

		Object.Print();
	}

	PrintLineSeparator();

	{
		CExplicitConstructors									Object;

		// !!! Kedze CONSTRUCTOR s PARAMETER [CONST WCHAR_T*] je IMPLICIT, je mozne vykonat nasledujuci prikaz, ked sa IMPLICITNE zavola CONSTRUCTOR.
		Object=L"AAA";

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!! Kedze CONSTRUCTOR s PARAMETER [CONST WCHAR_T*] je IMPLICIT, je mozne vykonat nasledujuci prikaz, ked sa IMPLICITNE zavola CONSTRUCTOR.
		ExplicitConstructorsFunction(L"AAA");
	}

	/*
	PrintLineSeparator();

	{
		CExplicitConstructors									Object;

		// !!! Kedze CONSTRUCTOR s PARAMETER [INT] je EXPLICIT, COMPILER hodi ERROR.
		Object=10;

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!! Kedze CONSTRUCTOR s PARAMETER [INT] je EXPLICIT, COMPILER hodi ERROR.
		ExplicitConstructorsFunction(10);
	}
	*/

	PrintLineSeparator();

	{
		CExplicitConstructors									Object;

		// !!! Kedze CONSTRUCTOR s PARAMETERS [CONST WCHAR_T*,INT] je IMPLICIT, je mozne vykonat nasledujuci prikaz, ked sa IMPLICITNE zavola CONSTRUCTOR.
		Object={L"AAA",10};

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!! Kedze CONSTRUCTOR s PARAMETER [CONST WCHAR_T*,INT] je IMPLICIT, je mozne vykonat nasledujuci prikaz, ked sa IMPLICITNE zavola CONSTRUCTOR.
		ExplicitConstructorsFunction({L"AAA",10});
	}

	/*
	PrintLineSeparator();

	{
		CExplicitConstructors									Object;

		// !!! Kedze CONSTRUCTOR s PARAMETER [INT,CONST WCHAR_T*] je EXPLICIT, COMPILER hodi ERROR.
		Object={10,L"AAA"};

		Object.Print();
	}

	PrintLineSeparator();

	{
		// !!! Kedze CONSTRUCTOR s PARAMETER [INT,CONST WCHAR_T*] je EXPLICIT, COMPILER hodi ERROR.
		ExplicitConstructorsFunction({10,L"AAA"});
	}
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInClassInitializers(void)
{
	PrintLineSeparator();

	wcout << L"VALUE GlobalVariable [" << GlobalVariable << L"] !" << endl;

	PrintLineSeparator();

	{
		// Pre FIELD 'MValue3' a FIELD 'MValue4' sa NEVOLALI INITIALIZERS v MEMBER INITIALIZER LIST, a preto sa pre tieto FIELDS pouziju IN CLASS INITIALIZES.
		CInClassInitializers									Object(100,200);

		PrintLineSeparator();

		wcout << L"VALUE Value1 [" << Object.GetValue1().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value2 [" << Object.GetValue2().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value3 [" << Object.GetValue3().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value4 [" << Object.GetValue4().GetValue() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	wcout << L"VALUE GlobalVariable [" << GlobalVariable << L"] !" << endl;

	PrintLineSeparator();

	{
		// !!! Kedze CONSTRUCTOR NENASTAVUJE hodnoty FIELDS v MEMBER INITIALIZER LIST, ale inicializacia sa vykonava volanim OPERATOR=, IN CLASS INITIALIZERS sa v tomto pripade POUZIJU.
		CInClassInitializers									Object(100,200,300,400,500);

		PrintLineSeparator();

		wcout << L"VALUE Value1 [" << Object.GetValue1().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value2 [" << Object.GetValue2().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value3 [" << Object.GetValue3().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value4 [" << Object.GetValue4().GetValue() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	wcout << L"VALUE GlobalVariable [" << GlobalVariable << L"] !" << endl;

	PrintLineSeparator();

	{
		// !!! Kedze CONSTRUCTOR nastavuje v MEMBER INITIALIZER LIST VSETKY FIELDS, IN CLASS INITIALIZERS sa NEVOLAJU.
		CInClassInitializers									Object(100,200,300,400);

		PrintLineSeparator();

		wcout << L"VALUE Value1 [" << Object.GetValue1().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value2 [" << Object.GetValue2().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value3 [" << Object.GetValue3().GetValue() << L"] !" << endl;
		wcout << L"VALUE Value4 [" << Object.GetValue4().GetValue() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	wcout << L"VALUE GlobalVariable [" << GlobalVariable << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInClassMethods(void)
{
	PrintLineSeparator();

	CInClassMethods												Object;

	Object.InClassMethod();

	Object.OutClassMethod();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstClasses(void)
{
	PrintLineSeparator();

	CConstObject												NonConstObject(100,200);

	wcout << L"NON CONST OBJECT - CONST FIELD [" << NonConstObject.GetConstField() << L"] NON-CONST FIELD [" << NonConstObject.GetNonConstField() << L"] !" << endl;

	PrintLineSeparator();

	NonConstObject.SetNonConstField(250);

	wcout << L"NON CONST OBJECT - CONST FIELD [" << NonConstObject.GetConstField() << L"] NON-CONST FIELD [" << NonConstObject.GetNonConstField() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vola sa NON-CONST VERSION METHOD.
	NonConstObject.Method();

	PrintLineSeparator();

	const CConstObject											ConstObject(300,400);

	// !!! CONST OBJECTS NEMOZU volat NON-CONST METHODS.
	//ConstObject.SetNonConstField(250);

	wcout << L"CONST OBJECT - CONST FIELD [" << ConstObject.GetConstField() << L"] NON-CONST FIELD [" << ConstObject.GetNonConstField() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vola sa CONST VERSION METHOD.
	ConstObject.Method();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMutableFields(void)
{
	PrintLineSeparator();

	CMutableFields												Object(100);

	wcout << L"OBJECT - MUTABLE FIELD [" << Object.GetMutableField() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Aj NAPRIEK tomu, ze METHOD je CONST METHOD, kedze FIELD je MUTABLE FIELD, tak METHOD MOZE nastavit VALUE MUTABLE FIELD.
	Object.SetMutableField(200);

	wcout << L"OBJECT - MUTABLE FIELD [" << Object.GetMutableField() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstFieldsPointerReference(void)
{
	PrintLineSeparator();

	CConstFieldsField											PointerField(100);
	CConstFieldsField											ReferenceField(200);
	CConstFieldsPointerReference								Object(300,&PointerField,ReferenceField);

	wcout << L"OBJECT - VALUE FIELD [" << Object.GetValueField() << L"] POINTER FIELD [" << Object.GetPointerField() << L"] REFERENCE FIELD [" << Object.GetReferenceField() << L"] !" << endl;
	wcout << L"POINTER FIELD [" << Object.GetPointerField() << L"] !" << endl;
	wcout << L"REFERENCE FIELD [" << Object.GetReferenceField() << L"] !" << endl;

	PrintLineSeparator();

	// !!!!! Aj ked METHOD je deklarovana ako CONST, CONST METHODS MOZU volat NON-CONST METHODS POINTER FIELDS a REFERENCE FIELDS.
	Object.SetValues(1100,1200);

	wcout << L"OBJECT - VALUE FIELD [" << Object.GetValueField() << L"] POINTER FIELD [" << Object.GetPointerField() << L"] REFERENCE FIELD [" << Object.GetReferenceField() << L"] !" << endl;
	wcout << L"POINTER FIELD [" << Object.GetPointerField() << L"] !" << endl;
	wcout << L"REFERENCE FIELD [" << Object.GetReferenceField() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestThisPointer(void)
{
	PrintLineSeparator();

	CThisPointer												Object(100);

	wcout << L"OBJECT - FIELD [" << Object.GetField() << L"] !" << endl;

	Object.SetField(200);

	wcout << L"OBJECT - FIELD [" << Object.GetField() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Ak METHOD vracia ako RETURN VALUE REFERENCE na THIS OBJECT, potom je mozne vykonat METHOD CHAINING.
	Object.MethodChaining1().MethodChaining2().MethodChaining3();

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
void TestStaticFieldsAndMethods(void)
{
	PrintLineSeparator();

	// Citanie STATIC VARIABLE.
	wcout << L"STATIC FIELD [" << CStaticFieldsAndMethods::GetStaticField() << L"] !" << endl;

	PrintLineSeparator();

	{
		CStaticFieldsAndMethods									Object1(100);

		wcout << L"OBJECT 1 - NON-STATIC FIELD [" << Object1.GetNonStaticField() << L"] !" << endl;
		wcout << L"STATIC FIELD [" << CStaticFieldsAndMethods::GetStaticField() << L"] !" << endl;

		PrintLineSeparator();

		{
			CStaticFieldsAndMethods								Object2(200);

			wcout << L"OBJECT 2 - NON-STATIC FIELD [" << Object2.GetNonStaticField() << L"] !" << endl;
			wcout << L"STATIC FIELD [" << CStaticFieldsAndMethods::GetStaticField() << L"] !" << endl;
		}

		PrintLineSeparator();

		wcout << L"STATIC FIELD [" << CStaticFieldsAndMethods::GetStaticField() << L"] !" << endl;
	}

	PrintLineSeparator();

	wcout << L"STATIC FIELD [" << CStaticFieldsAndMethods::GetStaticField() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNestedClasses(void)
{
	PrintLineSeparator();

	{
		COuterNestedClasses											OuterClass(100);
		COuterNestedClasses::CNestedClass							NestedClass(200);

		PrintLineSeparator();

		OuterClass.PrintNestedField(NestedClass);
		OuterClass.PrintOuterField();

		PrintLineSeparator();

		NestedClass.PrintNestedField();
		NestedClass.PrintOuterField(OuterClass);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorsOverloading1(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << (COperatorOverloading(20)+10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (COperatorOverloading(20)-10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (COperatorOverloading(20)*10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (COperatorOverloading(20)/10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (COperatorOverloading(20)%10).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20+COperatorOverloading(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20-COperatorOverloading(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20*COperatorOverloading(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20/COperatorOverloading(10)).GetValue() << L"] !" << endl;
	
	PrintLineSeparator();

	wcout << L"VALUE [" << (20%COperatorOverloading(10)).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorsOverloading2(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << (+COperatorOverloading(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (-COperatorOverloading(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (++COperatorOverloading(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (COperatorOverloading(20)++).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (--COperatorOverloading(20)).GetValue() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE [" << (COperatorOverloading(20)--).GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestClass();
	//TestAccessControl();
	//TestStructure();
	//TestConstructors();
	//TestExplicitConstructors();
	//TestInClassInitializers();
	//TestInClassMethods();
	//TestConstClasses();
	//TestMutableFields();
	//TestConstFieldsPointerReference();
	//TestThisPointer();
	//TestPointerToMemberVariables();
	TestPointerToMemberFunctions();
	//TestStaticFieldsAndMethods();
	//TestNestedClasses();
	//TestOperatorsOverloading1();
	//TestOperatorsOverloading2();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------