//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <string>
#include <iostream>
#include <chrono>
#include <vector>
#include <deque>
#include <array>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <sstream>
#include <iterator>
#include <functional>
#include <random>
#include "MyDebug.h"
#include "CInt.h"
#include "CFunctionObjectFindByValue.h"
#include "CSimpleObject.h"
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::placeholders;
using namespace std::chrono;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void PrintDuration(wstring Prefix, TType Duration)
{
	milliseconds												DurationInMilliseconds=duration_cast<milliseconds>(Duration);

	wcout << Prefix << L" [" << DurationInMilliseconds.count() << L"] in MILLSECOND !\n";
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVector(void)
{
	PrintLineSeparator();

	vector<int>													Vector;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back((Index+1)*10);
	}

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"INDEX [" << Index << L"] VALUE [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDequeue(void)
{
	PrintLineSeparator();

	deque<int>													Dequeue;

	for(int Index=0;Index<10;Index++)
	{
		Dequeue.push_front((Index+1)*10);
		Dequeue.push_back((Index+1)*100);
	}

	for(size_t Index=0;Index<Dequeue.size();Index++)
	{
		wcout << L"INDEX [" << Index << L"] VALUE [" << Dequeue[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArray(void)
{
	PrintLineSeparator();

	array<int,10>												Array;

	for(int Index=0;Index<10;Index++)
	{
		Array[Index]=((Index+1)*10);
	}

	for(size_t Index=0;Index<Array.size();Index++)
	{
		wcout << L"INDEX [" << Index << L"] VALUE [" << Array[Index] << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestList(void)
{
	PrintLineSeparator();

	list<int>													List;
	
	for(int Index=0;Index<10;Index++)
	{
		List.push_back((Index+1)*10);
	}

	// !!! Pristup k ITEMS je mozne IBA pomocou ITERATION.
	for(int Value : List)
	{
		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();

	// Zmena hodnoty ITEMS.
	for(int& Value : List)
	{
		Value*=2;
	}

	// !!! Iterovanie ITEMS a zaroven ich odstranovanie z LIST.
	while(List.empty()==false)
	{
		wcout << L"VALUE [" << List.front() << L"] !" << endl;

		// Odstrananie ITEM pocas ITERATION.
		List.pop_front();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForwardList(void)
{
	PrintLineSeparator();

	forward_list<int>											ForwardList;
	forward_list<int>::const_iterator							Iterator;
	
	Iterator=ForwardList.before_begin();

	for(int Index=0;Index<10;Index++)
	{
		ForwardList.insert_after(Iterator,(Index+1)*10);
		Iterator++;
	}

	// !!! Pristup k ITEMS je mozne IBA pomocou ITERATION.
	for(int Value : ForwardList)
	{
		wcout << L"VALUE [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSet(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back((Index+1)*10);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v SET SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	set<int>													Set;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		Set.insert(Vector[Index]);
	}

	for(int Value : Set)
	{
		wcout << L"SET [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiSet(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<5;Index++)
	{
		Vector.push_back((Index+1)*10);

		// Vlozia sa 2 ITEMS s tou istou hodnotou.
		Vector.push_back((Index+1)*10);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v MULTISET SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	multiset<int>												MultiSet;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		MultiSet.insert(Vector[Index]);
	}

	for(int Value : MultiSet)
	{
		wcout << L"MULTISET [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMap(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back(Index);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v MAP SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	map<int,char>												Map;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		Map[Vector[Index]]=('A'+char(Vector[Index]));
	}

	// !!! ITEMS v MAP maju podobu PAIR.
	for(const pair<const int,char>& Pair : Map)
	{
		wcout << L"KEY [" << Pair.first << L"] VALUE [" << Pair.second << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultiMap(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<5;Index++)
	{
		Vector.push_back(Index);

		// Vlozia sa 2 ITEMS s tou istou hodnotou.
		Vector.push_back(Index);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v MULTIMAP SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	multimap<int,char>											MultiMap;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		MultiMap.insert(pair<const int,char>(Vector[Index],'A'+char(Vector[Index])));
	}

	// !!! ITEMS v MULTIMAP maju podobu PAIR.
	for(const pair<const int,char>& Pair : MultiMap)
	{
		wcout << L"KEY [" << Pair.first << L"] VALUE [" << Pair.second << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSetVSUnorderedSet(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;
	set<int>													Set;
	unordered_set<int>											UnorderedSet;
	const int													NUMBER_OF_ITERATIONS=1000*1000;
	steady_clock::time_point									Now1;
	steady_clock::time_point									Now2;
	steady_clock::duration										Difference;
	size_t														Count;

	wcout << L"CREATING VECTOR !" << endl;

	for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
	{
		Vector.push_back(Index);
	}

	wcout << L"SHUFFLING VECTOR !" << endl;

	shuffle(Vector.begin(),Vector.end(),Random);

	wcout << L"WORKING !" << endl;

	Now1=steady_clock::now();

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		Set.insert(Vector[Index]);
	}

	Now2=steady_clock::now();

	Difference=Now2-Now1;

	PrintDuration(L"SET INSERT TIME",Difference);

	Now1=steady_clock::now();

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		UnorderedSet.insert(Vector[Index]);
	}

	Now2=steady_clock::now();

	Difference=Now2-Now1;

	PrintDuration(L"UNORDERED SET INSERT TIME",Difference);

	Count=0;

	Now1=steady_clock::now();

	for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
	{
		Count+=Set.count(Vector[Index]);
	}

	Now2=steady_clock::now();

	Difference=Now2-Now1;

	wcout << L"COUNT [" << Count << L"] !" << endl;

	PrintDuration(L"SET ACCESS TIME",Difference);

	Count=0;

	Now1=steady_clock::now();

	for(int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
	{
		Count+=UnorderedSet.count(Vector[Index]);
	}

	Now2=steady_clock::now();

	Difference=Now2-Now1;

	wcout << L"COUNT [" << Count << L"] !" << endl;

	PrintDuration(L"UNORDERED SET ACCESS TIME",Difference);

	Now1=steady_clock::now();

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		Set.erase(Vector[Index]);
	}

	Now2=steady_clock::now();

	Difference=Now2-Now1;

	PrintDuration(L"SET REMOVE TIME",Difference);

	Now1=steady_clock::now();

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		UnorderedSet.erase(Vector[Index]);
	}

	Now2=steady_clock::now();

	Difference=Now2-Now1;

	PrintDuration(L"UNORDERED SET REMOVE TIME",Difference);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedSet(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back((Index+1)*10);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v SET SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	unordered_set<int>											UnorderedSet;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		UnorderedSet.insert(Vector[Index]);
	}

	for(int Value : UnorderedSet)
	{
		wcout << L"UNORDERED SET [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiSet(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<5;Index++)
	{
		Vector.push_back((Index+1)*10);

		// Vlozia sa 2 ITEMS s tou istou hodnotou.
		Vector.push_back((Index+1)*10);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v MULTISET SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	unordered_multiset<int>										UnorderedSetMultiSet;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		UnorderedSetMultiSet.insert(Vector[Index]);
	}

	for(int Value : UnorderedSetMultiSet)
	{
		wcout << L"UNORDERED MULTISET [" << Value << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMap(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back(Index);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v MAP SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	unordered_map<int,char>										UnorderedMap;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		UnorderedMap[Vector[Index]]=('A'+char(Vector[Index]));
	}
	
	// !!! ITEMS v MAP maju podobu PAIR.
	for(const pair<const int,char>& Pair : UnorderedMap)
	{
		wcout << L"KEY [" << Pair.first << L"] VALUE [" << Pair.second << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUnorderedMultiMap(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector;

	for(int Index=0;Index<5;Index++)
	{
		Vector.push_back(Index);

		// Vlozia sa 2 ITEMS s tou istou hodnotou.
		Vector.push_back(Index);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v MULTIMAP SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	PrintLineSeparator();

	unordered_multimap<int,char>								UnorderedMultiMap;

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		UnorderedMultiMap.insert(pair<const int,char>(Vector[Index],'A'+char(Vector[Index])));
	}

	// !!! ITEMS v MULTIMAP maju podobu PAIR.
	for(const pair<const int,char>& Pair : UnorderedMultiMap)
	{
		wcout << L"KEY [" << Pair.first << L"] VALUE [" << Pair.second << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAssociativeArrays(void)
{
	PrintLineSeparator();

	map<wstring,int>											AssociativeArray;

	// Vytvara nove ITEMS v ASSOCIATIVE ARRAY.
	AssociativeArray[L"10"]=10;
	AssociativeArray[L"20"]=20;
	AssociativeArray[L"30"]=30;

	// !!! Vytvori novy ITEM v ASSOCIATIVE ARRAY s DEFAULT VALUE.
	AssociativeArray[L"40"];

	for(const pair<const wstring,int>& Pair : AssociativeArray)
	{
		wcout << L"KEY [" << Pair.first << L"] VALUE [" << Pair.second << L"] !" << endl;
	}

	try
	{
		wcout << L"KEY [" << L"20" << L"] VALUE [" << AssociativeArray.at(L"20") << L"] !" << endl;
	}
	catch(...)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	try
	{
		// !!! Kedze ITEM [L"50"] sa v ASSOCIATIVE ARRAY NENACHADZA, METHOD at() hodi EXCEPTION.
		wcout << L"KEY [" << L"50" << L"] VALUE [" << AssociativeArray.at(L"50") << L"] !" << endl;
	}
	catch(...)
	{
		wcout << L"Can't ACCESS ITEM !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStrings(void)
{
	PrintLineSeparator();

	wstring														String(L"My name is TIMMY ANDERSON !");

	wcout << L"STRING [" << String << L"] !" << endl;

	// !!! Kedze CLASS [wstring] je CONTAINER, tak je mozne nad instanciami CLASS [wstring] aplikovat C++ ALGORITHMS.
	reverse(String.begin(),String.end());

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCArrays(void)
{
	PrintLineSeparator();

	wchar_t														String[]=L"My name is TIMMY ANDERSON !";

	wcout << L"STRING [" << String << L"] !" << endl;

	// !!! Kedze C-ARRAY je CONTAINER, tak je mozne nad C-ARRAYS aplikovat C++ ALGORITHMS.
	reverse(String,String+10);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPriorityQueue(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	priority_queue<int>											PriorityQueue;
	vector<int>													Vector;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back((Index+1)*10);
	}

	// Umyselne sa prehodi poradie ITEMS, aby sa demonstrovalo, ze ITEMS su v SET SORTED.
	shuffle(Vector.begin(),Vector.end(),Random);

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		wcout << L"VECTOR [" << Vector[Index] << L"] !" << endl;
	}

	for(size_t Index=0;Index<Vector.size();Index++)
	{
		PriorityQueue.push(Vector[Index]);
	}

	PrintLineSeparator();

	// !!! ITEMS su ulozene podla PRIORITY, ktora je urcena DEFAULT pomocou OPERATOR<.
	while(PriorityQueue.empty()==false)
	{
		int														Value=PriorityQueue.top();

		wcout << L"PRIORITY QUEUE [" << Value << L"] !" << endl;

		PriorityQueue.pop();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestQueue(void)
{
	PrintLineSeparator();

	queue<int>													Queue;

	for(int Index=0;Index<10;Index++)
	{
		Queue.push((Index+1)*10);
	}

	while(Queue.empty()==false)
	{
		int														Value=Queue.front();

		wcout << L"QUEUE [" << Value << L"] !" << endl;

		Queue.pop();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStack(void)
{
	PrintLineSeparator();

	stack<int>													Stack;

	for(int Index=0;Index<10;Index++)
	{
		Stack.push((Index+1)*10);
	}

	while(Stack.empty()==false)
	{
		int														Value=Stack.top();

		wcout << L"STACK [" << Value << L"] !" << endl;

		Stack.pop();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIterations(void)
{
	PrintLineSeparator();

	vector<int>													Vector{10,20,30,40,50};

	// !!! ITERATOR je NON-CONST a preto je MOZNE ZMENIT VALUES jednotlivych ITEMS.
	for(vector<int>::iterator Iterator=Vector.begin();Iterator!=Vector.end();Iterator++)
	{
		wcout << L"VALUE [" << *Iterator << L"] !" << endl;

		(*Iterator)++;
	}

	PrintLineSeparator();

	// !!! ITERATOR je CONST a preto NIE je MOZNE ZMENIT VALUES jednotlivych ITEMS.
	for(vector<int>::const_iterator Iterator=Vector.cbegin();Iterator!=Vector.cend();Iterator++)
	{
		wcout << L"VALUE [" << *Iterator << L"] !" << endl;

		// !!! Hodi COMPILATION ERROR.
		//(*Iterator)++;
	}

	PrintLineSeparator();

	// !!! ITERATOR je inkrementovany cez PREFIX OPERATOR++.
	for(vector<int>::const_iterator Iterator=Vector.cbegin();Iterator!=Vector.cend();++Iterator)
	{
		wcout << L"VALUE [" << *Iterator << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAlgorithms(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Vector{10,20,30,40,50,60,70,80,90};

	wcout << L"VALUES [";

	for(vector<int>::const_iterator Iterator=Vector.cbegin();Iterator!=Vector.cend();Iterator++)
	{
		if (Iterator!=Vector.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// Je NUTNE pouzit NON-CONST ITERATORS, lebo ALGORITHM modifikuje VECTOR.
	shuffle(Vector.begin(),Vector.end(),Random);

	wcout << L"VALUES [";

	for(vector<int>::const_iterator Iterator=Vector.cbegin();Iterator!=Vector.cend();Iterator++)
	{
		if (Iterator!=Vector.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// Kedze ALGORITHMS NEMODIFIKUJU VECTOR, je mozne pouzit aj CONST ITERATORS.
	wcout << L"MIN ELEMENT [" << *min_element(Vector.cbegin(),Vector.cend()) << L"] !" << endl;
	wcout << L"MAX ELEMENT [" << *max_element(Vector.cbegin(),Vector.cend()) << L"] !" << endl;

	// Je NUTNE pouzit NON-CONST ITERATORS, lebo ALGORITHM modifikuje VECTOR.
	sort(Vector.begin(),Vector.end());

	wcout << L"VALUES [";

	for(vector<int>::const_iterator Iterator=Vector.cbegin();Iterator!=Vector.cend();Iterator++)
	{
		if (Iterator!=Vector.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// Je NUTNE pouzit NON-CONST ITERATORS, lebo ALGORITHM modifikuje VECTOR.
	reverse(Vector.begin(),Vector.end());

	wcout << L"VALUES [";

	for(vector<int>::const_iterator Iterator=Vector.cbegin();Iterator!=Vector.cend();Iterator++)
	{
		if (Iterator!=Vector.begin())
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
void TestIteratorRange1(void)
{
	PrintLineSeparator();

	// !!! COLLECTION LIST NEMA RANDOM ACCESS ITERATORS.
	list<int>													List{10,20,30,40,50,60,70,80,90};

	list<int>::const_iterator									Iterator1=find(List.cbegin(),List.cend(),20);
	list<int>::const_iterator									Iterator2=find(List.cbegin(),List.cend(),80);

	// !!! Kedze ITERATORS pouzivaju HALF-OPEN ITERATOR RANGE, kde ITEM na ktory odkazuje 'Iterator2' uz NIE JE ZAHRNUTY do vykonavania ALGORITHM, tak MAX ELEMENT bude mat hodnotu 70, namiesto 80.
	wcout << L"MAX ELEMENT [" << *max_element(Iterator1,Iterator2) << L"] !" << endl;

	// !!! Ak sa ma zahrnut aj ITEM na ktory odkazuje 'Iterator2' je NUTNE posunut 'END_ITERATOR' po poziciu ZA 'Iterator2'. Teraz uz find() vrati ako MAX ELEMENT hodnotu 80.
	wcout << L"MAX ELEMENT [" << *max_element(Iterator1,++Iterator2) << L"] !" << endl;

	// !!!!! Kedze pre ITERATOR RANGE plati, ze 'BEGIN_ITERATOR'<='END_ITERATOR', nasledujuci CODE je CHYBNY a sposobi UNDEFINED BEHAVIOR.
	//wcout << L"MAX ELEMENT [" << *max_element(Iterator2,Iterator1) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ProcessItems(const list<int>& List, int Value1, int Value2)
{
	list<int>::const_iterator									BeginIterator;
	list<int>::const_iterator									EndIterator;

	// !!!!! Kedze C++ ALGORITHMS vyzaduju OPEN-HALF ITERATOR RANGES, kde 'BEGIN_ITERATOR'<='END_ITERATOR', uz pri vyhladavani ITERATORS pre ITERATOR RANGE je NUTNE toto zohladnit.

	// !!! Najde sa 'BEGIN_ITERATOR', ktory ma bud hodnotu 'Value1', alebo 'Value2'. Kedze COLLECTION je UNSORTED tak poradie VALUES v COLLECTION moze byt lubovolne.
	BeginIterator=find_if(List.cbegin(),List.cend(),[Value1,Value2](int Value)->bool{return(Value==Value1 || Value==Value2);});

	if (BeginIterator==List.cend())
	{
		wcout << L"BEGIN ITERATOR NOT FOUND !" << endl;
	}
	else
	{
		// !!! Urci sa ci 'BEGIN_ITERATOR' odkazuje na 'Value1', alebo na 'Value2'.
		if (*BeginIterator==Value1)
		{
			list<int>::const_iterator							Iterator=BeginIterator;

			EndIterator=find(++Iterator,List.cend(),Value2);
		}
		else
		{
			list<int>::const_iterator							Iterator=BeginIterator;

			EndIterator=find(++Iterator,List.cend(),Value1);
		}

		if (EndIterator==List.cend())
		{
			wcout << L"END ITERATOR NOT FOUND !" << endl;
		}
		else
		{
			// Hodnota 'END_ITERATOR' sa posunie, aby sa aj ITEM na ktory 'END_ITERATOR' referuje bol vypisany.
			EndIterator++;

			// !!! Vypisu sa ITEMS medzi 'BEGIN_ITERATOR' a 'END_ITERATOR'.
			wcout << L"VALUES [";

			for(list<int>::const_iterator Iterator=BeginIterator;Iterator!=EndIterator;Iterator++)
			{
				if (Iterator!=BeginIterator)
				{
					wcout << L" ";
				}

				wcout << *Iterator;
			}

			wcout << L"] !" << endl;
		}
	}
}
//-----------------------------------------------------------------------------
void TestIteratorRange2(void)
{
	PrintLineSeparator();

	// !!! COLLECTION LIST NEMA RANDOM ACCESS ITERATORS.
	list<int>													List{40,80,10,30,90,50,60,70,20};

	wcout << L"VALUES [";

	for(list<int>::const_iterator Iterator=List.cbegin();Iterator!=List.cend();Iterator++)
	{
		if (Iterator!=List.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	ProcessItems(List,60,80);
	ProcessItems(List,80,60);
	ProcessItems(List,0,60);
	ProcessItems(List,60,0);
	ProcessItems(List,0,80);
	ProcessItems(List,80,0);
	ProcessItems(List,100,60);
	ProcessItems(List,60,100);
	ProcessItems(List,100,80);
	ProcessItems(List,80,100);
	ProcessItems(List,0,100);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestIteratorRange3(void)
{
	PrintLineSeparator();

	vector<int>													Collection1{1,2,3,4,5,6,7,8,9,10};
	vector<int>													Collection2;

	wcout << L"VALUES [";

	for(vector<int>::const_iterator Iterator=Collection1.cbegin();Iterator!=Collection1.cend();Iterator++)
	{
		if (Iterator!=Collection1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! COLLECTION 'Collection2' MUSI mat dostatocny pocet ITEMS, aby ALGORITHM prebehol korektne.
	Collection2.resize(Collection1.size());

	// !!! ALGORITHM vyzaduje 2 ITERATOR RANGES, pricom 2. ITERATOR RANGE je definovany iba cez svoj BEGIN_ITERATOR. Pocet ITEMS v 2. COLLECTION musi byt taky, aby sa don zmestili vsetky ITEMS v ITERATOR RANGE BEGIN_ITERATOR a END_ITERATOR.
	copy(Collection1.begin(),Collection1.end(),Collection2.begin());

	PrintLineSeparator();

	wcout << L"VALUES [";

	for(vector<int>::const_iterator Iterator=Collection2.cbegin();Iterator!=Collection2.cend();Iterator++)
	{
		if (Iterator!=Collection2.begin())
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
void TestInsertIterators(void)
{
	PrintLineSeparator();

	vector<int>													Collection{1,2,3,4,5,6,7,8,9,10};
	// !!! Namiesto VECTOR sa pouzila DEQUEUE, pretoze tato COLLECTION ma METHOD push_front(), METHOD push_back() aj METHOD insert().
	deque<int>													CollectionFront{100,200,300,400};
	deque<int>													CollectionEnd{100,200,300,400};
	deque<int>													CollectionGeneral{100,200,300,400};

	wcout << L"VALUES [";

	for(vector<int>::const_iterator Iterator=Collection.cbegin();Iterator!=Collection.cend();Iterator++)
	{
		if (Iterator!=Collection.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Kedze sa pouzil FRONT INSERT ITERATOR, tak sa ITEMS budu namiesto kopirovania vkladat na ZACIATOK COLLECTION.
	// !!! Vkladanie ITEMS na ZACIATOK COLLECTION sposobi, ze ITEMS budu v COLLECTION ulozene v obratenom poradi.
	copy(Collection.begin(),Collection.end(),front_inserter(CollectionFront));

	PrintLineSeparator();

	wcout << L"VALUES [";

	for(deque<int>::const_iterator Iterator=CollectionFront.cbegin();Iterator!=CollectionFront.cend();Iterator++)
	{
		if (Iterator!=CollectionFront.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Kedze sa pouzil BACK INSERT ITERATOR, tak sa ITEMS budu namiesto kopirovania vkladat na KONIEC COLLECTION.
	copy(Collection.begin(),Collection.end(),back_inserter(CollectionEnd));

	wcout << L"VALUES [";

	for(deque<int>::const_iterator Iterator=CollectionEnd.cbegin();Iterator!=CollectionEnd.cend();Iterator++)
	{
		if (Iterator!=CollectionEnd.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Kedze sa pouzil GENERAL INSERT ITERATOR, tak sa ITEMS budu namiesto kopirovania vkladat na poziciu v COLLECTION pred 2. ITEM.
	copy(Collection.begin(),Collection.end(),inserter(CollectionGeneral,CollectionGeneral.begin()+2));

	wcout << L"VALUES [";

	for(deque<int>::const_iterator Iterator=CollectionGeneral.cbegin();Iterator!=CollectionGeneral.cend();Iterator++)
	{
		if (Iterator!=CollectionGeneral.begin())
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
void TestStreamIterators1(void)
{
	PrintLineSeparator(false);

	stringstream												Stream("My name is Timmy Anderson !");
	vector<string>												Words;

	// !!! Kedze OPERATOR>> pre STRING cita STRINGS po vyskyt prveho WHITE CHARACTER, tak nasledujuci CODE sposobi rozklad celeho STRING na jednotlive WORDS.
	// 1. PARAMETER je INPUT STREAM ITERATOR nad STREAM 'Stream'.
	// !!! 2. PARAMETER je PRAZDNY INPUT STREAM ITERATOR, ktory sa pouziva ako zarazka indikujuca kedy sa ma iterovanie skoncit. To sa konci vtedy, ked bol cely STREAM precitany, alebo doslo k ERROR. Koniec STREAMU je signalizovany prave 2. PARAMETROM obsahujucim na prazdny INPUT STREAM ITERATOR.
	// 3. PARAMETER je INSERT ITERATOR, ktory zabezpeci vkladanie ITEMS (jednotlivych WORDS) do COLLECTION.
	copy(istream_iterator<string>(Stream),istream_iterator<string>(),back_inserter(Words));

	cout << "VALUES [";

	// !!! Nasledujuci CODE vypise WORDS.
	// 1. PARAMETER a 2. PARAMETER su ITERATORS na COLLECTION obsahujucu WORDS.
	// !!! 3. PARAMETER je OUTPUT STREAM ITERATOR nad STDOUT. 2. PARAMETER jeho CONSTRUCTOR je DELIMITER.
	copy(Words.begin(),Words.end(),ostream_iterator<string>(cout,","));

	cout << "] !" << endl;

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamIterators2(void)
{
	PrintLineSeparator();

	wstringstream												Stream(L"My name is Timmy Anderson !");
	vector<wstring>												Words;

	// !!! Kedze OPERATOR>> pre STRING cita STRINGS po vyskyt prveho WHITE CHARACTER, tak nasledujuci CODE sposobi rozklad celeho STRING na jednotlive WORDS.
	// 1. PARAMETER je INPUT STREAM ITERATOR nad STREAM 'Stream'.
	// !!! 2. PARAMETER je PRAZDNY INPUT STREAM ITERATOR, ktory sa pouziva ako zarazka indikujuca kedy sa ma iterovanie skoncit. To sa konci vtedy, ked bol cely STREAM precitany, alebo doslo k ERROR. Koniec STREAMU je signalizovany prave 2. PARAMETROM obsahujucim na prazdny INPUT STREAM ITERATOR.
	// 3. PARAMETER je INSERT ITERATOR, ktory zabezpeci vkladanie ITEMS (jednotlivych WORDS) do COLLECTION.
	// !!! Pre WCHAR verziu STREAM ITERATOR je NUTNE explicitne dosadit hodnoty dalsich TYPE PARAMETERS, inak COMPILER hodi ERROR.
	copy(istream_iterator<wstring,wchar_t,char_traits<wchar_t>>(Stream),istream_iterator<wstring,wchar_t,char_traits<wchar_t>>(),back_inserter(Words));

	wcout << L"VALUES [";

	// !!! Nasledujuci CODE vypise WORDS.
	// 1. PARAMETER a 2. PARAMETER su ITERATORS na COLLECTION obsahujucu WORDS.
	// !!! 3. PARAMETER je OUTPUT STREAM ITERATOR nad STDOUT. 2. PARAMETER jeho CONSTRUCTOR je DELIMITER.
	// !!! Pre WCHAR verziu STREAM ITERATOR je NUTNE explicitne dosadit hodnoty dalsich TYPE PARAMETERS, inak COMPILER hodi ERROR.
	copy(Words.begin(),Words.end(),ostream_iterator<wstring,wchar_t,char_traits<wchar_t>>(wcout,L","));

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamIterators3(void)
{
	PrintLineSeparator(false);

	stringstream												Stream("10 20 30 40 50");
	vector<int>													Values;

	// !!! Kedze OPERATOR>> pre INTEGERS cita INTEGERS po vyskyt prveho WHITE CHARACTER, tak nasledujuci CODE sposobi rozklad celeho STRING na jednotlive INTEGERS.
	// 1. PARAMETER je INPUT STREAM ITERATOR nad STREAM 'Stream'.
	// !!! 2. PARAMETER je PRAZDNY INPUT STREAM ITERATOR, ktory sa pouziva ako zarazka indikujuca kedy sa ma iterovanie skoncit. To sa konci vtedy, ked bol cely STREAM precitany, alebo doslo k ERROR. Koniec STREAMU je signalizovany prave 2. PARAMETROM obsahujucim na prazdny INPUT STREAM ITERATOR.
	// 3. PARAMETER je INSERT ITERATOR, ktory zabezpeci vkladanie ITEMS (jednotlivych INTEGERS) do COLLECTION.
	copy(istream_iterator<int>(Stream),istream_iterator<int>(),back_inserter(Values));

	cout << "VALUES [";

	// !!! Nasledujuci CODE vypise INTEGERS.
	// 1. PARAMETER a 2. PARAMETER su ITERATORS na COLLECTION obsahujucu INTEGERS.
	// !!! 3. PARAMETER je OUTPUT STREAM ITERATOR nad STDOUT. 2. PARAMETER jeho CONSTRUCTOR je DELIMITER.
	copy(Values.begin(),Values.end(),ostream_iterator<int>(cout,","));

	cout << "] !" << endl;

	PrintLineSeparator(false);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestReverseIterators(void)
{
	PrintLineSeparator();

	vector<int>													Collection{1,2,3,4,5,6,7,8,9,10};

	wcout << L"VALUES [";

	for(vector<int>::reverse_iterator Iterator=Collection.rbegin();Iterator!=Collection.rend();Iterator++)
	{
		if (Iterator!=Collection.rbegin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"VALUES [";

	// OPERATOR-- REVERSE ITERATOR posuva svoju poziciu smerom dopredu.
	for(vector<int>::reverse_iterator Iterator=Collection.rend();Iterator!=Collection.rbegin();Iterator--)
	{
		if (Iterator!=Collection.rend())
		{
			wcout << L" ";
		}

		wcout << *(Iterator-1);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMoveIterators(void)
{
	PrintLineSeparator();

	vector<wstring>												CollectionIn{L"1",L"2",L"3",L"4",L"5",L"6",L"7",L"8",L"9",L"10"};
	vector<wstring>												CollectionOut;

	wcout << L"VALUES [";

	for(vector<wstring>::iterator Iterator=CollectionIn.begin();Iterator!=CollectionIn.end();Iterator++)
	{
		if (Iterator!=CollectionIn.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!!!! Pri iterovani dochadza k MOVE vsetkych ITEMS z COLLECTION 'CollectionIn' do COLLECTION 'CollectionOut'. Vysledkom je, ze COLLECTION 'CollectionIn' bude obsahovat 10 PRAZDNYCH STRINGS.
	copy(move_iterator<vector<wstring>::iterator>(CollectionIn.begin()),move_iterator<vector<wstring>::iterator>(CollectionIn.end()),back_inserter(CollectionOut));

	wcout << L"VALUES [";

	for(vector<wstring>::iterator Iterator=CollectionIn.begin();Iterator!=CollectionIn.end();Iterator++)
	{
		if (Iterator!=CollectionIn.begin())
		{
			wcout << L" ";
		}

		if ((*Iterator)!=L"")
		{
			wcout << *Iterator;
		}
		else
		{
			wcout << "EMPTY";
		}
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestModifyAlgorithmsProblems(void)
{
	PrintLineSeparator();

	list<int>													Collection;

	for(int Index=0;Index<5;Index++)
	{
		Collection.push_back(Index+1);
		Collection.push_front(Index+1);
	}

	wcout << L"VALUES [";

	for(list<int>::iterator Iterator=Collection.begin();Iterator!=Collection.end();Iterator++)
	{
		if (Iterator!=Collection.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"NUMBER of ITEMS [" << Collection.size() << "] !" << endl;

	PrintLineSeparator();

	// !!!!! ALGORITHM remove() v skutocnosti NEMENI VELKOST COLLECTION, iba presuva ITEMS, tak aby z nej vyradil najdne ITEMS.
	// !!! ALGORITHM remove() ako RETURN VALUE vracia novy END ITERATOR uz bez vyradenych ITEMS.
	list<int>::iterator											NewEndIterator=remove(Collection.begin(),Collection.end(),4);

	wcout << L"AFTER REMOVE '4' [";

	for(list<int>::iterator Iterator=Collection.begin();Iterator!=Collection.end();Iterator++)
	{
		if (Iterator!=Collection.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! COLLECTION ma stale 10 ITEMS a dokonca aj ITEM '4', pretoze tento lezi na 9. pozicii, ktora je uz za novym END ITERATOR.
	wcout << L"NUMBER of ITEMS [" << Collection.size() << "] !" << endl;

	PrintLineSeparator();

	// !!! Nato, aby sa COLLECTION skratila na skutocny pocet ITEMS je potrebne pouzit METHOD erase().
	Collection.erase(NewEndIterator,Collection.end());

	wcout << L"AFTER ERASE [";

	for(list<int>::iterator Iterator=Collection.begin();Iterator!=Collection.end();Iterator++)
	{
		if (Iterator!=Collection.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Teraz uz ma COLLECTION iba 8 ITEMS a NEOBSAHUJE ITEM s hodnotou '4'.
	wcout << L"NUMBER of ITEMS [" << Collection.size() << "] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRemovePerformance(void)
{
	PrintLineSeparator();

	list<CInt>													Collection1;
	list<CInt>													Collection2;

	for(int Index=0;Index<5;Index++)
	{
		Collection1.push_back(Index+1);
		Collection1.push_front(Index+1);
		Collection2.push_back(Index+1);
		Collection2.push_front(Index+1);
	}

	wcout << L"VALUES - COLLECTION 1 [";

	for(list<CInt>::iterator Iterator=Collection1.begin();Iterator!=Collection1.end();Iterator++)
	{
		if (Iterator!=Collection1.begin())
		{
			wcout << L" ";
		}

		wcout << Iterator->GetValue();
	}

	wcout << L"] !" << endl;

	wcout << L"VALUES - COLLECTION 2 [";

	for(list<CInt>::iterator Iterator=Collection2.begin();Iterator!=Collection2.end();Iterator++)
	{
		if (Iterator!=Collection2.begin())
		{
			wcout << L" ";
		}

		wcout << Iterator->GetValue();
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"BEFORE MOVE !" << endl;

	// !!! Vykona sa REMOVE cez ALGORITHM.
	// !!!!! Kedze ALGORITHM PRESUVA ITEMS, tak aby NEOBSAHOVALI vymazane ITEMS je VELMI POMALY. Kazdy presun totizto vyzaduje NAROCNE volanie OPERATOR= a kopirovanie hodnot co je pomale.
	list<CInt>::iterator										NewEndIterator=remove(Collection1.begin(),Collection1.end(),4);

	wcout << L"BEFORE ERASE !" << endl;

	// Odstrania sa prebytocne ITEMS.
	Collection1.erase(NewEndIterator,Collection1.end());

	wcout << L"VALUES - COLLECTION 1 [";

	for(list<CInt>::iterator Iterator=Collection1.begin();Iterator!=Collection1.end();Iterator++)
	{
		if (Iterator!=Collection1.begin())
		{
			wcout << L" ";
		}

		wcout << Iterator->GetValue();
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Vykona sa REMOVE cez METHOD.
	// !!!!! Kedze METHOD remove() NAMIESTO PRESUVANIA PRIAMO VYMAZAVA ITEMS, NEDOCHADZA k casovo narocnemu KOPIROVANIU ITEMS.
	Collection2.remove(4);

	wcout << L"VALUES - COLLECTION 2 [";

	for(list<CInt>::iterator Iterator=Collection2.begin();Iterator!=Collection2.end();Iterator++)
	{
		if (Iterator!=Collection2.begin())
		{
			wcout << L" ";
		}

		wcout << Iterator->GetValue();
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int Square(int Value)
{
	return(Value*Value);
}
//-----------------------------------------------------------------------------
void TestAlgorithmsFunctionParameters(void)
{
	PrintLineSeparator();

	list<int>													Collection;

	for(int Index=0;Index<10;Index++)
	{
		Collection.push_back(Index+1);
	}

	wcout << L"VALUES [";

	for(list<int>::iterator Iterator=Collection.begin();Iterator!=Collection.end();Iterator++)
	{
		if (Iterator!=Collection.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// Pre KAZDY ITEM sa vola CUSTOM FUNCTION Square().
	transform(Collection.begin(),Collection.end(),Collection.begin(),Square);

	wcout << L"VALUES [";

	for(list<int>::iterator Iterator=Collection.begin();Iterator!=Collection.end();Iterator++)
	{
		if (Iterator!=Collection.begin())
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
bool PredicateIsEven(int Value)
{
	if ((Value % 2)==0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
// PREDICATE implementuje OPERATOR>.
bool PredicateSort(int Left, int Right)
{
	if (Left>Right)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
void TestPredicates(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Values{1,3,4,6,9,11};

	// Ako posledny PARAMETER sa prenasa UNARY PREDICATE.
	vector<int>::iterator										Position=find_if(Values.begin(),Values.end(),PredicateIsEven);

	if (Position!=Values.end())
	{
		wcout << L"FIRST EVEN VALUE is [" << *Position << L"] !" << endl;
	}
	else
	{
		wcout << L"COLECTION doesn't have EVEN VALUE !" << endl;
	}

	PrintLineSeparator();

	vector<int>													Vector;
	vector<int>													Result1;
	vector<int>													Result2;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back((Index+1)*10);
	}

	shuffle(Vector.begin(),Vector.end(),Random);
	copy(Vector.begin(),Vector.end(),back_inserter(Result1));
	copy(Vector.begin(),Vector.end(),back_inserter(Result2));

	wcout << L"RESULT 1 before SORT [";

	for(vector<int>::iterator Iterator=Result1.begin();Iterator!=Result1.end();Iterator++)
	{
		if (Iterator!=Result1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Nepouziva sa CUSTOM SORT PREDICATE.
	sort(Result1.begin(),Result1.end());

	wcout << L"RESULT 1 after SORT [";

	for(vector<int>::iterator Iterator=Result1.begin();Iterator!=Result1.end();Iterator++)
	{
		if (Iterator!=Result1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"RESULT 2 before SORT [";

	for(vector<int>::iterator Iterator=Result2.begin();Iterator!=Result2.end();Iterator++)
	{
		if (Iterator!=Result2.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Pouzije sa CUSTOM SORT PREDICATE, ktory je BINARY PREDICATE.
	sort(Result2.begin(),Result2.end(),PredicateSort);

	wcout << L"RESULT 2 after SORT [";

	for(vector<int>::iterator Iterator=Result2.begin();Iterator!=Result2.end();Iterator++)
	{
		if (Iterator!=Result2.begin())
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
void TestLambdaFunctions(void)
{
	PrintLineSeparator();

	random_device												Generator;
	mt19937														Random(Generator());

	vector<int>													Values{1,3,4,6,9,11};

	// Ako posledny PARAMETER sa prenasa UNARY PREDICATE.
	// PREDICATE je definovany ako LAMBDA FUNCTION.
	vector<int>::iterator										Position=find_if(Values.begin(),Values.end(),[](int Value)->bool{return((Value%2)==0);});

	if (Position!=Values.end())
	{
		wcout << L"FIRST EVEN VALUE is [" << *Position << L"] !" << endl;
	}
	else
	{
		wcout << L"COLECTION doesn't have EVEN VALUE !" << endl;
	}

	PrintLineSeparator();

	vector<int>													Vector;
	vector<int>													Result1;
	vector<int>													Result2;

	for(int Index=0;Index<10;Index++)
	{
		Vector.push_back((Index+1)*10);
	}

	shuffle(Vector.begin(),Vector.end(),Random);
	copy(Vector.begin(),Vector.end(),back_inserter(Result1));
	copy(Vector.begin(),Vector.end(),back_inserter(Result2));

	wcout << L"RESULT 1 before SORT [";

	for(vector<int>::iterator Iterator=Result1.begin();Iterator!=Result1.end();Iterator++)
	{
		if (Iterator!=Result1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Nepouziva sa CUSTOM SORT PREDICATE.
	sort(Result1.begin(),Result1.end());

	wcout << L"RESULT 1 after SORT [";

	for(vector<int>::iterator Iterator=Result1.begin();Iterator!=Result1.end();Iterator++)
	{
		if (Iterator!=Result1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"RESULT 2 before SORT [";

	for(vector<int>::iterator Iterator=Result2.begin();Iterator!=Result2.end();Iterator++)
	{
		if (Iterator!=Result2.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!! Pouzije sa CUSTOM SORT PREDICATE, ktory je BINARY PREDICATE.
	// PREDICATE je definovany ako LAMBDA FUNCTION.
	sort(Result2.begin(),Result2.end(),[](int Left, int Right)->bool{return(Left>Right);});

	wcout << L"RESULT 2 after SORT [";

	for(vector<int>::iterator Iterator=Result2.begin();Iterator!=Result2.end();Iterator++)
	{
		if (Iterator!=Result2.begin())
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
void TestFunctionObjects(void)
{
	PrintLineSeparator();

	vector<wstring>												Strings{L"My",L"name",L"is",L"Timmy",L"Anderson",L"!"};

	wcout << L"STRINGS [";

	for(vector<wstring>::iterator Iterator=Strings.begin();Iterator!=Strings.end();Iterator++)
	{
		if (Iterator!=Strings.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	CFunctionObjectFindByValue<wstring>							PredicateFunctionObject(L"Timmy");

	// !!! Ako PREDICATE sa pouzije FUNCTION OBJECT.
	vector<wstring>::iterator									Position=find_if(Strings.begin(),Strings.end(),PredicateFunctionObject);

	if (Position!=Strings.end())
	{
		wcout << L"COLLECTION contains VALUE is [" << *Position << L"] at POSITION [" << distance(Strings.begin(),Position) << L"] !" << endl;
	}
	else
	{
		wcout << L"COLECTION doesn't have SEARCHING VALUE !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPredefinedFunctionObjects(void)
{
	PrintLineSeparator();

	vector<int>													Collection1{1,2,3,4,5,6,7,8,9,10};
	vector<int>													Collection2{10,20,30,40,50,60,70,80,90,100};
	vector<int>													Collection3;
	vector<int>													Collection4;

	wcout << L"COLLECTION 1 [";

	for(vector<int>::iterator Iterator=Collection1.begin();Iterator!=Collection1.end();Iterator++)
	{
		if (Iterator!=Collection1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	wcout << L"COLLECTION 2 [";

	for(vector<int>::iterator Iterator=Collection2.begin();Iterator!=Collection2.end();Iterator++)
	{
		if (Iterator!=Collection2.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pouzije sa BINARNY FUNCTION OBJECT plus(), ktory scita hodnoty 2 COLLECTIONS.
	// !!!!! Tato veriza FUNCTION transform() ma 5 PARAMETERS a vyzaduje zaslanie BINARY OPERATOR.
	transform(Collection1.cbegin(),Collection1.cend(),Collection2.cbegin(),back_inserter(Collection3),plus<int>());

	wcout << L"COLLECTION 3 [";

	for(vector<int>::iterator Iterator=Collection3.begin();Iterator!=Collection3.end();Iterator++)
	{
		if (Iterator!=Collection3.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pouzije sa UNARY FUNCTION OBJECT negate(), ktory obrati znamienko.
	// !!!!! Tato veriza FUNCTION transform() ma 4 PARAMETERS a vyzaduje zaslanie UNARY OPERATOR.
	transform(Collection3.cbegin(),Collection3.cend(),back_inserter(Collection4),negate<int>());

	wcout << L"COLLECTION 4 [";

	for(vector<int>::iterator Iterator=Collection4.begin();Iterator!=Collection4.end();Iterator++)
	{
		if (Iterator!=Collection4.begin())
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

	vector<int>													Collection1{1,2,3,4,5,6,7,8,9,10};
	vector<int>													Collection2;

	wcout << L"COLLECTION 1 [";

	for(vector<int>::iterator Iterator=Collection1.begin();Iterator!=Collection1.end();Iterator++)
	{
		if (Iterator!=Collection1.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

	// !!!!! FUNCTION bind() z BINARY OPERATOR spravi CALLABLE OBJECT, ktory ma 1 PARAMETER a chova sa ako UNARY OPERATOR.
	// !!!!! Hodnota 10 sa namapuje ako 2. PARAMETER povodneho FUNCTION OBJECT [plus<int>]. 1. PARAMETER bude substituovanym PARAMETER, ktory sa zada pri volani novovytvoreneho CALLABLE OBJECT. V tomto pripade je to hodnota ITEM z 'Collection1'.
	transform(Collection1.cbegin(),Collection1.cend(),back_inserter(Collection2),bind(plus<int>(),_1,10));

	wcout << L"COLLECTION 2 [";

	for(vector<int>::iterator Iterator=Collection2.begin();Iterator!=Collection2.end();Iterator++)
	{
		if (Iterator!=Collection2.begin())
		{
			wcout << L" ";
		}

		wcout << *Iterator;
	}

	wcout << L"] !" << endl;

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
void TestContainerErrorChecking(void)
{
	PrintLineSeparator();

	vector<int>													Collection;

	Collection.push_back(10);
	Collection.push_back(20);
	Collection.push_back(30);

	try
	{
		// !!! METHOD vector<int>::at() detekuje neplatny INDEX a hodi EXCEPTION [out_of_range].
		wcout << L"ITEM [5] - VALUE [" << Collection.at(5) << L"] !" << endl;
	}
	catch(const out_of_range&)
	{
		wcout << L"COLLECTION doesn't have an ITEM with INDEX [5] !" << endl;
	}

	size_t														MaxSize=Collection.max_size();

	try
	{
		// !!! METHOD vector<int>::reserve() detekuje ak pocet ITEMS presiahne hodnotu vector<int>::max_size().
		Collection.resize(MaxSize+1);
	}
	catch(const length_error&)
	{
		wcout << L"COLLECTION can't RESERVE SPACE for [" << (MaxSize+1) << "] ITEMS !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestVector();
	//TestDequeue();
	//TestArray();
	//TestList();
	//TestForwardList();
	//TestSet();
	//TestMultiSet();
	//TestMap();
	//TestMultiMap();
	//TestSetVSUnorderedSet();
	//TestUnorderedSet();
	//TestUnorderedMultiSet();
	//TestUnorderedMap();
	//TestUnorderedMultiMap();
	//TestAssociativeArrays();
	//TestStrings();
	//TestCArrays();
	//TestPriorityQueue();
	//TestQueue();
	//TestStack();
	//TestIterations();
	//TestAlgorithms();
	//TestIteratorRange1();
	//TestIteratorRange2();
	//TestIteratorRange3();
	//TestInsertIterators();
	//TestStreamIterators1();
	//TestStreamIterators2();
	//TestStreamIterators3();
	//TestReverseIterators();
	//TestMoveIterators();
	//TestModifyAlgorithmsProblems();
	//TestRemovePerformance();
	//TestAlgorithmsFunctionParameters();
	//TestPredicates();
	//TestLambdaFunctions();
	//TestFunctionObjects();
	//TestPredefinedFunctionObjects();
	//TestBind1();
	//TestBind2();
	//TestBind3();
	TestContainerErrorChecking();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------