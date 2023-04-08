//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <string>
#include <utility>
#include <functional>
#include "MyDebug.h"
#include "CClass.h"
#include "CClassWithMethods.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
void TestSimpleLambdaExpressions(void)
{
	PrintLineSeparator();

	// Definovanie a okamzite volanie LAMBDA EXPRESSION.
	[]
	{
		wcout << L"LAMBDA 1 CALLED !" << endl;
	}();

	// LAMBDA EXPRESSION moze byt priradena do LOCAL VARIABLE.
	auto														Lambda1=[]{wcout << L"LAMBDA 2 CALLED !" << endl;};

	Lambda1();

	// LAMBDA EXPRESSION moze mat PARAMETERS.
	auto														Lambda2=[](wstring Value){wcout << L"LAMBDA 3 CALLED with PARAMETER [" << Value << L"] !" << endl;};

	Lambda2(L"Timmy Anderson");

	// LAMBDA EXPRESSION vracia RETURN VALUE, ktorej TYPE si C++ sam odvodi.
	auto														Lambda3=[](int Value1, int Value2){return(Value1+Value2);};

	wcout << L"LAMBDA EXPRESSION RESULT [" << Lambda3(10,20) << L"] !" << endl;

	// !!! LAMBDA EXPRESSION vracia RETURN VALUE, ktorej TYPE je EXPLICITNE definovany.
	auto														Lambda4=[](int Value1, int Value2) -> double {return(Value1+Value2);};
	double														Result1=Lambda4(10,20);

	wcout << L"LAMBDA EXPRESSION RESULT [" << Result1 << L"] !" << endl;

	// !!! LAMBDA EXPRESSION vracia RETURN VALUE, ktorej TYPE je EXPLICITNE definovany.
	// !!! Zaroven je pouzity KEYWORD [noexcept].
	auto														Lambda5=[](int Value1, int Value2) noexcept -> double {return(Value1+Value2);};
	double														Result2=Lambda5(10,20);

	wcout << L"LAMBDA EXPRESSION RESULT [" << Result2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaExpressionsWithOuterScope1(void)
{
	PrintLineSeparator();

	wstring														Value1=L"DEFAULT";
	wstring														Value2=L"DEFAULT";

	auto														Lambda=[Value1,&Value2]
	{
		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

		// COMPILER hodi ERROR, pretoze NIE je mozne zapisovat do VARIABLE prenesenej BY-VALUE.
		//Value1=L"CHANGED in LAMBDA EXPRESSION";

		// Tento CODE prebehne OK, pretoze do VARIABLE prenesenej BY-REFERENCE je mozne zapisovat.
		Value2=L"CHANGED in LAMBDA EXPRESSION";

		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	};

	Value1=L"CHANGED in FUNCTION";
	Value2=L"CHANGED in FUNCTION";

	// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-VALUE, jej hodnota sa prenasa v case DEFINICIE LAMBDA EXPRESSION.
	// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
	Lambda();

	PrintLineSeparator();

	// !!! Hodnota [Value1] bude NEZMENENA, pretoze sa preniesla BY-VALUE a tym padom NEMOHLA byt modifikovana v LAMBDA FUNCTION.
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	// !!! Hodnota [Value2] bude ZMENENA, pretoze sa preniesla BY-REFERENCE a bola zmenena v LAMBDA FUNCTION.
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaExpressionsWithOuterScope2(void)
{
	PrintLineSeparator();

	wstring														Value1=L"DEFAULT";
	wstring														Value2=L"DEFAULT";

	// !!! VSETKY LOCAL VARIABLES su prenesene BY-VALUE.
	auto														Lambda=[=]
	{
		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

		// COMPILER hodi ERROR, pretoze NIE je mozne zapisovat do VARIABLE prenesenej BY-VALUE.
		//Value1=L"CHANGED in LAMBDA EXPRESSION";

		// COMPILER hodi ERROR, pretoze NIE je mozne zapisovat do VARIABLE prenesenej BY-VALUE.
		//Value2=L"CHANGED in LAMBDA EXPRESSION";

		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	};

	Value1=L"CHANGED in FUNCTION";
	Value2=L"CHANGED in FUNCTION";

	// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-VALUE, jej hodnota sa prenasa v case DEFINICIE LAMBDA EXPRESSION.
	// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-VALUE, jej hodnota sa prenasa v case DEFINICIE LAMBDA EXPRESSION.
	Lambda();

	PrintLineSeparator();

	// !!! Hodnota [Value1] bude NEZMENENA, pretoze sa preniesla BY-VALUE a tym padom NEMOHLA byt modifikovana v LAMBDA FUNCTION.
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	// !!! Hodnota [Value2] bude NEZMENENA, pretoze sa preniesla BY-VALUE a tym padom NEMOHLA byt modifikovana v LAMBDA FUNCTION.
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaExpressionsWithOuterScope3(void)
{
	PrintLineSeparator();

	wstring														Value1=L"DEFAULT";
	wstring														Value2=L"DEFAULT";

	// !!! VSETKY LOCAL VARIABLES su prenesene BY-REFERENCE.
	auto														Lambda=[&]
	{
		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

		// Tento CODE prebehne OK, pretoze do VARIABLE prenesenej BY-REFERENCE je mozne zapisovat.
		Value1=L"CHANGED in LAMBDA EXPRESSION";

		// Tento CODE prebehne OK, pretoze do VARIABLE prenesenej BY-REFERENCE je mozne zapisovat.
		Value2=L"CHANGED in LAMBDA EXPRESSION";

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	};

	Value1=L"CHANGED in FUNCTION";
	Value2=L"CHANGED in FUNCTION";

	// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
	// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
	Lambda();

	PrintLineSeparator();

	// !!! Hodnota [Value1] bude ZMENENA, pretoze sa preniesla BY-REFERENCE a bola zmenena v LAMBDA FUNCTION.
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	// !!! Hodnota [Value2] bude ZMENENA, pretoze sa preniesla BY-REFERENCE a bola zmenena v LAMBDA FUNCTION.
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaExpressionsWithOuterScopeInClass1(void)
{
	PrintLineSeparator();

	CClass														Class;

	Class.TestLambdaExpressionsWithOuterScope1();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaExpressionsWithOuterScopeInClass2(void)
{
	PrintLineSeparator();

	CClass														Class;

	Class.TestLambdaExpressionsWithOuterScope2();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaExpressionsWithOuterScopeInClass3(void)
{
	PrintLineSeparator();

	CClass														Class;

	Class.TestLambdaExpressionsWithOuterScope3();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLambdaExpressionsWithOuterScopeInClass4(void)
{
	PrintLineSeparator();

	CClass														Class;

	Class.TestLambdaExpressionsWithOuterScope4();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMutable1(void)
{
	PrintLineSeparator();

	wstring														Value1=L"DEFAULT";
	wstring														Value2=L"DEFAULT";

	// !!!!! KEYWORD MUTABLE sposobi, ze VSETKY LOCAL VARIABLES su MODIFIKOVATELNE.
	// !!!!! Zaroven sa vsak ZMENY v LAMBDA EXPRESSION NEPRENESU do OUTER SCOPE.
	auto														Lambda=[Value1,&Value2]() mutable
	{
		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

		// !!! Tento CODE prebehne OK, pretoze aj ked VARIABLE je prenesena BY-VALUE, tak vdaka pouzitiu KEYWORD [mutable] je to nej mozne zapisovat.
		Value1=L"CHANGED in LAMBDA EXPRESSION";

		// Tento CODE prebehne OK, pretoze do VARIABLE prenesenej BY-REFERENCE je mozne zapisovat.
		Value2=L"CHANGED in LAMBDA EXPRESSION";

		wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
		wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;
	};

	Value1=L"CHANGED in FUNCTION";
	Value2=L"CHANGED in FUNCTION";

	// !!!!! Kedze VARIABLE [Value1] sa prenasa BY-VALUE, jej hodnota sa prenasa v case DEFINICIE LAMBDA EXPRESSION.
	// !!!!! Kedze VARIABLE [Value2] sa prenasa BY-REFERENCE, jej hodnota sa prenasa v case VOLANIA LAMBDA EXPRESSION.
	Lambda();

	PrintLineSeparator();

	// !!!!! Hodnota [Value1] bude NEZMENENA, pretoze sa preniesla BY-VALUE a hoci vdaka pouzitiu KEYWORD [mutable] BOLA zmenena v LAMBDA FUNCTION, tato zmena sa NEPRENIESLA do OUTER SCOPE.
	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	// !!! Hodnota [Value2] bude ZMENENA, pretoze sa preniesla BY-REFERENCE a bola zmenena v LAMBDA FUNCTION.
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMutable2(void)
{
	PrintLineSeparator();

	CClassWithMethods											Class1;
	CClassWithMethods											Class2;
	CClassWithMethods											Class3;

	// !!! Pre [Class1] sa vola COPY CONSTRUCTOR.
	auto														Lambda1=[Class1]()
	{
		// !!! Kedze [Class] sa preniesla BY-VALUE, NIE JE mozne volat NON-CONST MEMBERS.
		//Class1.NonConstMethod();

		Class1.ConstMethod();
	};

	Lambda1();
	Class1.PrintValue();

	PrintLineSeparator();

	auto														Lambda2=[&Class2]()
	{
		// !!! Kedze [Class] sa preniesla BY-REFERENCE, JE mozne volat NON-CONST MEMBERS.
		Class2.NonConstMethod();

		Class2.ConstMethod();
	};

	Lambda2();
	Class2.PrintValue();

	PrintLineSeparator();

	// !!! Pre [Class3] sa vola COPY CONSTRUCTOR.
	auto														Lambda3=[Class3]() mutable
	{
		// !!! Aj ked sa [Class] sa preniesla BY-VALUE, JE mozne volat NON-CONST MEMBERS, pretoze sa pouzil KEYWORD [mutable].
		Class3.NonConstMethod();

		Class3.ConstMethod();
	};

	Lambda3();
	Class3.PrintValue();

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestExceptions(void)
{
	PrintLineSeparator();

	try
	{
		auto														Lambda=[]
		{
			throw(wstring(L"EXCEPTION from LAMBDA FUNCTION !"));
		};

		Lambda();
	}
	catch(const wstring& E)
	{
		wcout << L"EXCEPTION [" << E << L"] !" << endl;
	}

	/*
	PrintLineSeparator();

	try
	{
		// !!! LAMBDA EXPRESSION NESMIE hodit EXCEPTION, pretoze sa pouzil KEYWORD [noexcept].
		// !!!!! Kedze vsak LAMBDA EXPRESSION hodi EXCEPTION, dojde k PADU PROGRAMU.
		auto														Lambda=[] () noexcept
		{
			throw(wstring(L"EXCEPTION from LAMBDA FUNCTION !"));
		};

		// !!! Sposobi PAD PROGRAMU.
		Lambda();
	}
	catch(const wstring& E)
	{
		wcout << L"EXCEPTION [" << E << L"] !" << endl;
	}
	*/

	PrintLineSeparator();

	try
	{
		// !!! LAMBDA EXPRESSION MOZE hodit EXCEPTION, pretoze EXCEPTION CONDITION je FALSE, co znaci, ze NIKDY nenastane situacia za ktorej by LAMBDA EXPRESSION nemohla hodit EXCEPTION.
		auto														Lambda=[] () noexcept(false)
		{
			throw(wstring(L"EXCEPTION from LAMBDA FUNCTION !"));
		};

		Lambda();
	}
	catch(const wstring& E)
	{
		wcout << L"EXCEPTION [" << E << L"] !" << endl;
	}

	PrintLineSeparator();

	const bool														CanNotThrowException=sizeof(int)>10;

	try
	{
		// !!! LAMBDA EXPRESSION MOZE hodit EXCEPTION, pretoze [CanNotThrowException==FALSE].
		auto														Lambda=[] () noexcept(CanNotThrowException)
		{
			throw(wstring(L"EXCEPTION from LAMBDA FUNCTION !"));
		};

		Lambda();
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
void TestLambdaExpressionType(void)
{
	PrintLineSeparator();

	auto														Lambda1=[]{wcout << L"LAMBDA 1 CALLED !" << endl;};
	auto														Lambda2=[]{wcout << L"LAMBDA 1 CALLED !" << endl;};
	auto														Lambda3=[](int Value1, int Value2) -> double {return(Value1+Value2);};

	// !!! Mena su MANGLED.
	wcout << "LAMBDA 1 TYPE [" << ConvertStringToWideString(typeid(Lambda1).name()) << L"] !" << endl;
	wcout << "LAMBDA 2 TYPE [" << ConvertStringToWideString(typeid(Lambda2).name()) << L"] !" << endl;
	wcout << "LAMBDA 3 TYPE [" << ConvertStringToWideString(typeid(Lambda3).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! LAMBDA EXPRESSIONS je mozne konverovat na CLASS [function].
function<int(int,int)> ReturnLambdaExpression1(void)
{
	int															Value=100;
	function<int(int,int)>										LambdaExpression=[Value](int Value1, int Value2) -> int {return(Value1+Value2+Value);};

	return(LambdaExpression);
}
//-----------------------------------------------------------------------------
// !!!!! LAMBDA EXPRESSIONS je mozne konverovat na CLASS [function].
function<int(int,int)> ReturnLambdaExpression2(void)
{
	// Hodnotu 100 IGNORUJE a ta sa NEPRENESIE do LAMBDA FUNCTION, a namiesto nej bude [Value=0].
	int															Value=123;
	function<int(int,int)>										LambdaExpression=[&Value](int Value1, int Value2) -> int
	{
		wcout << L"VALUE [" << Value << L"] !" << endl;

		Value+=10; 
		
		wcout << L"VALUE [" << Value << L"] !" << endl;

		return(Value1+Value2+Value);
	};

	return(LambdaExpression);
}
//-----------------------------------------------------------------------------
void TestReturnLambdaExpression(void)
{
	PrintLineSeparator();

	function<int(int,int)>										LambdaExpression1=ReturnLambdaExpression1();
	int															Result1=LambdaExpression1(10,20);

	wcout << L"RESULT 1 [" << Result1 << L"] !" << endl;

	PrintLineSeparator();

	function<int(int,int)>										LambdaExpression2=ReturnLambdaExpression2();
	int															Result2=LambdaExpression2(10,20);

	wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSimpleLambdaExpressions();
	//TestLambdaExpressionsWithOuterScope1();
	//TestLambdaExpressionsWithOuterScope2();
	//TestLambdaExpressionsWithOuterScope3();
	//TestLambdaExpressionsWithOuterScopeInClass1();
	//TestLambdaExpressionsWithOuterScopeInClass2();
	//TestLambdaExpressionsWithOuterScopeInClass3();
	//TestMutable1();
	//TestMutable2();
	TestExceptions();
	//TestLambdaExpressionType();
	//TestReturnLambdaExpression();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------