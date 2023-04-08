//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include "MyDebug.h"
#include "CConstructorDestructor.h"
#include "CExceptionInConstructor.h"
#include "CMultipleDestructorCalls.h"
#include "CClassHierarchyDerived.h"
#include "CFieldConstructorDestructorCallOrder.h"
#include "CPlacementNew.h"
#include "CNonVirtualDestructorDerived.h"
#include "CVirtualDestructorDerived.h"
#include "CDefaultInitialization.h"
#include "CInitializerListConstructor.h"
#include "CMemberInitializerListDerived.h"
#include "CDelegatingConstructor.h"
#include "CInClassInitializers.h"
#include "CStaticMembersInitializers.h"
#include "CCopyOperations.h"
#include "CMoveOperations.h"
#include "CMoveOperationDerived.h"
#include "CDefaultOperationsGeneration.h"
#include "CDefaultOperationsGenerationDerived.h"
#include "CDefaultOperationsForcedGeneration.h"
#include "CDefaultOperationsForcedGenerationDerived.h"
#include "CDefaultConstructorGeneration.h"
#include "CDeletedDefaultOperations.h"
#include "CDeletedMethods.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstructorDestructor(void)
{
	PrintLineSeparator();

	{
		// Pouzije sa DEFAULT CONSTRUCTOR.
		CConstructorDestructor									Value1;

		PrintLineSeparator();

		wcout << L"VALUE 1 [" << Value1.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// Pouzije sa NON-DEFAULT CONSTRUCTOR.
		CConstructorDestructor									Value2(L"Timmy Anderson");

		PrintLineSeparator();

		wcout << L"VALUE 2 [" << Value2.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// Pouzije sa COPY OPERATOR.
		Value1=Value2;

		wcout << L"VALUE 1 [" << Value1.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// Pouzije sa NON-DEFAULT CONSTRUCTOR.
		CConstructorDestructor									Value3(L"Jenny Thompson");

		PrintLineSeparator();

		wcout << L"VALUE 3 [" << Value3.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		Value1=move(Value3);

		PrintLineSeparator();

		wcout << L"VALUE 1 [" << Value1.GetValue() << L"] !" << endl;
		wcout << L"VALUE 3 [" << Value3.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// Pouzije sa COPY CONSTRUCTOR.
		CConstructorDestructor									Value4(Value1);

		PrintLineSeparator();

		wcout << L"VALUE 4 [" << Value4.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// Pouzije sa MOVE CONSTRUCTOR.
		CConstructorDestructor									Value5(move(Value4));

		PrintLineSeparator();

		wcout << L"VALUE 4 [" << Value4.GetValue() << L"] !" << endl;
		wcout << L"VALUE 5 [" << Value5.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// Volaju sa DESTRUCTORS.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestExceptionInConstructor(void)
{
	PrintLineSeparator();

	try
	{
		// !!! CONSTRUCTOR hodi EXCEPTION.
		// !!!!! DESTRUCTOR sa NEVOLA.
		CExceptionInConstructor									Value(L"Timmy Anderson");

		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"EXCEPTION [" << E << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDestructorFunctionCall(void)
{
	PrintLineSeparator();

	{
		CMultipleDestructorCalls								Value(100);

		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!! DESTRUCTORS mozu byt volane cez FUNCTION CALL SYNTAX.
		// !!!!! DESTRUCTOR VZDY vola DESTRUCTORS VSETKYCH svojich FIELDS.
		Value.~CMultipleDestructorCalls();

		PrintLineSeparator();

		// !!!!! VALUE je nastaveny na 0, pretoze DESTRUCTOR CLASS CMultipleDestructorCallsField nastavil FIELD 'MValue' na 0.
		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!! DESTRUCTORS mozu byt volane cez FUNCTION CALL SYNTAX.
		// !!!!! DESTRUCTOR VZDY vola DESTRUCTORS VSETKYCH svojich FIELDS.
		Value.~CMultipleDestructorCalls();

		PrintLineSeparator();

		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!! DESTRUCTORS mozu byt volane cez FUNCTION CALL SYNTAX.
		// !!!!! DESTRUCTOR VZDY vola DESTRUCTORS VSETKYCH svojich FIELDS.
		Value.~CMultipleDestructorCalls();

		PrintLineSeparator();

		wcout << L"VALUE [" << Value.GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// DESTRUCTOR sa IMPLICITNE vola este raz.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestConstructorDestructorCallOrder(void)
{
	PrintLineSeparator();

	{
		CClassHierarchyDerived									Object(10,110,120,130,210,220,230,300);

		PrintLineSeparator();

		wcout << L"VALUE VA [" << Object.GetValueVA() << L"] !" << endl;
		wcout << L"VALUE A via B1 [" << static_cast<CClassHierarchyBaseB1&>(Object).GetValueA() << L"] !" << endl;
		wcout << L"VALUE A via B2 [" << static_cast<CClassHierarchyBaseB2&>(Object).GetValueA() << L"] !" << endl;
		wcout << L"VALUE B1 [" << Object.GetValueB1() << L"] !" << endl;
		wcout << L"VALUE B2 [" << Object.GetValueB2() << L"] !" << endl;
		wcout << L"VALUE [" << Object.GetValue() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFieldConstructorDestructorCallOrder(void)
{
	PrintLineSeparator();

	{
		CFieldConstructorDestructorCallOrder					Object(100,200,300);

		PrintLineSeparator();

		wcout << L"VALUE 1 [" << Object.GetValue1().GetValue() << L"] !" << endl;
		wcout << L"VALUE 2 [" << Object.GetValue2().GetValue() << L"] !" << endl;
		wcout << L"VALUE 3 [" << Object.GetValue3().GetValue() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPlacementNew(void)
{
	PrintLineSeparator();

	// BUFFER do ktoreho sa ulozi instancia CLASS 'CPlacementNew'.
	char														Buffer[sizeof(CPlacementNew)];

	// !!! PLACEMENT NEW SYNTAX NEALOKUJE IMPLICITNE MEMORY.
	// !!!!! Nasledujuce volanie ulozi instanciu 'Object' do MEMORY 'Buffer'.
	CPlacementNew*												Object=new (Buffer) CPlacementNew(100,200,300);

	PrintLineSeparator();

	wcout << L"VALUE 1 [" << Object->GetValue1().GetValue() << L"] !" << endl;
	wcout << L"VALUE 2 [" << Object->GetValue2().GetValue() << L"] !" << endl;
	wcout << L"VALUE 3 [" << Object->GetValue3().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!! PLACEMENT NEW SYNTAX NEVOLA EXPLICITNE DESTRUCTOR, a preto je ho nutne zavolat EXPLICITNE.
	Object->~CPlacementNew();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVirtualNonVirtualDestructor(void)
{
	PrintLineSeparator();

#ifdef _MSC_VER
	CNonVirtualDestructorBase*									NonVirtualObject=new CNonVirtualDestructorDerived(100);

	PrintLineSeparator();

	// !!!!! Kedze CLASS 'CNonVirtualDestructorBase' NEMA VIRTUAL CONSTRUCTOR vola sa NESPRAVNY DESTRUCTOR CLASS 'CNonVirtualDestructorDerived'.
	wcout << L"VALUE [" << NonVirtualObject->GetValue() << L"] !" << endl;

	PrintLineSeparator();
	
	// !!! GCC hodi WARNING, ze CLASS 'CNonVirtualDestructorBase' NEMA VIRTUAL DESTRUCTOR.
	delete(NonVirtualObject);

	PrintLineSeparator();
#endif

	CVirtualDestructorBase*										VirtualObject=new CVirtualDestructorDerived(100);

	PrintLineSeparator();

	wcout << L"VALUE [" << VirtualObject->GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Kedze CLASS 'CVirtualDestructorBase' ma VIRTUAL CONSTRUCTOR vola sa SPRAVNY DESTRUCTOR CLASS 'CVirtualDestructorDerived'.
	delete(VirtualObject);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNonConstructor(void)
{
	PrintLineSeparator();

	// !!!!! Pre STATIC VARIABLES AJ KED sa NEPOUZILA SYNTAX [{}], tak C++ vola DEFAULT CONSTRUCTORS pre VSETKY FIELDS, vratane FIELDS PRIMITIVE TYPES.
	static CDefaultInitialization								StaticObject;

	wcout << L"StaticObject - MObject1 [" << StaticObject.GetObject1().GetValue() << L"] !" << endl;
	wcout << L"StaticObject - MObject2 [" << StaticObject.GetObject2().GetValue() << L"] !" << endl;
	wcout << L"StaticObject - MPrimitiveType1 [" << StaticObject.GetPrimitiveType1() << L"] !" << endl;
	wcout << L"StaticObject - MPrimitiveType2 [" << StaticObject.GetPrimitiveType2() << L"] !" << endl;

	PrintLineSeparator();

	{
		// !!! Kedze sa NEPOUZILA SYNTAX [{}], tak C++ vola DEFAULT CONSTRUCTORS IBA pre FIELDS typu CLASS. PRIMITIVE TYPE FIELDS ostavaju NENAINICIALIZOVANE.
		CDefaultInitialization								LocalObject1;

		wcout << L"LocalObject1 - MObject1 [" << LocalObject1.GetObject1().GetValue() << L"] !" << endl;
		wcout << L"LocalObject1 - MObject2 [" << LocalObject1.GetObject2().GetValue() << L"] !" << endl;
		// !!! OBSAHUJE RANDOM VALUE.
		wcout << L"LocalObject1 - MPrimitiveType1 [" << LocalObject1.GetPrimitiveType1() << L"] !" << endl;
		// !!! OBSAHUJE RANDOM VALUE.
		wcout << L"LocalObject1 - MPrimitiveType2 [" << LocalObject1.GetPrimitiveType2() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// !!! Kedze sa POUZILA SYNTAX [{}], tak C++ vola DEFAULT CONSTRUCTORS pre VSETKY FIELDS, vratane FIELDS PRIMITIVE TYPES.
		CDefaultInitialization								LocalObject2{};

		wcout << L"LocalObject2 - MObject1 [" << LocalObject2.GetObject1().GetValue() << L"] !" << endl;
		wcout << L"LocalObject2 - MObject2 [" << LocalObject2.GetObject2().GetValue() << L"] !" << endl;
		wcout << L"LocalObject2 - MPrimitiveType1 [" << LocalObject2.GetPrimitiveType1() << L"] !" << endl;
		wcout << L"LocalObject2 - MPrimitiveType2 [" << LocalObject2.GetPrimitiveType2() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// Pouzije sa MEMBERWISE INITIALIZATION.
		CDefaultInitialization								LocalObject3{CField1(100),CField2(200),300,456.789};

		wcout << L"LocalObject3 - MObject1 [" << LocalObject3.GetObject1().GetValue() << L"] !" << endl;
		wcout << L"LocalObject3 - MObject2 [" << LocalObject3.GetObject2().GetValue() << L"] !" << endl;
		wcout << L"LocalObject3 - MPrimitiveType1 [" << LocalObject3.GetPrimitiveType1() << L"] !" << endl;
		wcout << L"LocalObject3 - MPrimitiveType2 [" << LocalObject3.GetPrimitiveType2() << L"] !" << endl;

		PrintLineSeparator();

		// Pouzije sa COPY INITIALIZATION.
		CDefaultInitialization								LocalObject4{LocalObject3};

		wcout << L"LocalObject4 - MObject1 [" << LocalObject4.GetObject1().GetValue() << L"] !" << endl;
		wcout << L"LocalObject4 - MObject2 [" << LocalObject4.GetObject2().GetValue() << L"] !" << endl;
		wcout << L"LocalObject4 - MPrimitiveType1 [" << LocalObject4.GetPrimitiveType1() << L"] !" << endl;
		wcout << L"LocalObject4 - MPrimitiveType2 [" << LocalObject4.GetPrimitiveType2() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultConstructor(void)
{
	PrintLineSeparator();

	// Pre VARIABLE sa NEVOLA ZIADNY CONSTRUCTOR.
	int															Value1;

	// !!! COMPILER hodi ERROR, pretoze VARIABLE 'Value1' je NENAICIALIZOVANA.
	//wcout << L"Value1 [" << Value1 << L"] !" << endl;

	Value1=100;

	wcout << L"Value1 [" << Value1 << L"] !" << endl;

	PrintLineSeparator();

	// Pre VARIABLE sa VOLA DEFAULT CONSTRUCTOR.
	int															Value2{};

	wcout << L"Value2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	// Pre VARIABLE sa NEVOLA ZIADNY CONSTRUCTOR.
	int*														Value3=new int;

	wcout << L"Value3 [" << *Value3 << L"] !" << endl;

	delete(Value3);

	PrintLineSeparator();

	// Pre VARIABLE sa VOLA DEFAULT CONSTRUCTOR.
	int*														Value4=new int{};

	wcout << L"Value4 [" << *Value4 << L"] !" << endl;

	delete(Value4);

	PrintLineSeparator();

	// CONST VARIABLES MUSIA byt INITIALIZED.
	const int													Value5=100;

	wcout << L"Value5 [" << Value5 << L"] !" << endl;

	PrintLineSeparator();

	// CONST VARIABLES MUSIA byt INITIALIZED.
	int&														Value6=Value2;

	wcout << L"Value6 [" << Value6 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInitializerListConstructor(void)
{
	PrintLineSeparator();

	{
		CInitializerListConstructor								Object({10.5,12.4,7.8});

		PrintLineSeparator();

		for(double Value : Object.GetField())
		{
			wcout << L"VALUE [" << Value << L"] !" << endl;
		}

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// !!! ITEMS v OBJECT [initializer_list<T>] MUSIA byt HOMOGENNE. To znaci, ze musia byt ROVNAKEHO, alebo KONVERTOVATELNEHO TYPE.
		CInitializerListConstructor								Object({10,12,7});

		PrintLineSeparator();

		for(double Value : Object.GetField())
		{
			wcout << L"VALUE [" << Value << L"] !" << endl;
		}

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// !!! Aj ked pocet a typ PARAMETERS zodpoveda PARAMETRIZED CONSTRUCTOR, C++ pri pouziti SYNTAXE [{}], uprednostni INITIALIZER LIST CONSTRUCTOR.
		CInitializerListConstructor								Object({10.5,12.4});

		PrintLineSeparator();

		for(double Value : Object.GetField())
		{
			wcout << L"VALUE [" << Value << L"] !" << endl;
		}

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// !!! Pri pouziti SYNTAXE [()] sa uprednostni PARAMETRIZED CONSTRUCTOR pred INITIALIZER LIST CONSTRUCTOR.
		CInitializerListConstructor								Object(10.5,12.4);

		PrintLineSeparator();

		for(double Value : Object.GetField())
		{
			wcout << L"VALUE [" << Value << L"] !" << endl;
		}

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// !!! Uprednostni sa DEFAULT CONSTRUCTOR pred INITIALIZER LIST CONSTRUCTOR.
		CInitializerListConstructor								Object{};

		PrintLineSeparator();

		for(double Value : Object.GetField())
		{
			wcout << L"VALUE [" << Value << L"] !" << endl;
		}

		PrintLineSeparator();

		// Priradenie pomocou INITIALIZER LIST.
		Object={123.456,456.123};

		PrintLineSeparator();

		for(double Value : Object.GetField())
		{
			wcout << L"VALUE [" << Value << L"] !" << endl;
		}

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMemberInitializerList(void)
{
	PrintLineSeparator();

	{
		CMemberInitializerListDerived							Object(100,200,300,400,500);

		PrintLineSeparator();

		wcout << L"VALUE ValueBase1 [" << Object.GetValueBase1() << L"] !" << endl;
		wcout << L"VALUE ValueBase2 [" << Object.GetValueBase2() << L"] !" << endl;
		wcout << L"VALUE ConstField [" << Object.GetConstField().GetValue() << L"] !" << endl;
		wcout << L"VALUE Field1 [" << Object.GetField1().GetValue() << L"] !" << endl;
		wcout << L"VALUE Field2 [" << Object.GetField2().GetValue() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDelegatingConstructor(void)
{
	PrintLineSeparator();

	{
		// Vola sa DELEGATING CONSTRUCTOR.
		CDelegatingConstructor									Object;

		PrintLineSeparator();

		wcout << L"VALUE Value1 [" << Object.GetValue1() << L"] !" << endl;
		wcout << L"VALUE Value2 [" << Object.GetValue2() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// Vola sa DELEGATING CONSTRUCTOR.
		CDelegatingConstructor									Object(100);

		PrintLineSeparator();

		wcout << L"VALUE Value1 [" << Object.GetValue1() << L"] !" << endl;
		wcout << L"VALUE Value2 [" << Object.GetValue2() << L"] !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	{
		// Vola sa NON-DELEGATING CONSTRUCTOR.
		CDelegatingConstructor									Object(100,200);

		PrintLineSeparator();

		wcout << L"VALUE Value1 [" << Object.GetValue1() << L"] !" << endl;
		wcout << L"VALUE Value2 [" << Object.GetValue2() << L"] !" << endl;

		PrintLineSeparator();
	}

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
void TestStaticMemberInitializers(void)
{
	PrintLineSeparator();

	wcout << L"VALUE CStaticMembersInitializers::MValue1 [" << CStaticMembersInitializers::GetValue1() << L"] !" << endl;
	wcout << L"VALUE CStaticMembersInitializers::MValue2 [" << int(CStaticMembersInitializers::GetValue2()) << L"] !" << endl;
	wcout << L"VALUE CStaticMembersInitializers::MValue3 [" << CStaticMembersInitializers::GetValue3() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopyOperations(void)
{
	PrintLineSeparator();

	{
		int														Array1[3]{10,20,30};
		int														Array2[5]{10,20,30,40,50};

		CCopyOperations											Object1(Array1,3);

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa COPY CONSTRUCTOR.
		CCopyOperations											Object2(Object1);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		CCopyOperations											Object3(Array2,5);

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa COPY OPERATOR=.
		Object2=Object3;

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopyOperationsClassHierarchy(void)
{
	PrintLineSeparator();

	{
		CClassHierarchyDerived									Object1(110,210,310,410,510,610,710,810);

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa COPY CONSTRUCTOR.
		CClassHierarchyDerived									Object2(Object1);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		CClassHierarchyDerived									Object3(120,220,320,420,520,620,720,820);

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa COPY OPERATOR=.
		Object2=Object3;

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMoveOperations(void)
{
	PrintLineSeparator();

	{
		int														Array1[3]{10,20,30};
		int														Array2[5]{10,20,30,40,50};

		CMoveOperations											Object1(Array1,3);

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa MOVE CONSTRUCTOR.
		CMoveOperations											Object2(std::move(Object1));

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		CMoveOperations											Object3(Array2,5);

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa MOVE OPERATOR=.
		Object2=std::move(Object3);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMoveOperationsClassHierarchy(void)
{
	PrintLineSeparator();

	wstring														StringA1(L"A A");
	wstring														StringA2(L"A BB");
	wstring														StringA3(L"A CCC");
	wstring														StringA4(L"A DDDD");
	wstring														StringA5(L"A EEEEE");
	wstring														StringA6(L"A FFFFFF");
	wstring														StringA7(L"A GGGGGGG");
	wstring														StringA8(L"A HHHHHHHH");

	wstring														StringB1(L"BB A");
	wstring														StringB2(L"BB BB");
	wstring														StringB3(L"BB CCC");
	wstring														StringB4(L"BB DDDD");
	wstring														StringB5(L"BB EEEEE");
	wstring														StringB6(L"BB FFFFFF");
	wstring														StringB7(L"BB GGGGGGG");
	wstring														StringB8(L"BB HHHHHHHH");

	{
		CMoveOperationDerived									Object1(StringA1.c_str(),StringA1.size(),StringA2.c_str(),StringA2.size(),StringA3.c_str(),StringA3.size(),StringA4.c_str(),StringA4.size(),StringA5.c_str(),StringA5.size(),StringA6.c_str(),StringA6.size(),StringA7.c_str(),StringA7.size(),StringA8.c_str(),StringA8.size());

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		// Vola sa MOVE CONSTRUCTOR.
		CMoveOperationDerived									Object2(std::move(Object1));

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object1.Print(L"Object1");

		PrintLineSeparator();

		CMoveOperationDerived									Object3(StringB1.c_str(),StringB1.size(),StringB2.c_str(),StringB2.size(),StringB3.c_str(),StringB3.size(),StringB4.c_str(),StringB4.size(),StringB5.c_str(),StringB5.size(),StringB6.c_str(),StringB6.size(),StringB7.c_str(),StringB7.size(),StringB8.c_str(),StringB8.size());

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();

		// Vola sa MOVE OPERATOR=.
		Object2=std::move(Object3);

		PrintLineSeparator();

		Object2.Print(L"Object2");

		PrintLineSeparator();

		Object3.Print(L"Object3");

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultOperationsGeneration(void)
{
	PrintLineSeparator();

	CDefaultOperationsGeneration								Object1(L"Timmy Anderson",12);

	Object1.Print(L"Object1");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED COPY CONSTRUCTOR.
	CDefaultOperationsGeneration								Object2(Object1);

	Object2.Print(L"Object2");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED MOVE CONSTRUCTOR.
	CDefaultOperationsGeneration								Object3(move(Object1));

	Object3.Print(L"Object3");
	Object1.Print(L"Object1");

	PrintLineSeparator();

	CDefaultOperationsGeneration								Object4;

	// !!! Vola sa DEFAULT GENERATED COPY OPERATOR=.
	Object4=Object3;

	Object4.Print(L"Object4");

	PrintLineSeparator();

	CDefaultOperationsGeneration								Object5;

	// !!! Vola sa DEFAULT GENERATED MOVE OPERATOR=.
	Object5=move(Object4);

	Object5.Print(L"Object5");
	Object4.Print(L"Object4");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultOperationsGenerationClassHierarchy(void)
{
	PrintLineSeparator();

	CDefaultOperationsGenerationDerived							Object1(L"Timmy Anderson",12,L"Jenny Thompson",13);

	Object1.Print(L"Object1");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED COPY CONSTRUCTOR.
	CDefaultOperationsGenerationDerived							Object2(Object1);

	Object2.Print(L"Object2");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED MOVE CONSTRUCTOR.
	CDefaultOperationsGenerationDerived							Object3(move(Object1));

	Object3.Print(L"Object3");
	Object1.Print(L"Object1");

	PrintLineSeparator();

	CDefaultOperationsGenerationDerived							Object4;

	// !!! Vola sa DEFAULT GENERATED COPY OPERATOR=.
	Object4=Object3;

	Object4.Print(L"Object4");

	PrintLineSeparator();

	CDefaultOperationsGenerationDerived							Object5;

	// !!! Vola sa DEFAULT GENERATED MOVE OPERATOR=.
	Object5=move(Object4);

	Object5.Print(L"Object5");
	Object4.Print(L"Object4");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultOperationsForcedGeneration(void)
{
	PrintLineSeparator();

	CDefaultOperationsForcedGeneration							Object1(L"Timmy Anderson",12);

	Object1.Print(L"Object1");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED COPY CONSTRUCTOR.
	CDefaultOperationsForcedGeneration							Object2(Object1);

	Object2.Print(L"Object2");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED MOVE CONSTRUCTOR.
	CDefaultOperationsForcedGeneration							Object3(move(Object1));

	Object3.Print(L"Object3");
	Object1.Print(L"Object1");

	PrintLineSeparator();

	CDefaultOperationsForcedGeneration							Object4;

	// !!! Vola sa DEFAULT GENERATED COPY OPERATOR=.
	Object4=Object3;

	Object4.Print(L"Object4");

	PrintLineSeparator();

	CDefaultOperationsForcedGeneration							Object5;

	// !!! Vola sa DEFAULT GENERATED MOVE OPERATOR=.
	Object5=move(Object4);

	Object5.Print(L"Object5");
	Object4.Print(L"Object4");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultOperationsForcedGenerationClassHierarchy(void)
{
	PrintLineSeparator();

	CDefaultOperationsForcedGenerationDerived					Object1(L"Timmy Anderson",12,L"Jenny Thompson",13);

	Object1.Print(L"Object1");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED COPY CONSTRUCTOR.
	CDefaultOperationsForcedGenerationDerived					Object2(Object1);

	Object2.Print(L"Object2");

	PrintLineSeparator();

	// !!! Vola sa DEFAULT GENERATED MOVE CONSTRUCTOR.
	CDefaultOperationsForcedGenerationDerived					Object3(move(Object1));

	Object3.Print(L"Object3");
	Object1.Print(L"Object1");

	PrintLineSeparator();

	CDefaultOperationsForcedGenerationDerived					Object4;

	// !!! Vola sa DEFAULT GENERATED COPY OPERATOR=.
	Object4=Object3;

	Object4.Print(L"Object4");

	PrintLineSeparator();

	CDefaultOperationsForcedGenerationDerived					Object5;

	// !!! Vola sa DEFAULT GENERATED MOVE OPERATOR=.
	Object5=move(Object4);

	Object5.Print(L"Object5");
	Object4.Print(L"Object4");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDefaultConstructorGeneration(void)
{
	PrintLineSeparator();

	// !!! GENERATED DEFAULT CONSTRUCTOR ponechava FIELDS PRIMITIVE TYPES NENAINICIALIZOVANE.
	CDefaultConstructorGeneration								Object;

	Object.Print(L"Object");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDeletedDefaultOperations(void)
{
	PrintLineSeparator();

	CDeletedDefaultOperations									Object1(L"Timmy Anderson",12);

	Object1.Print(L"Object1");

	PrintLineSeparator();

	/*
	// !!! Vola sa DEFAULT GENERATED COPY CONSTRUCTOR.
	CDeletedDefaultOperations									Object2(Object1);

	Object2.Print(L"Object2");

	PrintLineSeparator();
	*/

	// !!! Vola sa DEFAULT GENERATED MOVE CONSTRUCTOR.
	CDeletedDefaultOperations									Object3(move(Object1));

	Object3.Print(L"Object3");
	Object1.Print(L"Object1");

	PrintLineSeparator();

	/*
	CDeletedDefaultOperations									Object4;

	// !!! Kedze DEFAULT COPY OPERATOR= bol DELETED, nasledujuci CODE hodi COMPILATION ERROR.
	Object4=Object3;

	Object4.Print(L"Object4");

	PrintLineSeparator();
	*/

	CDeletedDefaultOperations									Object5;

	// !!! Vola sa DEFAULT GENERATED MOVE OPERATOR=.
	Object5=move(Object3);

	Object5.Print(L"Object5");
	Object3.Print(L"Object3");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDeletedMethods(void)
{
	PrintLineSeparator();

	CDeletedMethods												Object;

	Object.Overload1(10);

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze METHOD Overload2() s INT PARAMETER je DELETED METHOD.
	//Object.Overload2(10);

	Object.Overload2(10.5);

	PrintLineSeparator();

	// !!! COMPILER hodi ERROR, pretoze OPERATOR() s INT PARAMETER je DELETED OPERATOR.
	//Object(10);

	Object(10.5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestConstructorDestructor();
	//TestExceptionInConstructor();
	//TestDestructorFunctionCall();
	//TestConstructorDestructorCallOrder();
	//TestFieldConstructorDestructorCallOrder();
	//TestPlacementNew();
	//TestVirtualNonVirtualDestructor();
	//TestNonConstructor();
	//TestDefaultConstructor();
	//TestInitializerListConstructor();
	//TestMemberInitializerList();
	//TestDelegatingConstructor();
	//TestInClassInitializers();
	//TestStaticMemberInitializers();
	//TestCopyOperations();
	//TestCopyOperationsClassHierarchy();
	//TestMoveOperations();
	//TestMoveOperationsClassHierarchy();
	//TestDefaultOperationsGeneration();
	//TestDefaultOperationsGenerationClassHierarchy();
	//TestDefaultOperationsForcedGeneration();
	//TestDefaultOperationsForcedGenerationClassHierarchy();
	//TestDefaultConstructorGeneration();
	//TestDeletedDefaultOperations();
	TestDeletedMethods();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------