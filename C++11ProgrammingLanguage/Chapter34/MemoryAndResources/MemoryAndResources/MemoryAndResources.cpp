//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable:4996)
#endif
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>
#include <string>
#include <array>
#include <iostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <list>
#include <thread>
#include <deque>
#include <scoped_allocator>
#include "MyDebug.h"
#include "CInt.h"
#include "CTuple.h"
#include "CPrintTuple.h"
#include "CCustomClass.h"
#include "CBaseClass.h"
#include "CDerivedClass.h"
#include "CClassWithUniquePointers.h"
#include "CClassWithUniquePointersException.h"
#include "CCustomDeleteFuctionForUniquePointer.h"
#include "CBaseNonVirtual.h"
#include "CBaseVirtual.h"
#include "CDerivedNonVirtual.h"
#include "CDerivedVirtual.h"
#include "CErrorThisChildShared.h"
#include "CErrorThisParentShared.h"
#include "CSharedPointerOnThis.h"
#include "CSharedPointerOnThisError.h"
#include "CName.h"
#include "CCyclicReferencesShared1.h"
#include "CCyclicReferencesShared2.h"
#include "CCyclicReferencesWeak1.h"
#include "CCyclicReferencesWeak2.h"
#include "CMyAllocator.h"
#include "CMyAllocator1.h"
#include "CMyAllocator2.h"
#include "CMyAllocator3.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TCollection>
void PrintCollection(const wstring& Prefix, const TCollection& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const auto& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << Item;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayInitialization(void)
{
	PrintLineSeparator();

	// !!! ARRAY je NEINICAILIZOVANE. ITEMS obsahuju UNDEFINED VALUES.
	array<int,5>												Array1;

	PrintCollection(L"ARRAY 1",Array1);

	// !!! ARRAY je INICAILIZOVANE. ITEMS obsahuju 0.
	array<int,5>												Array2{};

	PrintCollection(L"ARRAY 2",Array2);

	array<int,5>												Array3{5,4,8};

	PrintCollection(L"ARRAY 3",Array3);

	array<int,5>												Array4{5,4,8,9,23};

	PrintCollection(L"ARRAY 4",Array4);

	array<int,5>												Array5{};

	PrintCollection(L"ARRAY 5",Array5);

	// Vola sa IMPLICITNY OPERATOR=
	Array5=Array4;

	PrintCollection(L"ARRAY 5",Array5);

	array<int,5>												Array6=Array5;

	PrintCollection(L"ARRAY 6",Array6);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArraySwap(void)
{
	PrintLineSeparator();

	{
		array<CInt,5>											Array1{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		array<CInt,5>											Array2{CInt(11),CInt(12),CInt(13),CInt(14),CInt(15)};

		PrintCollection(L"ARRAY 1",Array1);
		PrintCollection(L"ARRAY 2",Array2);

		PrintLineSeparator();

		// !!!!! METHOD swap() na rozdiel od ostatnych CONTAINERS NEVYMIENA POINTER na INTERNAL DATA (v pripade ARRAY je to C-ARRAY), ale vykonava COPY VSETKYCH ITEMS. Je preto ZNACNE NEEFEKTIVNA.
		// !!! Pre KAZDY ITEM sa vola MOVE OPERATOR=.
		Array1.swap(Array2);

		PrintLineSeparator();

		PrintCollection(L"ARRAY 1",Array1);
		PrintCollection(L"ARRAY 2",Array2);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayMove(void)
{
	PrintLineSeparator();

	{
		array<CInt,5>											Array1{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		array<CInt,5>											Array2{CInt(11),CInt(12),CInt(13),CInt(14),CInt(15)};

		PrintCollection(L"ARRAY 1",Array1);
		PrintCollection(L"ARRAY 2",Array2);

		PrintLineSeparator();

		// !!! Pre KAZDY ITEM sa vola MOVE OPERATOR=.
		Array2=std::move(Array1);

		PrintLineSeparator();

		PrintCollection(L"ARRAY 2",Array2);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayComparison(void)
{
	PrintLineSeparator();

	array<int,5>												Array1{5,4,8,9,23};
	array<int,5>												Array2{5,4,8,7,23};

	PrintCollection(L"ARRAY 1",Array1);
	PrintCollection(L"ARRAY 2",Array2);

	PrintLineSeparator();

	wcout << L"ARRAY1==ARRAY2 [" << ((Array1==Array2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"ARRAY1!=ARRAY2 [" << ((Array1!=Array2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"ARRAY1<ARRAY2 [" << ((Array1<Array2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"ARRAY1<=ARRAY2 [" << ((Array1<=Array2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"ARRAY1>=ARRAY2 [" << ((Array1>=Array2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"ARRAY1>ARRAY2 [" << ((Array1>Array2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArraySize(void)
{
	PrintLineSeparator();

	array<int,5>												Array{5,4,8,9,23};

	PrintCollection(L"ARRAY",Array);

	wcout << L"ARRAY - SIZE [" << Array.size() << L"] !" << endl;
	wcout << L"ARRAY - MAX SIZE [" << Array.max_size() << L"] !" << endl;
	wcout << L"ARRAY - EMPTY [" << Array.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayFill(void)
{
	PrintLineSeparator();

	array<int,5>												Array{5,4,8,9,23};

	PrintCollection(L"ARRAY",Array);

	Array.fill(10);

	PrintCollection(L"ARRAY",Array);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayElementAccess(void)
{
	PrintLineSeparator();

	array<int,5>												Array{5,4,8,9,23};

	PrintCollection(L"ARRAY",Array);

	Array[1]=Array[1]+5;
	Array.at(2)=17;

	PrintCollection(L"ARRAY",Array);

	try
	{
		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"ARRAY [20] VALUE [" << Array.at(20) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintCollection(L"ARRAY",Array);

	wcout << L"ARRAY FRONT [" << Array.front() << L"] !" << endl;
	wcout << L"ARRAY BACK [" << Array.back() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayIterators(void)
{
	PrintLineSeparator();

	array<int,5>												Array{5,4,8,9,23};

	wcout << L"ARRAY [";

	for(array<int,5>::iterator Iterator=Array.begin();Iterator!=Array.end();Iterator++)
	{
		if (Iterator!=Array.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"ARRAY [";

	// Pouzije sa CONST ITERATOR.
	for(array<int,5>::const_iterator Iterator=Array.cbegin();Iterator!=Array.cend();Iterator++)
	{
		if (Iterator!=Array.cbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayAsCArray(void)
{
	PrintLineSeparator();

	array<wchar_t,27>											Array{L'M',L'y',L' ',L'n',L'a',L'm',L'e',L' ',L'i',L's',L' ',L'T',L'i',L'm',L'm',L'y',L' ',L'A',L'n',L'd',L'e',L'r',L's',L'o',L'n',L'.',L'\0'};

	// !!! Pouzitie ARRAY ako C-ARRAY.
	wprintf(L"TEXT [%ls] !\n",Array.data());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArrayTupleInterface(void)
{
	PrintLineSeparator();

	array<int,5>												Array{5,4,8,9,23};

	PrintCollection(L"ARRAY",Array);

	PrintLineSeparator();

	wcout << L"TYPES are SAME [" << ((typeid(tuple_element<2,array<int,5>>::type)==typeid(tuple_element<3,array<int,5>>::type)) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"ARRAY SAME [" << tuple_size<array<int,5>>::value << L"] !" << endl;

	PrintLineSeparator();

	// Pristup k ITEMS pomocou FUNCTION get().
	wcout << L"ARRAY [0] [" << get<0>(Array) << L"] !" << endl;
	wcout << L"ARRAY [1] [" << get<1>(Array) << L"] !" << endl;
	wcout << L"ARRAY [2] [" << get<2>(Array) << L"] !" << endl;
	wcout << L"ARRAY [3] [" << get<3>(Array) << L"] !" << endl;
	wcout << L"ARRAY [4] [" << get<4>(Array) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBitSetReference(void)
{
	PrintLineSeparator();

	bitset<10>													BitSet(857);

	wcout << L"BITSET [" << BitSet << L"] !" << endl;
	wcout << L"BITSET [" << BitSet.to_ulong() << L"] !" << endl;

	PrintLineSeparator();

	// Vrati REFERENCE na 2. NAJNIZSI BIT (hodnota 4).
	bitset<10>::reference										Reference1=BitSet[1];

	// Vrati REFERENCE na 3. NAJNIZSI BIT (hodnota 8).
	bitset<10>::reference										Reference2=BitSet[2];

	wcout << L"REFERENCE 1 [" << Reference1.operator bool() << L"] !" << endl;
	wcout << L"REFERENCE 2 [" << Reference2.operator bool() << L"] !" << endl;

	// !!! Obratia sa hodnoty BITS v POVODNOM BITSET.
	Reference1.flip();
	Reference2.flip();

	wcout << L"REFERENCE 1 [" << Reference1.operator bool() << L"] !" << endl;
	wcout << L"REFERENCE 2 [" << Reference2.operator bool() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"BITSET [" << BitSet << L"] !" << endl;
	wcout << L"BITSET [" << BitSet.to_ulong() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBitSetConstruction(void)
{
	PrintLineSeparator();

	bitset<10>													BitSet1(857);

	wcout << L"BITSET 1 [" << BitSet1 << L"] !" << endl;

	bitset<10>													BitSet2("0010011101");

	wcout << L"BITSET 2 [" << BitSet2 << L"] !" << endl;

	// Zoberie iba prvych 10 CHARACTERS.
	bitset<10>													BitSet3("0010011101110");

	wcout << L"BITSET 3 [" << BitSet3 << L"] !" << endl;

	bitset<10>													BitSet4(string("0010011101110"),3,10,'0','1');

	wcout << L"BITSET 4 [" << BitSet4 << L"] !" << endl;

	bitset<10>													BitSet5(string("--+--+++-+++-"),3,10,'-','+');

	wcout << L"BITSET 5 [" << BitSet5 << L"] !" << endl;

	try
	{
		// Hodi EXCEPTION, pretoze STRING obsahuje INVALID VALUE.
		bitset<10>												BitSet6("00100W1101");

		wcout << L"BITSET 6 [" << BitSet6 << L"] !" << endl;
	}
	catch(const invalid_argument&)
	{
		wcout << L"BITSET 6 can't be CREATED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBitSetSerialization(void)
{
	PrintLineSeparator();

	bitset<10>													BitSet1(857);

	wcout << L"BITSET 1 [" << BitSet1 << L"] !" << endl;

	PrintLineSeparator();

	wstringstream												Stream;

	Stream << BitSet1;

	wcout << L"STREAM [" << Stream.str() << L"] !" << endl;

	PrintLineSeparator();

	bitset<10>													BitSet2;

	Stream >> BitSet2;

	wcout << L"BITSET 2 [" << BitSet2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBitSetOperations(void)
{
	PrintLineSeparator();

	bitset<10>													BitSet1(857);
	bitset<10>													BitSet2(155);

	wcout << L"BITSET 1 [" << BitSet1 << L"] !" << endl;
	wcout << L"BITSET 2 [" << BitSet2 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"BITSET 1 AND BITSET 2 [" << (BitSet1 & BitSet2) << L"] !" << endl;
	wcout << L"BITSET 1 OR BITSET 2 [" << (BitSet1 | BitSet2) << L"] !" << endl;
	wcout << L"BITSET 1 XOR BITSET 2 [" << (BitSet1 ^ BitSet2) << L"] !" << endl;
	wcout << L"NOT BITSET 1 [" << (~BitSet1) << L"] !" << endl;
	wcout << L"NOT BITSET 2 [" << (~BitSet2) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Index=0;Index<20;Index++)
	{
		try
		{
			wcout << L"INDEX [" << Index << L"] VALUE [" << BitSet1.test(Index) << "] !" << endl;
		}
		catch(const out_of_range&)
		{
			wcout << L"INDEX [" << Index << L"] is OUT of RANGE !" << endl;
			break;
		}
	}

	PrintLineSeparator();

	wcout << L"BITSET 1 COUNT [" << BitSet1.count() << L"] !" << endl;
	wcout << L"BITSET 1 SIZE [" << BitSet1.size() << L"] !" << endl;
	wcout << L"BITSET 1 ALL [" << BitSet1.all() << L"] !" << endl;
	wcout << L"BITSET 1 ANY [" << BitSet1.any() << L"] !" << endl;
	wcout << L"BITSET 1 NONE [" << BitSet1.none() << L"] !" << endl;
	wcout << L"BITSET 1 FLIP [" << BitSet1.flip() << L"] !" << endl;
	wcout << L"BITSET 1 SET [" << BitSet1.set() << L"] !" << endl;
	wcout << L"BITSET 1 RESET [" << BitSet1.reset() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorBool(void)
{
	PrintLineSeparator();

	vector<bool>												Vector{true,false,false,true,false};

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	Vector.flip();

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	Vector[3]=true;

	// Vola sa OPERATOR BOOL().
	wcout << L"VECTOR [3] [" << Vector[3] << L"] !" << endl;

	Vector[3].flip();

	wcout << L"VECTOR [3] [" << Vector[3] << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
void TestSimplePairs(void)
{
	PrintLineSeparator();

	pair<wstring,int>											Pair(L"Timmy Anderson",12);

	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",Pair.first.c_str(),Pair.second);
	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Pair).c_str(),get<1>(Pair));

	wcout << L"TUPLE SIZE [" << tuple_size<pair<wstring,int>>::value << L"] !\n";

	printf_s("TYPE 1 [%s], TYPE 2 [%s] !\n",typeid(tuple_element<0,pair<wstring,int>>::type).name(),typeid(tuple_element<1,pair<wstring,int>>::type).name());

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

	wprintf_s(L"FIRST [%ls,%ls,%d] !\n",PiecewisePair.first.GetItem<0>().c_str(),PiecewisePair.first.GetItem<1>().c_str(),PiecewisePair.first.GetItem<2>());
	wprintf_s(L"SECOND [%ls,%d] !\n",PiecewisePair.second.GetItem<0>().c_str(),PiecewisePair.second.GetItem<1>());

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

	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",Pair1.first.c_str(),Pair1.second);
	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",Pair2.first.c_str(),Pair2.second);
	// FIELD [first] ma TYPE [const wchar*] a NIE TYPE [wstring].
	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",Pair3.first,Pair3.second);

	PrintLineSeparator();

	wstring														Name=L"Timmy Anderson";
	int															Age=12;

	// STRUCTURE [pair<T1,T2>] moze obsahovat aj REFERENCES.
	// !!! FUNCTION ref() prinuti COMPILER generovat PAIR, ktory bude mat REFERENCES na VALUES, namiesto VALUES.
	auto														Pair4=make_pair(ref(Name),ref(Age));

	wprintf_s(L"BEFORE - Name [%ls], Age [%d] !\n",Name.c_str(),Age);
	wprintf_s(L"BEFORE - VALUE 1 [%ls], VALUE 2 [%d] !\n",Pair4.first.c_str(),Pair4.second);
	
	// !!!!! Kedze PAIR 4 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	Pair4.first=L"Jenny Thompson";
	Pair4.second=13;

	// !!! Hodnoty 'Name' a 'Age' su ZMENENE.
	wprintf_s(L"AFTER - Name [%ls], Age [%d] !\n",Name.c_str(),Age);
	wprintf_s(L"AFTER - VALUE 1 [%ls], VALUE 2 [%d] !\n",Pair4.first.c_str(),Pair4.second);

	PrintLineSeparator();

	int															X=10;
	int															Y=20;

	// STRUCTURE [pair<T1,T2>] moze obsahovat aj REFERENCES.
	pair<int&,int&>												Pair5=make_pair(ref(X),ref(Y));

	wprintf_s(L"BEFORE - X [%d], Y [%d] !\n",X,Y);
	wprintf_s(L"BEFORE - VALUE 1 [%d], VALUE 2 [%d] !\n",Pair5.first,Pair5.second);

	// !!!!! Kedze PAIR 5 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	Pair5.first+=4;
	Pair5.second+=6;

	// !!! Hodnoty 'X' a 'Y' su ZMENENE.
	wprintf_s(L"AFTER - X [%d], Y [%d] !\n",X,Y);
	wprintf_s(L"AFTER - VALUE 1 [%d], VALUE 2 [%d] !\n",Pair5.first,Pair5.second);

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

	wprintf_s(L"PAIR(%d,%f) < PAIR(%d,%f) [%ls] !\n",Pair1.first,Pair1.second,Pair2.first,Pair2.second,(Pair1<Pair2) ? L"TRUE" : L"FALSE");
	wprintf_s(L"PAIR(%d,%f) < PAIR(%d,%f) [%ls] !\n",Pair1.first,Pair1.second,Pair3.first,Pair3.second,(Pair1<Pair3) ? L"TRUE" : L"FALSE");

	// Porovnavaju sa VALUES [first] a ak su rovne, tak aj VALUES [second].
	wprintf_s(L"PAIR(%d,%f) < PAIR(%d,%f) [%ls] !\n",Pair2.first,Pair2.second,Pair3.first,Pair3.second,(Pair2<Pair3) ? L"TRUE" : L"FALSE");
	wprintf_s(L"PAIR(%d,%f) < PAIR(%d,%f) [%ls] !\n",Pair3.first,Pair3.second,Pair4.first,Pair4.second,(Pair3<Pair4) ? L"TRUE" : L"FALSE");
	wprintf_s(L"PAIR(%d,%f) < PAIR(%d,%f) [%ls] !\n",Pair4.first,Pair4.second,Pair5.first,Pair5.second,(Pair4<Pair5) ? L"TRUE" : L"FALSE");
	wprintf_s(L"PAIR(%d,%f) <= PAIR(%d,%f) [%ls] !\n",Pair4.first,Pair4.second,Pair5.first,Pair5.second,(Pair4<=Pair5) ? L"TRUE" : L"FALSE");
	wprintf_s(L"PAIR(%d,%f) == PAIR(%d,%f) [%ls] !\n",Pair4.first,Pair4.second,Pair5.first,Pair5.second,(Pair4==Pair5) ? L"TRUE" : L"FALSE");
	wprintf_s(L"PAIR(%d,%f) != PAIR(%d,%f) [%ls] !\n",Pair4.first,Pair4.second,Pair5.first,Pair5.second,(Pair4!=Pair5) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleTuples(void)
{
	PrintLineSeparator();

	tuple<wstring,wstring,int>									Tuple(L"Timmy",L"Anderson",12);

	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%ls], VALUE 3 [%d] !\n",get<0>(Tuple).c_str(),get<1>(Tuple).c_str(),get<2>(Tuple));

	wcout << L"TUPLE SIZE [" << tuple_size<tuple<wstring,wstring,int>>::value << L"] !\n";

	PrintLineSeparator();

	printf_s("TYPE 1 [%s], TYPE 2 [%s], TYPE 3 [%s] !\n",typeid(tuple_element<0,tuple<wstring,wstring,int>>::type).name(),typeid(tuple_element<1,tuple<wstring,wstring,int>>::type).name(),typeid(tuple_element<2,tuple<wstring,wstring,int>>::type).name());

	PrintLineSeparator();

	// !!! Pouzitie sa INITIALIZER LIST.
	tuple<wstring,wstring,int>									TupleInitialized{L"Timmy",L"Anderson",12};

	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%ls], VALUE 3 [%d] !\n",get<0>(TupleInitialized).c_str(),get<1>(TupleInitialized).c_str(),get<2>(TupleInitialized));

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

	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Tuple1).c_str(),get<1>(Tuple1));
	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Tuple2).c_str(),get<1>(Tuple2));
	// 1. FIELD ma TYPE [const wchar*] a NIE TYPE [wstring].
	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Tuple3),get<1>(Tuple3));

	PrintLineSeparator();

	wstring														Name=L"Timmy Anderson";
	int															Age=12;

	// STRUCTURE [tuple<T...>] moze obsahovat aj REFERENCES.
	// !!! FUNCTION ref() prinuti COMPILER generovat TUPLE, ktory bude mat REFERENCES na VALUES, namiesto VALUES.
	auto														Tuple4=make_tuple(ref(Name),ref(Age));

	wprintf_s(L"BEFORE - Name [%ls], Age [%d] !\n",Name.c_str(),Age);
	wprintf_s(L"BEFORE - VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Tuple4).c_str(),get<1>(Tuple4));
	
	// !!!!! Kedze TUPLE 4 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple4)=L"Jenny Thompson";
	get<1>(Tuple4)=13;

	// !!! Hodnoty 'Name' a 'Age' su ZMENENE.
	wprintf_s(L"AFTER - Name [%ls], Age [%d] !\n",Name.c_str(),Age);
	wprintf_s(L"AFTER - VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Tuple4).c_str(),get<1>(Tuple4));

	PrintLineSeparator();

	int															X=10;
	int															Y=20;

	// CLASS [TUPLE<T...>] moze obsahovat aj REFERENCES.
	tuple<int&,int&>											Tuple5=make_tuple(ref(X),ref(Y));

	wprintf_s(L"BEFORE - X [%d], Y [%d] !\n",X,Y);
	wprintf_s(L"BEFORE - VALUE 1 [%d], VALUE 2 [%d] !\n",get<0>(Tuple5),get<1>(Tuple5));

	// !!!!! Kedze TUPLE 5 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple5)+=4;
	get<1>(Tuple5)+=6;

	// !!! Hodnoty 'X' a 'Y' su ZMENENE.
	wprintf_s(L"AFTER - X [%d], Y [%d] !\n",X,Y);
	wprintf_s(L"AFTER - VALUE 1 [%d], VALUE 2 [%d] !\n",get<0>(Tuple5),get<1>(Tuple5));

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

	wprintf_s(L"BEFORE - Name [%ls], Age [%d] !\n",Name.c_str(),Age);
	wprintf_s(L"BEFORE - VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Tuple1).c_str(),get<1>(Tuple1));
	
	// !!!!! Kedze TUPLE 1 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple1)=L"Jenny Thompson";
	get<1>(Tuple1)=13;

	// !!! Hodnoty 'Name' a 'Age' su ZMENENE.
	wprintf_s(L"AFTER - Name [%ls], Age [%d] !\n",Name.c_str(),Age);
	wprintf_s(L"AFTER - VALUE 1 [%ls], VALUE 2 [%d] !\n",get<0>(Tuple1).c_str(),get<1>(Tuple1));

	PrintLineSeparator();

	int															X=10;
	int															Y=20;

	// !!! CLASS [TUPLE<T...>] moze obsahovat aj REFERENCES. FUNCTION tie() vytvara TUPLE, ktoreho VSETKY TYPE PARAMETERS su REFERENCES.
	tuple<int&,int&>											Tuple2=tie(X,Y);

	wprintf_s(L"BEFORE - X [%d], Y [%d] !\n",X,Y);
	wprintf_s(L"BEFORE - VALUE 1 [%d], VALUE 2 [%d] !\n",get<0>(Tuple2),get<1>(Tuple2));

	// !!!!! Kedze TUPLE 2 obsahuje REFERENCES, je MOZNE ZMENIT VALUES oboch FIELDS.
	get<0>(Tuple2)+=4;
	get<1>(Tuple2)+=6;

	// !!! Hodnoty 'X' a 'Y' su ZMENENE.
	wprintf_s(L"AFTER - X [%d], Y [%d] !\n",X,Y);
	wprintf_s(L"AFTER - VALUE 1 [%d], VALUE 2 [%d] !\n",get<0>(Tuple2),get<1>(Tuple2));

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

	wprintf_s(L"TUPLE(%d,%f) < TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple1),get<1>(Tuple1),get<0>(Tuple2),get<1>(Tuple2),(Tuple1<Tuple2) ? L"TRUE" : L"FALSE");
	wprintf_s(L"TUPLE(%d,%f) < TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple1),get<1>(Tuple1),get<0>(Tuple3),get<1>(Tuple3),(Tuple1<Tuple3) ? L"TRUE" : L"FALSE");

	// Porovnavaju sa VALUES [first] a ak su rovne, tak aj VALUES [second].
	wprintf_s(L"TUPLE(%d,%f) < TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple2),get<1>(Tuple2),get<0>(Tuple3),get<1>(Tuple3),(Tuple2<Tuple3) ? L"TRUE" : L"FALSE");
	wprintf_s(L"TUPLE(%d,%f) < TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple3),get<1>(Tuple3),get<0>(Tuple4),get<1>(Tuple4),(Tuple3<Tuple4) ? L"TRUE" : L"FALSE");
	wprintf_s(L"TUPLE(%d,%f) < TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple4),get<1>(Tuple4),get<0>(Tuple5),get<1>(Tuple5),(Tuple4<Tuple5) ? L"TRUE" : L"FALSE");
	wprintf_s(L"TUPLE(%d,%f) <= TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple4),get<1>(Tuple4),get<0>(Tuple5),get<1>(Tuple5),(Tuple4<=Tuple5) ? L"TRUE" : L"FALSE");
	wprintf_s(L"TUPLE(%d,%f) == TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple4),get<1>(Tuple4),get<0>(Tuple5),get<1>(Tuple5),(Tuple4==Tuple5) ? L"TRUE" : L"FALSE");
	wprintf_s(L"TUPLE(%d,%f) != TUPLE(%d,%f) [%ls] !\n",get<0>(Tuple4),get<1>(Tuple4),get<0>(Tuple5),get<1>(Tuple5),(Tuple4!=Tuple5) ? L"TRUE" : L"FALSE");

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

	wprintf_s(L"VALUE 1 [%ls], VALUE 2 [%ls], VALUE 3 [%d] !\n",get<0>(Tuple).c_str(),get<1>(Tuple).c_str(),get<2>(Tuple));

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
wstring PrintVector(const vector<double>& Vector)
{
	wstringstream												Text;
	bool														First=true;

	for(double Item : Vector)
	{
		if (First==true)
		{
			First=false;
		}
		else
		{
			Text << L" ";
		}

		Text << Item;
	}

	return(Text.str());
}
//-----------------------------------------------------------------------------
void TestTuplesConversion(void)
{
	PrintLineSeparator();

	tuple<wstring,vector<double>,int>							Tuple1;
	tuple<const wchar_t*,vector<double>,char>					Tuple2({L"Some TEXT !",vector<double>({100,200,300}),'X'});

	// C++ umoznuje konverziu TUPLES s ROZNYM TYPES FILDS, ak su TYPES jednotlivych FIELDS konvertovatelne.
	Tuple1=Tuple2;

	wcout << L"TUPLE 1 [0] - [" << get<0>(Tuple1) << L"] !" << endl;
	wcout << L"TUPLE 2 [0] - [" << get<0>(Tuple2) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TUPLE 1 [1] - [" << PrintVector(get<1>(Tuple1)) << L"] !" << endl;
	wcout << L"TUPLE 2 [1] - [" << PrintVector(get<1>(Tuple2)) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TUPLE 1 [2] - [" << get<2>(Tuple1) << L"] !" << endl;
	wcout << L"TUPLE 2 [2] - [" << get<2>(Tuple2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer1(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		// !!! OPERATR= NIE JE PRETAZENY pre POINTER. Preto COMPILER hodi na tento CODE ERROR.
		//Pointer=new CCustomClass(L"Jenny Thompson");

		wprintf(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer2(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wprintf(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());

		// !!! Zavola DESTRUCTOR.
		Pointer.reset();

		if (Pointer!=nullptr)
		{
			wprintf(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());
		}
		else
		{
			wprintf(L"VALUE is NULL !\n");
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer3(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wprintf(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());

		// !!! NEZAVOLA sa DESTRUCTOR, iba instancia CLASS unique_ptr<CCustomClass> uz NEBUDE odkazovat na povodny POINTER.
		CCustomClass*											InnerPointer=Pointer.release();

		if (Pointer!=nullptr)
		{
			wprintf(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());
		}
		else
		{
			wprintf(L"VALUE is NULL !\n");
		}

		if (InnerPointer!=nullptr)
		{
			wprintf(L"INNER VALUE [%ls] !\n",InnerPointer->GetValue().c_str());
		}
		else
		{
			wprintf(L"INNER VALUE is NULL !\n");
		}

		delete(InnerPointer);
		InnerPointer=nullptr;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer4(void)
{
	PrintLineSeparator();

	{
		unique_ptr<wstring>										Pointer(new wstring(L"Timmy Anderson"));

		wprintf(L"VALUE [%ls] !\n",Pointer->c_str());

		(*Pointer)[2]=L'M';

		wprintf(L"VALUE [%ls] !\n",Pointer->c_str());

		// !!! FUNCTION unique_ptr<T>.get() vracia POINTER na referovany OBJECT.
		wstring*												InnerPointer=Pointer.get();

		wprintf(L"INNER VALUE [%ls] !\n",InnerPointer->c_str());

		wcout << L"INNER VALUE " << *InnerPointer << L" !\n";

		// Pouzitie OPERATOR BOOL.
		if (Pointer!=nullptr)
		{
			wprintf(L"POINTER is VALID !\n");
		}
		else
		{
			wprintf(L"POINTER is NULL !\n");
		}

		Pointer.reset();

		// Pouzitie OPERATOR BOOL.
		if (Pointer!=nullptr)
		{
			wprintf(L"POINTER is VALID !\n");
		}
		else
		{
			wprintf(L"POINTER is NULL !\n");
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerAssignment1(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wprintf(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());

		PrintLineSeparator();

		// !!! Povodny OBJECT sa UVOLNI a nahradi sa NOVYM OBJECT.
		Pointer=unique_ptr<CCustomClass>(new CCustomClass(L"Jenny Thompson"));

		wprintf(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerAssignment2(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer1(new CCustomClass(L"Timmy Anderson"));

		wprintf(L"POINTER 1 [%ls] !\n",Pointer1->GetValue().c_str());

		PrintLineSeparator();

		// !!!!! COMPILER hodi ERROR, pretoze OPERATOR= s COPY CONSTRUCTOR NIE JE PODPOROVANY.
		//unique_ptr<CCustomClass>								Pointer2(Pointer1);

		unique_ptr<CCustomClass>								Pointer2;

		// !!!!! COMPILER hodi ERROR, pretoze OPERATOR= s COPY SEMANTICS NIE JE PODPOROVANY.
		//Pointer2=Pointer1;

		// !!!!! COMPILER OPERATOR= pre MOVE SEMANTICS PODPORUJE.
		// !!!!! Hodnota 'Pointer1' bude rovna NULL.
		Pointer2=move(Pointer1);

		wprintf(L"POINTER 2 [%ls] !\n",Pointer2->GetValue().c_str());

		if (Pointer1!=nullptr)
		{
			wprintf(L"POINTER 1 [%ls] !\n",Pointer1->GetValue().c_str());
		}
		else
		{
			wprintf(L"POINTER 1 is NULL !\n");
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! UNIQUE POINTERS je mozne bez problemov prenasat pomocou REFERENCES.
void UniquePointerByReference(unique_ptr<CCustomClass>& Pointer)
{
	wprintf(L"INSIDE UniquePointerByReference() [%ls] !\n",Pointer->GetValue().c_str());
}
//-----------------------------------------------------------------------------
// !!!!! FUNCTION preberie OBJECT ulozeny v PARAMETER 'Pointer'.
void UniquePointerByValue(unique_ptr<CCustomClass> Pointer)
{
	wprintf(L"INSIDE UniquePointerByValue() [%ls] !\n",Pointer->GetValue().c_str());

	// !!!!! Tu sa zavola DESTRUCTOR pre OBJECT ulozeny v PARAMETER 'Pointer'.
}
//-----------------------------------------------------------------------------
void TestUniquePointerFunctionCalling(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		PrintLineSeparator();

		wprintf_s(L"BEFORE CALL by REFERENCE !\n");

		UniquePointerByReference(Pointer);

		wprintf_s(L"AFTER CALL by REFERENCE !\n");

		PrintLineSeparator();

		/*
		wprintf_s(L"BEFORE CALL by VALUE !\n");

		// !!!!! COMPILER hodi ERROR, pretoze COPY SEMANTICS NIE JE PODPOROVANA.
		UniquePointerByValue(Pointer);

		wprintf_s(L"AFTER CALL by VALUE !\n");
		*/

		wprintf_s(L"BEFORE CALL by VALUE !\n");

		// !!!!! Tento CODE COMPILER akceptuje, pretoze MOVE SEMANTICS je POVOLENA.
		// !!!!! Kedze sa pouzila MOVE SEMANTICS, tak OBJECT ulozeny vo VARIABLE 'Pointer' bude PRENESENY do FUNCTION UniquePointerByValue(), ktora tento OBJECT uvolni z MEMORY. To znaci, ze VOLANA FUNCTION UVOLNI OBJECT z MEMORY.
		UniquePointerByValue(move(Pointer));

		wprintf_s(L"AFTER CALL by VALUE !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! FUNCTION vytvori NOVY OBJECT pomocou OPERATOR NEW.
unique_ptr<CCustomClass> CreateObject1(wstring Value)
{
	unique_ptr<CCustomClass>									Pointer(new CCustomClass(Value));

	// !!!!! Nie je NUTNE pouzit MOVE SEMANTICS, pretoze C++ ju POUZIJE AUTOMATICKY. Je to preto, lebo CLASS [unique_ptr<T>] ma definovany MOVE CONSTRUCTOR a C++ ho AUTOMATICKY POUZIJE.
	return(Pointer);
}
//-----------------------------------------------------------------------------
void TestUniquePointerReturnValue1(void)
{
	PrintLineSeparator();

	{
		// !!! FUNCTION CreateObject() VYTVORILA OBJECT, no tento sa uvolni AZ v TEJTO FUNCTION.
		unique_ptr<CCustomClass>								Pointer1=CreateObject1(L"Timmy Anderson");

		wprintf(L"POINTER 1 [%ls] !\n",Pointer1->GetValue().c_str());

		PrintLineSeparator();

		unique_ptr<CCustomClass>								Pointer2;

		// !!! FUNCTION CreateObject() VYTVORILA OBJECT, no tento sa uvolni AZ v TEJTO FUNCTION.
		Pointer2=CreateObject1(L"Jenny Thompson");

		wprintf(L"POINTER 2 [%ls] !\n",Pointer2->GetValue().c_str());

		PrintLineSeparator();

		// !!!!! Aj ked sa RETURN VALUE NEPRIRADI do ZIADNEJ VARIABLE, tato TEMPORARY VARIBLE bude UVOLNENA.
		// !!!!! DESTRUCTOR pre vytvoreny OBJECT sa vola OKAMZITE, teda este PRED skoncenim SCOPE.
		CreateObject1(L"XXX YYY");

		wprintf_s(L"END of SCOPE !\n");

		// !!! Teraz sa zavolaju DESTRUCTORS pre VARIABLES 'Pointer1' a 'Pointer2'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! FUNCTION vytvori NOVY OBJECT pomocou OPERATOR NEW.
unique_ptr<CCustomClass> CreateObject2(wstring Value)
{
	unique_ptr<CCustomClass>									Pointer(new CCustomClass(Value));

	// !!!!! Nie je NUTNE pouzit MOVE SEMANTICS, pretoze C++ ju POUZIJE AUTOMATICKY. Je to preto, lebo CLASS [unique_ptr<T>] ma definovany MOVE CONSTRUCTOR a C++ ho AUTOMATICKY POUZIJE.
	return(Pointer);
}
//-----------------------------------------------------------------------------
void TestUniquePointerReturnValue2(void)
{
	PrintLineSeparator();

	{
		wprintf_s(L"BEFORE CYCLE !\n");
		
		for(int Index=0;Index<5;Index++)
		{
			// !!! FUNCTION CreateObject() VYTVORILA OBJECT, no tento sa uvolni AZ v TEJTO FUNCTION.
			unique_ptr<CCustomClass>							Pointer=CreateObject2(L"Timmy Anderson");

			wprintf(L"POINTER [%ls] !\n",Pointer->GetValue().c_str());
		}

		wprintf_s(L"AFTER CYCLE !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassWithUniquePointers(void)
{
	PrintLineSeparator();

	{
		CClassWithUniquePointers								Object(L"Timmy",L"Anderson",12);

		// !!! Kedze CLASS 'CClassWithUniquePointers' NEDEFINOVALA CUSTOM OPERATOR= s COPY SEMANTICS a CLASS [unique_ptr<T>] NEDEKLARUJE CUSTOM OPERATOR= s COPY SEMANTICS, ktoru pouziva vo svojich FIELDS, C++ NIE JE SCHOPNE vytvorit IMPLICITNY OPERATOR= s COPY SEMANTICS a tym padom COMPILER hodi ERROR.
		//Object=Object;

		Object.Print();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClassWithUniquePointersWithException(void)
{
	PrintLineSeparator();

	try
	{
		// !!! CONSTRUCTOR hodi EXCEPTION pri inicializacii jednotlivych FIELDS. Vdaka pouzitiu CLASS [unique_ptr<T>] na ulozenie POINTERS NEDOJDE k MEMORY LEAK, ako pri pouziti standardnych POINTERS.
		CClassWithUniquePointersException						Object(L"Timmy",L"Anderson",12);

		// !!! Kedze CLASS 'CClassWithUniquePointersException' NEDEFINOVALA CUSTOM OPERATOR= s COPY SEMANTICS a CLASS [unique_ptr<T>] NEDEKLARUJE CUSTOM OPERATOR= s COPY SEMANTICS, ktoru pouziva vo svojich FIELDS, C++ NIE JE SCHOPNE vytvorit IMPLICITNY OPERATOR= s COPY SEMANTICS a tym padom COMPILER hodi ERROR.
		//Object=Object;

		Object.Print();
	}
	catch(CException& E)
	{
		wprintf_s(L"EXCEPTION [%ls] !\n",E.GetMessage().c_str());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays1(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;
		// !!! Deklaracia ARRAY.
		unique_ptr<wstring[]>									Array(new wstring[LENTGH]{L"A",L"B",L"C"});

		for(int Index=0;Index<LENTGH;Index++)
		{
			wprintf_s(L"ITEM[%d]=[%ls] !\n",Index,Array[Index].c_str());
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays2(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;
		unique_ptr<CCustomClass[]>								Array(new CCustomClass[LENTGH]{CCustomClass(L"A"),CCustomClass(L"B"),CCustomClass(L"C")});

		wprintf_s(L"BEFORE CYCLE !\n");

		for(int Index=0;Index<LENTGH;Index++)
		{
			wprintf_s(L"ITEM[%d]=[%ls] !\n",Index,Array[Index].GetValue().c_str());
		}

		wprintf_s(L"AFTER CYCLE !\n");

		// !!! Vola sa OPERATOR DELETE[], ktory zavola DESTRUCTORS vsetkych ARRAY ITEMS.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays3(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;

		// !!! Alokuje sa ARRAY obsahujuci POINTERS na CLASS 'CBaseClass' do ktorych sa ulozia instancie CLASS 'CDerivedClass'.
		unique_ptr<CBaseClass*[]>								Array(new CBaseClass*[LENTGH]{new CDerivedClass(L"A"),new CDerivedClass(L"B"),new CDerivedClass(L"C")});

		wprintf_s(L"BEFORE CYCLE !\n");

		for(int Index=0;Index<LENTGH;Index++)
		{
			wprintf_s(L"ITEM[%d]=[%ls] !\n",Index,Array[Index]->GetValue().c_str());
		}

		wprintf_s(L"AFTER CYCLE !\n");

		// Explicitne sa uvolnia POINTERS.
		for(int Index=0;Index<LENTGH;Index++)
		{
			delete(Array[Index]);
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerArrays4(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;

		// !!! Alokuje sa ARRAY obsahujuci UNIQUE SMART POINTERS na CLASS 'CBaseClass' do ktorych sa ulozia instancie CLASS 'CDerivedClass'.
		unique_ptr<unique_ptr<CBaseClass>[]>					Array(new unique_ptr<CBaseClass>[LENTGH]{unique_ptr<CBaseClass>(new CDerivedClass(L"A")),unique_ptr<CBaseClass>(new CDerivedClass(L"B")),unique_ptr<CBaseClass>(new CDerivedClass(L"C"))});

		wprintf_s(L"BEFORE CYCLE !\n");

		for(int Index=0;Index<LENTGH;Index++)
		{
			wprintf_s(L"ITEM[%d]=[%ls] !\n",Index,Array[Index]->GetValue().c_str());
		}

		wprintf_s(L"AFTER CYCLE !\n");

		// !!! Vola sa OPERATOR DELETE[], ktory zavola DESTRUCTORS vsetkych ARRAY ITEMS.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyCustomDeleteFunction(wstring* Pointer)
{
	delete(Pointer);

	wprintf_s(L"CUSTOM DELETE FUNCTION as FUNCTION CALLED !\n");
}
//-----------------------------------------------------------------------------
void TestUniquePointerCustomDeleteFunction(void)
{
	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako CUSTOM FUNCTION.
		unique_ptr<wstring,void(*)(wstring*)>					Pointer(new wstring(L"Timmy Anderson"),MyCustomDeleteFunction);

		wprintf_s(L"VALUE [%ls] !\n",Pointer->c_str());
	}

	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako CUSTOM FUNCTION.
		// TYPE PARAMETER je deklarovany pomocou TEMPLATE CLASS [function<T>].
		unique_ptr<wstring,function<void(wstring*)>>			Pointer(new wstring(L"Timmy Anderson"),MyCustomDeleteFunction);

		wprintf_s(L"VALUE [%ls] !\n",Pointer->c_str());
	}

	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako LAMBDA EXPRESSION.
		unique_ptr<wstring,void(*)(wstring*)>					Pointer(new wstring(L"Timmy Anderson"),[](wstring* Pointer){delete(Pointer); wprintf_s(L"CUSTOM DELETE FUNCTION as LAMBDA EXPRESSION CALLED !\n");});

		wprintf_s(L"VALUE [%ls] !\n",Pointer->c_str());
	}

	PrintLineSeparator();

	{
		CCustomDeleteFuctionForUniquePointer					Functor;

		// !!! CUSTOM DELETE FUNCTION je definovana ako FUNCTOR.
		unique_ptr<wstring,CCustomDeleteFuctionForUniquePointer>	Pointer(new wstring(L"Timmy Anderson"),Functor);

		wprintf_s(L"VALUE [%ls] !\n",Pointer->c_str());
	}

	PrintLineSeparator();

	{
		// !!! CUSTOM DELETE FUNCTION je definovana ako FUNCTOR.
		unique_ptr<wstring,CCustomDeleteFuctionForUniquePointer>	Pointer(new wstring(L"Timmy Anderson"),CCustomDeleteFuctionForUniquePointer());

		wprintf_s(L"VALUE [%ls] !\n",Pointer->c_str());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MyCustomDeleteFunctionForArrays(CCustomClass* Pointer)
{
	delete[](Pointer);

	wprintf_s(L"CUSTOM DELETE FUNCTION for ARRAYS CALLED !\n");
}
//-----------------------------------------------------------------------------
void TestUniquePointerCustomDeleteFunctionForArrays(void)
{
	PrintLineSeparator();

	{
		const int												LENTGH=3;
		unique_ptr<CCustomClass[],void(*)(CCustomClass*)>		Array(new CCustomClass[LENTGH]{CCustomClass(L"A"),CCustomClass(L"B"),CCustomClass(L"C")},MyCustomDeleteFunctionForArrays);

		wprintf_s(L"BEFORE CYCLE !\n");

		for(int Index=0;Index<LENTGH;Index++)
		{
			wprintf_s(L"ITEM[%d]=[%ls] !\n",Index,Array[Index].GetValue().c_str());
		}

		wprintf_s(L"AFTER CYCLE !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerInner(shared_ptr<CCustomClass> Pointer)
{
	wprintf_s(L"SharedPointerInner() - VALUE [%ls] !\n",Pointer->GetValue().c_str());
}
//-----------------------------------------------------------------------------
void SharedPointerOuter(shared_ptr<CCustomClass> Pointer)
{
	wprintf_s(L"SharedPointerOuter() - VALUE [%ls] !\n",Pointer->GetValue().c_str());

	SharedPointerInner(Pointer);
}
//-----------------------------------------------------------------------------
void TestSharedPointer1(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wprintf_s(L"TestSharedPointer() - VALUE [%ls] !\n",Pointer->GetValue().c_str());

		SharedPointerOuter(Pointer);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerPrintVector(vector<shared_ptr<CCustomClass>> Vector)
{
	for(const shared_ptr<CCustomClass>& Item : Vector)
	{
		wprintf_s(L"VALUE [%ls] !\n",Item->GetValue().c_str());
	}
}
//-----------------------------------------------------------------------------
void TestSharedPointer2(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer1(new CCustomClass(L"Timmy Anderson"));
		shared_ptr<CCustomClass>								Pointer2(new CCustomClass(L"Jenny Thompson"));
		vector<shared_ptr<CCustomClass>>						Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerPrintVector(vector<shared_ptr<wstring>> Vector)
{
	for(const shared_ptr<wstring>& Item : Vector)
	{
		wprintf_s(L"VALUE [%ls] !\n",Item->c_str());
	}
}
//-----------------------------------------------------------------------------
void TestSharedPointer3(void)
{
	PrintLineSeparator();

	{
		shared_ptr<wstring>										Pointer1(new wstring(L"Timmy Anderson"));
		shared_ptr<wstring>										Pointer2(new wstring(L"Jenny Thompson"));
		vector<shared_ptr<wstring>>								Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);

		PrintLineSeparator();

		// !!! Zmeni sa hodnota oboch OBJECTS na ktore SHARED SMART POINTER referuju pricom tato zmena sa premietne do vsetkych SHARED SMART POINTER, kedze referuju na tieto OBJECTS.
		*Pointer1=L"Timothy Anderson";
		(*Pointer2)[0]=L'Y';

		SharedPointerPrintVector(Vector);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointer4(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wprintf_s(L"BEFORE RESET !\n");

		// Uvolni sa predchadzajuci OBJECT a zavola sa pred DESTRUCTOR.
		Pointer.reset(new CCustomClass(L"Jenny Thompson"));

		wprintf_s(L"BEFORE NULL POINTER ASSIGNMENT !\n");

		// !!! OPERATR= NIE JE PRETAZENY pre POINTER. Preto COMPILER hodi na tento CODE ERROR.
		//Pointer=new CCustomClass(L"Jenny Thompson");

		// Uvolni sa OBJECT a zavola sa pred DESTRUCTOR.
		Pointer=nullptr;

		wprintf_s(L"AFTER NULL POINTER ASSIGNMENT !\n");

		// !!! Kedze tu uz 'Pointer' NEOBSAHUJE ziaden OBJECT, tak sa DESTRUCTOR NEVOLA.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointer5(void)
{
	PrintLineSeparator();

	{
		// !!! FUNCTION make_shared() predstavuje EFEKTIVNEJSI sposob vytvorenia SHARED SMART POINTER.
		shared_ptr<CCustomClass>								Pointer1=make_shared<CCustomClass>(L"Timmy Anderson");
		shared_ptr<CCustomClass>								Pointer2=make_shared<CCustomClass>(L"Jenny Thompson");
		vector<shared_ptr<CCustomClass>>						Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);

		wprintf_s(L"REFERENCE COUNTER POINTER 1 [%d] !\n",Pointer1.use_count());
		wprintf_s(L"REFERENCE COUNTER POINTER 2 [%d] !\n",Pointer2.use_count());

		wprintf_s(L"BEFORE CLEAR !\n");

		// !!! DESTRUCTORS sa NEVOLAJU, pretoze VARIABLES 'Pointer1' a 'Pointer2' sa referuju na OBJECTS.
		Vector.clear();

		wprintf_s(L"AFTER CLEAR !\n");

		wprintf_s(L"REFERENCE COUNTER POINTER 1 [%d] !\n",Pointer1.use_count());
		wprintf_s(L"REFERENCE COUNTER POINTER 2 [%d] !\n",Pointer2.use_count());

		Pointer1=nullptr;
		Pointer2=nullptr;

		wprintf_s(L"AFTER NULL POINTER ASSIGMENT !\n");

		wprintf_s(L"REFERENCE COUNTER POINTER 1 [%d] !\n",Pointer1.use_count());
		wprintf_s(L"REFERENCE COUNTER POINTER 2 [%d] !\n",Pointer2.use_count());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomDeleter(CCustomClass* ObjectToDelete) noexcept
{
	wprintf_s(L"CUSTOM DELETER was CALLED !\n");

	delete(ObjectToDelete);
}
//-----------------------------------------------------------------------------
void TestSharedPointerCustomDeleter(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"),CustomDeleter);

		wprintf_s(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());
	}

	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"),[](CCustomClass* ObjectToDelete){wprintf_s(L"CUSTOM DELETER was CALLED !\n"); delete(ObjectToDelete);});

		wprintf_s(L"VALUE [%ls] !\n",Pointer->GetValue().c_str());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomArrayDeleter1(int* ObjectToDelete) noexcept
{
	wprintf_s(L"CUSTOM ARRAY DELETER was CALLED !\n");

	delete[](ObjectToDelete);
}
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomArrayDeleter2(CCustomClass* ObjectToDelete) noexcept
{
	wprintf_s(L"CUSTOM ARRAY DELETER was CALLED !\n");

	delete[](ObjectToDelete);
}
//-----------------------------------------------------------------------------
void TestSharedPointerArrays(void)
{
	PrintLineSeparator();

	{
		// !!!!! Ak sa SHARED SMART POINTERS pouzivaju pre ulozenie ARRAYS, je NEVYHNUTNE definovat CUSTOM DELETE FUNCTION v ktorej sa zavola OPERATOR DELETE[].
		shared_ptr<int>											Pointer(new int[10],CustomArrayDeleter1);

		wprintf_s(L"REFERENCE COUNTER [%d] !\n",Pointer.use_count());
	}

	PrintLineSeparator();

	{
		// !!!!! Ak sa SHARED SMART POINTERS pouzivaju pre ulozenie ARRAYS, je NEVYHNUTNE definovat CUSTOM DELETE FUNCTION v ktorej sa zavola OPERATOR DELETE[].
		shared_ptr<CCustomClass>								Pointer(new CCustomClass[5],CustomArrayDeleter2);

		wprintf_s(L"REFERENCE COUNTER [%d] !\n",Pointer.use_count());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
void TestSharedPointerError(void)
{
	PrintLineSeparator();

	{
		wstring*												Data=new wstring(L"Timmy Anderson");
		shared_ptr<wstring>										Pointer1(Data);
		shared_ptr<wstring>										Pointer2(Data);

		wprintf_s(L"POINTER 1 [%ls] !\n",Pointer1->c_str());
		wprintf_s(L"POINTER 2 [%ls] !\n",Pointer2->c_str());

		// !!!!! CODE sposobi MEMORY ACCESS ERROR, pretoze VARIABLES 'Pointer1' a 'Pointer2' maju NEZAVISLE REFERENCE COUNTERS a ich DESTRUCTORS sa OBE pokusia zavolat OPERATOR DELETE pre VARIABLE 'Data'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
void TestSharedPointerOK(void)
{
	PrintLineSeparator();

	{
		wstring*												Data=new wstring(L"Timmy Anderson");
		shared_ptr<wstring>										Pointer1(Data);
		// !!! Namiesto POINTER sa prenasa instancia CLASS [shared_ptr<wstring>].
		shared_ptr<wstring>										Pointer2(Pointer1);

		wprintf_s(L"POINTER 1 [%ls] !\n",Pointer1->c_str());
		wprintf_s(L"POINTER 2 [%ls] !\n",Pointer2->c_str());

		// !!!!! CODE NESPOSOBI MEMORY ACCESS ERROR, pretoze VARIABLES 'Pointer1' a 'Pointer2' maju SPOLOCNY REFERENCE COUNTERS, ktory az ked klesne na 0, dojde k uvolneniu VARIABLE 'Data'. VARIABLE 'Data' sa teda uvolni iba raz.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
void TestErrorThisShared(void)
{
	PrintLineSeparator();

	{
		// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
		shared_ptr<CErrorThisParentShared>						Pointer1(new CErrorThisParentShared());
		shared_ptr<CErrorThisChildShared>						Pointer2(Pointer1->GetChild());

		Pointer1->CallChild();
		Pointer2->CallParent();

		wprintf_s(L"POINTER 1 REFERENCE COUNTER [%d] !\n",Pointer1.use_count());
		wprintf_s(L"POINTER 2 REFERENCE COUNTER [%d] !\n",Pointer2.use_count());

		wprintf_s(L"PARENT REFERENCE COUNTER 1 [%d] !\n",Pointer1->GetReferenceCounter());
		wprintf_s(L"CHILD REFERENCE COUNTER 2 [%d] !\n",Pointer2->GetReferenceCounter());

		// !!!!! Na konci SCOPE instancia CLASS [shared_ptr<CErrorThisParentShared>] vola DESTRUCTOR OBJECT [CErrorThisParentShared], lebo jeho REFERENCE COUNTER je rovny 1.
		// !!!!! Na konci SCOPE instancia CLASS [shared_ptr<CErrorThisChildShared>] NEVOLA DESTRUCTOR OBJECT [CErrorThisParentChild], pretoze jeho REFERENCE COUNTER je rovna 2. Je to preto, lebo instancia CLASS [shared_ptr<CErrorThisChildShared>] referuje na FIELD 'CErrorThisParentShared.MChild', ktory drzi inkrementoval hodnotu REFERENCE COUNTER o 1. Vysledna hodnota je teda 2.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerOK1(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CSharedPointerOnThis>						Pointer(new CSharedPointerOnThis());
		
		// !!! Do FIELD sa ulozi THIS POINTER.
		Pointer->SetPointer();

		Pointer->SomeMethod();

		// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
		Pointer->ResetPointer();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerOK2(void)
{
	PrintLineSeparator();

	CSharedPointerOnThis*										Pointer=nullptr;

	try
	{
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorenu instanciu CLASS [CSharedPointerOnThis] ulozit do instancie CLASS [shared_ptr<T>].
		Pointer=new CSharedPointerOnThis();
		
		// !!! Do FIELD sa ulozi THIS POINTER.
		Pointer->SetPointer();

		Pointer->SomeMethod();

		// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
		Pointer->ResetPointer();

		delete(Pointer);
		Pointer=nullptr;
	}
	catch(bad_weak_ptr& E)
	{
		if (Pointer!=nullptr)
		{
			// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
			Pointer->ResetPointer();

			delete(Pointer);
			Pointer=nullptr;
		}

		printf_s("EXCEPTION [%s] !\n",E.what());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerOK3(void)
{
	PrintLineSeparator();

	try
	{
		CSharedPointerOnThis									Object;
		
		// !!! Do FIELD sa ulozi THIS POINTER.
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorit instanciu CLASS [CSharedPointerOnThis] pomocou OPERATOR NEW.
		Object.SetPointer();

		Object.SomeMethod();

		// !!!!! Je NUTNE, aby sa pred koncom FUNCTION uvolnil POINTER NA THIS ulozeny vo FIELD. Ak by sa tak nestalo, potom by doslo k CYCLIC REFERENCE (FIELD obsahuje SHARED POINTER a drzi REFERENCE COUNTER na hodnote>1) a NEDOSLO by k UVOLNENIU MEMORY. Vznikol by tak MEMORY LEAK.
		Object.ResetPointer();
	}
	catch(bad_weak_ptr& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerError1(void)
{
	PrintLineSeparator();

	try
	{
		// !!!!! Hodi EXCEPTION, pretoze METHOD shared_from_this() je volana v CONSTRUCTOR CLASS [CSharedPointerOnThisError] co CLASS [enable_shared_from_this<T>] NEUMOZNUJE.
		shared_ptr<CSharedPointerOnThisError>					Pointer(new CSharedPointerOnThisError());
		
		Pointer->SomeMethod();
	}
	catch(bad_weak_ptr& E)
	{
		wcout << "EXCEPTION [" << ConvertStringToWideString(E.what()) << "] !\n";
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerError2(void)
{
	PrintLineSeparator();

	CSharedPointerOnThisError*									Pointer=nullptr;

	try
	{
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorenu instanciu CLASS [CSharedPointerOnThis] ulozit do instancie CLASS [shared_ptr<T>].
		Pointer=new CSharedPointerOnThisError();
		
		Pointer->SomeMethod();

		delete(Pointer);
		Pointer=nullptr;
	}
	catch(bad_weak_ptr& E)
	{
		if (Pointer!=nullptr)
		{
			delete(Pointer);
			Pointer=nullptr;
		}

		wcout << "EXCEPTION [" << ConvertStringToWideString(E.what()) << "] !\n";
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedThisPointerError3(void)
{
	PrintLineSeparator();

	try
	{
		// !!!!! HODI EXCEPTION, pretoze pri pouziti CLASS [enable_shared_from_this] je NEVYHNUTNE vytvorit instanciu CLASS [CSharedPointerOnThis] pomocou OPERATOR NEW.
		CSharedPointerOnThisError								Object;
		
		Object.SomeMethod();
	}
	catch(bad_weak_ptr& E)
	{
		wcout << "EXCEPTION [" << ConvertStringToWideString(E.what()) << "] !\n";
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerDynamicCasts(void)
{
	PrintLineSeparator();

	shared_ptr<CBaseVirtual>									Pointer1(new CDerivedVirtual());

	Pointer1->VirtualMethod();

	shared_ptr<CDerivedVirtual>									Pointer2=dynamic_pointer_cast<CDerivedVirtual,CBaseVirtual>(Pointer1);

	if (Pointer2!=nullptr)
	{
		Pointer2->VirtualMethod();
	}
	else
	{
		wprintf_s(L"POINTER 2 is NULL !\n");
	}

	shared_ptr<wstring>											Pointer3=dynamic_pointer_cast<wstring,CBaseVirtual>(Pointer1);

	if (Pointer3!=nullptr)
	{
		wprintf_s(L"POINTER 3 is [%ls] !\n",Pointer3->c_str());
	}
	else
	{
		wprintf_s(L"POINTER 3 is NULL !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerStaticCasts(void)
{
	PrintLineSeparator();

	/*
	shared_ptr<float>											Pointer1(new float(3.14f));
	// !!!!! COMPILER hodi ERROR, pretoze ako STANDARDNY C++ OPERATOR static_cast<T>(), tak ani FUNCTION static_pointer_cast<T1,T2>() NEPODPORUJU konverzie FLOAT a DOUBLE POINTERS. Dovodom preco static_cast<T>() NA ROZDIEL od STANDARDNEHO PRETYPOVACIEHO OPERATOR () konverzie takychto POINTERS NEPODPORUJE je, ze su POTENCIALNE NEBEZPECNE, pretoze po pretypovani POINTERS odkazuju na TYPE s INOU DLZKOU v BYTES (FLOAT ma 4 BYTES, zatial co DOUBLE ma 8 BYTES). Z bezpecnostnych dovodov su tieto konverzie pomocou OPERATOR static_cast<T>() ZAKAZANE.
	shared_ptr<double>											Pointer2=static_pointer_cast<double,float>(Pointer1);

	wprintf_s(L"DOUBLE VALUE [%f] !\n",*Pointer2);
	*/

	shared_ptr<CBaseVirtual>									Pointer3(new CDerivedVirtual());

	Pointer3->VirtualMethod();

	shared_ptr<CDerivedVirtual>									Pointer4=static_pointer_cast<CDerivedVirtual,CBaseVirtual>(Pointer3);

	Pointer4->VirtualMethod();

	// Konverzia na TYPE 'CBaseVirtual*'.
	shared_ptr<CBaseVirtual>									Pointer5=static_pointer_cast<CBaseVirtual,CDerivedVirtual>(Pointer4);

	Pointer5->VirtualMethod();

	shared_ptr<CBaseVirtual>									Pointer6(new CBaseVirtual());

	Pointer6->VirtualMethod();

	shared_ptr<CDerivedVirtual>									Pointer7=static_pointer_cast<CDerivedVirtual,CBaseVirtual>(Pointer6);

	Pointer7->VirtualMethod();

	PrintLineSeparator();

	// !!! Urobi STATICKU KONVERZIU na 'CBaseNonVirtual*'.
	shared_ptr<CBaseNonVirtual>									Pointer8(new CDerivedNonVirtual());

	Pointer8->NonVirtualMethod();

	shared_ptr<CDerivedNonVirtual>								Pointer9=static_pointer_cast<CDerivedNonVirtual,CBaseNonVirtual>(Pointer8);

	Pointer9->NonVirtualMethod();

	// !!! Urobi STATICKU KONVERZIU na 'CBaseNonVirtual*'.
	shared_ptr<CBaseNonVirtual>									Pointer10=static_pointer_cast<CBaseNonVirtual,CDerivedNonVirtual>(Pointer9);

	Pointer10->NonVirtualMethod();

	shared_ptr<CBaseNonVirtual>									Pointer11(new CBaseNonVirtual());

	Pointer11->NonVirtualMethod();

	shared_ptr<CDerivedNonVirtual>								Pointer12=static_pointer_cast<CDerivedNonVirtual,CBaseNonVirtual>(Pointer11);

	Pointer12->NonVirtualMethod();

	PrintLineSeparator();

	shared_ptr<void>											Pointer13(new wstring(L"Timmy Anderson"));

	// Pretypovanie na 'wstring*'.
	shared_ptr<wstring>											Pointer14=static_pointer_cast<wstring,void>(Pointer13);

	wprintf_s(L"VALUE [%ls] !\n",Pointer14->c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerConstCasts(void)
{
	PrintLineSeparator();

	shared_ptr<const int>										Pointer1(new const int(10));

	wprintf_s(L"POINTER 1 [%d] !\n",*Pointer1);

	shared_ptr<int>												Pointer2=const_pointer_cast<int,const int>(Pointer1);

	wprintf_s(L"POINTER 2 [%d] !\n",*Pointer2);

	*Pointer2=20;

	wprintf_s(L"POINTER 1 [%d] !\n",*Pointer1);
	wprintf_s(L"POINTER 2 [%d] !\n",*Pointer2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerAliasingConstructor(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CName>										Name(new CName(L"Timmy",L"Anderson",12));

		// !!! Pouzije sa ALIASING CONSTRUCTOR, pretoze zivotnost OBJECT 'Name' a jeho FIELDS je zviazana.
		shared_ptr<wstring>										FirstName(Name,&Name->MFirstName);
		shared_ptr<wstring>										LastName(Name,&Name->MLastName);
		shared_ptr<int>											Age(Name,&Name->MAge);

		wprintf_s(L"FIRST NAME [%ls], LAST NAME [%ls], AGE [%d] !\n",FirstName->c_str(),LastName->c_str(),*Age);

		wprintf_s(L"NAME COUNT [%d] !\n",Name.use_count());
		wprintf_s(L"FIRST NAME COUNT [%d] !\n",FirstName.use_count());
		wprintf_s(L"LAST NAME COUNT [%d] !\n",LastName.use_count());
		wprintf_s(L"AGE COUNT [%d] !\n",Age.use_count());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointerThreadSafe(void)
{
	PrintLineSeparator();

	{
		shared_ptr<wstring>										SharedPointer;
		shared_ptr<wstring>										LocalPointer(new wstring(L"Timmy Anderson"));

		// !!! Priradenie POINTER ATOMICKYM SPOSOBOM.
		atomic_store(&SharedPointer,LocalPointer);

		// !!! Citanie POINTER ATOMICKYM SPOSOBOM.
		shared_ptr<wstring>										CopiedPointer=atomic_load(&SharedPointer);

		wprintf_s(L"COPIED POINTER [%ls] !\n",CopiedPointer->c_str());

		wprintf_s(L"LOCAL POINTER [%d] !\n",LocalPointer.use_count());
		wprintf_s(L"SHARED POINTER [%d] !\n",SharedPointer.use_count());
		wprintf_s(L"COPIED POINTER [%d] !\n",CopiedPointer.use_count());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThreadCallback(int ThreadIndex, shared_ptr<wstring> SharedPointer)
{
	const int													NUMBER_OF_ITERATIONS=1000*1000;

	for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
	{
		shared_ptr<wstring>										Copy1(SharedPointer);
		shared_ptr<wstring>										Copy2(Copy1);

		Copy1=Copy2;
	}

	wstringstream												Stream;

	Stream << L"THREAD [" << ThreadIndex << L"] SHARED POINTER COUNTER [" << SharedPointer.use_count() << L"] !" << endl;

	wcout << Stream.str();
}
//-----------------------------------------------------------------------------
// !!!!! Pretoze CLASS [shared_ptr<T>] GARANTUJE, ze pristup k ROZNYM INSTANCIAM CLASS [shared_ptr<T>] z ROZLICNYCH THREADS ak referuju na TEN ISTY OBJECT JE THREAD SAFE, tento CODE prebehne uspesne BEZ hodenia RUNTIME ERROR.
void TestSharedPointerMultiThreadAccess(void)
{
	PrintLineSeparator();

	const int													NUMBER_OF_THREADS=100;
	thread														Threads[NUMBER_OF_THREADS];
	shared_ptr<wstring>											SharedPointer(new wstring(L"TIMMY ANDERSON"));

	wcout << L"SHARED POINTER [" << *SharedPointer << L"] !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			Threads[Index]=thread(ThreadCallback,Index+1,SharedPointer);
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wcout << L"SHARED POINTER [" << *SharedPointer << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestWeakPointer1(void)
{
	PrintLineSeparator();

	weak_ptr<wstring>											WeakPointer;

	{
		shared_ptr<wstring>										SharedPointer(new wstring(L"Timmy Anderson"));
		vector<shared_ptr<wstring>>								Vector;

		WeakPointer=SharedPointer;

		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);

		wprintf_s(L"REFERENCE COUNTER [%d] !\n",WeakPointer.use_count());
		wprintf_s(L"EXPIRED [%ls] !\n",(WeakPointer.expired()==true) ? L"TRUE" : L"FALSE");

		// !!! VALUE sa ziskava pomocou METHOD weak_ptr<T>.lock().
		wprintf_s(L"VALUE [%ls] !\n",WeakPointer.lock()->c_str());
	}

	wprintf_s(L"AFTER RELEASE - REFERENCE COUNTER [%d] !\n",WeakPointer.use_count());
	wprintf_s(L"AFTER RELEASE - EXPIRED [%ls] !\n",(WeakPointer.expired()==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestWeakPointer2(void)
{
	PrintLineSeparator();

	weak_ptr<wstring>											WeakPointer;

	{
		shared_ptr<wstring>										SharedPointer(new wstring(L"Timmy Anderson"));
		vector<shared_ptr<wstring>>								Vector;

		WeakPointer=SharedPointer;

		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);
		Vector.push_back(SharedPointer);

		wprintf_s(L"WEAK POINTER - REFERENCE COUNTER [%d] !\n",WeakPointer.use_count());
		wprintf_s(L"WEAK POINTER - EXPIRED [%ls] !\n",(WeakPointer.expired()==true) ? L"TRUE" : L"FALSE");

		// !!! CLASS weak_ptr<T> je mozne konvertovat na CLASS shared_ptr<T>.
		shared_ptr<wstring>										NewSharedPointer(WeakPointer.lock());

		wprintf_s(L"VALUE [%ls] !\n",NewSharedPointer->c_str());

		wprintf_s(L"SHARED POINTER - REFERENCE COUNTER [%d] !\n",SharedPointer.use_count());
		wprintf_s(L"NEW SHARED POINTER - REFERENCE COUNTER [%d] !\n",NewSharedPointer.use_count());
	}

	wprintf_s(L"AFTER RELEASE - REFERENCE COUNTER [%d] !\n",WeakPointer.use_count());
	wprintf_s(L"AFTER RELEASE - EXPIRED [%ls] !\n",(WeakPointer.expired()==true) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestWeakPointer3(void)
{
	PrintLineSeparator();

	try
	{
		shared_ptr<wstring>										SharedPointer1(new wstring(L"Timmy Anderson"));

		wprintf_s(L"SHARED POINTER 1 [%ls] !\n",SharedPointer1->c_str());

		weak_ptr<wstring>										WeakPointer(SharedPointer1);

		// !!! VALUE sa ziskava pomocou METHOD weak_ptr<T>.lock().
		wprintf_s(L"WEAK POINTER 1 [%ls] !\n",WeakPointer.lock()->c_str());
			
		// SHARED POINTER vytvoreny z WEAK POINTER.
		shared_ptr<wstring>										SharedPointer2(WeakPointer);

		wprintf_s(L"SHARED POINTER 2 [%ls] !\n",SharedPointer2->c_str());

		wprintf_s(L"WEAK POINTER - REFERENCE COUNTER [%d] !\n",WeakPointer.use_count());

		SharedPointer1.reset();

		wprintf_s(L"WEAK POINTER - REFERENCE COUNTER after RESET 1 [%d] !\n",WeakPointer.use_count());

		SharedPointer2.reset();

		wprintf_s(L"WEAK POINTER - REFERENCE COUNTER after RESET 2 [%d] !\n",WeakPointer.use_count());

		// !!!!! Pri pokuse o vytvorenie SHARED POINTER z PRAZDNEHO WEAK POINTER dojde k hodeniu EXCEPTION.
		shared_ptr<wstring>										SharedPointer3(WeakPointer);

		wprintf_s(L"SHARED POINTER 3 [%ls] !\n",SharedPointer3->c_str());
	}
	catch(bad_weak_ptr& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE vedie k MEMORY LEAK.
void TestCyclicReferencesSharedPointers1(void)
{
	PrintLineSeparator();

	{
		// !!!!! TENTO CODE vedie k MEMORY LEAK.
		shared_ptr<CCyclicReferencesShared1>					Pointer1(new CCyclicReferencesShared1());
		shared_ptr<CCyclicReferencesShared2>					Pointer2(new CCyclicReferencesShared2());

		// !!!!! Vytvori sa CYCLIC REFERENCE.
		Pointer1->SetPointer(Pointer2);
		Pointer2->SetPointer(Pointer1);

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Vdaka tomu, ze existuje CYCLIC REFERENCE, tak v DESTRUCTORS CLASS [shared_ptr<T>] NEDOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE vedie k MEMORY LEAK.
void TestCyclicReferencesSharedPointers2(void)
{
	PrintLineSeparator();

	weak_ptr<CCyclicReferencesShared1>							WeakPointer1;
	weak_ptr<CCyclicReferencesShared2>							WeakPointer2;

	{
		// !!!!! TENTO CODE vedie k MEMORY LEAK.
		shared_ptr<CCyclicReferencesShared1>					Pointer1(new CCyclicReferencesShared1());
		shared_ptr<CCyclicReferencesShared2>					Pointer2(new CCyclicReferencesShared2());

		WeakPointer1=Pointer1;
		WeakPointer2=Pointer2;

		// !!!!! Vytvori sa CYCLIC REFERENCE.
		Pointer1->SetPointer(Pointer2);
		Pointer2->SetPointer(Pointer1);

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 2, pretoze existuje CYCLIC REFERENCE.
		wprintf_s(L"IN SCOPE - WEAK POINTER 1 [%d] !\n",WeakPointer1.use_count());
		wprintf_s(L"IN SCOPE - WEAK POINTER 2 [%d] !\n",WeakPointer2.use_count());

		// !!!!! Vdaka tomu, ze existuje CYCLIC REFERENCE, tak v DESTRUCTORS CLASS [shared_ptr<T>] NEDOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 1, co je dovod preco neboli uvolnene.
	wprintf_s(L"OUT of SCOPE - WEAK POINTER 1 [%d] !\n",WeakPointer1.use_count());
	wprintf_s(L"OUT of SCOPE - WEAK POINTER 2 [%d] !\n",WeakPointer2.use_count());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE NESPOSOBI MEMORY LEAK.
void TestCyclicReferencesSharedPointers3(void)
{
	PrintLineSeparator();

	weak_ptr<CCyclicReferencesShared1>							WeakPointer1;
	weak_ptr<CCyclicReferencesShared2>							WeakPointer2;

	{
		// !!!!! TENTO CODE vedie k MEMORY LEAK.
		shared_ptr<CCyclicReferencesShared1>					Pointer1(new CCyclicReferencesShared1());
		shared_ptr<CCyclicReferencesShared2>					Pointer2(new CCyclicReferencesShared2());

		WeakPointer1=Pointer1;
		WeakPointer2=Pointer2;

		// !!!!! Vytvori sa CYCLIC REFERENCE.
		Pointer1->SetPointer(Pointer2);
		Pointer2->SetPointer(Pointer1);

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 2, pretoze existuje CYCLIC REFERENCE.
		wprintf_s(L"IN SCOPE - WEAK POINTER 1 [%d] !\n",WeakPointer1.use_count());
		wprintf_s(L"IN SCOPE - WEAK POINTER 2 [%d] !\n",WeakPointer2.use_count());

		// !!! Znizia sa hodnoty REFERENCE COUNTERS.
		Pointer1->GetPointer().reset();
		Pointer2->GetPointer().reset();

		// !!!!! Vdaka tomu, ze sa EXPLICITNE uvolnili CYCLIC REFERENCES, tak v DESTRUCTORS CLASS [shared_ptr<T>] DOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	// !!!!! Hodnoty REFERENCE COUNTERS oboch SHARED POINTERS budu 0.
	wprintf_s(L"OUT of SCOPE - WEAK POINTER 1 [%d] !\n",WeakPointer1.use_count());
	wprintf_s(L"OUT of SCOPE - WEAK POINTER 2 [%d] !\n",WeakPointer2.use_count());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCyclicReferencesWeakPointers(void)
{
	PrintLineSeparator();

	{
		// !!!!! TENTO CODE NEVEDIE k MEMORY LEAK, pretoze CYCLIC REFERENCE je realizovana cez CLASS [weak_ptr<T>].
		shared_ptr<CCyclicReferencesWeak1>						Pointer1(new CCyclicReferencesWeak1());
		shared_ptr<CCyclicReferencesWeak2>						Pointer2(new CCyclicReferencesWeak2());

		// !!!!! Vytvori sa CYCLIC REFERENCE cez WEAK POINTERS.
		Pointer1->SetPointer(weak_ptr<CCyclicReferencesWeak2>(Pointer2));
		Pointer2->SetPointer(weak_ptr<CCyclicReferencesWeak1>(Pointer1));

		Pointer1->CallOther();
		Pointer2->CallOther();

		// !!!!! Vdaka tomu, ze CYCLIC REFERENCE je realizovana cez WEAK POINTERS, tak v DESTRUCTORS CLASS [shared_ptr<T>] DOJDE k uvolneniu OBJECT 'CCyclicReferencesShared1' a 'CCyclicReferencesShared2'.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStandardAllocator(void)
{
	PrintLineSeparator();

	vector<int>													VectorNoAllocator;

	VectorNoAllocator.push_back(10);
	VectorNoAllocator.push_back(20);
	VectorNoAllocator.push_back(30);

	for(int Value : VectorNoAllocator)
	{
		wprintf_s(L"VALUE [%d] !\n",Value);
	}

	PrintLineSeparator();

	// !!! VECTOR pouziva ALLOCATOR z LIST.
	vector<int,list<int>::allocator_type>						VectorWithAllocator;

	VectorWithAllocator.push_back(10);
	VectorWithAllocator.push_back(20);
	VectorWithAllocator.push_back(30);

	for(int Value : VectorWithAllocator)
	{
		wprintf_s(L"VALUE [%d] !\n",Value);
	}

	PrintLineSeparator();

	// !!! ALLOCATORS je mozne porovnavat.
	wprintf_s(L"ALLOCATORS are [%ls] !\n",(VectorNoAllocator.get_allocator()==VectorWithAllocator.get_allocator()) ? L"SAME" : L"DIFFERENT");

	bool														AreSameCompatible=uses_allocator<vector<int>,list<wstring>::allocator_type>::value;

	wprintf_s(L"ALLOCATORS are [%ls] !\n",(AreSameCompatible==true) ? L"COMPATIBLE" : L"DIFFERENT");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomAllocator(void)
{
	PrintLineSeparator();

	{
		vector<wstring,CMyAllocator<wstring>>					VectorWithCustomAllocator;

		VectorWithCustomAllocator.push_back(L"AAA 10");
		VectorWithCustomAllocator.push_back(L"BBB 20");
		VectorWithCustomAllocator.push_back(L"CCC 30");

		for(wstring Value : VectorWithCustomAllocator)
		{
			wprintf_s(L"VALUE [%ls] !\n",Value.c_str());
		}

		PrintLineSeparator();

		wprintf_s(L"ALLOCATORS are [%ls] !\n",(VectorWithCustomAllocator.get_allocator()==VectorWithCustomAllocator.get_allocator()) ? L"SAME" : L"DIFFERENT");
		wprintf_s(L"ALLOCATORS are [%ls] !\n",(VectorWithCustomAllocator.get_allocator()!=VectorWithCustomAllocator.get_allocator()) ? L"DIFFERENT" : L"SAME");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAllocatorRebind(void)
{
	PrintLineSeparator();

	vector<wstring>::allocator_type								Allocator;

	wstring*													StringMemory=Allocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << StringMemory << L"] !" << endl;

	Allocator.deallocate(StringMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();

	// !!! Tento ALLOCATOR je schopny alokovat INTEGERS.
	vector<wstring>::allocator_type::rebind<int>::other			RebindAllocator;

	int*														IntMemory=RebindAllocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << IntMemory << L"] !" << endl;

	RebindAllocator.deallocate(IntMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomAllocatorRebind(void)
{
	PrintLineSeparator();

	CMyAllocator<wstring>										Allocator;

	wstring*													StringMemory=Allocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << StringMemory << L"] !" << endl;

	Allocator.deallocate(StringMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();

	// !!! Tento ALLOCATOR je schopny alokovat INTEGERS.
	CMyAllocator<wstring>::rebind<int>::other					RebindAllocator;

	int*														IntMemory=RebindAllocator.allocate(10);

	wcout << L"MEMORY was ALLOCATED at ADDRESS [" << IntMemory << L"] !" << endl;

	RebindAllocator.deallocate(IntMemory,10);

	wcout << L"MEMORY was DEALLOCATED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomScopedAllocatorAdaptors(void)
{
	PrintLineSeparator();
	
	wcout << L"TEST is STARTING !" << endl;

	PrintLineSeparator();

	{
		PrintLineSeparator();

		wcout << L"TEST is ENTERING SCOPE !" << endl;

		PrintLineSeparator();

		using													TAllocator1=CMyAllocator1<int>;
		using													TCollection1=deque<wstring,TAllocator1>;

		using													TAllocator2=scoped_allocator_adaptor<CMyAllocator2<TCollection1>,TAllocator1>;
		using													TCollection2=list<TCollection1,TAllocator2>;

		using													TAllocator3=scoped_allocator_adaptor<CMyAllocator3<TCollection2>,TAllocator2,TAllocator1>;
		using													TCollection3=list<TCollection2,TAllocator3>;

		TCollection1											Collection11;
		TCollection1											Collection12;
		TCollection1											Collection13;
		TCollection1											Collection14;

		PrintLineSeparator();

		Collection11.push_back(L"AAA");
		Collection11.push_back(L"BBB");

		Collection12.push_back(L"CCC");
		Collection12.push_back(L"DDD");

		Collection13.push_back(L"EEE");
		Collection13.push_back(L"FFF");

		Collection14.push_back(L"GGG");
		Collection14.push_back(L"HHH");

		PrintLineSeparator();

		wcout << L"ITEMS to COLLECTION LEVEL 1 were ADDED !" << endl;

		PrintLineSeparator();

		TCollection2											Collection21;
		TCollection2											Collection22;

		Collection21.push_back(Collection11);
		Collection21.push_back(Collection12);

		Collection22.push_back(Collection13);
		Collection22.push_back(Collection14);

		PrintLineSeparator();

		wcout << L"ITEMS to COLLECTION LEVEL 2 were ADDED !" << endl;

		PrintLineSeparator();

		TCollection3											Collection3;

		Collection3.push_back(Collection21);
		Collection3.push_back(Collection22);

		PrintLineSeparator();

		wcout << L"ITEMS to COLLECTION LEVEL 3 were ADDED !" << endl;

		PrintLineSeparator();

		using													TIterator1=list<deque<wstring,CMyAllocator1<int>>,scoped_allocator_adaptor<CMyAllocator2<deque<wstring,CMyAllocator1<int>>>,CMyAllocator1<int>>>;
		using													TIterator2=deque<wstring,CMyAllocator1<int>>;

		for(const TIterator1& Item1 : Collection3)
		{
			for(const TIterator2& Item2 : Item1)
			{
				for(const wstring& Value : Item2)
				{
					wcout << L"VALUE [" << Value << L"] !\n";
				}
			}
		}

		PrintLineSeparator();

		wcout << L"TEST is LEAVING SCOPE !" << endl;

		PrintLineSeparator();
	}

	PrintLineSeparator();

	wcout << L"TEST is ENDING !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedFill(void)
{
	PrintLineSeparator();

	const int													NUMBER_OF_ITEMS=3;
	int															Values[NUMBER_OF_ITEMS];

	uninitialized_fill(Values,Values+3,10);

	for(int Index=0;Index<NUMBER_OF_ITEMS;Index++)
	{
		wprintf_s(L"INDEX [%d] VALUE [%d] !\n",Index+1,Values[Index]);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedCopy(void)
{
	PrintLineSeparator();

	const int													NUMBER_OF_ITEMS=3;
	int															InitializedValues[NUMBER_OF_ITEMS]{10,20,30};
	int															UninitializedValues[NUMBER_OF_ITEMS];

	uninitialized_copy(InitializedValues,InitializedValues+3,UninitializedValues);

	for(int Index=0;Index<NUMBER_OF_ITEMS;Index++)
	{
		wprintf_s(L"INDEX [%d] VALUE [%d] !\n",Index+1,UninitializedValues[Index]);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTemporaryBuffer(void)
{
	PrintLineSeparator();

	// !!! FUNCTION NEMUSI alokovat celu pozadovanu MEMORY.
	pair<int*,ptrdiff_t>										Buffer=get_temporary_buffer<int>(100);

	wprintf_s(L"MEMORY [%p], NUMBER of ELEMENTS [%lld] !\n",Buffer.first,Buffer.second);

	return_temporary_buffer<int>(Buffer.first);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRawStorageIterator(void)
{
	PrintLineSeparator();

	const int													NUMBER_OF_ITEMS=3;
	int															InitializedValues[NUMBER_OF_ITEMS]{10,20,30};
	int															UninitializedValues[NUMBER_OF_ITEMS];

	copy(InitializedValues,InitializedValues+3,raw_storage_iterator<int*,int>(UninitializedValues));

	for(int Index=0;Index<NUMBER_OF_ITEMS;Index++)
	{
		wprintf_s(L"INDEX [%d] VALUE [%d] !\n",Index+1,UninitializedValues[Index]);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGarbageCollectorMode(void)
{
	PrintLineSeparator();

	pointer_safety												PointerSafety=get_pointer_safety();

	if (PointerSafety==pointer_safety::strict)
	{
		wcout << L"POINTER SAFETY MODE [strict] !" << endl;
	}
	else if (PointerSafety==pointer_safety::preferred)
	{
		wcout << L"POINTER SAFETY MODE [preferred] !" << endl;
	}
	else if (PointerSafety==pointer_safety::relaxed)
	{
		wcout << L"POINTER SAFETY MODE [relaxed] !" << endl;
	}
	else
	{
		wcout << L"POINTER SAFETY MODE [UNKNOWN] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestArrayInitialization();
	//TestArraySwap();
	//TestArrayMove();
	//TestArrayComparison();
	//TestArraySize();
	//TestArrayFill();
	//TestArrayElementAccess();
	//TestArrayIterators();
	//TestArrayAsCArray();
	//TestArrayTupleInterface();
	//TestBitSetReference();
	//TestBitSetConstruction();
	//TestBitSetSerialization();
	//TestBitSetOperations();
	//TestVectorBool();
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
	//TestTuplesConversion();
	//TestUniquePointer1();
	//TestUniquePointer2();
	//TestUniquePointer3();
	//TestUniquePointer4();
	//TestUniquePointerAssignment1();
	//TestUniquePointerAssignment2();
	//TestUniquePointerFunctionCalling();
	//TestUniquePointerReturnValue1();
	//TestUniquePointerReturnValue2();
	//TestClassWithUniquePointers();
	//TestClassWithUniquePointersWithException();
	//TestUniquePointerArrays1();
	//TestUniquePointerArrays2();
	//TestUniquePointerArrays3();
	//TestUniquePointerArrays4();
	//TestUniquePointerCustomDeleteFunction();
	//TestUniquePointerCustomDeleteFunctionForArrays();
	//TestSharedPointer1();
	//TestSharedPointer2();
	//TestSharedPointer3();
	//TestSharedPointer4();
	//TestSharedPointer5();
	//TestSharedPointerCustomDeleter();
	//TestSharedPointerArrays();
	// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
	//TestSharedPointerError();
	//TestSharedPointerOK();
	// !!!!! TENTO CODE SPOSOBI MEMORY ACCESS ERROR.
	//TestErrorThisShared();
	// !!!!! TENTO CODE SPOSOBI MEMORY LEAK.
	//TestSharedThisPointerOK1();
	//TestSharedThisPointerOK2();
	//TestSharedThisPointerOK3();
	//TestSharedThisPointerError1();
	//TestSharedThisPointerError2();
	//TestSharedThisPointerError3();
	//TestSharedPointerDynamicCasts();
	//TestSharedPointerStaticCasts();
	//TestSharedPointerConstCasts();
	//TestSharedPointerAliasingConstructor();
	//TestSharedPointerThreadSafe();
	//TestSharedPointerMultiThreadAccess();
	//TestWeakPointer1();
	//TestWeakPointer2();
	//TestWeakPointer3();
	// !!!!! TENTO CODE vedie k MEMORY LEAK.
	//TestCyclicReferencesSharedPointers1();
	// !!!!! TENTO CODE vedie k MEMORY LEAK.
	//TestCyclicReferencesSharedPointers2();
	// !!!!! TENTO CODE vedie k MEMORY LEAK.
	//TestCyclicReferencesSharedPointers3();
	//TestCyclicReferencesWeakPointers();
	//TestStandardAllocator();
	//TestCustomAllocator();
	//TestAllocatorRebind();
	//TestCustomAllocatorRebind();
	//TestCustomScopedAllocatorAdaptors();
	//TestUninitializedFill();
	//TestUninitializedCopy();
	//TestTemporaryBuffer();
	//TestRawStorageIterator();
	TestGarbageCollectorMode();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------