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
#include <list>
#include <stack>
#include <queue>
#include <bitset>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStack1(void)
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
void TestStack2(void)
{
	PrintLineSeparator();

	// Ako CONTAINER sa pouziva VECTOR.
	stack<int,vector<int>>										Stack;

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
void TestQueue1(void)
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
void TestQueue2(void)
{
	PrintLineSeparator();

	// !!! Ako CUSTOM COLLECTION sa pouzije LIST.
	// !!!!! VECTOR ako CUSTOM COLLECTION NIE JE mozne pouzit, pretoze NEMA OPERATION pop_front().
	queue<int,list<int>>										Queue1;

	Queue1.push(10);
	Queue1.push(20);
	Queue1.push(30);
	Queue1.push(40);
	Queue1.push(50);

	queue<int,list<int>>										Queue2;

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
void TestPriorityQueue1(void)
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
void TestPriorityQueue2(void)
{
	PrintLineSeparator();

	// Ako COLLECTION sa pouzije DEQUEUE.
	// !!! Ako CUSTOM COMPARER sa pouzije TYPE [greater<int>].
	priority_queue<int,deque<int>,greater<int>>					PriorityQueue;

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
int main(void)
{
	SafeMain();

	//TestStack1();
	//TestStack2();
	//TestQueue1();
	//TestQueue2();
	//TestPriorityQueue1();
	//TestPriorityQueue2();
	//TestBitSetReference();
	//TestBitSetConstruction();
	//TestBitSetSerialization();
	TestBitSetOperations();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------