//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <thread>
#include <chrono>
#include <system_error>
#include <sstream>
#include <future>
#include "MyDebug.h"
#include "CException.h"
#include "CThreadMethod.h"
#include "CThreadFunctor.h"
#include "CClassWithDestructor.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CClassWithDestructor											GlobalVariable(L"GLOBAL VARIABLE");
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThreadCallback(int Index)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestMultipleThreads(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=10;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(ThreadCallback,(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleThreadMethods(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];
	CThreadMethod												ThreadObjects[NUMBER_OF_THREADS]{CThreadMethod(1001),CThreadMethod(1002),CThreadMethod(1003),CThreadMethod(1004),CThreadMethod(1005)};

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			// !!!!! Ak sa pouziva METHOD ako CALLBACK FUNCTION, je NUTNE ako 2. PARAMETER preniest THIS OBJECT.
			Threads[Index]=thread(&CThreadMethod::ThreadMethod,&ThreadObjects[Index],(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleThreadFunctors(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];
	CThreadFunctor												ThreadObjects[NUMBER_OF_THREADS]{CThreadFunctor(1001),CThreadFunctor(1002),CThreadFunctor(1003),CThreadFunctor(1004),CThreadFunctor(1005)};

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// !!!!! Ak sa pouziva OPERATOR() ako CALLBACK FUNCTION, je NUTNE ako 2. PARAMETER preniest THIS OBJECT.
			Threads[Index]=thread(&CThreadFunctor::operator(),&ThreadObjects[Index],(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleLambdaTasks(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=10;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// !!! Ako CALLBACK FUNCTION sa pouziva LAMBDA EXPRESSION.
			Threads[Index]=thread([](int Index){wcout << L"LAMBDA TASK [" << Index << L"] STARTED !" << endl; this_thread::sleep_for(duration<int,ratio<1,1>>(5)); wcout << L"LAMBDA TASK [" << Index << L"] FINISHED !" << endl;},(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Pri ukonceni MAIN THREAD PRED ukoncenim BACKGROUND THREADS dojde pre instancie CLASS [thread] k MEMORY LEAKS. To vsak nie je problem, pretoze PROCESS bol ukonceny. Ak BACKGROUND THREADS je umoznene dobehnut do konca, k MEMORY LEAK NEDOJDE.
void TestBackgroundThreads(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(ThreadCallback,(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Vykona sa DETACH vsetkych THREADS.
				// !!!!! THREADS sa stanu BACKGROUND THREADS, pricom ak MAIN THREAD skonci SKOR ako dobehnu BACKGROUND THREADS, tak budu TERMINATED.
				// !!!!! THREAD TERMINATION znamena, ze dojde k MEMORY LEAK pre THREAD OBJECTS. To vsak NIE JE DOLEZITE, pretoze PROCESS uz skoncil.
				Threads[Index].detach();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void FastBackgroundThreadCallback(int Index)
{
	while(true)
	{
		wcout << L"THREAD [" << Index << L"] is RUNNING !" << endl;
	}
}
//-----------------------------------------------------------------------------
// !!!!! PROGRAM demonstruje, ze ked sa PROGRAM ukonci stlacenim klavesy, pre GLOBAL a STATIC a VARIABLES sa zavolaju ich DESTRUCTORS SKOR, ako sa ukonci beh PROGRAMU.
// !!!!! Pocas testov na LINUX a WINDOWS sa mi BEZNE stavalo, ze BACKGROUND THREADS este bezali, aj ked sa uz DESTRUCTORS pre VARIABLES 'GlobalVariable' a 'StaticVariable'. Ak by BACKGROUND THREADS k tymto VARIABLES pristupovali a tieto napriklad pouzivali HEAP MEMORY, dojde k PADU PROGRAMU.
void TestBackgroundThreadsExit(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(FastBackgroundThreadCallback,(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Vykona sa DETACH vsetkych THREADS.
				// !!!!! THREADS sa stanu BACKGROUND THREADS, pricom ak MAIN THREAD skonci SKOR ako dobehnu BACKGROUND THREADS, tak budu TERMINATED.
				// !!!!! THREAD TERMINATION znamena, ze dojde k MEMORY LEAK pre THREAD OBJECTS. To vsak NIE JE DOLEZITE, pretoze PROCESS uz skoncil.
				Threads[Index].detach();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! PROGRAM demonstruje RIESENIE PROBLEMU kedy sa DESTRUCTORS pre GLOBAL a STATIC OBJECTS volaju SKOR ako dojde k TERMINATION BACKGROUND THREADS.
// !!!!! Riesenim je pouzitie FUNCTION quick_exit(), ktora ukonci PROCESS BEZ zavolania DESTRUCTORS pre GLOBAL a STATIC OBJECTS.
void TestBackgroundThreadsQuickExit(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(FastBackgroundThreadCallback,(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Vykona sa DETACH vsetkych THREADS.
				// !!!!! THREADS sa stanu BACKGROUND THREADS, pricom ak MAIN THREAD skonci SKOR ako dobehnu BACKGROUND THREADS, tak budu TERMINATED.
				// !!!!! THREAD TERMINATION znamena, ze dojde k MEMORY LEAK pre THREAD OBJECTS. To vsak NIE JE DOLEZITE, pretoze PROCESS uz skoncil.
				Threads[Index].detach();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"PROCESS will be FINISHED !" << endl;

	// !!! Sposobi OKAMZITE ukoncenie PROGRAMU BEZ volania DESTRUCTORS pre GLOBAL a STATIC OBJECTS.
	quick_exit(EXIT_FAILURE);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThreadIDCallback(int Index)
{
	wstringstream												Stream1;

	// !!! Ziskanie THREAD ID pomocou FUNCTION this_thread::get_id().
	Stream1 << L"THREAD [" << Index << L"] with ID [" << this_thread::get_id() << L"] STARTED !" << endl;;

	wcout << Stream1.str();

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	// !!! Ziskanie THREAD ID pomocou FUNCTION this_thread::get_id().
	wstringstream												Stream2;

	Stream2 << L"THREAD [" << Index << L"] with ID [" << this_thread::get_id() << L"] FINISHED !" << endl;;

	wcout << Stream2.str();
}
//-----------------------------------------------------------------------------
void TestThreadIDs(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(ThreadIDCallback,(Index+1));

			wstringstream										Stream;

			// !!! Ziskanie THREAD ID pomocou METHOD thread::get_id().
			Stream << L"MAIN - THREAD [" << (Index+1) << L"] with ID [" << Threads[Index].get_id() << L"] STARTED !" << endl;;

			wcout << Stream.str();
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			wstringstream										Stream;

			// !!! Ziskanie THREAD ID pomocou METHOD thread::get_id().
			Stream << L"MAIN - THREAD [" << (Index+1) << L"] with ID [" << Threads[Index].get_id() << L"] FINISHING !" << endl;;

			wcout << Stream.str();

			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}

			// !!! Po skonceni THREAD uz NIE JE MOZNE ZISKAT THREAD ID.
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring GetTime(void)
{
	time_t														CurrentTime=time(nullptr);
	tm															LocalTime=*localtime(&CurrentTime);
	wstringstream												Stream;

	Stream.fill(L'0');
	Stream << L"TIME [";
	Stream.width(2);
	Stream << LocalTime.tm_hour;
	Stream << L":";
	Stream.width(2);
	Stream << LocalTime.tm_min;
	Stream << L":";
	Stream.width(2);
	Stream << LocalTime.tm_sec;
	Stream << L"]";

	wstring														Result(Stream.str());

	return(Result);
}
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackReturningResultAndSignalizing(promise<int>& Promise, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	int															Result=Index*2;

	wcout << GetTime() << L" THREAD [" << Index << L"] SET RESULT !" << endl;

	// !!! OKAMZITE po nastaveni RESULT je PROMISE SIGNALIZED.
	Promise.set_value(Result);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseReturningResultAndSignalizing(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=3;
	promise<int>												Promises[NUMBER_OF_THREADS];
	future<int>													FuturesFromPromises[NUMBER_OF_THREADS];
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
			Threads[Index]=thread(PromiseCallbackReturningResultAndSignalizing,ref(Promises[Index]),(Index+1));

			// !!! Z PROMISE sa vytvori FUTURE pomocou ktorej bude CURRENT THREAD cakat na ulozenie RESULT, alebo EXCEPTION do PROMISE.
			FuturesFromPromises[Index]=Promises[Index].get_future();
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				try
				{
					// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
					int											Result=FuturesFromPromises[Index].get();

					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
				}
				catch(const CException& E)
				{
					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
				}
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackThrowingExceptionAndSignalizing(promise<int>& Promise, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	try
	{
		throw(CException(L"SOME EXCEPTION !"));
	}
	catch(CException)
	{
		wcout << GetTime() << L" THREAD [" << Index << L"] SET EXCEPTION !" << endl;

		// !!! FUNCTION current_exception() vracia EXCEPTION asociovanu s EXCEPTION BLOCK.
		// !!! OKAMZITE po nastaveni EXCEPTION je PROMISE SIGNALIZED.
		Promise.set_exception(current_exception());
	}

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseThrowingExceptionAndSignalizing(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=3;
	promise<int>												Promises[NUMBER_OF_THREADS];
	future<int>													FuturesFromPromises[NUMBER_OF_THREADS];
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
			Threads[Index]=thread(PromiseCallbackThrowingExceptionAndSignalizing,ref(Promises[Index]),(Index+1));

			// !!! Z PROMISE sa vytvori FUTURE pomocou ktorej bude CURRENT THREAD cakat na ulozenie RESULT, alebo EXCEPTION do PROMISE.
			FuturesFromPromises[Index]=Promises[Index].get_future();
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				try
				{
					// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
					int											Result=FuturesFromPromises[Index].get();

					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
				}
				catch(const CException& E)
				{
					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
				}
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackReturningResultButNotSignalizing(promise<int>& Promise, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	int															Result=Index*2;

	wcout << GetTime() << L" THREAD [" << Index << L"] SET RESULT !" << endl;

	// !!! Nastavi RESULT, ale PROMISE NIE JE SIGNALIZED az kym sa CURRENT THREAD NESKONCI.
	Promise.set_value_at_thread_exit(Result);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseReturningResultButNotSignalizing(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=3;
	promise<int>												Promises[NUMBER_OF_THREADS];
	future<int>													FuturesFromPromises[NUMBER_OF_THREADS];
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
			Threads[Index]=thread(PromiseCallbackReturningResultButNotSignalizing,ref(Promises[Index]),(Index+1));

			// !!! Z PROMISE sa vytvori FUTURE pomocou ktorej bude CURRENT THREAD cakat na ulozenie RESULT, alebo EXCEPTION do PROMISE.
			FuturesFromPromises[Index]=Promises[Index].get_future();
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				try
				{
					// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
					int											Result=FuturesFromPromises[Index].get();

					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
				}
				catch(const CException& E)
				{
					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
				}
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackThrowingExceptionButNotSignalizing(promise<int>& Promise, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	try
	{
		throw(CException(L"SOME EXCEPTION !"));
	}
	catch(CException)
	{
		wcout << GetTime() << L" THREAD [" << Index << L"] SET EXCEPTION !" << endl;

		// !!! FUNCTION current_exception() vracia EXCEPTION asociovanu s EXCEPTION BLOCK.
		// !!! Nastavi EXCEPTION, ale PROMISE NIE JE SIGNALIZED az kym sa CURRENT THREAD NESKONCI.
		Promise.set_exception_at_thread_exit(current_exception());
	}

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseThrowingExceptionButNotSignalizing(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=3;
	promise<int>												Promises[NUMBER_OF_THREADS];
	future<int>													FuturesFromPromises[NUMBER_OF_THREADS];
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
			Threads[Index]=thread(PromiseCallbackThrowingExceptionButNotSignalizing,ref(Promises[Index]),(Index+1));

			// !!! Z PROMISE sa vytvori FUTURE pomocou ktorej bude CURRENT THREAD cakat na ulozenie RESULT, alebo EXCEPTION do PROMISE.
			FuturesFromPromises[Index]=Promises[Index].get_future();
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				try
				{
					// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
					int											Result=FuturesFromPromises[Index].get();

					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
				}
				catch(const CException& E)
				{
					wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
				}
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << GetTime() << L" MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PackagedTaskCallback(int Index)
{
	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskCallback(packaged_task<void(int)>& PackagedTask, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou OPERATOR().
	PackagedTask(Index);

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] PACKAGED TASK FINISHED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestPackagedTasks(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=3;
	packaged_task<void(int)>									PackagedTasks[NUMBER_OF_TASKS];
	thread														Threads[NUMBER_OF_TASKS];
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori PACKAGED TASK, ktory sa vsak AUTOMATICKY NESPUSTAJU v THREADS. Tieto THREADS je NUTNE vytvorit MANUALNE.
		PackagedTasks[Index]=packaged_task<void(int)>(PackagedTaskCallback);

		// !!! MANUALNE sa vytvori THREAD, ktory bude spustat TASK CODE. THREAD sa spusta OKAMZITE.
		Threads[Index]=thread(ThreadCodePackagedTaskCallback,ref(PackagedTasks[Index]),(Index+1));

		// Vytvori TASK z PACKAGED TASK. TASK sluzi na cakanie na ukoncenie PACKAGED TASK.
		Tasks[Index]=PackagedTasks[Index].get_future();
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wcout << GetTime() << L" MAIN AFTER GET !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithResultCallback(int Index)
{
	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] FINISHED !" << endl;

	int															Result=Index*2;

	return(Result);
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskWithResultCallback(packaged_task<int(int)>& PackagedTask, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou OPERATOR().
	PackagedTask(Index);

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] PACKAGED TASK FINISHED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithResult(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=3;
	packaged_task<int(int)>										PackagedTasks[NUMBER_OF_TASKS];
	thread														Threads[NUMBER_OF_TASKS];
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori PACKAGED TASK, ktory sa vsak AUTOMATICKY NESPUSTAJU v THREADS. Tieto THREADS je NUTNE vytvorit MANUALNE.
		PackagedTasks[Index]=packaged_task<int(int)>(PackagedTaskWithResultCallback);

		// !!! MANUALNE sa vytvori THREAD, ktory bude spustat TASK CODE. THREAD sa spusta OKAMZITE.
		Threads[Index]=thread(ThreadCodePackagedTaskWithResultCallback,ref(PackagedTasks[Index]),(Index+1));

		// Vytvori TASK z PACKAGED TASK. TASK sluzi na cakanie na ukoncenie PACKAGED TASK.
		Tasks[Index]=PackagedTasks[Index].get_future();
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		int														Result=Tasks[Index].get();

		wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
	}

	wcout << GetTime() << L" MAIN AFTER GET !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithExceptionCallback(int Index)
{
	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] FINISHED !" << endl;

	if ((Index%2)!=0)
	{
		int														Result=Index*2;

		return(Result);
	}
	else
	{
		throw(CException(L"SOME EXCEPTION !"));
	}
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskWithExceptionCallback(packaged_task<int(int)>& PackagedTask, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou OPERATOR().
	PackagedTask(Index);

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] PACKAGED TASK FINISHED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithException(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=3;
	packaged_task<int(int)>										PackagedTasks[NUMBER_OF_TASKS];
	thread														Threads[NUMBER_OF_TASKS];
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori PACKAGED TASK, ktory sa vsak AUTOMATICKY NESPUSTAJU v THREADS. Tieto THREADS je NUTNE vytvorit MANUALNE.
		PackagedTasks[Index]=packaged_task<int(int)>(PackagedTaskWithExceptionCallback);

		// !!! MANUALNE sa vytvori THREAD, ktory bude spustat TASK CODE. THREAD sa spusta OKAMZITE.
		Threads[Index]=thread(ThreadCodePackagedTaskWithExceptionCallback,ref(PackagedTasks[Index]),(Index+1));

		// Vytvori TASK z PACKAGED TASK. TASK sluzi na cakanie na ukoncenie PACKAGED TASK.
		Tasks[Index]=PackagedTasks[Index].get_future();
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
			int													Result=Tasks[Index].get();

			wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
		}
		catch(const CException& E)
		{
			wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN AFTER GET !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PackagedTaskAtAndOfThreadCallback(int Index)
{
	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskAtAndOfThreadCallback(packaged_task<void(int)>& PackagedTask, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou METHOD packaged_task::make_ready_at_thread_exit().
	PackagedTask.make_ready_at_thread_exit(Index);

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] PACKAGED TASK FINISHED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestPackagedTasksAtAndOfThread(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=3;
	packaged_task<void(int)>									PackagedTasks[NUMBER_OF_TASKS];
	thread														Threads[NUMBER_OF_TASKS];
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori PACKAGED TASK, ktory sa vsak AUTOMATICKY NESPUSTAJU v THREADS. Tieto THREADS je NUTNE vytvorit MANUALNE.
		PackagedTasks[Index]=packaged_task<void(int)>(PackagedTaskAtAndOfThreadCallback);

		// !!! MANUALNE sa vytvori THREAD, ktory bude spustat TASK CODE. THREAD sa spusta OKAMZITE.
		Threads[Index]=thread(ThreadCodePackagedTaskAtAndOfThreadCallback,ref(PackagedTasks[Index]),(Index+1));

		// Vytvori TASK z PACKAGED TASK. TASK sluzi na cakanie na ukoncenie PACKAGED TASK.
		Tasks[Index]=PackagedTasks[Index].get_future();
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wcout << GetTime() << L" MAIN AFTER GET !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithResultAtAndOfThreadCallback(int Index)
{
	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] FINISHED !" << endl;

	int															Result=Index*2;

	return(Result);
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskWithResultAtAndOfThreadCallback(packaged_task<int(int)>& PackagedTask, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou METHOD packaged_task::make_ready_at_thread_exit().
	PackagedTask.make_ready_at_thread_exit(Index);

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] PACKAGED TASK FINISHED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithResultAtAndOfThread(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=3;
	packaged_task<int(int)>										PackagedTasks[NUMBER_OF_TASKS];
	thread														Threads[NUMBER_OF_TASKS];
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori PACKAGED TASK, ktory sa vsak AUTOMATICKY NESPUSTAJU v THREADS. Tieto THREADS je NUTNE vytvorit MANUALNE.
		PackagedTasks[Index]=packaged_task<int(int)>(PackagedTaskWithResultAtAndOfThreadCallback);

		// !!! MANUALNE sa vytvori THREAD, ktory bude spustat TASK CODE. THREAD sa spusta OKAMZITE.
		Threads[Index]=thread(ThreadCodePackagedTaskWithResultAtAndOfThreadCallback,ref(PackagedTasks[Index]),(Index+1));

		// Vytvori TASK z PACKAGED TASK. TASK sluzi na cakanie na ukoncenie PACKAGED TASK.
		Tasks[Index]=PackagedTasks[Index].get_future();
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		int														Result=Tasks[Index].get();

		wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
	}

	wcout << GetTime() << L" MAIN AFTER GET !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithExceptionAtAndOfThreadCallback(int Index)
{
	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << GetTime() << L" PACKAGED TASK [" << Index << L"] FINISHED !" << endl;

	if ((Index%2)!=0)
	{
		int														Result=Index*2;

		return(Result);
	}
	else
	{
		throw(CException(L"SOME EXCEPTION !"));
	}
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskWithExceptionAtAndOfThreadCallback(packaged_task<int(int)>& PackagedTask, int Index)
{
	wcout << GetTime() << L" THREAD [" << Index << L"] STARTED !" << endl;

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou METHOD packaged_task::make_ready_at_thread_exit().
	PackagedTask.make_ready_at_thread_exit(Index);

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] PACKAGED TASK FINISHED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << "!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithExceptionAtAndOfThread(void)
{
	PrintLineSeparator();

	wcout << GetTime() << L" MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=3;
	packaged_task<int(int)>										PackagedTasks[NUMBER_OF_TASKS];
	thread														Threads[NUMBER_OF_TASKS];
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori PACKAGED TASK, ktory sa vsak AUTOMATICKY NESPUSTAJU v THREADS. Tieto THREADS je NUTNE vytvorit MANUALNE.
		PackagedTasks[Index]=packaged_task<int(int)>(PackagedTaskWithExceptionAtAndOfThreadCallback);

		// !!! MANUALNE sa vytvori THREAD, ktory bude spustat TASK CODE. THREAD sa spusta OKAMZITE.
		Threads[Index]=thread(ThreadCodePackagedTaskWithExceptionAtAndOfThreadCallback,ref(PackagedTasks[Index]),(Index+1));

		// Vytvori TASK z PACKAGED TASK. TASK sluzi na cakanie na ukoncenie PACKAGED TASK.
		Tasks[Index]=PackagedTasks[Index].get_future();
	}

	wcout << GetTime() << L" MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << GetTime() << L" MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
			int													Result=Tasks[Index].get();

			wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
		}
		catch(const CException& E)
		{
			wcout << GetTime() << L" MAIN - TASK [" << (Index+1) << L"] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
		}
	}

	wcout << GetTime() << L" MAIN AFTER GET !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wcout << GetTime() << L" MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestGetLevelOfParallelism(void)
{
	PrintLineSeparator();

	wcout << L"LEVEL of PARALLELISM [" << thread::hardware_concurrency() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SleepUntilThreadCallback(int Index)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	// Caka sa 5 sekund.
	// !!! Pouziva sa FUNCTION sleep_until().
	this_thread::sleep_until(system_clock::now()+duration<int,ratio<1,1>>(5));

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestSleepUntilThreads(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=10;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(SleepUntilThreadCallback,(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	// !!! Pouziva sa FUNCTION sleep_until().
	this_thread::sleep_until(system_clock::now()+duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void YieldThreadCallback(int Index)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(size_t Counter=0;Counter<1000;Counter++)
	{
		wcout << L"THREAD [" << Index << L"] WORKING !" << endl;

		// CURRENT THREAD sa vzda svojho casoveho kvanta.
		this_thread::yield();
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestYieldThreads(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_THREADS=2;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(YieldThreadCallback,(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestMultipleThreads();
	//TestMultipleThreadMethods();
	//TestMultipleThreadFunctors();
	//TestMultipleLambdaTasks();
	//TestBackgroundThreads();
	//TestBackgroundThreadsExit();
	//TestBackgroundThreadsQuickExit();
	//TestThreadIDs();
	//TestThreadsWithPromiseReturningResultAndSignalizing();
	//TestThreadsWithPromiseThrowingExceptionAndSignalizing();
	TestThreadsWithPromiseReturningResultButNotSignalizing();
	//TestThreadsWithPromiseThrowingExceptionButNotSignalizing();
	//TestPackagedTasks();
	//TestPackagedTasksWithResult();
	//TestPackagedTasksWithException();
	//TestPackagedTasksAtAndOfThread();
	//TestPackagedTasksWithResultAtAndOfThread();
	//TestPackagedTasksWithExceptionAtAndOfThread();
	//TestGetLevelOfParallelism();
	//TestSleepUntilThreads();
	//TestYieldThreads();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------