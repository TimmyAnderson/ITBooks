//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include <locale>
#include <codecvt> 
#include <typeindex>
#include <map>
#include "MyDebug.h"
#include "CBase.h"
#include "CDerivedPublic.h"
#include "CDerivedProtected.h"
#include "CDerivedPrivate.h"
#include "CType1.h"
#include "CType2.h"
#include "CClassWithCustomOperators.h"
#include "SFields.h"
#include "ESimpleEnum1.h"
#include "ESimpleEnum2.h"
#include "EClassEnum1.h"
#include "EClassEnum2.h"
#include "CPrivateCopyConstructor.h"
#include "CTypeWithOperatorsAndMethods.h"
#include "CTypeWithMoveConstructor.h"
#include "CTypeWithCopyAndMoveConstructor.h"
#include "CTypeWithMoveOperator.h"
#include "CTypeWithCopyAndNoExceptMoveConstructor.h"
#include "CInt.h"
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning (disable : 4996)
#undef min
#undef max
#endif
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void PrintDuration(wstring Prefix, TType Duration)
{
	wcout << Prefix << L" [" << Duration.count() << L"] in [" << TType::period::num << L"/" << TType::period::den << L"] SECOND !\n";
}
//-----------------------------------------------------------------------------
void PrintDurationInHHMMSSFFF(wstring Prefix, milliseconds Duration)
{
	hours														Hours=duration_cast<hours>(Duration);
	minutes														Minutes=duration_cast<minutes>(Duration % hours(1));
	seconds														Seconds=duration_cast<seconds>(Duration % minutes(1));
	milliseconds												Milliseconds=duration_cast<milliseconds>(Duration % seconds(1));

	int															State=wcout.rdstate();

	wcout << Prefix;
	wcout << L" [";

	wcout.fill(L'0');

	wcout.width(2);
	wcout << Hours.count();
	wcout << L":";

	wcout.width(2);
	wcout << Minutes.count();
	wcout << L":";

	wcout.width(2);
	wcout << Seconds.count();
	wcout << L".";

	wcout.width(3);
	wcout << Milliseconds.count();
	wcout << L"] !";

	wcout << endl;

	wcout.setstate(State);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDurationDefinitions(void)
{
	PrintLineSeparator();

	// Urcuje DURATION 10 sekund v sekundach.
	duration<int>												Duration1(10);

	// Vypisuje pocet TICKS v jednotkach casu, ktore DURATION reprezentuje.
	wcout << L"DURATION 1 [" << Duration1.count() << L"] in [" << duration<int>::period::num << L"/" << duration<int>::period::den << L"] SECOND !\n";

	// Urcuje DURATION 20 sekund v sekundach.
	duration<int,ratio<1,1>>									Duration2(20);

	wcout << L"DURATION 2 [" << Duration2.count() << L"] in [" << duration<int,ratio<1,1>>::period::num << L"/" << duration<int,ratio<1,1>>::period::den << L"] SECOND !\n";

	// Urcuje DURATION 20 sekund v 1/10 sekundy.
	duration<int,ratio<1,10>>									Duration3(200);

	wcout << L"DURATION 3 [" << Duration3.count() << L"] in [" << duration<int,ratio<1,10>>::period::num << L"/" << duration<int,ratio<1,10>>::period::den << L"] SECOND !\n";

	// Urcuje DURATION 5 sekund v 50/1000 sekundy.
	duration<int,ratio<50,1000>>								Duration4(100);

	wcout << L"DURATION 4 [" << Duration4.count() << L"] in [" << duration<int,ratio<50,1000>>::period::num << L"/" << duration<int,ratio<50,1000>>::period::den << L"] SECOND !\n";

	// Urcuje DURATION 14 sekund v 7/2 sekundy.
	// !!! Ako TYPE sa pouzije DOUBLE.
	duration<double,ratio<7,2>>									Duration5(4);

	wcout << L"DURATION 5 [" << Duration5.count() << L"] in [" << duration<double,ratio<7,2>>::period::num << L"/" << duration<double,ratio<7,2>>::period::den << L"] SECOND !\n";

	// Urcuje DURATION 10 sekund v MILISEKUNDACH.
	milliseconds												Duration6(10000);

	wcout << L"DURATION 6 [" << Duration6.count() << L"] in [" << milliseconds::period::num << L"/" << milliseconds::period::den << L"] SECOND !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDurationArithmeticOperations(void)
{
	PrintLineSeparator();

	// 6 sekund v milisekundach.
	duration<int,ratio<1,1000>>									Duration1(6000);
	// 2 sekundy v stotinach sekundy.
	duration<int,ratio<1,100>>									Duration2(200);

	// !!! Operacie su vykonane medzi 2 instanciami DURATION.
	// Vysledok je v jednotkach, ktory reprezentuje najvacsi spolocny delitelom co je v tomto pripade 1/1000 SEKUNDY.
	PrintDuration(L"RESULT 1",Duration1+Duration2);
	PrintDuration(L"RESULT 2",Duration1-Duration2);

	// !!! OPERATOR* je mozne aplikovat medzi DURATION a NUMERIC VALUE.
	// Vysledok je 30 sekund reprezentovany v 1/100 sekundy.
	PrintDuration(L"RESULT 3",Duration1*5);

	// !!! OPERATOR/ je mozne aplikovat medzi DURATION a NUMERIC VALUE.
	// Vysledok je 1.5 sekund reprezentovany v 1/1000 sekundy.
	PrintDuration(L"RESULT 4",Duration1/4);

	// !!! Operacia je vykonana medzi 2 instanciami DURATION. Vysledok je NUMERIC VALUE.
	// Vysledok je 3.
	wcout << L"RESULT 5 [" << Duration1/Duration2 << L"] !\n";

	// 15 sekund v 30/200 sekundy.
	duration<double,ratio<30,200>>								Duration3(100);

	// !!! Vysledny TYPE bude pouzivat na reprezentaciu TICKS TYPE [double], pretoze tento TYPE je COMMON TYPE pre TYPES [int] a [double].
	PrintDuration(L"RESULT 6",Duration1+Duration3);
	PrintDuration(L"RESULT 7",Duration1-Duration3);

	duration<double,ratio<1,3>>									Duration4(2);
	duration<double,ratio<2,5>>									Duration5(3);

	// Vysledok bude vyjadreny v 1/15 SEKUNDY.
	PrintDuration(L"RESULT 8",Duration4+Duration5);

	seconds														Duration6(3);
	milliseconds												Duration7(512);

	// !!! Operacia je vykonana medzi 2 instanciami DURATION. Vysledok je DURATION.
	PrintDuration(L"RESULT 9",Duration6%Duration7);

	// !!! Operacia je vykonana medzi 2 instanciami DURATION a NUMERIC VALUE. Vysledok je DURATION.
	PrintDuration(L"RESULT 10",Duration7%100);

	PrintDuration(L"RESULT 11",++Duration7);
	PrintDuration(L"RESULT 12",--Duration7);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDurationComparisonOperators(void)
{
	PrintLineSeparator();

	// 3 sekundy v rozlicnych DURATIONS.
	duration<int,ratio<1,1000>>									Duration1(3000);
	duration<int,ratio<1,100>>									Duration2(300);
	duration<double,ratio<1,1000>>								Duration3(3000);
	duration<double,ratio<75,50>>								Duration4(2);
	// 4 sekundy.
	duration<int,ratio<1,1>>									Duration5(4);

	// Vrati TRUE.
	wprintf_s(L"DURATION_1==DURATION_2 [%ls] !\n",(Duration1==Duration2) ? L"TRUE" : L"FALSE");
	// Vrati TRUE.
	wprintf_s(L"DURATION_1==DURATION_3 [%ls] !\n",(Duration1==Duration3) ? L"TRUE" : L"FALSE");
	// Vrati TRUE.
	wprintf_s(L"DURATION_1==DURATION_4 [%ls] !\n",(Duration1==Duration4) ? L"TRUE" : L"FALSE");
	// Vrati FALSE.
	wprintf_s(L"DURATION_1==DURATION_5 [%ls] !\n",(Duration1==Duration5) ? L"TRUE" : L"FALSE");
	// Vrati TRUE.
	wprintf_s(L"DURATION_1<DURATION_5 [%ls] !\n",(Duration1<Duration5) ? L"TRUE" : L"FALSE");
	// Vrati FALSE.
	wprintf_s(L"DURATION_1>DURATION_5 [%ls] !\n",(Duration1>Duration5) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestDurationConversions(void)
{
	PrintLineSeparator();

	seconds														Duration1(150);
	// !!! Kedze pri konverzii NEMOZE dojst k strate, IMPLICIT CONVERSION je MOZNA.
	milliseconds												Duration2=Duration1;

	PrintDuration(L"DURATION 1",Duration1);
	PrintDuration(L"DURATION 2",Duration2);

	// !!! Kedze pri konverzii MOZE dojst k strate, IMPLICIT CONVERSION NIE JE MOZNA.
	// !!!!! COMPILER hodi ERROR.
	//minutes													DurationError1=Duration1;

	// !!! Kedze pri konverzii MOZE dojst k strate, je NUTNE vykonat EXPLICIT CONVERSION pomocou TEMPLATE FUNCTION duration_cast<TType>.
	minutes														Duration3=duration_cast<minutes>(Duration1);

	PrintDuration(L"DURATION 3",Duration3);

	duration<double,ratio<1,1>>									Duration4(10);

	PrintDuration(L"DURATION 4",Duration4);

	// !!! Kedze pri konverzii MOZE dojst k strate (DOUBLE na INT), IMPLICIT CONVERSION NIE JE MOZNA.
	// !!!!! COMPILER hodi ERROR.
	//seconds													DurationError2=Duration4;

	// !!! Kedze pri konverzii MOZE dojst k strate (DOUBLE na INT), je NUTNE vykonat EXPLICIT CONVERSION pomocou TEMPLATE FUNCTION duration_cast<TType>.
	seconds														Duration5=duration_cast<seconds>(Duration4);

	PrintDuration(L"DURATION 5",Duration5);

	PrintLineSeparator();

	PrintDurationInHHMMSSFFF(L"10000 SECONDS",seconds(10000));
	PrintDurationInHHMMSSFFF(L"10000.123 SECONDS",(seconds(10000)+milliseconds(123)));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTimePoints(void)
{
	PrintLineSeparator();

	system_clock::time_point									Now1=system_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !\n";

	system_clock::time_point									Now2=system_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !\n";

	system_clock::duration										Difference=Now2-Now1;

	PrintDuration(L"DIFFERENCE",Difference);

	PrintLineSeparator();

	system_clock::time_point									TimePoint1;

	PrintDuration(L"TIME POINT 1",TimePoint1.time_since_epoch());

	// Pricitanie DURATION.
	system_clock::time_point									TimePoint2=TimePoint1+seconds(5);

	PrintDuration(L"TIME POINT 2",TimePoint2.time_since_epoch());

	// Pricitanie DURATION.
	TimePoint1+=seconds(2);

	PrintDuration(L"TIME POINT 1 - AFTER ADDITION",TimePoint1.time_since_epoch());

	// Odcitanie 2 TIME POINTS.
	PrintDuration(L"TIME POINT DIFFERENCE",TimePoint2-TimePoint1);

	PrintLineSeparator();

	// Vrati FALSE.
	wprintf_s(L"TIME_POINT_1==TIME_POINT_2 [%ls] !\n",(TimePoint1==TimePoint2) ? L"TRUE" : L"FALSE");
	// Vrati TRUE.
	wprintf_s(L"TIME_POINT_1!=TIME_POINT_2 [%ls] !\n",(TimePoint1!=TimePoint2) ? L"TRUE" : L"FALSE");
	// Vrati TRUE.
	wprintf_s(L"TIME_POINT_1<TIME_POINT_2 [%ls] !\n",(TimePoint1<TimePoint2) ? L"TRUE" : L"FALSE");
	// Vrati TRUE.
	wprintf_s(L"TIME_POINT_1<=TIME_POINT_2 [%ls] !\n",(TimePoint1<=TimePoint2) ? L"TRUE" : L"FALSE");
	// Vrati FALSE.
	wprintf_s(L"TIME_POINT_1>TIME_POINT_2 [%ls] !\n",(TimePoint1>TimePoint2) ? L"TRUE" : L"FALSE");
	// Vrati FALSE.
	wprintf_s(L"TIME_POINT_1>=TIME_POINT_2 [%ls] !\n",(TimePoint1>=TimePoint2) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();

	// !!! Pri strate presnosti je NUTNE na konverziu pouzit TEMPLATE FUNCTION time_point<TClock1,TDuration1>]::time_point_cast<[time_point<TClock2,TDuration2>]>().
	time_point<system_clock,seconds>								TimePointInSeconds=time_point_cast<seconds>(TimePoint2);

	PrintDuration(L"TIME POINT is SECONDS",TimePointInSeconds.time_since_epoch());

	// !!! Ak k strate presnosti NEDOCHADZA, vykonava sa IMPLICIT CONVERSION.
	time_point<system_clock,milliseconds>							TimePointInMillseconds=TimePointInSeconds;

	PrintDuration(L"TIME POINT is MILLISECONDS",TimePointInMillseconds.time_since_epoch());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSystemClock(void)
{
	PrintLineSeparator();

	wcout << L"IS STEADY [" << system_clock::is_steady << L"] !\n";
	wcout << L"DURATION [" << typeid(system_clock::duration).name() << L"] !\n";
	wcout << L"TICK TYPE [" << typeid(system_clock::rep).name() << L"] !\n";
	wcout << L"TICK PERIOD TYPE [" << typeid(system_clock::period).name() << L"] !\n";
	wcout << L"TIME POINT TYPE [" << typeid(system_clock::time_point).name() << L"] !\n";

	PrintLineSeparator();

	system_clock::time_point									Now1=system_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !\n";

	system_clock::time_point									Now2=system_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !\n";

	system_clock::duration										Difference=Now2-Now1;

	PrintDuration(L"DIFFERENCE",Difference);

	PrintLineSeparator();

	system_clock::time_point									Min=system_clock::time_point::min();
	system_clock::time_point									Max=system_clock::time_point::max();

	wcout << L"MIN [" << Min.time_since_epoch().count() << L"] !\n";
	wcout << L"MAX [" << Max.time_since_epoch().count() << L"] !\n";

	PrintLineSeparator();

	// CLOCK [system_clock] umoznuje konverziu na TYPE [time_t].
	time_t														Time1=system_clock::to_time_t(Now1);
	time_t														Time2=system_clock::to_time_t(Now2);
	string														Time1AsText(asctime(localtime(&Time1)));
	string														Time2AsText(asctime(localtime(&Time2)));

	// Kedze FUNCTION asctime() uplne absurdne pridava na koniec retazca znak '\n', treba ho odstranit.

	Time1AsText.erase(Time1AsText.find('\n'));
	Time2AsText.erase(Time2AsText.find('\n'));

	wcout << L"TIME 1 [" << Time1AsText.c_str() << L"] !\n";
	wcout << L"TIME 2 [" << Time2AsText.c_str() << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHighResolutionClock(void)
{
	PrintLineSeparator();

	// !!! Vo WINDOWS 10 bol CLOCK STEADY.
	wcout << L"IS STEADY [" << high_resolution_clock::is_steady << L"] !\n";
	wcout << L"DURATION [" << typeid(high_resolution_clock::duration).name() << L"] !\n";
	wcout << L"TICK TYPE [" << typeid(high_resolution_clock::rep).name() << L"] !\n";
	wcout << L"TICK PERIOD TYPE [" << typeid(high_resolution_clock::period).name() << L"] !\n";
	wcout << L"TIME POINT TYPE [" << typeid(high_resolution_clock::time_point).name() << L"] !\n";

	PrintLineSeparator();

	high_resolution_clock::time_point									Now1=high_resolution_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !\n";

	high_resolution_clock::time_point									Now2=high_resolution_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !\n";

	high_resolution_clock::duration										Difference=Now2-Now1;

	PrintDuration(L"DIFFERENCE",Difference);

	PrintLineSeparator();

	high_resolution_clock::time_point									Min=high_resolution_clock::time_point::min();
	high_resolution_clock::time_point									Max=high_resolution_clock::time_point::max();

	wcout << L"MIN [" << Min.time_since_epoch().count() << L"] !\n";
	wcout << L"MAX [" << Max.time_since_epoch().count() << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSteadyClock(void)
{
	PrintLineSeparator();

	wcout << L"IS STEADY [" << steady_clock::is_steady << L"] !\n";
	wcout << L"DURATION [" << typeid(steady_clock::duration).name() << L"] !\n";
	wcout << L"TICK TYPE [" << typeid(steady_clock::rep).name() << L"] !\n";
	wcout << L"TICK PERIOD TYPE [" << typeid(steady_clock::period).name() << L"] !\n";
	wcout << L"TIME POINT TYPE [" << typeid(steady_clock::time_point).name() << L"] !\n";

	PrintLineSeparator();

	steady_clock::time_point									Now1=steady_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !\n";

	steady_clock::time_point									Now2=steady_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !\n";

	steady_clock::duration										Difference=Now2-Now1;

	PrintDuration(L"DIFFERENCE",Difference);
	 
	PrintLineSeparator();

	steady_clock::time_point									Min=steady_clock::time_point::min();
	steady_clock::time_point									Max=steady_clock::time_point::max();

	wcout << L"MIN [" << Min.time_since_epoch().count() << L"] !\n";
	wcout << L"MAX [" << Max.time_since_epoch().count() << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTimeTraits(void)
{
	PrintLineSeparator();
	
	wcout << L"TREAT as FLOATING POINT<float> [" << treat_as_floating_point<float>::value << L"] !\n";
	wcout << L"TREAT as FLOATING POINT<int> [" << treat_as_floating_point<int>::value << L"] !\n";
	wcout << L"TREAT as FLOATING POINT<system_clock::rep> [" << treat_as_floating_point<system_clock::rep>::value << L"] !\n";
	wcout << L"TREAT as FLOATING POINT<high_resolution_clock::rep> [" << treat_as_floating_point<high_resolution_clock::rep>::value << L"] !\n";
	wcout << L"TREAT as FLOATING POINT<steady_clock::rep> [" << treat_as_floating_point<steady_clock::rep>::value << L"] !\n";

	PrintLineSeparator();

	wcout << L"DURATION VALUES<int> MIN [" << duration_values<int>::min() << L"] !\n";
	wcout << L"DURATION VALUES<int> MAX [" << duration_values<int>::max() << L"] !\n";
	wcout << L"DURATION VALUES<int> ZERO [" << duration_values<int>::zero() << L"] !\n";
	wcout << L"DURATION VALUES<float> MIN [" << duration_values<float>::min() << L"] !\n";
	wcout << L"DURATION VALUES<float> MAX [" << duration_values<float>::max() << L"] !\n";
	wcout << L"DURATION VALUES<float> ZERO [" << duration_values<float>::zero() << L"] !\n";

	PrintLineSeparator();

	wcout << L"COMMON TYPE<duration<int>,duration<short>> [" << typeid(common_type<duration<int>,duration<short>>::type).name() << L"] !\n";
	wcout << L"COMMON TYPE<duration<int>,duration<float>> [" << typeid(common_type<duration<int>,duration<float>>::type).name() << L"] !\n";

	PrintLineSeparator();

	using														Clock1=time_point<steady_clock,duration<float>>;
	using														Clock2=time_point<steady_clock,duration<double>>;

	// !!! CLOCK MUSI byt ROVNAKY pre OBE TYPE PARAMETERS, kedze takto je TEMPLATE definovana.
	wcout << L"COMMON TYPE<steady_clock::time_point,Clock1> [" << typeid(common_type<steady_clock::time_point,Clock1>::type).name() << L"] !\n";

	PrintLineSeparator();

	// !!! CLOCK MUSI byt ROVNAKY pre OBE TYPE PARAMETERS, kedze takto je TEMPLATE definovana.
	wcout << L"COMMON TYPE<Clock1,Clock2> [" << typeid(common_type<Clock1,Clock2>::type).name() << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRatios(void)
{
	PrintLineSeparator();

	wcout << L"VALUE [" << ratio<2,3>::num << L"/" << ratio<2,3>::den << "] !\n";

	// !!! Vypise [2/3], pretoze CLASS [ratio<N,D>] robi v COMPILE TIME vykratenie zlomku.
	wcout << L"VALUE [" << ratio<4,6>::num << L"/" << ratio<4,6>::den << "] !\n";

	PrintLineSeparator();

	// !!! COMPILER hodi WARNING, pretoze VARIABLES nie su pouzite. Vypis na konzolu sa za pouzitie nepovazuje.
	// !!!!! Definovanie VARIABLES typu [ratio<N,D>] NEMA PRAKTICKY VYZNAM, pretoze nad touto CLASS nie su definovane ZIADNE MEMBER OPERATORS, ani METHODS.
	ratio<7,6>													Value1;
	ratio<2,12>													Value2;

	// Aby COMPILER nehlasil WARNING, ze VARIABLES su nepouzite.
	(void)Value1;
	(void)Value2;

	wcout << L"VALUE 1 [" << Value1.num << L"/" << Value1.den << "] !\n";
	wcout << L"VALUE 2 [" << Value2.num << L"/" << Value2.den << "] !\n";

	// Operacie nad 2 zlomkami.
	using														TYPE1=ratio_add<ratio<3,4>,ratio<1,2>>::type;
	using														TYPE2=ratio_subtract<ratio<3,4>,ratio<1,2>>::type;
	using														TYPE3=ratio_multiply<ratio<3,4>,ratio<1,2>>::type;
	using														TYPE4=ratio_divide<ratio<3,4>,ratio<1,2>>::type;
	
	wcout << L"TYPE 1 [" << TYPE1::num << L"/" << TYPE1::den << "] !\n";
	wcout << L"TYPE 2 [" << TYPE2::num << L"/" << TYPE2::den << "] !\n";
	wcout << L"TYPE 3 [" << TYPE3::num << L"/" << TYPE3::den << "] !\n";
	wcout << L"TYPE 4 [" << TYPE4::num << L"/" << TYPE4::den << "] !\n";

	PrintLineSeparator();

	wcout << L"EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !\n";
	wcout << L"NOT EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_not_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !\n";
	wcout << L"LESS (ratio<3,4>,ratio<1,2>) [" << ((ratio_less<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !\n";
	wcout << L"LESS EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_less_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !\n";
	wcout << L"GREATER (ratio<3,4>,ratio<1,2>) [" << ((ratio_greater<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !\n";
	wcout << L"GREATER EQUAL (ratio<3,4>,ratio<1,2>) [" << ((ratio_greater_equal<ratio<3,4>,ratio<1,2>>()) ? L"TRUE" : L"FALSE") << "] !\n";

	PrintLineSeparator();

	wcout << L"MEGA [" << mega::num << L"/" << mega::den << "] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintValueOrPointer() ma ako 2. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je NON-POINTER VALUE.
template<typename TType>
void InternalPrintValueOrPointer(TType ValueOrPointer, false_type)
{
	wcout << L"VALUE from VALUE [" << ValueOrPointer << L"] !\n";
}
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintValueOrPointer() ma ako 2. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je POINTER VALUE.
template<typename TType>
void InternalPrintValueOrPointer(TType ValueOrPointer, true_type)
{
	wcout << L"VALUE from POINTER [" << *ValueOrPointer << L"] !\n";
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValueOrPointer(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je POINTER sa pouziva TYPE TRAIT is_pointer<T>().
	InternalPrintValueOrPointer(ValueOrPointer,is_pointer<TType>());
}
//-----------------------------------------------------------------------------
void TestIsPointerTrait(void)
{
	PrintLineSeparator();

	wstring														Name=L"Timmy Anderson";
	int															Age=100;
	wstring*													PointerToName=&Name;
	int*														PointerToAge=&Age;

	PrintValueOrPointer(Name);
	PrintValueOrPointer(Age);

	PrintLineSeparator();

	PrintValueOrPointer(PointerToName);
	PrintValueOrPointer(PointerToAge);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat1() ma ako 3. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je INTEGER VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)
{
	wprintf_s(L"INTEGER VALUE [%d] !\n",ValueOrPointer);
}
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat1() ma ako 3. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je FLOAT VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, false_type)
{
	wprintf_s(L"FLOAT VALUE [%f] !\n",ValueOrPointer);
}
//-----------------------------------------------------------------------------
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat1() ma ako 2. PARAMETER TYPE [false_type], TYPE je NON-ARITHMETIC TYPE.
// Pre PARAMETER [int] sa C++ chova nasledovne.
// !!!!! A. CODE [InternalPrintIntegerOrFloat1(ValueOrPointer,is_arithmetic<int>(),is_integral<int>())] volany vo FUNCTION PrintIntegerOrFloat1() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat1(wstring,false,false). DOVOD PRECO v 2. a 3. PARAMETRI su hodnoty FALSE je v tom, ze OVERLOADED OPERATORS is_arithmetic<T>::operator() a is_integral<T>::operator() vracaju BOOL HODNOTY a NIE TYPES [true_type] resp. [false_type].
// !!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat1(int,true,true)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! C. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze su nutne 2 USER DEFINED CONVERSIONS.
// !!!!! D. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! E. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, false_type, TTypes...)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!! F. Kedze z 3 kandidatov vyhovuje IBA FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)], C++ vyberie prave tuto FUNCTION.
// Pre PARAMETER [wstring] sa C++ chova nasledovne.
// !!!!! A. CODE [InternalPrintIntegerOrFloat1(ValueOrPointer,is_arithmetic<wstring>(),is_integral<wstring>())] volany vo FUNCTION PrintIntegerOrFloat1() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat1(wstring,false,false). DOVOD PRECO v 2. a 3. PARAMETRI su hodnoty FALSE je v tom, ze OVERLOADED OPERATORS is_arithmetic<T>::operator() a is_integral<T>::operator() vracaju BOOL HODNOTY a NIE TYPES [true_type] resp. [false_type].
// !!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat1(wstring,false,false)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! C. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA VALUE [false] na TYPE [true_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! D. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [false] na TYPE [true_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! E. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, false_type, TTypes...)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [false] na TYPE [false_type] co C++ PODPORUJE. Pre 3. PARAMETER NIE JE NUTNA ZIADNA KONVERZIA, kedze sa jedna o GENERIC PARAMETER. Tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze su nutne 2 USER DEFINED CONVERSIONS.
// !!! F. Kedze z 3 kandidatov vyhovuje IBA FUNCTION [void InternalPrintIntegerOrFloat1(TType ValueOrPointer, false_type, TTypes...)], C++ vyberie prave tuto FUNCTION.
template<typename TType, typename... TTypes>
void InternalPrintIntegerOrFloat1(TType, false_type, TTypes...)
{
	wprintf_s(L"TYPE is NOT an ARITHMETIC TYPE !\n");
}
//-----------------------------------------------------------------------------
template<typename TType>
void PrintIntegerOrFloat1(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je ARITHMETIC TYPE sa pouziva TYPE TRAIT is_arithmetic<T>().
	// !!! Na detekciu ci TYPE [TType] je INTEGER TYPE sa pouziva TYPE TRAIT is_integral<T>().
	InternalPrintIntegerOrFloat1(ValueOrPointer,is_arithmetic<TType>(),is_integral<TType>());
}
//-----------------------------------------------------------------------------
void TestIsIntegerTrait1(void)
{
	PrintLineSeparator();

	int															Value1=123;
	double														Value2=123.456;
	wstring														Value3=L"Timmy Anderson";

	PrintIntegerOrFloat1(Value1);
	PrintIntegerOrFloat1(Value2);
	PrintIntegerOrFloat1(Value3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat2() ma ako 3. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je INTEGER VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, true_type)
{
	wprintf_s(L"INTEGER VALUE [%d] !\n",ValueOrPointer);
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat2() ma ako 3. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je FLOAT VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, false_type)
{
	wprintf_s(L"FLOAT VALUE [%f] !\n",ValueOrPointer);
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!! Ak TYPE NIE JE ARITHMETIC TYPE, zavola sa tato verzia OVERLOADED FUNCTION.
template<typename... TTypes>
void InternalPrintIntegerOrFloat2(TTypes...)
{
	wprintf_s(L"TYPE is NOT an ARITHMETIC TYPE !\n");
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
// !!!!! Vdaka OVERLOADING RULES tento CODE aj pre INTEGER a FLOAT TYPES ZAVOLA VARIADIC FUNCTION [void InternalPrintIntegerOrFloat2(TTypes...)], co je ERROR. Dovod je nasledujuci.
// !!!!! A. CODE [InternalPrintIntegerOrFloat2(int,is_arithmetic<int>(),is_integral<int>())] volany vo FUNCTION PrintIntegerOrFloat2() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat2(int,true,true). DOVOD PRECO v 2. a 3. PARAMETRI su hodnoty TRUE je v tom, ze OVERLOADED OPERATORS is_arithmetic<T>::operator() a is_integral<T>::operator() vracaju BOOL HODNOTY a NIE TYPES [true_type] resp. [false_type].
// !!!!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat2(int,true,true)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! C. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER zisti, ze je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze su nutne 2 USER DEFINED CONVERSIONS.
// !!!!! D. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat2(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 2. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [true_type] co C++ PODPORUJE. Pre 3. PARAMETER je NUTNA KONVERZIA z VALUE [true] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! E. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat2(TTypes...)]. Pre tuto FUNCTION zisti, ze NIE SU POTREBNE ZIADNE CONVERSIONS, pretoze FUNCTION je VARIADIC FUNCTION, ktora moze mat LUBOVLNY POCET TYPE PARAMETERS. C++ zaradi FUNCTION ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze NIE SU NUTNE ZIADNE USER DEFINED CONVERSIONS.
// !!!!! F. Nasledne C++ porovna vsetky VYHOVUJUCU 1. a 3. FUNCTIONS. Kedze 3. FUNCTION NEVYZADUJE ZIADNE USER DEFINED CONVERSIONS, zatial do 1. FUNCTION VYZADUJE 2 USER DEFINED CONVERSIONS, vyberie 3. FUNCTION [void InternalPrintIntegerOrFloat2(TTypes...)].
// !!!!! G. Vysledkom je NESPRAVNA DETEKCIA, kde aj INTEGER a FLOAT TYPES su oznacene ako TYPES, ktore NIE SU ARITHMETIC TYPES. Cely PROBLEM spociva v tom, ze OPERATOR() pre TYPE [is_arithmetic<T>] a TYPE [is_integral<T>] vracia TYPE [bool], ktory je NUTNE KONVERTOVAT na OCAKAVANE TYPES [true_type] a [false_type].
template<typename TType>
void PrintIntegerOrFloat2(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je ARITHMETIC TYPE sa pouziva TYPE TRAIT is_arithmetic<T>().
	// !!! Na detekciu ci TYPE [TType] je INTEGER TYPE sa pouziva TYPE TRAIT is_integral<T>().
	// !!!!! Vola sa OPERATOR() a NIE FIELD [type].
	InternalPrintIntegerOrFloat2(ValueOrPointer,is_arithmetic<TType>(),is_integral<TType>());
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE UMYSELNE DEMONSTRUJE ERROR.
void TestIsIntegerTrait2(void)
{
	PrintLineSeparator();

	int															Value1=123;
	double														Value2=123.456;
	wstring														Value3=L"Timmy Anderson";

	// !!!!! CODE CHYBNE vypise, ze ZIADEN z TYPES NIE JE ARITHMETIC TYPE co je NEZMYSEL.
	PrintIntegerOrFloat2(Value1);
	PrintIntegerOrFloat2(Value2);
	PrintIntegerOrFloat2(Value3);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION InternalPrintIntegerOrFloat3().
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat3() ma ako 3. PARAMETER TYPE [true_type], predpoklada sa, ze VALUE je INTEGER VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, true_type)
{
	wprintf_s(L"INTEGER VALUE [%d] !\n",ValueOrPointer);
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION InternalPrintIntegerOrFloat3().
// !!! Ak OVERLOADED verzia FUNCTION InternalPrintIntegerOrFloat3() ma ako 3. PARAMETER TYPE [false_type], predpoklada sa, ze VALUE je FLOAT VALUE. 2. PARAMETER urcuje ci je TYPE ARITHMETIC TYPE.
template<typename TType>
void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, false_type)
{
	wprintf_s(L"FLOAT VALUE [%f] !\n",ValueOrPointer);
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION InternalPrintIntegerOrFloat3().
// !!! Ak TYPE NIE JE ARITHMETIC TYPE, zavola sa tato verzia OVERLOADED FUNCTION.
template<typename... TTypes>
void InternalPrintIntegerOrFloat3(TTypes...)
{
	wprintf_s(L"TYPE is NOT an ARITHMETIC TYPE !\n");
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION PrintIntegerOrFloat3().
// !!!!! A. CODE [InternalPrintIntegerOrFloat3(int,is_arithmetic<int>::type(),is_integral<int>::type())] volany vo FUNCTION PrintIntegerOrFloat3() C++ substituuje ako volanie FUNCTION InternalPrintIntegerOrFloat3(int,true_type,true_type).
// !!!!! B. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat3(int,true_type,true_type)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!! C. C++ vykona pokus pre CODE [FUNCTION InternalPrintIntegerOrFloat3(int,true_type,true_type)] najst NAJVHODNEJSIU OVERLOADED FUNCTION.
// !!!!! D. Ako 1. vyskusa FUNCTION [void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, true_type)]. Pre tuto FUNCTION zisti, ze NIE SU POTREBNE ZIADNE KONVERZIE a preto tuto FUNCTION C++ zaradi ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze ZIADNE CONVERSIONS NIE SU NUTNE.
// !!!!! E. Ako 2. vyskusa FUNCTION [void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, false_type)]. Pre tuto FUNCTION zisti, ze pre 3. PARAMETER je NUTNA KONVERZIA z TYPE [true_type] na TYPE [false_type] co C++ NEPODPORUJE. Kedze C++ tuto CONVERSION NEPODPORUJE, C++ VYRADI tuto FUNCTION zo zoznamu kandidatov na volanie.
// !!!!! F. Ako 3. vyskusa FUNCTION [void InternalPrintIntegerOrFloat3(TTypes...)]. Pre tuto FUNCTION zisti, ze NIE SU POTREBNE ZIADNE CONVERSIONS, pretoze FUNCTION je VARIADIC FUNCTION, ktora moze mat LUBOVLNY POCET TYPE PARAMETERS. C++ zaradi FUNCTION ako POTENCIALNEHO KANDIDATA na POUZITIE, pricom si poznaci, ze NIE SU NUTNE ZIADNE USER DEFINED CONVERSIONS.
// !!!!! G. Nasledne C++ porovna 1. a 3. FUNCTIONS, ktore ako JEDINE VYHOVUJU. Kedze ANI JEDNA FUNCTIONS NEVYZADUJE USER DEFINED CONVERSIONS, su v tomto kriteriu ROVNOCENNE. C++ v takom pripade PREFERUJE NON-VARIADIC FUNCTION PRED VARIADIC FUNCTION a preto vyberie 1. FUNCTION [void InternalPrintIntegerOrFloat3(TType ValueOrPointer, true_type, true_type)].
// !!!!! H. Vysledkom je SPRAVNA DETEKCIA TYPE.
template<typename TType>
void PrintIntegerOrFloat3(TType ValueOrPointer)
{
	// !!! Na detekciu ci TYPE [TType] je ARITHMETIC TYPE sa pouziva TYPE TRAIT is_arithmetic<T>().
	// !!! Na detekciu ci TYPE [TType] je INTEGER TYPE sa pouziva TYPE TRAIT is_integral<T>().
	// !!!!! ZASADNYM ROZDIELOM oproti FUNCTION PrintIntegerOrFloat3() je vytvorenie INSTANCII TYPE [is_arithmetic<TType>::type] a [is_integral<TType>::type] NAMIESTO POUZITIA OPERATOR(). DOVODOM PRECO tento variant FUNGUJE je v tom, ze [is_arithmetic<TType>::type] a [is_integral<TType>::type] su vo vysledku bud [true_type], alebo [false_type] co umoznuje EXACT TYPE MATCH voci TYPES pozadovanym InternalPrintIntegerOrFloat3(). OPERATOR() naopak vracia TYPE [bool], kde su na TYPES [true_type] a [false_type] co ZNEVYHODNUJE NON-VARIADIC FUNCTIONS oproti VARIADIC-FUNCTION.
	// !!! ZATVORKY za '::type' znamenaju VYTVORENIE INSTANCIE daneho TYPE.
	InternalPrintIntegerOrFloat3(ValueOrPointer,typename is_arithmetic<TType>::type(),typename is_integral<TType>::type());
}
//-----------------------------------------------------------------------------
// !!!!! TENTO CODE je KOREKTNOU ALTERNATIVOU voci CODE vo FUNCTION TestIsIntegerTrait2().
void TestIsIntegerTrait3(void)
{
	PrintLineSeparator();

	int															Value1=123;
	double														Value2=123.456;
	wstring														Value3=L"Timmy Anderson";

	// !!!!! CODE FNGUJE KOREKTNE.
	PrintIntegerOrFloat3(Value1);
	PrintIntegerOrFloat3(Value2);
	PrintIntegerOrFloat3(Value3);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits1(void)
{
	PrintLineSeparator();

	wprintf_s(L"IS_CLASS<int> [%d] !\n",is_class<int>::value);
	wprintf_s(L"IS_CLASS<wstring> [%d] !\n",is_class<wstring>::value);
	wprintf_s(L"IS_CLASS<CType1> [%d] !\n",is_class<CType1>::value);
	wprintf_s(L"IS_ABSTRACT<int> [%d] !\n",is_abstract<int>::value);
	wprintf_s(L"IS_ABSTRACT<wstring> [%d] !\n",is_abstract<wstring>::value);
	wprintf_s(L"IS_ABSTRACT<CType1> [%d] !\n",is_abstract<CType1>::value);
	wprintf_s(L"IS_TRIVIALLY_DESTRUCTIBLE<CType1> [%d] !\n",is_trivially_destructible<CType1>::value);
	wprintf_s(L"IS_TRIVIALLY_DESTRUCTIBLE<CType2> [%d] !\n",is_trivially_destructible<CType2>::value);
	wprintf_s(L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType1> [%d] !\n",is_trivially_default_constructible<CType1>::value);
	wprintf_s(L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType2> [%d] !\n",is_trivially_default_constructible<CType2>::value);
	wprintf_s(L"IS_FUNCTION<CType2> [%d] !\n",is_function<CType2>::value);
	wprintf_s(L"IS_FUNCTION<decltype(TypeTraits1)> [%d] !\n",is_function<decltype(TestTypeTraits1)>::value);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits2(void)
{
	PrintLineSeparator();

	using														XXX=int;
	typedef int													YYY;

	wprintf_s(L"IS_SAME<int,int> [%d] !\n",is_same<int,int>::value);
	// Vrati FALSE.
	wprintf_s(L"IS_SAME<int,const int> [%d] !\n",is_same<int,const int>::value);
	wprintf_s(L"IS_SAME<int,double> [%d] !\n",is_same<int,double>::value);
	wprintf_s(L"IS_SAME<int,XXX> [%d] !\n",is_same<int,XXX>::value);
	wprintf_s(L"IS_SAME<int,YYY> [%d] !\n",is_same<int,YYY>::value);
	// Vrati TRUE.
	wprintf_s(L"IS_BASE_OF<CBase,CDerivedPublic> [%d] !\n",is_base_of<CBase,CDerivedPublic>::value);
	// !!! Vrati TRUE.
	wprintf_s(L"IS_BASE_OF<CBase,CDerivedProtected> [%d] !\n",is_base_of<CBase,CDerivedProtected>::value);
	// !!! Vrati TRUE.
	wprintf_s(L"IS_BASE_OF<CBase,CDerivedPrivate> [%d] !\n",is_base_of<CBase,CDerivedPrivate>::value);
	// Vrati TRUE.
	wprintf_s(L"IS_CONVERTIBLE<CDerivedPublic,CBase> [%d] !\n",is_convertible<CDerivedPublic,CBase>::value);
	// !!! Vrati TRUE.
	wprintf_s(L"IS_CONVERTIBLE<CDerivedProtected,CBase> [%d] !\n",is_convertible<CDerivedProtected,CBase>::value);
	// !!! Vrati TRUE.
	wprintf_s(L"IS_CONVERTIBLE<CDerivedPrivate,CBase> [%d] !\n",is_convertible<CDerivedPrivate,CBase>::value);
	// Vrati TRUE, lebo CLASS 'CClassWithCustomOperators' MA CONSTRUCTOR s PARAMETER TYPU [int].
	wprintf_s(L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,int> [%d] !\n",is_constructible<CClassWithCustomOperators,int>::value);
	// Vrati TRUE, lebo CLASS 'CClassWithCustomOperators' MA CONSTRUCTOR s PARAMETER TYPU [int] a TYPE [double] je na TYPE KONVERTOVATELNY.
	wprintf_s(L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,double> [%d] !\n",is_constructible<CClassWithCustomOperators,double>::value);
	// Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' NEMA CONSTRUCTOR s PARAMETER TYPU [wstring] a ani NEEXISTUJE CONVERSION s TYPE [wstring] na TYPE [int].
	wprintf_s(L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,wstring> [%d] !\n",is_constructible<CClassWithCustomOperators,wstring>::value);
	// Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' NEMA DEFAULT CONSTRUCTOR.
	wprintf_s(L"IS_CONSTRUCTIBLE<CClassWithCustomOperators> [%d] !\n",is_constructible<CClassWithCustomOperators>::value);
	// Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' NEMA CONSTRUCTOR s 2 PARAMETERS.
	wprintf_s(L"IS_CONSTRUCTIBLE<CClassWithCustomOperators,int,int> [%d] !\n",is_constructible<CClassWithCustomOperators,int,int>::value);
	// !!! Vrati FALSE, lebo CLASS 'CClassWithCustomOperators' MA CONSTRUCTOR s PARAMETER TYPU [int] a TYPE [double] je na TYPE KONVERTOVATELNY, tak konverzia NIE JE POVAZOVANA za TRIVIALNU OPERACIU.
	wprintf_s(L"IS_TRIVIALLY_CONSTRUCTIBLE<CClassWithCustomOperators,double> [%d] !\n",is_trivially_constructible<CClassWithCustomOperators,double>::value);
	// !!! Vrati TRUE, lebo aj ked CLASS 'CClassWithCustomOperators' NEMA OPERATOR=(int), tak ma NON-EXPLICIT CONSTRUCTOR s 1 PARAMETROM TYPU [int] a ten je na priradenie mozne vyuzit. Ak by vsak CONSTRUCTOR oznaceny ako EXPLICIT, vysledkom by bola VALUE FALSE.
	wprintf_s(L"IS_ASSIGNABLE<CClassWithCustomOperators,int> [%d] !\n",is_assignable<CClassWithCustomOperators,int>::value);
	// !!! Vrati TRUE, lebo aj ked CLASS 'CClassWithCustomOperators' NEMA OPERATOR=(double), tak ma NON-EXPLICIT CONSTRUCTOR s 1 PARAMETROM TYPU [int] a ten je po konverzii z TYPE [double] na priradenie mozne vyuzit. Ak by vsak CONSTRUCTOR oznaceny ako EXPLICIT, vysledkom by bola VALUE FALSE.
	wprintf_s(L"IS_ASSIGNABLE<CClassWithCustomOperators,double> [%d] !\n",is_assignable<CClassWithCustomOperators,double>::value);

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits3(void)
{
	PrintLineSeparator();
	
	wstring_convert<codecvt_utf8<wchar_t>>						Coverter;

	wcout << L"REMOVE_CONST<int> [" << Coverter.from_bytes(typeid(remove_const<int>::type).name()) << L"] !\n";
	wcout << L"REMOVE_CONST<const int> [" << Coverter.from_bytes(typeid(remove_const<const int>::type).name()) << L"] !\n";
	// OPERATOR TYPEID() NEVYPISUJE 'CONST' MODIFIERS.
	wcout << L"ADD_CONST<int> [" << Coverter.from_bytes(typeid(add_const<int>::type).name()) << L"] !\n";
	wcout << L"MAKE_SIGNED<int> [" << Coverter.from_bytes(typeid(make_signed<int>::type).name()) << L"] !\n";
	wcout << L"MAKE_UNSIGNED<int> [" << Coverter.from_bytes(typeid(make_unsigned<int>::type).name()) << L"] !\n";
	wcout << L"MAKE_SIGNED<unsigned int> [" << Coverter.from_bytes(typeid(make_signed<unsigned int>::type).name()) << L"] !\n";
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"REMOVE_REFERENCE<int&> [" << Coverter.from_bytes(typeid(remove_reference<int&>::type).name()) << L"] !\n";
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"REMOVE_REFERENCE<int&&> [" << Coverter.from_bytes(typeid(remove_reference<int&&>::type).name()) << L"] !\n";
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"REMOVE_REFERENCE<int> [" << Coverter.from_bytes(typeid(remove_reference<int>::type).name()) << L"] !\n";
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"ADD_LVALUE_REFERENCE<int> [" << Coverter.from_bytes(typeid(add_lvalue_reference<int>::type).name()) << L"] !\n";
	// OPERATOR TYPEID() NEVYPISUJE REFERENCE MODIFIERS.
	wcout << L"ADD_RVALUE_REFERENCE<int> [" << Coverter.from_bytes(typeid(add_rvalue_reference<int>::type).name()) << L"] !\n";
	wcout << L"ADD_POINTER<int> [" << Coverter.from_bytes(typeid(add_pointer<int>::type).name()) << L"] !\n";
	wcout << L"ADD_POINTER<int*> [" << Coverter.from_bytes(typeid(add_pointer<int*>::type).name()) << L"] !\n";
	wcout << L"REMOVE_POINTER<int*> [" << Coverter.from_bytes(typeid(remove_pointer<int*>::type).name()) << L"] !\n";

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits4(void)
{
	PrintLineSeparator();

	wcout << L"RANK<int> [" << rank<int>::value << L"] !\n";
	wcout << L"RANK<int[]> [" << rank<int[]>::value << L"] !\n";
	wcout << L"RANK<int[5][5][5]> [" << rank<int[5][5][5]>::value << L"] !\n";
	wcout << L"RANK<int[2][3][5][2]> [" << rank<int[2][3][5][2]>::value << L"] !\n";
	wcout << L"EXTENT<int> [" << extent<int>::value << L"] !\n";
	wcout << L"EXTENT<int[]> [" << extent<int[]>::value << L"] !\n";
	wcout << L"EXTENT<int[5][4][3][2]> [" << extent<int[5][4][3][2]>::value << L"] !\n";
	wcout << L"EXTENT<int[15][14][13][12],2> [" << extent<int[15][14][13][12],2>::value << L"] !\n";
	wcout << L"EXTENT<int[15][14][13][12],7> [" << extent<int[15][14][13][12],7>::value << L"] !\n";
	wcout << L"REMOVE_EXTENT<int> [" << typeid(remove_extent<int>::type).name() << L"] !\n";
	wcout << L"REMOVE_EXTENT<int[10][20]> [" << typeid(remove_extent<int[10][20]>::type).name() << L"] !\n";
	wcout << L"REMOVE_ALL_EXTENTS<int> [" << typeid(remove_all_extents<int>::type).name() << L"] !\n";
	wcout << L"REMOVE_ALL_EXTENTS<int[10][20]> [" << typeid(remove_all_extents<int[10][20]>::type).name() << L"] !\n";
	wcout << L"UNDERLYING_TYPE<ESimpleEnum1> [" << typeid(underlying_type<ESimpleEnum1>::type).name() << L"] !\n";
	wcout << L"UNDERLYING_TYPE<ESimpleEnum2> [" << typeid(underlying_type<ESimpleEnum2>::type).name() << L"] !\n";
	wcout << L"UNDERLYING_TYPE<EClassEnum1> [" << typeid(underlying_type<EClassEnum1>::type).name() << L"] !\n";
	wcout << L"UNDERLYING_TYPE<EClassEnum2> [" << typeid(underlying_type<EClassEnum2>::type).name() << L"] !\n";

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void MyFunction(void)
{
}
//-------------------------------------------------------------------------------------------------------
int MyFunction(int)
{
	return(0);
}
//-------------------------------------------------------------------------------------------------------
float MyFunction(double,int)
{
	return(float());
}
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits5(void)
{
	PrintLineSeparator();

	wcout << L"DECAY<int> [" << typeid(decay<int>::type).name() << L"] !\n";
	wcout << L"DECAY<int&> [" << typeid(decay<int&>::type).name() << L"] !\n";
	wcout << L"DECAY<int&&> [" << typeid(decay<int&&>::type).name() << L"] !\n";
	wcout << L"DECAY<int*> [" << typeid(decay<int*>::type).name() << L"] !\n";
	wcout << L"DECAY<int**> [" << typeid(decay<int**>::type).name() << L"] !\n";
	wcout << L"DECAY<int[10]> [" << typeid(decay<int[10]>::type).name() << L"] !\n";
	wcout << L"DECAY<int[10][20]> [" << typeid(decay<int[10][20]>::type).name() << L"] !\n";
	wcout << L"DECAY<int (*)(int,double)> [" << typeid(decay<int (*)(int,double)>::type).name() << L"] !\n";
	wcout << L"DECAY<const volatile int> [" << typeid(decay<const volatile int>::type).name() << L"] !\n";
	wcout << L"DECAY<const volatile unsigned int> [" << typeid(decay<const volatile unsigned int>::type).name() << L"] !\n";
	wcout << L"ENABLE_IF<true,int> [" << typeid(enable_if<true,int>::type).name() << L"] !\n";
	// !!! Ak je PODMIENKA FALSE, potom ALIAS 'type' NIE JE DEFINOVANY a COMPILER hodi ERROR.
	//wcout << L"ENABLE_IF<false,int> [" << typeid(enable_if<false,int>::type).name() << L"] !\n";
	wcout << L"CONDITIONAL<true,int,double> [" << typeid(conditional<true,int,double>::type).name() << L"] !\n";
	wcout << L"CONDITIONAL<false,int,double> [" << typeid(conditional<false,int,double>::type).name() << L"] !\n";
	wcout << L"COMMON_TYPE<int,double,bool> [" << typeid(common_type<int,double,bool>::type).name() << L"] !\n";
	// !!! Vracia COMPILATION ERROR, pretoze medzi TYPES NEEXISTUJE TYPE, na ktory by vsetky ostatne TYPES bolo mozne konvertovat.
	//wcout << L"COMMON_TYPE<int,double,bool,CType1> [" << typeid(common_type<int,double,bool,CType1>::type).name() << L"] !\n";
	// !!! Vracia COMPILATION ERROR, pretoze medzi TYPES NEEXISTUJE TYPE, na ktory by vsetky ostatne TYPES bolo mozne konvertovat.
	//wcout << L"COMMON_TYPE<ESimpleEnum1,ESimpleEnum2,EClassEnum1,EClassEnum2> [" << typeid(common_type<ESimpleEnum1,ESimpleEnum2,EClassEnum1,EClassEnum2>::type).name() << L"] !\n";
	wcout << L"COMMON_TYPE<ESimpleEnum1,ESimpleEnum2> [" << typeid(common_type<ESimpleEnum1,ESimpleEnum2>::type).name() << L"] !\n";

	PrintLineSeparator();

	using														Refrence1=void(&)(void);
	using														Pointer1=void(*)(void);
	using														Refrence2=int(&)(int);
	using														Pointer2=int(*)(int);
	using														Refrence3=float(&)(double,int);
	using														Pointer3=float(*)(double,int);
	using														Pointer4=int(CTypeWithOperatorsAndMethods::*)(int,float);

	wstring_convert<codecvt_utf8<wchar_t>>						Coverter;

	wcout << L"RESULT_OF<Refrence1()> [" << typeid(result_of<Refrence1()>::type).name() << L"] !\n";
	wcout << L"RESULT_OF<Pointer1()> [" << typeid(result_of<Pointer1()>::type).name() << L"] !\n";
	wcout << L"RESULT_OF<Refrence2(int)> [" << typeid(result_of<Refrence2(int)>::type).name() << L"] !\n";
	wcout << L"RESULT_OF<Pointer2(int)> [" << typeid(result_of<Pointer2(int)>::type).name() << L"] !\n";
	wcout << L"RESULT_OF<Refrence3(double,int)> [" << typeid(result_of<Refrence3(double,int)>::type).name() << L"] !\n";
	wcout << L"RESULT_OF<Pointer3(double,int)> [" << typeid(result_of<Pointer3(double,int)>::type).name() << L"] !\n";
	wcout << L"RESULT_OF<Pointer4(double,int)> [" << Coverter.from_bytes(typeid(result_of<Pointer4(CTypeWithOperatorsAndMethods*,int,float)>::type).name()) << L"] !\n";

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits6(void)
{
	PrintLineSeparator();

	// Pouzitie C++ OPERATOR.
	wcout << L"ALIGNOF<SFields> [" << alignof(SFields) << L"] !\n";
	wcout << L"ALIGNMENT_OF<SFields> [" << alignment_of<SFields>::value << L"] !\n";
	wcout << L"ALIGNMENT_OF<char> [" << alignment_of<char>::value << L"] !\n";
	wcout << L"ALIGNMENT_OF<short> [" << alignment_of<short>::value << L"] !\n";
	wcout << L"ALIGNMENT_OF<long double> [" << alignment_of<long double>::value << L"] !\n";
	wcout << L"ALIGNMENT_OF<CType1*> [" << alignment_of<CType1*>::value << L"] !\n";
	wcout << L"ALIGNED_STORAGE<1> [" << typeid(aligned_storage<1>::type).name() << L"] !\n";
	wcout << L"ALIGNED_STORAGE<4> [" << typeid(aligned_storage<4>::type).name() << L"] !\n";
	wcout << L"ALIGNED_STORAGE<8> [" << typeid(aligned_storage<8>::type).name() << L"] !\n";
	wcout << L"ALIGNED_STORAGE<32> [" << typeid(aligned_storage<32>::type).name() << L"] !\n";
	wcout << L"ALIGNED_STORAGE<100> [" << typeid(aligned_storage<100>::type).name() << L"] !\n";
	wcout << L"ALIGNED_STORAGE<4,2> [" << typeid(aligned_storage<4,2>::type).name() << L"] !\n";
	wcout << L"ALIGNED_STORAGE<8,2> [" << typeid(aligned_storage<8,2>::type).name() << L"] !\n";
	wcout << L"ALIGNED_STORAGE<32,4> [" << typeid(aligned_storage<32,4>::type).name() << L"] !\n";
	wcout << L"ALIGNED_UNION<5,int,int,double> [" << typeid(aligned_union<5,int,int,double>::type).name() << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeTraitsTypeAccess(void)
{
	PrintLineSeparator();

	// !!! TYPE TRAIT [is_copy_constructible<T>] vrati FALSE, pretoze tento TYPE TRAIT (ako aj viacere ine) NEROBI ACCESS CHECKING a detekciu ci ma TYPE COPY CONSTRUCTOR robi ako keby bol volany z NON-MEMBER FUNCTION.
	wcout << "FROM FUNCTION - IS COPY CONSTRUCTIBLE [" << is_copy_constructible<CPrivateCopyConstructor>::value << "] !\n";

	CPrivateCopyConstructor										Object;

	// !!! Aj ked sa TYPE TRAIT [is_copy_constructible<T>] vola z METHOD, tak vrati FALSE, pretoze TYPE TRAIT [is_copy_constructible<T>] ako aj mnoho inych NEROBI ACCESS CHECK a kontrolu ci TYPE ma COPY CONSTRUCTOR VZDY robi ako keby bol volany z NON-MEMBER FUNCTION.
	wcout << "FROM METHOD - IS COPY CONSTRUCTIBLE [" << Object.IsCopyConstructible() << "] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void RemoveReference(TType Value)
{
	// Ak je 'TType' REFERENCE, tak sa vyrobi COPY z 'Value'.
	typename remove_reference<TType>::type						Copy=Value;
	// Ak je 'TType' REFERENCE, tak sa vyrobi REFERENCE na 'Value'.
	TType														CopyOrReference=Value;

	Copy++;

	CopyOrReference++;

	wcout << L"COPY [" << Copy << L"] !\n";
	wcout << L"COPY OR REFERENCE [" << CopyOrReference << L"] !\n";
	wcout << L"VALUE [" << Value << L"] !\n";
}
//-----------------------------------------------------------------------------
void TestTypeTraitsRemoveReference(void)
{
	PrintLineSeparator();

	int															Value1=100;

	wcout << L"MAIN BEFORE - VALUE 1 [" << Value1 << L"] !\n";

	// Prenasa sa BY-VALUE.
	RemoveReference(Value1);

	wcout << L"MAIN AFTER - VALUE 1 [" << Value1 << L"] !\n";

	PrintLineSeparator();

	int															Value2=100;

	wcout << L"MAIN BEFORE - VALUE 2 [" << Value2 << L"] !\n";

	// Prenasa sa BY-REFERENCE.
	RemoveReference<int&>(Value2);

	wcout << L"MAIN AFTER - VALUE 2 [" << Value2 << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMove(void)
{
	PrintLineSeparator();

	CTypeWithMoveConstructor									Value1(L"HELLO");

	wcout << L"VALUE 1 [" << Value1.GetValue() << L"] !\n";

	// !!! Pri move() sa zlikviduje obsah 'Value1'.
	// Pouziva sa MOVE CONSTRUCTOR.
	CTypeWithMoveConstructor									MovedValue1=move(Value1);

	wcout << L"VALUE 1 [" << Value1.GetValue() << L"] !\n";
	wcout << L"MOVED VALUE 1 [" << MovedValue1.GetValue() << L"] !\n";

	/*
	PrintLineSeparator();

	CTypeWithMoveOperator										Value(L"HELLO");

	wcout << L"VALUE [" << Value.GetValue() << L"] !\n";

	// !!!!! Hodi COMPILATION ERROR, pretoze CLASS 'CTypeWithMoveOperator' NEMA definovany MOVE CONSTRUCTOR.
	CTypeWithMoveOperator										MovedValue=move(Value);

	wcout << L"VALUE [" << Value.GetValue() << L"] !\n";
	wcout << L"MOVED VALUE [" << MovedValue.GetValue() << L"] !\n";
	*/

	PrintLineSeparator();

	CTypeWithCopyAndMoveConstructor								Value2(L"HELLO");

	wcout << L"VALUE 2 [" << Value2.GetValue() << L"] !\n";

	// !!! Pri move() sa zlikviduje obsah 'Value2'.
	// Pouziva sa MOVE CONSTRUCTOR.
	CTypeWithCopyAndMoveConstructor								MovedValue2=move(Value2);

	wcout << L"VALUE 2 [" << Value2.GetValue() << L"] !\n";
	wcout << L"MOVED VALUE 2 [" << MovedValue2.GetValue() << L"] !\n";

	PrintLineSeparator();

	CTypeWithMoveConstructor									Value3(L"HELLO");

	wcout << L"VALUE 3 [" << Value3.GetValue() << L"] !\n";

	// !!! Pri move() sa zlikviduje obsah 'Value3'.
	// !!!!! Vykonava MOVE OPERATION, pretoze TYPE NEMA definovany COPY CONSTRUCTOR.
	CTypeWithMoveConstructor									MovedValue3=move_if_noexcept(Value3);

	wcout << L"VALUE 3 [" << Value3.GetValue() << L"] !\n";
	wcout << L"MOVED VALUE 3 [" << MovedValue3.GetValue() << L"] !\n";

	PrintLineSeparator();

	CTypeWithCopyAndMoveConstructor								Value4(L"HELLO");

	wcout << L"VALUE 4 [" << Value4.GetValue() << L"] !\n";

	// !!!!! NEPOUZIJE sa MOVE OPERATION, pretoze TYPE ma definovany MOVE CONSTRUCTOR, ktory NIE je oznaceny ako NOTHROW a ZAROVEN MA definovany COPY CONSTRUCTOR.
	// !!! Pouzije sa COPY CONSTRUCTOR.
	CTypeWithCopyAndMoveConstructor								MovedValue4=move_if_noexcept(Value4);

	wcout << L"VALUE 4 [" << Value4.GetValue() << L"] !\n";
	wcout << L"MOVED VALUE 4 [" << MovedValue4.GetValue() << L"] !\n";

	PrintLineSeparator();

	CTypeWithCopyAndNoExceptMoveConstructor						Value5(L"HELLO");

	wcout << L"VALUE 5 [" << Value5.GetValue() << L"] !\n";

	// !!!!! POUZIJE sa MOVE OPERATION, pretoze TYPE ma definovany MOVE CONSTRUCTOR, ktory je oznaceny ako NOTHROW.
	CTypeWithCopyAndNoExceptMoveConstructor						MovedValue5=move_if_noexcept(Value5);

	wcout << L"VALUE 5 [" << Value5.GetValue() << L"] !\n";
	wcout << L"MOVED VALUE 5 [" << MovedValue5.GetValue() << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestForward(void)
{
	PrintLineSeparator();

	CTypeWithCopyAndMoveConstructor								Value(L"HELLO");

	wcout << L"VALUE [" << Value.GetValue() << L"] !\n";

	// !!! Pri forward() sa zlikviduje obsah 'Value'.
	// Pouziva sa MOVE CONSTRUCTOR.
	CTypeWithCopyAndMoveConstructor								MovedValue1=forward<CTypeWithCopyAndMoveConstructor>(Value);

	wcout << L"VALUE [" << Value.GetValue() << L"] !\n";
	wcout << L"MOVED VALUE 1 [" << MovedValue1.GetValue() << L"] !\n";

	PrintLineSeparator();

	CTypeWithCopyAndMoveConstructor								MovedValue2=forward<CTypeWithCopyAndMoveConstructor>(CTypeWithCopyAndMoveConstructor(L"HELLO"));

	wcout << L"MOVED VALUE 2 [" << MovedValue2.GetValue() << L"] !\n";

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSwap(void)
{
	PrintLineSeparator();

	int															Value1=100;
	int															Value2=200;

	swap(Value1,Value2);

	wcout << L"VALUE 1 [" << Value1 << L"] !\n";
	wcout << L"VALUE 2 [" << Value2 << L"] !\n";

	PrintLineSeparator();

	int															ArrayValue1[5]{1,2,3,4,5};
	int															ArrayValue2[5]{10,20,30,40,50};

	swap(ArrayValue1,ArrayValue2);

	wcout << L"ARRAY VALUE 1:\n";

	for(int Index=0;Index<5;Index++)
	{
		wcout << L"\tINDEX [" << Index << "] - [" << ArrayValue1[Index] << L"] !\n";
	}

	wcout << L"ARRAY VALUE 2:\n";

	for(int Index=0;Index<5;Index++)
	{
		wcout << L"\tINDEX [" << Index << "] - [" << ArrayValue2[Index] << L"] !\n";
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestOperators(void)
{
	PrintLineSeparator();

	using namespace std::rel_ops;

	CInt														Value1(100);
	CInt														Value2(200);

	// !!! Pouzije sa OPERATOR s NAMESPACE [std::rel_ops], ktory pouzije OPERATOR== definovany v CLASS CInt.
	// !!! CLASS [CInt] NEOBSAHUJE deklaracie OPERATOR!=, OPERATOR>, OPERATOR<= a OPERATOR>=.
	wprintf_s(L"VALUE1!=VALUE2 [%ls] !\n",(Value1!=Value2) ? L"TRUE" : L"FALSE");
	wprintf_s(L"VALUE1>VALUE2 [%ls] !\n",(Value1>Value2) ? L"TRUE" : L"FALSE");
	wprintf_s(L"VALUE1<=VALUE2 [%ls] !\n",(Value1<=Value2) ? L"TRUE" : L"FALSE");
	wprintf_s(L"VALUE1>=VALUE2 [%ls] !\n",(Value1>=Value2) ? L"TRUE" : L"FALSE");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTypeIndex(void)
{
	PrintLineSeparator();

	wcout << L"INT HASH [" << typeid(int).hash_code() << L"] !\n";
	wcout << L"INT HASH TYPE INFO [" << type_index(typeid(int)).hash_code() << L"] !\n";
	wcout << L"INT==INT [" << ((type_index(typeid(int))==type_index(typeid(int))) ? "TRUE" : "FALSE") << L"] !\n";
	wcout << L"INT<DOUBLE [" << ((type_index(typeid(int))<type_index(typeid(double))) ? "TRUE" : "FALSE") << L"] !\n";
	wcout << L"INT>DOUBLE [" << ((type_index(typeid(int))>type_index(typeid(double))) ? "TRUE" : "FALSE") << L"] !\n";

	PrintLineSeparator();

	// !!! CLASS [type_info] je mozne pouzit ako KEY v MAP.
    map<type_index,string>										Map;
 
    Map[type_index(typeid(int))]=typeid(int).name();
    Map[type_index(typeid(double))]=typeid(double).name();
    Map[type_index(typeid(CInt))]=typeid(CInt).name();
    Map[type_index(typeid(string))]=typeid(string).name();

	for(const map<type_index,string>::value_type& Value : Map)
	{
		wcout << L"HASH [" << Value.first.hash_code()  << "] VALUE [" << Map[Value.first].c_str() << L"] !\n";
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestDurationDefinitions();
	//TestDurationArithmeticOperations();
	//TestDurationComparisonOperators();
	//TestDurationConversions();
	//TestTimePoints();
	//TestSystemClock();
	//TestHighResolutionClock();
	//TestSteadyClock();
	//TestTimeTraits();
	//TestRatios();
	//TestIsPointerTrait();
	//TestIsIntegerTrait1();
	//TestIsIntegerTrait2();
	//TestIsIntegerTrait3();
	//TestTypeTraits1();
	//TestTypeTraits2();
	//TestTypeTraits3();
	//TestTypeTraits4();
	//TestTypeTraits5();
	//TestTypeTraits6();
	//TestTypeTraitsTypeAccess();
	//TestTypeTraitsRemoveReference();
	//TestMove();
	//TestForward();
	//TestSwap();
	//TestOperators();
	TestTypeIndex();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------