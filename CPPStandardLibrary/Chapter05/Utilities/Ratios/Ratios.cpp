//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <utility>
#include <ratio>
#include <iostream>
#include "MyDebug.h"
//-----------------------------------------------------------------------------
using namespace std;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRatios(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << ratio<2,3>::num << L"/" << ratio<2,3>::den << "] !" << endl;

	// !!! Vypise [2/3], pretoze CLASS [ratio<N,D>] robi v COMPILE TIME vykratenie zlomku.
	wcout << L"VALUE [" << ratio<4,6>::num << L"/" << ratio<4,6>::den << "] !" << endl;

	PrintLineSeparator();

	// !!! COMPILER hodi WARNING, pretoze VARIABLES nie su pouzite. Vypis na konzolu sa za pouzitie nepovazuje.
	// !!!!! Definovanie VARIABLES typu [ratio<N,D>] NEMA PRAKTICKY VYZNAM, pretoze nad touto CLASS nie su definovane ZIADNE MEMBER OPERATORS, ani METHODS.
	ratio<7,6>													Value1;
	ratio<2,12>													Value2;

	// Aby COMPILER nehlasil WARNING, ze VARIABLES su nepouzite.
	(void)Value1;
	(void)Value2;

	wcout << L"VALUE 1 [" << Value1.num << L"/" << Value1.den << "] !" << endl;
	wcout << L"VALUE 2 [" << Value2.num << L"/" << Value2.den << "] !" << endl;

	// Operacie nad 2 zlomkami.
	using														TYPE1=ratio_add<ratio<3,4>,ratio<1,2>>::type;
	using														TYPE2=ratio_subtract<ratio<3,4>,ratio<1,2>>::type;
	using														TYPE3=ratio_multiply<ratio<3,4>,ratio<1,2>>::type;
	using														TYPE4=ratio_divide<ratio<3,4>,ratio<1,2>>::type;
	
	wcout << L"TYPE 1 [" << TYPE1::num << L"/" << TYPE1::den << "] !" << endl;
	wcout << L"TYPE 2 [" << TYPE2::num << L"/" << TYPE2::den << "] !" << endl;
	wcout << L"TYPE 3 [" << TYPE3::num << L"/" << TYPE3::den << "] !" << endl;
	wcout << L"TYPE 4 [" << TYPE4::num << L"/" << TYPE4::den << "] !" << endl;

	PrintLineSeparator();

	wcout << L"EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !" << endl;
	wcout << L"NOT EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_not_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !" << endl;
	wcout << L"LESS (ratio<3,4>,ratio<1,2>) [" << ((ratio_less<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !" << endl;
	wcout << L"LESS EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_less_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !" << endl;
	wcout << L"GREATER (ratio<3,4>,ratio<1,2>) [" << ((ratio_greater<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !" << endl;
	wcout << L"GREATER EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_greater_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !" << endl;

	PrintLineSeparator();

	wcout << L"MEGA [" << mega::num << L"/" << mega::den << "] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	TestRatios();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------