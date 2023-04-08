//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <deque>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include <iterator>
#include "FunctorPrintItem.h"
#include "FunctorPrintItem.cpp"
#include "StandardPredicateFindFunctor.h"
#include "Name.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
int Compare(const void* Value1, const void* Value2)
{
	return((*(int*)Value1)-(*(int*)Value2));
}
//-------------------------------------------------------------------------------------------------------
void GlobalPrintFullName(CName* Name)
{
	wcout << L"Name: [" << Name->GetFirstName() << L" " << Name->GetLastName() << L"], Age: [" << Name->GetAge() << "] !\n";
}
//-------------------------------------------------------------------------------------------------------
int IncreaseBy10(int Value)
{
	Value+=10;

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
int Generator(void)
{
	static int													Value=0;

	Value++;

	return(Value);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	vector<wstring>												Names;
	
	Names.push_back(L"Timmy");
	Names.push_back(L"Jenny");
	Names.push_back(L"Atreyu");

	CFunctorPrintItem<wstring>									FunctorPrintItem;

	for_each(Names.begin(),Names.end(),FunctorPrintItem);
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	wstring														Names[]={L"Timmy",L"Jenny",L"Atreyu"};
	int															Length=_countof(Names);

	CFunctorPrintItem<wstring>									FunctorPrintItem;

	wprintf_s(L"Length: [%d] !\n",Length);

	// !!! KONCOVY ITERATOR musi odkazovat az za (LAST_ITEM+1). V tomto pripade je to 3.
	for_each(&Names[0],&Names[Length],FunctorPrintItem);
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	vector<wstring>												Names;

	Names.push_back(L"Timmy");
	Names.push_back(L"Jenny");
	Names.push_back(L"Atreyu");

	vector<wstring>::iterator									Result1=find(Names.begin(),Names.end(),L"Jenny");
	vector<wstring>::iterator									Result2=find(Names.begin(),Names.end(),L"XXX");

	// !!! Ak ITEM NIE JE NAJDENY je vrateny KONCOVY ITERATOR.
	if (Result1!=Names.end())
	{
		wprintf_s(L"[Jenny] FOUND [%s] !\n",(*Result1).c_str());
	}
	else
	{
		wprintf_s(L"[Jenny] NOT FOUND !\n");
	}

	// !!! Ak ITEM NIE JE NAJDENY je vrateny KONCOVY ITERATOR.
	if (Result2!=Names.end())
	{
		wprintf_s(L"[XXX] FOUND [%s] !\n",(*Result2).c_str());
	}
	else
	{
		wprintf_s(L"[XXX] NOT FOUND !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	vector<wstring>												Names;

	Names.push_back(L"Timmy");
	Names.push_back(L"Jenny");
	Names.push_back(L"Atreyu");

	wprintf_s(L"BEFORE SORT:\n");

	for_each(Names.begin(),Names.end(),CFunctorPrintItem<wstring>());

	wprintf_s(L"\n");

	wprintf_s(L"AFTER SORT:\n");

	// !!! Pouzivam STANDARDNY FUNCTOR typu PREDICATE.
	sort(Names.begin(),Names.end(),less<wstring>());

	for_each(Names.begin(),Names.end(),CFunctorPrintItem<wstring>());
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	vector<wstring>												Names;

	Names.push_back(L"Timmy");
	Names.push_back(L"Jenny");
	Names.push_back(L"Atreyu");

	CStandardPredicateFindFunctor								FindFunctor1(L"Jenny");
	CStandardPredicateFindFunctor								FindFunctor2(L"XXX");

	vector<wstring>::iterator									Result1=find_if(Names.begin(),Names.end(),FindFunctor1);
	vector<wstring>::iterator									Result2=find_if(Names.begin(),Names.end(),FindFunctor2);

	// !!! Ak ITEM NIE JE NAJDENY je vrateny KONCOVY ITERATOR.
	if (Result1!=Names.end())
	{
		wprintf_s(L"[Jenny] FOUND [%s] !\n",(*Result1).c_str());
	}
	else
	{
		wprintf_s(L"[Jenny] NOT FOUND !\n");
	}

	// !!! Ak ITEM NIE JE NAJDENY je vrateny KONCOVY ITERATOR.
	if (Result2!=Names.end())
	{
		wprintf_s(L"[XXX] FOUND [%s] !\n",(*Result2).c_str());
	}
	else
	{
		wprintf_s(L"[XXX] NOT FOUND !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	vector<int>													Numbers;

	Numbers.push_back(4);
	Numbers.push_back(3);
	Numbers.push_back(1);
	Numbers.push_back(6);
	Numbers.push_back(8);

	// !!! Pomocou BINDER najde PRVE CISLO MENSIE ako 5.
	vector<int>::iterator										Result1=find_if(Numbers.begin(),Numbers.end(),bind2nd(less<int>(),5));
	// !!! Pomocou BINDER a UNARY NEGATER najde PRVE CISLO VACSIE, alebo ROVNE ako 5.
	vector<int>::iterator										Result2=find_if(Numbers.begin(),Numbers.end(),not1(bind2nd(less<int>(),5)));
	// !!! Pomocou BINDER a BINARY NEGATER najde PRVE CISLO VACSIE, alebo ROVNE ako 7.
	vector<int>::iterator										Result3=find_if(Numbers.begin(),Numbers.end(),bind2nd(not2(less<int>()),7));

	// !!! Ak ITEM NIE JE NAJDENY je vrateny KONCOVY ITERATOR.
	if (Result1!=Numbers.end())
	{
		wprintf_s(L"Number LOWER than 5 FOUND [%d] !\n",(*Result1));
	}
	else
	{
		wprintf_s(L"Number LOWER than 5 NOT FOUND !\n");
	}

	// !!! Ak ITEM NIE JE NAJDENY je vrateny KONCOVY ITERATOR.
	if (Result2!=Numbers.end())
	{
		wprintf_s(L"Number GREATER of EQUAL than 5 [%d] !\n",(*Result2));
	}
	else
	{
		wprintf_s(L"Number GREATER of EQUAL than 5 NOT FOUND !\n");
	}

	// !!! Ak ITEM NIE JE NAJDENY je vrateny KONCOVY ITERATOR.
	if (Result3!=Numbers.end())
	{
		wprintf_s(L"Number GREATER of EQUAL than 7 [%d] !\n",(*Result3));
	}
	else
	{
		wprintf_s(L"Number GREATER of EQUAL than 7 NOT FOUND !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	vector<CName>												VectorReferences;
	vector<CName*>												VectorPointers;

	VectorReferences.push_back(CName(L"Timmy",L"Anderson",12));
	VectorReferences.push_back(CName(L"Atreyu",L"",12));
	VectorReferences.push_back(CName(L"Jenny",L"Thompson",13));

	CName														Name1(L"Timmy",L"Anderson",12);
	CName														Name2(L"Atreyu",L"",12);
	CName														Name3(L"Jenny",L"Thompson",13);

	VectorPointers.push_back(&Name1);
	VectorPointers.push_back(&Name2);
	VectorPointers.push_back(&Name3);

	wprintf_s(L"METHODS CALLED by REFERENCE:\n");

	// !!! Pouzivam POINTER na MEMBER (METHOD).
	for_each(VectorReferences.begin(),VectorReferences.end(),mem_fun_ref(&CName::PrintFullName));

	wprintf_s(L"\n");

	wprintf_s(L"METHODS CALLED by POINTER:\n");

	// !!! Pouzivam POINTER na MEMBER (METHOD).
	for_each(VectorPointers.begin(),VectorPointers.end(),mem_fun(&CName::PrintFullName));

	wprintf_s(L"\n");

	wprintf_s(L"FUNCTIONS CALLED by POINTER:\n");

	for_each(VectorPointers.begin(),VectorPointers.end(),ptr_fun(&GlobalPrintFullName));
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;

	Vector1.push_back(3);
	Vector1.push_back(6);
	Vector1.push_back(7);
	Vector1.push_back(2);
	Vector1.push_back(12);
	Vector1.push_back(1);

	Vector2.push_back(4);
	Vector2.push_back(12);
	Vector2.push_back(8);
	Vector2.push_back(1);
	Vector2.push_back(10);
	Vector2.push_back(2);

	// Najde 1. ITEM vo 'Vector1', ktory je zaroven i vo 'Vector2'.
	vector<int>::iterator										Item1=find_first_of(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end());

	if (Item1!=Vector1.end())
	{
		wprintf_s(L"ITEM1: [%d] !\n",*Item1);

		// Najde 2. ITEM vo 'Vector1', ktory je zaroven i vo 'Vector2'.
		vector<int>::iterator									Item2=find_first_of(Item1+1,Vector1.end(),Vector2.begin(),Vector2.end());

		if (Item2!=Vector1.end())
		{
			wprintf_s(L"ITEM2: [%d] !\n",*Item2);
		}
		else
		{
			wprintf_s(L"ITEM2 was NOT FOUND !\n");
		}
	}
	else
	{
		wprintf_s(L"ITEM1 was NOT FOUND !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(6);
	Vector.push_back(6);
	Vector.push_back(2);
	Vector.push_back(12);
	Vector.push_back(12);

	// Najde 1. DVOJICU ZHODNYCH ITEMS.
	vector<int>::iterator										Item1=adjacent_find(Vector.begin(),Vector.end());

	if (Item1!=Vector.end())
	{
		wprintf_s(L"ITEM1: [%d] !\n",*Item1);

		// Najde 2. DVOJICU ZHODNYCH ITEMS.
		vector<int>::iterator									Item2=adjacent_find(Item1+1,Vector.end());

		if (Item2!=Vector.end())
		{
			wprintf_s(L"ITEM2: [%d] !\n",*Item2);
		}
		else
		{
			wprintf_s(L"ITEM2 was NOT FOUND !\n");
		}
	}
	else
	{
		wprintf_s(L"ITEM1 was NOT FOUND !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(6);
	Vector.push_back(14);
	Vector.push_back(2);
	Vector.push_back(12);
	Vector.push_back(22);
	Vector.push_back(122);
	
	size_t														Count=count_if(Vector.begin(),Vector.end(),bind2nd(greater<int>(),10));

	wprintf_s(L"Count: [%d] !\n",Count);
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;
	vector<int>													Vector3;

	Vector1.push_back(3);
	Vector1.push_back(6);
	Vector1.push_back(14);

	Vector2.push_back(3);
	Vector2.push_back(16);
	Vector2.push_back(14);

	// Zhodny s 'Vector1'.
	Vector3.push_back(3);
	Vector3.push_back(6);
	Vector3.push_back(14);

	pair<vector<int>::iterator,vector<int>::iterator>			Pair1=mismatch(Vector1.begin(),Vector1.end(),Vector2.begin());

	if (Pair1.first!=Vector1.end() && Pair1.second!=Vector2.end())
	{
		wprintf_s(L"COLLECTIONS 1 a 2 ARE DIFFERENT at ITEMS [%d,%d] !\n",*Pair1.first,*Pair1.second);
	}
	else
	{
		wprintf_s(L"COLLECTIONS 1 a 2 ARE SAME !\n");
	}

	pair<vector<int>::iterator,vector<int>::iterator>			Pair2=mismatch(Vector1.begin(),Vector1.end(),Vector3.begin());

	if (Pair2.first!=Vector1.end() && Pair2.second!=Vector3.end())
	{
		wprintf_s(L"COLLECTIONS 1 a 3 ARE DIFFERENT at ITEMS [%d,%d] !\n",*Pair2.first,*Pair2.second);
	}
	else
	{
		wprintf_s(L"COLLECTIONS 1 a 3 ARE SAME !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;

	Vector1.push_back(3);
	Vector1.push_back(5);
	Vector1.push_back(4);
	Vector1.push_back(12);
	Vector1.push_back(32);
	Vector1.push_back(5);
	Vector1.push_back(4);
	Vector1.push_back(17);

	Vector2.push_back(5);
	Vector2.push_back(4);

	vector<int>::iterator										Item1=search(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end());

	if (Item1!=Vector1.end())
	{
		wprintf_s(L"COLLECTION 2 was FOUND in COLLECTION 1 at POSITION [%d] !\n",(Item1-Vector1.begin()));
	}
	else
	{
		wprintf_s(L"COLLECTION 2 was NOT FOUND in COLLECTION 1 !\n");
	}

	// !!! Hlada COLLECTION 2 v COLLECTION 1 ZOZADU smerom DOPREDU.
	vector<int>::iterator										Item2=find_end(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end());

	// !!! Ak sa NENAJDE ITEM vracia KONCOVY ITERATOR COLLECTION 1.
	if (Item2!=Vector1.end())
	{
		wprintf_s(L"COLLECTION 2 was FOUND in COLLECTION 1 at POSITION [%d] !\n",(Item2-Vector1.begin()));
	}
	else
	{
		wprintf_s(L"COLLECTION 2 was NOT FOUND in COLLECTION 1 !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(5);
	Vector.push_back(4);
	Vector.push_back(12);
	Vector.push_back(12);
	Vector.push_back(5);
	Vector.push_back(4);
	Vector.push_back(12);
	Vector.push_back(12);
	Vector.push_back(12);
	Vector.push_back(17);

	// Hlada 3 vyskyty hodnoty 12 v COLLECTION
	vector<int>::iterator										Item=search_n(Vector.begin(),Vector.end(),3,12);
	
	if (Item!=Vector.end())
	{
		wprintf_s(L"ITEM [12] was FOUND at POSITION [%d] !\n",(Item-Vector.begin()));
	}
	else
	{
		wprintf_s(L"ITEM [12] was NOT FOUND in COLLECTION !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(5);
	Vector.push_back(4);
	Vector.push_back(2);
	Vector.push_back(8);
	Vector.push_back(11);
	Vector.push_back(4);
	Vector.push_back(12);

	vector<int>													OutputVector;

	// !!! Pouzijem back_inserter(), aby som skopirovane ITEMS mohol ukladat do OutputVector.
	copy(Vector.begin(),Vector.end(),back_inserter(OutputVector));

	wprintf_s(L"COPY:\n");

	for_each(OutputVector.begin(),OutputVector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");

	vector<int>													OutputVectorBack;

	// !!! Musim alokovat MIESTO pre OutputVectorBack, kedze NEPOUZIVAM INSERTER.
	OutputVectorBack.resize(Vector.size(),0);

	copy_backward(Vector.begin(),Vector.end(),OutputVectorBack.rend());

	wprintf_s(L"COPY BACKWARD:\n");

	for_each(OutputVectorBack.begin(),OutputVectorBack.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(5);
	Vector.push_back(4);

	vector<int>													OutputVector;

	// !!! Pouzijem back_inserter(), aby som skopirovane ITEMS mohol ukladat do OutputVector.
	transform(Vector.begin(),Vector.end(),back_inserter(OutputVector),ptr_fun(IncreaseBy10));

	wprintf_s(L"VECTOR:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");

	wprintf_s(L"OUTPUT VECTOR:\n");

	for_each(OutputVector.begin(),OutputVector.end(),CFunctorPrintItem<int>());

	// !!! Modifikujem samotny Vector tym, ze vysledok TRANSFORM vkladat SPAT do TEJ ISTEJ COLLECTION.
	transform(Vector.begin(),Vector.end(),Vector.begin(),ptr_fun(IncreaseBy10));

	wprintf_s(L"\n");

	wprintf_s(L"OUTPUT VECTOR after TRANSFORM:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(5);
	Vector.push_back(4);
	Vector.push_back(12);
	Vector.push_back(12);
	Vector.push_back(5);
	Vector.push_back(4);
	Vector.push_back(11);
	Vector.push_back(11);
	Vector.push_back(11);
	Vector.push_back(17);

	vector<int>													OutputVector;

	unique_copy(Vector.begin(),Vector.end(),back_inserter(OutputVector));

	wprintf_s(L"VECTOR:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");

	wprintf_s(L"OUTPUT VECTOR:\n");

	for_each(OutputVector.begin(),OutputVector.end(),CFunctorPrintItem<int>());

	// !!! Modifikuje samotny Vector tak, ze na ZACIATKU COLLECTION budu UNIKATNE ITEMS.
	vector<int>::iterator										EndOfUniqueCollection=unique(Vector.begin(),Vector.end());

	wprintf_s(L"\n");

	wprintf_s(L"VECTOR after UNIQUE:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");
	wprintf_s(L"Number of UNIQUE ITEMS: [%d] !\n",(EndOfUniqueCollection-Vector.begin()));
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(5);
	Vector.push_back(4);

	vector<int>													OutputVector;

	replace_copy(Vector.begin(),Vector.end(),back_inserter(OutputVector),5,16);

	wprintf_s(L"VECTOR:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");

	wprintf_s(L"OUTPUT VECTOR:\n");

	for_each(OutputVector.begin(),OutputVector.end(),CFunctorPrintItem<int>());

	replace(Vector.begin(),Vector.end(),5,16);

	wprintf_s(L"\n");

	wprintf_s(L"VECTOR after REPLACE:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(5);
	Vector.push_back(4);

	vector<int>													OutputVector;

	remove_copy(Vector.begin(),Vector.end(),back_inserter(OutputVector),5);

	wprintf_s(L"VECTOR:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");

	wprintf_s(L"OUTPUT VECTOR:\n");

	for_each(OutputVector.begin(),OutputVector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");

	// !!! Modifikuje samotny Vector tak, ze na ZACIATKU COLLECTION budu NEODSTRANENE ITEMS.
	vector<int>::iterator										EndOfCollection=remove(Vector.begin(),Vector.end(),5);

	wprintf_s(L"VECTOR after REMOVE:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"Number of ITEMS: [%d] !\n",(EndOfCollection-Vector.begin()));
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);

	fill(Vector.begin(),Vector.end(),10);

	wprintf_s(L"VECTOR after FILL:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	wprintf_s(L"\n");

	wprintf_s(L"VECTOR after GENERATE:\n");

	generate(Vector.begin(),Vector.end(),Generator);

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);

	// !!! MIDDLE ITERATOR urcuje kolko rotacii sa ma spravit.
	rotate(Vector.begin(),Vector.begin()+2,Vector.end());

	wprintf_s(L"VECTOR after ROTATE:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);

	reverse(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after REVERSE:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test22(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);

	random_shuffle(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after SHUFFLE:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test23(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);

	swap_ranges(Vector.begin(),Vector.begin()+2,Vector.begin()+2);

	wprintf_s(L"VECTOR after SWAP RANGES:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test24(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);

	iter_swap(Vector.begin(),Vector.begin()+2);

	wprintf_s(L"VECTOR after ITER SWAP:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test25(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(1);
	Vector.push_back(4);
	Vector.push_back(6);
	Vector.push_back(5);
	Vector.push_back(2);
	Vector.push_back(2);
	Vector.push_back(4);

	sort(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after SORT:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test26(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(1);
	Vector.push_back(4);
	Vector.push_back(6);
	Vector.push_back(5);
	Vector.push_back(2);
	Vector.push_back(2);
	Vector.push_back(4);

	// !!! Vykonam SORT PRVYCH 4 ITEMS.
	partial_sort(Vector.begin(),Vector.begin()+4,Vector.end());

	wprintf_s(L"VECTOR after PARTIAL SORT:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test27(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(1);
	Vector.push_back(4);
	Vector.push_back(6);
	Vector.push_back(5);
	Vector.push_back(2);
	Vector.push_back(2);
	Vector.push_back(4);

	nth_element(Vector.begin(),Vector.begin()+3,Vector.end());

	wprintf_s(L"VECTOR after Nth ELEMENT:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test28(void)
{
	vector<int>													Vector;

	Vector.push_back(3);
	Vector.push_back(1);
	Vector.push_back(4);
	Vector.push_back(6);
	Vector.push_back(5);
	Vector.push_back(2);
	Vector.push_back(2);
	Vector.push_back(4);

	// !!! COLLECTION MUSI BYT SORTED.
	sort(Vector.begin(),Vector.end());

	pair<vector<int>::iterator,vector<int>::iterator>			Pair=equal_range(Vector.begin(),Vector.end(),2);

	wprintf_s(L"POSITION of 2: [%d,%d] !\n",(Pair.first-Vector.begin()),(Pair.second-Vector.begin()));
}
//-------------------------------------------------------------------------------------------------------
void Test29(void)
{
	vector<int>													Vector;

	// 1. CAST COLLECTION.
	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	// 2. CAST COLLECTION.
	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	// !!! Obe casti COLLECTION MUSIA byt SORTED.
	inplace_merge(Vector.begin(),Vector.begin()+3,Vector.end());

	wprintf_s(L"VECTOR after INPLACE MERGE:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test30(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;
	vector<int>													VectorOut;

	Vector1.push_back(1);
	Vector1.push_back(2);
	Vector1.push_back(3);

	Vector2.push_back(1);
	Vector2.push_back(2);
	Vector2.push_back(3);

	// !!! Obe COLLECTIONS MUSIA byt SORTED.
	merge(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end(),back_inserter(VectorOut));

	wprintf_s(L"VECTOR after MERGE:\n");

	for_each(VectorOut.begin(),VectorOut.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test31(void)
{
	vector<int>													Vector;

	Vector.push_back(4);
	Vector.push_back(12);
	Vector.push_back(13);
	Vector.push_back(1);
	Vector.push_back(8);
	Vector.push_back(6);

	// !!! COLLECTION MUSI byt SORTED.
	sort(Vector.begin(),Vector.end());

	partition(Vector.begin(),Vector.end(),bind2nd(greater<int>(),10));

	wprintf_s(L"VECTOR after PARTITION:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test32(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;
	vector<int>													VectorOut;

	Vector1.push_back(2);
	Vector1.push_back(14);
	Vector1.push_back(5);
	Vector1.push_back(6);
	Vector1.push_back(1);

	Vector2.push_back(8);
	Vector2.push_back(18);
	Vector2.push_back(2);
	Vector2.push_back(1);
	Vector2.push_back(13);

	sort(Vector1.begin(),Vector1.end());
	sort(Vector2.begin(),Vector2.end());

	// !!! Vrati ITEMS, ktore su v COLLECTION 1, ale NIE SU v COLLECTION 2.
	set_difference(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end(),back_inserter(VectorOut));

	wprintf_s(L"VECTOR after SET DIFFERENCE:\n");

	for_each(VectorOut.begin(),VectorOut.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test33(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;
	vector<int>													VectorOut;

	Vector1.push_back(2);
	Vector1.push_back(14);
	Vector1.push_back(5);
	Vector1.push_back(6);
	Vector1.push_back(1);

	Vector2.push_back(8);
	Vector2.push_back(18);
	Vector2.push_back(2);
	Vector2.push_back(1);
	Vector2.push_back(13);

	sort(Vector1.begin(),Vector1.end());
	sort(Vector2.begin(),Vector2.end());

	// !!! Vrati ITEMS, ktore su v COLLECTION 1, alebo COLLECTION 2, ale NIE v OBOCH.
	set_symmetric_difference(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end(),back_inserter(VectorOut));

	wprintf_s(L"VECTOR after SET SYMMETRIC DIFFERENCE:\n");

	for_each(VectorOut.begin(),VectorOut.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test34(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;
	vector<int>													VectorOut;

	Vector1.push_back(2);
	Vector1.push_back(14);
	Vector1.push_back(5);
	Vector1.push_back(6);
	Vector1.push_back(1);

	Vector2.push_back(8);
	Vector2.push_back(18);
	Vector2.push_back(2);
	Vector2.push_back(1);
	Vector2.push_back(13);

	sort(Vector1.begin(),Vector1.end());
	sort(Vector2.begin(),Vector2.end());

	set_union(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end(),back_inserter(VectorOut));

	wprintf_s(L"VECTOR after SET UNION:\n");

	for_each(VectorOut.begin(),VectorOut.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test35(void)
{
	vector<int>													Vector1;
	vector<int>													Vector2;
	vector<int>													VectorOut;

	Vector1.push_back(2);
	Vector1.push_back(14);
	Vector1.push_back(5);
	Vector1.push_back(6);
	Vector1.push_back(1);

	Vector2.push_back(8);
	Vector2.push_back(18);
	Vector2.push_back(2);
	Vector2.push_back(1);
	Vector2.push_back(13);

	sort(Vector1.begin(),Vector1.end());
	sort(Vector2.begin(),Vector2.end());

	set_intersection(Vector1.begin(),Vector1.end(),Vector2.begin(),Vector2.end(),back_inserter(VectorOut));

	wprintf_s(L"VECTOR after SET INTERSECTION:\n");

	for_each(VectorOut.begin(),VectorOut.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test36(void)
{
	vector<int>													Vector;

	Vector.push_back(2);
	Vector.push_back(14);
	Vector.push_back(5);
	Vector.push_back(6);
	Vector.push_back(1);

	make_heap(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after MAKE HEAP:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	Vector.push_back(7);
	push_heap(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after PUSH HEAP 7:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	Vector.push_back(10);
	push_heap(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after PUSH HEAP 10:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	sort_heap(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after SORT HEAP:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test37(void)
{
	vector<int>													Vector;

	Vector.push_back(2);
	Vector.push_back(14);
	Vector.push_back(5);
	Vector.push_back(6);
	Vector.push_back(1);

	vector<int>::iterator										MinElement=min_element(Vector.begin(),Vector.end());
	vector<int>::iterator										MaxElement=max_element(Vector.begin(),Vector.end());

	wprintf_s(L"MIN: [%d] !\n",*MinElement);
	wprintf_s(L"MAX: [%d] !\n",*MaxElement);
}
//-------------------------------------------------------------------------------------------------------
void Test38(void)
{
	wstring														Name1=L"Timmy Anderson";
	wstring														Name2=L"TIMMY ANDERSON";

	// !!! Vykona sa LEXIKOGRAFICKE POROVNANIE.
	bool														Compare1=lexicographical_compare(Name1.begin(),Name1.end(),Name2.begin(),Name2.end());

	if (Compare1==true)
	{
		wprintf_s(L"STRING 1 is SMALER than STRING 2 !\n");
	}
	else
	{
		wprintf_s(L"STRING 1 is EQUAL or GREATER than STRING 2 !\n");
	}

	// !!! Vykona sa LEXIKOGRAFICKE POROVNANIE.
	bool														Compare2=lexicographical_compare(Name2.begin(),Name2.end(),Name1.begin(),Name1.end());

	if (Compare2==true)
	{
		wprintf_s(L"STRING 2 is SMALER than STRING 1 !\n");
	}
	else
	{
		wprintf_s(L"STRING 2 is EQUAL or GREATER than STRING 1 !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test39(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);
	Vector.push_back(4);
	Vector.push_back(5);
	Vector.push_back(6);

	next_permutation(Vector.begin(),Vector.end());
	next_permutation(Vector.begin(),Vector.end());
	next_permutation(Vector.begin(),Vector.end());
	next_permutation(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after NEXT PERMUTATION:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());

	prev_permutation(Vector.begin(),Vector.end());
	prev_permutation(Vector.begin(),Vector.end());
	prev_permutation(Vector.begin(),Vector.end());
	prev_permutation(Vector.begin(),Vector.end());

	wprintf_s(L"VECTOR after PREV PERMUTATION:\n");

	for_each(Vector.begin(),Vector.end(),CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
void Test40(void)
{
	int															Values[]={40,10,100,90,20,25};

	qsort(Values,6,sizeof(int),Compare);

	wprintf_s(L"SORTED ARRAY:\n");

	for_each(&Values[0],&Values[_countof(Values)],CFunctorPrintItem<int>());
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	//Test8();
	//Test9();
	//Test10();
	//Test11();
	//Test12();
	//Test13();
	//Test14();
	//Test15();
	//Test16();
	//Test17();
	//Test18();
	//Test19();
	//Test20();
	//Test21();
	//Test22();
	//Test23();
	//Test24();
	//Test25();
	//Test26();
	//Test27();
	//Test28();
	//Test29();
	//Test30();
	//Test31();
	//Test32();
	//Test33();
	//Test34();
	//Test35();
	//Test36();
	//Test37();
	//Test38();
	//Test39();
	Test40();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------