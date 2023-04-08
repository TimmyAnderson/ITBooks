//-------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <conio.h>
#include <string>
#include <istream>
#include <ostream>
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <iterator>
#include "Name.h"
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void PrintIntValue(int Value)
{
	wcout << L"Vakue: " << Value << L" !\n";
}
//-------------------------------------------------------------------------------------------------------
bool IntValuePredicate(int Value)
{
	if (Value<10)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-------------------------------------------------------------------------------------------------------
void CoutTest(void)
{
	wcout << L"Hello world !\n";

	wstring				Name=L"Timmy Anderson";

	// !!!!! Tento riadok VC NESKOMPILUJE, pokial nepridam [#include <string>].
	wcout << L"My name is: [" << Name << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void CinTest(void)
{
	wstring				Text;

	wcout << L"Enter text WITH SPACE !\n";

	// !!! Nacita text iba po 1. WHITE CHAR.
	wcin >> Text;

	wcout << L"You entered text [" << Text << L"] !\n";

	wstring				Temp;

	// Vycistim BUFFER.
	getline(wcin,Temp);

	wstring				Name;
	int					Age;

	wcout << L"Enter FULL NAME !\n";

	// !!! Na nacitanie CELEHO RIADKU, musim pouzit getline().
	getline(wcin,Name);

	wcout << L"Enter AGE !\n";

	wcin >> Age;

	wcout << L"Name: [" << Name << L"], Age: [" << Age << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void VectorTest(void)
{
	vector<int>			Vector1(1000);

	wcout << L"Vector.size(): [" << Vector1.size() << L"] !\n";
	wcout << L"Vector.capacity(): [" << Vector1.capacity() << L"] !\n";

	Vector1.push_back(100);

	wcout << L"PUSH BACK !\n";

	wcout << L"Vector.size(): [" << Vector1.size() << L"] !\n";
	wcout << L"Vector.capacity(): [" << Vector1.capacity() << L"] !\n";

	vector<int>			Vector2(1000);

	try
	{
		// !!!!! Nato, aby nasledujuci test zbehol je treba pouzit RELEASE kompilaciu, kde su vypnute dodatocne kontroly zapnute v DEBUG kompilacii.

		// NEHODI EXCEPTION, aj ked som PREKROCIL VELKOST vector.
		int				Temp=Vector2[2222];
	}
	catch(...)
	{
		wcout << L"EXCEPTION after using [] !!!\n";
	}

	try
	{
		// !!!!! Nato, aby nasledujuci test zbehol je treba pouzit RELEASE kompilaciu, kde su vypnute dodatocne kontroly zapnute v DEBUG kompilacii.

		// !!! HODI EXCEPTION kedze som PREKROCIL VELKOST vector.
		Vector2.at(2222);
	}
	catch(out_of_range)
	{
		wcout << L"EXCEPTION after using at() !!!\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void ListTest(void)
{
	list<wstring>		List;

	List.push_back(L"Timmy");
	List.push_back(L"Atreyu");
	List.push_back(L"Jenny");
	
	// Kedze pri iteracii nemodifikujem data, mozem pouzit CONST ITERATOR.
	for(list<wstring>::const_iterator i=List.cbegin();i!=List.cend();i++)
	{
		const wstring&	Value=*i;

		wcout << L"Name: [" << Value << L"] !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void MapTest(void)
{
	map<int,wstring>	Map;

	Map[1]=L"Timmy";
	Map[2]=L"Atreyu";
	Map[3]=L"Jenny";

	wcout << L"Name for ID 1: [" << Map[1] << L"] !\n";
	wcout << L"Name for ID 2: [" << Map[2] << L"] !\n";
	wcout << L"Name for ID 3: [" << Map[3] << L"] !\n";

	Map[1]=L"Timothy Anderson";

	wcout << L"Map was MODIFIED !\n";

	wcout << L"Name for ID 1: [" << Map[1] << L"] !\n";
	wcout << L"Name for ID 2: [" << Map[2] << L"] !\n";
	wcout << L"Name for ID 3: [" << Map[3] << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void SortTest(void)
{
	vector<wstring>		Vector;

	Vector.push_back(L"Timmy");
	Vector.push_back(L"Atreyu");
	Vector.push_back(L"Jenny");

	sort(Vector.begin(),Vector.end());

	for(vector<wstring>::const_iterator i=Vector.cbegin();i!=Vector.cend();i++)
	{
		const wstring&	Value=*i;

		wcout << L"Name: [" << Value << L"] !\n";
	}
}
//-------------------------------------------------------------------------------------------------------
void CountTest(void)
{
	wstring			WStringName=L"Timothy Anderson";
	wchar_t			WCharTName[]=L"Timothy Anderson";

	// !!! Funguje to preto, lebo count() INTERNE pouziva operatory '++' a '==', ktore ITERATOR 'wstring' DEFINUJE.
	// !!! Vysledok je vracany ako 'iterator_traits<_InIt>::difference_type', ktory 'wstring' definuje ako 'int'.
	__int64			Count1=count(WStringName.begin(),WStringName.end(),'o');

	wcout << L"Count1: [" << Count1 << L"] !\n";

	int				ArraySize=_countof(WCharTName);

	// Ukazuje na znak '\0'.
	wchar_t*		EndOfStringPosition=WCharTName+ArraySize;
	__int64			Count2=count(WCharTName,EndOfStringPosition,'o');

	wcout << L"Count2: [" << Count2 << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void IStreamIteratorTest(void)
{
	wcout << L"Enter your NAME !\n";

	istream_iterator<wstring,wchar_t>	InputIterator(wcin);

	wstring						FirstName=*InputIterator;

	// Preskocim vsetky WHITE SPACES.
	InputIterator++;

	wstring						LastName=*InputIterator;

	wcout << L"Your FIRST name is: [" << FirstName << L"] !\n";
	wcout << L"Your LAST name is: [" << LastName << L"] !\n";
}
//-------------------------------------------------------------------------------------------------------
void OStreamIteratorTest(void)
{
	ostream_iterator<wstring,wchar_t>	OutputIterator(wcout);

	*OutputIterator=L"Name:";
	*OutputIterator=L" Timmy";
	*OutputIterator=L" Anderson";
	*OutputIterator=L" !\n";
}
//-------------------------------------------------------------------------------------------------------
void ForEachTest(void)
{
	int					Numbers[]={12,3,8,23,6,11,17,4,44,9,5,30};

	int*				StartIterator=Numbers;
	int*				EndIterator=Numbers+_countof(Numbers);

	// Vypise vsetky hodnoty.
	for_each(StartIterator,EndIterator,PrintIntValue);
}
//-------------------------------------------------------------------------------------------------------
void FindIfTest(void)
{
	int					Numbers[]={12,3,8,23,6,11,17,4,44,9,5,30};

	int*				StartIterator=Numbers;
	int*				EndIterator=Numbers+_countof(Numbers);

	int*				FirstOccurrence=find_if(StartIterator,EndIterator,IntValuePredicate);

	wcout << L"First value LOWER than 10 is: [" << *FirstOccurrence << "] !\n";
}
//-------------------------------------------------------------------------------------------------------
void CountIfTest(void)
{
	int					Numbers[]={12,3,8,23,6,11,17,4,44,9,5,30};

	int*				StartIterator=Numbers;
	int*				EndIterator=Numbers+_countof(Numbers);

	__int64				NumberOfOccurrences=count_if(StartIterator,EndIterator,IntValuePredicate);

	wcout << L"Number of values LOWER than 10: [" << NumberOfOccurrences << "] !\n";
}
//-------------------------------------------------------------------------------------------------------
void MemFunTest(void)
{
	vector<CName>		Names;

	Names.push_back(CName(L"Timmy",L"Anderson",12));
	Names.push_back(CName(L"Atreyu",L"",12));
	Names.push_back(CName(L"Jenny",L"Thompson",13));

	// !!! Kedze 'vector' obsahuje objekty a NIE SMERNIKY, tak MUSIM NAMIESTO mem_fun() pouzit mem_fun_ref().
	for_each(Names.begin(),Names.end(),mem_fun_ref(&CName::PrintFullName));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	//CoutTest();
	//CinTest();
	//VectorTest();
	//ListTest();
	//MapTest();
	//SortTest();
	//CountTest();
	//IStreamIteratorTest();
	//OStreamIteratorTest();
	//ForEachTest();
	//FindIfTest();
	//CountIfTest();
	MemFunTest();

	wprintf_s(L"Press any key to EXIT !\n");
	_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------