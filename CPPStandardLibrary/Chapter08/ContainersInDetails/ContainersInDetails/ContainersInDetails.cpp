//-----------------------------------------------------------------------------
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
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
#include "MyDebug.h"
#include "CInt.h"
#include "CCustomEqual.h"
#include "COddEvenHash.h"
#include "CCustomComparer.h"
#include "CMyAllocator.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TCollection>
void PrintCollectionSharedPointer(const wstring& Prefix, const TCollection& Collection)
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

		wcout << *Item;
	}

	wcout << L"] !" << endl;
}
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
void TestCollectionTypes1(void)
{
	PrintLineSeparator();
	
	vector<int>													Vector({1,2,3,4,5});

	wcout << L"VALUE TYPE SIZE [" << sizeof(vector<int>::value_type) << L"] !" << endl;

	vector<int>::reference										Item1=Vector[0];

	Item1+=10;

	wcout << L"REFERENCE[0] [" << Item1 << L"] !" << endl;

	vector<int>::const_reference								Item2=Vector[0];

	wcout << L"CONST REFERENCE[0] [" << Item2 << L"] !" << endl;

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

	wcout << L"NEXT ITEM after REMOVED ITEM [" << *Result2 << L"] !" << endl;

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
void TestReserve(void)
{
	PrintLineSeparator();

	{
		vector<CInt>											Vector;

		Vector.reserve(3);

		Vector.push_back(CInt(1));
		Vector.push_back(CInt(2));
		Vector.push_back(CInt(3));
		Vector.push_back(CInt(4));
		Vector.push_back(CInt(5));

		wcout << L"CAPACITY [" << Vector.capacity() << L"] !" << endl;

		PrintCollection(L"VECTOR",Vector);

		PrintLineSeparator();
	}

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
void TestCollectionConstructorWithAllocator1(void)
{
	PrintLineSeparator();

	{
		CMyAllocator<CInt>										Allocator1;
		CMyAllocator<CInt>										Allocator2;
		CMyAllocator<CInt>										Allocator3;

		vector<CInt,CMyAllocator<CInt>>							Vector1(Allocator1);

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
		vector<CInt,CMyAllocator<CInt>>							Vector2(Vector1,Allocator2);

		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// Vola sa MOVE CONSTRUCTOR.
		vector<CInt,CMyAllocator<CInt>>							Vector3(std::move(Vector2),Allocator3);

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
void TestCollectionConstructorWithAllocator2(void)
{
	PrintLineSeparator();

	{
		CMyAllocator<int>										Allocator;

		COddEvenHash											HashFunction;
		CCustomEqual<int>										KeyEqualFunction;

		// 1. PARAMETER definuje pocet BUCKETS.
		// 2. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
		// 3. PARAMETER definuje pocet CUSTOM KEY EQUAL FUNCTION.
		// 4. PARAMETER definuje CUSTOM ALLOCATOR.
		unordered_set<int,COddEvenHash,CCustomEqual<int>,CMyAllocator<int>>	UnorderedSet(2,HashFunction,KeyEqualFunction,Allocator);

		UnorderedSet.insert(10);
		UnorderedSet.insert(20);
		UnorderedSet.insert(30);
		UnorderedSet.insert(40);

		PrintCollection(L"UNORDERED SET",UnorderedSet);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructorWithAllocator3(void)
{
	PrintLineSeparator();

	{
		CMyAllocator<int>										Allocator;
		vector<int>												Vector;

		Vector.push_back(10);
		Vector.push_back(20);
		Vector.push_back(30);
		Vector.push_back(40);

		COddEvenHash											HashFunction;
		CCustomEqual<int>										KeyEqualFunction;

		// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initializovat.
		// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initializovat.
		// 3. PARAMETER definuje pocet BUCKETS.
		// 4. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
		// 5. PARAMETER definuje pocet CUSTOM KEY EQUAL FUNCTION.
		// 6. PARAMETER definuje CUSTOM ALLOCATOR.
		unordered_set<int,COddEvenHash,CCustomEqual<int>,CMyAllocator<int>>		UnorderedSet(Vector.cbegin(),Vector.cend(),2,HashFunction,KeyEqualFunction,Allocator);

		PrintCollection(L"UNORDERED SET",UnorderedSet);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructorWithAllocator4(void)
{
	PrintLineSeparator();

	{
		CMyAllocator<int>										Allocator;
		COddEvenHash											HashFunction;
		CCustomEqual<int>										KeyEqualFunction;

		// 1. PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initializovat.
		// 2. PARAMETER definuje pocet BUCKETS.
		// 3. PARAMETER definuje pocet CUSTOM HASH FUNCTION.
		// 4. PARAMETER definuje pocet CUSTOM KEY EQUAL FUNCTION.
		// 5. PARAMETER definuje CUSTOM ALLOCATOR.
		unordered_set<int,COddEvenHash,CCustomEqual<int>,CMyAllocator<int>>	UnorderedSet({10,20,30,40},2,HashFunction,KeyEqualFunction,Allocator);

		PrintCollection(L"UNORDERED SET",UnorderedSet);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructorWithAllocator5(void)
{
	PrintLineSeparator();

	{
		CMyAllocator<int>										Allocator;
		CCustomComparer											CompareFunction(false);
		vector<int>												Vector;

		Vector.push_back(10);
		Vector.push_back(20);
		Vector.push_back(30);
		Vector.push_back(40);

		// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initializovat.
		// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initializovat.
		// 3. PARAMETER definuje pocet CUSTOM COMPARE FUNCTION.
		// 4. PARAMETER definuje CUSTOM ALLOCATOR.
		set<int,CCustomComparer,CMyAllocator<int>>				Set1(Vector.cbegin(),Vector.cend(),CompareFunction,Allocator);

		PrintCollection(L"SET 1",Set1);

		PrintLineSeparator();

		// 1. PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initializovat.
		// 2. PARAMETER definuje pocet CUSTOM COMPARE FUNCTION.
		// 3. PARAMETER definuje CUSTOM ALLOCATOR.
		set<int,CCustomComparer,CMyAllocator<int>>				Set2({10,20,30,40},CompareFunction,Allocator);

		PrintCollection(L"SET 2",Set2);

		PrintLineSeparator();

		// 1. PARAMETER definuje pocet CUSTOM COMPARE FUNCTION.
		// 2. PARAMETER definuje CUSTOM ALLOCATOR.
		set<int,CCustomComparer,CMyAllocator<int>>				Set3(CompareFunction,Allocator);

		Set3.insert(10);
		Set3.insert(20);
		Set3.insert(30);
		Set3.insert(40);

		PrintCollection(L"SET 3",Set3);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCollectionConstructorWithAllocator6(void)
{
	PrintLineSeparator();

	{
		CMyAllocator<int>										Allocator;

		// 1. PARAMETER definuje INITIALIZATION LIST odkial sa bude COLLECTION initializovat.
		// 2. PARAMETER definuje CUSTOM ALLOCATOR.
		vector<int,CMyAllocator<int>>							Vector1({10,20,30,40},Allocator);

		PrintCollection(L"VECTOR 1",Vector1);

		PrintLineSeparator();

		// 1. PARAMETER definuje BEGIN ITERATOR odkial sa bude COLLECTION initializovat.
		// 2. PARAMETER definuje END ITERATOR odkial sa bude COLLECTION initializovat.
		// 3. PARAMETER definuje CUSTOM ALLOCATOR.
		vector<int,CMyAllocator<int>>							Vector2(Vector1.cbegin(),Vector1.cend(),Allocator);

		PrintCollection(L"VECTOR 2",Vector2);

		PrintLineSeparator();

		// Vytvori COLLECTION s 3 ITEMS, ktore su inicializovane VALUE prenesenou v 2. PARAMETER.
		// 1. PARAMETER definuje pocet ITEMS na ktore sa ma COLLECTION inicializovat.
		// 2. PARAMETER definuje VALUE, ktora sa skopiruje do inicializovanych ITEMS.
		// 3. PARAMETER definuje CUSTOM ALLOCATOR.
		vector<int,CMyAllocator<int>>							Vector3(3,999,Allocator);

		PrintCollection(L"VECTOR 3",Vector3);

		PrintLineSeparator();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

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
	//TestSizeOperations();
	//TestComparisonOperators();
	//TestCount();
	//TestFind();
	//TestLowerBound();
	//TestUpperBound();
	//TestEqualBound();
	//TestOperatorAssignment();
	//TestAssign();
	//TestFill();
	//TestSwap();
	//TestAt1();
	//TestAt2();
	//TestOperatorSubscript1();
	//TestOperatorSubscript2();
	//TestFront();
	//TestBack();
	//TestData();
	//TestIterators();
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
	TestErase();
	//TestPopFrontPopBack();
	//TestClear();
	//TestResize();
	//TestRemoveRemoveIf();
	//TestUnique();
	//TestSplice1();
	//TestSplice2();
	//TestSplice3();
	//TestSort();
	//TestMerge1();
	//TestMerge2();
	//TestMerge3();
	//TestMerge4();
	//TestReverse();
	//TestBeforeBegin();
	//TestInsertAfter();
	//TestEmplaceAfter();
	//TestEraseAfter();
	//TestSpliceAfter1();
	//TestSpliceAfter2();
	//TestSpliceAfter3();
	//TestCapacity();
	//TestCompareMethods();
	//TestLoadFactor1();
	//TestLoadFactor2();
	//TestReserve();
	//TestShrinkToFit();
	//TestRehash();
	//TestBuckets1();
	//TestBuckets2();
	//TestGetAllocator();
	//TestCollectionConstructorWithAllocator1();
	//TestCollectionConstructorWithAllocator2();
	//TestCollectionConstructorWithAllocator3();
	//TestCollectionConstructorWithAllocator4();
	//TestCollectionConstructorWithAllocator5();
	//TestCollectionConstructorWithAllocator6();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------