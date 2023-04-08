//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <array>
#include <vector>
#include <forward_list>
#include <list>
#include <sstream>
#include "MyDebug.h"
#include "CPerson.h"
#include "CString.h"
#include "CCustomIterator.h"
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
template<typename TIteratorType>
void PrintIteratorTraits(const wstring& TypeName)
{
	wcout << L"TYPE [" << TypeName << L"] !" << endl;

	wcout << L"CATEGORY [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::iterator_category).name()) << L"] !" << endl;
	wcout << L"VALUE TYPE [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::value_type).name()) << L"] !" << endl;
	wcout << L"POINTER [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::pointer).name()) << L"] !" << endl;
	wcout << L"REFERENCE [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::reference).name()) << L"] !" << endl;
	wcout << L"DIFFERENCE TYPE [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::difference_type).name()) << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOutputIterator(void)
{
	PrintLineSeparator();

	vector<int>													Vector;

	PrintCollection(L"VECTOR",Vector);

	back_insert_iterator<vector<int>>							OutputIterator=back_inserter(Vector);

	// !!! OPERATOR= AUTOMATICKY INKREMENTUJE ITERATOR POSITION.
	*OutputIterator=100;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// !!! OPERATOR= AUTOMATICKY INKREMENTUJE ITERATOR POSITION.
	*OutputIterator=200;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// ++OPERATOR a OPERATOR++ su PRAZDNE OPERATIONS, ktore NIC NEROBIA.
	OutputIterator++;
	OutputIterator++;
	++OutputIterator;
	++OutputIterator;

	// !!! OPERATOR= AUTOMATICKY INKREMENTUJE ITERATOR POSITION.
	*OutputIterator=300;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInputIterator(void)
{
	PrintLineSeparator();

	vector<wstring>												Vector1;
	vector<wstring>												Vector2;
	wstringstream												Stream(L"My name is Timmy Anderson !");
	
	// !!! Cyklus porovnava VALUES s PRAZDNY INPUT STREAM ITERATOR, ktory sa pouziva ako zarazka indikujuca kedy sa ma iterovanie skoncit. To sa konci vtedy, ked bol cely STREAM precitany, alebo doslo k ERROR. Koniec STREAMU je signalizovany prave 2. PARAMETROM obsahujucim na prazdny INPUT STREAM ITERATOR.
	for(istream_iterator<wstring,wchar_t> Iterator=istream_iterator<wstring,wchar_t>(Stream);Iterator!=istream_iterator<wstring,wchar_t>();Iterator++)
	{
		Vector1.push_back(*Iterator);
	}

	PrintCollection(L"VECTOR 1",Vector1);

	PrintLineSeparator();

	// Kedze STREAM uz bol cely prejdeny, tak iteracia OKAMZITE SKONCI a VECTOR ostane PRAZDNY.
	for(istream_iterator<wstring,wchar_t> Iterator=istream_iterator<wstring,wchar_t>(Stream);Iterator!=istream_iterator<wstring,wchar_t>();Iterator++)
	{
		Vector2.push_back(*Iterator);
	}

	PrintCollection(L"VECTOR 2",Vector2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardIterator(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList({10,20,30,40,50});

	wcout << L"FORWARD LIST [";

	for(forward_list<int>::const_iterator ForwardIterator=ForwardList.cbegin();ForwardIterator!=ForwardList.cend();ForwardIterator++)
	{
		if (ForwardIterator!=ForwardList.cbegin())
		{
			wcout << L" ";
		}

		wcout << *ForwardIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	for(forward_list<int>::iterator ForwardIterator=ForwardList.begin();ForwardIterator!=ForwardList.end();ForwardIterator++)
	{
		// Kedze FORWARD ITERATOR je zaroven aj MUTABLE FORWARD ITERATOR, je mozne modifikovat VALUES v COLLECTION.
		*ForwardIterator=*ForwardIterator*2;
	}

	wcout << L"FORWARD LIST [";

	for(forward_list<int>::const_iterator ForwardIterator=ForwardList.cbegin();ForwardIterator!=ForwardList.cend();ForwardIterator++)
	{
		if (ForwardIterator!=ForwardList.cbegin())
		{
			wcout << L" ";
		}

		wcout << *ForwardIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBidirectionalIterator(void)
{
	PrintLineSeparator();

	list<int>													List({10,20,30,40,50});

	wcout << L"LIST [";

	for(list<int>::const_iterator BidirectionalIterator=List.cbegin();BidirectionalIterator!=List.cend();BidirectionalIterator++)
	{
		if (BidirectionalIterator!=List.cbegin())
		{
			wcout << L" ";
		}

		wcout << *BidirectionalIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"LIST [";

	list<int>::const_iterator									BidirectionalIterator1=List.cend();

	while(BidirectionalIterator1!=List.cbegin())
	{
		if (BidirectionalIterator1!=List.cend())
		{
			wcout << L" ";
		}

		BidirectionalIterator1--;

		wcout << *BidirectionalIterator1;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	for(list<int>::iterator BidirectionalIterator=List.begin();BidirectionalIterator!=List.end();BidirectionalIterator++)
	{
		// Kedze BIDIRECTIONAL ITERATOR je zaroven aj MUTABLE BIDIRECTIONAL ITERATOR, je mozne modifikovat VALUES v COLLECTION.
		*BidirectionalIterator=*BidirectionalIterator*2;
	}

	wcout << L"LIST [";

	for(list<int>::const_iterator BidirectionalIterator=List.cbegin();BidirectionalIterator!=List.cend();BidirectionalIterator++)
	{
		if (BidirectionalIterator!=List.cbegin())
		{
			wcout << L" ";
		}

		wcout << *BidirectionalIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"LIST [";

	list<int>::const_iterator									BidirectionalIterator2=List.cend();

	while(BidirectionalIterator2!=List.cbegin())
	{
		if (BidirectionalIterator2!=List.cend())
		{
			wcout << L" ";
		}

		BidirectionalIterator2--;

		wcout << *BidirectionalIterator2;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomAccessIterator(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	wcout << L"VECTOR [";

	for(vector<int>::const_iterator RandomAccessIterator=Vector.cbegin();RandomAccessIterator!=Vector.cend();RandomAccessIterator++)
	{
		if (RandomAccessIterator!=Vector.cbegin())
		{
			wcout << L" ";
		}

		wcout << *RandomAccessIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pouzije sa OPERATOR- na zistenie velkosti VECTOR.
	wcout << L"VECTOR SIZE [" << (Vector.cend()-Vector.cbegin()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VECTOR [";

	// !!! Pre porovnanie sa pouzije OPERATOR<.
	// !!! Pre posun sa pouziva OPERATOR+=.
	for(vector<int>::iterator RandomAccessIterator=Vector.begin();RandomAccessIterator<Vector.end();RandomAccessIterator+=1)
	{
		// Pouzije sa OPERATOR>.
		if (RandomAccessIterator>Vector.cbegin())
		{
			wcout << L" ";
		}

		// Kedze ITERATOR je MUTABLE, je mozne menit hodnoty ITEMS.
		*RandomAccessIterator=*RandomAccessIterator*2;

		wcout << *RandomAccessIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VECTOR [";

	vector<int>::const_iterator									Iterator1=Vector.cbegin();

	for(vector<int>::size_type Index=0;Index<vector<int>::size_type(Vector.cend()-Vector.cbegin());Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		// Na pristup k ITEMS sa pouziva OPERATOR[].
		// !!!!! Pouziva sa OPERATOR[] ITERATORU a NIE VECTOR.
		wcout << Iterator1[Index];
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator2=Vector.cbegin();

	// !!! Pouzije sa OPERATOR+ na pristup k ITEMS.
	wcout << L"ITEM [2] - [" << *(Iterator2+2) << L"] !" << endl;
	wcout << L"ITEM [4] - [" << *(Iterator2+4) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIteratorPortabilityProblem(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	// !!!!! Tento CODE v pripade, ze ITERATOR je implementovany ako POINTER bude NEKOMPILOVATELNY.
	//wcout << L"ITEM [1] - [" << *(++Vector.begin()) << L"] !" << endl;
	//wcout << L"ITEM [4] - [" << *(--Vector.end()) << L"] !" << endl;

	// !!!!! Tento CODE funguje aj ked ITERATOR je implementovany ako POINTER.
	wcout << L"ITEM [1] - [" << *(next(Vector.begin())) << L"] !" << endl;
	wcout << L"ITEM [4] - [" << *(prev(Vector.end())) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAdvance(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=Vector.cbegin();

	// Posunie ITERATOR o 4 POSITIONS.
	advance(Iterator1,4);

	wcout << L"ITEM [5] - [" << *(Iterator1) << L"] !" << endl;

	PrintLineSeparator();

	// Posunie ITERATOR o -2 POSITIONS.
	advance(Iterator1,-2);

	wcout << L"ITEM [3] - [" << *(Iterator1) << L"] !" << endl;

	PrintLineSeparator();

	forward_list<int>											ForwardList({100,200,300,400,500});

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Iterator2=ForwardList.cbegin();

	// Posunie ITERATOR o 4 POSITIONS.
	advance(Iterator2,4);

	wcout << L"ITEM [5] - [" << *(Iterator2) << L"] !" << endl;

	/*
	// Posunie ITERATOR o -2 POSITIONS.
	// !!!!! Posun dozadu FORWARD ITERATORS NEPODPORUJU a pre tieto ITERATORS FUNCTION advance() ma UNDEFINED BEHVIOR.
	// !!!!! CODE moze sposobit RUNTIME ERROR v zavislosti na PLATFORM. V GCC CODE sposobil RUNTIME ERROR.
	advance(Iterator2,-2);

	wcout << L"ITEM [3] - [" << *(Iterator2) << L"] !" << endl;
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNext(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=Vector.cbegin();

	// Posunie ITERATOR o 4 POSITIONS.
	Iterator1=next(Iterator1,4);

	wcout << L"ITEM [5] - [" << *(Iterator1) << L"] !" << endl;

	PrintLineSeparator();

	// Posunie ITERATOR o -2 POSITIONS.
	Iterator1=next(Iterator1,-2);

	wcout << L"ITEM [3] - [" << *(Iterator1) << L"] !" << endl;

	PrintLineSeparator();

	forward_list<int>											ForwardList({100,200,300,400,500});

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Iterator2=ForwardList.cbegin();

	// Posunie ITERATOR o 4 POSITIONS.
	Iterator2=next(Iterator2,4);

	wcout << L"ITEM [5] - [" << *(Iterator2) << L"] !" << endl;

	/*
	// Posunie ITERATOR o -2 POSITIONS.
	// !!!!! Posun dozadu FORWARD ITERATORS NEPODPORUJU a pre tieto ITERATORS FUNCTION next() ma UNDEFINED BEHVIOR.
	// !!!!! CODE moze sposobit RUNTIME ERROR v zavislosti na PLATFORM. V GCC CODE sposobil RUNTIME ERROR.
	Iterator2=next(Iterator2,-2);

	wcout << L"ITEM [3] - [" << *(Iterator2) << L"] !" << endl;
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPrev(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator=Vector.cend();

	// Posunie ITERATOR o 4 POSITIONS.
	Iterator=prev(Iterator,4);

	wcout << L"ITEM [2] - [" << *(Iterator) << L"] !" << endl;

	PrintLineSeparator();

	// Posunie ITERATOR o -2 POSITIONS.
	Iterator=prev(Iterator,-2);

	wcout << L"ITEM [4] - [" << *(Iterator) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDistance(void)
{
	PrintLineSeparator();

	// Pouziva RANDOM-ACCESS ITERATORS.
	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=find(Vector.cbegin(),Vector.cend(),20);
	vector<int>::const_iterator									Iterator2=find(Vector.cbegin(),Vector.cend(),50);

	wcout << L"DISTANCE (20,50) - [" << distance(Iterator1,Iterator2) << L"] !" << endl;
	wcout << L"DISTANCE (50,20) - [" << distance(Iterator2,Iterator1) << L"] !" << endl;
	wcout << L"DISTANCE (20,20) - [" << distance(Iterator1,Iterator1) << L"] !" << endl;
	wcout << L"DISTANCE (20,END) - [" << distance(Iterator1,Vector.cend()) << L"] !" << endl;

	PrintLineSeparator();

	// Pouziva BIDIRECTIONAL ITERATORS.
	list<int>													List({10,20,30,40,50});

	PrintCollection(L"List",List);

	PrintLineSeparator();

	list<int>::const_iterator									Iterator3=find(List.cbegin(),List.cend(),20);
	list<int>::const_iterator									Iterator4=find(List.cbegin(),List.cend(),50);

	wcout << L"DISTANCE (20,50) - [" << distance(Iterator3,Iterator4) << L"] !" << endl;

	// !!!!! Sposobi RUNTIME ERROR, pretoze ITERATOR v 1. PARAMETER sa MUSI odkazovat PRED, alebo na ROVNAKU POSITION ako ITERATOR v 2. PARAMETER.
	//wcout << L"DISTANCE (50,20) - [" << distance(Iterator4,Iterator3) << L"] !" << endl;

	wcout << L"DISTANCE (20,20) - [" << distance(Iterator3,Iterator3) << L"] !" << endl;
	wcout << L"DISTANCE (20,END) - [" << distance(Iterator3,List.cend()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIterSwap(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// ITERATORS MUSIA byt NON-CONST.
	vector<int>::iterator										Iterator1=find(Vector.begin(),Vector.end(),20);
	vector<int>::iterator										Iterator2=find(Vector.begin(),Vector.end(),50);

	iter_swap(Iterator1,Iterator2);

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReverseIterator(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50,60,70});

	wcout << L"VECTOR [";

	for(vector<int>::const_iterator RandomAccessIterator=Vector.cbegin();RandomAccessIterator!=Vector.cend();RandomAccessIterator++)
	{
		if (RandomAccessIterator!=Vector.cbegin())
		{
			wcout << L" ";
		}

		wcout << *RandomAccessIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=find(Vector.begin(),Vector.end(),20);

	wcout << L"ITERATOR 1 - [" << *Iterator1 << L"] !" << endl;

	// !!! Konverzia normalneho ITERATOR na REVERSE ITERATOR.
	// !!!!! Pri konverzii dochadza k posunu ITERATOR o 1 POSITION DOZADU.
	vector<int>::const_reverse_iterator							ReverseIterator1(Iterator1);

	// REVERSE ITERATOR ukazuje na ITEM '10'.
	wcout << L"REVERSE ITERATOR 1 - [" << *ReverseIterator1 << L"] !" << endl;

	// !!! Konverzia REVERSE ITERATOR na normalny ITERATOR pomocou METHOD base().
	// !!!!! Pri konverzii dochadza k posunu ITERATOR o 1 POSITION DOPREDU.
	vector<int>::const_iterator									NormalIterator1=ReverseIterator1.base();

	// NORMAL ITERATOR ukazuje na ITEM '20'.
	wcout << L"NORMAL ITERATOR 1 - [" << *NormalIterator1 << L"] !" << endl;

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator2=find(Vector.begin(),Vector.end(),70);

	wcout << L"ITERATOR 2 - [" << *Iterator2 << L"] !" << endl;

	// !!! Konverzia normalneho ITERATOR na REVERSE ITERATOR.
	// !!!!! Pri konverzii dochadza k posunu ITERATOR o 1 POSITION DOZADU.
	vector<int>::const_reverse_iterator							ReverseIterator2(Iterator2);

	// REVERSE ITERATOR ukazuje na ITEM '60'.
	wcout << L"REVERSE ITERATOR 2 - [" << *ReverseIterator2 << L"] !" << endl;

	// !!! Konverzia REVERSE ITERATOR na normalny ITERATOR pomocou METHOD base().
	// !!!!! Pri konverzii dochadza k posunu ITERATOR o 1 POSITION DOPREDU.
	vector<int>::const_iterator									NormalIterator2=ReverseIterator2.base();

	// NORMAL ITERATOR ukazuje na ITEM '70'.
	wcout << L"NORMAL ITERATOR 2 - [" << *NormalIterator2 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"REVERSE VECTOR [";

	// !!! Pouzije sa REVERSE ITERATOR.
	for(vector<int>::reverse_iterator ReverseRandomAccessIterator=Vector.rbegin();ReverseRandomAccessIterator!=Vector.rend();ReverseRandomAccessIterator++)
	{
		if (ReverseRandomAccessIterator!=Vector.rbegin())
		{
			wcout << L" ";
		}

		wcout << *ReverseRandomAccessIterator;

		// Kedze ITERATOR je MUTABLE, je mozne menit hodnoty ITEMS.
		*ReverseRandomAccessIterator=*ReverseRandomAccessIterator*2;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"REVERSE VECTOR [";

	// !!! Pouzije sa REVERSE ITERATOR.
	for(vector<int>::const_reverse_iterator ConstReverseRandomAccessIterator=Vector.crbegin();ConstReverseRandomAccessIterator!=Vector.crend();ConstReverseRandomAccessIterator++)
	{
		if (ConstReverseRandomAccessIterator!=Vector.rbegin())
		{
			wcout << L" ";
		}

		wcout << *ConstReverseRandomAccessIterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBackInsertIterator(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// Vytvori sa BACK INSERT ITERATOR.
	back_insert_iterator<vector<int>>							BackInsertIterator=back_inserter(Vector);

	// Prida ITEM na KONIEC COLLECTION.
	*BackInsertIterator=100;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// Prida ITEM na KONIEC COLLECTION.
	*BackInsertIterator=200;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFrontInsertIterator(void)
{
	PrintLineSeparator();

	// !!! Kedze VECTOR NEMA METHOD push_front() pouzije sa LIST.
	list<int>													List({10,20,30,40,50});

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// Vytvori sa FRONT INSERT ITERATOR.
	front_insert_iterator<list<int>>							FrontInsertIterator=front_inserter(List);

	// Prida ITEM na ZACIATOK COLLECTION.
	*FrontInsertIterator=100;

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// Prida ITEM na ZACIATOK COLLECTION.
	*FrontInsertIterator=200;

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGeneralInsertIterator(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>::iterator										Iterator=find(Vector.begin(),Vector.end(),30);

	wcout << L"ITERATOR - [" << *Iterator << L"] !" << endl;

	PrintLineSeparator();

	// Vytvori sa GENERAL INSERT ITERATOR, ktory pridava ITEMS PRED ITEM '30'.
	insert_iterator<vector<int>>								GeneralInsertIterator=inserter(Vector,Iterator);

	// Prida ITEM COLLECTION PRED ITEM '30'.
	*GeneralInsertIterator=100;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// Prida ITEM COLLECTION PRED ITEM '30'.
	*GeneralInsertIterator=200;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOutputStreamIterator(void)
{
	PrintLineSeparator();

	wstringstream												Stream;

	ostream_iterator<int,wchar_t>								Iterator1(Stream);

	*Iterator1=10;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator1=20;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	// !!! Je to EMPTY OPERATION.
	(void)*Iterator1++;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator1=30;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	// Definuje sa aj SEPARATOR.
	ostream_iterator<int,wchar_t>								Iterator2(Stream,L" ");

	*Iterator2=10;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator2=20;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	// !!! Je to EMPTY OPERATION.
	(void)*Iterator2++;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator2=30;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	ostream_iterator<wstring,wchar_t>								Iterator3(Stream,L" ");

	*Iterator3=L"AAA";

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator3=L"BBB";

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	ostream_iterator<CPerson,wchar_t>								Iterator4(Stream);

	*Iterator4=CPerson(L"Timmy",12);

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInputStreamIterator(void)
{
	PrintLineSeparator();

	// !!! EMPTY INPUT STREAM ITERATOR sluzi ako identifikator EOR, alebo ERROR.
	istream_iterator<int,wchar_t>								ErrorEof1;
	istream_iterator<CPerson,wchar_t>							ErrorEof2;
	bool														AddSeparator;

	wstringstream												Stream1(L"100 200 300");
	istream_iterator<int,wchar_t>								Iterator1(Stream1);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator1!=ErrorEof1)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		int														Item=*Iterator1;

		wcout << Item;

		Iterator1++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream1.eof() << L"] GOOD [" << Stream1.good() << L"] !" << L"] BAD [" << Stream1.bad() << L"] !" << L"] FAIL [" << Stream1.fail() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Obsahuje NON-INTEGER, ktory bude vyhodnoteny ako ERROR.
	wstringstream												Stream2(L"100 200zzz300");
	istream_iterator<int,wchar_t>								Iterator2(Stream2);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator2!=ErrorEof1)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		int														Item=*Iterator2;

		wcout << Item;

		Iterator2++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream2.eof() << L"] GOOD [" << Stream2.good() << L"] !" << L"] BAD [" << Stream2.bad() << L"] !" << L"] FAIL [" << Stream2.fail() << L"] !" << endl;

	PrintLineSeparator();

	wstringstream												Stream3(L"{Timmy 12}{Jenny 13}");
	istream_iterator<CPerson,wchar_t>							Iterator3(Stream3);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator3!=ErrorEof2)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		CPerson													Item=*Iterator3;

		wcout << Item;

		Iterator3++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream3.eof() << L"] GOOD [" << Stream3.good() << L"] !" << L"] BAD [" << Stream3.bad() << L"] !" << L"] FAIL [" << Stream3.fail() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Chybny format.
	wstringstream												Stream4(L"{Timmy 12{Jenny 13}");
	istream_iterator<CPerson,wchar_t>							Iterator4(Stream4);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator4!=ErrorEof2)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		CPerson													Item=*Iterator4;
		
		wcout << Item;

		Iterator4++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream4.eof() << L"] GOOD [" << Stream4.good() << L"] !" << L"] BAD [" << Stream4.bad() << L"] !" << L"] FAIL [" << Stream4.fail() << L"] !" << endl;

	PrintLineSeparator();

	wstringstream												Stream5(L"100 200 300 400 500 600 700");
	istream_iterator<int,wchar_t>								Iterator5(Stream5);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator5!=ErrorEof1)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		int														Item=*Iterator5;

		wcout << Item;

		Iterator5++;

		// Preskoci nasledujuci ITEM.
		Iterator5++;

		// Preskoci nasledujuci ITEM.
		advance(Iterator5,1);
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream5.eof() << L"] GOOD [" << Stream5.good() << L"] !" << L"] BAD [" << Stream5.bad() << L"] !" << L"] FAIL [" << Stream5.fail() << L"] !" << endl;
	
	PrintLineSeparator();

	wstringstream												Stream6(L"{Timmy 12}{Jenny 13}");
	istream_iterator<CPerson,wchar_t>							Iterator6(Stream6);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator6!=ErrorEof2)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// !!! Citaju sa MEMBERS daneho ITEM pomocou OPERATOR->.
		wstring													Name=Iterator6->GetName();
		int														Age=Iterator6->GetAge();

		wcout << L"[";
		wcout << Name;
		wcout << L" ";
		wcout << Age;
		wcout << L"]";

		Iterator6++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream6.eof() << L"] GOOD [" << Stream6.good() << L"] !" << L"] BAD [" << Stream6.bad() << L"] !" << L"] FAIL [" << Stream6.fail() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMoveIterator(void)
{
	PrintLineSeparator();

	{
		list<CString>											List({CString(L"10"),CString(L"20"),CString(L"30")});

		PrintCollection(L"LIST",List);

		PrintLineSeparator();

		// Pouzije sa COPY SEMANTICS.
		vector<CString>											Vector1(List.begin(),List.end());

		PrintCollection(L"LIST",List);
		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// Pouzije sa MOVE SEMANTICS.
		// !!!!! Pocet ITEMS v SOURCE COLLECTION 'List' NEZMENI, no SOURCE COLLECTION 'List' obsahuje PRAZDNE STRINGS.
		vector<CString>											Vector2(make_move_iterator(List.begin()),make_move_iterator(List.end()));

		PrintLineSeparator();

		// !!! LIST obsahuje stale 3 ITEMS.
		wcout << L"LIST - LENGTH [" << List.size() << L"] !" << endl;
		wcout << L"VECTOR 1 - LENGTH [" << Vector1.size() << L"] !" << endl;
		wcout << L"VECTOR 2 - LENGTH [" << Vector2.size() << L"] !" << endl;

		PrintLineSeparator();

		// !!! LIST obsahuje stale 3 PRAZDNE ITEMS, kedze ITEMS boli presunute pomocou MOVE SEMANTICS.
		PrintCollection(L"LIST",List);
		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIteratorTraits(void)
{
	PrintLineSeparator();

	PrintIteratorTraits<vector<int>::iterator>(L"VECTOR<INT>");

	PrintLineSeparator();

	PrintIteratorTraits<forward_list<double>::iterator>(L"FORWARD_LIST<DOUBLE>");

	PrintLineSeparator();

	PrintIteratorTraits<list<CPerson>::iterator>(L"LIST<CPerson>");

	PrintLineSeparator();

	// !!! Aj POINTER je ITERATOR.
	PrintIteratorTraits<array<int*,5>::iterator>(L"ARRAY<INT*,5>");

	PrintLineSeparator();

	PrintIteratorTraits<back_insert_iterator<vector<int>>>(L"BACK_INSERT_ITERATOR<VECTOR<INT*>>");

	PrintLineSeparator();
	
	PrintIteratorTraits<istream_iterator<int>>(L"ISTREAM_ITERATOR<INT>");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Emulacia pouzitia ITERATOR TRAITS v GENERIC ALGORITHM.
template<typename TIterator>
void PrintItemsAlgorithm(TIterator Begin, TIterator End)
{
	using														TValueType=typename iterator_traits<TIterator>::value_type;

	TIterator													Iterator=Begin;

	wcout << L"VALUES [";

	while(Iterator!=End)
	{
		// TEMPORARY VARIABLE sluzi iba na simulaciu pouzitia ITERATOR TRAITS.
		TValueType												TemporaryValue=*Iterator;

		if (Iterator!=Begin)
		{
			wcout << L" ";
		}

		wcout << TemporaryValue;

		Iterator++;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestUseIteratorTraits1(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintItemsAlgorithm(Vector.cbegin(),Vector.cend());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Specificky ALGORITHM pre FORWARD ITERATORS.
// !!!!! Posledny PARAMETER urcuje ITERATOR CATEGORY.
template<typename TIterator>
void InternalPrintItemsAlgorithmByIteratorCategory(TIterator Begin, TIterator End, forward_iterator_tag)
{
	using														TValueType=typename iterator_traits<TIterator>::value_type;

	TIterator													Iterator=Begin;

	wcout << L"FORWARD ITERATOR - VALUES [";

	while(Iterator!=End)
	{
		// TEMPORARY VARIABLE sluzi iba na simulaciu pouzitia ITERATOR TRAITS.
		TValueType												TemporaryValue=*Iterator;

		if (Iterator!=Begin)
		{
			wcout << L" ";
		}

		wcout << TemporaryValue;

		Iterator++;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!! Specificky ALGORITHM pre RANDOM-ACCESS ITERATORS.
// !!!!! Posledny PARAMETER urcuje ITERATOR CATEGORY.
template<typename TIterator>
void InternalPrintItemsAlgorithmByIteratorCategory(TIterator Begin, TIterator End, random_access_iterator_tag)
{
	using														TValueType=typename iterator_traits<TIterator>::value_type;

	TIterator													Iterator=Begin;

	wcout << L"RANDOM ACCESS ITERATOR - VALUES [";

	while(Iterator!=End)
	{
		// TEMPORARY VARIABLE sluzi iba na simulaciu pouzitia ITERATOR TRAITS.
		TValueType												TemporaryValue=*Iterator;

		if (Iterator!=Begin)
		{
			wcout << L" ";
		}

		wcout << TemporaryValue;

		Iterator++;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!! Emulacia pouzitia ITERATOR TRAITS v GENERIC ALGORITHM.
template<typename TIterator>
void PrintItemsAlgorithmByIteratorCategory(TIterator Begin, TIterator End)
{
	using														TIteratorCategory=typename iterator_traits<TIterator>::iterator_category;

	// !!! Podla CATEGORY sa pouzije ina verzia FUNCTION.
	InternalPrintItemsAlgorithmByIteratorCategory(Begin,End,TIteratorCategory());
}
//-----------------------------------------------------------------------------
void TestUseIteratorTraits2(void)
{
	PrintLineSeparator();

	list<int>													List({100,200,300,400,500});

	PrintItemsAlgorithmByIteratorCategory(List.cbegin(),List.cend());

	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintItemsAlgorithmByIteratorCategory(Vector.cbegin(),Vector.cend());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TIterator>
typename iterator_traits<TIterator>::difference_type InternalDistance(TIterator Begin, TIterator End, forward_iterator_tag)
{
	typename iterator_traits<TIterator>::difference_type		Distance=0;

	// !!! Kedze ITERATOR NIE je RANDOM-ACCESS ITERATOR, je NUTNE iterovat cez COLLECTION.
	while(Begin!=End)
	{
		Distance++;

		Begin++;
	}

	return(Distance);
}
//-----------------------------------------------------------------------------
template<typename TIterator>
typename iterator_traits<TIterator>::difference_type InternalDistance(TIterator Begin, TIterator End, random_access_iterator_tag)
{
	// !!! Kedze ITERATOR je RANDOM-ACCESS ITERATOR, je mozne pouzit OPERATOR-.
	typename iterator_traits<TIterator>::difference_type		Distance=End-Begin;

	return(Distance);
}
//-----------------------------------------------------------------------------
template<typename TIterator>
typename iterator_traits<TIterator>::difference_type Distance(TIterator Begin, TIterator End)
{
	using														TIteratorCategory=typename iterator_traits<TIterator>::iterator_category;

	// !!! Podla CATEGORY sa pouzije ina verzia FUNCTION.
	return(InternalDistance(Begin,End,TIteratorCategory()));
}
//-----------------------------------------------------------------------------
void TestUseIteratorTraits3(void)
{
	PrintLineSeparator();

	list<int>													List({100,200,300,400,500});

	PrintCollection(L"LIST",List);

	iterator_traits<list<int>::const_iterator>::difference_type	ListSize=Distance(List.cbegin(),List.cend());

	wcout << L"LIST SIZE [" << ListSize << L"] !" << endl;

	PrintLineSeparator();

	vector<int>													Vector({10,20,30});

	PrintCollection(L"VECTOR",Vector);

	iterator_traits<vector<int>::const_iterator>::difference_type	VectorSize=Distance(Vector.cbegin(),Vector.cend());

	wcout << L"VECTOR SIZE [" << VectorSize << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomIterator(void)
{
	PrintLineSeparator();

	list<int>													List({100,200,300});

	PrintCollection(L"LIST",List);

	CCustomIterator<list<int>>									IteratorListBegin(List,List.begin());
	CCustomIterator<list<int>>									IteratorListEnd(List,List.end());
	CCustomIterator<list<int>>									IteratorList=IteratorListBegin;

	// Just for TESTING PURPOSES.
	//IteratorList=IteratorListBegin;

	wcout << L"LIST [";

	while(IteratorList!=IteratorListEnd)
	{
		if (IteratorList!=IteratorListBegin)
		{
			wcout << L" ";
		}
		/*
		// Just for TESTING PURPOSES.
		else if (IteratorList==IteratorListBegin)
		{
			wcout << L"!!!";
		}
		*/

		wcout << *IteratorList;

		IteratorList++;
		// Just for TESTING PURPOSES.
		//++IteratorList;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	vector<CPerson>												Vector({CPerson(L"TIMMY",12),CPerson(L"JENNY",13)});

	PrintCollection(L"VECTOR",Vector);

	CCustomIterator<vector<CPerson>>							IteratorVectorBegin(Vector,Vector.begin());
	CCustomIterator<vector<CPerson>>							IteratorVectorEnd(Vector,Vector.end());
	CCustomIterator<vector<CPerson>>							IteratorVector=IteratorVectorBegin;

	wcout << L"VECTOR [";

	while(IteratorVector!=IteratorVectorEnd)
	{
		if (IteratorVector==IteratorVectorBegin)
		{
			// EMPTY.
		}
		else
		{
			wcout << L" ";
		}

		// !!! Na pristup k MEMBER jednotlivych ITEMS sa pouziva OPERATOR->().
		wcout << L"(";
		wcout << IteratorVector->GetName();
		wcout << L" ";
		wcout << IteratorVector->GetAge();
		wcout << L")";

		++IteratorVector;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestOutputIterator();
	//TestInputIterator();
	//TestForwardIterator();
	//TestBidirectionalIterator();
	//TestRandomAccessIterator();
	//TestIteratorPortabilityProblem();
	//TestAdvance();
	//TestNext();
	//TestPrev();
	//TestDistance();
	//TestIterSwap();
	//TestReverseIterator();
	//TestBackInsertIterator();
	//TestFrontInsertIterator();
	//TestGeneralInsertIterator();
	//TestOutputStreamIterator();
	//TestInputStreamIterator();
	//TestMoveIterator();
	//TestIteratorTraits();
	//TestUseIteratorTraits1();
	//TestUseIteratorTraits2();
	//TestUseIteratorTraits3();
	TestCustomIterator();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------