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
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <forward_list>
#include <list>
#include <array>
#include <numeric>
#include "MyDebug.h"
#include "CPerson.h"
#include "CCustomIterator.h"
#include "CString.h"
#include "CSimpleObject.h"
#include "CSumFunctionObject.h"
#include "CFunctor.h"
#include "CName.h"
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::placeholders;
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
template<typename TType, typename TCompare>
void PrintSet(const wstring& Prefix, const set<TType,TCompare>& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const typename set<TType,TCompare>::value_type& Item : Collection)
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
template<typename TType, typename TCompare>
void PrintMultiSet(const wstring& Prefix, const multiset<TType,TCompare>& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const typename multiset<TType,TCompare>::value_type& Item : Collection)
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
template<typename TKey, typename TValue, typename TCompare>
void PrintMap(const wstring& Prefix, const map<TKey,TValue,TCompare>& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const typename map<TKey,TValue,TCompare>::value_type& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << L"[" << Item.first << "]=[" << Item.second << "]";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename TCompare>
void PrintMultiMap(const wstring& Prefix, const multimap<TKey,TValue,TCompare>& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const typename multimap<TKey,TValue,TCompare>::value_type& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << L"[" << Item.first << "]=[" << Item.second << "]";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename THash, typename TCompare>
void PrintUnorderedMap(const wstring& Prefix, const unordered_map<TKey,TValue,THash,TCompare>& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const typename map<TKey,TValue,THash>::value_type& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << L"[" << Item.first << "]=[" << Item.second << "]";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename THash, typename TCompare>
void PrintUnorderedMultiMap(const wstring& Prefix, const unordered_multimap<TKey,TValue,THash,TCompare>& Collection)
{
	wcout << Prefix;
	wcout << L" [";

	bool														PrintSeparator=false;

	for(const typename multimap<TKey,TValue,THash>::value_type& Item : Collection)
	{
		if (PrintSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			PrintSeparator=true;
		}

		wcout << L"[" << Item.first << "]=[" << Item.second << "]";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
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
void TestCArrayCollection(void)
{
	PrintLineSeparator();

	int															Array[5]{40,50,30,10,20};

	wcout << L"ARRAY [";

	// !!! Pouzije sa FUNCTION begin() a FUNCTION end() na iterovanie danym ARRAY.
	for(int* Iterator=begin(Array);Iterator!=end(Array);Iterator++)
	{
		if (Iterator!=begin(Array))
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"ARRAY [";

	// !!! Pouzije sa FUNCTION cbegin() a FUNCTION cend() na iterovanie danym ARRAY.
	for(const int* Iterator=cbegin(Array);Iterator!=cend(Array);Iterator++)
	{
		if (Iterator!=cbegin(Array))
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Pouzitie ALGORITHM s vyuzitim C-ARRAY ITERATORS.
	sort(begin(Array),end(Array));

	wcout << L"ARRAY [";

	// !!! Pouzije sa FUNCTION cbegin() a FUNCTION cend() na iterovanie danym ARRAY.
	for(const int* Iterator=cbegin(Array);Iterator!=cend(Array);Iterator++)
	{
		if (Iterator!=cbegin(Array))
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
void TestSTLCollection(void)
{
	PrintLineSeparator();

	vector<int>													Array({40,50,30,10,20});

	wcout << L"STL COLLECTION [";

	// !!! Pouzije sa FUNCTION begin() a FUNCTION end() na iterovanie danou COLLECTION.
	for(vector<int>::iterator Iterator=begin(Array);Iterator!=end(Array);Iterator++)
	{
		if (Iterator!=begin(Array))
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"STL COLLECTION [";

	// !!! Pouzije sa FUNCTION cbegin() a FUNCTION cend() na iterovanie danou COLLECTION.
	for(vector<int>::const_iterator Iterator=cbegin(Array);Iterator!=cend(Array);Iterator++)
	{
		if (Iterator!=cbegin(Array))
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Pouzitie ALGORITHM s vyuzitim C-ARRAY ITERATORS.
	sort(begin(Array),end(Array));

	wcout << L"STL COLLECTION [";

	// !!! Pouzije sa FUNCTION cbegin() a FUNCTION cend() na iterovanie danou COLLECTION.
	for(vector<int>::const_iterator Iterator=cbegin(Array);Iterator!=cend(Array);Iterator++)
	{
		if (Iterator!=cbegin(Array))
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
void TestPredefinedFunctionObjects(void)
{
	PrintLineSeparator();

	wcout << L"FUNCTION OBJECT - NEGATE(10) [" << negate<int>()(10) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - PLUS(10,5) [" << plus<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - MINUS(10,5) [" << minus<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - MULTIPLES(10,5) [" << multiplies<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - DIVIDES(10,5) [" << divides<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - MODULUS(10,6) [" << modulus<int>()(10,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - EQUAL_TO(10,5) [" << equal_to<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - NOT_EQUAL_TO(10,5) [" << not_equal_to<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LESS(10,5) [" << less<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - GREATER(10,5) [" << greater<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LESS_EQUAL(10,5) [" << less_equal<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - GREATER_EQUAL(10,5) [" << greater_equal<int>()(10,5) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LOGICAL_NOT(10) [" << logical_not<int>()(10) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LOGICAL_AND(0,6) [" << logical_and<int>()(0,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - LOGICAL_OR(15,0) [" << logical_or<int>()(15,0) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_NOT(13) [" << bit_not<int>()(13) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_AND(13,6) [" << bit_and<int>()(13,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_OR(13,6) [" << bit_or<int>()(13,6) << L"] !" << endl;
	wcout << L"FUNCTION OBJECT - BIT_XOR(13,6) [" << bit_xor<int>()(13,6) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFunction(int Parameter1, int Parameter2, int Parameter3, int Parameter4)
{
	wcout << L"PARAMETER_1 [" << Parameter1 << "], PARAMETER_2 [" << Parameter2 << "], PARAMETER_3 [" << Parameter3 << "], PARAMETER_4 [" << Parameter4 << "] !" << endl;
}
//-----------------------------------------------------------------------------
void FunctionWithMultipleParameters(int Parameter1, int Parameter2, int Parameter3, int Parameter4, int Parameter5)
{
	wcout << L"PARAMETER_1 [" << Parameter1 << "], PARAMETER_2 [" << Parameter2 << "], PARAMETER_3 [" << Parameter3 << "], PARAMETER_4 [" << Parameter4 << "], PARAMETER_5 [" << Parameter5 << "] !" << endl;
}
//-----------------------------------------------------------------------------
void TestBind1(void)
{
	PrintLineSeparator();

	// Nasledujuci CODE vytvori NOVY CALLABLE OBJECT, ktory bude mat 2 PARAMETERS. PARAMETERS FUNCTION bind() maju nasledujuci vyznam.
	// A. PARAMETER 'TestFunction' reprezentuje CALLABLE OBJECT, ktory ma novovytvoreny CALLABLE OBJECT obalovat.
	// B. PARAMETER '100' reprezentuje 1. PARAMETER FUNCTION TestFunction(). Pri volani CALLABLE OBJECT 'CallableObject' bude 1. PARAMETER FUNCTION TestFunction() VZDY subsitutovany hodnotou 100.
	// C. PARAMETER '_1' reprezentuje 2. PARAMETER FUNCTION TestFunction(). Kedze sa pouzil PLACEHOLDER [_1], tak pri volani CALLABLE OBJECT 'CallableObject' bude tento PLACEHOLDER nahradeny 1. PARAMETER pouzitym pri volani CALLABLE OBJECT 'CallableObject'.
	// D. PARAMETER '_2' reprezentuje 3. PARAMETER FUNCTION TestFunction(). Kedze sa pouzil PLACEHOLDER [_2], tak pri volani CALLABLE OBJECT 'CallableObject' bude tento PLACEHOLDER nahradeny 2. PARAMETER pouzitym pri volani CALLABLE OBJECT 'CallableObject'.
	// E. PARAMETER '200' reprezentuje 4. PARAMETER FUNCTION TestFunction(). Pri volani CALLABLE OBJECT 'CallableObject' bude 4. PARAMETER FUNCTION TestFunction() VZDY subsitutovany hodnotou 200.
	auto														CallableObject1=bind(TestFunction,100,_1,_2,200);

	// !!!!! Nasledujuce CODE sa intepretuje ako volanie FUNCTION [TestFunction(100,77,888,200)].
	CallableObject1(777,888);

	PrintLineSeparator();

	FunctionWithMultipleParameters(10,20,30,40,50);

	PrintLineSeparator();

	// !!!!! FUNCTION bind() vytvori sa CALLABLE OBJECT, ktory definuje 3 ARGUMENTS a 2 ARGUMENTS (1. a 3.) nahradi PLACEHOLDERS, ktore budu reprezentovat PARAMETERS vrateneho CALLABLE OBJECT.
	// !!!!! Vysledny CALLABLE OBJECT bude mat namiest 5 iba 2 PARAMETERS.
	auto														CallableObject2=bind(FunctionWithMultipleParameters,_2,111,_1,666,888);

	// !!! Hodnota '11' bude nahradi 1. PLACEHOLDER, ktory reprezentuje 3. PARAMETER FUNCTION FunctionWithMultipleParameters().
	// !!! Hodnota '22' bude nahradi 2. PLACEHOLDER, ktory reprezentuje 1. PARAMETER FUNCTION FunctionWithMultipleParameters().
	CallableObject2(11,22);

	PrintLineSeparator();

	// !!! Kedze sa pouzili PLACEHOLDERS [_3] a [_4], tak vrateny CALLABLE OBJECT MUSI mat 4 PARAMETERS.
	auto														CallableObject3=bind(FunctionWithMultipleParameters,_3,111,_4,666,888);

	// !!!!! CALLABLE OBJECT ma 4 PARAMETERS, alebo  1. a 2. PARAMETER sa NEPOUZIJU, pretoze nemaju svoje PLACEHOLDERS.
	CallableObject3(11,22,33,44);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind2(void)
{
	PrintLineSeparator();

	// !!!!! FUNCTION bind() z BINARY OPERATOR spravi CALLABLE OBJECT, ktory ma 1 PARAMETER a chova sa ako UNARY OPERATOR.
	// !!!!! Hodnota 10 sa namapuje ako 1. PARAMETER povodneho FUNCTION OBJECT [plus<int>]. 2. PARAMETER bude substituovanym PARAMETER, ktory sa zada pri volani novovytvoreneho CALLABLE OBJECT.
	auto														CallableObject1=bind(plus<int>(),10,_1);
	// Explicitne zavolanie CALLABLE OBJECT vrateneho FUNCTION bind().
	auto														Result1=CallableObject1(7);

	wcout << L"RESULT 1 [" <<  Result1 << L"] !" << endl;

	const type_info&											TypeInfo1=typeid(Result1);

	if (TypeInfo1==typeid(int))
	{
		wcout << L"RESULT 1 TYPE [int] !" << endl;
	}
	else
	{
		wcout << L"RESULT 1 TYPE [UNEXPECTED] !" << endl;
	}

	PrintLineSeparator();

	// !!! Pouziva sa verzia FUNCTION bind(), ktora umoznuje definovat RETURN VALUE TYPE.
	auto														CallableObject2=bind<double>(plus<int>(),_1,10);
	// Explicitne zavolanie CALLABLE OBJECT vrateneho FUNCTION bind().
	auto														Result2=CallableObject2(7);

	wcout << L"RESULT 2 [" << Result2 << L"] !" << endl;

	const type_info&											TypeInfo2=typeid(Result2);
	
	// !!! Kontrola ci RETURN TYPE je naozaj [double].
	if (TypeInfo2==typeid(double))
	{
		wcout << L"RESULT 2 TYPE [double] !" << endl;
	}
	else
	{
		wcout << L"RESULT 2 TYPE [UNEXPECTED] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind3(void)
{
	PrintLineSeparator();

	vector<CSimpleObject>										Object;

	Object.push_back(CSimpleObject(10));
	Object.push_back(CSimpleObject(20));
	Object.push_back(CSimpleObject(30));
	Object.push_back(CSimpleObject(40));
	Object.push_back(CSimpleObject(50));

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	auto														CallableObject1=bind(&CSimpleObject::PrintValue,_1);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	for_each(Object.begin(),Object.end(),CallableObject1);

	PrintLineSeparator();

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	// !!! PLACEHOLDER [_2] reprezentuje CUSTOM PARAMETER.
	// !!! Kedze sa pouzili 2 PLACEHOLDERS, tak vrateny CALLABLE OBJECT ma 2 PARAMETERS.
	auto														TempCallableObject=bind(&CSimpleObject::AddAndPrintValue,_1,_2);

	// !!! Kedze CALLABLE OBJECT 'TempCallableObject' ma 2 PARAMETERS a ALGORITHM for_each() vyzaduje CALLABLE OBJECT s 1 PARAMETER, je nutne vytvorit CALLABLE OBJECT s 1 PARAMETER.
	auto														CallableObject2=bind(TempCallableObject,_1,6);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	for_each(Object.begin(),Object.end(),CallableObject2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind4(void)
{
	PrintLineSeparator();

	vector<CSimpleObject*>										Objects;

	Objects.push_back(new CSimpleObject(10));
	Objects.push_back(new CSimpleObject(20));
	Objects.push_back(new CSimpleObject(30));
	Objects.push_back(new CSimpleObject(40));
	Objects.push_back(new CSimpleObject(50));

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	auto														CallableObject=bind(&CSimpleObject::PrintValue,_1);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	// !!! FUNCTION je volana pre POINTERS.
	for_each(Objects.begin(),Objects.end(),CallableObject);

	for(CSimpleObject* Object : Objects)
	{
		delete(Object);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind5(void)
{
	PrintLineSeparator();

	vector<shared_ptr<CSimpleObject>>							Objects;

	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(10)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(20)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(30)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(40)));
	Objects.push_back(shared_ptr<CSimpleObject>(new CSimpleObject(50)));

	// !!! PLACEHOLDER [_1] reprezentuje THIS POINTER.
	auto														CallableObject=bind(&CSimpleObject::PrintValue,_1);

	// !!! Vrateny CALLABLE OBJECT ma 1 PARAMETER, ktory sa substituuje za THIS POINTER.
	// !!! FUNCTION je volana pre SHARED POINTERS.
	for_each(Objects.begin(),Objects.end(),CallableObject);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBind6(void)
{
	PrintLineSeparator();

	CSumFunctionObject											FunctionObject;

	// !!! FUNCTION bind() sa pouzije na CUSTOM FUNCTION OBJECT.
	auto														CallableObject=bind(FunctionObject,10,_1);

	wcout << L"RESULT [" << CallableObject(2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBindMemberFunction(void)
{
	PrintLineSeparator();

	auto														CallableMethod1=mem_fn(&CSimpleObject::PrintValue);

	CallableMethod1(CSimpleObject(10));

	PrintLineSeparator();

	auto														CallableMethod2=mem_fn(&CSimpleObject::PrintValuePrefixPostfix);

	CallableMethod2(CSimpleObject(20),L"<<<",L">>>");

	PrintLineSeparator();

	vector<CSimpleObject>										Objects;

	Objects.push_back(CSimpleObject(10));
	Objects.push_back(CSimpleObject(20));
	Objects.push_back(CSimpleObject(30));
	Objects.push_back(CSimpleObject(40));
	Objects.push_back(CSimpleObject(50));

	auto														CallableMethod3=mem_fn(&CSimpleObject::PrintValuePrefixPostfix);

	for_each(Objects.begin(),Objects.end(),bind(CallableMethod3,_1,L"<",L">"));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBindField(void)
{
	PrintLineSeparator();

	map<wstring,int>											Map;

	Map[L"1"]=11;
	Map[L"2"]=22;
	Map[L"3"]=33;

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	plus<int>													Plus;

	// Pouziva sa FIELD 'map<wstring,int>::value_type::second'.
	// !!! PLACEHOLDER '_1' reprezentuje kumulativnu VALUE a je typu 'int'.
	// !!! PLACEHOLDER '_2' reprezentuje ITEM danej MAP a je typu 'pair<const wstring,int>'.
	// !!!!! CODE [bind(&map<wstring,int>::value_type::second,_2)] vola FIELD 'map<wstring,int>::value_type::second' pre PLACEHOLDER, ktory reprezentuje ITEM danej MAP. Vysledkom je ziskanie VALUE pre kazdy KEY danej MAP.
	auto														Bind=bind(Plus,_1,bind(&map<wstring,int>::value_type::second,_2));

	int															Sum=accumulate(Map.begin(),Map.end(),0,Bind);

	wcout << L"MAP SUM [" << Sum << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int Add(int X, int Y)
{
	return(X+Y);
}
//-----------------------------------------------------------------------------
int Subtract(int X, int Y)
{
	return(X-Y);
}
//-----------------------------------------------------------------------------
int Multiple(int X, int Y)
{
	return(X*Y);
}
//-----------------------------------------------------------------------------
int Divide(int X, int Y)
{
	return(X/Y);
}
//-----------------------------------------------------------------------------
void TestFunctionWrapper(void)
{
	PrintLineSeparator();

	// FUNCTIONS je mozne vdaka CLASS [function<R(TArgs...)>] ukladat do COLLECTIONS.
	list<function<int(int,int)>>								Functions;

	Functions.push_back(Add);
	Functions.push_back(Subtract);
	Functions.push_back(Multiple);
	Functions.push_back(Divide);
	// CLASS [function<R(TArgs...)>] reprezentuje aj LAMBDA FUNCTIONS.
	Functions.push_back([](int X, int Y){return(Y-X);});
	// CLASS [function<R(TArgs...)>] reprezentuje FUNCTOR.
	Functions.push_back(CFunctor());

	for(function<int(int,int)>& Function : Functions)
	{
		wprintf_s(L"FUNCTION(10,2) [%d] !\n",Function(10,2));
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMethodWrapper(void)
{
	PrintLineSeparator();

	CName														Name(L"Timmy",L"Anderson",12);

	// !!! CLASS [function<R(TArgs...)>] moze reprezentovat aj METHODS.
	// !!! 1. PARAMETER je skryty THIS POINTER reprezentujuci CLASS, v ktorej je METHOD definovana.
	function<void(CName&,wstring,wstring)>						Method=&CName::PrintName;

	Method(Name,L"This is",L"!\n");

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
	//TestIteratorTraits();
	//TestUseIteratorTraits1();
	//TestUseIteratorTraits2();
	//TestUseIteratorTraits3();
	//TestCustomIterator();
	//TestReverseIterator();
	//TestBackInsertIterator();
	//TestFrontInsertIterator();
	//TestGeneralInsertIterator();
	//TestMoveIterator();
	//TestCArrayCollection();
	//TestSTLCollection();
	//TestPredefinedFunctionObjects();
	//TestBind1();
	//TestBind2();
	//TestBind3();
	//TestBind4();
	//TestBind5();
	//TestBind6();
	//TestBindMemberFunction();
	//TestBindField();
	//TestFunctionWrapper();
	TestMethodWrapper();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------