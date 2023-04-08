//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <chrono>
#include <string>
#include <thread>
#include <sstream>
#include "MyDebug.h"
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
	wcout << Prefix << L" [" << Duration.count() << L"] in [" << TType::period::num << L"/" << TType::period::den << L"] SECOND !" << endl;
}
//-----------------------------------------------------------------------------
void PrintDurationInHHMMSSFFF(wstring Prefix, milliseconds Duration)
{
	hours														Hours=duration_cast<hours>(Duration);
	minutes														Minutes=duration_cast<minutes>(Duration % hours(1));
	seconds														Seconds=duration_cast<seconds>(Duration % minutes(1));
	milliseconds												Milliseconds=duration_cast<milliseconds>(Duration % seconds(1));

	ios_base::iostate											State=wcout.rdstate();

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
	wcout << L"DURATION 1 [" << Duration1.count() << L"] in [" << duration<int>::period::num << L"/" << duration<int>::period::den << L"] SECOND !" << endl;

	// Urcuje DURATION 20 sekund v sekundach.
	duration<int,ratio<1,1>>									Duration2(20);

	wcout << L"DURATION 2 [" << Duration2.count() << L"] in [" << duration<int,ratio<1,1>>::period::num << L"/" << duration<int,ratio<1,1>>::period::den << L"] SECOND !" << endl;

	// Urcuje DURATION 20 sekund v 1/10 sekundy.
	duration<int,ratio<1,10>>									Duration3(200);

	wcout << L"DURATION 3 [" << Duration3.count() << L"] in [" << duration<int,ratio<1,10>>::period::num << L"/" << duration<int,ratio<1,10>>::period::den << L"] SECOND !" << endl;

	// Urcuje DURATION 5 sekund v 50/1000 sekundy.
	duration<int,ratio<50,1000>>								Duration4(100);

	wcout << L"DURATION 4 [" << Duration4.count() << L"] in [" << duration<int,ratio<50,1000>>::period::num << L"/" << duration<int,ratio<50,1000>>::period::den << L"] SECOND !" << endl;

	// Urcuje DURATION 14 sekund v 7/2 sekundy.
	// !!! Ako TYPE sa pouzije DOUBLE.
	duration<double,ratio<7,2>>									Duration5(4);

	wcout << L"DURATION 5 [" << Duration5.count() << L"] in [" << duration<double,ratio<7,2>>::period::num << L"/" << duration<double,ratio<7,2>>::period::den << L"] SECOND !" << endl;

	// Urcuje DURATION 10 sekund v MILISEKUNDACH.
	milliseconds												Duration6(10000);

	wcout << L"DURATION 6 [" << Duration6.count() << L"] in [" << milliseconds::period::num << L"/" << milliseconds::period::den << L"] SECOND !" << endl;

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
	wcout << L"RESULT 5 [" << Duration1/Duration2 << L"] !" << endl;

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
	wcout << L"DURATION_1==DURATION_2 [" << ((Duration1==Duration2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"DURATION_1==DURATION_3 [" << ((Duration1==Duration3) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"DURATION_1==DURATION_4 [" << ((Duration1==Duration4) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati FALSE.
	wcout << L"DURATION_1==DURATION_5 [" << ((Duration1==Duration5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"DURATION_1<DURATION_5 [" << ((Duration1<Duration5) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati FALSE.
	wcout << L"DURATION_1>DURATION_5 [" << ((Duration1>Duration5) ? L"TRUE" : L"FALSE") << L"] !" << endl;

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
void TestSystemClock(void)
{
	PrintLineSeparator();

	wcout << L"IS STEADY [" << system_clock::is_steady << L"] !" << endl;
	wcout << L"DURATION [" << typeid(system_clock::duration).name() << L"] !" << endl;
	wcout << L"TICK TYPE [" << typeid(system_clock::rep).name() << L"] !" << endl;
	wcout << L"TICK PERIOD TYPE [" << typeid(system_clock::period).name() << L"] !" << endl;
	wcout << L"TIME POINT TYPE [" << typeid(system_clock::time_point).name() << L"] !" << endl;

	PrintLineSeparator();

	system_clock::time_point									Now1=system_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !" << endl;

	system_clock::time_point									Now2=system_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !" << endl;

	system_clock::duration										Difference=Now2-Now1;

	PrintDuration(L"DIFFERENCE",Difference);

	PrintLineSeparator();

	system_clock::time_point									Min=system_clock::time_point::min();
	system_clock::time_point									Max=system_clock::time_point::max();

	wcout << L"MIN [" << Min.time_since_epoch().count() << L"] !" << endl;
	wcout << L"MAX [" << Max.time_since_epoch().count() << L"] !" << endl;

	PrintLineSeparator();

	// CLOCK [system_clock] umoznuje konverziu na TYPE [time_t].
	time_t														Time1=system_clock::to_time_t(Now1);
	time_t														Time2=system_clock::to_time_t(Now2);
	string														Time1AsText(asctime(localtime(&Time1)));
	string														Time2AsText(asctime(localtime(&Time2)));

	// Kedze FUNCTION asctime() uplne absurdne pridava na koniec retazca znak '\n', treba ho odstranit.

	Time1AsText.erase(Time1AsText.find('\n'));
	Time2AsText.erase(Time2AsText.find('\n'));

	wcout << L"TIME 1 [" << Time1AsText.c_str() << L"] !" << endl;
	wcout << L"TIME 2 [" << Time2AsText.c_str() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestHighResolutionClock(void)
{
	PrintLineSeparator();

	// !!! Vo WINDOWS 10 bol CLOCK STEADY.
	wcout << L"IS STEADY [" << high_resolution_clock::is_steady << L"] !" << endl;
	wcout << L"DURATION [" << typeid(high_resolution_clock::duration).name() << L"] !" << endl;
	wcout << L"TICK TYPE [" << typeid(high_resolution_clock::rep).name() << L"] !" << endl;
	wcout << L"TICK PERIOD TYPE [" << typeid(high_resolution_clock::period).name() << L"] !" << endl;
	wcout << L"TIME POINT TYPE [" << typeid(high_resolution_clock::time_point).name() << L"] !" << endl;

	PrintLineSeparator();

	high_resolution_clock::time_point									Now1=high_resolution_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !" << endl;

	high_resolution_clock::time_point									Now2=high_resolution_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !" << endl;

	high_resolution_clock::duration										Difference=Now2-Now1;

	PrintDuration(L"DIFFERENCE",Difference);

	PrintLineSeparator();

	high_resolution_clock::time_point									Min=high_resolution_clock::time_point::min();
	high_resolution_clock::time_point									Max=high_resolution_clock::time_point::max();

	wcout << L"MIN [" << Min.time_since_epoch().count() << L"] !" << endl;
	wcout << L"MAX [" << Max.time_since_epoch().count() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSteadyClock(void)
{
	PrintLineSeparator();

	wcout << L"IS STEADY [" << steady_clock::is_steady << L"] !" << endl;
	wcout << L"DURATION [" << typeid(steady_clock::duration).name() << L"] !" << endl;
	wcout << L"TICK TYPE [" << typeid(steady_clock::rep).name() << L"] !" << endl;
	wcout << L"TICK PERIOD TYPE [" << typeid(steady_clock::period).name() << L"] !" << endl;
	wcout << L"TIME POINT TYPE [" << typeid(steady_clock::time_point).name() << L"] !" << endl;

	PrintLineSeparator();

	steady_clock::time_point									Now1=steady_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !" << endl;

	steady_clock::time_point									Now2=steady_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !" << endl;

	steady_clock::duration										Difference=Now2-Now1;

	PrintDuration(L"DIFFERENCE",Difference);
	 
	PrintLineSeparator();

	steady_clock::time_point									Min=steady_clock::time_point::min();
	steady_clock::time_point									Max=steady_clock::time_point::max();

	wcout << L"MIN [" << Min.time_since_epoch().count() << L"] !" << endl;
	wcout << L"MAX [" << Max.time_since_epoch().count() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTimePoints(void)
{
	PrintLineSeparator();

	system_clock::time_point									Now1=system_clock::now();

	wcout << L"NOW 1 [" << Now1.time_since_epoch().count() << L"] !" << endl;

	system_clock::time_point									Now2=system_clock::now();

	wcout << L"NOW 2 [" << Now2.time_since_epoch().count() << L"] !" << endl;

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
	wcout << L"TIME_POINT_1==TIME_POINT_2 [" << ((TimePoint1==TimePoint2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"TIME_POINT_1!=TIME_POINT_2 [" << ((TimePoint1!=TimePoint2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"TIME_POINT_1<TIME_POINT_2 [" << ((TimePoint1<TimePoint2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati TRUE.
	wcout << L"TIME_POINT_1<=TIME_POINT_2 [" << ((TimePoint1<=TimePoint2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati FALSE.
	wcout << L"TIME_POINT_1>TIME_POINT_2 [" << ((TimePoint1>TimePoint2) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	// Vrati FALSE.
	wcout << L"TIME_POINT_1>=TIME_POINT_2 [" << ((TimePoint1>=TimePoint2) ? L"TRUE" : L"FALSE") << L"] !" << endl;

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
void TestStandardCTimeLibrary(void)
{
	PrintLineSeparator();

	clock_t														CurrentClock1=clock();

	// !!! Ako EPOCH je pouzity START PROGRAMU.
	wcout << L"CURRENT CLOCK 1 [" << CurrentClock1 << L"] !" << endl;

	clock_t														CurrentClock2=clock();

	// !!! Ako EPOCH je pouzity START PROGRAMU.
	wcout << L"CURRENT CLOCK 2 [" << CurrentClock2 << L"] !" << endl;

	wcout << L"CURRENT CLOCK DIFFERENCE [" << (CurrentClock2-CurrentClock1) << L"] !" << endl;

	PrintLineSeparator();

	time_t														CurrentTime1=time(nullptr);

	// !!! Ako EPOCH je pouzity datum 1.1.1970 00:00:00.
	wcout << L"CURRENT TIME 1 [" << CurrentTime1 << L"] !" << endl;

	time_t														CurrentTime2=time(nullptr);

	// !!! Ako EPOCH je pouzity datum 1.1.1970 00:00:00.
	wcout << L"CURRENT TIME 2 [" << CurrentTime2 << L"] !" << endl;

	// Vracia rozdiel v SEKUNDACH.
	wcout << L"CURRENT TIME DIFFERENCE [" << difftime(CurrentTime1,CurrentTime2) << L"] !" << endl;

	PrintLineSeparator();

	time_t														CurrentTime=time(nullptr);

	wcout << L"CURRENT TIME [" << CurrentTime << L"] !" << endl;

	tm															LocalTime=*localtime(&CurrentTime);
	tm															GMTime=*gmtime(&CurrentTime);

	wstringstream												Stream1;

	Stream1.fill(L'0');
	Stream1 << L"LOCAL TIME [";
	Stream1.width(2);
	Stream1 << LocalTime.tm_hour;
	Stream1 << L":";
	Stream1.width(2);
	Stream1 << LocalTime.tm_min;
	Stream1 << L":";
	Stream1.width(2);
	Stream1 << LocalTime.tm_sec;
	Stream1 << L" ";
	Stream1.width(2);
	Stream1 << LocalTime.tm_mday;
	Stream1 << L"-";
	Stream1.width(2);
	Stream1 << (LocalTime.tm_mon+1);
	Stream1 << L"-";
	Stream1.width(4);
	Stream1 << (LocalTime.tm_year+1900);
	Stream1 << L"] !";

	wcout << Stream1.str() << endl;

	wstringstream												Stream2;

	Stream2.fill(L'0');
	Stream2 << L"GM TIME [";
	Stream2.width(2);
	Stream2 << GMTime.tm_hour;
	Stream2 << L":";
	Stream2.width(2);
	Stream2 << GMTime.tm_min;
	Stream2 << L":";
	Stream2.width(2);
	Stream2 << GMTime.tm_sec;
	Stream2 << L" ";
	Stream2.width(2);
	Stream2 << GMTime.tm_mday;
	Stream2 << L"-";
	Stream2.width(2);
	Stream2 << (GMTime.tm_mon+1);
	Stream2 << L"-";
	Stream2.width(4);
	Stream2 << (GMTime.tm_year+1900);
	Stream2 << L"] !";

	wcout << Stream2.str() << endl;

	char														Buffer[100];

	strftime(Buffer,sizeof(Buffer),"%H:%M:%S %d-%m-%Y",&LocalTime);

	wcout << L"LOCAL TIME [" << Buffer << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestThreadSleep(void)
{
	PrintLineSeparator();

	time_t														CurrentTime1=time(nullptr);
	tm															LocalTime1=*localtime(&CurrentTime1);

	wstringstream												Stream1;

	Stream1.fill(L'0');
	Stream1 << L"LOCAL TIME [";
	Stream1.width(2);
	Stream1 << LocalTime1.tm_hour;
	Stream1 << L":";
	Stream1.width(2);
	Stream1 << LocalTime1.tm_min;
	Stream1 << L":";
	Stream1.width(2);
	Stream1 << LocalTime1.tm_sec;
	Stream1 << L" ";
	Stream1.width(2);
	Stream1 << LocalTime1.tm_mday;
	Stream1 << L"-";
	Stream1.width(2);
	Stream1 << (LocalTime1.tm_mon+1);
	Stream1 << L"-";
	Stream1.width(4);
	Stream1 << (LocalTime1.tm_year+1900);
	Stream1 << L"] !";

	wcout << Stream1.str() << endl;

	// !!! NAMESPACE [this_thread] definuje FUNCTION sleep_for().
	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	time_t														CurrentTime2=time(nullptr);
	tm															LocalTime2=*localtime(&CurrentTime2);

	wstringstream												Stream2;

	Stream2.fill(L'0');
	Stream2 << L"LOCAL TIME [";
	Stream2.width(2);
	Stream2 << LocalTime2.tm_hour;
	Stream2 << L":";
	Stream2.width(2);
	Stream2 << LocalTime2.tm_min;
	Stream2 << L":";
	Stream2.width(2);
	Stream2 << LocalTime2.tm_sec;
	Stream2 << L" ";
	Stream2.width(2);
	Stream2 << LocalTime2.tm_mday;
	Stream2 << L"-";
	Stream2.width(2);
	Stream2 << (LocalTime2.tm_mon+1);
	Stream2 << L"-";
	Stream2.width(4);
	Stream2 << (LocalTime2.tm_year+1900);
	Stream2 << L"] !";

	wcout << Stream2.str() << endl;

	PrintLineSeparator();

	time_t														CurrentTime3=time(nullptr);
	tm															LocalTime3=*localtime(&CurrentTime3);

	wstringstream												Stream3;

	Stream3.fill(L'0');
	Stream3 << L"LOCAL TIME [";
	Stream3.width(2);
	Stream3 << LocalTime3.tm_hour;
	Stream3 << L":";
	Stream3.width(2);
	Stream3 << LocalTime3.tm_min;
	Stream3 << L":";
	Stream3.width(2);
	Stream3 << LocalTime3.tm_sec;
	Stream3 << L" ";
	Stream3.width(2);
	Stream3 << LocalTime3.tm_mday;
	Stream3 << L"-";
	Stream3.width(2);
	Stream3 << (LocalTime3.tm_mon+1);
	Stream3 << L"-";
	Stream3.width(4);
	Stream3 << (LocalTime3.tm_year+1900);
	Stream3 << L"] !";

	wcout << Stream3.str() << endl;

	// Caka sa NOW+3 sekundy.
	this_thread::sleep_until(system_clock::now()+duration<int,ratio<1,1>>(3));

	time_t														CurrentTime4=time(nullptr);
	tm															LocalTime4=*localtime(&CurrentTime4);

	wstringstream												Stream4;

	Stream4.fill(L'0');
	Stream4 << L"LOCAL TIME [";
	Stream4.width(2);
	Stream4 << LocalTime4.tm_hour;
	Stream4 << L":";
	Stream4.width(2);
	Stream4 << LocalTime4.tm_min;
	Stream4 << L":";
	Stream4.width(2);
	Stream4 << LocalTime4.tm_sec;
	Stream4 << L" ";
	Stream4.width(2);
	Stream4 << LocalTime4.tm_mday;
	Stream4 << L"-";
	Stream4.width(2);
	Stream4 << (LocalTime4.tm_mon+1);
	Stream4 << L"-";
	Stream4.width(4);
	Stream4 << (LocalTime4.tm_year+1900);
	Stream4 << L"] !";

	wcout << Stream3.str() << endl;

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
	//TestSystemClock();
	//TestHighResolutionClock();
	//TestSteadyClock();
	//TestTimePoints();
	//TestStandardCTimeLibrary();
	TestThreadSleep();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------