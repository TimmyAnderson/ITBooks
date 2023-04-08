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
#include <tuple>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include "MyDebug.h"
#include "CCustomComparer.h"
#include "CInt.h"
#include "CCustomEqual.h"
#include "COddEvenHash.h"
#include "CUnorderedInt.h"
#include "CCustomHashFunction.h"
#include "CCustomEqualFunction.h"
#include "CUnorderedInt.h"
#include "CUnorderedIntEqualFunction.h"
#include "CUnorderedIntHashFunction.h"
#include "CCustomHashInStdNamespace.h"
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
template<typename TType, typename TCompare>
void PrintSetIterator(const wstring& Prefix, const set<TType,TCompare>& Collection, const typename set<TType,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << *Iterator;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType, typename TCompare>
void PrintMultiSetIterator(const wstring& Prefix, const multiset<TType,TCompare>& Collection, const typename multiset<TType,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << *Iterator;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename TCompare>
void PrintMapIterator(const wstring& Prefix, const map<TKey,TValue,TCompare>& Collection, const typename map<TKey,TValue,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << Iterator->first << L"," << Iterator->second;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename TCompare>
void PrintMultiMapIterator(const wstring& Prefix, const multimap<TKey,TValue,TCompare>& Collection, const typename multimap<TKey,TValue,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << Iterator->first << L"," << Iterator->second;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename THash, typename TCompare>
void PrintUnorderedSetIterator(const wstring& Prefix, const unordered_set<TKey,THash,TCompare>& Collection, const typename unordered_set<TKey,THash,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << *Iterator;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename THash, typename TCompare>
void PrintUnorderedMultiSetIterator(const wstring& Prefix, const unordered_multiset<TKey,THash,TCompare>& Collection, const typename unordered_multiset<TKey,THash,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << *Iterator;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename THash, typename TCompare>
void PrintUnorderedMapIterator(const wstring& Prefix, const unordered_map<TKey,TValue,THash,TCompare>& Collection, const typename unordered_map<TKey,TValue,THash,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << Iterator->first << L"," << Iterator->second;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TKey, typename TValue, typename THash, typename TCompare>
void PrintUnorderedMultiMapIterator(const wstring& Prefix, const unordered_multimap<TKey,TValue,THash,TCompare>& Collection, const typename unordered_multimap<TKey,TValue,THash,TCompare>::const_iterator& Iterator)
{
	wcout << Prefix;
	wcout << L" [";

	if (Iterator!=Collection.cend())
	{
		wcout << Iterator->first << L"," << Iterator->second;
	}
	else
	{
		wcout << L"END";
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
size_t OddEvenHash(int Value)
{
	size_t														Hash=(Value % 2);
	
	return(Hash);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomCompared(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);

	PrintCollection(L"SET 1",Set1);

	PrintLineSeparator();

	// !!! COMPARER sa vytvara zavolanim DEFAULT CONSTRUCTOR daneho COMPARER.
	set<int,greater<int>>										Set2;

	Set2.insert(1);
	Set2.insert(2);
	Set2.insert(3);

	PrintCollection(L"SET 2",Set2);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(true);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	set<int,CCustomComparer>									Set3(CustomComparer1);

	Set3.insert(1);
	Set3.insert(2);
	Set3.insert(3);

	PrintCollection(L"SET 3",Set3);

	CCustomComparer												CustomComparer2(false);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	set<int,CCustomComparer>									Set4(CustomComparer2);

	Set4.insert(1);
	Set4.insert(2);
	Set4.insert(3);

	PrintCollection(L"SET 4",Set4);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionTypes1(void)
{
	PrintLineSeparator();
	
	vector<int>													Vector({1,2,3,4,5});

	wcout << L"VALUE TYPE SIZE [" << sizeof(vector<int>::value_type) << L"] !" << endl;

	vector<int>::reference										Item1=Vector[0];

	Item1+=10;

	wcout << L"REFERENCE[0] [" << Item1 << L"] !" << endl;

	vector<int>::const_reference								Item2=Vector[0];

	wcout << L"CONST REFERENCE[0] [" << Item1 << L"] !" << endl;

	vector<int>::pointer										Item3=&Vector[1];

	*Item3+=20;

	wcout << L"POINTER[1] [" << *Item3 << L"] !" << endl;

	vector<int>::const_pointer									Item4=&Vector[1];

	wcout << L"CONST POINTER[1] [" << *Item4 << L"] !" << endl;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	wcout << L"ITERATOR [";

	for(vector<int>::iterator Iterator=Vector.begin();Iterator!=Vector.end();Iterator++)
	{
		if (Iterator!=Vector.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"CONST ITERATOR [";

	for(vector<int>::const_iterator Iterator=Vector.begin();Iterator!=Vector.end();Iterator++)
	{
		if (Iterator!=Vector.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"REVERSE ITERATOR [";

	for(vector<int>::reverse_iterator Iterator=Vector.rbegin();Iterator!=Vector.rend();Iterator++)
	{
		if (Iterator!=Vector.rbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"CONST REVERSE ITERATOR [";

	for(vector<int>::const_reverse_iterator Iterator=Vector.crbegin();Iterator!=Vector.crend();Iterator++)
	{
		if (Iterator!=Vector.crbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"VECTOR",Vector);

	vector<int>::size_type										Size=Vector.size();

	wcout << L"SIZE [" << Size << L"] !" << endl;

	vector<int>::const_iterator									Iterator=Vector.cbegin();
	vector<int>::difference_type								Difference=3;

	wcout << L"ITERATOR+DIFFERENCE(3) [" << *(Iterator+Difference) << L"] !" << endl;
	
	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionTypes2(void)
{
	PrintLineSeparator();

	wcout << "VALUE TYPE [" << ConvertStringToWideString(typeid(vector<int>::value_type).name()) << L"] !" << endl;
	wcout << "SIZE TYPE [" << ConvertStringToWideString(typeid(vector<int>::size_type).name()) << L"] !" << endl;
	wcout << "DIFFERENCE TYPE [" << ConvertStringToWideString(typeid(vector<int>::difference_type).name()) << L"] !" << endl;
	wcout << "ITERATOR TYPE [" << ConvertStringToWideString(typeid(vector<int>::iterator).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionTypes3(void)
{
	PrintLineSeparator();

	map<int,wstring>											Map;

	Map.insert(map<int,wstring>::value_type(1,L"10"));
	Map.insert(map<int,wstring>::value_type(2,L"20"));
	Map.insert(map<int,wstring>::value_type(3,L"30"));

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	map<int,wstring>::key_type									Key=2;
	// Je to VALUE TYPE, teda [wstring].
	map<int,wstring>::mapped_type								Value=Map[Key];

	wcout << L"KEY [" << Key << L"] VALUE [" << Value << L"] !" << endl;

	PrintLineSeparator();

	// Je to TYPE [less<TType>].
	map<int,wstring>::key_compare								KeyCompare=Map.key_comp();

	// !!! Porovnava VALUES, teda PAIRS a nie STRINGS.
	// !!!!! V skutocnosti porovnava IBA KEYS. VALUES IGNORUJE.
	map<int,wstring>::value_compare								ValueCompare=Map.value_comp();

	wcout << "KEY COMPARE [" << ConvertStringToWideString(typeid(KeyCompare).name()) << L"] !" << endl;
	wcout << "VALUE COMPARE [" << ConvertStringToWideString(typeid(ValueCompare).name()) << L"] !" << endl;

	wcout << L"KEY COMPARE(10,10) [" << KeyCompare(10,10) << L"] !" << endl;
	wcout << L"KEY COMPARE(10,20) [" << KeyCompare(10,20) << L"] !" << endl;
	wcout << L"KEY COMPARE(20,10) [" << KeyCompare(20,10) << L"] !" << endl;

	// !!!!! Vracia IDENTICKE hodnoty ako KEY COMPARER, pretoze VALUE COMPARER porovnava IBA hodnoty KEY a hodnoty VALUES ignoruje.
	wcout << L"VALUE COMPARE(Map[BEGIN],Map[BEGIN]) [" << ValueCompare(*Map.cbegin(),*Map.cbegin()) << L"] !" << endl;
	wcout << L"VALUE COMPARE(Map[BEGIN],Map[BEGIN+1]) [" << ValueCompare(*Map.cbegin(),*(++Map.cbegin())) << L"] !" << endl;
	wcout << L"VALUE COMPARE(Map[BEGIN+1],Map[BEGIN]) [" << ValueCompare(*(++Map.cbegin()),*Map.cbegin()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionTypes4(void)
{
	PrintLineSeparator();

	unordered_map<int,wstring>									UnorderedMap;

	UnorderedMap.insert(unordered_map<int,wstring>::value_type(1,L"10"));
	UnorderedMap.insert(unordered_map<int,wstring>::value_type(2,L"20"));
	UnorderedMap.insert(unordered_map<int,wstring>::value_type(3,L"30"));

	PrintUnorderedMap(L"MAP",UnorderedMap);

	PrintLineSeparator();

	unordered_map<int,wstring>::key_type						Key=2;
	// Je to VALUE TYPE, teda [wstring].
	unordered_map<int,wstring>::mapped_type						Value=UnorderedMap[Key];

	wcout << L"KEY [" << Key << L"] VALUE [" << Value << L"] !" << endl;

	PrintLineSeparator();

	unordered_map<int,wstring>::hasher							Hasher=UnorderedMap.hash_function();
	unordered_map<int,wstring>::key_equal						KeyEqual=UnorderedMap.key_eq();

	wcout << "HASHER [" << ConvertStringToWideString(typeid(Hasher).name()) << L"] !" << endl;
	wcout << "KEY EQUAL [" << ConvertStringToWideString(typeid(KeyEqual).name()) << L"] !" << endl;

	wcout << L"HASHER(10) [" << Hasher(10) << L"] !" << endl;
	wcout << L"HASHER(20) [" << Hasher(20) << L"] !" << endl;
	wcout << L"HASHER(999) [" << Hasher(999) << L"] !" << endl;

	// Porovnava hodnoty KEYS.
	wcout << L"KEY EQUAL(10,10) [" << KeyEqual(10,10) << L"] !" << endl;
	wcout << L"KEY EQUAL(10,20) [" << KeyEqual(10,20) << L"] !" << endl;
	wcout << L"KEY EQUAL(20,10) [" << KeyEqual(20,10) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionTypes5(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map;

	Map.max_load_factor(3);

	Map.insert(pair<int,int>(1,11));
	Map.insert(pair<int,int>(2,12));
	Map.insert(pair<int,int>(3,13));
	Map.insert(pair<int,int>(4,14));
	Map.insert(pair<int,int>(5,15));

	PrintUnorderedMap(L"MAP",Map);

	PrintLineSeparator();

	wcout << L"BUCKET COUNT [" << Map.bucket_count() << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map.bucket_count();Bucket++)
	{
		wcout << L"BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_map<int,int>::local_iterator Iterator=Map.begin(Bucket);Iterator!=Map.end(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";

			// !!! Zmeni hodnotu VALUE.
			Iterator->second*=2;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map.bucket_count();Bucket++)
	{
		wcout << L"BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_map<int,int>::const_local_iterator Iterator=Map.cbegin(Bucket);Iterator!=Map.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionTypes6(void)
{
	PrintLineSeparator();

	vector<int>													Vector;
	vector<int>::allocator_type									Allocator=Vector.get_allocator();

	wcout << "ALLOCATOR TYPE [" << ConvertStringToWideString(typeid(Allocator).name()) << L"] !" << endl;
	wcout << "MAX SIZE [" << Allocator.max_size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructorDestructor(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector1;

		Vector1.reserve(10);

		Vector1.push_back(CInt(10));
		
		PrintLineSeparator();

		Vector1.push_back(CInt(20));

		PrintLineSeparator();

		Vector1.push_back(CInt(30));

		PrintLineSeparator();

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// Vola sa COPY CONSTRUCTOR.
		vector<CInt>											Vector2(Vector1);

		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// Vola sa MOVE CONSTRUCTOR.
		vector<CInt>											Vector3(std::move(Vector2));

		PrintCollection(L"VECTOR 2",Vector2);
		PrintCollection(L"VECTOR 3",Vector3);

		PrintLineSeparator();

		// !!! DESTRUCTOR kazdeho VECTOR zavola DESTRUCTORS pre vsetky instancie CLASS 'CInt', ktore su vo VECTOR ulozene.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructor1(void)
{
	PrintLineSeparator();

	COddEvenHash												HashFunction;
	CCustomEqual<int>											KeyEqualFunction;

	// 1. PARAMETER definuje pocet BUCKETS.
	// 2. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
	// 3. PARAMETER definuje pocet CUSTOM KEY EQUAL FUNCTION.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet1(2,HashFunction,KeyEqualFunction);

	UnorderedSet1.insert(10);
	UnorderedSet1.insert(20);
	UnorderedSet1.insert(30);
	UnorderedSet1.insert(40);

	PrintCollection(L"UNORDERED SET 1",UnorderedSet1);

	// 1. PARAMETER definuje pocet BUCKETS.
	// 2. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet2(2,HashFunction);

	UnorderedSet2.insert(10);
	UnorderedSet2.insert(20);
	UnorderedSet2.insert(30);
	UnorderedSet2.insert(40);

	PrintCollection(L"UNORDERED SET 2",UnorderedSet2);

	// PARAMETER definuje pocet BUCKETS.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet3(2);

	UnorderedSet3.insert(10);
	UnorderedSet3.insert(20);
	UnorderedSet3.insert(30);
	UnorderedSet3.insert(40);

	PrintCollection(L"UNORDERED SET 3",UnorderedSet3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructor2(void)
{
	PrintLineSeparator();

	vector<int>													Vector;

	Vector.push_back(10);
	Vector.push_back(20);
	Vector.push_back(30);
	Vector.push_back(40);

	COddEvenHash												HashFunction;
	CCustomEqual<int>											KeyEqualFunction;

	// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 3. PARAMETER definuje pocet BUCKETS.
	// 4. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
	// 5. PARAMETER definuje pocet CUSTOM KEY EQUAL FUNCTION.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet1(Vector.cbegin(),Vector.cend(),2,HashFunction,KeyEqualFunction);

	PrintCollection(L"UNORDERED SET 1",UnorderedSet1);

	// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 3. PARAMETER definuje pocet BUCKETS.
	// 4. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet2(Vector.cbegin(),Vector.cend(),2,HashFunction);

	PrintCollection(L"UNORDERED SET 2",UnorderedSet2);

	// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 3. PARAMETER definuje pocet BUCKETS.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet3(Vector.cbegin(),Vector.cend(),2);

	PrintCollection(L"UNORDERED SET 3",UnorderedSet3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructor3(void)
{
	PrintLineSeparator();

	COddEvenHash												HashFunction;
	CCustomEqual<int>											KeyEqualFunction;

	// 1. PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje pocet BUCKETS.
	// 3. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
	// 4. PARAMETER definuje pocet CUSTOM KEY EQUAL FUNCTION.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet1({10,20,30,40},2,HashFunction,KeyEqualFunction);

	PrintCollection(L"UNORDERED SET 1",UnorderedSet1);

	// 1. PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje pocet BUCKETS.
	// 3. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet2({10,20,30,40},2,HashFunction);

	PrintCollection(L"UNORDERED SET 2",UnorderedSet2);

	// 1. PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje pocet BUCKETS.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			UnorderedSet3({10,20,30,40},2);

	PrintCollection(L"UNORDERED SET 3",UnorderedSet3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructor4(void)
{
	PrintLineSeparator();

	CCustomComparer												CompareFunction(false);
	vector<int>													Vector;

	Vector.push_back(10);
	Vector.push_back(20);
	Vector.push_back(30);
	Vector.push_back(40);

	// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 3. PARAMETER definuje pocet CUSTOM COMPARE FUNCTION.
	set<int,CCustomComparer>									Set1(Vector.cbegin(),Vector.cend(),CompareFunction);

	PrintCollection(L"SET 1",Set1);

	// 1. PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje pocet CUSTOM COMPARE FUNCTION.
	set<int,CCustomComparer>									Set2({10,20,30,40},CompareFunction);

	PrintCollection(L"SET 2",Set2);

	// PARAMETER definuje pocet CUSTOM COMPARE FUNCTION.
	set<int,CCustomComparer>									Set3(CompareFunction);

	Set3.insert(10);
	Set3.insert(20);
	Set3.insert(30);
	Set3.insert(40);

	PrintCollection(L"SET 3",Set3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructor5(void)
{
	PrintLineSeparator();

	vector<int>													Vector1({10,20,30,40});

	// PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initiacizovat.
	PrintCollection(L"VECTOR 1",Vector1);

	// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initiacizovat.
	// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initiacizovat.
	vector<int>													Vector2(Vector1.cbegin(),Vector1.cend());

	PrintCollection(L"VECTOR 2",Vector2);

	// Vytvori COLLECTION s 3 ITEMS pre ktore je volany DEFAULT CONSTRUCTOR.
	vector<int>													Vector3(3);

	PrintCollection(L"VECTOR 3",Vector3);

	// Vytvori COLLECTION s 3 ITEMS, ktore su inicializovane VALUE prenesenou v 2. PARAMETER.
	vector<int>													Vector4(3,999);

	PrintCollection(L"VECTOR 4",Vector4);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorAssignment(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector1;

		Vector1.reserve(10);

		Vector1.push_back(CInt(10));
		
		PrintLineSeparator();

		Vector1.push_back(CInt(20));

		PrintLineSeparator();

		Vector1.push_back(CInt(30));

		PrintLineSeparator();

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// !!! Pouzije sa COPY OPERATOR=.
		vector<CInt>											Vector2;

		Vector2=Vector1;

		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// !!! Pouzije sa MOVE OPERATOR=.
		vector<CInt>											Vector3;

		Vector3=std::move(Vector1);

		PrintCollection(L"VECTOR 3",Vector3);

		PrintLineSeparator();

		vector<CInt>											Vector4;

		Vector4.reserve(10);

		// Pouzije sa OPERATOR= priradzujuci INITIALIZER LIST.
		Vector4={1,2,3,4,5};

		PrintCollection(L"VECTOR 4",Vector4);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAssign(void)
{
	PrintLineSeparator();

	{
		array<CInt,3>											Array{CInt(1),CInt(2),CInt(3)};
		vector<CInt>											Vector1;

		PrintCollection(L"ARRAY",Array);

		// !!! Pre kazdy ITEM sa vola COPY CONSTRUCTOR.
		Vector1.assign(Array.cbegin(),Array.cend());

		PrintLineSeparator();

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		vector<CInt>											Vector2;

		Vector2.assign({CInt(1),CInt(2),CInt(3)});

		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		vector<CInt>											Vector3;

		Vector3.assign(3,CInt(999));

		PrintCollection(L"VECTOR 3",Vector3);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSizeOperations(void)
{
	PrintLineSeparator();

	vector<int>													Vector{3,4,6,8,2};

	PrintCollection(L"VECTOR",Vector);

	wcout << L"SIZE [" << Vector.size() << L"] !" << endl;
	wcout << L"MAX SIZE [" << Vector.max_size() << L"] !" << endl;
	wcout << L"EMPTY [" << Vector.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestResize(void)
{
	PrintLineSeparator();

	vector<int>													Vector{5,4,8,9,23};

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	Vector.resize(3);

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// Doplni sa NULAMI.
	Vector.resize(6);

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	// Doplni sa hodnotou 999.
	Vector.resize(9,999);

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestShrinkToFit(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector;

		Vector.reserve(100);

		Vector.push_back(CInt(1));
		Vector.push_back(CInt(2));
		Vector.push_back(CInt(3));
		Vector.push_back(CInt(4));
		Vector.push_back(CInt(5));

		wcout << L"CAPACITY [" << Vector.capacity() << L"] !" << endl;

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();

		Vector.shrink_to_fit();

		wcout << L"CAPACITY [" << Vector.capacity() << L"] !" << endl;

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestClear(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue{5,4,8,9,23};

	PrintCollection(L"DEQUEUE",Dequeue);

	PrintLineSeparator();

	Dequeue.clear();

	PrintCollection(L"DEQUEUE",Dequeue);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCapacity(void)
{
	PrintLineSeparator();

	vector<int>													Vector;

	wcout << L"CAPACITY [" << Vector.capacity() << L"] !" << endl;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);
	Vector.push_back(7);
	Vector.push_back(8);
	Vector.push_back(9);

	wcout << L"CAPACITY [" << Vector.capacity() << L"] !" << endl;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIterators(void)
{
	PrintLineSeparator();

	vector<int>													Vector1({10,20,30,40,50});
	const vector<int>&											Vector2=Vector1;

	wcout << L"VECTOR 1 [";

	for(vector<int>::iterator Iterator=Vector1.begin();Iterator!=Vector1.end();Iterator++)
	{
		if (Iterator!=Vector1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"VECTOR 1 [";

	for(vector<int>::const_iterator Iterator=Vector1.cbegin();Iterator!=Vector1.cend();Iterator++)
	{
		if (Iterator!=Vector1.cbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"VECTOR 2 [";

	for(vector<int>::const_iterator Iterator=Vector2.begin();Iterator!=Vector2.end();Iterator++)
	{
		if (Iterator!=Vector2.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VECTOR 1 [";

	for(vector<int>::reverse_iterator Iterator=Vector1.rbegin();Iterator!=Vector1.rend();Iterator++)
	{
		if (Iterator!=Vector1.rbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"VECTOR 1 [";

	for(vector<int>::const_reverse_iterator Iterator=Vector1.crbegin();Iterator!=Vector1.crend();Iterator++)
	{
		if (Iterator!=Vector1.crbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"VECTOR 2 [";

	for(vector<int>::const_reverse_iterator Iterator=Vector2.rbegin();Iterator!=Vector2.rend();Iterator++)
	{
		if (Iterator!=Vector2.rbegin())
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
void TestFront(void)
{
	PrintLineSeparator();

	vector<int>													Vector1({1,2,3,4,5});

	PrintCollection(L"VECTOR 1",Vector1);

	wcout << L"VECTOR 1 FRONT [" << Vector1.front() << L"] !" << endl;

	const vector<int>&											Vector2=Vector1;

	PrintCollection(L"VECTOR 2",Vector2);

	wcout << L"VECTOR 2 FRONT [" << Vector2.front() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBack(void)
{
	PrintLineSeparator();

	vector<int>													Vector1({1,2,3,4,5});

	PrintCollection(L"VECTOR 1",Vector1);

	wcout << L"VECTOR 1 BACK [" << Vector1.back() << L"] !" << endl;

	const vector<int>&											Vector2=Vector1;

	PrintCollection(L"VECTOR 2",Vector2);

	wcout << L"VECTOR 2 BACK [" << Vector2.back() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorSubscript1(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue1{5,4,8,9,23};

	PrintCollection(L"DEQUEUE 1",Dequeue1);

	wcout << L"DEQUEUE 1 [2] VALUE [" << Dequeue1[2] << L"] !" << endl;

	PrintLineSeparator();

	const deque<int>&											Dequeue2=Dequeue1;

	wcout << L"DEQUEUE 2 [2] VALUE [" << Dequeue2[2] << L"] !" << endl;

	PrintCollection(L"DEQUEUE 2",Dequeue2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperatorSubscript2(void)
{
	PrintLineSeparator();

	{
		map<CInt,CInt>											Map;

		Map.insert(map<int,int>::value_type(1,11));
		Map.insert(map<int,int>::value_type(2,12));
		Map.insert(map<int,int>::value_type(3,13));
		Map.insert(map<int,int>::value_type(4,14));
		Map.insert(map<int,int>::value_type(5,15));

		PrintMap(L"MAP",Map);

		CInt													Int(20);

		Map[1]=CInt(44);

		// Vola sa VERSION FUNCTION s MOVE OPERATOR.
		wcout << L"MAP [2] VALUE [" << Map[CInt(2)] << L"] !" << endl;

		PrintMap(L"MAP",Map);

		// Vola sa VERSION FUNCTION s COPY OPERATOR.
		// !!! Prida ITEM s hodnotou KEY '20' a hodnotou VALUE '0' do COLLECTION.
		wcout << L"MAP [20] VALUE [" << Map[Int] << L"] !" << endl;

		PrintMap(L"MAP",Map);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAt1(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue1{5,4,8,9,23};

	PrintCollection(L"DEQUEUE 1",Dequeue1);

	Dequeue1.at(2)=17;

	wcout << L"DEQUEUE 1 [2] VALUE [" << Dequeue1.at(2) << L"] !" << endl;

	PrintCollection(L"DEQUEUE 1",Dequeue1);

	try
	{
		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"DEQUEUE 1 [20] VALUE [" << Dequeue1.at(20) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintCollection(L"DEQUEUE 1",Dequeue1);

	PrintLineSeparator();

	const deque<int>&											Dequeue2=Dequeue1;

	wcout << L"DEQUEUE 2 [2] VALUE [" << Dequeue2.at(2) << L"] !" << endl;

	try
	{
		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"DEQUEUE 2 [20] VALUE [" << Dequeue2.at(20) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintCollection(L"DEQUEUE 2",Dequeue2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAt2(void)
{
	PrintLineSeparator();

	map<int,int>												Map1;

	Map1.insert(map<int,int>::value_type(1,11));
	Map1.insert(map<int,int>::value_type(2,12));
	Map1.insert(map<int,int>::value_type(3,13));
	Map1.insert(map<int,int>::value_type(4,14));
	Map1.insert(map<int,int>::value_type(5,15));

	PrintMap(L"MAP 1",Map1);

	Map1.at(2)=17;

	wcout << L"MAP 1 [2] VALUE [" << Map1.at(2) << L"] !" << endl;

	PrintMap(L"MAP 1",Map1);

	try
	{
		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"MAP 1 [20] VALUE [" << Map1.at(20) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintMap(L"MAP 1",Map1);

	PrintLineSeparator();

	const map<int,int>&											Map2=Map1;

	wcout << L"MAP 2 [2] VALUE [" << Map2.at(2) << L"] !" << endl;

	try
	{
		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"DEQUEUE 2 [20] VALUE [" << Map2.at(20) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintMap(L"MAP 2",Map2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSingleInsert1(void)
{
	PrintLineSeparator();

	{
		set<CInt>												Set{10,20};
		CInt													Int(30);

		PrintCollection(L"SET",Set);

		PrintLineSeparator();

		// Pouziva sa COPY SEMANTICS.
		pair<set<CInt>::iterator,bool>							InsertResult1=Set.insert(Int);

		if (InsertResult1.second==true)
		{
			wcout << L"ITEM [" << (*InsertResult1.first) << L"] ADDED to COLLECTION !" << endl;
		}
		else
		{
			wcout << L"ITEM [" << (*InsertResult1.first) << L"] was NOT ADDED to COLLECTION !" << endl;
		}

		PrintCollection(L"SET",Set);

		PrintLineSeparator();

		// Pouziva sa COPY SEMANTICS.
		pair<set<CInt>::iterator,bool>							InsertResult2=Set.insert(Int);

		if (InsertResult2.second==true)
		{
			wcout << L"ITEM [" << (*InsertResult2.first) << L"] ADDED to COLLECTION !" << endl;
		}
		else
		{
			wcout << L"ITEM [" << (*InsertResult2.first) << L"] was NOT ADDED to COLLECTION !" << endl;
		}

		PrintCollection(L"SET",Set);

		PrintLineSeparator();

		// Pouziva sa MOVE SEMANTICS.
		pair<set<CInt>::iterator,bool>							InsertResult3=Set.insert(CInt(40));

		if (InsertResult3.second==true)
		{
			wcout << L"ITEM [" << (*InsertResult3.first) << L"] ADDED to COLLECTION !" << endl;
		}
		else
		{
			wcout << L"ITEM [" << (*InsertResult3.first) << L"] was NOT ADDED to COLLECTION !" << endl;
		}

		PrintCollection(L"SET",Set);

		PrintLineSeparator();

		// Pouziva sa MOVE SEMANTICS.
		pair<set<CInt>::iterator,bool>							InsertResult4=Set.insert(CInt(40));

		if (InsertResult4.second==true)
		{
			wcout << L"ITEM [" << (*InsertResult4.first) << L"] ADDED to COLLECTION !" << endl;
		}
		else
		{
			wcout << L"ITEM [" << (*InsertResult4.first) << L"] was NOT ADDED to COLLECTION !" << endl;
		}

		PrintCollection(L"SET",Set);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSingleInsert2(void)
{
	PrintLineSeparator();

	{
		multiset<CInt>											MultiSet{10,20};
		CInt													Int(30);

		PrintCollection(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// Pouziva sa COPY SEMANTICS.
		multiset<CInt>::iterator								Iterator1=MultiSet.insert(Int);

		wcout << L"ITEM [" << *Iterator1 << L"] ADDED to COLLECTION !" << endl;

		PrintCollection(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// Pouziva sa COPY SEMANTICS.
		multiset<CInt>::iterator								Iterator2=MultiSet.insert(Int);

		wcout << L"ITEM [" << *Iterator2 << L"] ADDED to COLLECTION !" << endl;

		PrintCollection(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// Pouziva sa MOVE SEMANTICS.
		multiset<CInt>::iterator								Iterator3=MultiSet.insert(CInt(40));

		wcout << L"ITEM [" << *Iterator3 << L"] ADDED to COLLECTION !" << endl;

		PrintCollection(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// Pouziva sa MOVE SEMANTICS.
		multiset<CInt>::iterator								Iterator4=MultiSet.insert(CInt(40));

		wcout << L"ITEM [" << *Iterator4 << L"] ADDED to COLLECTION !" << endl;

		PrintCollection(L"MULTISET",MultiSet);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSingleInsert3(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector{10,20,30};

		Vector.reserve(10);

		CInt													Int(888);

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();

		vector<CInt>::const_iterator							Position1=find(Vector.cbegin(),Vector.cend(),20);

		// !!! Prida ITEM pomocou COPY SEMANTICS.
		vector<CInt>::iterator									Iterator1=Vector.insert(Position1,Int);

		wcout << L"ITEM [" << *Iterator1 << L"] ADDED to COLLECTION !" << endl;

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();

		vector<CInt>::const_iterator							Position2=find(Vector.cbegin(),Vector.cend(),20);

		// !!! Prida ITEM pomocou MOVE SEMANTICS.
		vector<CInt>::iterator									Iterator2=Vector.insert(Position2,CInt(999));

		wcout << L"ITEM [" << *Iterator2 << L"] ADDED to COLLECTION !" << endl;

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiInsert(void)
{
	PrintLineSeparator();

	set<int>													Set;

	Set.insert({10,20,30});

	PrintCollection(L"SET",Set);

	PrintLineSeparator();

	vector<int>													SmallVector({55,66});

	Set.insert(SmallVector.cbegin(),SmallVector.cend());

	PrintCollection(L"SET",Set);

	PrintLineSeparator();

	vector<int>													Vector({10,20,30});

	PrintCollection(L"VECTOR",Vector);

	vector<int>::const_iterator									Position1=find(Vector.cbegin(),Vector.cend(),20);
	vector<int>::const_iterator									Result1=Vector.insert(Position1,{99,88});

	wcout << L"ITEMS since ITEM [" << *Result1 << L"] ADDED to COLLECTION !" << endl;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>::const_iterator									Position2=find(Vector.cbegin(),Vector.cend(),30);
	vector<int>::const_iterator									Result2=Vector.insert(Position2,2,22);

	wcout << L"ITEMS since ITEM [" << *Result2 << L"] ADDED to COLLECTION !" << endl;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	vector<int>::const_iterator									Position3=find(Vector.cbegin(),Vector.cend(),10);
	vector<int>::const_iterator									Result3=Vector.insert(Position3,SmallVector.cbegin(),SmallVector.cend());

	wcout << L"ITEMS since ITEM [" << *Result3 << L"] ADDED to COLLECTION !" << endl;

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEmplace1(void)
{
	PrintLineSeparator();

	{
		set<CInt>												Set;

		Set.insert(CInt(11));

		PrintSet(L"SET",Set);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM uz v SET NACHADZA.
		pair<set<CInt>::iterator,bool>							Result1=Set.emplace(set<CInt>::value_type(2));

		if (Result1.second==true)
		{
			wcout << L"ITEM (" << *(Result1.first) << L") was ADDED to SET !" << endl;
		}
		else
		{
			wcout << L"ITEM (2) was NOT ADDED to SET !" << endl;
		}

		PrintSet(L"SET",Set);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM s danym KEY uz v SET NACHADZA.
		pair<set<CInt>::iterator,bool>							Result2=Set.emplace(set<CInt>::value_type(2));

		// !!!!! Kedze ITEM s KEY '2' uz v SET EXISTUJE, tak volanie METHOD insert() ZLYHA.
		if (Result2.second==true)
		{
			wcout << L"ITEM (" << *(Result2.first) << L") was ADDED to SET !" << endl;
		}
		else
		{
			wcout << L"ITEM (2) was NOT ADDED to SET !" << endl;
		}

		PrintSet(L"SET",Set);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEmplace2(void)
{
	PrintLineSeparator();

	{
		multiset<CInt>											MultiSet{multiset<CInt>::value_type(1)};

		PrintMultiSet(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
		multiset<CInt>::iterator								Result1=MultiSet.emplace(multiset<CInt>::value_type(2));

		wcout << L"ITEM (" << *Result1 << L") was ADDED to MULTISET !" << endl;

		PrintMultiSet(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM.
		multiset<CInt>::iterator								Result2=MultiSet.emplace(multiset<CInt>::value_type(2));

		// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
		wcout << L"ITEM (" << *Result2 << L") was ADDED to MULTISET !" << endl;

		PrintMultiSet(L"MULTISET",MultiSet);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEmplace3(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector{10,20,30};

		Vector.reserve(10);

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();

		vector<CInt>::const_iterator							Position=find(Vector.cbegin(),Vector.cend(),20);
		vector<CInt>::iterator									Iterator=Vector.emplace(Position,888);

		wcout << L"ITEM [" << *Iterator << L"] ADDED to COLLECTION !" << endl;

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEmplaceHint(void)
{
	PrintLineSeparator();

	{
		set<CInt>												Set{CInt(10),CInt(20),CInt(30)};

		PrintSet(L"SET",Set);

		PrintLineSeparator();

		set<CInt>::const_iterator								Position=find(Set.cbegin(),Set.cend(),20);
		set<CInt>::iterator										Iterator1=Set.emplace_hint(Position,25);

		wcout << L"ITEM [" << *Iterator1 << L"] ADDED to COLLECTION !" << endl;

		PrintSet(L"SET",Set);

		PrintLineSeparator();

		// Zly HINT.
		set<CInt>::iterator										Iterator2=Set.emplace_hint(Position,888);

		wcout << L"ITEM [" << *Iterator2 << L"] ADDED to COLLECTION !" << endl;

		PrintSet(L"SET",Set);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPushFront(void)
{
	PrintLineSeparator();

	{
		deque<CInt>												Dequeue{5,4,8};

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();

		CInt													Int(33);

		// Pouzije sa COPY VERSION METOHD.
		Dequeue.push_front(Int);

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();

		// Pouzije sa MOVE VERSION METOHD.
		Dequeue.push_front(CInt(999));

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEmplaceFront(void)
{
	PrintLineSeparator();

	{
		deque<CInt>												Dequeue{5,4,8};

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();

		Dequeue.emplace_front(999);

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPushBack(void)
{
	PrintLineSeparator();

	{
		deque<CInt>												Dequeue{5,4,8};

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();

		CInt													Int(33);

		// Pouzije sa COPY VERSION METOHD.
		Dequeue.push_back(Int);

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();

		// Pouzije sa MOVE VERSION METOHD.
		Dequeue.push_back(CInt(999));

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEmplaceBack(void)
{
	PrintLineSeparator();

	{
		deque<CInt>												Dequeue{5,4,8};

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();

		Dequeue.emplace_back(999);

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestErase(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet{10,20,30,20,333,30,55,87,147};

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	multiset<int>::size_type									NumberOfItemsRemoved=MultiSet.erase(20);

	wcout << L"NUMBER of REMOVED ITEMS [" << NumberOfItemsRemoved << L"] !" << endl;

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	multiset<int>::const_iterator								Position1=find(MultiSet.cbegin(),MultiSet.cend(),10);
	multiset<int>::const_iterator								Result1=MultiSet.erase(Position1);

	wcout << L"NEXT ITEM after REMOVED ITEM [" << *Result1 << L"] !" << endl;

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	multiset<int>::const_iterator								Position2=find(MultiSet.cbegin(),MultiSet.cend(),30);
	multiset<int>::const_iterator								Position3=find(MultiSet.cbegin(),MultiSet.cend(),87);

	multiset<int>::const_iterator								Result2=MultiSet.erase(Position2,Position3);

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPopFrontPopBack(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue{5,4,8,9,23};

	PrintCollection(L"DEQUEUE",Dequeue);

	PrintLineSeparator();

	Dequeue.pop_front();
	Dequeue.pop_back();

	PrintCollection(L"DEQUEUE",Dequeue);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComparisonOperators(void)
{
	PrintLineSeparator();

	vector<int>													Vector1{3,4,6,8,2};
	vector<int>													Vector2{3,4,16,8,2};

	PrintCollection(L"VECTOR 1",Vector1);
	PrintCollection(L"VECTOR 2",Vector2);

	PrintLineSeparator();

	wcout << L"OPERATOR== [" << ((Vector1==Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR!= [" << ((Vector1!=Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR< [" << ((Vector1<Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR<= [" << ((Vector1<=Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR>= [" << ((Vector1>=Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR> [" << ((Vector1>Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSwap(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector1({CInt(11),CInt(12),CInt(13)});
		vector<CInt>											Vector2({CInt(21),CInt(22),CInt(23)});

		PrintLineSeparator();

		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// !!! Vola sa METHOD swap().
		Vector1.swap(Vector2);

		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// !!! Vola sa FUNCTION swap().
		swap(Vector1,Vector2);

		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRemoveRemoveIf(void)
{
	PrintLineSeparator();

	list<int>													List;

	List.push_back(10);
	List.push_back(20);
	List.push_back(30);
	List.push_back(40);
	List.push_back(50);
	List.push_back(60);
	List.push_back(70);
	List.push_back(80);
	List.push_back(66);
	List.push_back(66);
	List.push_back(66);
	List.push_back(90);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// !!! Odstrani vsetky ITEMS s hodnotou '66'.
	List.remove(66);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// !!! Odstrani vsetky ITEMS s hodnotami v intervale <30,70>.
	List.remove_if([](int Value)->bool{return(Value>=30 && Value<=70);});

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnique(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,4,4,1,4,3,3});
	list<int>													List2({2,5,4,4,4,1,4,3,3});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// Odstrani kazdy vyskyt 2 za sebou identickych ITEMS.
	List1.unique();

	// Odstrani kazdy vyskyt 2 za sebou identickych ITEMS.
	// 2. PARAMETER definuje CUSTOM COMPARER.
	List2.unique([](int Value1, int Value2)->bool{return(Value1==Value2);});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMerge1(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,1,3});
	list<int>													List2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	List1.sort();
	List2.sort();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'List2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'List1'.
	// !!! COLLECTION je prenesena cez COPY SEMANTICS.
	List1.merge(List2);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMerge2(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,1,3});
	list<int>													List2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	List1.sort();
	List2.sort();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'List2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'List1'.
	// !!! COLLECTION je prenesena cez MOVE SEMANTICS.
	List1.merge(std::move(List2));

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMerge3(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,1,3});
	list<int>													List2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	List1.sort();
	List2.sort();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'List2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'List1'.
	// !!! COLLECTION je prenesena cez COPY SEMANTICS.
	// 2. PARAMETER definuje CUSTOM COMPARER.
	List1.merge(List2,[](int Value1, int Value2)->bool{return(Value1<Value2);});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMerge4(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,1,3});
	list<int>													List2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	List1.sort();
	List2.sort();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'List2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'List1'.
	// !!! COLLECTION je prenesena cez MOVE SEMANTICS.
	// 2. PARAMETER definuje CUSTOM COMPARER.
	List1.merge(std::move(List2),[](int Value1, int Value2)->bool{return(Value1<Value2);});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSort(void)
{
	PrintLineSeparator();

	list<int>													List({2,5,4,1,3});

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	List.sort();

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	List.sort([](int Value1, int Value2)->bool{return(Value1>Value2);});

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReverse(void)
{
	PrintLineSeparator();

	list<int>													List({2,5,4,1,3});

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	List.reverse();

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSplice1(void)
{
	PrintLineSeparator();

	list<int>													List1({1,2,3,4,5});
	list<int>													List2({11,12,13,14,15});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	list<int>::const_iterator									Iterator1=List1.cbegin();

	Iterator1++;
	Iterator1++;

	wcout << L"ITEM [" << *Iterator1 << L"] !" << endl;

	// ITEMS sa pridaju pred POSITION na ktoru ukazuje 'Iterator1'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez COPY SEMANTICS.
	List1.splice(Iterator1,List2);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	list<int>::const_iterator									Iterator2=List1.cbegin();

	Iterator2++;
	Iterator2++;
	Iterator2++;
	Iterator2++;

	wcout << L"ITEM [" << *Iterator2 << L"] !" << endl;

	// ITEMS sa pridaju pred POSITION na ktoru ukazuje 'Iterator2'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez MOVE SEMANTICS.
	List1.splice(Iterator2,list<int>({111,222}));

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSplice2(void)
{
	PrintLineSeparator();

	list<int>													List1({1,2,3,4,5});
	list<int>													List2({11,12,13,14,15});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	list<int>::const_iterator									SourceIterator1=List1.cbegin();
	list<int>::const_iterator									DestinationIterator1=List2.cbegin();

	SourceIterator1++;
	SourceIterator1++;

	DestinationIterator1++;
	DestinationIterator1++;
	DestinationIterator1++;

	wcout << L"SOURCE ITEM [" << *SourceIterator1 << L"] !" << endl;
	wcout << L"DESTINATION ITEM [" << *DestinationIterator1 << L"] !" << endl;

	// ITEM na ktory odkazuje ITERATOR 'DestinationIterator1' sa prida pred POSITION na ktoru ukazuje 'Iterator1'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez COPY SEMANTICS.
	List1.splice(SourceIterator1,List2,DestinationIterator1);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	list<int>::const_iterator									SourceIterator2=List1.cbegin();
	list<int>::const_iterator									DestinationIterator2=List2.cbegin();

	SourceIterator2++;
	SourceIterator2++;
	SourceIterator2++;
	SourceIterator2++;

	DestinationIterator2++;

	wcout << L"SOURCE ITEM [" << *SourceIterator2 << L"] !" << endl;
	wcout << L"DESTINATION ITEM [" << *DestinationIterator2 << L"] !" << endl;

	// ITEM na ktory odkazuje ITERATOR 'DestinationIterator2' sa prida pred POSITION na ktoru ukazuje 'Iterator2'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez MOVE SEMANTICS.
	List1.splice(SourceIterator2,std::move(List2),DestinationIterator2);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSplice3(void)
{
	PrintLineSeparator();

	list<int>													List1({1,2,3,4,5});
	list<int>													List2({11,12,13,14,15,16,17,18});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	list<int>::const_iterator									SourceIterator1=List1.cbegin();

	SourceIterator1++;
	SourceIterator1++;

	list<int>::const_iterator									DestinationFromIterator1=List2.cbegin();

	DestinationFromIterator1++;

	list<int>::const_iterator									DestinationToIterator1=DestinationFromIterator1;

	DestinationToIterator1++;
	DestinationToIterator1++;
	DestinationToIterator1++;

	wcout << L"SOURCE ITEM [" << *SourceIterator1 << L"] !" << endl;
	wcout << L"DESTINATION FROM ITEM [" << *DestinationFromIterator1 << L"] !" << endl;
	wcout << L"DESTINATION TO ITEM [" << *DestinationToIterator1 << L"] !" << endl;

	// ITEMS medzi ITERATORS (DestinationFromIterator1,DestinationToIterator1) sa pridaju pred POSITION na ktoru ukazuje 'Iterator1'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez COPY SEMANTICS.
	List1.splice(SourceIterator1,List2,DestinationFromIterator1,DestinationToIterator1);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	list<int>::const_iterator									SourceIterator2=List1.cbegin();

	SourceIterator2++;
	SourceIterator2++;

	list<int>::const_iterator									DestinationFromIterator2=List2.cbegin();

	DestinationFromIterator2++;

	list<int>::const_iterator									DestinationToIterator2=DestinationFromIterator2;

	DestinationToIterator2++;
	DestinationToIterator2++;
	DestinationToIterator2++;

	wcout << L"SOURCE ITEM [" << *SourceIterator2 << L"] !" << endl;
	wcout << L"DESTINATION FROM ITEM [" << *DestinationFromIterator2 << L"] !" << endl;
	wcout << L"DESTINATION TO ITEM [" << *DestinationToIterator2 << L"] !" << endl;

	// ITEMS medzi ITERATORS (DestinationFromIterator2,DestinationToIterator2) sa pridaju pred POSITION na ktoru ukazuje 'Iterator2'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez MOVE SEMANTICS.
	List1.splice(SourceIterator2,std::move(List2),DestinationFromIterator2,DestinationToIterator2);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBeforeBegin(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({1,2,3,4,5});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);

	PrintLineSeparator();

	ForwardList1.insert_after(ForwardList1.before_begin(),333);
	ForwardList1.insert_after(ForwardList1.cbefore_begin(),444);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);

	PrintLineSeparator();

	const forward_list<int>&									ForwardList2=ForwardList1;

	// Vracia CONST ITERATOR.
	forward_list<int>::const_iterator							Iterator=ForwardList2.before_begin();

	wcout << L"FIRST ITEM [" << *(++Iterator) << L"] !" << endl;

	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInsertAfter(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList({1,2,3,4,5});

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	forward_list<int>::iterator									Iterator1=ForwardList.insert_after(ForwardList.cbefore_begin(),11);

	wcout << L"INSERTED ITEM [" << *(Iterator1) << L"] !" << endl;

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Position1=ForwardList.cbefore_begin();

	Position1++;
	Position1++;

	forward_list<int>::iterator									Iterator2=ForwardList.insert_after(Position1,3,15);

	wcout << L"LAST INSERTED ITEM [" << *(Iterator2) << L"] after ITEM [" << *Position1 << L"] !" << endl;

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Position2=ForwardList.cbefore_begin();

	Position2++;
	Position2++;
	Position2++;
	Position2++;

	forward_list<int>::iterator									Iterator3=ForwardList.insert_after(Position2,{33,44});

	wcout << L"LAST INSERTED ITEM [" << *(Iterator3) << L"] after ITEM [" << *Position2 << L"] !" << endl;

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	vector<int>													Vector({100,200,300});

	PrintCollection(L"VECTOR",Vector);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Position3=ForwardList.cbefore_begin();

	Position3++;
	Position3++;
	Position3++;
	Position3++;
	Position3++;
	Position3++;
	Position3++;
	Position3++;
	Position3++;

	forward_list<int>::iterator									Iterator4=ForwardList.insert_after(Position3,Vector.cbegin(),Vector.cend());

	wcout << L"LAST INSERTED ITEM [" << *(Iterator4) << L"] after ITEM [" << *Position3 << L"] !" << endl;

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEmplaceAfter(void)
{
	PrintLineSeparator();

	{
		forward_list<CInt>										ForwardList({1,2,3,4,5});

		PrintCollection(L"FORWARD LIST",ForwardList);

		PrintLineSeparator();

		forward_list<CInt>::const_iterator						Position=ForwardList.cbefore_begin();

		Position++;
		Position++;

		forward_list<CInt>::iterator							Iterator=ForwardList.emplace_after(Position,999);

		wcout << L"INSERTED ITEM [" << *Iterator << L"] after ITEM [" << *Position << L"] !" << endl;

		PrintCollection(L"FORWARD LIST",ForwardList);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEraseAfter(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList({1,2,3,4,5,6,7,8,9});

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Position=ForwardList.cbefore_begin();

	Position++;
	Position++;

	forward_list<int>::iterator									Iterator1=ForwardList.erase_after(Position);

	wcout << L"ITEM [" << *(Iterator1) << L"] after ERASED ITEM !" << endl;

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	forward_list<int>::const_iterator							PositionFrom=ForwardList.cbefore_begin();

	PositionFrom++;

	forward_list<int>::const_iterator							PositionTo=PositionFrom;

	PositionTo++;
	PositionTo++;
	PositionTo++;

	forward_list<int>::iterator									Iterator2=ForwardList.erase_after(PositionFrom,PositionTo);

	wcout << L"ITEM [" << *(Iterator2) << L"] after ERASED ITEM !" << endl;

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSpliceAfter1(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({1,2,3,4,5});
	forward_list<int>											ForwardList2({11,12,13,14,15});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Iterator1=ForwardList1.cbegin();

	Iterator1++;
	Iterator1++;

	wcout << L"ITEM [" << *Iterator1 << L"] !" << endl;

	// ITEMS sa pridaju za POSITION na ktoru ukazuje 'Iterator1'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez COPY SEMANTICS.
	ForwardList1.splice_after(Iterator1,ForwardList2);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	forward_list<int>::const_iterator							Iterator2=ForwardList1.cbegin();

	Iterator2++;
	Iterator2++;
	Iterator2++;
	Iterator2++;

	wcout << L"ITEM [" << *Iterator2 << L"] !" << endl;

	// ITEMS sa pridaju za POSITION na ktoru ukazuje 'Iterator2'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez MOVE SEMANTICS.
	ForwardList1.splice_after(Iterator2,forward_list<int>({111,222}));

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSpliceAfter2(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({1,2,3,4,5});
	forward_list<int>											ForwardList2({11,12,13,14,15});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	forward_list<int>::const_iterator							SourceIterator1=ForwardList1.cbegin();
	forward_list<int>::const_iterator							DestinationIterator1=ForwardList2.cbegin();

	SourceIterator1++;
	SourceIterator1++;

	DestinationIterator1++;
	DestinationIterator1++;
	DestinationIterator1++;

	wcout << L"SOURCE ITEM [" << *SourceIterator1 << L"] !" << endl;
	wcout << L"DESTINATION ITEM [" << *DestinationIterator1 << L"] !" << endl;

	// ITEM na ktory odkazuje ITERATOR 'DestinationIterator1' sa prida za POSITION na ktoru ukazuje 'Iterator1'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez COPY SEMANTICS.
	ForwardList1.splice_after(SourceIterator1,ForwardList2,DestinationIterator1);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	forward_list<int>::const_iterator							SourceIterator2=ForwardList1.cbegin();
	forward_list<int>::const_iterator							DestinationIterator2=ForwardList2.cbegin();

	SourceIterator2++;
	SourceIterator2++;
	SourceIterator2++;
	SourceIterator2++;

	DestinationIterator2++;

	wcout << L"SOURCE ITEM [" << *SourceIterator2 << L"] !" << endl;
	wcout << L"DESTINATION ITEM [" << *DestinationIterator2 << L"] !" << endl;

	// ITEM na ktory odkazuje ITERATOR 'DestinationIterator2' sa prida za POSITION na ktoru ukazuje 'Iterator2'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez MOVE SEMANTICS.
	ForwardList1.splice_after(SourceIterator2,std::move(ForwardList2),DestinationIterator2);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSpliceAfter3(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({1,2,3,4,5});
	forward_list<int>											ForwardList2({11,12,13,14,15,16,17,18});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	forward_list<int>::const_iterator							SourceIterator1=ForwardList1.cbegin();

	SourceIterator1++;
	SourceIterator1++;

	forward_list<int>::const_iterator							DestinationFromIterator1=ForwardList2.cbegin();

	DestinationFromIterator1++;

	forward_list<int>::const_iterator							DestinationToIterator1=DestinationFromIterator1;

	DestinationToIterator1++;
	DestinationToIterator1++;
	DestinationToIterator1++;

	wcout << L"SOURCE ITEM [" << *SourceIterator1 << L"] !" << endl;
	wcout << L"DESTINATION FROM ITEM [" << *DestinationFromIterator1 << L"] !" << endl;
	wcout << L"DESTINATION TO ITEM [" << *DestinationToIterator1 << L"] !" << endl;

	// ITEMS medzi ITERATORS (DestinationFromIterator1,DestinationToIterator1) sa pridaju za POSITION na ktoru ukazuje 'Iterator1'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez COPY SEMANTICS.
	ForwardList1.splice_after(SourceIterator1,ForwardList2,DestinationFromIterator1,DestinationToIterator1);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	forward_list<int>::const_iterator							SourceIterator2=ForwardList1.cbegin();

	SourceIterator2++;
	SourceIterator2++;

	forward_list<int>::const_iterator							DestinationFromIterator2=ForwardList2.cbegin();

	DestinationFromIterator2++;

	forward_list<int>::const_iterator							DestinationToIterator2=DestinationFromIterator2;

	DestinationToIterator2++;
	DestinationToIterator2++;
	DestinationToIterator2++;

	wcout << L"SOURCE ITEM [" << *SourceIterator2 << L"] !" << endl;
	wcout << L"DESTINATION FROM ITEM [" << *DestinationFromIterator2 << L"] !" << endl;
	wcout << L"DESTINATION TO ITEM [" << *DestinationToIterator2 << L"] !" << endl;

	// ITEMS medzi ITERATORS (DestinationFromIterator2,DestinationToIterator2) sa pridaju za POSITION na ktoru ukazuje 'Iterator2'.
	// !!! COLLECTION v 2. PARAMETERI je prenasana cez MOVE SEMANTICS.
	ForwardList1.splice_after(SourceIterator2,std::move(ForwardList2),DestinationFromIterator2,DestinationToIterator2);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCount(void)
{
	PrintLineSeparator();

	set<int>													Set;

	Set.insert(11);
	Set.insert(12);
	Set.insert(13);
	Set.insert(14);
	Set.insert(15);

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	wcout << L"SET - COUNT(11) - [" << Set.count(11) << L"] !" << endl;
	wcout << L"SET - COUNT(18) - [" << Set.count(18) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFind(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	Set1.insert(11);
	Set1.insert(12);
	Set1.insert(13);
	Set1.insert(14);
	Set1.insert(15);

	PrintSet(L"SET 1",Set1);

	PrintLineSeparator();

	PrintSetIterator(L"SET 1 - FIND(-1) -",Set1,Set1.find(-1));
	PrintSetIterator(L"SET 1 - FIND(13) -",Set1,Set1.find(13));
	PrintSetIterator(L"SET 1 - FIND(16) -",Set1,Set1.find(16));

	PrintLineSeparator();

	const set<int>&												Set2=Set1;

	PrintSetIterator(L"SET 2 - FIND(-1) -",Set2,Set2.find(-1));
	PrintSetIterator(L"SET 2 - FIND(13) -",Set2,Set2.find(13));
	PrintSetIterator(L"SET 2 - FIND(16) -",Set2,Set2.find(16));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLowerBound(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	Set1.insert(11);
	Set1.insert(12);
	Set1.insert(13);
	Set1.insert(14);
	Set1.insert(15);

	PrintSet(L"SET 1",Set1);

	PrintLineSeparator();

	PrintSetIterator(L"SET 1 - LOWER_BOUND(-1) -",Set1,Set1.lower_bound(-1));
	PrintSetIterator(L"SET 1 - LOWER_BOUND(13) -",Set1,Set1.lower_bound(13));
	PrintSetIterator(L"SET 1 - LOWER_BOUND(16) -",Set1,Set1.lower_bound(16));

	PrintLineSeparator();

	const set<int>&												Set2=Set1;

	PrintSetIterator(L"SET 2 - LOWER_BOUND(-1) -",Set2,Set2.lower_bound(-1));
	PrintSetIterator(L"SET 2 - LOWER_BOUND(13) -",Set2,Set2.lower_bound(13));
	PrintSetIterator(L"SET 2 - LOWER_BOUND(16) -",Set2,Set2.lower_bound(16));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUpperBound(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	Set1.insert(11);
	Set1.insert(12);
	Set1.insert(13);
	Set1.insert(14);
	Set1.insert(15);

	PrintSet(L"SET 1",Set1);

	PrintLineSeparator();

	PrintSetIterator(L"SET 1 - UPPER_BOUND(-1) -",Set1,Set1.upper_bound(-1));
	PrintSetIterator(L"SET 1 - UPPER_BOUND(13) -",Set1,Set1.upper_bound(13));
	PrintSetIterator(L"SET 1 - UPPER_BOUND(16) -",Set1,Set1.upper_bound(16));

	PrintLineSeparator();

	const set<int>&												Set2=Set1;

	PrintSetIterator(L"SET 2 - UPPER_BOUND(-1) -",Set2,Set2.upper_bound(-1));
	PrintSetIterator(L"SET 2 - UPPER_BOUND(13) -",Set2,Set2.upper_bound(13));
	PrintSetIterator(L"SET 2 - UPPER_BOUND(16) -",Set2,Set2.upper_bound(16));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestEqualBound(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	using														SetIteratorPair=pair<set<int>::const_iterator,set<int>::const_iterator>;
	using														SetConstIteratorPair=pair<set<int>::const_iterator,set<int>::const_iterator>;

	Set1.insert(11);
	Set1.insert(12);
	Set1.insert(13);
	Set1.insert(14);
	Set1.insert(15);

	PrintSet(L"SET 1",Set1);

	PrintLineSeparator();

	SetIteratorPair												IteratorPair1=Set1.equal_range(-1);
	SetIteratorPair												IteratorPair2=Set1.equal_range(13);
	SetIteratorPair												IteratorPair3=Set1.equal_range(16);

	PrintSetIterator(L"SET 1 - EQUAL_BOUND(-1).FIRST -",Set1,IteratorPair1.first);
	PrintSetIterator(L"SET 1 - EQUAL_BOUND(-1).SECOND -",Set1,IteratorPair1.second);
	PrintSetIterator(L"SET 1 - EQUAL_BOUND(13).FIRST -",Set1,IteratorPair2.first);
	PrintSetIterator(L"SET 1 - EQUAL_BOUND(13).SECOND -",Set1,IteratorPair2.second);
	PrintSetIterator(L"SET 1 - EQUAL_BOUND(16).FIRST -",Set1,IteratorPair3.first);
	PrintSetIterator(L"SET 1 - EQUAL_BOUND(16).SECOND -",Set1,IteratorPair3.second);

	PrintLineSeparator();

	const set<int>&												Set2=Set1;

	SetConstIteratorPair										ConstIteratorPair1=Set2.equal_range(-1);
	SetConstIteratorPair										ConstIteratorPair2=Set2.equal_range(13);
	SetConstIteratorPair										ConstIteratorPair3=Set2.equal_range(16);

	PrintSetIterator(L"SET 2 - EQUAL_BOUND(-1).FIRST -",Set2,ConstIteratorPair1.first);
	PrintSetIterator(L"SET 2 - EQUAL_BOUND(-1).SECOND -",Set2,ConstIteratorPair1.second);
	PrintSetIterator(L"SET 2 - EQUAL_BOUND(13).FIRST -",Set2,ConstIteratorPair2.first);
	PrintSetIterator(L"SET 2 - EQUAL_BOUND(13).SECOND -",Set2,ConstIteratorPair2.second);
	PrintSetIterator(L"SET 2 - EQUAL_BOUND(16).FIRST -",Set2,ConstIteratorPair3.first);
	PrintSetIterator(L"SET 2 - EQUAL_BOUND(16).SECOND -",Set2,ConstIteratorPair3.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCompareMethods(void)
{
	PrintLineSeparator();

	map<int,wstring>											Map;

	wcout << L"KEY COMPARE (10,20) [" << Map.key_comp()(10,20) << L"] !" << endl;
	wcout << L"KEY COMPARE (20,10) [" << Map.key_comp()(20,10) << L"] !" << endl;
	wcout << L"KEY COMPARE (10,10) [" << Map.key_comp()(10,10) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUE COMPARE (PAIR(10,'XXX'),PAIR(20,'YYY')) [" << Map.value_comp()(pair<const int,wstring>(10,L"XXX"),pair<const int,wstring>(20,L"YYY")) << L"] !" << endl;
	wcout << L"VALUE COMPARE (PAIR(20,'YYY'),PAIR(10,'XXX')) [" << Map.value_comp()(pair<const int,wstring>(20,L"YYY"),pair<const int,wstring>(10,L"XXX")) << L"] !" << endl;
	wcout << L"VALUE COMPARE (PAIR(10,'XXX'),PAIR(10,'XXX')) [" << Map.value_comp()(pair<const int,wstring>(10,L"XXX"),pair<const int,wstring>(10,L"XXX")) << L"] !" << endl;

	PrintLineSeparator();

	unordered_map<int,wstring>									UnorderedMap;

	wcout << L"KEY EQUAL (10,20) [" << UnorderedMap.key_eq()(10,20) << L"] !" << endl;
	wcout << L"KEY EQUAL (20,10) [" << UnorderedMap.key_eq()(20,10) << L"] !" << endl;
	wcout << L"KEY EQUAL (10,10) [" << UnorderedMap.key_eq()(10,10) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"HASH FUNCTION (-10) [" << UnorderedMap.hash_function()(-10) << L"] !" << endl;
	wcout << L"HASH FUNCTION (10) [" << UnorderedMap.hash_function()(10) << L"] !" << endl;
	wcout << L"HASH FUNCTION (100) [" << UnorderedMap.hash_function()(100) << L"] !" << endl;
	wcout << L"HASH FUNCTION (10000000) [" << UnorderedMap.hash_function()(10000000) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLoadFactor1(void)
{
	PrintLineSeparator();

	unordered_set<int>											UnorderedSet;

	wcout << L"LOAD FACTOR [" << UnorderedSet.load_factor() << L"] !" << endl;
	wcout << L"MAX LOAD FACTOR [" << UnorderedSet.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLoadFactor2(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	Set1.insert(0);
	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);
	Set1.insert(5);
	Set1.insert(6);
	Set1.insert(7);
	Set1.insert(8);
	Set1.insert(9);

	PrintCollection(L"SET 1",Set1);

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - MAX BUCKET COUNT [" << Set1.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Set1.insert(Index);
	}

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - MAX BUCKET COUNT [" << Set1.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	unordered_set<int>											Set2;

	Set2.max_load_factor(5);

	Set2.insert(0);
	Set2.insert(1);
	Set2.insert(2);
	Set2.insert(3);
	Set2.insert(4);
	Set2.insert(5);
	Set2.insert(6);
	Set2.insert(7);
	Set2.insert(8);
	Set2.insert(9);

	PrintCollection(L"SET 2",Set2);

	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - MAX BUCKET COUNT [" << Set2.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Set2.insert(Index);
	}

	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - MAX BUCKET COUNT [" << Set2.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRehash(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(5);
	Set1.insert(6);
	Set1.insert(7);
	Set1.insert(8);

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(9);
	Set1.insert(10);

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(8);
	Set1.insert(9);
	Set1.insert(10);
	
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	unordered_set<int>											Set2(Set1.cbegin(),Set1.cend(),Set1.bucket_count()/2);

	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	Set2.rehash(Set2.size());

	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Neznizi sa pocet BUCKETS. COLLECTION poziadavku ignoruje. METHOD rehash() je len POZIADAVKA o znizenie BUCKETS, ktoru moze COLLECTION ignorovat.
	Set2.rehash(Set2.size()/2);

	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBuckets1(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set;

	Set.max_load_factor(3);

	Set.insert(1);
	Set.insert(2);
	Set.insert(3);
	Set.insert(4);
	Set.insert(5);

	PrintCollection(L"SET",Set);

	PrintLineSeparator();

	wcout << L"SET - MAX BUCKET COUNT [" << Set.max_bucket_count() << L"] !" << endl;
	wcout << L"SET - BUCKET COUNT [" << Set.bucket_count() << L"] !" << endl;
	wcout << L"SET - ITEM(1) - BUCKET [" << Set.bucket(1) << L"] !" << endl;
	wcout << L"SET - ITEM(2) - BUCKET [" << Set.bucket(2) << L"] !" << endl;
	wcout << L"SET - ITEM(3) - BUCKET [" << Set.bucket(3) << L"] !" << endl;
	wcout << L"SET - ITEM(4) - BUCKET [" << Set.bucket(4) << L"] !" << endl;
	wcout << L"SET - ITEM(5) - BUCKET [" << Set.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Set.bucket_count();Bucket++)
	{
		wcout << L"SET - BUCKET SIZE (" << Bucket << L") [" << Set.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Set.bucket_count();Bucket++)
	{
		wcout << L"SET - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_set<int>::const_local_iterator Iterator=Set.cbegin(Bucket);Iterator!=Set.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << *Iterator;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestBuckets2(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map;

	Map.max_load_factor(3);

	Map.insert(pair<int,int>(1,11));
	Map.insert(pair<int,int>(2,12));
	Map.insert(pair<int,int>(3,13));
	Map.insert(pair<int,int>(4,14));
	Map.insert(pair<int,int>(5,15));

	PrintUnorderedMap(L"MAP",Map);

	PrintLineSeparator();

	wcout << L"MAP - BUCKET COUNT [" << Map.bucket_count() << L"] !" << endl;
	wcout << L"MAP - ITEM(1) - BUCKET [" << Map.bucket(1) << L"] !" << endl;
	wcout << L"MAP - ITEM(2) - BUCKET [" << Map.bucket(2) << L"] !" << endl;
	wcout << L"MAP - ITEM(3) - BUCKET [" << Map.bucket(3) << L"] !" << endl;
	wcout << L"MAP - ITEM(4) - BUCKET [" << Map.bucket(4) << L"] !" << endl;
	wcout << L"MAP - ITEM(5) - BUCKET [" << Map.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map.bucket_count();Bucket++)
	{
		wcout << L"MAP - BUCKET SIZE (" << Bucket << L") [" << Map.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map.bucket_count();Bucket++)
	{
		wcout << L"MAP - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_map<int,int>::local_iterator Iterator=Map.begin(Bucket);Iterator!=Map.end(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";

			// Zmeni sa hodnota VALUE.
			Iterator->second*=2;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map.bucket_count();Bucket++)
	{
		wcout << L"MAP - BUCKET (" << Bucket << L") - MODIFIED VALUES [";

		bool													AddSpace=false;
		const unordered_map<int,int>&							ConstMap=Map;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		// Pouzivaju sa CONST verzie begin() a end() METHODS.
		for(unordered_map<int,int>::const_local_iterator Iterator=ConstMap.begin(Bucket);Iterator!=ConstMap.end(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestFill(void)
{
	PrintLineSeparator();

	{
		array<CInt,3>											Array{CInt(1),CInt(2),CInt(3)};

		PrintCollection(L"ARRAY",Array);

		PrintLineSeparator();

		Array.fill(CInt(999));

		PrintCollection(L"ARRAY",Array);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestData(void)
{
	PrintLineSeparator();

	vector<int>													Vector1({10,20,30,40,50});

	PrintCollection(L"VECTOR 1",Vector1);

	int*														Pointer1=Vector1.data();

	for(size_t Index=0;Index<Vector1.size();Index++)
	{
		Pointer1[Index]*=2;
	}

	PrintCollection(L"VECTOR 1",Vector1);

	PrintLineSeparator();

	const vector<int>&											Vector2=Vector1;

	PrintCollection(L"VECTOR 2",Vector2);

	wcout << L"VECTOR 2 [";

	const int*													Pointer2=Vector2.data();

	for(size_t Index=0;Index<Vector2.size();Index++)
	{
		if (Index!=0)
		{
			wcout << L" ";
		}

		wcout << Pointer2[Index];
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGetAllocator(void)
{
	PrintLineSeparator();

	vector<int>													Vector;
	vector<int>::allocator_type									Allocator=Vector.get_allocator();

	wcout << "ALLOCATOR TYPE [" << ConvertStringToWideString(typeid(Allocator).name()) << L"] !" << endl;
	wcout << "MAX SIZE [" << Allocator.max_size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorCapacity(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector;

		// CAPACITY je nastavena na 4 ITEMS.
		// !!! Nevola sa DEFAULT CONSTRUCTOR.
		Vector.reserve(4);

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		Vector.push_back(CInt(1));
		Vector.push_back(CInt(2));
		Vector.push_back(CInt(3));
		Vector.push_back(CInt(4));

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();

		// !!!!! Pri realokacii ARRAY sa NEVOLA COPY OPERATOR= ani MOVE OPERATOR=, ale dochadza iba k prekopirovaniu MEMORY do novoalokovaneho bloku.
		Vector.push_back(CInt(5));

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		Vector.push_back(CInt(6));

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		Vector.push_back(CInt(7));

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		Vector.push_back(CInt(8));

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		Vector.push_back(CInt(9));

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		Vector.push_back(CInt(10));

		size_t													Capacity1=Vector.capacity();

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();

		// !!!!! METHOD shrink_to_fit() je len REQUEST o zmenu CAPACITY. To ci METHOD shrink_to_fit() zmenu CAPACITY naozaj vykonaje IMPLEMENTACNE ZAVISLE.
		Vector.shrink_to_fit();

		wcout << L"VECTOR - CAPACITY [" << Vector.capacity() << L"] !" << endl;

		size_t													Capacity2=Vector.capacity();

		if (Capacity1==Capacity2)
		{
			wcout << L"VECTOR CAPACITY was NOT CHANGED !" << endl;
		}
		else
		{
			wcout << L"VECTOR CAPACITY was CHANGED !" << endl;
		}

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorComparison(void)
{
	PrintLineSeparator();

	vector<int>													Vector1{5,4,8,9,23};
	vector<int>													Vector2{5,4,8,7,23};

	PrintCollection(L"VECTOR 1",Vector1);
	PrintCollection(L"VECTOR 2",Vector2);

	PrintLineSeparator();

	wcout << L"VECTOR1==VECTOR2 [" << ((Vector1==Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VECTOR1!=VECTOR2 [" << ((Vector1!=Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VECTOR1<VECTOR2 [" << ((Vector1<Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VECTOR1<=VECTOR2 [" << ((Vector1<=Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VECTOR1>=VECTOR2 [" << ((Vector1>=Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VECTOR1>VECTOR2 [" << ((Vector1>Vector2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorSize(void)
{
	PrintLineSeparator();

	vector<int>													Vector{5,4,8,9,23};

	PrintCollection(L"VECTOR",Vector);

	wcout << L"VECTOR - SIZE [" << Vector.size() << L"] !" << endl;
	wcout << L"VECTOR - MAX SIZE [" << Vector.max_size() << L"] !" << endl;
	wcout << L"VECTOR - EMPTY [" << Vector.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorMove(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector1{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		vector<CInt>											Vector2{CInt(11),CInt(12),CInt(13),CInt(14),CInt(15)};

		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// !!!!! NEVOLA sa MOVE OPERATOR, pretoze sa iba presunie iba POINTER na INTERNAL BUFFER.
		Vector2=std::move(Vector1);

		PrintLineSeparator();

		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorSwap(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector1{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		vector<CInt>											Vector2{CInt(11),CInt(12),CInt(13),CInt(14),CInt(15)};

		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// !!!!! METHOD swap() VYMIENA POINTER na INTERNAL DATA.
		// !!! Pre jednotlive ITEMS sa MOVE OPERATOR= NEVOLAJU.
		Vector1.swap(Vector2);

		PrintLineSeparator();

		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorAssign(void)
{
	PrintLineSeparator();

	{
		array<CInt,5>											Array{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		vector<CInt>											Vector;

		PrintCollection(L"ARRAY",Array);

		// !!! ITEMS z ARRAY sa ulozia do VECTOR pomocou METHOD assign(), ktora umoznuje kopirovat ITEMS z inych CONTAINERS.
		// !!! Pre kazdy ITEM sa vola COPY CONSTRUCTOR.
		Vector.assign(Array.cbegin(),Array.cend());

		PrintLineSeparator();

		PrintCollection(L"VECTOR",Vector);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorElementAccess(void)
{
	PrintLineSeparator();

	vector<int>													Vector{5,4,8,9,23};

	PrintCollection(L"VECTOR",Vector);

	Vector[1]=Vector[1]+5;
	Vector.at(2)=17;

	PrintCollection(L"VECTOR",Vector);

	try
	{
		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"VECTOR [20] VALUE [" << Vector.at(20) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintCollection(L"VECTOR",Vector);

	wcout << L"VECTOR FRONT [" << Vector.front() << L"] !" << endl;
	wcout << L"VECTOR BACK [" << Vector.back() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorIterators(void)
{
	PrintLineSeparator();

	vector<int>													Vector{5,4,8,9,23};

	wcout << L"VECTOR [";

	for(vector<int>::iterator Iterator=Vector.begin();Iterator!=Vector.end();Iterator++)
	{
		if (Iterator!=Vector.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"VECTOR [";

	// Pouzije sa CONST ITERATOR.
	for(vector<int>::const_iterator Iterator=Vector.cbegin();Iterator!=Vector.cend();Iterator++)
	{
		if (Iterator!=Vector.cbegin())
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
void TestVectorInsertEraseEmplace(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector1{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		vector<CInt>											Vector2{CInt(100),CInt(200)};

		PrintCollection(L"VECTOR 1",Vector1);
		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// Vlozi sa 1 ITEM.
		Vector1.insert(Vector1.begin()+2,CInt(10));

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// Vlozi sa 'N' ITEM.
		Vector1.insert(Vector1.begin()+4,Vector2.begin(),Vector2.end());

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// Odstrani sa 1 ITEM.
		Vector1.erase(Vector1.begin()+5);

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// Odstrani sa 'N' ITEM.
		// !!! ITEM na ktory sa odkazuje ITERATOR v 2. PARAMETRI sa NEODSTRANUJE. Cize v tomto pripade sa odstrania 2 ITEMS.
		Vector1.erase(Vector1.begin()+1,Vector1.begin()+3);

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// !!! Prida sa ITEM, pricom sa vola CONSTRUCTOR CLASS 'CInt'.
		// !!! 2. PARAMETER je PARAMETER CONSTRUCTOR CLASS 'CInt'.
		Vector1.emplace(Vector1.begin()+1,33);

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// Pridavanie ITEMS na koniec VECTOR je velmi efektivne.
		Vector1.push_back(CInt(55));

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// Odstranovanie ITEMS z konca VECTOR je velmi efektivne.
		Vector1.pop_back();

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVectorAsCArray(void)
{
	PrintLineSeparator();

	vector<wchar_t>												Vector{L'M',L'y',L' ',L'n',L'a',L'm',L'e',L' ',L'i',L's',L' ',L'T',L'i',L'm',L'm',L'y',L' ',L'A',L'n',L'd',L'e',L'r',L's',L'o',L'n',L'.',L'\0'};

	// !!! Pouzitie VECTOR ako C-ARRAY.
	wprintf(L"TEXT [%ls] !\n",Vector.data());

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
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListInitialization(void)
{
	PrintLineSeparator();

	list<int>													List1;

	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);

	PrintCollection(L"LIST 1",List1);

	// Pouzije sa COPY CONSTRUCTOR.
	list<int>													List2(List1);
	
	PrintCollection(L"LIST 2",List2);

	list<int>													List3;

	// Pouzije sa COPY OPERATOR=.
	List3=List1;

	PrintCollection(L"LIST 3",List3);

	PrintLineSeparator();

	// Pouzije sa MOVE OPERATOR=.
	List3=std::move(List2);

	PrintCollection(L"LIST 2",List2);
	PrintCollection(L"LIST 3",List3);

	PrintLineSeparator();

	{
		list<CInt>												List4;

		List4.push_back(1);
		List4.push_back(2);
		List4.push_back(3);

		PrintCollection(L"LIST 4",List4);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListComparison(void)
{
	PrintLineSeparator();

	list<int>													List1;

	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);

	list<int>													List2;

	List2.push_back(1);
	List2.push_back(-2);
	List2.push_back(3);

	list<int>													List3;

	List3.push_back(1);
	List3.push_back(2);
	List3.push_back(3);

	list<int>													List4;

	List4.push_back(1);
	List4.push_back(2);
	List4.push_back(3);
	List4.push_back(4);

	list<int>													List5;

	List5.push_back(1);
	List5.push_back(22);
	List5.push_back(3);

	list<int>													List6;

	List6.push_back(50);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	wcout << L"LIST 1 == LIST 2 [" << ((List1==List2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 != LIST 2 [" << ((List1!=List2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 < LIST 2 [" << ((List1<List2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 <= LIST 2 [" << ((List1<=List2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 >= LIST 2 [" << ((List1>=List2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 > LIST 2 [" << ((List1>List2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 3",List3);

	wcout << L"LIST 1 < LIST 3 [" << ((List1<List3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 <= LIST 3 [" << ((List1<=List3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 >= LIST 3 [" << ((List1>=List3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 > LIST 3 [" << ((List1>List3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 4",List4);

	wcout << L"LIST 1 < LIST 4 [" << ((List1<List4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 <= LIST 4 [" << ((List1<=List4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 >= LIST 4 [" << ((List1>=List4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 > LIST 4 [" << ((List1>List4) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 5",List5);

	wcout << L"LIST 1 < LIST 5 [" << ((List1<List5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 <= LIST 5 [" << ((List1<=List5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 >= LIST 5 [" << ((List1>=List5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 > LIST 5 [" << ((List1>List5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 6",List6);

	// !!! Vrati TRUE, pretoze aj ked LIST 6 obsahuje iba 1 ITEM, ten je vacsi ako kazdy ITEM v MAP1.
	wcout << L"LIST 1 < LIST 6 [" << ((List1<List6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 <= LIST 6 [" << ((List1<=List6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 >= LIST 6 [" << ((List1>=List6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"LIST 1 > LIST 6 [" << ((List1>List6) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListSize(void)
{
	PrintLineSeparator();

	list<int>													List;

	List.push_back(1);
	List.push_back(2);
	List.push_back(3);

	PrintCollection(L"LIST",List);

	wcout << L"LIST - MAX SIZE [" << List.max_size() << L"] !" << endl;
	wcout << L"LIST - SIZE [" << List.size() << L"] !" << endl;
	wcout << L"LIST - EMPTY [" << List.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListAssign(void)
{
	PrintLineSeparator();

	list<int>													List1;

	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);
	List1.push_back(4);
	List1.push_back(5);

	PrintCollection(L"LIST 1",List1);

	list<int>													List2(List1);

	PrintCollection(L"LIST 2",List2);

	list<int>													List3;

	List3=List1;

	PrintCollection(L"LIST 3",List3);

	list<int>													List4;
	
	List4.assign(List1.cbegin(),List1.cend());

	PrintCollection(L"LIST 4",List4);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListIterators(void)
{
	PrintLineSeparator();

	list<int>													List{5,4,8,9,23};

	// METHOD front() a METHOD back() je okrem iterovania jedinym sposobom ako sa dostat k ITEMS (iba 1. ITEM a POSLEDNEMU) v LIST.
	wcout << L"LIST - FRONT [" << List.front() << L"] !" << endl;
	wcout << L"LIST - BACK [" << List.back() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"LIST [";

	for(list<int>::iterator Iterator=List.begin();Iterator!=List.end();Iterator++)
	{
		if (Iterator!=List.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"LIST [";

	// Pouzije sa CONST ITERATOR.
	for(list<int>::const_iterator Iterator=List.cbegin();Iterator!=List.cend();Iterator++)
	{
		if (Iterator!=List.cbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"LIST [";

	// Pouzije sa CONST REVERSE ITERATOR.
	for(list<int>::const_reverse_iterator Iterator=List.crbegin();Iterator!=List.crend();Iterator++)
	{
		if (Iterator!=List.crbegin())
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
void TestListInsert(void)
{
	PrintLineSeparator();

	array<int,3>												Array{5,6,7};
	list<int>													List;
	list<int>::const_iterator									Iterator;

	List.push_back(10);
	List.push_back(20);
	List.push_back(30);
	List.push_back(40);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	Iterator=find(List.cbegin(),List.cend(),20);

	if (Iterator!=List.cend())
	{
		// !!! ITEM je pridany PRED ITEM '20'.
		List.insert(Iterator,100);

		PrintCollection(L"LIST",List);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	Iterator=find(List.cbegin(),List.cend(),30);

	if (Iterator!=List.cend())
	{
		// !!! ITEMS su pridane PREED ITEM '30'.
		List.insert(Iterator,Array.cbegin(),Array.cend());

		PrintCollection(L"LIST",List);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	// ITEM je pridany na zaciatok LIST.
	List.push_front(33);

	// ITEM je pridany na koniec LIST.
	List.push_back(333);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListEmplace(void)
{
	PrintLineSeparator();

	{
		list<CInt>												List;
		list<CInt>::const_iterator								Iterator;

		List.push_back(10);
		List.push_back(20);
		List.push_back(30);
		List.push_back(40);

		PrintCollection(L"LIST",List);

		PrintLineSeparator();

		Iterator=find(List.cbegin(),List.cend(),20);

		if (Iterator!=List.cend())
		{
			// !!! ITEM je pridany PRED ITEM '20'.
			// !!! Pouziva sa EMPLACE SYNTAX.
			List.emplace(Iterator,100);

			PrintCollection(L"LIST",List);
		}
		else
		{
			wcout << L"ITEM NOT FOUND !" << endl;
		}

		PrintLineSeparator();

		// ITEM je pridany na zaciatok LIST pomocou EMPLACE SYNTAX.
		List.emplace_front(33);

		// ITEM je pridany na koniec LIST pomocou EMPLACE SYNTAX.
		List.emplace_back(333);

		PrintCollection(L"LIST",List);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListErase(void)
{
	PrintLineSeparator();

	list<int>													List;
	list<int>::const_iterator									Iterator;

	List.push_back(10);
	List.push_back(20);
	List.push_back(30);
	List.push_back(40);
	List.push_back(50);
	List.push_back(60);
	List.push_back(70);
	List.push_back(80);
	List.push_back(90);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	Iterator=find(List.cbegin(),List.cend(),20);

	if (Iterator!=List.cend())
	{
		// !!!!! Odstrani sa ITEM '20'.
		List.erase(Iterator);

		PrintCollection(L"LIST",List);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	Iterator=find(List.cbegin(),List.cend(),50);

	if (Iterator!=List.cend())
	{
		list<int>::const_iterator								IteratorFirst=Iterator;
		list<int>::const_iterator								IteratorLast=Iterator;

		IteratorLast++;
		IteratorLast++;
		IteratorLast++;

		// !!!!! Odstrania sa 3 ITEMS, ktore sa nachadzaju od ITEM '50', teda ITEMS '50', '60' a '70'.
		List.erase(IteratorFirst,IteratorLast);

		PrintCollection(L"LIST",List);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	// Odstrani sa ITEM zo zaciatku LIST, teda ITEM '10'.
	List.pop_front();

	// Odstrani sa ITEM z konca LIST, teda ITEM '90'.
	List.pop_back();

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListRemove(void)
{
	PrintLineSeparator();

	list<int>													List;

	List.push_back(10);
	List.push_back(20);
	List.push_back(30);
	List.push_back(40);
	List.push_back(50);
	List.push_back(60);
	List.push_back(70);
	List.push_back(80);
	List.push_back(66);
	List.push_back(66);
	List.push_back(66);
	List.push_back(90);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// !!! Odstrani vsetky ITEMS s hodnotou '66'.
	List.remove(66);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// !!! Odstrani vsetky ITEMS s hodnotami v intervale <30,70>.
	List.remove_if([](int Value)->bool{return(Value>=30 && Value<=70);});

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListResize(void)
{
	PrintLineSeparator();

	list<int>													List;

	List.push_back(10);
	List.push_back(20);
	List.push_back(30);
	List.push_back(40);
	List.push_back(50);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// !!! Prida 2 nove ITEMS s hodnotou '888'.
	List.resize(7,888);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	// !!! Odstrani 3 ITEMS.
	List.resize(4,888);

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListSplice1(void)
{
	PrintLineSeparator();

	list<int>													List1({1,2,3,4,5});
	list<int>													List2({11,12,13,14,15});
	list<int>::const_iterator									Iterator1;
	list<int>::const_iterator									Iterator2;

	Iterator1=find(List1.cbegin(),List1.cend(),3);
	Iterator2=find(List2.cbegin(),List2.cend(),12);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	if (Iterator1!=List1.cend() && Iterator2!=List2.cend())
	{
		wcout << L"ITERATOR 1 [" << *Iterator1 << L"] !" << endl;
		wcout << L"ITERATOR 2 [" << *Iterator2 << L"] !" << endl;

		// !!! Do 'List1' PRED poziciu na ktoru ukazuje ITERATOR 'Iterator1' ('3') je pridany ITEM, ktory sa na pozicii na ktoru sa odkazuje ITERATOR 'Iterator2' ('12'). ITEMS prenesene z 'List2' su z 'List2' su odstranene.
		List1.splice(Iterator1,List2,Iterator2);

		PrintCollection(L"LIST 1",List1);
		PrintCollection(L"LIST 2",List2);
	}
	else
	{
		wcout << L"ITEMS NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListSplice2(void)
{
	PrintLineSeparator();

	list<int>													List1({1,2,3,4,5});
	list<int>													List2({11,12,13,14,15});
	list<int>::const_iterator									Iterator1;
	list<int>::const_iterator									Iterator2;
	list<int>::const_iterator									Iterator3;

	Iterator1=find(List1.cbegin(),List1.cend(),3);
	Iterator2=Iterator3=find(List2.cbegin(),List2.cend(),12);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	if (Iterator1!=List1.cend() && Iterator2!=List2.cend())
	{
		Iterator3++;
		Iterator3++;
		Iterator3++;

		wcout << L"ITERATOR 1 [" << *Iterator1 << L"] !" << endl;
		wcout << L"ITERATOR 2 [" << *Iterator2 << L"] !" << endl;
		wcout << L"ITERATOR 3 [" << *Iterator3 << L"] !" << endl;

		// !!! Do 'List1' PRED poziciu na ktoru ukazuje ITERATOR 'Iterator1' ('3') su pridane ITEMS, ktore sa nachadzaju od pozicie na ktoru odkazuje ITERATOR 'Iterator2' ('12') az po ITEM, na ktory odkazuje ITERATOR 'Iterator3' ('15'). ITEM na ktory odkazuje ITERATOR 'Iterator3' ('15') do 'List1' pridany nie je. ITEMS prenesene z 'List2' su z 'List2' su odstranene.
		List1.splice(Iterator1,List2,Iterator2,Iterator3);

		PrintCollection(L"LIST 1",List1);
		PrintCollection(L"LIST 2",List2);
	}
	else
	{
		wcout << L"ITEMS NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListSortAndMerge1(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,1,3});
	list<int>													List2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	List1.sort();
	List2.sort();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'List2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'List1'.
	List1.merge(List2);

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListSortAndMerge2(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,1,3});
	list<int>													List2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	List1.sort();
	List2.sort();

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'List2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'List1'.
	// 2. PARAMETER definuje CUSTOM COMPARER.
	List1.merge(List2,[](int Value1, int Value2)->bool{return(Value1<Value2);});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListUnique(void)
{
	PrintLineSeparator();

	list<int>													List1({2,5,4,4,4,1,4,3,3});
	list<int>													List2({2,5,4,4,4,1,4,3,3});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();

	// Odstrani kazdy vyskyt 2 za sebou identickych ITEMS.
	List1.unique();

	// Odstrani kazdy vyskyt 2 za sebou identickych ITEMS.
	// 2. PARAMETER definuje CUSTOM COMPARER.
	List2.unique([](int Value1, int Value2)->bool{return(Value1==Value2);});

	PrintCollection(L"LIST 1",List1);
	PrintCollection(L"LIST 2",List2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestListReverse(void)
{
	PrintLineSeparator();

	list<int>													List({2,5,4,1,3});

	PrintCollection(L"LIST",List);

	PrintLineSeparator();

	List.reverse();

	PrintCollection(L"LIST",List);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListInitialization(void)
{
	PrintLineSeparator();

	forward_list<int>												ForwardList1;
	forward_list<int>::const_iterator								Iterator1;

	Iterator1=ForwardList1.insert_after(ForwardList1.cbefore_begin(),1);
	Iterator1=ForwardList1.insert_after(Iterator1,2);
	ForwardList1.insert_after(Iterator1,3);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);

	// Pouzije sa COPY CONSTRUCTOR.
	forward_list<int>											ForwardList2(ForwardList1);
	
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	forward_list<int>											ForwardList3;

	// Pouzije sa COPY OPERATOR=.
	ForwardList3=ForwardList1;

	PrintCollection(L"FORWARD LIST 3",ForwardList3);

	PrintLineSeparator();

	// Pouzije sa MOVE OPERATOR=.
	ForwardList3=std::move(ForwardList2);

	PrintCollection(L"FORWARD LIST 2",ForwardList2);
	PrintCollection(L"FORWARD LIST 3",ForwardList3);

	PrintLineSeparator();

	{
		forward_list<CInt>										ForwardList4;
		forward_list<CInt>::const_iterator						Iterator2;

		Iterator2=ForwardList4.insert_after(ForwardList4.cbefore_begin(),1);
		Iterator2=ForwardList4.insert_after(Iterator2,2);
		ForwardList4.insert_after(Iterator2,3);

		PrintCollection(L"FORWARD LIST 4",ForwardList4);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListComparison(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1;
	forward_list<int>::const_iterator							Iterator;

	Iterator=ForwardList1.insert_after(ForwardList1.before_begin(),1);
	Iterator=ForwardList1.insert_after(Iterator,2);
	ForwardList1.insert_after(Iterator,3);

	forward_list<int>											ForwardList2;

	Iterator=ForwardList2.insert_after(ForwardList2.before_begin(),1);
	Iterator=ForwardList2.insert_after(Iterator,-2);
	ForwardList2.insert_after(Iterator,3);

	forward_list<int>											ForwardList3;

	Iterator=ForwardList3.insert_after(ForwardList3.before_begin(),1);
	Iterator=ForwardList3.insert_after(Iterator,2);
	ForwardList3.insert_after(Iterator,3);

	forward_list<int>											ForwardList4;

	Iterator=ForwardList4.insert_after(ForwardList4.before_begin(),1);
	Iterator=ForwardList4.insert_after(Iterator,2);
	Iterator=ForwardList4.insert_after(Iterator,3);
	ForwardList4.insert_after(Iterator,4);

	forward_list<int>											ForwardList5;

	Iterator=ForwardList5.insert_after(ForwardList5.before_begin(),1);
	Iterator=ForwardList5.insert_after(Iterator,22);
	ForwardList5.insert_after(Iterator,3);

	forward_list<int>											ForwardList6;

	ForwardList6.insert_after(ForwardList6.before_begin(),50);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	wcout << L"FORWARD LIST 1 == FORWARD LIST 2 [" << ((ForwardList1==ForwardList2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 != FORWARD LIST 2 [" << ((ForwardList1!=ForwardList2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 < FORWARD LIST 2 [" << ((ForwardList1<ForwardList2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 <= FORWARD LIST 2 [" << ((ForwardList1<=ForwardList2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 >= FORWARD LIST 2 [" << ((ForwardList1>=ForwardList2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 > FORWARD LIST 2 [" << ((ForwardList1>ForwardList2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 3",ForwardList3);

	wcout << L"FORWARD LIST 1 < FORWARD LIST 3 [" << ((ForwardList1<ForwardList3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 <= FORWARD LIST 3 [" << ((ForwardList1<=ForwardList3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 >= FORWARD LIST 3 [" << ((ForwardList1>=ForwardList3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 > FORWARD LIST 3 [" << ((ForwardList1>ForwardList3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 4",ForwardList4);

	wcout << L"FORWARD LIST 1 < FORWARD LIST 4 [" << ((ForwardList1<ForwardList4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 <= FORWARD LIST 4 [" << ((ForwardList1<=ForwardList4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 >= FORWARD LIST 4 [" << ((ForwardList1>=ForwardList4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 > FORWARD LIST 4 [" << ((ForwardList1>ForwardList4) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 5",ForwardList5);

	wcout << L"FORWARD LIST 1 < FORWARD LIST 5 [" << ((ForwardList1<ForwardList5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 <= FORWARD LIST 5 [" << ((ForwardList1<=ForwardList5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 >= FORWARD LIST 5 [" << ((ForwardList1>=ForwardList5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 > FORWARD LIST 5 [" << ((ForwardList1>ForwardList5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 6",ForwardList6);

	// !!! Vrati TRUE, pretoze aj ked FORWARD LIST 6 obsahuje iba 1 ITEM, ten je vacsi ako kazdy ITEM v MAP1.
	wcout << L"FORWARD LIST 1 < FORWARD LIST 6 [" << ((ForwardList1<ForwardList6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 <= FORWARD LIST 6 [" << ((ForwardList1<=ForwardList6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 >= FORWARD LIST 6 [" << ((ForwardList1>=ForwardList6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"FORWARD LIST 1 > FORWARD LIST 6 [" << ((ForwardList1>ForwardList6) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListMaxSize(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList;
	forward_list<int>::const_iterator							Iterator;

	Iterator=ForwardList.insert_after(ForwardList.cbefore_begin(),1);
	Iterator=ForwardList.insert_after(Iterator,2);
	ForwardList.insert_after(Iterator,3);

	PrintCollection(L"FORWARD LIST",ForwardList);

	wcout << L"FORWARD LIST - MAX SIZE [" << ForwardList.max_size() << L"] !" << endl;
	wcout << L"FORWARD LIST - EMPTY [" << ForwardList.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListAssign(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1;
	forward_list<int>::const_iterator							Iterator;

	Iterator=ForwardList1.insert_after(ForwardList1.before_begin(),1);
	Iterator=ForwardList1.insert_after(Iterator,2);
	Iterator=ForwardList1.insert_after(Iterator,3);
	Iterator=ForwardList1.insert_after(Iterator,4);
	ForwardList1.insert_after(Iterator,5);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);

	forward_list<int>											ForwardList2(ForwardList1);

	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	forward_list<int>											ForwardList3;

	ForwardList3=ForwardList1;

	PrintCollection(L"FORWARD LIST 3",ForwardList3);

	forward_list<int>											ForwardList4;
	
	ForwardList4.assign(ForwardList1.cbegin(),ForwardList1.cend());

	PrintCollection(L"FORWARD LIST 4",ForwardList4);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListIterators(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList{5,4,8,9,23};

	// METHOD front() je okrem iterovania jedinym sposobom ako sa dostat k ITEMS (iba 1. ITEM) vo FORWARD LIST.
	wcout << L"FORWARD LIST - FRONT [" << ForwardList.front() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"FORWARD LIST [";

	for(forward_list<int>::iterator Iterator=ForwardList.begin();Iterator!=ForwardList.end();Iterator++)
	{
		if (Iterator!=ForwardList.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"FORWARD LIST [";

	// Pouzije sa CONST ITERATOR.
	for(forward_list<int>::const_iterator Iterator=ForwardList.cbegin();Iterator!=ForwardList.cend();Iterator++)
	{
		if (Iterator!=ForwardList.cbegin())
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
void TestForwardListInsert(void)
{
	PrintLineSeparator();

	array<int,3>												Array{5,6,7};
	forward_list<int>											ForwardList;
	forward_list<int>::const_iterator							Iterator;

	Iterator=ForwardList.insert_after(ForwardList.before_begin(),10);
	Iterator=ForwardList.insert_after(Iterator,20);
	Iterator=ForwardList.insert_after(Iterator,30);
	ForwardList.insert_after(Iterator,40);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	Iterator=find(ForwardList.cbegin(),ForwardList.cend(),20);

	if (Iterator!=ForwardList.cend())
	{
		// !!! ITEM je pridany AZ ITEM '20'.
		ForwardList.insert_after(Iterator,100);

		PrintCollection(L"FORWARD LIST",ForwardList);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	Iterator=find(ForwardList.cbegin(),ForwardList.cend(),30);

	if (Iterator!=ForwardList.cend())
	{
		// !!! ITEMS su pridane AZ ITEM '30'.
		ForwardList.insert_after(Iterator,Array.cbegin(),Array.cend());

		PrintCollection(L"FORWARD LIST",ForwardList);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	// ITEM je pridany na zaciatok FORWARD LIST.
	ForwardList.push_front(33);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListEmplace(void)
{
	PrintLineSeparator();

	{
		forward_list<CInt>										ForwardList;
		forward_list<CInt>::const_iterator						Iterator;

		Iterator=ForwardList.insert_after(ForwardList.before_begin(),10);
		Iterator=ForwardList.insert_after(Iterator,20);
		Iterator=ForwardList.insert_after(Iterator,30);
		ForwardList.insert_after(Iterator,40);

		PrintCollection(L"FORWARD LIST",ForwardList);

		PrintLineSeparator();

		Iterator=find(ForwardList.cbegin(),ForwardList.cend(),20);

		if (Iterator!=ForwardList.cend())
		{
			// !!! ITEM je pridany AZ ITEM '20'.
			// !!! Pouziva sa EMPLACE SYNTAX.
			ForwardList.emplace_after(Iterator,100);

			PrintCollection(L"FORWARD LIST",ForwardList);
		}
		else
		{
			wcout << L"ITEM NOT FOUND !" << endl;
		}

		PrintLineSeparator();

		// ITEM je pridany na zaciatok FORWARD LIST pomocou EMPLACE SYNTAX.
		ForwardList.emplace_front(33);

		PrintCollection(L"FORWARD LIST",ForwardList);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListErase(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList;
	forward_list<int>::const_iterator							Iterator;

	Iterator=ForwardList.insert_after(ForwardList.before_begin(),10);
	Iterator=ForwardList.insert_after(Iterator,20);
	Iterator=ForwardList.insert_after(Iterator,30);
	Iterator=ForwardList.insert_after(Iterator,40);
	Iterator=ForwardList.insert_after(Iterator,50);
	Iterator=ForwardList.insert_after(Iterator,60);
	Iterator=ForwardList.insert_after(Iterator,70);
	Iterator=ForwardList.insert_after(Iterator,80);
	ForwardList.insert_after(Iterator,90);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	Iterator=find(ForwardList.cbegin(),ForwardList.cend(),20);

	if (Iterator!=ForwardList.cend())
	{
		// !!!!! Odstrani sa ITEM, ktory sa nachadza ZA ITEM '20', teda ITEM '30'.
		ForwardList.erase_after(Iterator);

		PrintCollection(L"FORWARD LIST",ForwardList);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	Iterator=find(ForwardList.cbegin(),ForwardList.cend(),50);

	if (Iterator!=ForwardList.cend())
	{
		forward_list<int>::const_iterator						IteratorFirst=Iterator;
		forward_list<int>::const_iterator						IteratorLast=Iterator;

		IteratorLast++;
		IteratorLast++;
		IteratorLast++;

		// !!!!! Odstrania sa 2 ITEMS, ktore sa nachadzaju ZA ITEM '50', teda ITEMS '60' a '70'.
		// !!!!! Namiesto 3 ITEMS sa odstranuju iba 2. To je specifikum FORWARD LIST.
		ForwardList.erase_after(IteratorFirst,IteratorLast);

		PrintCollection(L"FORWARD LIST",ForwardList);
	}
	else
	{
		wcout << L"ITEM NOT FOUND !" << endl;
	}

	PrintLineSeparator();

	// Odstrani sa ITEM zo zaciatku FORWARD LIST, teda ITEM '10'.
	ForwardList.pop_front();

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListRemove(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList;
	forward_list<int>::const_iterator							Iterator;

	Iterator=ForwardList.insert_after(ForwardList.before_begin(),10);
	Iterator=ForwardList.insert_after(Iterator,20);
	Iterator=ForwardList.insert_after(Iterator,30);
	Iterator=ForwardList.insert_after(Iterator,40);
	Iterator=ForwardList.insert_after(Iterator,50);
	Iterator=ForwardList.insert_after(Iterator,60);
	Iterator=ForwardList.insert_after(Iterator,70);
	Iterator=ForwardList.insert_after(Iterator,80);
	Iterator=ForwardList.insert_after(Iterator,66);
	Iterator=ForwardList.insert_after(Iterator,66);
	Iterator=ForwardList.insert_after(Iterator,66);
	ForwardList.insert_after(Iterator,90);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	// !!! Odstrani vsetky ITEMS s hodnotou '66'.
	ForwardList.remove(66);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	// !!! Odstrani vsetky ITEMS s hodnotami v intervale <30,70>.
	ForwardList.remove_if([](int Value)->bool{return(Value>=30 && Value<=70);});

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListResize(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList;
	forward_list<int>::const_iterator							Iterator;

	Iterator=ForwardList.insert_after(ForwardList.before_begin(),10);
	Iterator=ForwardList.insert_after(Iterator,20);
	Iterator=ForwardList.insert_after(Iterator,30);
	Iterator=ForwardList.insert_after(Iterator,40);
	ForwardList.insert_after(Iterator,50);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	// !!! Prida 2 nove ITEMS s hodnotou '888'.
	ForwardList.resize(7,888);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	// !!! Odstrani 3 ITEMS.
	ForwardList.resize(4,888);

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListSplice1(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({1,2,3,4,5});
	forward_list<int>											ForwardList2({11,12,13,14,15});
	forward_list<int>::const_iterator							Iterator1;
	forward_list<int>::const_iterator							Iterator2;

	Iterator1=find(ForwardList1.cbegin(),ForwardList1.cend(),3);
	Iterator2=find(ForwardList2.cbegin(),ForwardList2.cend(),12);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	if (Iterator1!=ForwardList1.cend() && Iterator2!=ForwardList2.cend())
	{
		wcout << L"ITERATOR 1 [" << *Iterator1 << L"] !" << endl;
		wcout << L"ITERATOR 2 [" << *Iterator2 << L"] !" << endl;

		// !!! Do 'ForwardList1' ZA poziciu na ktoru ukazuje ITERATOR 'Iterator1' ('3') je pridany ITEM, ktory sa nachadza ZA ITEM na ktory odkazuje ITERATOR 'Iterator2' ('12'). ITEMS prenesene z 'ForwardList2' su z 'ForwardList2' su odstranene.
		ForwardList1.splice_after(Iterator1,ForwardList2,Iterator2);

		PrintCollection(L"FORWARD LIST 1",ForwardList1);
		PrintCollection(L"FORWARD LIST 2",ForwardList2);
	}
	else
	{
		wcout << L"ITEMS NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListSplice2(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({1,2,3,4,5});
	forward_list<int>											ForwardList2({11,12,13,14,15});
	forward_list<int>::const_iterator							Iterator1;
	forward_list<int>::const_iterator							Iterator2;
	forward_list<int>::const_iterator							Iterator3;

	Iterator1=find(ForwardList1.cbegin(),ForwardList1.cend(),3);
	Iterator2=Iterator3=find(ForwardList2.cbegin(),ForwardList2.cend(),12);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	if (Iterator1!=ForwardList1.cend() && Iterator2!=ForwardList2.cend())
	{
		Iterator3++;
		Iterator3++;
		Iterator3++;

		wcout << L"ITERATOR 1 [" << *Iterator1 << L"] !" << endl;
		wcout << L"ITERATOR 2 [" << *Iterator2 << L"] !" << endl;
		wcout << L"ITERATOR 3 [" << *Iterator3 << L"] !" << endl;

		// !!! Do 'ForwardList1' ZA poziciu na ktoru ukazuje ITERATOR 'Iterator1' ('3') su pridane ITEMS, ktore sa nachadzaju ZA ITEM na ktory odkazuje ITERATOR 'Iterator2' ('12') az po ITEM, na ktory odkazuje ITERATOR 'Iterator3' ('15'). ITEM na ktory odkazuje ITERATOR 'Iterator3' ('15') do 'ForwardList1' pridany nie je. ITEMS prenesene z 'ForwardList2' su z 'ForwardList2' su odstranene.
		ForwardList1.splice_after(Iterator1,ForwardList2,Iterator2,Iterator3);

		PrintCollection(L"FORWARD LIST 1",ForwardList1);
		PrintCollection(L"FORWARD LIST 2",ForwardList2);
	}
	else
	{
		wcout << L"ITEMS NOT FOUND !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListSortAndMerge1(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({2,5,4,1,3});
	forward_list<int>											ForwardList2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	ForwardList1.sort();
	ForwardList2.sort();

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE FORWARD LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'ForwardList2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'ForwardList1'.
	ForwardList1.merge(ForwardList2);

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListSortAndMerge2(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({2,5,4,1,3});
	forward_list<int>											ForwardList2({2,33,15,11,14,13,12,1,44});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	ForwardList1.sort();
	ForwardList2.sort();

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	// !!! Pred pouzitim METHOD merge() MUSIA byt OBE FORWARD LIST SORTED.
	// !!! Po skonceni volania METHOD merge() bude 'ForwardList2' PRAZDNY, pretoze sa vsetky ITEMS presunu do 'ForwardList1'.
	// 2. PARAMETER definuje CUSTOM COMPARER.
	ForwardList1.merge(ForwardList2,[](int Value1, int Value2)->bool{return(Value1<Value2);});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListUnique(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList1({2,5,4,4,4,1,4,3,3});
	forward_list<int>											ForwardList2({2,5,4,4,4,1,4,3,3});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();

	// Odstrani kazdy vyskyt 2 za sebou identickych ITEMS.
	ForwardList1.unique();

	// Odstrani kazdy vyskyt 2 za sebou identickych ITEMS.
	// 2. PARAMETER definuje CUSTOM COMPARER.
	ForwardList2.unique([](int Value1, int Value2)->bool{return(Value1==Value2);});

	PrintCollection(L"FORWARD LIST 1",ForwardList1);
	PrintCollection(L"FORWARD LIST 2",ForwardList2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardListReverse(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList({2,5,4,1,3});

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();

	ForwardList.reverse();

	PrintCollection(L"FORWARD LIST",ForwardList);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetInitialization(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);

	PrintCollection(L"SET 1",Set1);

	// Pouzije sa COPY CONSTRUCTOR.
	set<int>													Set2(Set1);
	
	PrintCollection(L"SET 2",Set2);

	set<int>													Set3;

	// Pouzije sa COPY OPERATOR=.
	Set3=Set1;

	PrintCollection(L"SET 3",Set3);

	PrintLineSeparator();

	// Pouzije sa MOVE OPERATOR=.
	Set3=std::move(Set2);

	PrintCollection(L"SET 2",Set2);
	PrintCollection(L"SET 3",Set3);

	PrintLineSeparator();

	// !!! COMPARER sa vytvara zavolanim DEFAULT CONSTRUCTOR daneho COMPARER.
	set<int,greater<int>>										Set4;

	Set4.insert(1);
	Set4.insert(2);
	Set4.insert(3);

	PrintCollection(L"SET 4",Set4);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(true);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	set<int,CCustomComparer>									Set5(CustomComparer1);

	Set5.insert(1);
	Set5.insert(2);
	Set5.insert(3);

	PrintCollection(L"SET 5",Set5);

	CCustomComparer												CustomComparer2(false);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	set<int,CCustomComparer>									Set6(CustomComparer2);

	Set6.insert(1);
	Set6.insert(2);
	Set6.insert(3);

	PrintCollection(L"SET 6",Set6);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetInitialization(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet1;

	MultiSet1.insert(1);
	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(3);

	PrintCollection(L"MULTISET 1",MultiSet1);

	// Pouzije sa COPY CONSTRUCTOR.
	multiset<int>												MultiSet2(MultiSet1);
	
	PrintCollection(L"MULTISET 2",MultiSet2);

	multiset<int>												MultiSet3;

	// Pouzije sa COPY OPERATOR=.
	MultiSet3=MultiSet1;

	PrintCollection(L"MULTISET 3",MultiSet3);

	PrintLineSeparator();

	// Pouzije sa MOVE OPERATOR=.
	MultiSet3=std::move(MultiSet2);

	PrintCollection(L"MULTISET 2",MultiSet2);
	PrintCollection(L"MULTISET 3",MultiSet3);

	PrintLineSeparator();

	// !!! COMPARER sa vytvara zavolanim DEFAULT CONSTRUCTOR daneho COMPARER.
	multiset<int,greater<int>>									MultiSet4;

	MultiSet4.insert(1);
	MultiSet4.insert(1);
	MultiSet4.insert(2);
	MultiSet4.insert(2);
	MultiSet4.insert(3);
	MultiSet4.insert(3);

	PrintCollection(L"MULTISET 4",MultiSet4);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(true);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	multiset<int,CCustomComparer>								MultiSet5(CustomComparer1);

	MultiSet5.insert(1);
	MultiSet5.insert(1);
	MultiSet5.insert(2);
	MultiSet5.insert(2);
	MultiSet5.insert(3);
	MultiSet5.insert(3);

	PrintCollection(L"MULTISET 5",MultiSet5);

	CCustomComparer												CustomComparer2(false);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	multiset<int,CCustomComparer>								MultiSet6(CustomComparer2);

	MultiSet6.insert(1);
	MultiSet6.insert(1);
	MultiSet6.insert(2);
	MultiSet6.insert(2);
	MultiSet6.insert(3);
	MultiSet6.insert(3);

	PrintCollection(L"MULTISET 6",MultiSet6);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetComparison(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);

	set<int>													Set2;

	Set2.insert(1);
	Set2.insert(-2);
	Set2.insert(3);

	set<int>													Set3;

	Set3.insert(1);
	Set3.insert(2);
	Set3.insert(3);

	set<int>													Set4;

	Set4.insert(1);
	Set4.insert(2);
	Set4.insert(3);
	Set4.insert(4);

	set<int>													Set5;

	Set5.insert(1);
	Set5.insert(22);
	Set5.insert(3);

	set<int>													Set6;

	Set6.insert(50);

	PrintCollection(L"SET 1",Set1);
	PrintCollection(L"SET 2",Set2);

	wcout << L"SET1==SET2 [" << ((Set1==Set2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1!=SET2 [" << ((Set1!=Set2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1<SET2 [" << ((Set1<Set2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1<=SET2 [" << ((Set1<=Set2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>=SET2 [" << ((Set1>=Set2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>SET2 [" << ((Set1>Set2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"SET 1",Set1);
	PrintCollection(L"SET 3",Set3);

	wcout << L"SET1<SET3 [" << ((Set1<Set3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1<=SET3 [" << ((Set1<=Set3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>=SET3 [" << ((Set1>=Set3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>SET3 [" << ((Set1>Set3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"SET 1",Set1);
	PrintCollection(L"SET 4",Set4);

	wcout << L"SET1<SET4 [" << ((Set1<Set4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1<=SET4 [" << ((Set1<=Set4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>=SET4 [" << ((Set1>=Set4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>SET4 [" << ((Set1>Set4) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"SET 1",Set1);
	PrintCollection(L"SET 5",Set5);

	wcout << L"SET1<SET5 [" << ((Set1<Set5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1<=SET5 [" << ((Set1<=Set5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>=SET5 [" << ((Set1>=Set5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>SET5 [" << ((Set1>Set5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"SET 1",Set1);
	PrintCollection(L"SET 6",Set6);

	// !!! Vrati TRUE, pretoze aj ked SET6 obsahuje iba 1 ITEM, ten je vacsi ako kazdy ITEM v MAP1.
	wcout << L"SET1<SET6 [" << ((Set1<Set6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1<=SET6 [" << ((Set1<=Set6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>=SET6 [" << ((Set1>=Set6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"SET1>SET6 [" << ((Set1>Set6) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetComparison(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet1;

	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(3);

	multiset<int>												MultiSet2;

	MultiSet2.insert(1);
	MultiSet2.insert(-2);
	MultiSet2.insert(3);

	multiset<int>												MultiSet3;

	MultiSet3.insert(1);
	MultiSet3.insert(2);
	MultiSet3.insert(3);

	multiset<int>												MultiSet4;

	MultiSet4.insert(1);
	MultiSet4.insert(2);
	MultiSet4.insert(3);
	MultiSet4.insert(4);

	multiset<int>												MultiSet5;

	MultiSet5.insert(1);
	MultiSet5.insert(22);
	MultiSet5.insert(3);

	multiset<int>												MultiSet6;

	MultiSet6.insert(1);
	MultiSet6.insert(2);
	MultiSet6.insert(2);
	MultiSet6.insert(3);

	multiset<int>												MultiSet7;

	MultiSet7.insert(1);
	MultiSet7.insert(2);
	MultiSet7.insert(2);
	MultiSet7.insert(3);

	multiset<int>												MultiSet8;

	MultiSet8.insert(1);
	MultiSet8.insert(2);
	MultiSet8.insert(2);

	multiset<int>												MultiSet9;

	MultiSet9.insert(50);

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 2",MultiSet2);

	wcout << L"MULTISET1==MULTISET2 [" << ((MultiSet1==MultiSet2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1!=MULTISET2 [" << ((MultiSet1!=MultiSet2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<MULTISET2 [" << ((MultiSet1<MultiSet2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET2 [" << ((MultiSet1<=MultiSet2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET2 [" << ((MultiSet1>=MultiSet2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET2 [" << ((MultiSet1>MultiSet2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 3",MultiSet3);

	wcout << L"MULTISET1<MULTISET3 [" << ((MultiSet1<MultiSet3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET3 [" << ((MultiSet1<=MultiSet3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET3 [" << ((MultiSet1>=MultiSet3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET3 [" << ((MultiSet1>MultiSet3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 4",MultiSet4);

	wcout << L"MULTISET1<MULTISET4 [" << ((MultiSet1<MultiSet4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET4 [" << ((MultiSet1<=MultiSet4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET4 [" << ((MultiSet1>=MultiSet4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET4 [" << ((MultiSet1>MultiSet4) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 5",MultiSet5);

	wcout << L"MULTISET1<MULTISET5 [" << ((MultiSet1<MultiSet5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET5 [" << ((MultiSet1<=MultiSet5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET5 [" << ((MultiSet1>=MultiSet5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET5 [" << ((MultiSet1>MultiSet5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 6",MultiSet6);

	wcout << L"MULTISET1<MULTISET6 [" << ((MultiSet1<MultiSet6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET6 [" << ((MultiSet1<=MultiSet6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET6 [" << ((MultiSet1>=MultiSet6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET6 [" << ((MultiSet1>MultiSet6) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 7",MultiSet7);

	wcout << L"MULTISET1<MULTISET7 [" << ((MultiSet1<MultiSet7) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET7 [" << ((MultiSet1<=MultiSet7) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET7 [" << ((MultiSet1>=MultiSet7) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET7 [" << ((MultiSet1>MultiSet7) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 8",MultiSet8);

	wcout << L"MULTISET1<MULTISET8 [" << ((MultiSet1<MultiSet8) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET8 [" << ((MultiSet1<=MultiSet8) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET8 [" << ((MultiSet1>=MultiSet8) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET8 [" << ((MultiSet1>MultiSet8) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 9",MultiSet9);

	// !!! Vrati TRUE, pretoze aj ked MULTISET9 obsahuje iba 1 ITEM, ten je vacsi ako kazdy ITEM v MULTIMAP1.
	wcout << L"MULTISET1<MULTISET9 [" << ((MultiSet1<MultiSet9) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1<=MULTISET9 [" << ((MultiSet1<=MultiSet9) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>=MULTISET9 [" << ((MultiSet1>=MultiSet9) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTISET1>MULTISET9 [" << ((MultiSet1>MultiSet9) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetSize(void)
{
	PrintLineSeparator();

	set<int>													Set;

	Set.insert(1);
	Set.insert(2);
	Set.insert(3);

	PrintSet(L"SET",Set);

	wcout << L"SET - SIZE [" << Set.size() << L"] !" << endl;
	wcout << L"SET - MAX SIZE [" << Set.max_size() << L"] !" << endl;
	wcout << L"SET - EMPTY [" << Set.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetSize(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet;

	MultiSet.insert(3);
	MultiSet.insert(3);
	MultiSet.insert(1);
	MultiSet.insert(1);
	MultiSet.insert(2);
	MultiSet.insert(2);

	PrintMultiSet(L"MULTISET",MultiSet);

	wcout << L"MULTISET - SIZE [" << MultiSet.size() << L"] !" << endl;
	wcout << L"MULTISET - MAX SIZE [" << MultiSet.max_size() << L"] !" << endl;
	wcout << L"MULTISET - EMPTY [" << MultiSet.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetFind(void)
{
	PrintLineSeparator();

	set<int>													Set;

	Set.insert(11);
	Set.insert(12);
	Set.insert(13);
	Set.insert(14);
	Set.insert(15);

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	wcout << L"SET - COUNT(11) - [" << Set.count(11) << L"] !" << endl;
	wcout << L"SET - COUNT(18) - [" << Set.count(18) << L"] !" << endl;
	
	PrintLineSeparator();

	PrintSetIterator(L"SET - FIND(-1) -",Set,Set.find(-1));
	PrintSetIterator(L"SET - FIND(13) -",Set,Set.find(13));
	PrintSetIterator(L"SET - FIND(16) -",Set,Set.find(16));
	
	PrintLineSeparator();

	PrintSetIterator(L"SET - LOWER_BOUND(-1) -",Set,Set.lower_bound(-1));
	PrintSetIterator(L"SET - LOWER_BOUND(13) -",Set,Set.lower_bound(13));
	PrintSetIterator(L"SET - LOWER_BOUND(16) -",Set,Set.lower_bound(16));
	
	PrintLineSeparator();

	PrintSetIterator(L"SET - UPPER_BOUND(-1) -",Set,Set.upper_bound(-1));
	PrintSetIterator(L"SET - UPPER_BOUND(13) -",Set,Set.upper_bound(13));
	PrintSetIterator(L"SET - UPPER_BOUND(16) -",Set,Set.upper_bound(16));

	PrintLineSeparator();

	using														SetIteratorPair=pair<set<int>::const_iterator,set<int>::const_iterator>;

	SetIteratorPair												IteratorPair1=Set.equal_range(-1);
	SetIteratorPair												IteratorPair2=Set.equal_range(13);
	SetIteratorPair												IteratorPair3=Set.equal_range(16);

	PrintSetIterator(L"SET - EQUAL_BOUND(-1).FIRST -",Set,IteratorPair1.first);
	PrintSetIterator(L"SET - EQUAL_BOUND(-1).SECOND -",Set,IteratorPair1.second);
	PrintSetIterator(L"SET - EQUAL_BOUND(13).FIRST -",Set,IteratorPair2.first);
	PrintSetIterator(L"SET - EQUAL_BOUND(13).SECOND -",Set,IteratorPair2.second);
	PrintSetIterator(L"SET - EQUAL_BOUND(16).FIRST -",Set,IteratorPair3.first);
	PrintSetIterator(L"SET - EQUAL_BOUND(16).SECOND -",Set,IteratorPair3.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetFind(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet;

	MultiSet.insert(11);
	MultiSet.insert(11);
	MultiSet.insert(12);
	MultiSet.insert(12);
	MultiSet.insert(13);
	MultiSet.insert(13);
	MultiSet.insert(14);
	MultiSet.insert(14);
	MultiSet.insert(15);
	MultiSet.insert(15);

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	wcout << L"MULTISET - COUNT(11) - [" << MultiSet.count(11) << L"] !" << endl;
	wcout << L"MULTISET - COUNT(18) - [" << MultiSet.count(18) << L"] !" << endl;
	
	PrintLineSeparator();

	PrintMultiSetIterator(L"MULTISET - FIND(-1) -",MultiSet,MultiSet.find(-1));
	PrintMultiSetIterator(L"MULTISET - FIND(13) -",MultiSet,MultiSet.find(13));
	PrintMultiSetIterator(L"MULTISET - FIND(16) -",MultiSet,MultiSet.find(16));
	
	PrintLineSeparator();

	PrintMultiSetIterator(L"MULTISET - LOWER_BOUND(-1) -",MultiSet,MultiSet.lower_bound(-1));
	PrintMultiSetIterator(L"MULTISET - LOWER_BOUND(13) -",MultiSet,MultiSet.lower_bound(13));
	PrintMultiSetIterator(L"MULTISET - LOWER_BOUND(16) -",MultiSet,MultiSet.lower_bound(16));
	
	PrintLineSeparator();

	PrintMultiSetIterator(L"MULTISET - UPPER_BOUND(-1) -",MultiSet,MultiSet.upper_bound(-1));
	PrintMultiSetIterator(L"MULTISET - UPPER_BOUND(13) -",MultiSet,MultiSet.upper_bound(13));
	PrintMultiSetIterator(L"MULTISET - UPPER_BOUND(16) -",MultiSet,MultiSet.upper_bound(16));

	PrintLineSeparator();

	using														MultiSetIteratorPair=pair<multiset<int>::const_iterator,multiset<int>::const_iterator>;

	MultiSetIteratorPair										IteratorPair1=MultiSet.equal_range(-1);
	MultiSetIteratorPair										IteratorPair2=MultiSet.equal_range(13);
	MultiSetIteratorPair										IteratorPair3=MultiSet.equal_range(16);

	PrintMultiSetIterator(L"MULTISET - EQUAL_BOUND(-1).FIRST -",MultiSet,IteratorPair1.first);
	PrintMultiSetIterator(L"MULTISET - EQUAL_BOUND(-1).SECOND -",MultiSet,IteratorPair1.second);
	PrintMultiSetIterator(L"MULTISET - EQUAL_BOUND(13).FIRST -",MultiSet,IteratorPair2.first);
	PrintMultiSetIterator(L"MULTISET - EQUAL_BOUND(13).SECOND -",MultiSet,IteratorPair2.second);
	PrintMultiSetIterator(L"MULTISET - EQUAL_BOUND(16).FIRST -",MultiSet,IteratorPair3.first);
	PrintMultiSetIterator(L"MULTISET - EQUAL_BOUND(16).SECOND -",MultiSet,IteratorPair3.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetAssign(void)
{
	PrintLineSeparator();

	set<int>													Set1;

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);
	Set1.insert(5);

	PrintSet(L"SET 1",Set1);

	set<int>													Set2(Set1);

	PrintSet(L"SET 2",Set2);

	set<int>													Set3;

	Set3=Set1;

	PrintSet(L"SET 3",Set3);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(false);
	CCustomComparer												CustomComparer2(true);

	// !!! Obe SETS maju ten isty TYPE, ale INY COMPARER s INYMI SEARCH CRITERIA.
	set<int,CCustomComparer>									Set4(CustomComparer1);
	set<int,CCustomComparer>									Set5(CustomComparer2);

	Set4.insert(5);
	Set4.insert(6);
	Set4.insert(7);

	// !!! ITEMS su SORTED podla POVODNEHO COMPARER.
	Set5.insert(15);
	Set5.insert(16);
	Set5.insert(17);

	PrintSet(L"SET 4",Set4);
	PrintSet(L"SET 5",Set5);

	PrintLineSeparator();

	// !!! SET UMOZNUJE priradzovat jednu instanciu SET ak maju ROVANKY COMPARER TYPE, ale zaroven kazda instancia SET pouziva INU INSTANCIU COMPARER s INYMI SEARCH CRITERIA.
	// !!!!! Kedze pri priradzovani sa prenasa aj COMPARER, ITEMS v 'Set5' vsak budu SORTED podla COMPARER z 'Set4'.
	Set5=Set4;

	PrintSet(L"SET 5",Set5);

	PrintLineSeparator();

	// Kedze pri priradeni sa PRENIESOL aj COMPARER, dalsie ITEMS uz su ORDERED podla NOVEHO COMPARER, ktory bol preneseny z 'Set4'.
	Set5.insert(1);
	Set5.insert(20);

	PrintSet(L"SET 5",Set5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetAssign(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet1;

	MultiSet1.insert(1);
	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(3);
	MultiSet1.insert(4);
	MultiSet1.insert(4);
	MultiSet1.insert(5);
	MultiSet1.insert(5);

	PrintMultiSet(L"MULTISET 1",MultiSet1);

	multiset<int>												MultiSet2(MultiSet1);

	PrintMultiSet(L"MULTISET 2",MultiSet2);

	multiset<int>												MultiSet3;

	MultiSet3=MultiSet1;

	PrintMultiSet(L"MULTISET 3",MultiSet3);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(false);
	CCustomComparer												CustomComparer2(true);

	// !!! Obe SETS maju ten isty TYPE, ale INY COMPARER s INYMI SEARCH CRITERIA.
	multiset<int,CCustomComparer>								MultiSet4(CustomComparer1);
	multiset<int,CCustomComparer>								MultiSet5(CustomComparer2);

	MultiSet4.insert(5);
	MultiSet4.insert(5);
	MultiSet4.insert(6);
	MultiSet4.insert(6);
	MultiSet4.insert(7);
	MultiSet4.insert(6);

	// !!! ITEMS su SORTED podla POVODNEHO COMPARER.
	MultiSet5.insert(15);
	MultiSet5.insert(15);
	MultiSet5.insert(16);
	MultiSet5.insert(16);
	MultiSet5.insert(17);
	MultiSet5.insert(17);

	PrintMultiSet(L"MULTISET 4",MultiSet4);
	PrintMultiSet(L"MULTISET 5",MultiSet5);

	PrintLineSeparator();

	// !!! SET UMOZNUJE priradzovat jednu instanciu MULTISET ak maju ROVANKY COMPARER TYPE, ale zaroven kazda instancia MULTISET pouziva INU INSTANCIU COMPARER s INYMI SEARCH CRITERIA.
	// !!!!! Kedze pri priradzovani sa prenasa aj COMPARER, ITEMS v 'MultiSet5' vsak budu SORTED podla COMPARER z 'MultiSet4'.
	MultiSet5=MultiSet4;

	PrintMultiSet(L"MULTISET 5",MultiSet5);

	PrintLineSeparator();

	// Kedze pri priradeni sa PRENIESOL aj COMPARER, dalsie ITEMS uz su ORDERED podla NOVEHO COMPARER, ktory bol preneseny z 'MultiSet4'.
	MultiSet5.insert(1);
	MultiSet5.insert(1);
	MultiSet5.insert(20);
	MultiSet5.insert(20);

	PrintMultiSet(L"MULTISET 5",MultiSet5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetIterators(void)
{
	PrintLineSeparator();

	set<int>													Set;

	Set.insert(1);
	Set.insert(2);
	Set.insert(3);
	Set.insert(4);
	Set.insert(5);

	wcout << L"SET [";

	for(set<int>::iterator Iterator=Set.begin();Iterator!=Set.end();Iterator++)
	{
		if (Iterator!=Set.cbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"SET [";

	bool														IsFirst=true;

	// Pouzije sa C++ 11 ITERATION.
	for(const set<int>::value_type& Value : Set)
	{
		if (IsFirst==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst=false;
		}

		wcout << Value;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetIterators(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet;

	MultiSet.insert(1);
	MultiSet.insert(1);
	MultiSet.insert(2);
	MultiSet.insert(2);
	MultiSet.insert(3);
	MultiSet.insert(3);
	MultiSet.insert(4);
	MultiSet.insert(4);
	MultiSet.insert(5);
	MultiSet.insert(5);

	wcout << L"MULTISET [";

	for(multiset<int>::iterator Iterator=MultiSet.begin();Iterator!=MultiSet.end();Iterator++)
	{
		if (Iterator!=MultiSet.cbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"MULTISET [";

	bool														IsFirst=true;

	// Pouzije sa C++ 11 ITERATION.
	for(const multiset<int>::value_type& Value : MultiSet)
	{
		if (IsFirst==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst=false;
		}

		wcout << Value;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetInsert(void)
{
	PrintLineSeparator();

	set<int>													Set;

	Set.insert(1);

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM uz v SET NACHADZA.
	pair<set<int>::iterator,bool>								Result1=Set.insert(set<int>::value_type(2));

	if (Result1.second==true)
	{
		wcout << L"ITEM (" << *(Result1.first) << L") was ADDED to SET !" << endl;
	}
	else
	{
		wcout << L"ITEM (2,22) was NOT ADDED to SET !" << endl;
	}

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM uz v SET NACHADZA.
	pair<set<int>::iterator,bool>								Result2=Set.insert(set<int>::value_type(2));

	// !!!!! Kedze ITEM s VALUE '2' uz v SET EXISTUJE, tak volanie METHOD insert() ZLYHA.
	if (Result2.second==true)
	{
		wcout << L"ITEM (" << *(Result2.first) << L") was ADDED to SET !" << endl;
	}
	else
	{
		wcout << L"ITEM (2) was NOT ADDED to SET !" << endl;
	}

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	array<set<int>::value_type,2>								Array1{set<int>::value_type(3),set<int>::value_type(4)};
	array<set<int>::value_type,3>								Array2{set<int>::value_type(3),set<int>::value_type(4),set<int>::value_type(5)};

	// Vklada sa naraz viacero ITEMS.
	// !!! Existujuce ITEMS sa PREPISU na nove VALUES.
	Set.insert(Array1.begin(),Array1.end());

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	// Vklada sa naraz viacero ITEMS.
	Set.insert(Array2.begin(),Array2.end());

	PrintSet(L"SET",Set);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetInsert(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet{multiset<int>::value_type(1)};

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
	multiset<int>::iterator										Result1=MultiSet.insert(multiset<int>::value_type(2));

	wcout << L"ITEM (" << *Result1 << L") was ADDED to SET !" << endl;

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM.
	multiset<int>::iterator										Result2=MultiSet.insert(multiset<int>::value_type(2));

	// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
	wcout << L"ITEM (" << *Result2 << L") was ADDED to SET !" << endl;

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	array<set<int>::value_type,2>								Array1{set<int>::value_type(3),set<int>::value_type(4)};
	array<set<int>::value_type,3>								Array2{set<int>::value_type(3),set<int>::value_type(4),set<int>::value_type(5)};

	// Vklada sa naraz viacero ITEMS.
	MultiSet.insert(Array1.begin(),Array1.end());

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	// Vklada sa naraz viacero ITEMS.
	// !!! Pridaju sa aj ITEMS s EXISTUJUCIMI VALUES, pretoze sa jedna o MULTISET.
	MultiSet.insert(Array2.begin(),Array2.end());

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetEmplace(void)
{
	PrintLineSeparator();

	{
		set<CInt>												Set;

		Set.insert(CInt(11));

		PrintSet(L"SET",Set);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM uz v SET NACHADZA.
		pair<set<CInt>::iterator,bool>							Result1=Set.emplace(set<CInt>::value_type(2));

		if (Result1.second==true)
		{
			wcout << L"ITEM (" << *(Result1.first) << L") was ADDED to SET !" << endl;
		}
		else
		{
			wcout << L"ITEM (2) was NOT ADDED to SET !" << endl;
		}

		PrintSet(L"SET",Set);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM s danym KEY uz v SET NACHADZA.
		pair<set<CInt>::iterator,bool>							Result2=Set.emplace(set<CInt>::value_type(2));

		// !!!!! Kedze ITEM s KEY '2' uz v SET EXISTUJE, tak volanie METHOD insert() ZLYHA.
		if (Result2.second==true)
		{
			wcout << L"ITEM (" << *(Result2.first) << L") was ADDED to SET !" << endl;
		}
		else
		{
			wcout << L"ITEM (2) was NOT ADDED to SET !" << endl;
		}

		PrintSet(L"SET",Set);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetEmplace(void)
{
	PrintLineSeparator();

	{
		multiset<CInt>											MultiSet{multiset<CInt>::value_type(1)};

		PrintMultiSet(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
		multiset<CInt>::iterator								Result1=MultiSet.emplace(multiset<CInt>::value_type(2));

		wcout << L"ITEM (" << *Result1 << L") was ADDED to MULTISET !" << endl;

		PrintMultiSet(L"MULTISET",MultiSet);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM.
		multiset<CInt>::iterator								Result2=MultiSet.emplace(multiset<CInt>::value_type(2));

		// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
		wcout << L"ITEM (" << *Result2 << L") was ADDED to MULTISET !" << endl;

		PrintMultiSet(L"MULTISET",MultiSet);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetErase(void)
{
	PrintLineSeparator();

	set<int>													Set;

	Set.insert(1);
	Set.insert(2);
	Set.insert(3);
	Set.insert(4);
	Set.insert(5);

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	// Odstrani 2 ITEMS.
	Set.erase(Set.cbegin(),++(++Set.cbegin()));

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	// Odstrani ITEM s hodnotou '5'.
	wcout << L"NUMBER of REMOVED ITEMS [" << Set.erase(5) << L"] !" << endl;

	PrintSet(L"SET",Set);

	PrintLineSeparator();

	// Neodstrani nic, pretoze ITEM '5' sa v SET NENACHADZA.
	wcout << L"NUMBER of REMOVED ITEMS [" << Set.erase(5) << L"] !" << endl;

	PrintSet(L"SET",Set);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSetErase(void)
{
	PrintLineSeparator();

	multiset<int>												MultiSet;

	MultiSet.insert(1);
	MultiSet.insert(1);
	MultiSet.insert(2);
	MultiSet.insert(2);
	MultiSet.insert(3);
	MultiSet.insert(3);
	MultiSet.insert(4);
	MultiSet.insert(4);
	MultiSet.insert(5);
	MultiSet.insert(5);

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	// Odstrani 2 ITEMS.
	MultiSet.erase(MultiSet.cbegin(),++(++MultiSet.cbegin()));

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	// Odstrani 2 ITEM s hodnotou ITEM '5'.
	wcout << L"NUMBER of REMOVED ITEMS [" << MultiSet.erase(5) << L"] !" << endl;

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();

	// Neodstrani nic, pretoze ITEM '5' sa v MULTISET NENACHADZA.
	wcout << L"NUMBER of REMOVED ITEMS [" << MultiSet.erase(5) << L"] !" << endl;

	PrintMultiSet(L"MULTISET",MultiSet);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapInitialization(void)
{
	PrintLineSeparator();

	map<int,wstring>											Map1;

	Map1[1]=L"11";
	Map1[2]=L"12";
	Map1[3]=L"13";

	PrintMap(L"MAP 1",Map1);

	// Pouzije sa COPY CONSTRUCTOR.
	map<int,wstring>											Map2(Map1);
	
	PrintMap(L"MAP 2",Map2);

	map<int,wstring>											Map3;

	// Pouzije sa COPY OPERATOR=.
	Map3=Map1;

	PrintMap(L"MAP 3",Map3);

	PrintLineSeparator();

	// Pouzije sa MOVE OPERATOR=.
	Map3=std::move(Map2);

	PrintMap(L"MAP 2",Map2);
	PrintMap(L"MAP 3",Map3);

	PrintLineSeparator();

	// !!! COMPARER sa vytvara zavolanim DEFAULT CONSTRUCTOR daneho COMPARER.
	map<int,wstring,greater<int>>								Map4;

	Map4[1]=L"11";
	Map4[2]=L"12";
	Map4[3]=L"13";

	PrintMap(L"MAP 4",Map4);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(true);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	map<int,wstring,CCustomComparer>							Map5(CustomComparer1);

	Map5[1]=L"11";
	Map5[2]=L"12";
	Map5[3]=L"13";

	PrintMap(L"MAP 5",Map5);

	CCustomComparer												CustomComparer2(false);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	map<int,wstring,CCustomComparer>							Map6(CustomComparer2);

	Map6[1]=L"11";
	Map6[2]=L"12";
	Map6[3]=L"13";

	PrintMap(L"MAP 6",Map6);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapInitialization(void)
{
	PrintLineSeparator();

	multimap<int,wstring>										MultiMap1;

	MultiMap1.insert(pair<int,wstring>(1,L"11"));
	MultiMap1.insert(pair<int,wstring>(1,L"11"));
	MultiMap1.insert(pair<int,wstring>(2,L"12"));
	MultiMap1.insert(pair<int,wstring>(2,L"12"));
	MultiMap1.insert(pair<int,wstring>(3,L"13"));
	MultiMap1.insert(pair<int,wstring>(3,L"13"));

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);

	// Pouzije sa COPY CONSTRUCTOR.
	multimap<int,wstring>										MultiMap2(MultiMap1);
	
	PrintMultiMap(L"MULTIMAP 2",MultiMap2);

	multimap<int,wstring>										MultiMap3;

	// Pouzije sa COPY OPERATOR=.
	MultiMap3=MultiMap1;

	PrintMultiMap(L"MULTIMAP 3",MultiMap3);

	PrintLineSeparator();

	// Pouzije sa MOVE OPERATOR=.
	MultiMap3=std::move(MultiMap2);

	PrintMultiMap(L"MULTIMAP 2",MultiMap2);
	PrintMultiMap(L"MULTIMAP 3",MultiMap3);

	PrintLineSeparator();

	// !!! COMPARER sa vytvara zavolanim DEFAULT CONSTRUCTOR daneho COMPARER.
	multimap<int,wstring,greater<int>>							MultiMap4;

	MultiMap4.insert(pair<int,wstring>(1,L"11"));
	MultiMap4.insert(pair<int,wstring>(1,L"11"));
	MultiMap4.insert(pair<int,wstring>(2,L"12"));
	MultiMap4.insert(pair<int,wstring>(2,L"12"));
	MultiMap4.insert(pair<int,wstring>(3,L"13"));
	MultiMap4.insert(pair<int,wstring>(3,L"13"));

	PrintMultiMap(L"MULTIMAP 4",MultiMap4);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(true);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	multimap<int,wstring,CCustomComparer>						MultiMap5(CustomComparer1);

	MultiMap5.insert(pair<int,wstring>(1,L"11"));
	MultiMap5.insert(pair<int,wstring>(1,L"11"));
	MultiMap5.insert(pair<int,wstring>(2,L"12"));
	MultiMap5.insert(pair<int,wstring>(2,L"12"));
	MultiMap5.insert(pair<int,wstring>(3,L"13"));
	MultiMap5.insert(pair<int,wstring>(3,L"13"));

	PrintMultiMap(L"MULTIMAP 5",MultiMap5);

	CCustomComparer												CustomComparer2(false);

	// !!! COMPARER sa zadava do ako PARAMETER do CONSTRUCTOR.
	multimap<int,wstring,CCustomComparer>						MultiMap6(CustomComparer2);

	MultiMap6.insert(pair<int,wstring>(1,L"11"));
	MultiMap6.insert(pair<int,wstring>(1,L"11"));
	MultiMap6.insert(pair<int,wstring>(2,L"12"));
	MultiMap6.insert(pair<int,wstring>(2,L"12"));
	MultiMap6.insert(pair<int,wstring>(3,L"13"));
	MultiMap6.insert(pair<int,wstring>(3,L"13"));

	PrintMultiMap(L"MULTIMAP 6",MultiMap6);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapComparison(void)
{
	PrintLineSeparator();

	map<int,int>												Map1;

	Map1[1]=11;
	Map1[2]=12;
	Map1[3]=13;

	map<int,int>												Map2;

	Map2[1]=11;
	Map2[2]=2;
	Map2[3]=13;

	map<int,int>												Map3;

	Map3[1]=11;
	Map3[2]=22;
	Map3[3]=13;

	map<int,int>												Map4;

	Map4[1]=11;
	Map4[2]=12;
	Map4[3]=13;
	Map4[4]=14;

	map<int,int>												Map5;

	Map5[1]=11;
	Map5[22]=12;
	Map5[3]=13;

	PrintMap(L"MAP 1",Map1);
	PrintMap(L"MAP 2",Map2);

	wcout << L"MAP1==MAP2 [" << ((Map1==Map2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1!=MAP2 [" << ((Map1!=Map2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1<MAP2 [" << ((Map1<Map2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1<=MAP2 [" << ((Map1<=Map2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>=MAP2 [" << ((Map1>=Map2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>MAP2 [" << ((Map1>Map2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMap(L"MAP 1",Map1);
	PrintMap(L"MAP 3",Map3);

	wcout << L"MAP1<MAP3 [" << ((Map1<Map3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1<=MAP3 [" << ((Map1<=Map3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>=MAP3 [" << ((Map1>=Map3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>MAP3 [" << ((Map1>Map3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMap(L"MAP 1",Map1);
	PrintMap(L"MAP 4",Map4);

	wcout << L"MAP1<MAP4 [" << ((Map1<Map4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1<=MAP4 [" << ((Map1<=Map4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>=MAP4 [" << ((Map1>=Map4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>MAP4 [" << ((Map1>Map4) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMap(L"MAP 1",Map1);
	PrintMap(L"MAP 5",Map5);

	wcout << L"MAP1<MAP5 [" << ((Map1<Map5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1<=MAP5 [" << ((Map1<=Map5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>=MAP5 [" << ((Map1>=Map5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MAP1>MAP5 [" << ((Map1>Map5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapComparison(void)
{
	PrintLineSeparator();

	multimap<int,int>											MultiMap1;

	MultiMap1.insert(pair<int,int>(1,11));
	MultiMap1.insert(pair<int,int>(2,12));
	MultiMap1.insert(pair<int,int>(3,13));

	multimap<int,int>											MultiMap2;

	MultiMap2.insert(pair<int,int>(1,11));
	MultiMap2.insert(pair<int,int>(2,2));
	MultiMap2.insert(pair<int,int>(3,13));

	multimap<int,int>											MultiMap3;

	MultiMap3.insert(pair<int,int>(1,11));
	MultiMap3.insert(pair<int,int>(2,22));
	MultiMap3.insert(pair<int,int>(3,13));

	multimap<int,int>											MultiMap4;

	MultiMap4.insert(pair<int,int>(1,11));
	MultiMap4.insert(pair<int,int>(2,12));
	MultiMap4.insert(pair<int,int>(3,13));
	MultiMap4.insert(pair<int,int>(4,14));

	multimap<int,int>											MultiMap5;

	MultiMap5.insert(pair<int,int>(1,11));
	MultiMap5.insert(pair<int,int>(22,12));
	MultiMap5.insert(pair<int,int>(3,13));

	multimap<int,int>											MultiMap6;

	MultiMap6.insert(pair<int,int>(1,11));
	MultiMap6.insert(pair<int,int>(2,12));
	MultiMap6.insert(pair<int,int>(2,2));
	MultiMap6.insert(pair<int,int>(3,13));

	multimap<int,int>											MultiMap7;

	MultiMap7.insert(pair<int,int>(1,11));
	MultiMap7.insert(pair<int,int>(2,12));
	MultiMap7.insert(pair<int,int>(2,22));
	MultiMap7.insert(pair<int,int>(3,13));

	multimap<int,int>											MultiMap8;

	MultiMap8.insert(pair<int,int>(1,11));
	MultiMap8.insert(pair<int,int>(2,12));
	MultiMap8.insert(pair<int,int>(2,22));

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintMultiMap(L"MULTIMAP 2",MultiMap2);

	wcout << L"MULTIMAP1==MULTIMAP2 [" << ((MultiMap1==MultiMap2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1!=MULTIMAP2 [" << ((MultiMap1!=MultiMap2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<MULTIMAP2 [" << ((MultiMap1<MultiMap2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<=MULTIMAP2 [" << ((MultiMap1<=MultiMap2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>=MULTIMAP2 [" << ((MultiMap1>=MultiMap2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>MULTIMAP2 [" << ((MultiMap1>MultiMap2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintMultiMap(L"MULTIMAP 3",MultiMap3);

	wcout << L"MULTIMAP1<MULTIMAP3 [" << ((MultiMap1<MultiMap3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<=MULTIMAP3 [" << ((MultiMap1<=MultiMap3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>=MULTIMAP3 [" << ((MultiMap1>=MultiMap3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>MULTIMAP3 [" << ((MultiMap1>MultiMap3) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintMultiMap(L"MULTIMAP 4",MultiMap4);

	wcout << L"MULTIMAP1<MULTIMAP4 [" << ((MultiMap1<MultiMap4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<=MULTIMAP4 [" << ((MultiMap1<=MultiMap4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>=MULTIMAP4 [" << ((MultiMap1>=MultiMap4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>MULTIMAP4 [" << ((MultiMap1>MultiMap4) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintMultiMap(L"MULTIMAP 5",MultiMap5);

	wcout << L"MULTIMAP1<MULTIMAP5 [" << ((MultiMap1<MultiMap5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<=MULTIMAP5 [" << ((MultiMap1<=MultiMap5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>=MULTIMAP5 [" << ((MultiMap1>=MultiMap5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>MULTIMAP5 [" << ((MultiMap1>MultiMap5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintMultiMap(L"MULTIMAP 6",MultiMap6);

	wcout << L"MULTIMAP1<MULTIMAP6 [" << ((MultiMap1<MultiMap6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<=MULTIMAP6 [" << ((MultiMap1<=MultiMap6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>=MULTIMAP6 [" << ((MultiMap1>=MultiMap6) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>MULTIMAP6 [" << ((MultiMap1>MultiMap6) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintMultiMap(L"MULTIMAP 7",MultiMap7);

	wcout << L"MULTIMAP1<MULTIMAP7 [" << ((MultiMap1<MultiMap7) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<=MULTIMAP7 [" << ((MultiMap1<=MultiMap7) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>=MULTIMAP7 [" << ((MultiMap1>=MultiMap7) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>MULTIMAP7 [" << ((MultiMap1>MultiMap7) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintMultiMap(L"MULTIMAP 8",MultiMap8);

	wcout << L"MULTIMAP1<MULTIMAP8 [" << ((MultiMap1<MultiMap8) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1<=MULTIMAP8 [" << ((MultiMap1<=MultiMap8) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>=MULTIMAP8 [" << ((MultiMap1>=MultiMap8) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"MULTIMAP1>MULTIMAP8 [" << ((MultiMap1>MultiMap8) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapSize(void)
{
	PrintLineSeparator();

	map<int,int>												Map;

	Map[1]=11;
	Map[2]=12;
	Map[3]=13;

	PrintMap(L"MAP",Map);

	wcout << L"MAP - SIZE [" << Map.size() << L"] !" << endl;
	wcout << L"MAP - MAX SIZE [" << Map.max_size() << L"] !" << endl;
	wcout << L"MAP - EMPTY [" << Map.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapSize(void)
{
	PrintLineSeparator();

	multimap<int,int>											MultiMap;

	MultiMap.insert(pair<int,int>(1,11));
	MultiMap.insert(pair<int,int>(2,12));
	MultiMap.insert(pair<int,int>(3,13));

	PrintMultiMap(L"MULTIMAP",MultiMap);

	wcout << L"MULTIMAP - SIZE [" << MultiMap.size() << L"] !" << endl;
	wcout << L"MULTIMAP - MAX SIZE [" << MultiMap.max_size() << L"] !" << endl;
	wcout << L"MULTIMAP - EMPTY [" << MultiMap.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapFind(void)
{
	PrintLineSeparator();

	map<int,int>												Map;

	Map[1]=11;
	Map[2]=12;
	Map[3]=13;
	Map[4]=14;
	Map[5]=15;

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	wcout << L"MAP - COUNT(1) - [" << Map.count(1) << L"] !" << endl;
	wcout << L"MAP - COUNT(8) - [" << Map.count(8) << L"] !" << endl;
	
	PrintLineSeparator();

	PrintMapIterator(L"MAP - FIND(-1) -",Map,Map.find(-1));
	PrintMapIterator(L"MAP - FIND(3) -",Map,Map.find(3));
	PrintMapIterator(L"MAP - FIND(6) -",Map,Map.find(6));
	
	PrintLineSeparator();

	PrintMapIterator(L"MAP - LOWER_BOUND(-1) -",Map,Map.lower_bound(-1));
	PrintMapIterator(L"MAP - LOWER_BOUND(3) -",Map,Map.lower_bound(3));
	PrintMapIterator(L"MAP - LOWER_BOUND(6) -",Map,Map.lower_bound(6));
	
	PrintLineSeparator();

	PrintMapIterator(L"MAP - UPPER_BOUND(-1) -",Map,Map.upper_bound(-1));
	PrintMapIterator(L"MAP - UPPER_BOUND(3) -",Map,Map.upper_bound(3));
	PrintMapIterator(L"MAP - UPPER_BOUND(6) -",Map,Map.upper_bound(6));

	PrintLineSeparator();

	using														MapIteratorPair=pair<map<int,int>::const_iterator,map<int,int>::const_iterator>;

	MapIteratorPair												IteratorPair1=Map.equal_range(-1);
	MapIteratorPair												IteratorPair2=Map.equal_range(3);
	MapIteratorPair												IteratorPair3=Map.equal_range(6);

	PrintMapIterator(L"MAP - EQUAL_BOUND(-1).FIRST -",Map,IteratorPair1.first);
	PrintMapIterator(L"MAP - EQUAL_BOUND(-1).SECOND -",Map,IteratorPair1.second);
	PrintMapIterator(L"MAP - EQUAL_BOUND(3).FIRST -",Map,IteratorPair2.first);
	PrintMapIterator(L"MAP - EQUAL_BOUND(3).SECOND -",Map,IteratorPair2.second);
	PrintMapIterator(L"MAP - EQUAL_BOUND(6).FIRST -",Map,IteratorPair3.first);
	PrintMapIterator(L"MAP - EQUAL_BOUND(6).SECOND -",Map,IteratorPair3.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapFind(void)
{
	PrintLineSeparator();

	multimap<int,int>											MultiMap;

	MultiMap.insert(pair<int,int>(1,11));
	MultiMap.insert(pair<int,int>(1,111));
	MultiMap.insert(pair<int,int>(2,22));
	MultiMap.insert(pair<int,int>(2,222));
	MultiMap.insert(pair<int,int>(3,33));
	MultiMap.insert(pair<int,int>(3,333));
	MultiMap.insert(pair<int,int>(4,44));
	MultiMap.insert(pair<int,int>(4,444));
	MultiMap.insert(pair<int,int>(5,55));
	MultiMap.insert(pair<int,int>(5,555));

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	wcout << L"MULTIMAP - COUNT(1) - [" << MultiMap.count(1) << L"] !" << endl;
	wcout << L"MULTIMAP - COUNT(8) - [" << MultiMap.count(8) << L"] !" << endl;
	
	PrintLineSeparator();

	PrintMultiMapIterator(L"MULTIMAP - FIND(-1) -",MultiMap,MultiMap.find(-1));
	PrintMultiMapIterator(L"MULTIMAP - FIND(3) -",MultiMap,MultiMap.find(3));
	PrintMultiMapIterator(L"MULTIMAP - FIND(6) -",MultiMap,MultiMap.find(6));
	
	PrintLineSeparator();

	PrintMultiMapIterator(L"MULTIMAP - LOWER_BOUND(-1) -",MultiMap,MultiMap.lower_bound(-1));
	PrintMultiMapIterator(L"MULTIMAP - LOWER_BOUND(3) -",MultiMap,MultiMap.lower_bound(3));
	PrintMultiMapIterator(L"MULTIMAP - LOWER_BOUND(6) -",MultiMap,MultiMap.lower_bound(6));
	
	PrintLineSeparator();

	PrintMultiMapIterator(L"MULTIMAP - UPPER_BOUND(-1) -",MultiMap,MultiMap.upper_bound(-1));
	PrintMultiMapIterator(L"MULTIMAP - UPPER_BOUND(3) -",MultiMap,MultiMap.upper_bound(3));
	PrintMultiMapIterator(L"MULTIMAP - UPPER_BOUND(6) -",MultiMap,MultiMap.upper_bound(6));

	PrintLineSeparator();

	using														MultiMapIteratorPair=pair<multimap<int,int>::const_iterator,multimap<int,int>::const_iterator>;

	MultiMapIteratorPair										IteratorPair1=MultiMap.equal_range(-1);
	MultiMapIteratorPair										IteratorPair2=MultiMap.equal_range(3);
	MultiMapIteratorPair										IteratorPair3=MultiMap.equal_range(6);

	PrintMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(-1).FIRST -",MultiMap,IteratorPair1.first);
	PrintMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(-1).SECOND -",MultiMap,IteratorPair1.second);
	PrintMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(3).FIRST -",MultiMap,IteratorPair2.first);
	PrintMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(3).SECOND -",MultiMap,IteratorPair2.second);
	PrintMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(6).FIRST -",MultiMap,IteratorPair3.first);
	PrintMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(6).SECOND -",MultiMap,IteratorPair3.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapAssign(void)
{
	PrintLineSeparator();

	map<int,int>												Map1;

	Map1[1]=11;
	Map1[2]=12;
	Map1[3]=13;
	Map1[4]=14;
	Map1[5]=15;

	PrintMap(L"MAP 1",Map1);

	map<int,int>												Map2(Map1);

	PrintMap(L"MAP 2",Map2);

	map<int,int>												Map3;

	Map3=Map1;

	PrintMap(L"MAP 3",Map3);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(true);
	CCustomComparer												CustomComparer2(false);

	// !!! Obe MAPS maju ten isty TYPE, ale INY COMPARER s INYMI SEARCH CRITERIA.
	map<int,wstring,CCustomComparer>							Map4(CustomComparer1);
	map<int,wstring,CCustomComparer>							Map5(CustomComparer2);

	Map4[5]=L"5";
	Map4[6]=L"6";
	Map4[7]=L"7";

	// !!! ITEMS su SORTED podla POVODNEHO COMPARER.
	Map5[15]=L"15";
	Map5[16]=L"16";
	Map5[17]=L"17";

	PrintMap(L"MAP 4",Map4);
	PrintMap(L"MAP 5",Map5);

	PrintLineSeparator();

	// !!! MAP UMOZNUJE priradzovat jednu instanciu MAP ak maju ROVANKY COMPARER TYPE, ale zaroven kazda instancia MAP pouziva INU INSTANCIU COMPARER s INYMI SEARCH CRITERIA.
	// !!!!! Kedze pri priradzovani sa prenasa aj COMPARER, ITEMS v 'Map5' vsak budu SORTED podla COMPARER z 'Map4'.
	Map5=Map4;

	PrintMap(L"MAP 5",Map5);

	PrintLineSeparator();

	// Kedze pri priradeni sa PRENIESOL aj COMPARER, dalsie ITEMS uz su ORDERED podla NOVEHO COMPARER, ktory bol preneseny z 'Map4'.
	Map5[1]=L"1";
	Map5[20]=L"20";

	PrintMap(L"MAP 5",Map5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapAssign(void)
{
	PrintLineSeparator();

	multimap<int,int>											MultiMap1;

	MultiMap1.insert(pair<int,int>(1,11));
	MultiMap1.insert(pair<int,int>(1,111));
	MultiMap1.insert(pair<int,int>(2,12));
	MultiMap1.insert(pair<int,int>(2,112));
	MultiMap1.insert(pair<int,int>(3,13));
	MultiMap1.insert(pair<int,int>(3,113));
	MultiMap1.insert(pair<int,int>(4,14));
	MultiMap1.insert(pair<int,int>(4,114));
	MultiMap1.insert(pair<int,int>(5,15));
	MultiMap1.insert(pair<int,int>(5,115));

	PrintMultiMap(L"MULTIMAP 1",MultiMap1);

	multimap<int,int>											MultiMap2(MultiMap1);

	PrintMultiMap(L"MULTIMAP 2",MultiMap2);

	multimap<int,int>											MultiMap3;

	MultiMap3=MultiMap1;

	PrintMultiMap(L"MULTIMAP 3",MultiMap3);

	PrintLineSeparator();

	CCustomComparer												CustomComparer1(true);
	CCustomComparer												CustomComparer2(false);

	// !!! Obe MAPS maju ten isty TYPE, ale INY COMPARER s INYMI SEARCH CRITERIA.
	multimap<int,wstring,CCustomComparer>						MultiMap4(CustomComparer1);
	multimap<int,wstring,CCustomComparer>						MultiMap5(CustomComparer2);

	MultiMap4.insert(pair<int,wstring>(5,L"5"));
	MultiMap4.insert(pair<int,wstring>(5,L"55"));
	MultiMap4.insert(pair<int,wstring>(6,L"6"));
	MultiMap4.insert(pair<int,wstring>(6,L"66"));
	MultiMap4.insert(pair<int,wstring>(7,L"7"));
	MultiMap4.insert(pair<int,wstring>(6,L"77"));

	// !!! ITEMS su SORTED podla POVODNEHO COMPARER.
	MultiMap5.insert(pair<int,wstring>(15,L"15"));
	MultiMap5.insert(pair<int,wstring>(15,L"115"));
	MultiMap5.insert(pair<int,wstring>(16,L"16"));
	MultiMap5.insert(pair<int,wstring>(16,L"116"));
	MultiMap5.insert(pair<int,wstring>(17,L"17"));
	MultiMap5.insert(pair<int,wstring>(17,L"117"));

	PrintMultiMap(L"MULTIMAP 4",MultiMap4);
	PrintMultiMap(L"MULTIMAP 5",MultiMap5);

	PrintLineSeparator();

	// !!! MAP UMOZNUJE priradzovat jednu instanciu MULTIMAP ak maju ROVANKY COMPARER TYPE, ale zaroven kazda instancia MULTIMAP pouziva INU INSTANCIU COMPARER s INYMI SEARCH CRITERIA.
	// !!!!! Kedze pri priradzovani sa prenasa aj COMPARER, ITEMS v 'MultiMap5' vsak budu SORTED podla COMPARER z 'MultiMap4'.
	MultiMap5=MultiMap4;

	PrintMultiMap(L"MULTIMAP 5",MultiMap5);

	PrintLineSeparator();

	// Kedze pri priradeni sa PRENIESOL aj COMPARER, dalsie ITEMS uz su ORDERED podla NOVEHO COMPARER, ktory bol preneseny z 'MultiMap4'.
	MultiMap5.insert(pair<int,wstring>(1,L"1"));
	MultiMap5.insert(pair<int,wstring>(1,L"100"));
	MultiMap5.insert(pair<int,wstring>(20,L"20"));
	MultiMap5.insert(pair<int,wstring>(20,L"2000"));

	PrintMultiMap(L"MULTIMAP 5",MultiMap5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapIterators(void)
{
	PrintLineSeparator();

	map<int,int>												Map;

	Map[1]=11;
	Map[2]=12;
	Map[3]=13;
	Map[4]=14;
	Map[5]=15;

	wcout << L"MAP [";

	for(map<int,int>::iterator Iterator=Map.begin();Iterator!=Map.end();Iterator++)
	{
		if (Iterator!=Map.cbegin())
		{
			wcout << L" ";
		}

		wcout << L"[" << Iterator->first << "]=[" << Iterator->second << "]";

		// Modifikuje sa VALUE. KEYS NIE JE MOZNE modifikovat, pretoze su oznacene ako CONST.
		Iterator->second=Iterator->second*2;
	}

	wcout << L"] !" << endl;

	wcout << L"MAP [";

	// Pouzije sa CONST ITERATOR.
	for(map<int,int>::const_iterator Iterator=Map.cbegin();Iterator!=Map.cend();Iterator++)
	{
		if (Iterator!=Map.cbegin())
		{
			wcout << L" ";
		}

		wcout << L"[" << Iterator->first << "]=[" << Iterator->second << "]";
	}

	wcout << L"] !" << endl;

	wcout << L"MAP [";

	bool														IsFirst=true;

	// Pouzije sa C++ 11 ITERATION.
	for(const map<int,int>::value_type& Pair : Map)
	{
		if (IsFirst==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst=false;
		}

		wcout << L"[" << Pair.first << "]=[" << Pair.second << "]";
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapIterators(void)
{
	PrintLineSeparator();

	multimap<int,int>											MultiMap;

	MultiMap.insert(pair<int,int>(1,11));
	MultiMap.insert(pair<int,int>(1,111));
	MultiMap.insert(pair<int,int>(2,12));
	MultiMap.insert(pair<int,int>(2,112));
	MultiMap.insert(pair<int,int>(3,13));
	MultiMap.insert(pair<int,int>(3,113));
	MultiMap.insert(pair<int,int>(4,14));
	MultiMap.insert(pair<int,int>(4,114));
	MultiMap.insert(pair<int,int>(5,15));
	MultiMap.insert(pair<int,int>(5,115));

	wcout << L"MULTIMAP [";

	for(multimap<int,int>::iterator Iterator=MultiMap.begin();Iterator!=MultiMap.end();Iterator++)
	{
		if (Iterator!=MultiMap.cbegin())
		{
			wcout << L" ";
		}

		wcout << L"[" << Iterator->first << "]=[" << Iterator->second << "]";

		// Modifikuje sa VALUE. KEYS NIE JE MOZNE modifikovat, pretoze su oznacene ako CONST.
		Iterator->second=Iterator->second*2;
	}

	wcout << L"] !" << endl;

	wcout << L"MULTIMAP [";

	// Pouzije sa CONST ITERATOR.
	for(multimap<int,int>::const_iterator Iterator=MultiMap.cbegin();Iterator!=MultiMap.cend();Iterator++)
	{
		if (Iterator!=MultiMap.cbegin())
		{
			wcout << L" ";
		}

		wcout << L"[" << Iterator->first << "]=[" << Iterator->second << "]";
	}

	wcout << L"] !" << endl;

	wcout << L"MULTIMAP [";

	bool														IsFirst=true;

	// Pouzije sa C++ 11 ITERATION.
	for(const multimap<int,int>::value_type& Pair : MultiMap)
	{
		if (IsFirst==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst=false;
		}

		wcout << L"[" << Pair.first << "]=[" << Pair.second << "]";
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapInsert(void)
{
	PrintLineSeparator();

	map<int,int>												Map;

	Map[1]=11;

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM s danym KEY uz v MAP NACHADZA.
	pair<map<int,int>::iterator,bool>							Result1=Map.insert(map<int,int>::value_type(2,22));

	if (Result1.second==true)
	{
		wcout << L"ITEM (" << Result1.first->first << L"," << Result1.first->second << L") was ADDED to MAP !" << endl;
	}
	else
	{
		wcout << L"ITEM (2,22) was NOT ADDED to MAP !" << endl;
	}

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM s danym KEY uz v MAP NACHADZA.
	pair<map<int,int>::iterator,bool>							Result2=Map.insert(map<int,int>::value_type(2,22));

	// !!!!! Kedze ITEM s KEY '2' uz v MAP EXISTUJE, tak volanie METHOD insert() ZLYHA.
	if (Result2.second==true)
	{
		wcout << L"ITEM (" << Result2.first->first << L"," << Result2.first->second << L") was ADDED to MAP !" << endl;
	}
	else
	{
		wcout << L"ITEM (2,22) was NOT ADDED to MAP !" << endl;
	}

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	array<map<int,int>::value_type,2>							Array1{map<int,int>::value_type(3,33),map<int,int>::value_type(4,44)};
	array<map<int,int>::value_type,3>							Array2{map<int,int>::value_type(3,33),map<int,int>::value_type(4,44),map<int,int>::value_type(5,55)};

	// Vklada sa naraz viacero ITEMS.
	// !!! Existujuce ITEMS sa PREPISU na nove VALUES.
	Map.insert(Array1.begin(),Array1.end());

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	// Vklada sa naraz viacero ITEMS.
	Map.insert(Array2.begin(),Array2.end());

	PrintMap(L"MAP",Map);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapInsert(void)
{
	PrintLineSeparator();

	multimap<int,int>											MultiMap{multimap<int,int>::value_type(1,11)};

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
	multimap<int,int>::iterator									Result1=MultiMap.insert(multimap<int,int>::value_type(2,22));

	wcout << L"ITEM (" << Result1->first << L"," << Result1->second << L") was ADDED to MULTIMAP !" << endl;

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM.
	multimap<int,int>::iterator									Result2=MultiMap.insert(multimap<int,int>::value_type(2,222));

	// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
	wcout << L"ITEM (" << Result2->first << L"," << Result2->second << L") was ADDED to MULTIMAP !" << endl;

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	array<map<int,int>::value_type,2>							Array1{map<int,int>::value_type(3,33),map<int,int>::value_type(4,44)};
	array<map<int,int>::value_type,3>							Array2{map<int,int>::value_type(3,33),map<int,int>::value_type(4,44),map<int,int>::value_type(5,55)};

	// Vklada sa naraz viacero ITEMS.
	MultiMap.insert(Array1.begin(),Array1.end());

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	// Vklada sa naraz viacero ITEMS.
	// !!! Pridaju sa aj ITEMS s EXISTUJUCIMI KEYS, pretoze sa jedna o MULTIMAP.
	MultiMap.insert(Array2.begin(),Array2.end());

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapEmplace(void)
{
	PrintLineSeparator();

	{
		map<int,CInt>											Map;

		Map[1]=CInt(11);

		PrintMap(L"MAP",Map);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM s danym KEY uz v MAP NACHADZA.
		pair<map<int,CInt>::iterator,bool>						Result1=Map.emplace(map<int,CInt>::value_type(2,22));

		if (Result1.second==true)
		{
			wcout << L"ITEM (" << Result1.first->first << L"," << Result1.first->second << L") was ADDED to MAP !" << endl;
		}
		else
		{
			wcout << L"ITEM (2,22) was NOT ADDED to MAP !" << endl;
		}

		PrintMap(L"MAP",Map);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM. ITEM sa NEPODARI vlozit, ak sa ITEM s danym KEY uz v MAP NACHADZA.
		pair<map<int,CInt>::iterator,bool>						Result2=Map.emplace(map<int,CInt>::value_type(2,22));

		// !!!!! Kedze ITEM s KEY '2' uz v MAP EXISTUJE, tak volanie METHOD insert() ZLYHA.
		if (Result2.second==true)
		{
			wcout << L"ITEM (" << Result2.first->first << L"," << Result2.first->second << L") was ADDED to MAP !" << endl;
		}
		else
		{
			wcout << L"ITEM (2,22) was NOT ADDED to MAP !" << endl;
		}

		PrintMap(L"MAP",Map);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapEmplace(void)
{
	PrintLineSeparator();

	{
		multimap<int,CInt>										MultiMap{multimap<int,CInt>::value_type(1,11)};

		PrintMultiMap(L"MULTIMAP",MultiMap);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
		multimap<int,CInt>::iterator							Result1=MultiMap.emplace(multimap<int,CInt>::value_type(2,22));

		wcout << L"ITEM (" << Result1->first << L"," << Result1->second << L") was ADDED to MULTIMAP !" << endl;

		PrintMultiMap(L"MULTIMAP",MultiMap);

		PrintLineSeparator();

		// !!! RETURN VALUE obsahuje informaciu ci sa ITEM podarilo pridat a ak ano tak aj ITERATOR na tento ITEM.
		multimap<int,CInt>::iterator							Result2=MultiMap.emplace(multimap<int,CInt>::value_type(2,222));

		// !!! RETURN VALUE obsahuje ITERATOR na pridany ITEM.
		wcout << L"ITEM (" << Result2->first << L"," << Result2->second << L") was ADDED to MULTIMAP !" << endl;

		PrintMultiMap(L"MULTIMAP",MultiMap);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapErase(void)
{
	PrintLineSeparator();

	map<int,int>												Map;

	Map[1]=11;
	Map[2]=12;
	Map[3]=13;
	Map[4]=14;
	Map[5]=15;

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	// Odstrani 2 ITEMS.
	Map.erase(Map.cbegin(),++(++Map.cbegin()));

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	// Odstrani ITEM s hodnotou KEY '5'.
	wcout << L"NUMBER of REMOVED ITEMS [" << Map.erase(5) << L"] !" << endl;

	PrintMap(L"MAP",Map);

	PrintLineSeparator();

	// Neodstrani nic, pretoze KEY '5' sa v MAP NENACHADZA.
	wcout << L"NUMBER of REMOVED ITEMS [" << Map.erase(5) << L"] !" << endl;

	PrintMap(L"MAP",Map);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMapErase(void)
{
	PrintLineSeparator();

	multimap<int,int>											MultiMap;

	MultiMap.insert(pair<int,int>(1,11));
	MultiMap.insert(pair<int,int>(1,111));
	MultiMap.insert(pair<int,int>(2,12));
	MultiMap.insert(pair<int,int>(2,112));
	MultiMap.insert(pair<int,int>(3,13));
	MultiMap.insert(pair<int,int>(3,113));
	MultiMap.insert(pair<int,int>(4,14));
	MultiMap.insert(pair<int,int>(4,114));
	MultiMap.insert(pair<int,int>(5,15));
	MultiMap.insert(pair<int,int>(5,115));

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	// Odstrani 2 ITEMS.
	MultiMap.erase(MultiMap.cbegin(),++(++MultiMap.cbegin()));

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	// Odstrani 2 ITEM s hodnotou KEY '5'.
	wcout << L"NUMBER of REMOVED ITEMS [" << MultiMap.erase(5) << L"] !" << endl;

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	// Neodstrani nic, pretoze KEY '5' sa v MULTIMAP NENACHADZA.
	wcout << L"NUMBER of REMOVED ITEMS [" << MultiMap.erase(5) << L"] !" << endl;

	PrintMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMapAtAndOperatorSubscription(void)
{
	PrintLineSeparator();

	map<int,int>												Map1;

	// Pridavaju sa nove ITEMS do MAP.
	Map1[1]=11;
	Map1[2]=12;
	Map1[3]=13;

	wcout << L"MAP 1 [";

	bool														IsFirst1=true;

	// Pouzije sa C++ 11 ITERATION.
	for(const map<int,int>::value_type& Pair : Map1)
	{
		if (IsFirst1==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst1=false;
		}

		// !!! Na pristup k MAP ITEMS sa pouziva OPERATOR[].
		wcout << L"[" << Pair.first << "]=[" << Map1[Pair.first] << "]";
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	{
		map<int,CInt>											Map2;

		// !!! Pre KAZDY ITEM sa vola DEFAULT CONSTRUCTOR a OPERATOR=. To je NEVYHODA pouzitia OPERATOR[] pri pridavani novych ITEMS.
		Map2[1]=CInt(11);
		Map2[2]=CInt(12);
		Map2[3]=CInt(13);

		PrintMap(L"MAP 2",Map2);

		PrintLineSeparator();

		// !!! Aj ked je OPERATOR[] na RIGHT SIDE danej EXPRESSION, tak sa NOVY ITEMS prida do MAP, pretoze ITEMS s KEY '4' sa v MAP nenachadza.
		// !!! Novy ITEM bude obsahovat DEFAULT VALUE.
		wcout << L"ITEM [4]=[" << Map2[4] << "] !" << endl;

		PrintMap(L"MAP 2",Map2);

		PrintLineSeparator();

		wcout << L"MAP 2 [";

		bool													IsFirst2=true;

		// Pouzije sa C++ 11 ITERATION.
		for(const map<int,CInt>::value_type& Pair : Map2)
		{
			if (IsFirst2==false)
			{
				wcout << L" ";
			}
			else
			{
				IsFirst2=false;
			}

			// !!! Na pristup k MAP ITEMS sa pouziva METHOD at().
			wcout << L"[" << Pair.first << "]=[" << Map2.at(Pair.first) << "]";
		}

		wcout << L"] !" << endl;

		PrintLineSeparator();

		try
		{
			// !!! Hodi EXCEPTION, pretoze ITEM s hodnotu '5' sa v MAP NENACHADZA.
			wcout << L"[5]=[" << Map2.at(5) << "]";
		}
		catch(const out_of_range&)
		{
			wcout << L"Can't ACCESS ITEM !" << endl;
		}

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetInitialization(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(5);
	Set1.insert(6);
	Set1.insert(7);
	Set1.insert(8);

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(9);
	Set1.insert(10);

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Set1.insert(8);
	Set1.insert(9);
	Set1.insert(10);
	
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	unordered_set<int>											Set2(Set1.cbegin(),Set1.cend(),Set1.bucket_count()/2);

	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	Set2.rehash(Set2.size());

	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Neznizi sa pocet BUCKETS. COLLECTION poziadavku ignoruje. METHOD rehash() je len POZIADAVKA o znizenie BUCKETS, ktoru moze COLLECTION ignorovat.
	Set2.rehash(Set2.size()/2);

	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetInitialization(void)
{
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet1;

	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(4);

	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	MultiSet1.insert(5);
	MultiSet1.insert(6);
	MultiSet1.insert(7);
	MultiSet1.insert(8);

	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// ITEMS sa mozu OPAKOVAT.
	MultiSet1.insert(9);
	MultiSet1.insert(10);

	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	MultiSet1.insert(8);
	MultiSet1.insert(9);
	MultiSet1.insert(10);
	
	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	unordered_multiset<int>										MultiSet2(MultiSet1.cbegin(),MultiSet1.cend(),MultiSet1.bucket_count()/2);

	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	MultiSet2.rehash(MultiSet2.size());

	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Neznizi sa pocet BUCKETS. COLLECTION poziadavku ignoruje. METHOD rehash() je len POZIADAVKA o znizenie BUCKETS, ktoru moze COLLECTION ignorovat.
	MultiSet2.rehash(MultiSet2.size()/2);

	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX LOAD FACTOR [" << MultiSet2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapInitialization(void)
{
	PrintLineSeparator();

	unordered_map<int,wstring>									Map1;

	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Map1.insert(pair<const int,wstring>(1,L"1"));
	Map1.insert(pair<const int,wstring>(2,L"2"));
	Map1.insert(pair<const int,wstring>(3,L"3"));
	Map1.insert(pair<const int,wstring>(4,L"4"));

	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Map1.insert(pair<const int,wstring>(5,L"5"));
	Map1.insert(pair<const int,wstring>(6,L"6"));
	Map1.insert(pair<const int,wstring>(7,L"7"));
	Map1.insert(pair<const int,wstring>(8,L"8"));

	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Map1.insert(pair<const int,wstring>(9,L"9"));
	Map1.insert(pair<const int,wstring>(10,L"10"));

	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	Map1.insert(pair<const int,wstring>(8,L"8"));
	Map1.insert(pair<const int,wstring>(9,L"9"));
	Map1.insert(pair<const int,wstring>(10,L"10"));
	
	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	unordered_map<int,wstring>									Map2(Map1.cbegin(),Map1.cend(),Map1.bucket_count()/2);

	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - LOAD FACTOR [" << Map2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	Map2.rehash(Map2.size());

	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - LOAD FACTOR [" << Map2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Neznizi sa pocet BUCKETS. COLLECTION poziadavku ignoruje. METHOD rehash() je len POZIADAVKA o znizenie BUCKETS, ktoru moze COLLECTION ignorovat.
	Map2.rehash(Map2.size()/2);

	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - LOAD FACTOR [" << Map2.load_factor() << L"] !" << endl;
	wcout << L"MAP 2 - MAX LOAD FACTOR [" << Map2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapInitialization(void)
{
	PrintLineSeparator();

	unordered_multimap<int,wstring>								MultiMap1;

	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	MultiMap1.insert(pair<const int,wstring>(1,L"1"));
	MultiMap1.insert(pair<const int,wstring>(2,L"2"));
	MultiMap1.insert(pair<const int,wstring>(3,L"3"));
	MultiMap1.insert(pair<const int,wstring>(4,L"4"));

	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	MultiMap1.insert(pair<const int,wstring>(5,L"5"));
	MultiMap1.insert(pair<const int,wstring>(6,L"6"));
	MultiMap1.insert(pair<const int,wstring>(7,L"7"));
	MultiMap1.insert(pair<const int,wstring>(8,L"8"));

	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	MultiMap1.insert(pair<const int,wstring>(9,L"9"));
	MultiMap1.insert(pair<const int,wstring>(10,L"10"));

	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// ITEMS sa mozu OPAKOVAT.
	MultiMap1.insert(pair<const int,wstring>(8,L"8"));
	MultiMap1.insert(pair<const int,wstring>(9,L"9"));
	MultiMap1.insert(pair<const int,wstring>(10,L"10"));
	
	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	unordered_multimap<int,wstring>								MultiMap2(MultiMap1.cbegin(),MultiMap1.cend(),MultiMap1.bucket_count()/2);

	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// Znizi sa pocet BUCKETS.
	MultiMap2.rehash(MultiMap2.size());

	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Neznizi sa pocet BUCKETS. COLLECTION poziadavku ignoruje. METHOD rehash() je len POZIADAVKA o znizenie BUCKETS, ktoru moze COLLECTION ignorovat.
	MultiMap2.rehash(MultiMap2.size()/2);

	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX LOAD FACTOR [" << MultiMap2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetCustomHash1(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	Set1.insert(0);
	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);
	Set1.insert(5);
	Set1.insert(6);
	Set1.insert(7);
	Set1.insert(8);
	Set1.insert(9);

	PrintCollection(L"SET 1",Set1);

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - MAX BUCKET COUNT [" << Set1.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Set1.insert(Index);
	}

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - MAX BUCKET COUNT [" << Set1.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	unordered_set<int>											Set2;

	Set2.max_load_factor(5);

	Set2.insert(0);
	Set2.insert(1);
	Set2.insert(2);
	Set2.insert(3);
	Set2.insert(4);
	Set2.insert(5);
	Set2.insert(6);
	Set2.insert(7);
	Set2.insert(8);
	Set2.insert(9);

	PrintCollection(L"SET 2",Set2);

	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - MAX BUCKET COUNT [" << Set2.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Set2.insert(Index);
	}

	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - MAX BUCKET COUNT [" << Set2.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_set<int,size_t(*)(int)>							Set3(2,OddEvenHash);

	Set3.insert(0);
	Set3.insert(1);
	Set3.insert(2);
	Set3.insert(3);
	Set3.insert(4);
	Set3.insert(5);
	Set3.insert(6);
	Set3.insert(7);
	Set3.insert(8);
	Set3.insert(9);

	PrintCollection(L"SET 3",Set3);

	wcout << L"SET 3 - SIZE [" << Set3.size() << L"] !" << endl;
	wcout << L"SET 3 - BUCKET COUNT [" << Set3.bucket_count() << L"] !" << endl;
	wcout << L"SET 3 - MAX BUCKET COUNT [" << Set3.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 3 - LOAD FACTOR [" << Set3.load_factor() << L"] !" << endl;
	wcout << L"SET 3 - MAX LOAD FACTOR [" << Set3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Set3.insert(Index);
	}

	wcout << L"SET 3 - SIZE [" << Set3.size() << L"] !" << endl;
	wcout << L"SET 3 - BUCKET COUNT [" << Set3.bucket_count() << L"] !" << endl;
	wcout << L"SET 3 - MAX BUCKET COUNT [" << Set3.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 3 - LOAD FACTOR [" << Set3.load_factor() << L"] !" << endl;
	wcout << L"SET 3 - MAX LOAD FACTOR [" << Set3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_set<int,size_t(*)(int)>							Set4(2,OddEvenHash);

	Set4.max_load_factor(5);

	Set4.insert(0);
	Set4.insert(1);
	Set4.insert(2);
	Set4.insert(3);
	Set4.insert(4);
	Set4.insert(5);
	Set4.insert(6);
	Set4.insert(7);
	Set4.insert(8);
	Set4.insert(9);

	PrintCollection(L"SET 4",Set4);

	wcout << L"SET 4 - SIZE [" << Set4.size() << L"] !" << endl;
	wcout << L"SET 4 - BUCKET COUNT [" << Set4.bucket_count() << L"] !" << endl;
	wcout << L"SET 4 - MAX BUCKET COUNT [" << Set4.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 4 - LOAD FACTOR [" << Set4.load_factor() << L"] !" << endl;
	wcout << L"SET 4 - MAX LOAD FACTOR [" << Set4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Set4.insert(Index);
	}

	wcout << L"SET 4 - SIZE [" << Set4.size() << L"] !" << endl;
	wcout << L"SET 4 - BUCKET COUNT [" << Set4.bucket_count() << L"] !" << endl;
	wcout << L"SET 4 - MAX BUCKET COUNT [" << Set4.max_bucket_count() << L"] !" << endl;
	wcout << L"SET 4 - LOAD FACTOR [" << Set4.load_factor() << L"] !" << endl;
	wcout << L"SET 4 - MAX LOAD FACTOR [" << Set4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetCustomHash1(void)
{
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet1;

	MultiSet1.insert(0);
	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(4);
	MultiSet1.insert(5);
	MultiSet1.insert(6);
	MultiSet1.insert(7);
	MultiSet1.insert(8);
	MultiSet1.insert(9);

	PrintCollection(L"MULTISET 1",MultiSet1);

	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX BUCKET COUNT [" << MultiSet1.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiSet1.insert(Index);
	}

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiSet1.insert(Index);
	}

	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX BUCKET COUNT [" << MultiSet1.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet2;

	MultiSet2.max_load_factor(5);

	MultiSet2.insert(0);
	MultiSet2.insert(1);
	MultiSet2.insert(2);
	MultiSet2.insert(3);
	MultiSet2.insert(4);
	MultiSet2.insert(5);
	MultiSet2.insert(6);
	MultiSet2.insert(7);
	MultiSet2.insert(8);
	MultiSet2.insert(9);

	PrintCollection(L"MULTISET 2",MultiSet2);

	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX BUCKET COUNT [" << MultiSet2.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX LOAD FACTOR [" << MultiSet2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiSet2.insert(Index);
	}

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiSet2.insert(Index);
	}

	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX BUCKET COUNT [" << MultiSet2.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX LOAD FACTOR [" << MultiSet2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_multiset<int,size_t(*)(int)>						MultiSet3(2,OddEvenHash);

	MultiSet3.insert(0);
	MultiSet3.insert(1);
	MultiSet3.insert(2);
	MultiSet3.insert(3);
	MultiSet3.insert(4);
	MultiSet3.insert(5);
	MultiSet3.insert(6);
	MultiSet3.insert(7);
	MultiSet3.insert(8);
	MultiSet3.insert(9);

	PrintCollection(L"MULTISET 3",MultiSet3);

	wcout << L"MULTISET 3 - SIZE [" << MultiSet3.size() << L"] !" << endl;
	wcout << L"MULTISET 3 - BUCKET COUNT [" << MultiSet3.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 3 - MAX BUCKET COUNT [" << MultiSet3.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 3 - LOAD FACTOR [" << MultiSet3.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 3 - MAX LOAD FACTOR [" << MultiSet3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiSet3.insert(Index);
	}

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiSet3.insert(Index);
	}

	wcout << L"MULTISET 3 - SIZE [" << MultiSet3.size() << L"] !" << endl;
	wcout << L"MULTISET 3 - BUCKET COUNT [" << MultiSet3.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 3 - MAX BUCKET COUNT [" << MultiSet3.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 3 - LOAD FACTOR [" << MultiSet3.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 3 - MAX LOAD FACTOR [" << MultiSet3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_multiset<int,size_t(*)(int)>						MultiSet4(2,OddEvenHash);

	MultiSet4.max_load_factor(5);

	MultiSet4.insert(0);
	MultiSet4.insert(1);
	MultiSet4.insert(2);
	MultiSet4.insert(3);
	MultiSet4.insert(4);
	MultiSet4.insert(5);
	MultiSet4.insert(6);
	MultiSet4.insert(7);
	MultiSet4.insert(8);
	MultiSet4.insert(9);

	PrintCollection(L"MULTISET 4",MultiSet4);

	wcout << L"MULTISET 4 - SIZE [" << MultiSet4.size() << L"] !" << endl;
	wcout << L"MULTISET 4 - BUCKET COUNT [" << MultiSet4.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 4 - MAX BUCKET COUNT [" << MultiSet4.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 4 - LOAD FACTOR [" << MultiSet4.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 4 - MAX LOAD FACTOR [" << MultiSet4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiSet4.insert(Index);
	}

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiSet4.insert(Index);
	}

	wcout << L"MULTISET 4 - SIZE [" << MultiSet4.size() << L"] !" << endl;
	wcout << L"MULTISET 4 - BUCKET COUNT [" << MultiSet4.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 4 - MAX BUCKET COUNT [" << MultiSet4.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 4 - LOAD FACTOR [" << MultiSet4.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 4 - MAX LOAD FACTOR [" << MultiSet4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapCustomHash1(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map1;

	Map1.insert(pair<int,int>(0,0));
	Map1.insert(pair<int,int>(1,1));
	Map1.insert(pair<int,int>(2,2));
	Map1.insert(pair<int,int>(3,3));
	Map1.insert(pair<int,int>(4,4));
	Map1.insert(pair<int,int>(5,5));
	Map1.insert(pair<int,int>(6,6));
	Map1.insert(pair<int,int>(7,7));
	Map1.insert(pair<int,int>(8,8));
	Map1.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 1",Map1);

	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - MAX BUCKET COUNT [" << Map1.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Map1.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - MAX BUCKET COUNT [" << Map1.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	unordered_map<int,int>										Map2;

	Map2.max_load_factor(5);

	Map2.insert(pair<int,int>(0,0));
	Map2.insert(pair<int,int>(1,1));
	Map2.insert(pair<int,int>(2,2));
	Map2.insert(pair<int,int>(3,3));
	Map2.insert(pair<int,int>(4,4));
	Map2.insert(pair<int,int>(5,5));
	Map2.insert(pair<int,int>(6,6));
	Map2.insert(pair<int,int>(7,7));
	Map2.insert(pair<int,int>(8,8));
	Map2.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 2",Map2);

	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - MAX BUCKET COUNT [" << Map2.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - LOAD FACTOR [" << Map2.load_factor() << L"] !" << endl;
	wcout << L"MAP 2 - MAX LOAD FACTOR [" << Map2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Map2.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - MAX BUCKET COUNT [" << Map2.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - LOAD FACTOR [" << Map2.load_factor() << L"] !" << endl;
	wcout << L"MAP 2 - MAX LOAD FACTOR [" << Map2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_map<int,int,size_t(*)(int)>						Map3(2,OddEvenHash);

	Map3.insert(pair<int,int>(0,0));
	Map3.insert(pair<int,int>(1,1));
	Map3.insert(pair<int,int>(2,2));
	Map3.insert(pair<int,int>(3,3));
	Map3.insert(pair<int,int>(4,4));
	Map3.insert(pair<int,int>(5,5));
	Map3.insert(pair<int,int>(6,6));
	Map3.insert(pair<int,int>(7,7));
	Map3.insert(pair<int,int>(8,8));
	Map3.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 3",Map3);

	wcout << L"MAP 3 - SIZE [" << Map3.size() << L"] !" << endl;
	wcout << L"MAP 3 - BUCKET COUNT [" << Map3.bucket_count() << L"] !" << endl;
	wcout << L"MAP 3 - MAX BUCKET COUNT [" << Map3.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 3 - LOAD FACTOR [" << Map3.load_factor() << L"] !" << endl;
	wcout << L"MAP 3 - MAX LOAD FACTOR [" << Map3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Map3.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MAP 3 - SIZE [" << Map3.size() << L"] !" << endl;
	wcout << L"MAP 3 - BUCKET COUNT [" << Map3.bucket_count() << L"] !" << endl;
	wcout << L"MAP 3 - MAX BUCKET COUNT [" << Map3.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 3 - LOAD FACTOR [" << Map3.load_factor() << L"] !" << endl;
	wcout << L"MAP 3 - MAX LOAD FACTOR [" << Map3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_map<int,int,size_t(*)(int)>						Map4(2,OddEvenHash);

	Map4.max_load_factor(5);

	Map4.insert(pair<int,int>(0,0));
	Map4.insert(pair<int,int>(1,1));
	Map4.insert(pair<int,int>(2,2));
	Map4.insert(pair<int,int>(3,3));
	Map4.insert(pair<int,int>(4,4));
	Map4.insert(pair<int,int>(5,5));
	Map4.insert(pair<int,int>(6,6));
	Map4.insert(pair<int,int>(7,7));
	Map4.insert(pair<int,int>(8,8));
	Map4.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 4",Map4);

	wcout << L"MAP 4 - SIZE [" << Map4.size() << L"] !" << endl;
	wcout << L"MAP 4 - BUCKET COUNT [" << Map4.bucket_count() << L"] !" << endl;
	wcout << L"MAP 4 - MAX BUCKET COUNT [" << Map4.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 4 - LOAD FACTOR [" << Map4.load_factor() << L"] !" << endl;
	wcout << L"MAP 4 - MAX LOAD FACTOR [" << Map4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		Map4.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MAP 4 - SIZE [" << Map4.size() << L"] !" << endl;
	wcout << L"MAP 4 - BUCKET COUNT [" << Map4.bucket_count() << L"] !" << endl;
	wcout << L"MAP 4 - MAX BUCKET COUNT [" << Map4.max_bucket_count() << L"] !" << endl;
	wcout << L"MAP 4 - LOAD FACTOR [" << Map4.load_factor() << L"] !" << endl;
	wcout << L"MAP 4 - MAX LOAD FACTOR [" << Map4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapCustomHash1(void)
{
	PrintLineSeparator();

	unordered_multimap<int,int>									MultiMap1;

	MultiMap1.insert(pair<int,int>(0,0));
	MultiMap1.insert(pair<int,int>(1,1));
	MultiMap1.insert(pair<int,int>(2,2));
	MultiMap1.insert(pair<int,int>(3,3));
	MultiMap1.insert(pair<int,int>(4,4));
	MultiMap1.insert(pair<int,int>(5,5));
	MultiMap1.insert(pair<int,int>(6,6));
	MultiMap1.insert(pair<int,int>(7,7));
	MultiMap1.insert(pair<int,int>(8,8));
	MultiMap1.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX BUCKET COUNT [" << MultiMap1.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiMap1.insert(pair<int,int>(Index,Index));
	}

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiMap1.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX BUCKET COUNT [" << MultiMap1.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	unordered_multimap<int,int>									MultiMap2;

	MultiMap2.max_load_factor(5);

	MultiMap2.insert(pair<int,int>(0,0));
	MultiMap2.insert(pair<int,int>(1,1));
	MultiMap2.insert(pair<int,int>(2,2));
	MultiMap2.insert(pair<int,int>(3,3));
	MultiMap2.insert(pair<int,int>(4,4));
	MultiMap2.insert(pair<int,int>(5,5));
	MultiMap2.insert(pair<int,int>(6,6));
	MultiMap2.insert(pair<int,int>(7,7));
	MultiMap2.insert(pair<int,int>(8,8));
	MultiMap2.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 2",MultiMap2);

	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX BUCKET COUNT [" << MultiMap2.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX LOAD FACTOR [" << MultiMap2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiMap2.insert(pair<int,int>(Index,Index));
	}

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiMap2.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX BUCKET COUNT [" << MultiMap2.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX LOAD FACTOR [" << MultiMap2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_multimap<int,int,size_t(*)(int)>					MultiMap3(2,OddEvenHash);

	MultiMap3.insert(pair<int,int>(0,0));
	MultiMap3.insert(pair<int,int>(1,1));
	MultiMap3.insert(pair<int,int>(2,2));
	MultiMap3.insert(pair<int,int>(3,3));
	MultiMap3.insert(pair<int,int>(4,4));
	MultiMap3.insert(pair<int,int>(5,5));
	MultiMap3.insert(pair<int,int>(6,6));
	MultiMap3.insert(pair<int,int>(7,7));
	MultiMap3.insert(pair<int,int>(8,8));
	MultiMap3.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 3",MultiMap3);

	wcout << L"MULTIMAP 3 - SIZE [" << MultiMap3.size() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - BUCKET COUNT [" << MultiMap3.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - MAX BUCKET COUNT [" << MultiMap3.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - LOAD FACTOR [" << MultiMap3.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - MAX LOAD FACTOR [" << MultiMap3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiMap3.insert(pair<int,int>(Index,Index));
	}

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiMap3.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 3 - SIZE [" << MultiMap3.size() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - BUCKET COUNT [" << MultiMap3.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - MAX BUCKET COUNT [" << MultiMap3.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - LOAD FACTOR [" << MultiMap3.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - MAX LOAD FACTOR [" << MultiMap3.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	unordered_multimap<int,int,size_t(*)(int)>					MultiMap4(2,OddEvenHash);

	MultiMap4.max_load_factor(5);

	MultiMap4.insert(pair<int,int>(0,0));
	MultiMap4.insert(pair<int,int>(1,1));
	MultiMap4.insert(pair<int,int>(2,2));
	MultiMap4.insert(pair<int,int>(3,3));
	MultiMap4.insert(pair<int,int>(4,4));
	MultiMap4.insert(pair<int,int>(5,5));
	MultiMap4.insert(pair<int,int>(6,6));
	MultiMap4.insert(pair<int,int>(7,7));
	MultiMap4.insert(pair<int,int>(8,8));
	MultiMap4.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 4",MultiMap4);

	wcout << L"MULTIMAP 4 - SIZE [" << MultiMap4.size() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - BUCKET COUNT [" << MultiMap4.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - MAX BUCKET COUNT [" << MultiMap4.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - LOAD FACTOR [" << MultiMap4.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - MAX LOAD FACTOR [" << MultiMap4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	for(int Index=10;Index<1000;Index++)
	{
		MultiMap4.insert(pair<int,int>(Index,Index));
	}

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<1000;Index++)
	{
		MultiMap4.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 4 - SIZE [" << MultiMap4.size() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - BUCKET COUNT [" << MultiMap4.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - MAX BUCKET COUNT [" << MultiMap4.max_bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - LOAD FACTOR [" << MultiMap4.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 4 - MAX LOAD FACTOR [" << MultiMap4.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetCustomHash2(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	Set1.insert(0);
	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);
	Set1.insert(5);
	Set1.insert(6);
	Set1.insert(7);
	Set1.insert(8);
	Set1.insert(9);

	PrintCollection(L"SET 1",Set1);

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Set1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	unordered_set<int,COddEvenHash>								Set2;

	Set2.insert(0);
	Set2.insert(1);
	Set2.insert(2);
	Set2.insert(3);
	Set2.insert(4);
	Set2.insert(5);
	Set2.insert(6);
	Set2.insert(7);
	Set2.insert(8);
	Set2.insert(9);

	PrintCollection(L"SET 2",Set2);

	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Set2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetCustomHash2(void)
{
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet1;

	MultiSet1.insert(0);
	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(4);
	MultiSet1.insert(5);
	MultiSet1.insert(6);
	MultiSet1.insert(7);
	MultiSet1.insert(8);
	MultiSet1.insert(9);

	PrintCollection(L"MULTISET 1",MultiSet1);

	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiSet1.insert(Index);
	}

	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiSet1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	unordered_multiset<int,COddEvenHash>						MultiSet2;

	MultiSet2.insert(0);
	MultiSet2.insert(1);
	MultiSet2.insert(2);
	MultiSet2.insert(3);
	MultiSet2.insert(4);
	MultiSet2.insert(5);
	MultiSet2.insert(6);
	MultiSet2.insert(7);
	MultiSet2.insert(8);
	MultiSet2.insert(9);

	PrintCollection(L"MULTISET 2",MultiSet2);

	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX LOAD FACTOR [" << MultiSet2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiSet2.insert(Index);
	}

	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX LOAD FACTOR [" << MultiSet2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiSet2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapCustomHash2(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map1;

	Map1.insert(pair<int,int>(0,0));
	Map1.insert(pair<int,int>(1,1));
	Map1.insert(pair<int,int>(2,2));
	Map1.insert(pair<int,int>(3,3));
	Map1.insert(pair<int,int>(4,4));
	Map1.insert(pair<int,int>(5,5));
	Map1.insert(pair<int,int>(6,6));
	Map1.insert(pair<int,int>(7,7));
	Map1.insert(pair<int,int>(8,8));
	Map1.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 1",Map1);

	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Map1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	unordered_map<int,int,COddEvenHash>							Map2;

	Map2.insert(pair<int,int>(0,0));
	Map2.insert(pair<int,int>(1,1));
	Map2.insert(pair<int,int>(2,2));
	Map2.insert(pair<int,int>(3,3));
	Map2.insert(pair<int,int>(4,4));
	Map2.insert(pair<int,int>(5,5));
	Map2.insert(pair<int,int>(6,6));
	Map2.insert(pair<int,int>(7,7));
	Map2.insert(pair<int,int>(8,8));
	Map2.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 2",Map2);

	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - LOAD FACTOR [" << Map2.load_factor() << L"] !" << endl;
	wcout << L"MAP 2 - MAX LOAD FACTOR [" << Map2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Map2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapCustomHash2(void)
{
	PrintLineSeparator();

	unordered_multimap<int,int>									MultiMap1;

	MultiMap1.insert(pair<int,int>(0,0));
	MultiMap1.insert(pair<int,int>(1,1));
	MultiMap1.insert(pair<int,int>(2,2));
	MultiMap1.insert(pair<int,int>(3,3));
	MultiMap1.insert(pair<int,int>(4,4));
	MultiMap1.insert(pair<int,int>(5,5));
	MultiMap1.insert(pair<int,int>(6,6));
	MultiMap1.insert(pair<int,int>(7,7));
	MultiMap1.insert(pair<int,int>(8,8));
	MultiMap1.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiMap1.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiMap1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	unordered_multimap<int,int,COddEvenHash>					MultiMap2;

	MultiMap2.insert(pair<int,int>(0,0));
	MultiMap2.insert(pair<int,int>(1,1));
	MultiMap2.insert(pair<int,int>(2,2));
	MultiMap2.insert(pair<int,int>(3,3));
	MultiMap2.insert(pair<int,int>(4,4));
	MultiMap2.insert(pair<int,int>(5,5));
	MultiMap2.insert(pair<int,int>(6,6));
	MultiMap2.insert(pair<int,int>(7,7));
	MultiMap2.insert(pair<int,int>(8,8));
	MultiMap2.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 2",MultiMap2);

	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX LOAD FACTOR [" << MultiMap2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiMap2.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX LOAD FACTOR [" << MultiMap2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiMap2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetCustomHashAndEquatableFunctions(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	Set1.insert(0);
	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);
	Set1.insert(5);
	Set1.insert(6);
	Set1.insert(7);
	Set1.insert(8);
	Set1.insert(9);

	PrintCollection(L"SET 1",Set1);

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - LOAD FACTOR [" << Set1.load_factor() << L"] !" << endl;
	wcout << L"SET 1 - MAX LOAD FACTOR [" << Set1.max_load_factor() << L"] !" << endl;

	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Set1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	// !!! Pouziva sa CUSTOM EQUATABLE FUNCTION.
	unordered_set<int,COddEvenHash,CCustomEqual<int>>			Set2;

	Set2.insert(0);
	Set2.insert(1);
	Set2.insert(2);
	Set2.insert(3);
	Set2.insert(4);
	Set2.insert(5);
	Set2.insert(6);
	Set2.insert(7);
	Set2.insert(8);
	Set2.insert(9);

	PrintCollection(L"SET 2",Set2);

	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - LOAD FACTOR [" << Set2.load_factor() << L"] !" << endl;
	wcout << L"SET 2 - MAX LOAD FACTOR [" << Set2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Set2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetCustomHashAndEquatableFunctions(void)
{
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet1;

	MultiSet1.insert(0);
	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(4);
	MultiSet1.insert(5);
	MultiSet1.insert(6);
	MultiSet1.insert(7);
	MultiSet1.insert(8);
	MultiSet1.insert(9);

	PrintCollection(L"MULTISET 1",MultiSet1);

	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiSet1.insert(Index);
	}

	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - LOAD FACTOR [" << MultiSet1.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX LOAD FACTOR [" << MultiSet1.max_load_factor() << L"] !" << endl;

	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiSet1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	// !!! Pouziva sa CUSTOM EQUATABLE FUNCTION.
	unordered_multiset<int,COddEvenHash,CCustomEqual<int>>		MultiSet2;

	MultiSet2.insert(0);
	MultiSet2.insert(1);
	MultiSet2.insert(2);
	MultiSet2.insert(3);
	MultiSet2.insert(4);
	MultiSet2.insert(5);
	MultiSet2.insert(6);
	MultiSet2.insert(7);
	MultiSet2.insert(8);
	MultiSet2.insert(9);

	PrintCollection(L"MULTISET 2",MultiSet2);

	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX LOAD FACTOR [" << MultiSet2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTISET umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiSet2.insert(Index);
	}

	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - LOAD FACTOR [" << MultiSet2.load_factor() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX LOAD FACTOR [" << MultiSet2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiSet2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapCustomHashAndEquatableFunctions(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map1;

	Map1.insert(pair<int,int>(0,0));
	Map1.insert(pair<int,int>(1,1));
	Map1.insert(pair<int,int>(2,2));
	Map1.insert(pair<int,int>(3,3));
	Map1.insert(pair<int,int>(4,4));
	Map1.insert(pair<int,int>(5,5));
	Map1.insert(pair<int,int>(6,6));
	Map1.insert(pair<int,int>(7,7));
	Map1.insert(pair<int,int>(8,8));
	Map1.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 1",Map1);

	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - LOAD FACTOR [" << Map1.load_factor() << L"] !" << endl;
	wcout << L"MAP 1 - MAX LOAD FACTOR [" << Map1.max_load_factor() << L"] !" << endl;

	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Map1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	// !!! Pouziva sa CUSTOM EQUATABLE FUNCTION.
	unordered_map<int,int,COddEvenHash,CCustomEqual<int>>		Map2;

	Map2.insert(pair<int,int>(0,0));
	Map2.insert(pair<int,int>(1,1));
	Map2.insert(pair<int,int>(2,2));
	Map2.insert(pair<int,int>(3,3));
	Map2.insert(pair<int,int>(4,4));
	Map2.insert(pair<int,int>(5,5));
	Map2.insert(pair<int,int>(6,6));
	Map2.insert(pair<int,int>(7,7));
	Map2.insert(pair<int,int>(8,8));
	Map2.insert(pair<int,int>(9,9));

	PrintUnorderedMap(L"MAP 2",Map2);

	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - LOAD FACTOR [" << Map2.load_factor() << L"] !" << endl;
	wcout << L"MAP 2 - MAX LOAD FACTOR [" << Map2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << Map2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapCustomHashAndEquatableFunctions(void)
{
	PrintLineSeparator();

	unordered_multimap<int,int>									MultiMap1;

	MultiMap1.insert(pair<int,int>(0,0));
	MultiMap1.insert(pair<int,int>(1,1));
	MultiMap1.insert(pair<int,int>(2,2));
	MultiMap1.insert(pair<int,int>(3,3));
	MultiMap1.insert(pair<int,int>(4,4));
	MultiMap1.insert(pair<int,int>(5,5));
	MultiMap1.insert(pair<int,int>(6,6));
	MultiMap1.insert(pair<int,int>(7,7));
	MultiMap1.insert(pair<int,int>(8,8));
	MultiMap1.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiMap1.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - LOAD FACTOR [" << MultiMap1.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX LOAD FACTOR [" << MultiMap1.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiMap1.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
	PrintLineSeparator();
	PrintLineSeparator();

	// !!! Pouziva sa EXTREMNE ZLA HASH FUNCTION, ktora vracia iba 2 HASH VALUES.
	// !!! Pouziva sa CUSTOM EQUATABLE FUNCTION.
	unordered_multimap<int,int,COddEvenHash,CCustomEqual<int>>	MultiMap2;

	MultiMap2.insert(pair<int,int>(0,0));
	MultiMap2.insert(pair<int,int>(1,1));
	MultiMap2.insert(pair<int,int>(2,2));
	MultiMap2.insert(pair<int,int>(3,3));
	MultiMap2.insert(pair<int,int>(4,4));
	MultiMap2.insert(pair<int,int>(5,5));
	MultiMap2.insert(pair<int,int>(6,6));
	MultiMap2.insert(pair<int,int>(7,7));
	MultiMap2.insert(pair<int,int>(8,8));
	MultiMap2.insert(pair<int,int>(9,9));

	PrintUnorderedMultiMap(L"MULTIMAP 2",MultiMap2);

	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX LOAD FACTOR [" << MultiMap2.max_load_factor() << L"] !" << endl;

	PrintLineSeparator();

	// MULTIMAP umoznuje ulozenie rovnakych ITEMS.
	for(int Index=0;Index<10;Index++)
	{
		MultiMap2.insert(pair<int,int>(Index,Index));
	}

	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - LOAD FACTOR [" << MultiMap2.load_factor() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX LOAD FACTOR [" << MultiMap2.max_load_factor() << L"] !" << endl;

	// !!!!! Aj napriek tomu, ze HASH FUNCTION vracia iba 2 VALUES a teda ITEMS su realne zaradene iba do 2 BUCKETS, COLLECTION obsahuje ovela viac BUCKETS, ktore su vsak PRAZDNE.
	for(int Index=0;Index<10;Index++)
	{
		wcout << L"ITEM [" << Index << L"] - BUCKET [" << MultiMap2.bucket(Index) << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetCompare(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);

	unordered_set<int>											Set2;

	Set2=Set1;

	unordered_set<int>											Set3;

	Set3.insert(1);
	Set3.insert(2);
	Set3.insert(4);

	PrintCollection(L"SET 1",Set1);
	PrintCollection(L"SET 2",Set2);
	PrintCollection(L"SET 3",Set3);

	PrintLineSeparator();

	wcout << L"SET 1 == SET 2 [" << (Set1==Set2) << L"] !" << endl;
	wcout << L"SET 1 == SET 3 [" << (Set1==Set3) << L"] !" << endl;
	wcout << L"SET 1 == SET 2 [" << (Set1!=Set2) << L"] !" << endl;
	wcout << L"SET 1 == SET 3 [" << (Set1!=Set3) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SET 1 - SIZE [" << Set1.size() << L"] !" << endl;
	wcout << L"SET 1 - MAX SIZE [" << Set1.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SET 2 - SIZE [" << Set2.size() << L"] !" << endl;
	wcout << L"SET 2 - MAX SIZE [" << Set2.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"SET 3 - SIZE [" << Set3.size() << L"] !" << endl;
	wcout << L"SET 3 - MAX SIZE [" << Set3.max_size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetCompare(void)
{
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet1;

	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(3);

	unordered_multiset<int>										MultiSet2;

	MultiSet2=MultiSet1;

	unordered_multiset<int>										MultiSet3;

	MultiSet3.insert(1);
	MultiSet3.insert(2);
	MultiSet3.insert(3);
	MultiSet3.insert(4);

	PrintCollection(L"MULTISET 1",MultiSet1);
	PrintCollection(L"MULTISET 2",MultiSet2);
	PrintCollection(L"MULTISET 3",MultiSet3);

	PrintLineSeparator();

	wcout << L"MULTISET 1 == MULTISET 2 [" << (MultiSet1==MultiSet2) << L"] !" << endl;
	wcout << L"MULTISET 1 == MULTISET 3 [" << (MultiSet1==MultiSet3) << L"] !" << endl;
	wcout << L"MULTISET 1 == MULTISET 2 [" << (MultiSet1!=MultiSet2) << L"] !" << endl;
	wcout << L"MULTISET 1 == MULTISET 3 [" << (MultiSet1!=MultiSet3) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MULTISET 1 - SIZE [" << MultiSet1.size() << L"] !" << endl;
	wcout << L"MULTISET 1 - MAX SIZE [" << MultiSet1.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MULTISET 2 - SIZE [" << MultiSet2.size() << L"] !" << endl;
	wcout << L"MULTISET 2 - MAX SIZE [" << MultiSet2.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MULTISET 3 - SIZE [" << MultiSet3.size() << L"] !" << endl;
	wcout << L"MULTISET 3 - MAX SIZE [" << MultiSet3.max_size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapCompare(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map1;

	Map1.insert(pair<int,int>(1,1));
	Map1.insert(pair<int,int>(2,2));
	Map1.insert(pair<int,int>(3,3));

	unordered_map<int,int>										Map2;

	Map2=Map1;

	unordered_map<int,int>										Map3;

	Map3.insert(pair<int,int>(1,1));
	Map3.insert(pair<int,int>(2,2));
	Map3.insert(pair<int,int>(3,4));

	PrintUnorderedMap(L"MAP 1",Map1);
	PrintUnorderedMap(L"MAP 2",Map2);
	PrintUnorderedMap(L"MAP 3",Map3);

	PrintLineSeparator();

	wcout << L"MAP 1 == MAP 2 [" << (Map1==Map2) << L"] !" << endl;
	wcout << L"MAP 1 == MAP 3 [" << (Map1==Map3) << L"] !" << endl;
	wcout << L"MAP 1 == MAP 2 [" << (Map1!=Map2) << L"] !" << endl;
	wcout << L"MAP 1 == MAP 3 [" << (Map1!=Map3) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MAP 1 - SIZE [" << Map1.size() << L"] !" << endl;
	wcout << L"MAP 1 - MAX SIZE [" << Map1.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MAP 2 - SIZE [" << Map2.size() << L"] !" << endl;
	wcout << L"MAP 2 - MAX SIZE [" << Map2.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MAP 3 - SIZE [" << Map3.size() << L"] !" << endl;
	wcout << L"MAP 3 - MAX SIZE [" << Map3.max_size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapCompare(void)
{
	PrintLineSeparator();

	unordered_multimap<int,int>									MultiMap1;

	MultiMap1.insert(pair<int,int>(1,1));
	MultiMap1.insert(pair<int,int>(2,2));
	MultiMap1.insert(pair<int,int>(3,3));
	MultiMap1.insert(pair<int,int>(3,4));

	unordered_multimap<int,int>									MultiMap2;

	MultiMap2=MultiMap1;

	unordered_multimap<int,int>									MultiMap3;

	MultiMap3.insert(pair<int,int>(1,1));
	MultiMap3.insert(pair<int,int>(2,2));
	MultiMap3.insert(pair<int,int>(3,3));
	MultiMap3.insert(pair<int,int>(3,5));

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);
	PrintUnorderedMultiMap(L"MULTIMAP 2",MultiMap2);
	PrintUnorderedMultiMap(L"MULTIMAP 3",MultiMap3);

	PrintLineSeparator();

	wcout << L"MULTIMAP 1 == MULTIMAP 2 [" << (MultiMap1==MultiMap2) << L"] !" << endl;
	wcout << L"MULTIMAP 1 == MULTIMAP 3 [" << (MultiMap1==MultiMap3) << L"] !" << endl;
	wcout << L"MULTIMAP 1 == MULTIMAP 2 [" << (MultiMap1!=MultiMap2) << L"] !" << endl;
	wcout << L"MULTIMAP 1 == MULTIMAP 3 [" << (MultiMap1!=MultiMap3) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MULTIMAP 1 - SIZE [" << MultiMap1.size() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - MAX SIZE [" << MultiMap1.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MULTIMAP 2 - SIZE [" << MultiMap2.size() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - MAX SIZE [" << MultiMap2.max_size() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MULTIMAP 3 - SIZE [" << MultiMap3.size() << L"] !" << endl;
	wcout << L"MULTIMAP 3 - MAX SIZE [" << MultiMap3.max_size() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetSearch(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set;
	
	Set.insert(1);
	Set.insert(2);
	Set.insert(3);

	PrintCollection(L"SET",Set);

	PrintLineSeparator();

	wcout << L"SET - COUNT(1) [" << Set.count(1) << L"] !" << endl;
	wcout << L"SET - COUNT(10) [" << Set.count(10) << L"] !" << endl;
	wcout << L"SET - FIND(1) [" << ((Set.find(1)!=Set.cend()) ? L"VALUE 1 FOUND" : L"VALUE 1 NOT FOUND") << L"] !" << endl;
	wcout << L"SET - FIND(10) [" << ((Set.find(10)!=Set.cend()) ? L"VALUE 10 FOUND" : L"VALUE 10 NOT FOUND") << L"] !" << endl;

	using														SetIteratorPair=pair<unordered_set<int>::const_iterator,unordered_set<int>::const_iterator>;

	// !!! Kedze ITEMS su UNORDERED, pozicie oboch ITERATORS su zavisle na implementacii UNORDERED SET.
	SetIteratorPair												IteratorPair=Set.equal_range(2);

	PrintUnorderedSetIterator(L"SET - EQUAL_BOUND(2).FIRST -",Set,IteratorPair.first);
	PrintUnorderedSetIterator(L"SET - EQUAL_BOUND(2).SECOND -",Set,IteratorPair.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetSearch(void)
{
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet;

	MultiSet.insert(1);
	MultiSet.insert(1);
	MultiSet.insert(2);
	MultiSet.insert(2);
	MultiSet.insert(2);
	MultiSet.insert(3);
	MultiSet.insert(3);

	PrintCollection(L"MULTISET",MultiSet);

	PrintLineSeparator();

	wcout << L"MULTISET - COUNT(2) [" << MultiSet.count(2) << L"] !" << endl;
	wcout << L"MULTISET - COUNT(10) [" << MultiSet.count(10) << L"] !" << endl;
	wcout << L"MULTISET - FIND(2) [" << ((MultiSet.find(2)!=MultiSet.cend()) ? L"VALUE 2 FOUND" : L"VALUE 2 NOT FOUND") << L"] !" << endl;
	wcout << L"MULTISET - FIND(10) [" << ((MultiSet.find(10)!=MultiSet.cend()) ? L"VALUE 10 FOUND" : L"VALUE 10 NOT FOUND") << L"] !" << endl;

	// !!! Kedze ITEMS su UNORDERED, pozicie oboch ITERATORS su zavisle na implementacii UNORDERED MULTISET.
	using														MultiSetIteratorPair=pair<unordered_multiset<int>::const_iterator,unordered_multiset<int>::const_iterator>;

	MultiSetIteratorPair										IteratorPair=MultiSet.equal_range(2);

	PrintUnorderedMultiSetIterator(L"MULTISET - EQUAL_BOUND(2).FIRST -",MultiSet,IteratorPair.first);
	PrintUnorderedMultiSetIterator(L"MULTISET - EQUAL_BOUND(2).SECOND -",MultiSet,IteratorPair.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapSearch(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map;

	Map.insert(pair<int,int>(1,1));
	Map.insert(pair<int,int>(2,2));
	Map.insert(pair<int,int>(3,3));

	PrintUnorderedMap(L"MAP",Map);

	PrintLineSeparator();

	wcout << L"MAP - COUNT(1) [" << Map.count(1) << L"] !" << endl;
	wcout << L"MAP - COUNT(10) [" << Map.count(10) << L"] !" << endl;
	wcout << L"MAP - FIND(1) [" << ((Map.find(1)!=Map.cend()) ? L"VALUE 1 FOUND" : L"VALUE 1 NOT FOUND") << L"] !" << endl;
	wcout << L"MAP - FIND(10) [" << ((Map.find(10)!=Map.cend()) ? L"VALUE 10 FOUND" : L"VALUE 10 NOT FOUND") << L"] !" << endl;

	using														MapIteratorPair=pair<unordered_map<int,int>::const_iterator,unordered_map<int,int>::const_iterator>;

	// !!! Kedze ITEMS su UNORDERED, pozicie oboch ITERATORS su zavisle na implementacii UNORDERED MAP.
	MapIteratorPair												IteratorPair=Map.equal_range(2);

	PrintUnorderedMapIterator(L"MAP - EQUAL_BOUND(2).FIRST -",Map,IteratorPair.first);
	PrintUnorderedMapIterator(L"MAP - EQUAL_BOUND(2).SECOND -",Map,IteratorPair.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapSearch(void)
{
	PrintLineSeparator();

	unordered_multimap<int,int>									MultiMap;

	MultiMap.insert(pair<int,int>(1,1));
	MultiMap.insert(pair<int,int>(2,2));
	MultiMap.insert(pair<int,int>(2,3));
	MultiMap.insert(pair<int,int>(2,4));
	MultiMap.insert(pair<int,int>(3,3));

	PrintUnorderedMultiMap(L"MULTIMAP",MultiMap);

	PrintLineSeparator();

	wcout << L"MULTIMAP - COUNT(2) [" << MultiMap.count(2) << L"] !" << endl;
	wcout << L"MULTIMAP - COUNT(10) [" << MultiMap.count(10) << L"] !" << endl;
	wcout << L"MULTIMAP - FIND(2) [" << ((MultiMap.find(2)!=MultiMap.cend()) ? L"VALUE 2 FOUND" : L"VALUE 2 NOT FOUND") << L"] !" << endl;
	wcout << L"MULTIMAP - FIND(10) [" << ((MultiMap.find(10)!=MultiMap.cend()) ? L"VALUE 10 FOUND" : L"VALUE 10 NOT FOUND") << L"] !" << endl;

	using														MultiMapIteratorPair=pair<unordered_multimap<int,int>::const_iterator,unordered_multimap<int,int>::const_iterator>;

	// !!! Kedze ITEMS su UNORDERED, pozicie oboch ITERATORS su zavisle na implementacii UNORDERED MULTIMAP.
	MultiMapIteratorPair										IteratorPair=MultiMap.equal_range(2);

	PrintUnorderedMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(2).FIRST -",MultiMap,IteratorPair.first);
	PrintUnorderedMultiMapIterator(L"MULTIMAP - EQUAL_BOUND(2).SECOND -",MultiMap,IteratorPair.second);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetAssignment(void)
{
	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction1(10);
	CCustomEqualFunction<int>									CustomEqualFunction1(10);
	unordered_set<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	Set1(10,CustomHashFunction1,CustomEqualFunction1);

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);

	PrintCollection(L"SET 1",Set1);

	PrintLineSeparator();

	wcout << L"SET 1 [" << Set1.hash_function().GetValue() << L"] !" << endl;
	wcout << L"SET 1 [" << Set1.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction2(20);
	CCustomEqualFunction<int>									CustomEqualFunction2(20);
	unordered_set<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	Set2(10,CustomHashFunction2,CustomEqualFunction2);

	wcout << L"SET 2 [" << Set2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"SET 2 [" << Set2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pri pouziti OPERATOR= dochadza k presunu CUSTOM HASH FUNCTION a CUSTOM EQUATABLE FUNCTION.
	Set2=Set1;

	PrintCollection(L"SET 2",Set2);

	PrintLineSeparator();

	wcout << L"SET 2 [" << Set2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"SET 2 [" << Set2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetAssignment(void)
{
	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction1(10);
	CCustomEqualFunction<int>									CustomEqualFunction1(10);
	unordered_multiset<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	MultiSet1(10,CustomHashFunction1,CustomEqualFunction1);

	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(3);

	PrintCollection(L"MULTISET 1",MultiSet1);

	PrintLineSeparator();

	wcout << L"MULTISET 1 [" << MultiSet1.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MULTISET 1 [" << MultiSet1.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction2(20);
	CCustomEqualFunction<int>									CustomEqualFunction2(20);
	unordered_multiset<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	MultiSet2(10,CustomHashFunction2,CustomEqualFunction2);

	wcout << L"MULTISET 2 [" << MultiSet2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MULTISET 2 [" << MultiSet2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pri pouziti OPERATOR= dochadza k presunu CUSTOM HASH FUNCTION a CUSTOM EQUATABLE FUNCTION.
	MultiSet2=MultiSet1;

	PrintCollection(L"MULTISET 2",MultiSet2);

	PrintLineSeparator();

	wcout << L"MULTISET 2 [" << MultiSet2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MULTISET 2 [" << MultiSet2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapAssignment(void)
{
	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction1(10);
	CCustomEqualFunction<int>									CustomEqualFunction1(10);
	unordered_map<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	Map1(10,CustomHashFunction1,CustomEqualFunction1);

	Map1.insert(pair<int,int>(1,1));
	Map1.insert(pair<int,int>(2,2));
	Map1.insert(pair<int,int>(3,3));

	PrintUnorderedMap(L"MAP 1",Map1);

	PrintLineSeparator();

	wcout << L"MAP 1 [" << Map1.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MAP 1 [" << Map1.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction2(20);
	CCustomEqualFunction<int>									CustomEqualFunction2(20);
	unordered_map<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	Map2(10,CustomHashFunction2,CustomEqualFunction2);

	wcout << L"MAP 2 [" << Map2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MAP 2 [" << Map2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pri pouziti OPERATOR= dochadza k presunu CUSTOM HASH FUNCTION a CUSTOM EQUATABLE FUNCTION.
	Map2=Map1;

	PrintUnorderedMap(L"MAP 2",Map2);

	PrintLineSeparator();

	wcout << L"MAP 2 [" << Map2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MAP 2 [" << Map2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapAssignment(void)
{
	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction1(10);
	CCustomEqualFunction<int>									CustomEqualFunction1(10);
	unordered_multimap<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	MultiMap1(10,CustomHashFunction1,CustomEqualFunction1);

	MultiMap1.insert(pair<int,int>(1,1));
	MultiMap1.insert(pair<int,int>(2,2));
	MultiMap1.insert(pair<int,int>(3,3));
	MultiMap1.insert(pair<int,int>(3,4));

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	PrintLineSeparator();

	wcout << L"MULTIMAP 1 [" << MultiMap1.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MULTIMAP 1 [" << MultiMap1.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	CCustomHashFunction<int>									CustomHashFunction2(20);
	CCustomEqualFunction<int>									CustomEqualFunction2(20);
	unordered_multimap<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	MultiMap2(10,CustomHashFunction2,CustomEqualFunction2);

	wcout << L"MULTIMAP 2 [" << MultiMap2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MULTIMAP 2 [" << MultiMap2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pri pouziti OPERATOR= dochadza k presunu CUSTOM HASH FUNCTION a CUSTOM EQUATABLE FUNCTION.
	MultiMap2=MultiMap1;

	PrintUnorderedMultiMap(L"MULTIMAP 2",MultiMap2);

	PrintLineSeparator();

	wcout << L"MULTIMAP 2 [" << MultiMap2.hash_function().GetValue() << L"] !" << endl;
	wcout << L"MULTIMAP 2 [" << MultiMap2.key_eq().GetValue() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetInsertErase(void)
{
	PrintLineSeparator();

	vector<int>													Vector{11,12,13};
	unordered_set<int>											Set1;

	Set1.insert(1);
	Set1.insert({2,3});
	Set1.insert(Vector.cbegin(),Vector.cend());

	pair<unordered_set<int>::iterator,bool>						InsertResult=Set1.insert(1);

	// !!! VALUE 'second' obsahuje informaciu ci ITEM bol pridany do COLLECTION.
	if (InsertResult.second==true)
	{
		wcout << L"ITEM [" << (*InsertResult.first) << L"] ADDED to COLLECTION to BUCKET [" << Set1.bucket(*InsertResult.first) << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM [" << (*InsertResult.first) << L"] was NOT ADDED to COLLECTION !" << endl;
	}

	// Vola sa CONSTRUCTOR TYPU [int].
	Set1.emplace(5);

	PrintCollection(L"SET 1",Set1);

	size_t														NumberOfRemovedItems=Set1.erase(11);

	wcout << L"NUMBER of REMOVED ITEMS [" << NumberOfRemovedItems << L"] !" << endl;

	PrintCollection(L"SET 1",Set1);

	unordered_set<int>::const_iterator							Iterator1=Set1.cbegin();

	Iterator1++;

	unordered_set<int>::const_iterator							Iterator2=Iterator1;

	Iterator2++;
	Iterator2++;

	// Kedze ITEMS NIE SU SORTED, to ktore ITEMS budu odstranene zavisi od internej reprezentacie ITEMS v COLLECTION.
	Set1.erase(Iterator1,Iterator2);

	PrintCollection(L"SET 1",Set1);

	PrintLineSeparator();

	CUnorderedIntHashFunction									CustomHashFunction2(20);
	CUnorderedIntEqualFunction									CustomEqualFunction2(20);
	unordered_set<CUnorderedInt,CUnorderedIntHashFunction,CUnorderedIntEqualFunction>	Set2(10,CustomHashFunction2,CustomEqualFunction2);

	Set2.insert(CUnorderedInt(1));

	// Vola sa CONSTRUCTOR CLASS [CUnorderedInt].
	Set2.emplace(2);

	PrintCollection(L"SET 2",Set2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetInsertErase(void)
{
	PrintLineSeparator();

	vector<int>													Vector{11,12,13};
	unordered_multiset<int>										MultiSet1;

	MultiSet1.insert(1);
	MultiSet1.insert({2,3});
	MultiSet1.insert({2,3});
	MultiSet1.insert(Vector.cbegin(),Vector.cend());

	// Vola sa CONSTRUCTOR TYPU [int].
	MultiSet1.emplace(5);

	PrintCollection(L"MULTISET 1",MultiSet1);

	size_t														NumberOfRemovedItems=MultiSet1.erase(2);

	wcout << L"NUMBER of REMOVED ITEMS [" << NumberOfRemovedItems << L"] !" << endl;

	PrintCollection(L"MULTISET 1",MultiSet1);

	unordered_multiset<int>::const_iterator						Iterator1=MultiSet1.cbegin();

	Iterator1++;

	unordered_multiset<int>::const_iterator						Iterator2=Iterator1;

	Iterator2++;
	Iterator2++;

	// Kedze ITEMS NIE SU SORTED, to ktore ITEMS budu odstranene zavisi od internej reprezentacie ITEMS v COLLECTION.
	MultiSet1.erase(Iterator1,Iterator2);

	PrintCollection(L"MULTISET 1",MultiSet1);

	PrintLineSeparator();

	CUnorderedIntHashFunction									CustomHashFunction2(20);
	CUnorderedIntEqualFunction									CustomEqualFunction2(20);
	unordered_multiset<CUnorderedInt,CUnorderedIntHashFunction,CUnorderedIntEqualFunction>	MultiSet2(10,CustomHashFunction2,CustomEqualFunction2);

	MultiSet2.insert(CUnorderedInt(1));

	// Vola sa CONSTRUCTOR CLASS [CUnorderedInt].
	MultiSet2.emplace(2);

	PrintCollection(L"MULTISET 2",MultiSet2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapInsertErase(void)
{
	PrintLineSeparator();

	vector<pair<int,int>>										Vector{pair<int,int>(11,111),pair<int,int>(12,112),pair<int,int>(13,113)};
	unordered_map<int,int>										Map1;

	Map1.insert(pair<int,int>(1,101));
	Map1.insert({pair<int,int>(2,102),pair<int,int>(3,103)});
	Map1.insert(Vector.cbegin(),Vector.cend());

	pair<unordered_map<int,int>::iterator,bool>					InsertResult=Map1.insert(pair<int,int>(1,101));

	// !!! VALUE 'second' obsahuje informaciu ci ITEM bol pridany do COLLECTION.
	if (InsertResult.second==true)
	{
		wcout << L"ITEM [" << (InsertResult.first->second) << L"] ADDED to COLLECTION to BUCKET [" << Map1.bucket(InsertResult.first->second) << L"] !" << endl;
	}
	else
	{
		wcout << L"ITEM [" << (InsertResult.first->second) << L"] was NOT ADDED to COLLECTION !" << endl;
	}

	// Vola sa CONSTRUCTOR TYPU [pair<int,int>].
	Map1.emplace(5,105);

	PrintUnorderedMap(L"MAP 1",Map1);

	size_t														NumberOfRemovedItems=Map1.erase(1);

	wcout << L"NUMBER of REMOVED ITEMS [" << NumberOfRemovedItems << L"] !" << endl;

	PrintUnorderedMap(L"MAP 1",Map1);

	unordered_map<int,int>::const_iterator						Iterator1=Map1.cbegin();

	Iterator1++;

	unordered_map<int,int>::const_iterator						Iterator2=Iterator1;

	Iterator2++;
	Iterator2++;

	// Kedze ITEMS NIE SU SORTED, to ktore ITEMS budu odstranene zavisi od internej reprezentacie ITEMS v COLLECTION.
	Map1.erase(Iterator1,Iterator2);

	PrintUnorderedMap(L"MAP 1",Map1);

	PrintLineSeparator();

	CUnorderedIntHashFunction									CustomHashFunction2(20);
	CUnorderedIntEqualFunction									CustomEqualFunction2(20);
	unordered_map<CUnorderedInt,int,CUnorderedIntHashFunction,CUnorderedIntEqualFunction>	Map2(10,CustomHashFunction2,CustomEqualFunction2);

	Map2.insert(pair<CUnorderedInt,int>(CUnorderedInt(1),101));

	// Vola sa CONSTRUCTOR CLASS [pair<CUnorderedInt,int>].
	Map2.emplace(2,102);

	PrintUnorderedMap(L"MAP 2",Map2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapInsertErase(void)
{
	PrintLineSeparator();

	vector<pair<int,int>>										Vector{pair<int,int>(11,111),pair<int,int>(12,112),pair<int,int>(13,113)};
	unordered_multimap<int,int>									MultiMap1;

	MultiMap1.insert(pair<int,int>(1,101));
	MultiMap1.insert(pair<int,int>(1,1001));
	MultiMap1.insert(pair<int,int>(1,1002));
	MultiMap1.insert({pair<int,int>(2,102),pair<int,int>(3,103)});
	MultiMap1.insert({pair<int,int>(2,1002),pair<int,int>(3,1003)});
	MultiMap1.insert(Vector.cbegin(),Vector.cend());

	// Vola sa CONSTRUCTOR TYPU [pair<int,int>].
	MultiMap1.emplace(5,105);

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	size_t														NumberOfRemovedItems=MultiMap1.erase(1);

	wcout << L"NUMBER of REMOVED ITEMS [" << NumberOfRemovedItems << L"] !" << endl;

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	unordered_multimap<int,int>::const_iterator					Iterator1=MultiMap1.cbegin();

	Iterator1++;

	unordered_multimap<int,int>::const_iterator					Iterator2=Iterator1;

	Iterator2++;
	Iterator2++;

	// Kedze ITEMS NIE SU SORTED, to ktore ITEMS budu odstranene zavisi od internej reprezentacie ITEMS v COLLECTION.
	MultiMap1.erase(Iterator1,Iterator2);

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	PrintLineSeparator();

	CUnorderedIntHashFunction									CustomHashFunction2(20);
	CUnorderedIntEqualFunction									CustomEqualFunction2(20);
	unordered_multimap<CUnorderedInt,int,CUnorderedIntHashFunction,CUnorderedIntEqualFunction>	MultiMap2(10,CustomHashFunction2,CustomEqualFunction2);

	MultiMap2.insert(pair<CUnorderedInt,int>(CUnorderedInt(1),101));

	// Vola sa CONSTRUCTOR CLASS [pair<CUnorderedInt,int>].
	MultiMap2.emplace(2,102);

	PrintUnorderedMultiMap(L"MULTIMAP 2",MultiMap2);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSetBucketInterface(void)
{
	PrintLineSeparator();

	unordered_set<int>											Set1;

	Set1.max_load_factor(3);

	Set1.insert(1);
	Set1.insert(2);
	Set1.insert(3);
	Set1.insert(4);
	Set1.insert(5);

	PrintCollection(L"SET 1",Set1);

	PrintLineSeparator();

	wcout << L"SET 1 - BUCKET COUNT [" << Set1.bucket_count() << L"] !" << endl;
	wcout << L"SET 1 - ITEM(1) - BUCKET [" << Set1.bucket(1) << L"] !" << endl;
	wcout << L"SET 1 - ITEM(2) - BUCKET [" << Set1.bucket(2) << L"] !" << endl;
	wcout << L"SET 1 - ITEM(3) - BUCKET [" << Set1.bucket(3) << L"] !" << endl;
	wcout << L"SET 1 - ITEM(4) - BUCKET [" << Set1.bucket(4) << L"] !" << endl;
	wcout << L"SET 1 - ITEM(5) - BUCKET [" << Set1.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Set1.bucket_count();Bucket++)
	{
		wcout << L"SET 1 - BUCKET SIZE (" << Bucket << L") [" << Set1.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Set1.bucket_count();Bucket++)
	{
		wcout << L"SET 1 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_set<int>::const_local_iterator Iterator=Set1.cbegin(Bucket);Iterator!=Set1.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << *Iterator;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	CCustomHashFunction<int>									CustomHashFunction(10);
	CCustomEqualFunction<int>									CustomEqualFunction(10);
	unordered_set<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	Set2(10,CustomHashFunction,CustomEqualFunction);

	Set2.max_load_factor(4);

	Set2.insert(1);
	Set2.insert(2);
	Set2.insert(3);
	Set2.insert(4);
	Set2.insert(5);

	PrintCollection(L"SET 2",Set2);

	PrintLineSeparator();

	wcout << L"SET 2 - BUCKET COUNT [" << Set2.bucket_count() << L"] !" << endl;
	wcout << L"SET 2 - ITEM(1) - BUCKET [" << Set2.bucket(1) << L"] !" << endl;
	wcout << L"SET 2 - ITEM(2) - BUCKET [" << Set2.bucket(2) << L"] !" << endl;
	wcout << L"SET 2 - ITEM(3) - BUCKET [" << Set2.bucket(3) << L"] !" << endl;
	wcout << L"SET 2 - ITEM(4) - BUCKET [" << Set2.bucket(4) << L"] !" << endl;
	wcout << L"SET 2 - ITEM(5) - BUCKET [" << Set2.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Set2.bucket_count();Bucket++)
	{
		wcout << L"SET 2 - BUCKET SIZE (" << Bucket << L") [" << Set2.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Set2.bucket_count();Bucket++)
	{
		wcout << L"SET 2 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_set<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>::const_local_iterator Iterator=Set2.cbegin(Bucket);Iterator!=Set2.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << *Iterator;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSetBucketInterface(void)
{
	PrintLineSeparator();

	unordered_multiset<int>										MultiSet1;

	MultiSet1.max_load_factor(3);

	MultiSet1.insert(1);
	MultiSet1.insert(2);
	MultiSet1.insert(2);
	MultiSet1.insert(3);
	MultiSet1.insert(3);
	MultiSet1.insert(4);
	MultiSet1.insert(4);
	MultiSet1.insert(5);

	PrintCollection(L"MULTISET 1",MultiSet1);

	PrintLineSeparator();

	wcout << L"MULTISET 1 - BUCKET COUNT [" << MultiSet1.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 1 - ITEM(1) - BUCKET [" << MultiSet1.bucket(1) << L"] !" << endl;
	wcout << L"MULTISET 1 - ITEM(2) - BUCKET [" << MultiSet1.bucket(2) << L"] !" << endl;
	wcout << L"MULTISET 1 - ITEM(3) - BUCKET [" << MultiSet1.bucket(3) << L"] !" << endl;
	wcout << L"MULTISET 1 - ITEM(4) - BUCKET [" << MultiSet1.bucket(4) << L"] !" << endl;
	wcout << L"MULTISET 1 - ITEM(5) - BUCKET [" << MultiSet1.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiSet1.bucket_count();Bucket++)
	{
		wcout << L"MULTISET 1 - BUCKET SIZE (" << Bucket << L") [" << MultiSet1.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiSet1.bucket_count();Bucket++)
	{
		wcout << L"MULTISET 1 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_multiset<int>::const_local_iterator Iterator=MultiSet1.cbegin(Bucket);Iterator!=MultiSet1.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << *Iterator;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	CCustomHashFunction<int>									CustomHashFunction(10);
	CCustomEqualFunction<int>									CustomEqualFunction(10);
	unordered_multiset<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	MultiSet2(10,CustomHashFunction,CustomEqualFunction);

	MultiSet2.max_load_factor(4);

	MultiSet2.insert(1);
	MultiSet2.insert(2);
	MultiSet2.insert(2);
	MultiSet2.insert(3);
	MultiSet2.insert(3);
	MultiSet2.insert(4);
	MultiSet2.insert(4);
	MultiSet2.insert(5);

	PrintCollection(L"MULTISET 2",MultiSet2);

	PrintLineSeparator();

	wcout << L"MULTISET 2 - BUCKET COUNT [" << MultiSet2.bucket_count() << L"] !" << endl;
	wcout << L"MULTISET 2 - ITEM(1) - BUCKET [" << MultiSet2.bucket(1) << L"] !" << endl;
	wcout << L"MULTISET 2 - ITEM(2) - BUCKET [" << MultiSet2.bucket(2) << L"] !" << endl;
	wcout << L"MULTISET 2 - ITEM(3) - BUCKET [" << MultiSet2.bucket(3) << L"] !" << endl;
	wcout << L"MULTISET 2 - ITEM(4) - BUCKET [" << MultiSet2.bucket(4) << L"] !" << endl;
	wcout << L"MULTISET 2 - ITEM(5) - BUCKET [" << MultiSet2.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiSet2.bucket_count();Bucket++)
	{
		wcout << L"MULTISET 2 - BUCKET SIZE (" << Bucket << L") [" << MultiSet2.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiSet2.bucket_count();Bucket++)
	{
		wcout << L"MULTISET 2 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_multiset<int,CCustomHashFunction<int>,CCustomEqualFunction<int>>::const_local_iterator Iterator=MultiSet2.cbegin(Bucket);Iterator!=MultiSet2.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << *Iterator;
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapBucketInterface(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map1;

	Map1.max_load_factor(3);

	Map1.insert(pair<int,int>(1,11));
	Map1.insert(pair<int,int>(2,12));
	Map1.insert(pair<int,int>(3,13));
	Map1.insert(pair<int,int>(4,14));
	Map1.insert(pair<int,int>(5,15));

	PrintUnorderedMap(L"MAP 1",Map1);

	PrintLineSeparator();

	wcout << L"MAP 1 - BUCKET COUNT [" << Map1.bucket_count() << L"] !" << endl;
	wcout << L"MAP 1 - ITEM(1) - BUCKET [" << Map1.bucket(1) << L"] !" << endl;
	wcout << L"MAP 1 - ITEM(2) - BUCKET [" << Map1.bucket(2) << L"] !" << endl;
	wcout << L"MAP 1 - ITEM(3) - BUCKET [" << Map1.bucket(3) << L"] !" << endl;
	wcout << L"MAP 1 - ITEM(4) - BUCKET [" << Map1.bucket(4) << L"] !" << endl;
	wcout << L"MAP 1 - ITEM(5) - BUCKET [" << Map1.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map1.bucket_count();Bucket++)
	{
		wcout << L"MAP 1 - BUCKET SIZE (" << Bucket << L") [" << Map1.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map1.bucket_count();Bucket++)
	{
		wcout << L"MAP 1 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_map<int,int>::const_local_iterator Iterator=Map1.cbegin(Bucket);Iterator!=Map1.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	CCustomHashFunction<int>									CustomHashFunction(10);
	CCustomEqualFunction<int>									CustomEqualFunction(10);
	unordered_map<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	Map2(10,CustomHashFunction,CustomEqualFunction);

	Map2.max_load_factor(4);

	Map2.insert(pair<int,int>(1,11));
	Map2.insert(pair<int,int>(2,12));
	Map2.insert(pair<int,int>(3,13));
	Map2.insert(pair<int,int>(4,14));
	Map2.insert(pair<int,int>(5,15));

	PrintUnorderedMap(L"MAP 2",Map2);

	PrintLineSeparator();

	wcout << L"MAP 2 - BUCKET COUNT [" << Map2.bucket_count() << L"] !" << endl;
	wcout << L"MAP 2 - ITEM(1) - BUCKET [" << Map2.bucket(1) << L"] !" << endl;
	wcout << L"MAP 2 - ITEM(2) - BUCKET [" << Map2.bucket(2) << L"] !" << endl;
	wcout << L"MAP 2 - ITEM(3) - BUCKET [" << Map2.bucket(3) << L"] !" << endl;
	wcout << L"MAP 2 - ITEM(4) - BUCKET [" << Map2.bucket(4) << L"] !" << endl;
	wcout << L"MAP 2 - ITEM(5) - BUCKET [" << Map2.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map2.bucket_count();Bucket++)
	{
		wcout << L"MAP 2 - BUCKET SIZE (" << Bucket << L") [" << Map2.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<Map2.bucket_count();Bucket++)
	{
		wcout << L"MAP 2 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_map<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>::const_local_iterator Iterator=Map2.cbegin(Bucket);Iterator!=Map2.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMapBucketInterface(void)
{
	PrintLineSeparator();

	unordered_multimap<int,int>									MultiMap1;

	MultiMap1.max_load_factor(3);

	MultiMap1.insert(pair<int,int>(1,11));
	MultiMap1.insert(pair<int,int>(2,12));
	MultiMap1.insert(pair<int,int>(2,22));
	MultiMap1.insert(pair<int,int>(2,32));
	MultiMap1.insert(pair<int,int>(3,13));
	MultiMap1.insert(pair<int,int>(3,23));
	MultiMap1.insert(pair<int,int>(3,33));
	MultiMap1.insert(pair<int,int>(4,14));
	MultiMap1.insert(pair<int,int>(4,24));
	MultiMap1.insert(pair<int,int>(4,34));
	MultiMap1.insert(pair<int,int>(5,15));

	PrintUnorderedMultiMap(L"MULTIMAP 1",MultiMap1);

	PrintLineSeparator();

	wcout << L"MULTIMAP 1 - BUCKET COUNT [" << MultiMap1.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 1 - ITEM(1) - BUCKET [" << MultiMap1.bucket(1) << L"] !" << endl;
	wcout << L"MULTIMAP 1 - ITEM(2) - BUCKET [" << MultiMap1.bucket(2) << L"] !" << endl;
	wcout << L"MULTIMAP 1 - ITEM(3) - BUCKET [" << MultiMap1.bucket(3) << L"] !" << endl;
	wcout << L"MULTIMAP 1 - ITEM(4) - BUCKET [" << MultiMap1.bucket(4) << L"] !" << endl;
	wcout << L"MULTIMAP 1 - ITEM(5) - BUCKET [" << MultiMap1.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiMap1.bucket_count();Bucket++)
	{
		wcout << L"MULTIMAP 1 - BUCKET SIZE (" << Bucket << L") [" << MultiMap1.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiMap1.bucket_count();Bucket++)
	{
		wcout << L"MULTIMAP 1 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_multimap<int,int>::const_local_iterator Iterator=MultiMap1.cbegin(Bucket);Iterator!=MultiMap1.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! EXTREMNE NEEFEKTIVNA HASH FUNCTION.
	CCustomHashFunction<int>									CustomHashFunction(10);
	CCustomEqualFunction<int>									CustomEqualFunction(10);
	unordered_multimap<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>	MultiMap2(10,CustomHashFunction,CustomEqualFunction);

	MultiMap2.max_load_factor(4);

	MultiMap2.insert(pair<int,int>(1,11));
	MultiMap2.insert(pair<int,int>(2,12));
	MultiMap2.insert(pair<int,int>(2,22));
	MultiMap2.insert(pair<int,int>(2,32));
	MultiMap2.insert(pair<int,int>(3,13));
	MultiMap2.insert(pair<int,int>(3,23));
	MultiMap2.insert(pair<int,int>(3,33));
	MultiMap2.insert(pair<int,int>(4,14));
	MultiMap2.insert(pair<int,int>(4,24));
	MultiMap2.insert(pair<int,int>(4,34));
	MultiMap2.insert(pair<int,int>(5,15));

	PrintUnorderedMultiMap(L"MULTIMAP 2",MultiMap2);

	PrintLineSeparator();

	wcout << L"MULTIMAP 2 - BUCKET COUNT [" << MultiMap2.bucket_count() << L"] !" << endl;
	wcout << L"MULTIMAP 2 - ITEM(1) - BUCKET [" << MultiMap2.bucket(1) << L"] !" << endl;
	wcout << L"MULTIMAP 2 - ITEM(2) - BUCKET [" << MultiMap2.bucket(2) << L"] !" << endl;
	wcout << L"MULTIMAP 2 - ITEM(3) - BUCKET [" << MultiMap2.bucket(3) << L"] !" << endl;
	wcout << L"MULTIMAP 2 - ITEM(4) - BUCKET [" << MultiMap2.bucket(4) << L"] !" << endl;
	wcout << L"MULTIMAP 2 - ITEM(5) - BUCKET [" << MultiMap2.bucket(5) << L"] !" << endl;

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiMap2.bucket_count();Bucket++)
	{
		wcout << L"MULTIMAP 2 - BUCKET SIZE (" << Bucket << L") [" << MultiMap2.bucket_size(Bucket) << L"] !" << endl;
	}

	PrintLineSeparator();

	for(size_t Bucket=0;Bucket<MultiMap2.bucket_count();Bucket++)
	{
		wcout << L"MULTIMAP 2 - BUCKET (" << Bucket << L") - VALUES [";

		bool													AddSpace=false;

		// !!! CODE iteruje vsetkymi ITEMS v danom BUCKET.
		for(unordered_multimap<int,int,CCustomHashFunction<int>,CCustomEqualFunction<int>>::const_local_iterator Iterator=MultiMap2.cbegin(Bucket);Iterator!=MultiMap2.cend(Bucket);Iterator++)
		{
			if (AddSpace==false)
			{
				AddSpace=true;
			}
			else
			{
				wcout << L" ";
			}

			wcout << L"[" << Iterator->first << L"," << Iterator->second << L"]";
		}

		wcout << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMapSubscriptionAt(void)
{
	PrintLineSeparator();

	unordered_map<int,int>										Map;

	Map.insert(pair<int,int>(1,11));
	Map.insert(pair<int,int>(2,12));
	Map.insert(pair<int,int>(3,13));
	Map.insert(pair<int,int>(4,14));
	Map.insert(pair<int,int>(5,15));

	PrintUnorderedMap(L"MAP",Map);

	PrintLineSeparator();

	wcout << L"MAP [";

	for(int Index=1;Index<=5;Index++)
	{
		if (Index>1)
		{
			wcout << L" ";
		}

		// !!! Pouzije sa OPERATOR[] na pristup k ITEMS.
		wcout << L"[" << Index << "]=[" << Map[Index] << "]";
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MAP [";

	// !!! UMYSELNE sa prekroci horna medza.
	for(int Index=1;Index<=6;Index++)
	{
		if (Index>1)
		{
			wcout << L" ";
		}
		
		try
		{
			// !!! Pouzije sa METHOD at() na pristup k ITEMS.
			wcout << L"[" << Index << "]=[" << Map.at(Index) << "]";
		}
		catch(const out_of_range&)
		{
			wcout << L"[" << Index << "]=[OUT OF RANGE]";
		}
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueInitialization(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue1;

	Dequeue1.push_back(1);
	Dequeue1.push_back(2);
	Dequeue1.push_back(3);

	PrintCollection(L"DEQUEUE 1",Dequeue1);

	// Pouzije sa COPY CONSTRUCTOR.
	deque<int>													Dequeue2(Dequeue1);
	
	PrintCollection(L"DEQUEUE 2",Dequeue2);

	deque<int>													Dequeue3;

	// Pouzije sa COPY OPERATOR=.
	Dequeue3=Dequeue1;

	PrintCollection(L"DEQUEUE 3",Dequeue3);

	PrintLineSeparator();

	// Pouzije sa MOVE OPERATOR=.
	Dequeue3=std::move(Dequeue2);

	PrintCollection(L"DEQUEUE 2",Dequeue2);
	PrintCollection(L"DEQUEUE 3",Dequeue3);

	PrintLineSeparator();

	{
		deque<CInt>												Dequeue4;

		Dequeue4.push_back(1);
		Dequeue4.push_back(2);
		Dequeue4.push_back(3);

		PrintCollection(L"DEQUEUE 4",Dequeue4);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueComparison(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue1{5,4,8,9,23};
	deque<int>													Dequeue2{5,4,8,7,23};

	PrintCollection(L"DEQUEUE 1",Dequeue1);
	PrintCollection(L"DEQUEUE 2",Dequeue2);

	PrintLineSeparator();

	wcout << L"DEQUEUE1==DEQUEUE2 [" << ((Dequeue1==Dequeue2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"DEQUEUE1!=DEQUEUE2 [" << ((Dequeue1!=Dequeue2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"DEQUEUE1<DEQUEUE2 [" << ((Dequeue1<Dequeue2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"DEQUEUE1<=DEQUEUE2 [" << ((Dequeue1<=Dequeue2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"DEQUEUE1>=DEQUEUE2 [" << ((Dequeue1>=Dequeue2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"DEQUEUE1>DEQUEUE2 [" << ((Dequeue1>Dequeue2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueSize(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue{5,4,8,9,23};

	PrintCollection(L"DEQUEUE",Dequeue);

	wcout << L"DEQUEUE - SIZE [" << Dequeue.size() << L"] !" << endl;
	wcout << L"DEQUEUE - MAX SIZE [" << Dequeue.max_size() << L"] !" << endl;
	wcout << L"DEQUEUE - EMPTY [" << Dequeue.empty() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueSwap(void)
{
	PrintLineSeparator();

	{
		deque<CInt>												Dequeue1{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		deque<CInt>												Dequeue2{CInt(11),CInt(12),CInt(13),CInt(14),CInt(15)};

		PrintCollection(L"DEQUEUE 1",Dequeue1);
		PrintCollection(L"DEQUEUE 2",Dequeue2);

		PrintLineSeparator();

		// !!!!! METHOD swap() VYMIENA POINTER na INTERNAL DATA.
		// !!! Pre jednotlive ITEMS sa MOVE OPERATOR= NEVOLAJU.
		Dequeue1.swap(Dequeue2);

		PrintLineSeparator();

		PrintCollection(L"DEQUEUE 1",Dequeue1);
		PrintCollection(L"DEQUEUE 2",Dequeue2);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueAssign(void)
{
	PrintLineSeparator();

	{
		array<CInt,5>											Array{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		deque<CInt>												Dequeue;

		PrintCollection(L"ARRAY",Array);

		// !!! ITEMS z ARRAY sa ulozia do DEQUEUE pomocou METHOD assign(), ktora umoznuje kopirovat ITEMS z inych CONTAINERS.
		// !!! Pre kazdy ITEM sa vola COPY CONSTRUCTOR.
		Dequeue.assign(Array.cbegin(),Array.cend());

		PrintLineSeparator();

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueElementAccess(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue{5,4,8,9,23};

	PrintCollection(L"DEQUEUE",Dequeue);

	Dequeue[1]=Dequeue[1]+5;
	Dequeue.at(2)=17;

	PrintCollection(L"DEQUEUE",Dequeue);

	try
	{
		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"DEQUEUE [20] VALUE [" << Dequeue.at(20) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintCollection(L"DEQUEUE",Dequeue);

	wcout << L"DEQUEUE FRONT [" << Dequeue.front() << L"] !" << endl;
	wcout << L"DEQUEUE BACK [" << Dequeue.back() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueIterators(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue{5,4,8,9,23};

	wcout << L"DEQUEUE [";

	for(deque<int>::iterator Iterator=Dequeue.begin();Iterator!=Dequeue.end();Iterator++)
	{
		if (Iterator!=Dequeue.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;

		// Modifikuje sa VALUE.
		*Iterator=*Iterator*2;
	}

	wcout << L"] !" << endl;

	wcout << L"DEQUEUE [";

	// Pouzije sa CONST ITERATOR.
	for(deque<int>::const_iterator Iterator=Dequeue.cbegin();Iterator!=Dequeue.cend();Iterator++)
	{
		if (Iterator!=Dequeue.cbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"DEQUEUE [";

	// Pouzije sa CONST REVERSE ITERATOR.
	for(deque<int>::const_reverse_iterator Iterator=Dequeue.crbegin();Iterator!=Dequeue.crend();Iterator++)
	{
		if (Iterator!=Dequeue.crbegin())
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
void TestDequeueInsertEraseEmplace(void)
{
	PrintLineSeparator();

	{
		deque<CInt>											Dequeue1{CInt(1),CInt(2),CInt(3),CInt(4),CInt(5)};
		deque<CInt>											Dequeue2{CInt(100),CInt(200)};

		PrintCollection(L"DEQUEUE 1",Dequeue1);
		PrintCollection(L"DEQUEUE 2",Dequeue2);

		PrintLineSeparator();

		// Vlozi sa 1 ITEM.
		Dequeue1.insert(Dequeue1.begin()+2,CInt(10));

		PrintCollection(L"DEQUEUE 1",Dequeue1);

		PrintLineSeparator();

		// Vlozi sa 'N' ITEM.
		Dequeue1.insert(Dequeue1.begin()+4,Dequeue2.begin(),Dequeue2.end());

		PrintCollection(L"DEQUEUE 1",Dequeue1);

		PrintLineSeparator();

		// Odstrani sa 1 ITEM.
		Dequeue1.erase(Dequeue1.begin()+5);

		PrintCollection(L"DEQUEUE 1",Dequeue1);

		PrintLineSeparator();

		// Odstrani sa 'N' ITEM.
		// !!! ITEM na ktory sa odkazuje ITERATOR v 2. PARAMETRI sa NEODSTRANUJE. Cize v tomto pripade sa odstrania 2 ITEMS.
		Dequeue1.erase(Dequeue1.begin()+1,Dequeue1.begin()+3);

		PrintCollection(L"DEQUEUE 1",Dequeue1);

		PrintLineSeparator();

		// !!! Prida sa ITEM, pricom sa vola CONSTRUCTOR CLASS 'CInt'.
		// !!! 2. PARAMETER je PARAMETER CONSTRUCTOR CLASS 'CInt'.
		Dequeue1.emplace(Dequeue1.begin()+1,33);

		PrintCollection(L"DEQUEUE 1",Dequeue1);

		PrintLineSeparator();

		// Pridavanie ITEMS na zaciatok DEQUEUE je velmi efektivne.
		Dequeue1.push_front(CInt(555));

		// Pridavanie ITEMS na koniec DEQUEUE je velmi efektivne.
		Dequeue1.push_back(CInt(55));

		PrintCollection(L"DEQUEUE 1",Dequeue1);

		PrintLineSeparator();

		// Odstranovanie ITEMS zo zaciatku DEQUEUE je velmi efektivne.
		Dequeue1.pop_front();

		// Odstranovanie ITEMS z konca DEQUEUE je velmi efektivne.
		Dequeue1.pop_back();

		PrintCollection(L"DEQUEUE 1",Dequeue1);
	
		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueShrink(void)
{
	PrintLineSeparator();

	{
		deque<CInt>												Dequeue;

		Dequeue.push_back(1);
		Dequeue.push_back(2);
		Dequeue.push_back(3);
		Dequeue.push_back(4);
		Dequeue.push_back(5);
		Dequeue.push_back(6);
		Dequeue.push_back(7);
		Dequeue.push_back(8);
		Dequeue.push_back(9);
		Dequeue.push_back(10);

		PrintCollection(L"DEQUEUE",Dequeue);

		Dequeue.pop_back();
		Dequeue.pop_back();
		Dequeue.pop_back();
		Dequeue.pop_back();

		PrintCollection(L"DEQUEUE",Dequeue);

		// !!!!! METHOD shrink_to_fit() je len REQUEST o uvolnenie nealokovanych MEMORY BLOCKS. To ci METHOD shrink_to_fit() zmenu CAPACITY naozaj vykonaje IMPLEMENTACNE ZAVISLE.
		Dequeue.shrink_to_fit();

		PrintCollection(L"DEQUEUE",Dequeue);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeueResize(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue;

	Dequeue.push_back(10);
	Dequeue.push_back(20);
	Dequeue.push_back(30);
	Dequeue.push_back(40);
	Dequeue.push_back(50);

	PrintCollection(L"DEQUEUE",Dequeue);

	PrintLineSeparator();

	// !!! Prida 2 nove ITEMS s hodnotou '888'.
	Dequeue.resize(7,888);

	PrintCollection(L"DEQUEUE",Dequeue);

	PrintLineSeparator();

	// !!! Odstrani 3 ITEMS.
	Dequeue.resize(4,888);

	PrintCollection(L"DEQUEUE",Dequeue);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCustomHashInStdNamespace(void)
{
	PrintLineSeparator();

	// !!! Pouziju sa GLOBAL HASH a EQUAL FUNCTIONS definovane v NAMESPACE [std].
	unordered_set<CCustomHashInStdNamespace>					Set;

	Set.insert(1);
	Set.insert(2);
	Set.insert(3);

	PrintCollection(L"SET",Set);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPriorityQueue(void)
{
	PrintLineSeparator();

	priority_queue<int>											PriorityQueue;

	PriorityQueue.push(20);
	PriorityQueue.push(50);
	PriorityQueue.push(30);
	PriorityQueue.push(10);
	PriorityQueue.push(40);

	bool														IsFirst=true;

	wcout << L"PRIORITY QUEUE [";

	while(PriorityQueue.empty()==false)
	{
		if (IsFirst==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst=false;
		}
		
		wcout << PriorityQueue.top();

		PriorityQueue.pop();
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestQueue(void)
{
	PrintLineSeparator();

	queue<int>													Queue1;

	Queue1.push(10);
	Queue1.push(20);
	Queue1.push(30);
	Queue1.push(40);
	Queue1.push(50);

	queue<int>													Queue2;

	Queue2.push(10);
	Queue2.push(20);
	Queue2.push(30);
	Queue2.push(40);
	Queue2.push(50);

	bool														IsFirst1=true;

	wcout << L"QUEUE [";

	while(Queue1.empty()==false)
	{
		if (IsFirst1==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst1=false;
		}
		
		wcout << Queue1.front();

		Queue1.pop();
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	bool														IsFirst2=true;

	wcout << L"QUEUE [";

	while(Queue2.empty()==false)
	{
		if (IsFirst2==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst2=false;
		}
		
		wcout << Queue2.back();

		Queue2.pop();
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStack(void)
{
	PrintLineSeparator();

	stack<int>													Stack;

	Stack.push(10);
	Stack.push(20);
	Stack.push(30);
	Stack.push(40);
	Stack.push(50);

	bool														IsFirst=true;

	wcout << L"STACK [";

	while(Stack.empty()==false)
	{
		if (IsFirst==false)
		{
			wcout << L" ";
		}
		else
		{
			IsFirst=false;
		}
		
		wcout << Stack.top();

		Stack.pop();
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

	//TestCustomCompared();
	//TestCollectionTypes1();
	//TestCollectionTypes2();
	//TestCollectionTypes3();
	//TestCollectionTypes4();
	//TestCollectionTypes5();
	//TestCollectionTypes6();
	//TestCollectionConstructorDestructor();
	//TestCollectionConstructor1();
	//TestCollectionConstructor2();
	//TestCollectionConstructor3();
	//TestCollectionConstructor4();
	//TestCollectionConstructor5();
	//TestOperatorAssignment();
	//TestAssign();
	//TestSizeOperations();
	//TestResize();
	//TestShrinkToFit();
	//TestClear();
	//TestCapacity();
	//TestIterators();
	//TestFront();
	//TestBack();
	//TestOperatorSubscript1();
	//TestOperatorSubscript2();
	//TestAt1();
	//TestAt2();
	//TestSingleInsert1();
	//TestSingleInsert2();
	//TestSingleInsert3();
	//TestMultiInsert();
	//TestEmplace1();
	//TestEmplace2();
	//TestEmplace3();
	//TestEmplaceHint();
	//TestPushFront();
	//TestEmplaceFront();
	//TestPushBack();
	//TestEmplaceBack();
	//TestErase();
	//TestPopFrontPopBack();
	//TestComparisonOperators();
	//TestSwap();
	//TestRemoveRemoveIf();
	//TestUnique();
	//TestMerge1();
	//TestMerge2();
	//TestMerge3();
	//TestMerge4();
	//TestSort();
	//TestReverse();
	//TestSplice1();
	//TestSplice2();
	//TestSplice3();
	//TestBeforeBegin();
	//TestInsertAfter();
	//TestEmplaceAfter();
	//TestEraseAfter();
	//TestSpliceAfter1();
	//TestSpliceAfter2();
	//TestSpliceAfter3();
	//TestCount();
	//TestFind();
	//TestLowerBound();
	//TestUpperBound();
	//TestEqualBound();
	//TestCompareMethods();
	//TestLoadFactor1();
	//TestLoadFactor2();
	//TestRehash();
	//TestBuckets1();
	//TestBuckets2();
	//TestFill();
	//TestData();
	//TestGetAllocator();
	//TestVectorCapacity();
	//TestVectorComparison();
	//TestVectorSize();
	//TestVectorMove();
	//TestVectorSwap();
	//TestVectorAssign();
	//TestVectorElementAccess();
	//TestVectorIterators();
	//TestVectorInsertEraseEmplace();
	//TestVectorAsCArray();
	//TestVectorBool();
	//TestListInitialization();
	//TestListComparison();
	//TestListSize();
	//TestListAssign();
	//TestListIterators();
	//TestListInsert();
	//TestListEmplace();
	//TestListErase();
	//TestListRemove();
	//TestListResize();
	//TestListSplice1();
	//TestListSplice2();
	//TestListSortAndMerge1();
	//TestListSortAndMerge2();
	//TestListUnique();
	//TestListReverse();
	//TestForwardListInitialization();
	//TestForwardListComparison();
	//TestForwardListMaxSize();
	//TestForwardListAssign();
	//TestForwardListIterators();
	//TestForwardListInsert();
	//TestForwardListEmplace();
	//TestForwardListErase();
	//TestForwardListRemove();
	//TestForwardListResize();
	//TestForwardListSplice1();
	//TestForwardListSplice2();
	//TestForwardListSortAndMerge1();
	//TestForwardListSortAndMerge2();
	//TestForwardListUnique();
	//TestForwardListReverse();
	//TestSetInitialization();
	//TestMultiSetInitialization();
	//TestSetComparison();
	//TestMultiSetComparison();
	//TestSetSize();
	//TestMultiSetSize();
	//TestSetFind();
	//TestMultiSetFind();
	//TestSetAssign();
	//TestMultiSetAssign();
	//TestSetIterators();
	//TestMultiSetIterators();
	//TestSetInsert();
	//TestMultiSetInsert();
	//TestSetEmplace();
	//TestMultiSetEmplace();
	//TestSetErase();
	//TestMultiSetErase();
	//TestMapInitialization();
	//TestMultiMapInitialization();
	//TestMapComparison();
	//TestMultiMapComparison();
	//TestMapSize();
	//TestMultiMapSize();
	//TestMapFind();
	//TestMultiMapFind();
	//TestMapAssign();
	//TestMultiMapAssign();
	//TestMapIterators();
	//TestMultiMapIterators();
	//TestMapInsert();
	//TestMultiMapInsert();
	//TestMapEmplace();
	//TestMultiMapEmplace();
	//TestMapErase();
	//TestMultiMapErase();
	//TestMapAtAndOperatorSubscription();
	//TestUnorderedSetInitialization();
	//TestUnorderedMultiSetInitialization();
	//TestUnorderedMapInitialization();
	//TestUnorderedMultiMapInitialization();
	//TestUnorderedSetCustomHash1();
	//TestUnorderedMultiSetCustomHash1();
	//TestUnorderedMapCustomHash1();
	//TestUnorderedMultiMapCustomHash1();
	//TestUnorderedSetCustomHash2();
	//TestUnorderedMultiSetCustomHash2();
	//TestUnorderedMapCustomHash2();
	//TestUnorderedMultiMapCustomHash2();
	//TestUnorderedSetCustomHashAndEquatableFunctions();
	//TestUnorderedMultiSetCustomHashAndEquatableFunctions();
	//TestUnorderedMapCustomHashAndEquatableFunctions();
	//TestUnorderedMultiMapCustomHashAndEquatableFunctions();
	//TestUnorderedSetCompare();
	//TestUnorderedMultiSetCompare();
	//TestUnorderedMapCompare();
	//TestUnorderedMultiMapCompare();
	//TestUnorderedSetSearch();
	//TestUnorderedMultiSetSearch();
	//TestUnorderedMapSearch();
	//TestUnorderedMultiMapSearch();
	//TestUnorderedSetAssignment();
	//TestUnorderedMultiSetAssignment();
	//TestUnorderedMapAssignment();
	//TestUnorderedMultiMapAssignment();
	//TestUnorderedSetInsertErase();
	//TestUnorderedMultiSetInsertErase();
	//TestUnorderedMapInsertErase();
	//TestUnorderedMultiMapInsertErase();
	//TestUnorderedSetBucketInterface();
	//TestUnorderedMultiSetBucketInterface();
	//TestUnorderedMapBucketInterface();
	//TestUnorderedMultiMapBucketInterface();
	//TestUnorderedMapSubscriptionAt();
	//TestDequeueInitialization();
	//TestDequeueComparison();
	//TestDequeueSize();
	//TestDequeueSwap();
	//TestDequeueAssign();
	//TestDequeueElementAccess();
	//TestDequeueIterators();
	//TestDequeueInsertEraseEmplace();
	//TestDequeueShrink();
	//TestDequeueResize();
	//TestCustomHashInStdNamespace();
	//TestPriorityQueue();
	//TestQueue();
	TestStack();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------