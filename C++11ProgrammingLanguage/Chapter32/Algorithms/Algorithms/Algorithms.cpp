//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <memory>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <random>
#include "MyDebug.h"
#include "CPrintFunctionObject1.h"
#include "CPrintFunctionObject2.h"
#include "CCountFunctionObject.h"
#include "CModifyingFunctionObject.h"
#include "CIsLesserComparer.h"
#include "CInt.h"
#include "CKeyValue.h"
//-----------------------------------------------------------------------------
#undef min
#undef max
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool															GIsFirst;
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
void ForEachPrint(const int& Value)
{
	if (GIsFirst==true)
	{
		GIsFirst=false;
	}
	else
	{
		wcout << L" ";
	}

	wcout << Value;
}
//-----------------------------------------------------------------------------
void TestForEach1(void)
{
	PrintLineSeparator();

	vector<int>													Collection({10,20,30,40,50});

	wcout << L"COLLECTION - PRINT by FUNCTION OBJECT - by REFERENCE [";

	for_each(Collection.cbegin(),Collection.cend(),CPrintFunctionObject1<int>());

	wcout << L"]" << endl;

	PrintLineSeparator();

	wcout << L"COLLECTION - PRINT by FUNCTION OBJECT - by VALUE [";

	for_each(Collection.cbegin(),Collection.cend(),CPrintFunctionObject2<int>());

	wcout << L"]" << endl;

	PrintLineSeparator();

	wcout << L"COLLECTION - PRINT by FUNCTION [";

	GIsFirst=true;

	for_each(Collection.cbegin(),Collection.cend(),ForEachPrint);

	wcout << L"]" << endl;

	PrintLineSeparator();

	wcout << L"COLLECTION - PRINT by LAMDBA EXPRESSION [";

	bool														IsFirst=true;

	for_each(Collection.cbegin(),Collection.cend(),[&IsFirst](const int& Value)->void{if (IsFirst==true){IsFirst=false;}else{wcout << L" ";}wcout << Value;});

	wcout << L"]" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForEach2(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({10,20,30,40,50});
	vector<int>													Collection2({60,70,80,90,100});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	{
		wcout << L"SUM 1 [" << for_each(Collection1.cbegin(),Collection1.cend(),CCountFunctionObject<int>()).GetSum() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		wcout << L"SUM 2 [" << for_each(Collection2.cbegin(),Collection2.cend(),CCountFunctionObject<int>()).GetSum() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CCountFunctionObject<int>								FunctionObject;

		// !!! Vola sa MOVE OPERATOR.
		FunctionObject=for_each(Collection1.cbegin(),Collection1.cend(),FunctionObject);

		// !!! Vola sa MOVE OPERATOR.
		FunctionObject=for_each(Collection2.cbegin(),Collection2.cend(),FunctionObject);

		wcout << L"SUM [" << FunctionObject.GetSum() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForEach3(void)
{
	PrintLineSeparator();

	vector<int>													Collection({10,20,30,40,50});

	PrintCollection(L"COLLECTION BEFORE FOREACH",Collection);

	// !!! ALGORITHM modifikuje hodnoty ITEMS.
	for_each(Collection.begin(),Collection.end(),CModifyingFunctionObject<int>());

	PrintCollection(L"COLLECTION AFTER FOREACH",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCount(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,8,4,12,5,4});

	PrintCollection(L"COLLECTION",Collection);

	wcout << L"COUNT '4' [" << count(Collection.cbegin(),Collection.cend(),4) << L"] !" << endl;
	wcout << L"COUNT '5' [" << count(Collection.cbegin(),Collection.cend(),5) << L"] !" << endl;
	wcout << L"COUNT '33' [" << count(Collection.cbegin(),Collection.cend(),33) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCountIf(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,8,4,12,5,4,17});

	PrintCollection(L"COLLECTION",Collection);

	wcout << L"COUNT_IF 'VALUE>5' [" << count_if(Collection.cbegin(),Collection.cend(),[](int Value)->bool{return(Value>5);}) << L"] !" << endl;
	wcout << L"COUNT_IF '(VALUE%2)==0' [" << count_if(Collection.cbegin(),Collection.cend(),[](int Value)->bool{return((Value%2)==0);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMinElement(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,1,8,4,1,12,5,4,17,5,17});

	PrintCollection(L"COLLECTION",Collection);

	vector<int>::const_iterator									Iterator1=min_element(Collection.cbegin(),Collection.cend());
	vector<int>::const_iterator									Iterator2=min_element(Collection.cbegin(),Collection.cend(),CIsLesserComparer<int>());

	wcout << L"NUMBER of ITEMS [" << distance(Collection.cbegin(),Collection.cend()) << L"] !" << endl;

	wcout << L"MIN_ELEMENT 1 [" << *Iterator1 << L"] !" << endl;
	wcout << L"MIN_ELEMENT 2 [" << *Iterator2 << L"] !" << endl;
	
	wcout << L"MIN_ELEMENT POSITION 1 [" << distance(Collection.cbegin(),Iterator1) << L"] !" << endl;
	wcout << L"MIN_ELEMENT POSITION 2 [" << distance(Collection.cbegin(),Iterator2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMaxElement(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,1,8,4,1,12,5,4,17,5,17});

	PrintCollection(L"COLLECTION",Collection);

	vector<int>::const_iterator									Iterator1=max_element(Collection.cbegin(),Collection.cend());
	vector<int>::const_iterator									Iterator2=max_element(Collection.cbegin(),Collection.cend(),CIsLesserComparer<int>());

	wcout << L"NUMBER of ITEMS [" << distance(Collection.cbegin(),Collection.cend()) << L"] !" << endl;

	wcout << L"MAX_ELEMENT 1 [" << *Iterator1 << L"] !" << endl;
	wcout << L"MAX_ELEMENT 2 [" << *Iterator2 << L"] !" << endl;
	
	wcout << L"MAX_ELEMENT POSITION 1 [" << distance(Collection.cbegin(),Iterator1) << L"] !" << endl;
	wcout << L"MAX_ELEMENT POSITION 2 [" << distance(Collection.cbegin(),Iterator2) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMinMaxElement(void)
{
	PrintLineSeparator();

	using														Pair=pair<vector<int>::const_iterator,vector<int>::const_iterator>;

	vector<int>													Collection({3,5,6,4,1,8,4,1,12,5,4,17,5,17});

	PrintCollection(L"COLLECTION",Collection);

	Pair														IteratorPair1=minmax_element(Collection.cbegin(),Collection.cend());
	Pair														IteratorPair2=minmax_element(Collection.cbegin(),Collection.cend(),CIsLesserComparer<int>());

	wcout << L"NUMBER of ITEMS [" << distance(Collection.cbegin(),Collection.cend()) << L"] !" << endl;

	wcout << L"MINMAX_ELEMENT 1 [" << *(IteratorPair1.first) << L"," << *(IteratorPair1.second) << L"] !" << endl;
	wcout << L"MINMAX_ELEMENT 2 [" << *(IteratorPair2.first) << L"," << *(IteratorPair2.second) << L"] !" << endl;
	
	wcout << L"MINMAX_ELEMENT POSITION 1 [" << distance(Collection.cbegin(),IteratorPair1.first) << L"," << distance(Collection.cbegin(),IteratorPair1.second) << L"] !" << endl;
	wcout << L"MINMAX_ELEMENT POSITION 2 [" << distance(Collection.cbegin(),IteratorPair2.first) << L"," << distance(Collection.cbegin(),IteratorPair2.second) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFind(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,1,8,4,1,12,5,4,17,5,17});

	PrintCollection(L"COLLECTION",Collection);

	vector<int>::const_iterator									Iterator1=find(Collection.cbegin(),Collection.cend(),8);
	vector<int>::const_iterator									Iterator2=find(Collection.cbegin(),Collection.cend(),15);

	if (Iterator1!=Collection.cend())
	{
		wcout << L"ITEM 8 [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM 8 NOT FOUND !" << endl;
	}

	if (Iterator2!=Collection.cend())
	{
		wcout << L"ITEM 15 [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM 15 NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindIf(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,1,8,4,1,12,5,4,17,5,17});

	PrintCollection(L"COLLECTION",Collection);

	vector<int>::const_iterator									Iterator1=find_if(Collection.cbegin(),Collection.cend(),[](int Value)->bool{return(Value==8);});
	vector<int>::const_iterator									Iterator2=find_if(Collection.cbegin(),Collection.cend(),[](int Value)->bool{return(Value==15);});

	if (Iterator1!=Collection.cend())
	{
		wcout << L"ITEM 8 [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM 8 NOT FOUND !" << endl;
	}

	if (Iterator2!=Collection.cend())
	{
		wcout << L"ITEM 15 [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM 15 NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindIfNot(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,1,8,4,1,12,5,4,17,5,17});

	PrintCollection(L"COLLECTION",Collection);

	vector<int>::const_iterator									Iterator1=find_if_not(Collection.cbegin(),Collection.cend(),[](int Value)->bool{return(Value<10);});
	vector<int>::const_iterator									Iterator2=find_if_not(Collection.cbegin(),Collection.cend(),[](int Value)->bool{return(Value<20);});

	if (Iterator1!=Collection.cend())
	{
		wcout << L"ITEM (VALUE<10) [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM (VALUE<10) NOT FOUND !" << endl;
	}

	if (Iterator2!=Collection.cend())
	{
		wcout << L"ITEM (VALUE<20) [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM (VALUE<20) NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSearchN(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,4,1,8,4,1,12,5,4,4,4,17,5,17});

	PrintCollection(L"COLLECTION",Collection);

	const int													NumberOfItems=3;
	vector<int>::const_iterator									Iterator1=search_n(Collection.cbegin(),Collection.cend(),NumberOfItems,4);
	// 2. PARAMETER BINARY PREDICATE je rovny 4. PARAMETER FUNCTION search_n().
	vector<int>::const_iterator									Iterator2=search_n(Collection.cbegin(),Collection.cend(),NumberOfItems,4,[](int Item, int Value)->bool{return(Item==Value);});

	if (Iterator1!=Collection.cend())
	{
		wcout << L"CONSECUTIVE ITEMS [";

		for(int Index=0;Index<NumberOfItems;Index++)
		{
			if (Index>0)
			{
				wcout << L" ";
			}

			wcout << *Iterator1++;
		}

		wcout << L"] !" << endl;
	}
	else
	{
		wcout << L"CONSECUTIVE ITEMS NOT FOUND !" << endl;
	}

	if (Iterator2!=Collection.cend())
	{
		wcout << L"CONSECUTIVE ITEMS [";

		for(int Index=0;Index<NumberOfItems;Index++)
		{
			if (Index>0)
			{
				wcout << L" ";
			}

			wcout << *Iterator2++;
		}

		wcout << L"] !" << endl;
	}
	else
	{
		wcout << L"CONSECUTIVE ITEMS NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSearch(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,4,1,8,4,1,12,5,4,4,17,5,17,8});
	vector<int>													SearchCollection1({1,12,5,4});
	vector<int>													SearchCollection2({5,16,4});

	PrintCollection(L"COLLECTION",Collection);
	PrintCollection(L"SEARCH COLLECTION 1",SearchCollection1);

	vector<int>::const_iterator									Iterator1=search(Collection.cbegin(),Collection.cend(),SearchCollection1.cbegin(),SearchCollection1.cend());

	if (Iterator1!=Collection.cend())
	{
		wcout << L"SEARCH COLLECTION [";

		for(vector<int>::size_type Index=0;Index<SearchCollection1.size();Index++)
		{
			if (Index>0)
			{
				wcout << L" ";
			}

			wcout << *Iterator1++;
		}

		wcout << L"] !" << endl;
	}
	else
	{
		wcout << L"SEARCH COLLECTION NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	PrintCollection(L"COLLECTION",Collection);
	PrintCollection(L"SEARCH COLLECTION 2",SearchCollection2);

	vector<int>::const_iterator									Iterator2=search(Collection.cbegin(),Collection.cend(),SearchCollection2.cbegin(),SearchCollection2.cend(),[](int Item1, int Item2)->bool{return((Item1+Item2)>20);});

	if (Iterator2!=Collection.cend())
	{
		wcout << L"SEARCH COLLECTION [";

		for(vector<int>::size_type Index=0;Index<SearchCollection2.size();Index++)
		{
			if (Index>0)
			{
				wcout << L" ";
			}

			wcout << *Iterator2++;
		}

		wcout << L"] !" << endl;
	}
	else
	{
		wcout << L"SEARCH COLLECTION NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindEnd(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,17,5,17,4,1,8,4,1,12,5,4,4,17,5,17,1,12,5,4,8});
	vector<int>													SearchCollection1({1,12,5,4});
	vector<int>													SearchCollection2({5,16,4});

	PrintCollection(L"COLLECTION",Collection);
	PrintCollection(L"SEARCH COLLECTION 1",SearchCollection1);

	vector<int>::const_iterator									Iterator1=find_end(Collection.cbegin(),Collection.cend(),SearchCollection1.cbegin(),SearchCollection1.cend());

	if (Iterator1!=Collection.cend())
	{
		wcout << L"POSITION [" << distance(Collection.cbegin(),Iterator1) << L"] !" << endl;
		wcout << L"SEARCH COLLECTION [";

		for(vector<int>::size_type Index=0;Index<SearchCollection1.size();Index++)
		{
			if (Index>0)
			{
				wcout << L" ";
			}

			wcout << *Iterator1++;
		}

		wcout << L"] !" << endl;
	}
	else
	{
		wcout << L"SEARCH COLLECTION NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	PrintCollection(L"COLLECTION",Collection);
	PrintCollection(L"SEARCH COLLECTION 2",SearchCollection2);

	vector<int>::const_iterator									Iterator2=find_end(Collection.cbegin(),Collection.cend(),SearchCollection2.cbegin(),SearchCollection2.cend(),[](int Item1, int Item2)->bool{return((Item1+Item2)>20);});

	if (Iterator2!=Collection.cend())
	{
		wcout << L"POSITION [" << distance(Collection.cbegin(),Iterator2) << L"] !" << endl;
		wcout << L"SEARCH COLLECTION [";

		for(vector<int>::size_type Index=0;Index<SearchCollection2.size();Index++)
		{
			if (Index>0)
			{
				wcout << L" ";
			}

			wcout << *Iterator2++;
		}

		wcout << L"] !" << endl;
	}
	else
	{
		wcout << L"SEARCH COLLECTION NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFindFirstOf(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,17,5,17,4,1,1,8,4,1,12,5,4,4,17,5,17,1,12,5,4,8});
	vector<int>													SearchCollection1({7,18,9,8});
	vector<int>													SearchCollection2({4,16,4});

	PrintCollection(L"COLLECTION",Collection);
	PrintCollection(L"SEARCH COLLECTION 1",SearchCollection1);

	vector<int>::const_iterator									Iterator1=find_first_of(Collection.cbegin(),Collection.cend(),SearchCollection1.cbegin(),SearchCollection1.cend());

	if (Iterator1!=Collection.cend())
	{
		wcout << L"POSITION [" << distance(Collection.cbegin(),Iterator1) << L"] !" << endl;
		wcout << L"ITEM [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	PrintCollection(L"COLLECTION",Collection);
	PrintCollection(L"SEARCH COLLECTION 2",SearchCollection2);

	vector<int>::const_iterator									Iterator2=find_first_of(Collection.cbegin(),Collection.cend(),SearchCollection2.cbegin(),SearchCollection2.cend(),[](int Item1, int Item2)->bool{return((Item1+Item2)>25);});

	if (Iterator2!=Collection.cend())
	{
		wcout << L"POSITION [" << distance(Collection.cbegin(),Iterator2) << L"] !" << endl;
		wcout << L"ITEM [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAdjacentFind(void)
{
	PrintLineSeparator();

	vector<int>													Collection({3,5,6,17,5,17,4,1,1,8,4,1,12,5,4,4,17,5,17,1,12,5,4,8});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=adjacent_find(Collection.cbegin(),Collection.cend());

	if (Iterator1!=Collection.cend())
	{
		wcout << L"POSITION [" << distance(Collection.cbegin(),Iterator1) << L"] !" << endl;
		wcout << L"ITEM [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator2=adjacent_find(Collection.cbegin(),Collection.cend(),[](int Item1, int Item2)->bool{return(Item1==(Item2/2));});

	if (Iterator2!=Collection.cend())
	{
		wcout << L"POSITION [" << distance(Collection.cbegin(),Iterator2) << L"] !" << endl;
		wcout << L"ITEM [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEqual(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,5,6,8,12});
	vector<int>													Collection2({4,5,6,8,12});
	vector<int>													Collection3({4,5,6,9,12});
	vector<int>													Collection4({4,5,6,9});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);
	PrintCollection(L"COLLECTION 4",Collection4);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 == COLLECTION 2 [" << equal(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin()) << L"] !" << endl;
	wcout << L"COLLECTION 1 == COLLECTION 3 [" << equal(Collection1.cbegin(),Collection1.cend(),Collection3.cbegin()) << L"] !" << endl;
	wcout << L"COLLECTION 1 == COLLECTION 4 [" << equal(Collection1.cbegin(),Collection1.cend(),Collection4.cbegin(),Collection4.cend()) << L"] !" << endl;

	PrintLineSeparator();

	// Porovnavaju sa iba PARNE CISLA.
	wcout << L"COLLECTION 1 == COLLECTION 2 [" << equal(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);}) << L"] !" << endl;
	// Porovnavaju sa iba PARNE CISLA.
	wcout << L"COLLECTION 1 == COLLECTION 3 [" << equal(Collection1.cbegin(),Collection1.cend(),Collection3.cbegin(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);}) << L"] !" << endl;
	// Porovnavaju sa iba PARNE CISLA.
	wcout << L"COLLECTION 1 == COLLECTION 4 [" << equal(Collection1.cbegin(),Collection1.cend(),Collection4.cbegin(),Collection4.cend(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIsPermutation(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,5,6,8,12});
	vector<int>													Collection2({6,4,5,12,8});
	vector<int>													Collection3({5,4,6,9,12});
	vector<int>													Collection4({4,5,6,9});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);
	PrintCollection(L"COLLECTION 4",Collection4);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 is PERMUTATION of COLLECTION 2 [" << is_permutation(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin()) << L"] !" << endl;
	wcout << L"COLLECTION 1 is PERMUTATION of COLLECTION 3 [" << is_permutation(Collection1.cbegin(),Collection1.cend(),Collection3.cbegin()) << L"] !" << endl;
	wcout << L"COLLECTION 1 is PERMUTATION of COLLECTION 4 [" << is_permutation(Collection1.cbegin(),Collection1.cend(),Collection4.cbegin(),Collection4.cend()) << L"] !" << endl;

	PrintLineSeparator();

	// Porovnavaju sa iba PARNE CISLA.
	wcout << L"COLLECTION 1 is PERMUTATION of COLLECTION 2 [" << is_permutation(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);}) << L"] !" << endl;
	// Porovnavaju sa iba PARNE CISLA.
	wcout << L"COLLECTION 1 is PERMUTATION of COLLECTION 3 [" << is_permutation(Collection1.cbegin(),Collection1.cend(),Collection3.cbegin(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);}) << L"] !" << endl;
	// Porovnavaju sa iba PARNE CISLA.
	wcout << L"COLLECTION 1 is PERMUTATION of COLLECTION 4 [" << is_permutation(Collection1.cbegin(),Collection1.cend(),Collection4.cbegin(),Collection4.cend(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMismatch(void)
{
	PrintLineSeparator();

	using														Pair=pair<vector<int>::const_iterator,vector<int>::const_iterator>;

	vector<int>													Collection1({4,5,6,8,12});
	vector<int>													Collection2({4,5,6,9,12});
	vector<int>													Collection3({4,5,6,8,12,25,41});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);

	PrintLineSeparator();

	Pair														Pair1=mismatch(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin());
	// Porovnavaju sa iba PARNE CISLA.
	Pair														Pair2=mismatch(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);});
	Pair														Pair3=mismatch(Collection1.cbegin(),Collection1.cend(),Collection3.cbegin(),Collection3.cend());
	// Porovnavaju sa iba PARNE CISLA.
	Pair														Pair4=mismatch(Collection1.cbegin(),Collection1.cend(),Collection3.cbegin(),Collection3.cend(),[](int Item1, int Item2)->bool{return((Item1%2 && Item2%2)==true ? (Item1==Item2) : true);});

	if (Pair1.first!=Collection1.cend())
	{
		wcout << L"COLLECTION 1 is NOT SUBSET of COLLECTION 2 - DIFFERENT ITEMS [" << *(Pair1.first) << L"," << *(Pair1.second) << L"] !" << endl;
	}
	else
	{
		if (Pair1.second!=Collection2.cend())
		{
			wcout << L"COLLECTION 1 is SUBSET of COLLECTION 2 - ITEM [" << *(Pair1.second) << L"] !" << endl;
		}
		else
		{
			wcout << L"COLLECTION 1 is EQUAL to COLLECTION 2 !" << endl;
		}
	}

	PrintLineSeparator();

	if (Pair2.first!=Collection1.cend())
	{
		wcout << L"COLLECTION 1 is NOT SUBSET of COLLECTION 2 - DIFFERENT ITEMS [" << *(Pair2.first) << L"," << *(Pair2.second) << L"] !" << endl;
	}
	else
	{
		if (Pair2.second!=Collection2.cend())
		{
			wcout << L"COLLECTION 1 is SUBSET of COLLECTION 2 - ITEM [" << *(Pair2.second) << L"] !" << endl;
		}
		else
		{
			wcout << L"COLLECTION 1 is EQUAL to COLLECTION 2 !" << endl;
		}
	}

	PrintLineSeparator();

	if (Pair3.first!=Collection1.cend())
	{
		wcout << L"COLLECTION 1 is NOT SUBSET of COLLECTION 3 - DIFFERENT ITEMS [" << *(Pair3.first) << L"," << *(Pair3.second) << L"] !" << endl;
	}
	else
	{
		if (Pair3.second!=Collection3.cend())
		{
			wcout << L"COLLECTION 1 is SUBSET of COLLECTION 3 - ITEM [" << *(Pair3.second) << L"] !" << endl;
		}
		else
		{
			wcout << L"COLLECTION 1 is EQUAL to COLLECTION 3 !" << endl;
		}
	}

	PrintLineSeparator();

	if (Pair4.first!=Collection1.cend())
	{
		wcout << L"COLLECTION 1 is NOT SUBSET of COLLECTION 3 - DIFFERENT ITEMS [" << *(Pair4.first) << L"," << *(Pair4.second) << L"] !" << endl;
	}
	else
	{
		if (Pair4.second!=Collection3.cend())
		{
			wcout << L"COLLECTION 1 is SUBSET of COLLECTION 3 - ITEM [" << *(Pair4.second) << L"] !" << endl;
		}
		else
		{
			wcout << L"COLLECTION 1 is EQUAL to COLLECTION 3 !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLexicographicalCompare(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,5,6,8,12});
	vector<int>													Collection2({4,5,6,9,12});
	vector<int>													Collection3({4,5,6,8,12,25,41});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 < COLLECTION 1 [" << lexicographical_compare(Collection1.cbegin(),Collection1.cend(),Collection1.cbegin(),Collection1.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 1 < COLLECTION 2 [" << lexicographical_compare(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin(),Collection2.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 1 < COLLECTION 3 [" << lexicographical_compare(Collection1.cbegin(),Collection1.cend(),Collection3.cbegin(),Collection3.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 3 < COLLECTION 1 [" << lexicographical_compare(Collection3.cbegin(),Collection3.cend(),Collection1.cbegin(),Collection1.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 3 < COLLECTION 1 [" << lexicographical_compare(Collection3.cbegin(),Collection3.cend(),Collection1.cbegin(),Collection1.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIsSorted(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,5,6,8,12,15});
	vector<int>													Collection2({4,5,6,8,12,7,15});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 - IS SORTED [" << is_sorted(Collection1.cbegin(),Collection1.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 2 - IS SORTED [" << is_sorted(Collection2.cbegin(),Collection2.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 2 - IS SORTED [" << is_sorted(Collection2.cbegin(),Collection2.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIsSortedUntil(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,5,6,8,12,15});
	vector<int>													Collection2({4,5,6,8,12,7,15});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=is_sorted_until(Collection1.cbegin(),Collection1.cend());
	vector<int>::const_iterator									Iterator2=is_sorted_until(Collection2.cbegin(),Collection2.cend());
	vector<int>::const_iterator									Iterator3=is_sorted_until(Collection2.cbegin(),Collection2.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	if (Iterator1!=Collection1.cend())
	{
		wcout << L"COLLECTION 1 - DIFFERENT ITEM [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 1 IS SORTED !" << endl;
	}

	PrintLineSeparator();

	if (Iterator2!=Collection2.cend())
	{
		wcout << L"COLLECTION 2 - DIFFERENT ITEM [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 2 IS SORTED !" << endl;
	}

	PrintLineSeparator();

	if (Iterator3!=Collection2.cend())
	{
		wcout << L"COLLECTION 2 - DIFFERENT ITEM [" << *Iterator3 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 2 IS SORTED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIsPartitioned(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,5,6,8,12,15});
	vector<int>													Collection2({4,5,6,8,12,4,15});
	vector<int>													Collection3({4,5,6,8});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 - IS PARTITIONED [" << is_partitioned(Collection1.cbegin(),Collection1.cend(),[](int Item)->bool{return(Item<=10);}) << L"] !" << endl;
	wcout << L"COLLECTION 2 - IS PARTITIONED [" << is_partitioned(Collection2.cbegin(),Collection2.cend(),[](int Item)->bool{return(Item<=10);}) << L"] !" << endl;
	wcout << L"COLLECTION 3 - IS PARTITIONED [" << is_partitioned(Collection3.cbegin(),Collection3.cend(),[](int Item)->bool{return(Item<=10);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPartitionPoint(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,5,6,8,12,15});
	vector<int>													Collection2({4,5,6,8,12,4,15});
	vector<int>													Collection3({4,5,6,8});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=partition_point(Collection1.cbegin(),Collection1.cend(),[](int Item)->bool{return(Item<=10);});
	// !!!!! CHYBNY CODE. COLLECTION 2 NIE JE PARTITIONED.
	vector<int>::const_iterator									Iterator2=partition_point(Collection2.cbegin(),Collection2.cend(),[](int Item)->bool{return(Item<=10);});
	vector<int>::const_iterator									Iterator3=partition_point(Collection3.cbegin(),Collection3.cend(),[](int Item)->bool{return(Item<=10);});

	if (Iterator1!=Collection1.cend())
	{
		wcout << L"COLLECTION 1 - PARTITION POINT [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 1 doesn't contain PARTITION POINT !" << endl;
	}

	if (Iterator2!=Collection2.cend())
	{
		// !!!!! CHYBNY VYSLEDOK. COLLECTION 2 NIE JE PARTITIONED.
		wcout << L"COLLECTION 2 - PARTITION POINT [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 2 doesn't contain PARTITION POINT !" << endl;
	}

	if (Iterator3!=Collection3.cend())
	{
		wcout << L"COLLECTION 3 - PARTITION POINT [" << *Iterator3 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 3 doesn't contain PARTITION POINT !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIsHeap(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({12,9,8,8,7,1,3});
	vector<int>													Collection2({12,9,8,8,7,1,3,4});
	// Uz NIE JE HEAP, pretoze VALUE '2' na POSITION 5 je > ako VALUE '1' na POSITION 11.
	vector<int>													Collection3({12,9,8,8,7,1,3,4,5,4,3,2,1});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 - IS HEAP [" << is_heap(Collection1.cbegin(),Collection1.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;
	wcout << L"COLLECTION 2 - IS HEAP [" << is_heap(Collection2.cbegin(),Collection2.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;
	wcout << L"COLLECTION 3 - IS HEAP [" << is_heap(Collection3.cbegin(),Collection3.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIsHeapUntil(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({12,9,8,8,7,1,3});
	vector<int>													Collection2({12,9,8,8,7,1,3,4});
	// Uz NIE JE HEAP, pretoze VALUE '2' na POSITION 5 je > ako VALUE '1' na POSITION 11.
	vector<int>													Collection3({12,9,8,8,7,1,3,4,5,4,3,2,1});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"COLLECTION 3",Collection3);

	PrintLineSeparator();

	vector<int>::const_iterator									Iterator1=is_heap_until(Collection1.cbegin(),Collection1.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);});
	vector<int>::const_iterator									Iterator2=is_heap_until(Collection2.cbegin(),Collection2.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);});
	vector<int>::const_iterator									Iterator3=is_heap_until(Collection3.cbegin(),Collection3.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	if (Iterator1!=Collection1.cend())
	{
		wcout << L"COLLECTION 1 - FIRST NON HEAP ITEM [" << *Iterator1 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 1 is HEAP !" << endl;
	}

	if (Iterator2!=Collection2.cend())
	{
		wcout << L"COLLECTION 2 - FIRST NON HEAP ITEM [" << *Iterator2 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 2 is HEAP !" << endl;
	}

	if (Iterator3!=Collection3.cend())
	{
		wcout << L"COLLECTION 3 - FIRST NON HEAP ITEM [" << *Iterator3 << L"] !" << endl;
	}
	else
	{
		wcout << L"COLLECTION 3 is HEAP !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAllOf(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({2,9,8,8,7,1,3});
	vector<int>													Collection2({2,9,8,8,7,11,3});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 - ALL OF < 10 [" << all_of(Collection1.cbegin(),Collection1.cend(),[](int Item)->bool{return(Item<10);}) << L"] !" << endl;
	wcout << L"COLLECTION 2 - ALL OF < 10 [" << all_of(Collection2.cbegin(),Collection2.cend(),[](int Item)->bool{return(Item<10);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAnyOf(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({2,9,8,8,7,1,3});
	vector<int>													Collection2({2,9,8,8,7,11,3});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 - ANY OF > 10 [" << any_of(Collection1.cbegin(),Collection1.cend(),[](int Item)->bool{return(Item>10);}) << L"] !" << endl;
	wcout << L"COLLECTION 2 - ANY OF > 10 [" << any_of(Collection2.cbegin(),Collection2.cend(),[](int Item)->bool{return(Item>10);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNoneOf(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({2,9,8,8,7,1,3});
	vector<int>													Collection2({2,9,8,8,7,11,3});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 - NONE OF > 10 [" << none_of(Collection1.cbegin(),Collection1.cend(),[](int Item)->bool{return(Item>10);}) << L"] !" << endl;
	wcout << L"COLLECTION 2 - NONE OF > 10 [" << none_of(Collection2.cbegin(),Collection2.cend(),[](int Item)->bool{return(Item>10);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopy(void)
{
	PrintLineSeparator();

	vector<CInt>												InputCollection({2,9,5,8,7,1,6,3});
	vector<CInt>												OutputCollection;

	OutputCollection.reserve(InputCollection.size());

	PrintLineSeparator();

	PrintCollection(L"INPUT COLLECTION",InputCollection);

	PrintLineSeparator();

	copy(InputCollection.cbegin(),InputCollection.cend(),back_inserter(OutputCollection));

	PrintLineSeparator();

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopyBackward(void)
{
	PrintLineSeparator();

	vector<CInt>												InputCollection({2,9,5,8,7,1,6,3});
	vector<CInt>												OutputCollection(InputCollection.size());

	OutputCollection.reserve(InputCollection.size());

	PrintLineSeparator();

	PrintCollection(L"INPUT COLLECTION",InputCollection);

	PrintLineSeparator();

	copy_backward(InputCollection.cbegin(),InputCollection.cend(),OutputCollection.end());

	PrintLineSeparator();

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopyN(void)
{
	PrintLineSeparator();

	vector<CInt>												InputCollection({2,9,5,8,7,1,6,3});
	vector<CInt>												OutputCollection;

	OutputCollection.reserve(InputCollection.size());

	PrintLineSeparator();

	PrintCollection(L"INPUT COLLECTION",InputCollection);

	PrintLineSeparator();

	copy_n(InputCollection.cbegin(),InputCollection.size(),back_inserter(OutputCollection));

	PrintLineSeparator();

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCopyIf(void)
{
	PrintLineSeparator();

	vector<CInt>												InputCollection({2,9,5,8,7,1,6,3});
	vector<CInt>												OutputCollection;

	OutputCollection.reserve(InputCollection.size());

	PrintLineSeparator();

	PrintCollection(L"INPUT COLLECTION",InputCollection);

	PrintLineSeparator();

	copy_if(InputCollection.cbegin(),InputCollection.cend(),back_inserter(OutputCollection),[](const CInt& Value)->bool{return((Value.GetValue()%2)==0);});

	PrintLineSeparator();

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMove(void)
{
	PrintLineSeparator();

	vector<CInt>												InputCollection({2,9,5,8,7,1,6,3});
	vector<CInt>												OutputCollection;

	OutputCollection.reserve(InputCollection.size());

	PrintLineSeparator();

	PrintCollection(L"INPUT COLLECTION",InputCollection);

	PrintLineSeparator();

	move(InputCollection.begin(),InputCollection.end(),back_inserter(OutputCollection));

	PrintLineSeparator();

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMoveBackward(void)
{
	PrintLineSeparator();

	vector<CInt>												InputCollection({2,9,5,8,7,1,6,3});
	vector<CInt>												OutputCollection(InputCollection.size());

	OutputCollection.reserve(InputCollection.size());

	PrintLineSeparator();

	PrintCollection(L"INPUT COLLECTION",InputCollection);

	PrintLineSeparator();

	move_backward(InputCollection.begin(),InputCollection.end(),OutputCollection.end());

	PrintLineSeparator();

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTransform(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({2,9,5,8,7,1,6,3});
	vector<int>													InputCollection2({11,12,13,18,19,20,14,15});
	vector<int>													OutputCollection1;
	vector<int>													OutputCollection2;

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);

	PrintLineSeparator();

	transform(InputCollection1.cbegin(),InputCollection1.cend(),back_inserter(OutputCollection1),[](int Item)->int{return(Item+10);});

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	PrintLineSeparator();

	transform(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),back_inserter(OutputCollection2),[](int Item1, int Item2)->int{return(Item1+Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSwapRanges(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({2,9,5,8,7,1,6,3});
	vector<int>													InputCollection2({11,12,13,18,19,20,14,15,33,44,55});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result=swap_ranges(InputCollection1.begin(),InputCollection1.end(),InputCollection2.begin());

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);

	if (Result!=InputCollection2.end())
	{
		wcout << "RESULT POINTS to VALUE [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << "RESULT POINTS to END of INPUT COLLECTION 2 !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFill(void)
{
	PrintLineSeparator();

	vector<int>													Collection({2,9,5,8,7,1,6,3});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	fill(Collection.begin(),Collection.end(),100);

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFillN(void)
{
	PrintLineSeparator();

	vector<int>													Collection({2,9,5,8,7,1,6,3});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Iterator=fill_n(Collection.begin(),4,100);

	PrintCollection(L"COLLECTION",Collection);

	if (Iterator!=Collection.end())
	{
		wcout << L"FIRST UNMODIFIED ITEM [" << *Iterator << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS were MODIFIED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGenerate(void)
{
	PrintLineSeparator();

	int															Key=100;
	vector<int>													Collection({2,9,5,8,7,1,6,3});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	generate(Collection.begin(),Collection.end(),[&Key](void)->int{return(Key++);});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGenerateN(void)
{
	PrintLineSeparator();

	int															Key=100;
	vector<int>													Collection({2,9,5,8,7,1,6,3});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Iterator=generate_n(Collection.begin(),4,[&Key](void)->int{return(Key++);});

	PrintCollection(L"COLLECTION",Collection);

	if (Iterator!=Collection.end())
	{
		wcout << L"FIRST UNMODIFIED ITEM [" << *Iterator << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS were MODIFIED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIota(void)
{
	PrintLineSeparator();

	vector<int>													Collection({2,9,5,8,7,1,6,3});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	iota(Collection.begin(),Collection.end(),100);

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReplace(void)
{
	PrintLineSeparator();

	vector<int>													Collection({2,9,9,5,8,9,7,1,6,3,9});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	replace(Collection.begin(),Collection.end(),9,555);

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReplaceIf(void)
{
	PrintLineSeparator();

	vector<int>													Collection({2,9,9,5,8,9,7,1,6,3,9});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	replace_if(Collection.begin(),Collection.end(),[](int Value)->bool{return(Value<5);},555);

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReplaceCopy(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({2,9,9,5,8,9,7,1,6,3,9});
	vector<int>													Collection2({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	// !!! INPUT COLLECTION sa NEMODIFIKUJE, preto je mozne pouzit CONST ITERATORS.
	vector<int>::iterator										Result=replace_copy(Collection1.cbegin(),Collection1.cend(),Collection2.begin(),9,555);

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	if (Result!=Collection2.end())
	{
		wcout << L"FIRST UNMODIFIED ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS were MODIFIED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReplaceCopyIf(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({2,9,9,5,8,9,7,1,6,3,9});
	vector<int>													Collection2({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	// !!! INPUT COLLECTION sa NEMODIFIKUJE, preto je mozne pouzit CONST ITERATORS.
	vector<int>::iterator										Result=replace_copy_if(Collection1.cbegin(),Collection1.cend(),Collection2.begin(),[](int Value)->bool{return(Value<5);},555);

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	if (Result!=Collection2.end())
	{
		wcout << L"FIRST UNMODIFIED ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS were MODIFIED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRemove(void)
{
	PrintLineSeparator();

	vector<int>													Collection({2,9,9,5,8,9,7,1,6,3,9});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Result=remove(Collection.begin(),Collection.end(),9);

	PrintCollection(L"COLLECTION",Collection);

	if (Result!=Collection.end())
	{
		wcout << L"FIRST REMOVED ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS were REMOVED !" << endl;
	}

	PrintLineSeparator();

	// !!! FYZICKY sa ODSTRANIA ITEMS z COLLECTION.
	Collection.erase(Result,Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRemoveIf(void)
{
	PrintLineSeparator();

	vector<int>													Collection({2,9,9,5,8,9,7,1,6,3,9});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Result=remove_if(Collection.begin(),Collection.end(),[](int Value)->bool{return(Value<5);});

	PrintCollection(L"COLLECTION",Collection);

	if (Result!=Collection.end())
	{
		wcout << L"FIRST REMOVED ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS were REMOVED !" << endl;
	}

	PrintLineSeparator();

	// !!! FYZICKY sa ODSTRANIA ITEMS z COLLECTION.
	Collection.erase(Result,Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRemoveCopy(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({2,9,9,5,8,9,7,1,6,3,9});
	vector<int>													Collection2({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	// !!! INPUT COLLECTION sa NEMODIFIKUJE, preto je mozne pouzit CONST ITERATORS.
	vector<int>::iterator										Result=remove_copy(Collection1.cbegin(),Collection1.cend(),Collection2.begin(),9);

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	wcout << L"NUMBER of COPIED ITEMS [" << distance(Collection2.begin(),Result) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRemoveCopyIf(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({2,9,9,5,8,9,7,1,6,3,9});
	vector<int>													Collection2({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	// !!! INPUT COLLECTION sa NEMODIFIKUJE, preto je mozne pouzit CONST ITERATORS.
	vector<int>::iterator										Result=remove_copy_if(Collection1.cbegin(),Collection1.cend(),Collection2.begin(),[](int Value)->bool{return(Value<5);});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	wcout << L"NUMBER of COPIED ITEMS [" << distance(Collection2.begin(),Result) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnique(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({3,4,4,2,6,1,2,2,3,1,6,6,6,5,7,5,4,4,4});

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	vector<int>::iterator										Result1=unique(Collection1.begin(),Collection1.end());

	PrintCollection(L"COLLECTION 1",Collection1);

	if (Result1!=Collection1.end())
	{
		wcout << L"FIRST REMOVED ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS were REMOVED !" << endl;
	}

	PrintLineSeparator();

	// !!! FYZICKY sa ODSTRANIA ITEMS z COLLECTION.
	Collection1.erase(Result1,Collection1.end());

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	vector<int>													Collection2({3,4,4,2,6,1,2,2,3,1,6,6,6,5,7,5,4,4,4});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	vector<int>::iterator										Result2=unique(Collection2.begin(),Collection2.end(),[](int Value1, int Value2)->bool{wcout << L"COMPARING (" << Value1 << L"," << Value2 << L") !" << endl;return(Value1>Value2);});

	PrintCollection(L"COLLECTION 2",Collection2);

	if (Result2!=Collection2.end())
	{
		wcout << L"FIRST REMOVED ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS were REMOVED !" << endl;
	}

	PrintLineSeparator();

	// !!! FYZICKY sa ODSTRANIA ITEMS z COLLECTION.
	Collection2.erase(Result2,Collection2.end());

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniqueCopy(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({3,4,4,2,6,1,2,2,3,1,6,6,6,5,7,5,4,4,4});
	vector<int>													OutputCollection1({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	PrintLineSeparator();

	vector<int>::iterator										Result1=unique_copy(InputCollection1.cbegin(),InputCollection1.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"FIRST REMOVED ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS were REMOVED !" << endl;
	}

	PrintLineSeparator();

	// !!! FYZICKY sa ODSTRANIA ITEMS z COLLECTION.
	OutputCollection1.erase(Result1,OutputCollection1.end());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	PrintLineSeparator();

	vector<int>													InputCollection2({3,4,4,2,6,1,2,2,3,1,6,6,6,5,7,5,4,4,4});
	vector<int>													OutputCollection2({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});

	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result2=unique_copy(InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Value1, int Value2)->bool{wcout << L"COMPARING (" << Value1 << L"," << Value2 << L") !" << endl;return(Value1>Value2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"FIRST REMOVED ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS were REMOVED !" << endl;
	}

	PrintLineSeparator();

	// !!! FYZICKY sa ODSTRANIA ITEMS z COLLECTION.
	OutputCollection2.erase(Result2,OutputCollection2.end());

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReverse(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	reverse(Collection.begin(),Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReverseCopy(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection({1,2,3,4,5,6,7,8,9,10});
	vector<int>													OutputCollection({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25});

	PrintCollection(L"INPUT COLLECTION",InputCollection);
	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();

	vector<int>::iterator										Result=reverse_copy(InputCollection.cbegin(),InputCollection.cend(),OutputCollection.begin());

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	if (Result!=OutputCollection.end())
	{
		wcout << L"FIRST NOT REPLACED ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS were REPLACED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRotate(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Result=rotate(Collection.begin(),Collection.begin()+3,Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	wcout << L"POSITION of ORIGINAL BEGIN ITERATOR [" << distance(Collection.begin(),Result) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRotateCopy(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection({1,2,3,4,5,6,7,8,9,10});
	vector<int>													OutputCollection({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});

	PrintCollection(L"INPUT COLLECTION",InputCollection);
	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();

	vector<int>::iterator										Result=rotate_copy(InputCollection.cbegin(),InputCollection.cbegin()+3,InputCollection.cend(),OutputCollection.begin());

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	if (Result!=OutputCollection.end())
	{
		wcout << L"FIRST NOT REPLACED ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS were REPLACED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNextPermutation(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({1,2,3,4});
	int															Index1=0;

	PrintCollection(L"COLLECTION 1",Collection1);

	while(next_permutation(Collection1.begin(),Collection1.end())==true)
	{
		wstringstream											Stream;

		Stream << L"COLLECTION 1 - ITERATION ";
		Stream << ++Index1;

		PrintCollection(Stream.str(),Collection1);
	}

	PrintLineSeparator();

	vector<int>													Collection2({1,2,3,4});
	int															Index2=0;

	PrintCollection(L"COLLECTION 2",Collection2);

	while(next_permutation(Collection2.begin(),Collection2.end(),[](int Item1, int Item2)->bool{return(Item1<Item2);})==true)
	{
		wstringstream											Stream;

		Stream << L"COLLECTION 2 - ITERATION ";
		Stream << ++Index2;

		PrintCollection(Stream.str(),Collection2);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPreviousPermutation(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({4,3,2,1});
	int															Index1=0;

	PrintCollection(L"COLLECTION 1",Collection1);

	while(prev_permutation(Collection1.begin(),Collection1.end())==true)
	{
		wstringstream											Stream;

		Stream << L"COLLECTION 1 - ITERATION ";
		Stream << ++Index1;

		PrintCollection(Stream.str(),Collection1);
	}

	PrintLineSeparator();

	vector<int>													Collection2({4,3,2,1});
	int															Index2=0;

	PrintCollection(L"COLLECTION 2",Collection2);

	while(prev_permutation(Collection2.begin(),Collection2.end(),[](int Item1, int Item2)->bool{return(Item1<Item2);})==true)
	{
		wstringstream											Stream;

		Stream << L"COLLECTION 2 - ITERATION ";
		Stream << ++Index2;

		PrintCollection(Stream.str(),Collection2);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestShuffle(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

    random_device												RandomDevice;
    mt19937														RandomGenerator(RandomDevice());

	shuffle(Collection.begin(),Collection.end(),RandomGenerator);

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPartition(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Result=partition(Collection.begin(),Collection.end(),[](int Value)->bool{return((Value % 2)==1);});

	PrintCollection(L"COLLECTION",Collection);

	if (Result!=Collection.end())
	{
		wcout << L"FIRST ITEM in SECOND GROUP [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS in SECOND GROUP !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStablePartition(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Result=stable_partition(Collection.begin(),Collection.end(),[](int Value)->bool{return((Value % 2)==1);});

	PrintCollection(L"COLLECTION",Collection);

	if (Result!=Collection.end())
	{
		wcout << L"FIRST ITEM in SECOND GROUP [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"NO ITEMS in SECOND GROUP !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPartitionCopy(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection({1,2,3,4,5,6,7,8,9,10});
	vector<int>													OutputCollection1({11,12,13,14,15,16,17,18,19,20,21,22,23,24,25});
	vector<int>													OutputCollection2({31,32,33,34,35,36,37,38,39,40,41,42,43,44,45});

	PrintCollection(L"INPUT COLLECTION",InputCollection);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	pair<vector<int>::iterator,vector<int>::iterator>			Result=partition_copy(InputCollection.cbegin(),InputCollection.cend(),OutputCollection1.begin(),OutputCollection2.begin(),[](int Value)->bool{return((Value % 2)==1);});

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result.first!=OutputCollection1.end())
	{
		wcout << L"FIRST ITEM after END ITERATOR of OUTPUT COLLECTION 1 [" << *(Result.first) << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS in OUTPUT COLLECTION 1 were FILLED !" << endl;
	}

	if (Result.second!=OutputCollection2.end())
	{
		wcout << L"FIRST ITEM after END ITERATOR of OUTPUT COLLECTION 2 [" << *(Result.second) << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS in OUTPUT COLLECTION 2 were FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSort(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({5,10,2,8,4,9,6,3,1,7});

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	sort(Collection1.begin(),Collection1.end());

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	vector<int>													Collection2({5,10,2,8,4,9,6,3,1,7});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	sort(Collection2.begin(),Collection2.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStableSort(void)
{
	PrintLineSeparator();

	vector<CKeyValue>											Collection1({CKeyValue(5,5),CKeyValue(7,77),CKeyValue(10,10),CKeyValue(2,2),CKeyValue(8,8),CKeyValue(2,22),CKeyValue(3,33),CKeyValue(4,4),CKeyValue(9,9),CKeyValue(6,6),CKeyValue(3,3),CKeyValue(1,1),CKeyValue(7,7),CKeyValue(2,222)});

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	stable_sort(Collection1.begin(),Collection1.end());

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	vector<CKeyValue>											Collection2({CKeyValue(5,5),CKeyValue(7,77),CKeyValue(10,10),CKeyValue(2,2),CKeyValue(8,8),CKeyValue(2,22),CKeyValue(3,33),CKeyValue(4,4),CKeyValue(9,9),CKeyValue(6,6),CKeyValue(3,3),CKeyValue(1,1),CKeyValue(7,7),CKeyValue(2,222)});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	stable_sort(Collection2.begin(),Collection2.end(),[](const CKeyValue& Item1, const CKeyValue& Item2)->bool{return(Item2.GetKey()<Item1.GetKey());});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPartialSort(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({5,10,2,8,4,9,6,3,1,7});

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	// Triedi sa prvych 6 ITEMS.
	partial_sort(Collection1.begin(),Collection1.begin()+6,Collection1.end());

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	vector<int>													Collection2({5,10,2,8,4,9,6,3,1,7});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	// Triedi sa prvych 6 ITEMS.
	partial_sort(Collection2.begin(),Collection2.begin()+6,Collection2.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPartialSortCopy(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({5,10,2,8,4,9,6,3,1,7});
	vector<int>													OutputCollection1({15,20,12,18,14,19,16,13,11,17,25,30,22});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	PrintLineSeparator();

	// Triedi sa prvych 6 ITEMS.
	vector<int>::iterator										Result1=partial_sort_copy(InputCollection1.begin(),InputCollection1.end(),OutputCollection1.begin(),OutputCollection1.begin()+6);

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"FIRST UNSORTED ITEM in COLLECTION 1 [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS in COLLECTION 1 are SORTED !" << endl;
	}

	PrintLineSeparator();

	vector<int>													InputCollection2({5,10,2,8,4,9,6,3,1,7});
	vector<int>													OutputCollection2({15,20,12,18,14,19,16,13,11,17,25,30,22});

	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	// Triedi sa prvych 6 ITEMS.
	vector<int>::iterator										Result2=partial_sort_copy(InputCollection2.begin(),InputCollection2.end(),OutputCollection2.begin(),OutputCollection2.begin()+6,[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"FIRST UNSORTED ITEM in COLLECTION 2 [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"ALL ITEMS in COLLECTION 2 are SORTED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestNthElement(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({5,10,2,8,4,9,6,3,1,7});

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	// Iba 6. ITEM je SORTED. To znaci, ze je umiestnany na tej pozicii, kde by sa nachadzal ak by cela COLLECTION bola SORTED.
	partial_sort(Collection1.begin(),Collection1.begin()+6,Collection1.end());

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	vector<int>													Collection2({5,10,2,8,4,9,6,3,1,7});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	// Iba 6. ITEM je SORTED. To znaci, ze je umiestnany na tej pozicii, kde by sa nachadzal ak by cela COLLECTION bola SORTED.
	partial_sort(Collection2.begin(),Collection2.begin()+6,Collection2.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHeap1(void)
{
	PrintLineSeparator();

	vector<int>													Collection({5,10,2,8,4,9,6,3});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	make_heap(Collection.begin(),Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	sort_heap(Collection.begin(),Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	make_heap(Collection.begin(),Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	// Prida sa ITEM na KONIEC COLLECTION. COLLECTION tym PRESTALA byt MAX HEAP.
	Collection.push_back(1);

	PrintCollection(L"COLLECTION",Collection);

	// FUNCTION push_heap() robi SORTING COLLECTION presunom POSLEDNEHO ITEM tak, aby COLLECTION bola ZNOVA HEAP COLLECTION.
	push_heap(Collection.begin(),Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	// Prida sa ITEM na KONIEC COLLECTION. COLLECTION tym PRESTALA byt MAX HEAP.
	Collection.push_back(7);

	PrintCollection(L"COLLECTION",Collection);

	// FUNCTION push_heap() robi SORTING COLLECTION presunom POSLEDNEHO ITEM tak, aby COLLECTION bola ZNOVA HEAP COLLECTION.
	push_heap(Collection.begin(),Collection.end());

	PrintCollection(L"COLLECTION",Collection);

	while(Collection.size()>0)
	{
		pop_heap(Collection.begin(),Collection.end());

		PrintLineSeparator();

		wcout << L"REMOVED ITEM [" << Collection.back() << L"] !" << endl;

		Collection.pop_back();

		PrintCollection(L"COLLECTION",Collection);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHeap2(void)
{
	PrintLineSeparator();

	vector<int>													Collection({5,10,2,8,4,9,6,3});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	make_heap(Collection.begin(),Collection.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION",Collection);

	sort_heap(Collection.begin(),Collection.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION",Collection);

	make_heap(Collection.begin(),Collection.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION",Collection);

	// Prida sa ITEM na KONIEC COLLECTION. COLLECTION tym PRESTALA byt MAX HEAP.
	Collection.push_back(1);

	PrintCollection(L"COLLECTION",Collection);

	// FUNCTION push_heap() robi SORTING COLLECTION presunom POSLEDNEHO ITEM tak, aby COLLECTION bola ZNOVA HEAP COLLECTION.
	push_heap(Collection.begin(),Collection.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION",Collection);

	// Prida sa ITEM na KONIEC COLLECTION. COLLECTION tym PRESTALA byt MAX HEAP.
	Collection.push_back(7);

	PrintCollection(L"COLLECTION",Collection);

	// FUNCTION push_heap() robi SORTING COLLECTION presunom POSLEDNEHO ITEM tak, aby COLLECTION bola ZNOVA HEAP COLLECTION.
	push_heap(Collection.begin(),Collection.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

	PrintCollection(L"COLLECTION",Collection);

	while(Collection.size()>0)
	{
		pop_heap(Collection.begin(),Collection.end(),[](int Item1, int Item2)->bool{return(Item2<Item1);});

		PrintLineSeparator();

		wcout << L"REMOVED ITEM [" << Collection.back() << L"] !" << endl;

		Collection.pop_back();

		PrintCollection(L"COLLECTION",Collection);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBinarySearch(void)
{
	PrintLineSeparator();

	vector<int>													Collection({5,10,2,8,4,9,6,3,1,7});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	if (binary_search(Collection.cbegin(),Collection.cend(),3)==true)
	{
		wcout << L"ITEM 3 FOUND !" << endl;
	}
	else
	{
		wcout << L"ITEM 3 FOUND !" << endl;
	}

	if (binary_search(Collection.cbegin(),Collection.cend(),13)==true)
	{
		wcout << L"ITEM 13 FOUND !" << endl;
	}
	else
	{
		wcout << L"ITEM 13 FOUND !" << endl;
	}

	PrintLineSeparator();

	if (binary_search(Collection.cbegin(),Collection.cend(),3,[](int Item1, int Item2)->bool{return(Item1<Item2);})==true)
	{
		wcout << L"ITEM 3 FOUND !" << endl;
	}
	else
	{
		wcout << L"ITEM 3 FOUND !" << endl;
	}

	if (binary_search(Collection.cbegin(),Collection.cend(),13,[](int Item1, int Item2)->bool{return(Item1<Item2);})==true)
	{
		wcout << L"ITEM 13 FOUND !" << endl;
	}
	else
	{
		wcout << L"ITEM 13 FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIncludes(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({1,2,3,4,5,6,7,8,9,10});
	vector<int>													Collection2({1,2,2,3,3,4});
	vector<int>													SearchCollection1({5,6,7});
	vector<int>													SearchCollection2({1,2,2});
	vector<int>													SearchCollection3({1,2,2,2});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);
	PrintCollection(L"SEARCH COLLECTION 1",SearchCollection1);
	PrintCollection(L"SEARCH COLLECTION 2",SearchCollection2);
	PrintCollection(L"SEARCH COLLECTION 3",SearchCollection3);

	PrintLineSeparator();

	wcout << L"COLLECTION 1 inlucdes SEARCH COLLECTION 1 [" << includes(Collection1.cbegin(),Collection1.cend(),SearchCollection1.cbegin(),SearchCollection1.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 2 inlucdes SEARCH COLLECTION 2 [" << includes(Collection2.cbegin(),Collection2.cend(),SearchCollection2.cbegin(),SearchCollection2.cend()) << L"] !" << endl;
	wcout << L"COLLECTION 2 inlucdes SEARCH COLLECTION 3 [" << includes(Collection2.cbegin(),Collection2.cend(),SearchCollection3.cbegin(),SearchCollection3.cend()) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"COLLECTION 1 inlucdes SEARCH COLLECTION 1 [" << includes(Collection1.cbegin(),Collection1.cend(),SearchCollection1.cbegin(),SearchCollection1.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;
	wcout << L"COLLECTION 2 inlucdes SEARCH COLLECTION 2 [" << includes(Collection2.cbegin(),Collection2.cend(),SearchCollection2.cbegin(),SearchCollection2.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;
	wcout << L"COLLECTION 2 inlucdes SEARCH COLLECTION 3 [" << includes(Collection2.cbegin(),Collection2.cend(),SearchCollection3.cbegin(),SearchCollection3.cend(),[](int Item1, int Item2)->bool{return(Item1<Item2);}) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLowerBound(void)
{
	PrintLineSeparator();

	vector<int>													Collection({11,22,33,44,44,44,55,66,77,88,99,111});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::const_iterator									Result1=lower_bound(Collection.cbegin(),Collection.cend(),44);

	if (Result1!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result1) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 44 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result2=lower_bound(Collection.cbegin(),Collection.cend(),44,[](int Item1, int Item2)->bool{return(Item1<Item2);});

	if (Result2!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result2) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 44 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result3=lower_bound(Collection.cbegin(),Collection.cend(),5);

	if (Result3!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 5 is at POSITION [" << distance(Collection.cbegin(),Result3) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 5 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result4=lower_bound(Collection.cbegin(),Collection.cend(),111);

	if (Result4!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 111 is at POSITION [" << distance(Collection.cbegin(),Result4) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 111 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result5=lower_bound(Collection.cbegin(),Collection.cend(),150);

	if (Result5!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 150 is at POSITION [" << distance(Collection.cbegin(),Result5) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 150 NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUpperBound(void)
{
	PrintLineSeparator();

	vector<int>													Collection({11,22,33,44,44,44,55,66,77,88,99,111});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::const_iterator									Result1=upper_bound(Collection.cbegin(),Collection.cend(),44);

	if (Result1!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result1) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 44 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result2=upper_bound(Collection.cbegin(),Collection.cend(),44,[](int Item1, int Item2)->bool{return(Item1<Item2);});

	if (Result2!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result2) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 44 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result3=upper_bound(Collection.cbegin(),Collection.cend(),5);

	if (Result3!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 5 is at POSITION [" << distance(Collection.cbegin(),Result3) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 5 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result4=upper_bound(Collection.cbegin(),Collection.cend(),111);

	if (Result4!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 111 is at POSITION [" << distance(Collection.cbegin(),Result4) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 111 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	vector<int>::const_iterator									Result5=upper_bound(Collection.cbegin(),Collection.cend(),150);

	if (Result5!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 150 is at POSITION [" << distance(Collection.cbegin(),Result5) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 150 NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEqualRange(void)
{
	PrintLineSeparator();

	using														Pair=pair<vector<int>::const_iterator,vector<int>::const_iterator>;

	vector<int>													Collection({11,22,33,44,44,44,55,66,77,88,99,111,111});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	Pair														Result1=equal_range(Collection.cbegin(),Collection.cend(),44);

	if (Result1.first!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result1.first) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 44 NOT FOUND !" << endl;
	}

	if (Result1.second!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result1.second) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 44 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	Pair														Result2=equal_range(Collection.cbegin(),Collection.cend(),44,[](int Item1, int Item2)->bool{return(Item1<Item2);});

	if (Result2.first!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result2.first) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 44 NOT FOUND !" << endl;
	}

	if (Result2.second!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 44 is at POSITION [" << distance(Collection.cbegin(),Result2.second) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 44 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	Pair														Result3=equal_range(Collection.cbegin(),Collection.cend(),5);

	if (Result3.first!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 5 is at POSITION [" << distance(Collection.cbegin(),Result3.first) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 5 NOT FOUND !" << endl;
	}

	if (Result3.second!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 5 is at POSITION [" << distance(Collection.cbegin(),Result3.second) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 5 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	Pair														Result4=equal_range(Collection.cbegin(),Collection.cend(),111);

	if (Result4.first!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 111 is at POSITION [" << distance(Collection.cbegin(),Result4.first) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 111 NOT FOUND !" << endl;
	}

	if (Result4.second!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 111 is at POSITION [" << distance(Collection.cbegin(),Result4.second) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 111 NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	Pair														Result5=equal_range(Collection.cbegin(),Collection.cend(),150);

	if (Result5.first!=Collection.cend())
	{
		wcout << L"LOWER BOUND of 150 is at POSITION [" << distance(Collection.cbegin(),Result5.first) << L"] !" << endl;
	}
	else
	{
		wcout << L"LOWER BOUND of 150 NOT FOUND !" << endl;
	}

	if (Result5.second!=Collection.cend())
	{
		wcout << L"UPPER BOUND of 150 is at POSITION [" << distance(Collection.cbegin(),Result5.second) << L"] !" << endl;
	}
	else
	{
		wcout << L"UPPER BOUND of 150 NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMerge(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({1,2,3,4,5,6,7,8,8,9,10});
	vector<int>													InputCollection2({1,3,3,5,7,8,8,8,11,14});
	vector<int>													OutputCollection1({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});
	vector<int>													OutputCollection2({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result1=merge(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 1 points at ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 1 was completely FILLED !" << endl;
	}

	PrintLineSeparator();

	vector<int>::iterator										Result2=merge(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 2 points at ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 2 was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetUnion(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({1,2,3,4,5,6,7,8,8,9,10});
	vector<int>													InputCollection2({1,3,3,5,7,8,8,8,11,14});
	vector<int>													OutputCollection1({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});
	vector<int>													OutputCollection2({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result1=set_union(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 1 points at ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 1 was completely FILLED !" << endl;
	}

	PrintLineSeparator();

	vector<int>::iterator										Result2=set_union(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 2 points at ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 2 was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetIntersection(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({1,2,3,4,5,6,7,8,8,9,10});
	vector<int>													InputCollection2({1,3,3,5,7,8,8,8,11,14});
	vector<int>													OutputCollection1({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});
	vector<int>													OutputCollection2({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result1=set_intersection(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 1 points at ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 1 was completely FILLED !" << endl;
	}

	PrintLineSeparator();

	vector<int>::iterator										Result2=set_intersection(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 2 points at ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 2 was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetDifference(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({1,2,3,4,5,6,7,8,8,9,9,9,10});
	vector<int>													InputCollection2({1,3,3,5,7,8,8,8,9,11,14});
	vector<int>													OutputCollection1({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});
	vector<int>													OutputCollection2({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result1=set_difference(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 1 points at ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 1 was completely FILLED !" << endl;
	}

	PrintLineSeparator();

	vector<int>::iterator										Result2=set_difference(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 2 points at ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 2 was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetSymmetricDifference(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({1,2,3,4,5,6,7,8,8,9,9,9,10});
	vector<int>													InputCollection2({1,3,3,5,7,8,8,8,9,11,14});
	vector<int>													OutputCollection1({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});
	vector<int>													OutputCollection2({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result1=set_symmetric_difference(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 1 points at ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 1 was completely FILLED !" << endl;
	}

	PrintLineSeparator();

	vector<int>::iterator										Result2=set_symmetric_difference(InputCollection1.cbegin(),InputCollection1.cend(),InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 2 points at ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 2 was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInplaceMerge(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({1,2,3,4,5,6,7,8,8,9,10,1,3,3,5,7,8,8,8,11,14});
	vector<int>													Collection2({1,2,3,4,5,6,7,8,8,9,10,1,3,3,5,7,8,8,8,11,14});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	inplace_merge(Collection1.begin(),Collection1.begin()+11,Collection1.end());

	PrintCollection(L"COLLECTION 1",Collection1);

	PrintLineSeparator();

	inplace_merge(Collection2.begin(),Collection2.begin()+11,Collection2.end(),[](int Item1, int Item2)->bool{return(Item1<Item2);});

	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAccumulate(void)
{
	PrintLineSeparator();

	vector<int>													Collection({5,15,30,22,88});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	int															Value1=accumulate(Collection.cbegin(),Collection.cend(),1000);

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;

	PrintLineSeparator();

	int															Value2=accumulate(Collection.cbegin(),Collection.cend(),2,[](int Item1, int Item2)->int{return(Item1*Item2);});

	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInnerProduct(void)
{
	PrintLineSeparator();

	vector<int>													Collection1({1,3,4,7,9});
	vector<int>													Collection2({0,2,4,6,8});

	PrintCollection(L"COLLECTION 1",Collection1);
	PrintCollection(L"COLLECTION 2",Collection2);

	PrintLineSeparator();

	int															Value1=inner_product(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin(),10);

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;

	PrintLineSeparator();

	int															Value2=inner_product(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin(),10,[](int Item1, int Item2)->int{return(Item1+Item2);},[](int Item1, int Item2)->int{return(Item1*Item2);});

	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPartialSum(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({1,2,3,4,5,6,7,8,9,10});
	vector<int>													InputCollection2({1,2,3,4,5,6,7,8,9,10});
	vector<int>													OutputCollection1({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115});
	vector<int>													OutputCollection2({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result1=partial_sum(InputCollection1.cbegin(),InputCollection1.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 1 points at ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 1 was completely FILLED !" << endl;
	}

	PrintLineSeparator();

	vector<int>::iterator										Result2=partial_sum(InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Item1, int Item2)->int{return(Item1*Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 2 points at ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 2 was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAdjacentDifference(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection1({1,2,3,7,11,13,17,19,23,29});
	vector<int>													InputCollection2({1,2,3,7,11,13,17,19,23,29});
	vector<int>													OutputCollection1({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115});
	vector<int>													OutputCollection2({101,102,103,104,105,106,107,108,109,110,111,112,113,114,115});

	PrintCollection(L"INPUT COLLECTION 1",InputCollection1);
	PrintCollection(L"INPUT COLLECTION 2",InputCollection2);
	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);
	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	PrintLineSeparator();

	vector<int>::iterator										Result1=adjacent_difference(InputCollection1.cbegin(),InputCollection1.cend(),OutputCollection1.begin());

	PrintCollection(L"OUTPUT COLLECTION 1",OutputCollection1);

	if (Result1!=OutputCollection1.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 1 points at ITEM [" << *Result1 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 1 was completely FILLED !" << endl;
	}

	PrintLineSeparator();

	vector<int>::iterator										Result2=adjacent_difference(InputCollection2.cbegin(),InputCollection2.cend(),OutputCollection2.begin(),[](int Item1, int Item2)->int{return(Item1-Item2);});

	PrintCollection(L"OUTPUT COLLECTION 2",OutputCollection2);

	if (Result2!=OutputCollection2.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION 2 points at ITEM [" << *Result2 << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION 2 was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedCopy(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection({2,22,222});
	vector<int>													OutputCollection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"INPUT COLLECTION",InputCollection);
	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();

	vector<int>::iterator										Result=uninitialized_copy(InputCollection.cbegin(),InputCollection.cend(),OutputCollection.begin());

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	if (Result!=OutputCollection.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION points at ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedCopyN(void)
{
	PrintLineSeparator();

	vector<int>													InputCollection({2,22,222});
	vector<int>													OutputCollection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"INPUT COLLECTION",InputCollection);
	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	PrintLineSeparator();

	vector<int>::iterator										Result=uninitialized_copy_n(InputCollection.cbegin(),InputCollection.size(),OutputCollection.begin());

	PrintCollection(L"OUTPUT COLLECTION",OutputCollection);

	if (Result!=OutputCollection.end())
	{
		wcout << L"END ITERATOR of LOGICAL OUTPUT COLLECTION points at ITEM [" << *Result << L"] !" << endl;
	}
	else
	{
		wcout << L"OUTPUT COLLECTION was completely FILLED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedFill(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	uninitialized_fill(Collection.begin(),Collection.end(),333);

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUninitializedFillN(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	uninitialized_fill_n(Collection.begin(),Collection.size(),333);

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSwap(void)
{
	PrintLineSeparator();

	int															Value1=10;
	int															Value2=20;

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	// Vymiena sa obsah 2 VALUES.
	swap(Value1,Value2);

	PrintLineSeparator();

	wcout << L"VALUE 1 [" << Value1 << L"] !" << endl;
	wcout << L"VALUE 2 [" << Value2 << L"] !" << endl;

	PrintLineSeparator();

	const size_t												SIZE=10;

	int															Array1[SIZE]{1,2,3,4,5,6,7,8,9,10};
	int															Array2[SIZE]{11,12,13,14,15,16,17,18,19,20};

	wcout << L"ARRAY 1 [";

	for(size_t Index=0;Index<SIZE;Index++)
	{
		if (Index>0)
		{
			wcout << ",";
		}

		wcout << Array1[Index];
	}

	wcout << L"] !" << endl;

	wcout << L"ARRAY 2 [";

	for(size_t Index=0;Index<SIZE;Index++)
	{
		if (Index>0)
		{
			wcout << ",";
		}

		wcout << Array2[Index];
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vymiena sa obsah 2 ARRAYS.
	swap(Array1,Array2);

	wcout << L"ARRAY 1 [";

	for(size_t Index=0;Index<SIZE;Index++)
	{
		if (Index>0)
		{
			wcout << ",";
		}

		wcout << Array1[Index];
	}

	wcout << L"] !" << endl;

	wcout << L"ARRAY 2 [";

	for(size_t Index=0;Index<SIZE;Index++)
	{
		if (Index>0)
		{
			wcout << ",";
		}

		wcout << Array2[Index];
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSwapIter(void)
{
	PrintLineSeparator();

	vector<int>													Collection({1,2,3,4,5,6,7,8,9,10});

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();

	vector<int>::iterator										Iterator1=Collection.begin()+2;
	vector<int>::iterator										Iterator2=Collection.begin()+4;

	wcout << L"ITERATOR 1 [" << *Iterator1 << L"] !" << endl;
	wcout << L"ITERATOR 2 [" << *Iterator2 << L"] !" << endl;

	// !!! Vymiena sa obsah 2 VALUES na ktore odkazuju ITERATORS.
	iter_swap(Iterator1,Iterator2);

	PrintLineSeparator();

	wcout << L"ITERATOR 1 [" << *Iterator1 << L"] !" << endl;
	wcout << L"ITERATOR 2 [" << *Iterator2 << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"COLLECTION",Collection);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMin(void)
{
	PrintLineSeparator();

	wcout << L"MIN(" << min(20,10) << L") !" << endl;
	wcout << L"MIN(" << min(20,10,[](int Value1, int Value2)->bool{return(Value1<Value2);}) << L") !" << endl;
	wcout << L"MIN(" << min({30,20,70,50,100,40,10,80}) << L") !" << endl;
	wcout << L"MIN(" << min({30,20,70,50,100,40,10,80},[](int Value1, int Value2)->bool{return(Value1<Value2);}) << L") !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMax(void)
{
	PrintLineSeparator();

	wcout << L"MAX(" << max(20,10) << L") !" << endl;
	wcout << L"MAX(" << max(20,10,[](int Value1, int Value2)->bool{return(Value1<Value2);}) << L") !" << endl;
	wcout << L"MAX(" << max({30,20,70,50,100,40,10,80}) << L") !" << endl;
	wcout << L"MAX(" << max({30,20,70,50,100,40,10,80},[](int Value1, int Value2)->bool{return(Value1<Value2);}) << L") !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMinMax(void)
{
	PrintLineSeparator();

	pair<int,int>												Result1=minmax(20,10);

	wcout << L"MINMAX(" << Result1.first << L"," << Result1.second << L") !" << endl;

	pair<int,int>												Result2=minmax(20,10,[](int Value1, int Value2)->bool{return(Value1<Value2);});

	wcout << L"MINMAX(" << Result2.first << L"," << Result2.second << L") !" << endl;

	pair<int,int>												Result3=minmax({30,20,70,50,100,40,10,80});

	wcout << L"MINMAX(" << Result3.first << L"," << Result3.second << L") !" << endl;

	pair<int,int>												Result4=minmax({30,20,70,50,100,40,10,80},[](int Value1, int Value2)->bool{return(Value1<Value2);});

	wcout << L"MINMAX(" << Result4.first << L"," << Result4.second << L") !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestForEach1();
	//TestForEach2();
	//TestForEach3();
	//TestCount();
	//TestCountIf();
	//TestMinElement();
	//TestMaxElement();
	//TestMinMaxElement();
	//TestFind();
	//TestFindIf();
	//TestFindIfNot();
	//TestSearchN();
	//TestSearch();
	//TestFindEnd();
	//TestFindFirstOf();
	//TestAdjacentFind();
	//TestEqual();
	//TestIsPermutation();
	//TestMismatch();
	//TestLexicographicalCompare();
	//TestIsSorted();
	//TestIsSortedUntil();
	//TestIsPartitioned();
	//TestPartitionPoint();
	//TestIsHeap();
	//TestIsHeapUntil();
	//TestAllOf();
	//TestAnyOf();
	//TestNoneOf();
	//TestCopy();
	//TestCopyBackward();
	//TestCopyN();
	//TestCopyIf();
	//TestMove();
	//TestMoveBackward();
	//TestTransform();
	//TestSwapRanges();
	//TestFill();
	//TestFillN();
	//TestGenerate();
	//TestGenerateN();
	//TestIota();
	//TestReplace();
	//TestReplaceIf();
	//TestReplaceCopy();
	//TestReplaceCopyIf();
	//TestRemove();
	//TestRemoveIf();
	//TestRemoveCopy();
	//TestRemoveCopyIf();
	//TestUnique();
	//TestUniqueCopy();
	//TestReverse();
	//TestReverseCopy();
	//TestRotate();
	//TestRotateCopy();
	//TestNextPermutation();
	//TestPreviousPermutation();
	//TestShuffle();
	//TestPartition();
	//TestStablePartition();
	//TestPartitionCopy();
	//TestSort();
	//TestStableSort();
	//TestPartialSort();
	//TestPartialSortCopy();
	//TestNthElement();
	//TestHeap1();
	//TestHeap2();
	//TestBinarySearch();
	//TestIncludes();
	//TestLowerBound();
	//TestUpperBound();
	//TestEqualRange();
	//TestMerge();
	//TestSetUnion();
	//TestSetIntersection();
	//TestSetDifference();
	//TestSetSymmetricDifference();
	//TestInplaceMerge();
	//TestAccumulate();
	//TestInnerProduct();
	//TestPartialSum();
	//TestAdjacentDifference();
	//TestUninitializedCopy();
	//TestUninitializedCopyN();
	//TestUninitializedFill();
	//TestUninitializedFillN();
	//TestSwap();
	//TestSwapIter();
	//TestMin();
	//TestMax();
	TestMinMax();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------