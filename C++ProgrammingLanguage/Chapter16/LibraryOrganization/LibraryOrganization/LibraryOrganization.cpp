//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <vector>
#include <list>
#include <cstdlib>
#include <cwchar>
#include <cwctype>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!!!! Ukazka GENERICKEHO ALGORITMU vyuzivajuceho ROVNAKO POMENOVANE TYPY v KAZDEJ COLLECTION vdaka comu sa TEMPLATE KOD stava NEZAVISLY na KONKRETNOM TYPE COLLECTION.
template<typename TCollection> void PrintAllItems(const TCollection& Collection)
{
	// !!!!! TEMPLATE FUNCTION funguje pre vector<T> i list<T>, lebo OBE definuju TYPE 'const_iterator'.
	TCollection::const_iterator									Iterator=Collection.begin();

	while(Iterator!=Collection.end())
	{
		// !!!!! TEMPLATE FUNCTION funguje pre vector<T> i list<T>, lebo OBE definuju TYPE 'value_type'.
		TCollection::value_type									Value=*Iterator;

		// !!! Pre jednoduchost predpokladam, ze COLLECTION obsahuje INTEGERS.
		wprintf_s(L"\tItem [%d] !\n",Value);
		Iterator++;
	}
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Ukazka GENERICKEHO ALGORITMU vyuzivajuceho ROVNAKO POMENOVANE TYPY v KAZDEJ COLLECTION vdaka comu sa TEMPLATE KOD stava NEZAVISLY na KONKRETNOM TYPE COLLECTION.
template<typename TCollection> void ReversePrintAllItems(const TCollection& Collection)
{
	// !!!!! TEMPLATE FUNCTION funguje pre vector<T> i list<T>, lebo OBE definuju TYPE 'const_reverse_iterator'.
	TCollection::const_reverse_iterator							Iterator=Collection.rbegin();

	while(Iterator!=Collection.rend())
	{
		// !!!!! TEMPLATE FUNCTION funguje pre vector<T> i list<T>, lebo OBE definuju TYPE 'value_type'.
		TCollection::value_type									Value=*Iterator;

		// !!! Pre jednoduchost predpokladam, ze COLLECTION obsahuje INTEGERS.
		wprintf_s(L"\tItem [%d] !\n",Value);
		Iterator++;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	int															Value1=std::atoi("10");

	wprintf_s(L"Value1: [%d] !\n",Value1);

	// !!! Nie je sucastou STL.
	int															Value2=_wtoi(L"10");

	wprintf_s(L"Value2: [%d] !\n",Value2);
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	vector<int>													Vector;
	int															Count=1;

	Vector.push_back(3);
	Vector.push_back(2);
	Vector.push_back(1);

	// !!! ITERATORS su implementovane ako TEMPLATES.
	for(vector<int>::iterator i=Vector.begin();i!=Vector.end();i++,Count++)
	{
		wprintf_s(L"Item [%d]: [%d] !\n",Count,*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	list<int>													List;

	List.push_back(1);
	List.push_back(2);
	List.push_back(3);

	wprintf_s(L"VECTOR:\n");
	PrintAllItems(Vector);

	wprintf_s(L"\n");

	wprintf_s(L"LIST:\n");
	PrintAllItems(List);

	wprintf_s(L"\n");

	wprintf_s(L"REVERSE VECTOR:\n");
	ReversePrintAllItems(Vector);

	wprintf_s(L"\n");

	wprintf_s(L"REVERSE LIST:\n");
	ReversePrintAllItems(List);
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	vector<int>													Vector;

	Vector.push_back(1);
	Vector.push_back(2);
	Vector.push_back(3);

	wprintf_s(L"VECTOR:\n");

	/*
	for(int i=0;i<100;i++)
	{
		// !!! Sposobi PAD PROGRAMU.
		wprintf_s(L"\tItem [%d] !\n",Vector[i]);
	}
	*/

	try
	{
		for(int i=0;i<100;i++)
		{
			// !!! Hodi EXCEPTION typu 'out_of_range'.
			wprintf_s(L"\tItem [%d] !\n",Vector.at(i));
		}
	}
	catch(const out_of_range& E)
	{
		printf_s("EXCEPTION [%s] !\n",E.what());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	vector<int>													Vector1;

	Vector1.push_back(1);
	Vector1.push_back(2);
	Vector1.push_back(3);

	vector<int>													Vector2;

	Vector2=Vector1;

	wprintf_s(L"VECTOR:\n");

	for(vector<int>::iterator i=Vector2.begin();i!=Vector2.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	vector<int>													Vector1;

	Vector1.push_back(1);
	Vector1.push_back(2);
	Vector1.push_back(3);

	vector<int>													Vector2;

	Vector2.assign(Vector1.begin(),Vector1.end()-1);

	wprintf_s(L"VECTOR:\n");

	for(vector<int>::iterator i=Vector2.begin();i!=Vector2.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	int															Array[]={1,2,3,4,5};

	// !!! Kopirovanie ITEMS z ARRAY pomocou ITERATORS. POINTER je TIEZ ITERATOR.
	vector<int>													Vector(&Array[0],&Array[5]);

	wprintf_s(L"VECTOR:\n");

	for(vector<int>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	int															Array[]={1,2,3,4,5};

	// !!! Kopirovanie ITEMS z ARRAY pomocou ITERATORS. POINTER je TIEZ ITERATOR.
	vector<int>													Vector(&Array[0],&Array[5]);

	wprintf_s(L"VECTOR:\n");

	for(vector<int>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	// !!! Odstrani 2 ITEMS Vector[1] a Vector[2].
	Vector.erase(Vector.begin()+1,Vector.begin()+3);

	wprintf_s(L"\n");

	wprintf_s(L"VECTOR:\n");

	for(vector<int>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	int															Array[]={1,2,3,4,5};

	// !!! Kopirovanie ITEMS z ARRAY pomocou ITERATORS. POINTER je TIEZ ITERATOR.
	vector<int>													Vector(&Array[0],&Array[5]);

	wprintf_s(L"VECTOR:\n");

	for(vector<int>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}

	// !!! NEFUNGUJE. Hodi KOMPILACNU CHYBU.
	//Vector.erase(&Vector[1],&Vector[3]);
	
	Vector.erase(vector<int>::const_iterator(&Vector[1],&Vector),vector<int>::const_iterator(&Vector[3],&Vector));

	wprintf_s(L"\n");

	wprintf_s(L"VECTOR:\n");

	for(vector<int>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		wprintf_s(L"\tItem: [%d] !\n",*i);
	}
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	vector<int>													Vector1;
	
	Vector1.push_back(1);
	Vector1.push_back(2);
	Vector1.push_back(3);

	vector<int>													Vector2;

	Vector2.push_back(1);
	Vector2.push_back(3);
	Vector2.push_back(2);
	
	if (Vector1<Vector2)
	{
		wprintf_s(L"Vector1<Vector2 !\n");
	}
	else
	{
		wprintf_s(L"Vector1>=Vector2 !\n");
	}

	if (Vector2<Vector1)
	{
		wprintf_s(L"Vector2<Vector1 !\n");
	}
	else
	{
		wprintf_s(L"Vector2>=Vector1 !\n");
	}

	if (Vector1>Vector2)
	{
		wprintf_s(L"Vector1>Vector2 !\n");
	}
	else
	{
		wprintf_s(L"Vector1<=Vector2 !\n");
	}

	if (Vector2>Vector1)
	{
		wprintf_s(L"Vector2>Vector1 !\n");
	}
	else
	{
		wprintf_s(L"Vector2<=Vector1 !\n");
	}

	if (Vector1==Vector2)
	{
		wprintf_s(L"Vector1==Vector2 !\n");
	}
	else
	{
		wprintf_s(L"Vector1!=Vector2 !\n");
	}

	if (Vector1!=Vector2)
	{
		wprintf_s(L"Vector1!=Vector2 !\n");
	}
	else
	{
		wprintf_s(L"Vector1==Vector2 !\n");
	}
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	vector<bool>												Vector;

	Vector.push_back(true);
	Vector.push_back(false);
	Vector.push_back(true);
	
	wprintf_s(L"VECTOR<bool>:\n");

	for(vector<bool>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		bool													Value=*i;

		wprintf_s(L"\tItem: [%d] !\n",Value);
	}

	Vector.flip();

	wprintf_s(L"\n");

	wprintf_s(L"VECTOR<bool>:\n");

	for(vector<bool>::iterator i=Vector.begin();i!=Vector.end();i++)
	{
		bool													Value=*i;

		wprintf_s(L"\tItem: [%d] !\n",Value);
	}
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
	Test11();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------