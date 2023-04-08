//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <algorithm>
#include <string>
#include "MyDebug.h"
#include "CName.h"
#include "CNameWithSwap.h"
#include "CInt.h"
//-----------------------------------------------------------------------------
// !!! VC++ ma hodnoty 'min' a 'max' definovane ako MACROS a preto ich je nutne oddefinovat.
#ifdef _MSC_VER
#undef min
#undef max
#endif
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::rel_ops;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CustomComparer(int X, int Y)
{
	wcout << L"CUSTOM COMPARER USED !" << endl;

	if (X<Y)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//-----------------------------------------------------------------------------
void TestMinMax(void)
{
	PrintLineSeparator();

	wcout << L"MIN(10,20) [" << min(10,20) << L"] !" << endl;
	wcout << L"MAX(10,20) [" << max(10,20) << L"] !" << endl;
	wcout << L"MIN(4,11,6,88,2,45) [" << min({4,11,6,88,2,45}) << L"] !" << endl;
	wcout << L"MAX(4,11,6,88,2,45) [" << max({4,11,6,88,2,45}) << L"] !" << endl;

	pair<int,int>												MinMax1=minmax({4,11,6,88,2,45});

	wcout << L"MIN(4,11,6,88,2,45) [" << MinMax1.first << L"] !" << endl;
	wcout << L"MAX(4,11,6,88,2,45) [" << MinMax1.second << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"MIN(10,20) [" << min(10,20,CustomComparer) << L"] !" << endl;
	wcout << L"MAX(10,20) [" << max(10,20,CustomComparer) << L"] !" << endl;

	pair<int,int>												MinMax2=minmax({4,11,6,88,2,45},CustomComparer);

	wcout << L"MIN(4,11,6,88,2,45) [" << MinMax2.first << L"] !" << endl;
	wcout << L"MAX(4,11,6,88,2,45) [" << MinMax2.second << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSwap(void)
{
	PrintLineSeparator();

	int															X=100;
	int															Y=200;

	swap(X,Y);

	wcout << L"X [" << X << L"] !" << endl;
	wcout << L"Y [" << Y << L"] !" << endl;

	PrintLineSeparator();

	wstring														String1=L"Timmy Anderson";
	wstring														String2=L"Jenny Thompson";

	swap(String1,String2);

	wcout << L"String1 [" << String1 << L"] !" << endl;
	wcout << L"String2 [" << String2 << L"] !" << endl;

	PrintLineSeparator();

	CName														Name1(L"Timmy",L"Anderson",12);
	CName														Name2(L"Jenny",L"Thompson",13);

	// !!! Pouzije sa MOVE SEMANTICS.
	swap(Name1,Name2);

	wcout << L"NAME [" << Name1.GetFirstName() << L" " << Name1.GetLastName() << L"], AGE [" << Name1.GetAge() << L"] !" << endl;
	wcout << L"NAME [" << Name2.GetFirstName() << L" " << Name2.GetLastName() << L"], AGE [" << Name2.GetAge() << L"] !" << endl;

	PrintLineSeparator();

	CNameWithSwap												NameSwap1(L"Timmy",L"Anderson",12);
	CNameWithSwap												NameSwap2(L"Jenny",L"Thompson",13);

	// !!! Pouzije sa CUSTOM FUNCTION swap().
	// !!! Pouzije sa MOVE SEMANTICS.
	swap(NameSwap1,NameSwap2);

	wcout << L"NAME [" << NameSwap1.GetFirstName() << L" " << NameSwap1.GetLastName() << L"], AGE [" << NameSwap1.GetAge() << L"] !" << endl;
	wcout << L"NAME [" << NameSwap2.GetFirstName() << L" " << NameSwap2.GetLastName() << L"], AGE [" << NameSwap2.GetAge() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperators(void)
{
	PrintLineSeparator();

	CInt														Value1(100);
	CInt														Value2(200);

	// !!! Pouzije sa OPERATOR s NAMESPACE [std::rel_ops], ktory pouzije OPERATOR== definovany v CLASS CInt.
	// !!! CLASS [CInt] NEOBSAHUJE deklaracie OPERATOR!=, OPERATOR>, OPERATOR<= a OPERATOR>=.
	wcout << L"VALUE1!=VALUE2 [" << ((Value1!=Value2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VALUE1>VALUE2 [" << ((Value1>Value2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VALUE1<=VALUE2 [" << ((Value1<=Value2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"VALUE1>=VALUE2 [" << ((Value1>=Value2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestMinMax();
	//TestSwap();
	TestOperators();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------