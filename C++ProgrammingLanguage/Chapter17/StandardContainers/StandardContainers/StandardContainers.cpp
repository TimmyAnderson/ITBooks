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
#include <valarray>
#include <bitset>
#include "MyIntComparatorFunctor.h"
#include "IntEqualFunctor.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	map<int,wstring>											Map1;

	Map1[100]=L"Timmy Anderson";
	Map1[200]=L"Jenny Thompson";
	Map1[50]=L"Atreyu";

	wprintf_s(L"MAP with DEFAULT ITERATOR COMPARER:\n");

	// !!!!! ITERATOR je SORTED podla hodnoty typu 'key_compare', ktora je standardne nastavena na OPERATOR<.
	for (map<int,wstring>::iterator i=Map1.begin();i!=Map1.end();i++)
	{
		const pair<int,wstring>&								Pair=*i;

		wprintf_s(L"Item [%d]: [%s] !\n",Pair.first,Pair.second.c_str());
	}

	wprintf_s(L"\n");

	// !!! CLASS greater<int> je FUNCTOR - CLASS s pretazenym OPERATOR().
	map<int,wstring,greater<int>>								Map2;

	Map2[100]=L"Timmy Anderson";
	Map2[200]=L"Jenny Thompson";
	Map2[50]=L"Atreyu";

	wprintf_s(L"MAP with GREATER ITERATOR COMPARER:\n");

	// !!!!! ITERATOR je SORTED podla hodnoty typu 'key_compare', ktora je nastavena na OPERATOR>.
	for (map<int,wstring,greater<int>>::iterator i=Map2.begin();i!=Map2.end();i++)
	{
		const pair<int,wstring>&								Pair=*i;

		wprintf_s(L"Item [%d]: [%s] !\n",Pair.first,Pair.second.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	// !!! Definujem CUSTOM FUNCTOR.
	map<int,wstring,CMyIntComparatorFunctor>					Map;

	Map[100]=L"Timmy Anderson";
	Map[200]=L"Jenny Thompson";
	Map[50]=L"Atreyu";

	wprintf_s(L"MAP with CUSTOM COMPARATOR FUNCTOR:\n");

	// !!!!! ITERATOR je SORTED podla hodnoty typu 'key_compare', ktora je nastavena na CUSTOM FUNCTOR CMyIntComparerFunctor.
	for (map<int,wstring,CMyIntComparatorFunctor>::iterator i=Map.begin();i!=Map.end();i++)
	{
		const pair<int,wstring>&								Pair=*i;

		wprintf_s(L"Item [%d]: [%s] !\n",Pair.first,Pair.second.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	list<int>													List;

	List.push_back(10);
	// Umoznuje pridavat ITEMS aj na ZACIATOK.
	List.push_front(12);
	List.push_back(35);

	wprintf_s(L"LIST:\n");

	for (list<int>::iterator i=List.begin();i!=List.end();i++)
	{
		wprintf_s(L"Item: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	list<int>													List1;
	list<int>													List2;

	List1.push_back(1);
	List1.push_back(2);
	List1.push_back(3);
	List1.push_back(4);
	
	List2.push_back(11);
	List2.push_back(12);
	List2.push_back(13);
	List2.push_back(14);

	wprintf_s(L"LIST 1:\n");

	for (list<int>::iterator i=List1.begin();i!=List1.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	wprintf_s(L"LIST 2:\n");

	for (list<int>::iterator i=List2.begin();i!=List2.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	list<int>::iterator											List1PushIterator=List1.begin();

	List1PushIterator++;
	List1PushIterator++;

	list<int>::iterator											List2PopIteratorStart=List2.begin();
	list<int>::iterator											List2PopIteratorEnd=List2.begin();

	List2PopIteratorStart++;
	List2PopIteratorStart++;

	List2PopIteratorEnd++;
	List2PopIteratorEnd++;
	List2PopIteratorEnd++;
	List2PopIteratorEnd++;

	// Vykonam SPLICE.
	List1.splice(List1PushIterator,List2,List2PopIteratorStart,List2PopIteratorEnd);

	wprintf_s(L"LIST 1 after SPLICE:\n");

	for (list<int>::iterator i=List1.begin();i!=List1.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	wprintf_s(L"LIST 2 after SPLICE:\n");

	for (list<int>::iterator i=List2.begin();i!=List2.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	list<int>													List1;
	list<int>													List2;

	List1.push_back(4);
	List1.push_back(1);
	List1.push_back(3);
	List1.push_back(2);
	
	List2.push_back(12);
	List2.push_back(13);
	List2.push_back(11);
	List2.push_back(14);

	wprintf_s(L"LIST 1:\n");

	for (list<int>::iterator i=List1.begin();i!=List1.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	wprintf_s(L"LIST 2:\n");

	for (list<int>::iterator i=List2.begin();i!=List2.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	List1.sort();
	List2.sort();

	// !!! Ak by NIEKTORY LIST NEBOL SORTED - hodi ASSERT ERROR.
	List1.merge(List2);

	wprintf_s(L"LIST 1 after MERGE:\n");

	for (list<int>::iterator i=List1.begin();i!=List1.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	wprintf_s(L"LIST 2 after MERGE:\n");

	for (list<int>::iterator i=List2.begin();i!=List2.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	list<int>													List;

	List.push_back(4);
	List.push_back(1);
	List.push_back(3);
	List.push_back(2);
	List.push_back(8);

	wprintf_s(L"LIST:\n");

	for (list<int>::iterator i=List.begin();i!=List.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	CIntEqualFunctor											Functor;

	List.remove_if(Functor);

	wprintf_s(L"LIST after REMOVE_IF:\n");

	for (list<int>::iterator i=List.begin();i!=List.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	list<int>													List;

	List.push_back(4);
	List.push_back(1);
	List.push_back(3);
	List.push_back(2);
	List.push_back(3);
	List.push_back(8);
	List.push_back(4);

	wprintf_s(L"LIST:\n");

	for (list<int>::iterator i=List.begin();i!=List.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	// !!! LIST MUSI byt SORTED pred volanim unique().
	List.sort();

	List.unique();

	wprintf_s(L"LIST after UNIQUE:\n");

	for (list<int>::iterator i=List.begin();i!=List.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	list<int>													List;

	List.push_back(4);
	List.push_back(1);
	List.push_back(3);
	List.push_back(2);
	List.push_back(8);

	wprintf_s(L"LIST:\n");

	for (list<int>::iterator i=List.begin();i!=List.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	List.reverse();

	wprintf_s(L"LIST after REVERSE:\n");

	for (list<int>::iterator i=List.begin();i!=List.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	deque<int>													Deque;

	Deque.push_back(4);
	Deque.push_front(1);
	Deque.push_back(3);
	Deque.push_front(2);
	Deque.push_back(8);

	wprintf_s(L"DEQUE:\n");

	for (deque<int>::iterator i=Deque.begin();i!=Deque.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	// !!! DEQUE umoznuje pouzit OPERATOR[].
	wprintf_s(L"Item[2]: [%d] !\n",Deque[2]);
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	stack<int>													Stack;

	Stack.push(4);
	Stack.push(1);
	Stack.push(3);
	Stack.push(2);
	Stack.push(8);
	
	wprintf_s(L"STACK:\n");

	// !!!!! Kedze SEQUENCE ADAPTERS NEMAJU ITERATORS, tak jediny sposob ako vybrat ITEMS z COLLECTION je VYBRAT ich VON z COLLECTION.
	while (Stack.empty()==false)
	{
		int														Value=Stack.top();

		wprintf_s(L"\tItem: [%d] !\n",Value);

		Stack.pop();
	}
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	queue<int>													Queue;

	Queue.push(4);
	Queue.push(1);
	Queue.push(3);
	Queue.push(2);
	Queue.push(8);
	
	wprintf_s(L"QUEUE:\n");
	
	// !!!!! Kedze SEQUENCE ADAPTERS NEMAJU ITERATORS, tak jediny sposob ako vybrat ITEMS z COLLECTION je VYBRAT ich VON z COLLECTION.
	while (Queue.empty()==false)
	{
		int														Value=Queue.front();

		wprintf_s(L"\tItem: [%d] !\n",Value);

		Queue.pop();
	}
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	priority_queue<int>											PriorityQueue;

	PriorityQueue.push(4);
	PriorityQueue.push(1);
	PriorityQueue.push(3);
	PriorityQueue.push(2);
	PriorityQueue.push(8);
	
	wprintf_s(L"STACK:\n");
	
	// !!!!! Kedze SEQUENCE ADAPTERS NEMAJU ITERATORS, tak jediny sposob ako vybrat ITEMS z COLLECTION je VYBRAT ich VON z COLLECTION.
	while (PriorityQueue.empty()==false)
	{
		// !!! Vrati ITEM s NAJVYSSOU HODNOTU.
		int														Value=PriorityQueue.top();

		wprintf_s(L"\tItem: [%d] !\n",Value);

		// !!! Odstrani ITEM s NAJVYSSOU HODNOTU.
		PriorityQueue.pop();
	}
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	map<int,wstring>											Map;

	// !!! ITERATOR je iba HINT. Normalne by mal ukazovat na poziciu, kde bude ITEM skutocne vlozeny a vtedy je INSERT OPTIMALNEJSI.
	Map.insert(Map.begin(),pair<int,wstring>(100,L"Timmy Anderson"));
	// !!! Ukazuje na NESPRAVNU poziciu.
	Map.insert(Map.begin(),pair<int,wstring>(200,L"Jenny Thompson"));
	// !!! Ukazuje na SPRAVNU poziciu.
	Map.insert(Map.begin(),pair<int,wstring>(50,L"Atreyu"));

	wprintf_s(L"MAP:\n");

	for (map<int,wstring>::iterator i=Map.begin();i!=Map.end();i++)
	{
		const pair<int,wstring>&								Pair=*i;

		wprintf_s(L"Item [%d]: [%s] !\n",Pair.first,Pair.second.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	map<wstring,int>											Map;

	// !!! Kedze ITEM este v map<K,T> NEEXISTUJE, tak ho OPERATOR[] PRIDA i s DEFUALT VALUE.
	wprintf_s(L"Key: [%s] - Value: [%d] !\n",L"Timmy Anderson",Map[L"Timmy Anderson"]);

	wprintf_s(L"MAP:\n");

	for (map<wstring,int>::iterator i=Map.begin();i!=Map.end();i++)
	{
		const pair<wstring,int>&								Pair=*i;

		wprintf_s(L"\tItem [%s]: [%d] !\n",Pair.first.c_str(),Pair.second);
	}

	wprintf_s(L"\n");

	// !!! Zmenim hodnotu VALUE pre dany KEY.
	Map[L"Timmy Anderson"]=12;
	
	wprintf_s(L"MAP:\n");

	for (map<wstring,int>::iterator i=Map.begin();i!=Map.end();i++)
	{
		const pair<wstring,int>&								Pair=*i;

		wprintf_s(L"\tItem [%s]: [%d] !\n",Pair.first.c_str(),Pair.second);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	map<int,wstring>											Map;

	Map[1]=L"ONE";
	Map[2]=L"TWO";
	Map[2]=L"TWO";
	Map[3]=L"THREE";
	Map[3]=L"THREE";
	Map[3]=L"THREE";

	wprintf_s(L"MAP:\n");

	for (map<int,wstring>::iterator i=Map.begin();i!=Map.end();i++)
	{
		const pair<int,wstring>&								Pair=*i;

		wprintf_s(L"Item [%d]: [%s] !\n",Pair.first,Pair.second.c_str());
	}

	wprintf_s(L"\n");

	multimap<int,wstring>										MultiMap;

	MultiMap.insert(MultiMap.end(),pair<int,wstring>(1,L"ONE"));
	MultiMap.insert(MultiMap.end(),pair<int,wstring>(2,L"TWO"));
	MultiMap.insert(MultiMap.end(),pair<int,wstring>(2,L"TWO"));
	MultiMap.insert(MultiMap.end(),pair<int,wstring>(3,L"THREE"));
	MultiMap.insert(MultiMap.end(),pair<int,wstring>(3,L"THREE"));
	MultiMap.insert(MultiMap.end(),pair<int,wstring>(3,L"THREE"));

	wprintf_s(L"MULTIMAP:\n");

	for (multimap<int,wstring>::iterator i=MultiMap.begin();i!=MultiMap.end();i++)
	{
		const pair<int,wstring>&								Pair=*i;

		wprintf_s(L"Item [%d]: [%s] !\n",Pair.first,Pair.second.c_str());
	}

	// !!! Hladanie ITEMS pomocou metody equal_range().
	pair<multimap<int,wstring>::iterator,multimap<int,wstring>::iterator>	Iterators;
		
	Iterators=MultiMap.equal_range(3);

	wprintf_s(L"\n");
	wprintf_s(L"MULTIMAP just 3:\n");

	for (multimap<int,wstring>::iterator i=Iterators.first;i!=Iterators.second;i++)
	{
		const pair<int,wstring>&								Pair=*i;

		wprintf_s(L"Item [%d]: [%s] !\n",Pair.first,Pair.second.c_str());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	set<int>													Set;

	Set.insert(Set.end(),1);
	Set.insert(Set.end(),2);
	Set.insert(Set.end(),2);
	Set.insert(Set.end(),3);
	Set.insert(Set.end(),3);
	Set.insert(Set.end(),3);

	wprintf_s(L"SET:\n");

	for (set<int>::iterator i=Set.begin();i!=Set.end();i++)
	{
		wprintf_s(L"Item: [%d] !\n",*i);
	}

	wprintf_s(L"\n");

	multiset<int>												MultiSet;

	MultiSet.insert(MultiSet.end(),1);
	MultiSet.insert(MultiSet.end(),2);
	MultiSet.insert(MultiSet.end(),2);
	MultiSet.insert(MultiSet.end(),3);
	MultiSet.insert(MultiSet.end(),3);
	MultiSet.insert(MultiSet.end(),3);

	wprintf_s(L"MULTISET:\n");

	for (multiset<int>::iterator i=MultiSet.begin();i!=MultiSet.end();i++)
	{
		wprintf_s(L"Item: [%d] !\n",*i);
	}

	// !!! Hladanie ITEMS pomocou metody equal_range().
	pair<multiset<int>::iterator,multiset<int>::iterator>		Iterators;
		
	Iterators=MultiSet.equal_range(3);

	wprintf_s(L"\n");
	wprintf_s(L"MULTISET just 3:\n");

	for (multiset<int>::iterator i=Iterators.first;i!=Iterators.second;i++)
	{
		wprintf_s(L"Item: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	valarray<int>												ValArray(3);

	ValArray[0]=1;
	ValArray[1]=2;
	ValArray[2]=3;

	for (int i=0;i<ValArray.size();i++)
	{
		wprintf_s(L"Item[%d]: [%d] !\n",i,ValArray[i]);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	wstring														String=L"Timmy";

	wprintf_s(L"ITERATION by ITERATORS:\n");

	for(wstring::iterator i=String.begin();i<String.end();i++)
	{
		wprintf_s(L"Item [%c] !\n",*i);
	}

	wprintf_s(L"ITERATION by OPERATOR[]:\n");

	for(int i=0;i<String.length();i++)
	{
		wprintf_s(L"Item [%c] !\n",String[i]);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	// !!! BIT SET ma 10 BITOV.
	bitset<10>													BitSet(255);

	wprintf_s(L"BITSET:\n");

	for(int i=0;i<BitSet.size();i++)
	{
		if (BitSet[i]==1)
		{
			wprintf_s(L"%d",1);
		}
		else
		{
			wprintf_s(L"%d",0);
		}
	}

	wprintf_s(L" !\n");

	try
	{
		// !!! HODI ASSERT a NIE EXCEPTION.
		wprintf_s(L"BitSet[50] [%d] !\n",BitSet[50]);
	}
	catch(const out_of_range& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	// !!! BIT SET sa da inicializovat i pomocou STRING.
	bitset<10>													BitSet("111001010");

	wprintf_s(L"BITSET:\n");

	for(int i=0;i<BitSet.size();i++)
	{
		if (BitSet[i]==1)
		{
			wprintf_s(L"%d",1);
		}
		else
		{
			wprintf_s(L"%d",0);
		}
	}

	wprintf_s(L" !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	// !!! BIT SET sa da inicializovat i pomocou STRING.
	bitset<10>													BitSet1("0111001010");
	bitset<10>													BitSet2("0101000001");

	// BIT AND.
	BitSet1&=BitSet2;

	wprintf_s(L"BITSET1:\n");

	for(int i=0;i<BitSet1.size();i++)
	{
		if (BitSet1[i]==1)
		{
			wprintf_s(L"%d",1);
		}
		else
		{
			wprintf_s(L"%d",0);
		}
	}

	wprintf_s(L" !\n");

	// !!! Pouzitie METODY to_string().
	printf_s("BITSET2: [%s] !\n",BitSet2.to_string().c_str());
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
	Test21();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------