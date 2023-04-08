//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <iterator>
#include "MyDebug.h"
#include "CCustomInputOutputOperatorsBase.h"
#include "CCustomInputOutputOperatorsDerived.h"
#include "CInt.h"
#include "CCustomComparer.h"
#include "CPrintFunctionObject1.h"
#include "CPrintFunctionObject2.h"
#include "CPerson.h"
#include "CPersonSortingCriteriaFunctionObject.h"
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
void TestString1(void)
{
	PrintLineSeparator();

	wstring														String1(L"Timmy Anderson");
	wstring														String2(L"Timmy Anderson",0,10);
	wstring														String3(10,L'Z');
	wstring														String4({L'A',L'B',L'C'});
	wstring														String5(String1.cbegin()+4,String1.cend());
	// Pouzije sa MOVE CONSTRUCTOR.
	wstring														String6(wstring(L"QWERTY"));

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 3 [" << String3 << L"] !" << endl;
	wcout << L"STRING 4 [" << String4 << L"] !" << endl;
	wcout << L"STRING 5 [" << String5 << L"] !" << endl;
	wcout << L"STRING 6 [" << String6 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestString2(void)
{
	PrintLineSeparator();

	wstring														Text1=L"ABC";

	wcout << L"TEXT 1 [" << Text1 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 1 [0] [" << int(Text1[0]) << L"] !" << endl;
	wcout << L"TEXT 1 [1] [" << int(Text1[1]) << L"] !" << endl;
	wcout << L"TEXT 1 [2] [" << int(Text1[2]) << L"] !" << endl;

	// !!! Od C++11 je pristup k [INDEX==SIZE] VALIDNY a vysledok je CHARACTER '\0'.
	wcout << L"TEXT 1 [3] [" << int(Text1[3]) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 1 at(0) [" << int(Text1.at(0)) << L"] !" << endl;
	wcout << L"TEXT 1 at(1) [" << int(Text1.at(1)) << L"] !" << endl;
	wcout << L"TEXT 1 at(2) [" << int(Text1.at(2)) << L"] !" << endl;

	try
	{
		// !!! METHOD at() NEUMOZNUJE pristup k CHARACTER s [INDEX==SIZE].
		wcout << L"TEXT 1 at(3) [" << int(Text1.at(3)) << L"] !" << endl;
	}
	catch(const out_of_range& E)
	{
		wcout << L"TEXT 1 at(3) EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! OPERATOR[] je mozne pouzit aj na zapis CHARACTERS.
	Text1[1]=L'!';

	wcout << L"TEXT 1 [" << Text1 << L"] !" << endl;

	PrintLineSeparator();

	wstring														Text2;

	Text2.resize(3);

	Text2[0]=L'A';
	Text2[1]=L'B';
	Text2[2]=L'C';

	wcout << L"TEXT 2 [" << Text2 << L"] !" << endl;
	wcout << L"TEXT 2 CAPACITY [" << Text2.capacity() << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 2 [0] [" << int(Text2[0]) << L"] !" << endl;
	wcout << L"TEXT 2 [1] [" << int(Text2[1]) << L"] !" << endl;
	wcout << L"TEXT 2 [2] [" << int(Text2[2]) << L"] !" << endl;

	// !!! Od C++11 je pristup k [INDEX==SIZE] VALIDNY a vysledok je CHARACTER '\0'.
	wcout << L"TEXT 2 [3] [" << int(Text2[3]) << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TEXT 2 at(0) [" << int(Text2.at(0)) << L"] !" << endl;
	wcout << L"TEXT 2 at(1) [" << int(Text2.at(1)) << L"] !" << endl;
	wcout << L"TEXT 2 at(2) [" << int(Text2.at(2)) << L"] !" << endl;

	try
	{
		// !!! METHOD at() NEUMOZNUJE pristup k CHARACTER s [INDEX==SIZE].
		wcout << L"TEXT 2 at(3) [" << int(Text2.at(3)) << L"] !" << endl;
	}
	catch(const out_of_range& E)
	{
		wcout << L"TEXT 2 at(3) EXCEPTION [" << ConvertStringToWideString(E.what()) << L"] !" << endl;
	}

	PrintLineSeparator();

	// !!! METHOD at() je mozne pouzit aj na zapis CHARACTERS.
	Text2.at(1)=L'!';

	wcout << L"TEXT 2 [" << Text2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestString3(void)
{
	PrintLineSeparator();

	wstring														String1(L"AAA");
	wstring														String2(L"BBB");
	wstring														String3(L"AAB");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;
	wcout << L"STRING 3 [" << String3 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"COMPARE(STRING 1,STRING 1) [" << String1.compare(String1) << L"] !" << endl;
	wcout << L"COMPARE(STRING 1,STRING 2) [" << String1.compare(String2) << L"] !" << endl;
	wcout << L"COMPARE(STRING 2,STRING 1) [" << String2.compare(String1) << L"] !" << endl;
	wcout << L"COMPARE(STRING 1,STRING 3) [" << String1.compare(String3) << L"] !" << endl;
	wcout << L"COMPARE(STRING 3,STRING 1) [" << String3.compare(String1) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestString4(void)
{
	PrintLineSeparator();

	wstring														String1(L"AAA");
	wstring														String2(L"BBB");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;
	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"OPERATOR== [" << ((String1==String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR!= [" << ((String1!=String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR< [" << ((String1<String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR<= [" << ((String1<=String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR>= [" << ((String1>=String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"OPERATOR> [" << ((String1>String2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestString5(void)
{
	PrintLineSeparator();

	wstring														String1(L"Timmy Anderson");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,L"AAA");

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,wstring(L"BBB"));

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,wstring(L"123456"),1,4);

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,L"123456",4);

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	String1.replace(2,3,5,L'!');

	wcout << L"STRING 1 [" << String1 << L"] !" << endl;

	PrintLineSeparator();

	wstring														String2(L"Timmy Anderson");

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,L"AAA");

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,wstring(L"BBB"));

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	wstring														TempString(L"123456");

	String2.replace(String2.begin()+2,String2.begin()+5,TempString.cbegin()+1,TempString.cbegin()+5);

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,L"123456",4);

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	String2.replace(String2.begin()+2,String2.begin()+5,5,L'!');

	wcout << L"STRING 2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestString6(void)
{
	PrintLineSeparator();

	wstring														String(L"Timmy Anderson");

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.erase(3,2);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.erase(String.begin(),String.begin()+3);

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();

	String.erase(String.begin());

	wcout << L"STRING [" << String << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamOperations1(void)
{
	PrintLineSeparator();

	try
	{
		wstringstream											StringStream(L"100 200");
		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream(L"ABC 200");
		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream(L"100 ABC");
		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamOperations2(void)
{
	PrintLineSeparator();

	try
	{
		wstringstream											StringStream;

		StringStream << 100;
		StringStream << L" ";
		StringStream << 200;

		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream;

		StringStream << L"ABC";
		StringStream << L" ";
		StringStream << 200;

		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();

	try
	{
		wstringstream											StringStream;

		StringStream << 100;
		StringStream << L" ";
		StringStream << L"ABC";

		int														Value1;
		int														Value2;

		StringStream >> Value1;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 1 FAILED !"));
		}

		StringStream >> Value2;

		if (StringStream.operator bool()==false)
		{
			throw(wstring(L"READ of VALUE 2 FAILED !"));
		}

		wcout << L"RESULT [" << (Value1+Value2) << L"] !" << endl;
	}
	catch(const wstring& E)
	{
		wcout << L"READ FAILED with EXCEPTION [" << E.c_str() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestStreamOperations3(void)
{
	PrintLineSeparator();

	{
		CCustomInputOutputOperatorsDerived						Object1(111,222.345,333,444.567);

		wcout << L"OBJECT 1 [" << Object1.ToString() << L"] !" << endl;

		PrintLineSeparator();

		wstringstream											StringStream;

		StringStream << Object1;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		PrintLineSeparator();

		CCustomInputOutputOperatorsDerived						Object2;

		StringStream >> Object2;

		wcout << L"OBJECT 2 [" << Object2.ToString() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		CCustomInputOutputOperatorsDerived						Object1(111,222.345,333,444.567);

		wcout << L"OBJECT 1 [" << Object1.ToString() << L"] !" << endl;

		PrintLineSeparator();

		wstringstream											StringStream;

		// !!! Nastavi sa CUSTOM WIDTH a FILL CHARACTER.
		StringStream << setw(50);
		StringStream << setfill(L'_');

		StringStream << Object1;

		wcout << L"STREAM CONTENT [" << StringStream.str() << L"] !" << endl;

		PrintLineSeparator();

		CCustomInputOutputOperatorsDerived						Object2;

		// !!! Citanie ZLYHA, pretoze STREAM zacina znakmi '_' a nie cislom.
		StringStream >> Object2;

		if (StringStream.operator bool()==true)
		{
			wcout << L"OBJECT 2 [" << Object2.ToString() << L"] !" << endl;
		}
		else
		{
			wcout << L"READ OPERATION FAILED !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestArray(void)
{
	PrintLineSeparator();

	// !!! ARRAY je NEINICAILIZOVANE. ITEMS obsahuju UNDEFINED VALUES.
	array<int,5>												Array1;

	PrintCollection(L"ARRAY 1",Array1);

	// !!! ARRAY je INICAILIZOVANE. ITEMS obsahuju 0.
	array<int,5>												Array2{};

	PrintCollection(L"ARRAY 2",Array2);

	array<int,5>												Array3{5,4,8};

	PrintCollection(L"ARRAY 3",Array3);

	array<int,5>												Array4{5,4,8,9,23};

	PrintCollection(L"ARRAY 4",Array4);

	array<int,5>												Array5{};

	PrintCollection(L"ARRAY 5",Array5);

	// Vola sa IMPLICITNY OPERATOR=
	Array5=Array4;

	PrintCollection(L"ARRAY 5",Array5);

	array<int,5>												Array6=Array5;

	PrintCollection(L"ARRAY 6",Array6);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestVector(void)
{
	PrintLineSeparator();

	vector<int>													Vector{5,4,8,9,23};

	PrintCollection(L"VECTOR",Vector);

	Vector[1]=Vector[1]+5;
	Vector.at(2)=17;

	PrintCollection(L"VECTOR",Vector);

	try
	{
		int														Value=Vector.at(20);

		// !!! Hodi EXCEPTION, pretoze INDEX je OUT OF BOUNDS.
		wcout << L"VECTOR [20] VALUE [" << Value << L"] !" << endl;
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
void TestDequeue(void)
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
void TestList(void)
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
void TestForwardList(void)
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
void TestSet(void)
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
void TestMultiSet(void)
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
void TestMap(void)
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
void TestMultiMap(void)
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
void TestUnorderedSet(void)
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
void TestUnorderedMultiSet(void)
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
void TestUnorderedMap(void)
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
void TestUnorderedMultiMap(void)
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
void TestAlgorithms1(void)
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
void TestAlgorithms2(void)
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
void TestAlgorithms3(void)
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
void TestOutputStreamIterator(void)
{
	PrintLineSeparator();

	wstringstream												Stream;

	ostream_iterator<int,wchar_t>								Iterator1(Stream);

	*Iterator1=10;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator1=20;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	// !!! Je to EMPTY OPERATION.
	(void)*Iterator1++;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator1=30;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	// Definuje sa aj SEPARATOR.
	ostream_iterator<int,wchar_t>								Iterator2(Stream,L" ");

	*Iterator2=10;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator2=20;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	// !!! Je to EMPTY OPERATION.
	(void)*Iterator2++;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator2=30;

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	ostream_iterator<wstring,wchar_t>								Iterator3(Stream,L" ");

	*Iterator3=L"AAA";

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	*Iterator3=L"BBB";

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	ostream_iterator<CPerson,wchar_t>								Iterator4(Stream);

	*Iterator4=CPerson(L"Timmy",12);

	wcout << L"STREAM - [" << Stream.str() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestInputStreamIterator(void)
{
	PrintLineSeparator();

	// !!! EMPTY INPUT STREAM ITERATOR sluzi ako identifikator EOR, alebo ERROR.
	istream_iterator<int,wchar_t>								ErrorEof1;
	istream_iterator<CPerson,wchar_t>							ErrorEof2;
	bool														AddSeparator;

	wstringstream												Stream1(L"100 200 300");
	istream_iterator<int,wchar_t>								Iterator1(Stream1);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator1!=ErrorEof1)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		int														Item=*Iterator1;

		wcout << Item;

		Iterator1++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream1.eof() << L"] GOOD [" << Stream1.good() << L"] !" << L"] BAD [" << Stream1.bad() << L"] !" << L"] FAIL [" << Stream1.fail() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Obsahuje NON-INTEGER, ktory bude vyhodnoteny ako ERROR.
	wstringstream												Stream2(L"100 200zzz300");
	istream_iterator<int,wchar_t>								Iterator2(Stream2);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator2!=ErrorEof1)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		int														Item=*Iterator2;

		wcout << Item;

		Iterator2++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream2.eof() << L"] GOOD [" << Stream2.good() << L"] !" << L"] BAD [" << Stream2.bad() << L"] !" << L"] FAIL [" << Stream2.fail() << L"] !" << endl;

	PrintLineSeparator();

	wstringstream												Stream3(L"{Timmy 12}{Jenny 13}");
	istream_iterator<CPerson,wchar_t>							Iterator3(Stream3);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator3!=ErrorEof2)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		CPerson													Item=*Iterator3;

		wcout << Item;

		Iterator3++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream3.eof() << L"] GOOD [" << Stream3.good() << L"] !" << L"] BAD [" << Stream3.bad() << L"] !" << L"] FAIL [" << Stream3.fail() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Chybny format.
	wstringstream												Stream4(L"{Timmy 12{Jenny 13}");
	istream_iterator<CPerson,wchar_t>							Iterator4(Stream4);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator4!=ErrorEof2)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		CPerson													Item=*Iterator4;
		
		wcout << Item;

		Iterator4++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream4.eof() << L"] GOOD [" << Stream4.good() << L"] !" << L"] BAD [" << Stream4.bad() << L"] !" << L"] FAIL [" << Stream4.fail() << L"] !" << endl;

	PrintLineSeparator();

	wstringstream												Stream5(L"100 200 300 400 500 600 700");
	istream_iterator<int,wchar_t>								Iterator5(Stream5);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator5!=ErrorEof1)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// Nacita sa ITEM z INPUT STREAM.
		int														Item=*Iterator5;

		wcout << Item;

		Iterator5++;

		// Preskoci nasledujuci ITEM.
		Iterator5++;

		// Preskoci nasledujuci ITEM.
		advance(Iterator5,1);
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream5.eof() << L"] GOOD [" << Stream5.good() << L"] !" << L"] BAD [" << Stream5.bad() << L"] !" << L"] FAIL [" << Stream5.fail() << L"] !" << endl;
	
	PrintLineSeparator();

	wstringstream												Stream6(L"{Timmy 12}{Jenny 13}");
	istream_iterator<CPerson,wchar_t>							Iterator6(Stream6);

	wcout << L"ITEMS - [";

	AddSeparator=false;

	// !!! Cita data pokym nedoslo k EOF, alebo ERROR.
	while(Iterator6!=ErrorEof2)
	{
		if (AddSeparator==true)
		{
			wcout << L" ";
		}
		else
		{
			AddSeparator=true;
		}

		// !!! Citaju sa MEMBERS daneho ITEM pomocou OPERATOR->.
		wstring													Name=Iterator6->GetName();
		int														Age=Iterator6->GetAge();

		wcout << L"[";
		wcout << Name;
		wcout << L" ";
		wcout << Age;
		wcout << L"]";

		Iterator6++;
	}

	wcout << L"] !" << endl;

	wcout << L"STATE - EOF [" << Stream6.eof() << L"] GOOD [" << Stream6.good() << L"] !" << L"] BAD [" << Stream6.bad() << L"] !" << L"] FAIL [" << Stream6.fail() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestPredicate(void)
{
	PrintLineSeparator();

	set<CPerson,CPersonSortingCriteriaFunctionObject>			Set;

	Set.insert(CPerson(L"Timmy",12));
	Set.insert(CPerson(L"Jenny",13));
	Set.insert(CPerson(L"Atreyu",12));

	// ITEMS su SORTED podla SORTING CRITERIAS implementovanymi FUNCTION OBJECT - podla ABECEDY.
	PrintCollection(L"SET",Set);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestString1();
	//TestString2();
	//TestString3();
	//TestString4();
	//TestString5();
	//TestString6();
	//TestStreamOperations1();
	//TestStreamOperations2();
	//TestStreamOperations3();
	//TestArray();
	//TestVector();
	//TestDequeue();
	//TestList();
	//TestForwardList();
	//TestSet();
	//TestMultiSet();
	//TestMap();
	//TestMultiMap();
	//TestUnorderedSet();
	//TestUnorderedMultiSet();
	//TestUnorderedMap();
	//TestUnorderedMultiMap();
	//TestAlgorithms1();
	//TestAlgorithms2();
	//TestAlgorithms3();
	//TestOutputIterator();
	//TestInputIterator();
	//TestForwardIterator();
	//TestBidirectionalIterator();
	//TestRandomAccessIterator();
	//TestOutputStreamIterator();
	//TestInputStreamIterator();
	TestPredicate();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------