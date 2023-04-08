//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <iostream>
#include <tuple>
#include <string>
#include <functional>
#include <sstream>
#include "MyDebug.h"
#include "CTuple.h"
#include "CPrintTuple.h"
#include "PrintHelper.h"
#include "SPrintHelper.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
void TestSimplePairs(void)
{
	PrintLineSeparator();

	pair<wstring,int>											Pair(L"Timmy Anderson",12);

	wcout << L"VALUE 1 [" << Pair.first << L"], VALUE 2 [" << Pair.second << L"] !" << endl;
	wcout << L"VALUE 1 [" << get<0>(Pair) << L"], VALUE 2 [" << get<1>(Pair) << L"] !" << endl;

	wcout << L"TUPLE SIZE [" << tuple_size<pair<wstring,int>>::value << L"] !" << endl;

	wcout << L"TYPE 1 [" << ConvertStringToWideString(typeid(tuple_element<0,pair<wstring,int>>::type).name()) << L"], TYPE 2 [" << ConvertStringToWideString(typeid(tuple_element<1,pair<wstring,int>>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPiecewiseConstructor(void)
{
	PrintLineSeparator();

	tuple<wstring,wstring,int>									Pair1(L"Timmy",L"Anderson",12);
	tuple<wstring,int>											Pair2(L"Jenny Thompson",13);

	// !!!!! CONSTRUCTOR rozbali FIELDS z CLASS [tuple<T...>] a vytvori z nich CLASS [CTuple<T...>] pre OBE PAIR FIELDS.
	pair<CTuple<wstring,wstring,int>,CTuple<wstring,int>>		PiecewisePair(piecewise_construct,Pair1,Pair2);

	PrintLineSeparator();

	wcout << L"FIRST [" << PiecewisePair.first.GetItem<0>() << L"," << PiecewisePair.first.GetItem<1>() << L"," << PiecewisePair.first.GetItem<2>() << L"] !" << endl;
	wcout << L"SECOND [" << PiecewisePair.second.GetItem<0>() << L"," << PiecewisePair.second.GetItem<1>() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMakePair(void)
{
	PrintLineSeparator();

	pair<wstring,int>											Pair1(L"Timmy Anderson",12);
	pair<wstring,int>											Pair2=make_pair(L"Timmy Anderson",12);

	// FUNCTION make_pair() DEDUKUJE PARAMETERS daneho PAIR.
	auto														Pair3=make_pair(L"Timmy Anderson",12);

	wcout << L"VALUE 1 [" << Pair1.first << L"], VALUE 2 [" << Pair1.second << L"] !" << endl;
	wcout << L"VALUE 1 [" << Pair2.first << L"], VALUE 2 [" << Pair2.second << L"] !" << endl;
	// FIELD [first] ma TYPE [const wchar*] a NIE TYPE [wstring].
	wcout << L"VALUE 1 [" << Pair3.first << L"], VALUE 2 [" << Pair3.second << L"] !" << endl;

	PrintLineSeparator();

	wstring														Name=L"Timmy Anderson";
	int															Age=12;

	// STRUCTURE [pair<T1,T2>] moze obsahovat aj REFERENCES.
	// !!! FUNCTION ref() prinuti COMPILER generovat PAIR, ktory bude mat REFERENCES na VALUES, namiesto VALUES.
	auto														Pair4=make_pair(ref(Name),ref(Age));

	wcout << L"BEFORE - Name [" << Name << L"], Age [" << Age << L"] !" << endl;
	wcout << L"BEFORE - VALUE 1 [" << Pair4.first << L"], VALUE 2 [" << Pair4.second << L"] !" << endl;
	
	// !!!!! Kedze PAIR 4 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	Pair4.first=L"Jenny Thompson";
	Pair4.second=13;

	// !!! Hodnoty 'Name' a 'Age' su ZMENENE.
	wcout << L"AFTER - Name [" << Name << L"], Age [" << Age << L"] !" << endl;
	wcout << L"AFTER - VALUE 1 [" << Pair4.first << L"], VALUE 2 [" << Pair4.second << L"] !" << endl;

	PrintLineSeparator();

	int															X=10;
	int															Y=20;

	// STRUCTURE [pair<T1,T2>] moze obsahovat aj REFERENCES.
	pair<int&,int&>												Pair5=make_pair(ref(X),ref(Y));

	wcout << L"BEFORE - X [" << X << L"], Y [" << Y << L"] !" << endl;
	wcout << L"BEFORE - VALUE 1 [" << Pair5.first << L"], VALUE 2 [" << Pair5.second << L"] !" << endl;

	// !!!!! Kedze PAIR 5 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	Pair5.first+=4;
	Pair5.second+=6;

	// !!! Hodnoty 'X' a 'Y' su ZMENENE.
	wcout << L"AFTER - X [" << X << L"], Y [" << Y << L"] !" << endl;
	wcout << L"AFTER - VALUE 1 [" << Pair5.first << L"], VALUE 2 [" << Pair5.second << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPairOperators(void)
{
	PrintLineSeparator();

	pair<int,double>											Pair1(12,14.5);
	pair<int,double>											Pair2(13,7.2);
	pair<int,double>											Pair3(13,4.3);
	pair<int,double>											Pair4(10,4.3);
	pair<int,double>											Pair5(10,4.3);

	wcout << L"PAIR(" << Pair1.first << L"," << Pair1.second << L") < PAIR(" << Pair2.first << L"," << Pair2.second << L") [" << ((Pair1<Pair2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"PAIR(" << Pair1.first << L"," << Pair1.second << L") < PAIR(" << Pair3.first << L"," << Pair3.second << L") [" << ((Pair1<Pair3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Porovnavaju sa VALUES [first] a ak su rovne, tak aj VALUES [second].
	wcout << L"PAIR(" << Pair2.first << L"," << Pair2.second << L") < PAIR(" << Pair3.first << L"," << Pair3.second << L") [" << ((Pair2<Pair3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"PAIR(" << Pair3.first << L"," << Pair3.second << L") < PAIR(" << Pair4.first << L"," << Pair4.second << L") [" << ((Pair3<Pair4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"PAIR(" << Pair4.first << L"," << Pair4.second << L") < PAIR(" << Pair5.first << L"," << Pair5.second << L") [" << ((Pair4<Pair5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"PAIR(" << Pair4.first << L"," << Pair4.second << L") <= PAIR(" << Pair5.first << L"," << Pair5.second << L") [" << ((Pair4<=Pair5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"PAIR(" << Pair4.first << L"," << Pair4.second << L") == PAIR(" << Pair5.first << L"," << Pair5.second << L") [" << ((Pair4==Pair5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"PAIR(" << Pair4.first << L"," << Pair4.second << L") != PAIR(" << Pair5.first << L"," << Pair5.second << L") [" << ((Pair4!=Pair5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleTuples(void)
{
	PrintLineSeparator();

	tuple<wstring,wstring,int>									Tuple(L"Timmy",L"Anderson",12);

	wcout << L"VALUE 1 [" << get<0>(Tuple) << L"], VALUE 2 [" << get<1>(Tuple) << L"], VALUE 3 [" << get<2>(Tuple) << L"] !" << endl;

	wcout << L"TUPLE SIZE [" << tuple_size<tuple<wstring,wstring,int>>::value << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPE 1 [" << ConvertStringToWideString(typeid(tuple_element<0,tuple<wstring,wstring,int>>::type).name()) << L"], TYPE 2 [" << ConvertStringToWideString(typeid(tuple_element<1,tuple<wstring,wstring,int>>::type).name()) << L"], TYPE 3 [" << ConvertStringToWideString(typeid(tuple_element<2,tuple<wstring,wstring,int>>::type).name()) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pouzitie sa INITIALIZER LIST.
	tuple<wstring,wstring,int>									TupleInitialized{L"Timmy",L"Anderson",12};

	wcout << L"VALUE 1 [" << get<0>(TupleInitialized) << L"], VALUE 2 [" << get<1>(TupleInitialized) << L"], VALUE 3 [" << get<2>(TupleInitialized) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMakeTuple(void)
{
	PrintLineSeparator();

	tuple<wstring,int>											Tuple1(L"Timmy Anderson",12);
	tuple<wstring,int>											Tuple2=make_tuple(L"Timmy Anderson",12);

	// FUNCTION make_tuple() DEDUKUJE PARAMETERS daneho TUPLE.
	auto														Tuple3=make_tuple(L"Timmy Anderson",12);

	wcout << L"VALUE 1 [" << get<0>(Tuple1) << L"], VALUE 2 [" << get<1>(Tuple1) << L"] !" << endl;
	wcout << L"VALUE 1 [" << get<0>(Tuple2) << L"], VALUE 2 [" << get<1>(Tuple2) << L"] !" << endl;
	// 1. FIELD ma TYPE [const wchar*] a NIE TYPE [wstring].
	wcout << L"VALUE 1 [" << get<0>(Tuple3) << L"], VALUE 2 [" << get<1>(Tuple3) << L"] !" << endl;

	PrintLineSeparator();

	wstring														Name=L"Timmy Anderson";
	int															Age=12;

	// STRUCTURE [tuple<T...>] moze obsahovat aj REFERENCES.
	// !!! FUNCTION ref() prinuti COMPILER generovat TUPLE, ktory bude mat REFERENCES na VALUES, namiesto VALUES.
	auto														Tuple4=make_tuple(ref(Name),ref(Age));

	wcout << L"BEFORE - Name [" << Name << L"], Age [" << Age << L"] !" << endl;
	wcout << L"BEFORE - VALUE 1 [" << get<0>(Tuple4) << L"], VALUE 2 [" << get<1>(Tuple4) << L"] !" << endl;
	
	// !!!!! Kedze TUPLE 4 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple4)=L"Jenny Thompson";
	get<1>(Tuple4)=13;

	// !!! Hodnoty 'Name' a 'Age' su ZMENENE.
	wcout << L"AFTER - Name [" << Name << L"], Age [" << Age << L"] !" << endl;
	wcout << L"AFTER - VALUE 1 [" << get<0>(Tuple4) << L"], VALUE 2 [" << get<1>(Tuple4) << L"] !" << endl;

	PrintLineSeparator();

	int															X=10;
	int															Y=20;

	// CLASS [TUPLE<T...>] moze obsahovat aj REFERENCES.
	tuple<int&,int&>											Tuple5=make_tuple(ref(X),ref(Y));

	wcout << L"BEFORE - X [" << X << L"], Y [" << Y << L"] !" << endl;
	wcout << L"BEFORE - VALUE 1 [" << get<0>(Tuple5) << L"], VALUE 2 [" << get<1>(Tuple5) << L"] !" << endl;

	// !!!!! Kedze TUPLE 5 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple5)+=4;
	get<1>(Tuple5)+=6;

	// !!! Hodnoty 'X' a 'Y' su ZMENENE.
	wcout << L"AFTER - X [" << X << L"], Y [" << Y << L"] !" << endl;
	wcout << L"AFTER - VALUE 1 [" << get<0>(Tuple5) << L"], VALUE 2 [" << get<1>(Tuple5) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTie(void)
{
	PrintLineSeparator();

	wstring														Name=L"Timmy Anderson";
	int															Age=12;

	// STRUCTURE [tuple<T...>] moze obsahovat aj REFERENCES.
	// !!! FUNCTION tie() prinuti COMPILER generovat TUPLE, ktory bude mat REFERENCES na VALUES, namiesto VALUES.
	auto														Tuple1=tie(Name,Age);

	wcout << L"BEFORE - Name [" << Name << L"], Age [" << Age << L"] !" << endl;
	wcout << L"BEFORE - VALUE 1 [" << get<0>(Tuple1) << L"], VALUE 2 [" << get<1>(Tuple1) << L"] !" << endl;
	
	// !!!!! Kedze TUPLE 1 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple1)=L"Jenny Thompson";
	get<1>(Tuple1)=13;

	// !!! Hodnoty 'Name' a 'Age' su ZMENENE.
	wcout << L"AFTER - Name [" << Name << L"], Age [" << Age << L"] !" << endl;
	wcout << L"AFTER - VALUE 1 [" << get<0>(Tuple1) << L"], VALUE 2 [" << get<1>(Tuple1) << L"] !" << endl;

	PrintLineSeparator();

	int															X=10;
	int															Y=20;

	// !!! CLASS [TUPLE<T...>] moze obsahovat aj REFERENCES. FUNCTION tie() vytvara TUPLE, ktoreho VSETKY TYPE PARAMETERS su REFERENCES.
	tuple<int&,int&>											Tuple2=tie(X,Y);

	wcout << L"BEFORE - X [" << X << L"], Y [" << Y << L"] !" << endl;
	wcout << L"BEFORE - VALUE 1 [" << get<0>(Tuple2) << L"], VALUE 2 [" << get<1>(Tuple2) << L"] !" << endl;

	// !!!!! Kedze TUPLE 2 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple2)+=4;
	get<1>(Tuple2)+=6;

	// !!! Hodnoty 'X' a 'Y' su ZMENENE.
	wcout << L"AFTER - X [" << X << L"], Y [" << Y << L"] !" << endl;
	wcout << L"AFTER - VALUE 1 [" << get<0>(Tuple2) << L"], VALUE 2 [" << get<1>(Tuple2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTupleOperators(void)
{
	PrintLineSeparator();

	tuple<int,double>											Tuple1(12,14.5);
	tuple<int,double>											Tuple2(13,7.2);
	tuple<int,double>											Tuple3(13,4.3);
	tuple<int,double>											Tuple4(10,4.3);
	tuple<int,double>											Tuple5(10,4.3);

	wcout << L"TUPLE(" << get<0>(Tuple1) << L"," << get<1>(Tuple1) << L") < TUPLE(" << get<0>(Tuple2) << L"," << get<1>(Tuple2) << L") [" << ((Tuple1<Tuple2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"TUPLE(" << get<0>(Tuple1) << L"," << get<1>(Tuple1) << L") < TUPLE(" << get<0>(Tuple3) << L"," << get<1>(Tuple3) << L") [" << ((Tuple1<Tuple3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// Porovnavaju sa VALUES [first] a ak su rovne, tak aj VALUES [second].
	wcout << L"TUPLE(" << get<0>(Tuple2) << L"," << get<1>(Tuple2) << L") < TUPLE(" << get<0>(Tuple3) << L"," << get<1>(Tuple3) << L") [" << ((Tuple2<Tuple3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"TUPLE(" << get<0>(Tuple3) << L"," << get<1>(Tuple3) << L") < TUPLE(" << get<0>(Tuple4) << L"," << get<1>(Tuple4) << L") [" << ((Tuple3<Tuple4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"TUPLE(" << get<0>(Tuple4) << L"," << get<1>(Tuple4) << L") < TUPLE(" << get<0>(Tuple5) << L"," << get<1>(Tuple5) << L") [" << ((Tuple4<Tuple5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"TUPLE(" << get<0>(Tuple4) << L"," << get<1>(Tuple4) << L") <= TUPLE(" << get<0>(Tuple5) << L"," << get<1>(Tuple5) << L") [" << ((Tuple4<=Tuple5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"TUPLE(" << get<0>(Tuple4) << L"," << get<1>(Tuple4) << L") == TUPLE(" << get<0>(Tuple5) << L"," << get<1>(Tuple5) << L") [" << ((Tuple4==Tuple5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"TUPLE(" << get<0>(Tuple4) << L"," << get<1>(Tuple4) << L") != TUPLE(" << get<0>(Tuple5) << L"," << get<1>(Tuple5) << L") [" << ((Tuple4!=Tuple5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTupleCat(void)
{
	PrintLineSeparator();

	// !!! FUNCTION tuple_cat() vytvori TUPLE z dvoch TUPLES, ktory bude obsahovat 3 FIELDS.
	tuple<wstring,wstring,int>									Tuple=tuple_cat(tuple<wstring,wstring>(L"Timmy",L"Anderson"),tuple<int>(12));

	wcout << L"VALUE 1 [" << get<0>(Tuple) << L"], VALUE 2 [" << get<1>(Tuple) << L"], VALUE 3 [" << get<2>(Tuple) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPrintTuples(void)
{
	PrintLineSeparator();

	tuple<wstring,wstring,int>									Tuple=tuple_cat(tuple<wstring,wstring>(L"Timmy",L"Anderson"),tuple<int>(12));

	PrintTuple(wstring(L"TUPLE"),Tuple);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGenericPrint(void)
{
	PrintLineSeparator();

	try
	{
		GenericPrint(L"FIRST NAME [{}], LAST NAME [{}], AGE [{}] !\n",L"Timmy",L"Anderson",12);
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! OK - Definuju sa aj nejake formatovacie retazce, ktore vsak FUNCTION v tejto verzii IGNORUJE. Je to len ukazka, ako je mozne robit formatovanie.
		GenericPrint(L"FIRST NAME [{s}], LAST NAME [{ss}], AGE [{ddd}] !\n",L"Timmy",L"Anderson",12);
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! OK - Chyba CLOSING BRACKET. Nespravne vsak vypise STRING, pretoze predoklada, ze retazec '], AGE [{' je formatovaci retazec.
		GenericPrint(L"FIRST NAME [{}], LAST NAME [{], AGE [{}] !\n",L"Timmy",L"Anderson",12);
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! ERROR - Chyba CLOSING BRACKET.
		GenericPrint(L"FIRST NAME [{}], LAST NAME [{}], AGE [{] !\n",L"Timmy",L"Anderson",12);
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! ERROR - Za CLOSING BRACKET musi, ak nie je sucastou formatovacieho retazca musi nasledovat dalsi CLOSING BRACKET.
		GenericPrint(L"FIRST NAME [{}], LAST NAME [{}], AGE [{}] }!\n",L"Timmy",L"Anderson",12);
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! ERROR - CLOSING BRACKET je na konci.
		GenericPrint(L"FIRST NAME [{}], LAST NAME [{}], AGE [{}] !\n}",L"Timmy",L"Anderson",12);
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! ERROR - Prilis vela PARAMETERS.
		GenericPrint(L"FIRST NAME [{}], LAST NAME [{}], AGE [{}], XYZ [{}] !\n",L"Timmy",L"Anderson",12);
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGenericSPrint(void)
{
	PrintLineSeparator();

	try
	{
		wstring													String=GenericSPrint(L"FIRST NAME [{}], LAST NAME [{}], AGE [{}] !\n",L"Timmy",L"Anderson",12);

		wcout << String;
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		// !!! OK - Definuju sa aj nejake formatovacie retazce, ktore vsak FUNCTION v tejto verzii IGNORUJE. Je to len ukazka, ako je mozne robit formatovanie.
		wstring													String=GenericSPrint(L"FIRST NAME [{s}], LAST NAME [{ss}], AGE [{ddd}] !\n",L"Timmy",L"Anderson",12);

		wcout << String;
	}
	catch(const CException& E)
	{
		wcout << L"\nEXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPairToTuple(void)
{
	PrintLineSeparator();

	pair<wstring,int>											Pair(L"Timmy Anderson",12);

	// PAIR je mozne konvertovat na TUPLE s 2 FIELDS.
	tuple<wstring,int>											Tuple1=Pair;

	wcout << L"TUPLE - ITEM 1 [" << get<0>(Tuple1) << L"] ITEM 2 [" << get<1>(Tuple1) << L"] !" << endl;

	tuple<wstring,int>											Tuple2=Pair;

	// PAIR je mozne konvertovat na TUPLE s 2 FIELDS.
	Tuple2=Pair;

	wcout << L"TUPLE - ITEM 1 [" << get<0>(Tuple2) << L"] ITEM 2 [" << get<1>(Tuple2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSimplePairs();
	//TestPiecewiseConstructor();
	//TestMakePair();
	//TestPairOperators();
	//TestSimpleTuples();
	//TestMakeTuple();
	//TestTie();
	//TestTupleOperators();
	//TestTupleCat();
	//TestPrintTuples();
	//TestGenericPrint();
	//TestGenericSPrint();
	TestPairToTuple();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------