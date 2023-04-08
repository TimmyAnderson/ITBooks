//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <utility>
#include <thread>
#include <mutex>
#include <sstream>
#include <iostream>
#include <condition_variable>
#include <future>
#include "MyDebug.h"
#include "CException.h"
#include "CThreadMethod.h"
#include "CThreadFunctor.h"
#include "CClassWithDestructor.h"
#include "CThreadLocal.h"
#include "CTaskMethod.h"
#include "CTaskFunctor.h"
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
thread_local int												GlobalVariable=0;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThreadCallback(int Index)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestMultipleThreads(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleThreadMethods(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleThreadFunctors(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleLambdaTasks(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_THREADS=10;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// !!! Ako CALLBACK FUNCTION sa pouziva LAMBDA EXPRESSION.
			Threads[Index]=thread([](int Index){wprintf_s(L"LAMBDA TASK [%d] STARTED !\n",Index); this_thread::sleep_for(duration<int,ratio<1,1>>(5)); wprintf_s(L"LAMBDA TASK [%d] FINISHED !\n",Index);},(Index+1));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ThreadIDCallback(int Index)
{
	wstringstream												Stream1;

	// !!! Ziskanie THREAD ID pomocou FUNCTION this_thread::get_id().
	Stream1 << L"THREAD [" << Index << L"] with ID [" << this_thread::get_id() << L"] STARTED !\n";

	wcout << Stream1.str();

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	// !!! Ziskanie THREAD ID pomocou FUNCTION this_thread::get_id().
	wstringstream												Stream2;

	Stream2 << L"THREAD [" << Index << L"] with ID [" << this_thread::get_id() << L"] FINISHED !\n";

	wcout << Stream2.str();
}
//-----------------------------------------------------------------------------
void TestThreadIDs(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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
			Stream << L"MAIN - THREAD [" << (Index+1) << L"] with ID [" << Threads[Index].get_id() << L"] STARTED !\n";

			wcout << Stream.str();
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			wstringstream										Stream;

			// !!! Ziskanie THREAD ID pomocou METHOD thread::get_id().
			Stream << L"MAIN - THREAD [" << (Index+1) << L"] with ID [" << Threads[Index].get_id() << L"] FINISHING !\n";

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!!!! Pri ukonceni MAIN THREAD PRED ukoncenim BACKGROUND THREADS dojde pre instancie CLASS [thread] k MEMORY LEAKS. To vsak nie je problem, pretoze PROCESS bol ukonceny. Ak BACKGROUND THREADS je umoznene dobehnut do konca, k MEMORY LEAK NEDOJDE.
void TestBackgroundThreads(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void FastBackgroundThreadCallback(int Index)
{
	while(true)
	{
		wprintf_s(L"THREAD [%d] is RUNNING !\n",Index);
	}
}
//-----------------------------------------------------------------------------
// !!!!! PROGRAM demonstruje, ze ked sa PROGRAM ukonci stlacenim klavesy, pre GLOBAL a STATIC a VARIABLES sa zavolaju ich DESTRUCTORS SKOR, ako sa ukonci beh PROGRAMU.
// !!!!! Pocas testov na LINUX aj WINDOWS sa mi BEZNE stavalo, ze BACKGROUND THREADS este bezali, aj ked sa uz DESTRUCTORS pre VARIABLES 'GlobalVariable' a 'StaticVariable'. Ak by BACKGROUND THREADS k tymto VARIABLES pristupovali a tieto napriklad pouzivali HEAP MEMORY, dojde k PADU PROGRAMU.
void TestBackgroundThreadsExit(void)
{
	PrintLineSeparator();

	static CClassWithDestructor									StaticVariable(L"STATIC VARIABLE");

	wprintf_s(L"MAIN STARTED !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

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

	wprintf_s(L"MAIN STARTED !\n");

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
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"PROCESS will be FINISHED !\n");

	// !!! Sposobi OKAMZITE ukoncenie PROGRAMU BEZ volania DESTRUCTORS pre GLOBAL a STATIC OBJECTS.
	quick_exit(EXIT_FAILURE);
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ClassThreadLocalThread(int Index)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	CThreadLocal::InitializeStaticVariable(Index);

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	// !!! Kazdy THREAD ma vlastnu instanciu STATIC VARIABLE.
	wprintf_s(L"THREAD [%d] - STATIC VARIABLE [%d] !\n",Index,CThreadLocal::GetStaticVariable());

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestClassThreadLocal(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(ClassThreadLocalThread,(Index+1));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ClassFunctionLocalThread(int Index)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	static thread_local int										StaticVariable=Index;

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	// !!! Kazdy THREAD ma vlastnu instanciu STATIC VARIABLE.
	wprintf_s(L"THREAD [%d] - STATIC VARIABLE [%d] !\n",Index,StaticVariable);

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestFunctionThreadLocal(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(ClassFunctionLocalThread,(Index+1));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ClassGlobalLocalThread(int Index)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	GlobalVariable=Index;

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	// !!! Kazdy THREAD ma vlastnu instanciu GLOBAL VARIABLE.
	wprintf_s(L"THREAD [%d] - GLOBAL VARIABLE [%d] !\n",Index,GlobalVariable);

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestGlobalThreadLocal(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(ClassGlobalLocalThread,(Index+1));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void ComplexClassThreadLocalThread(int Index)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	CThreadLocal::InitializeComplexStaticVariable(Index);

	this_thread::sleep_for(duration<int,ratio<1,1>>(1));

	// !!! Kazdy THREAD ma vlastnu instanciu STATIC VARIABLE.
	wprintf_s(L"THREAD [%d] - STATIC VARIABLE [%d] !\n",Index,CThreadLocal::GetComplexStaticVariable());

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestComplexClassThreadLocal(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(ComplexClassThreadLocalThread,(Index+1));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			if (Threads[Index].joinable()==true)
			{
				Threads[Index].join();
			}
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementMutex(int Index, mutex& Mutex, int* Counter)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! Vykona sa LOCKING.
		Mutex.lock();

		*Counter=*Counter+1;

		// !!! Vykona sa UNLOCKING.
		Mutex.unlock();
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestMutex(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	int															Counter=0;
	mutex														Mutex;

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(IncrementMutex,(Index+1),ref(Mutex),&Counter);
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	wprintf_s(L"COUNTER [%d] !\n",Counter);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementRecursiveMutex(int Index, recursive_mutex& Mutex, int* Counter)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! Vykona sa LOCKING.
		Mutex.lock();
		// !!! Vykona sa RESURSIVE LOCKING.
		Mutex.lock();

		*Counter=*Counter+1;

		// !!! Vykona sa RESURSIVE UNLOCKING.
		Mutex.unlock();
		// !!! Vykona sa UNLOCKING.
		Mutex.unlock();
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestRecursiveMutex(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	int															Counter=0;
	recursive_mutex												Mutex;

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(IncrementRecursiveMutex,(Index+1),ref(Mutex),&Counter);
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	wprintf_s(L"COUNTER [%d] !\n",Counter);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! V GCC sposobi CODE DEADLOCK.
void TestMutexErrorRecursiveLock(void)
{
	PrintLineSeparator();

	// NON-RECURSIVE MUTEX.
	mutex														Mutex;

	try
	{
		Mutex.lock();
		wprintf_s(L"LOCK ACQUIRED !\n");

		// !!!!! VC++ hodi EXCEPTION, pretoze LOCK uz bol ACQUIRED a MUTEX je NON-RECURSIVE.
		// !!!!! GCC sposobi DEADLOCK.
		Mutex.lock();
		wprintf_s(L"LOCK ACQUIRED !\n");

		Mutex.unlock();
		wprintf_s(L"LOCK RELEASED !\n");

		Mutex.unlock();
		wprintf_s(L"LOCK RELEASED !\n");
	}
	catch(const system_error& E)
	{
		printf_s("MUTEX EXCEPTION - CODE [%d], WHAT [%s] !\n",E.code().value(),E.what());

		Mutex.unlock();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DeadlockThread1(mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [1] STARTED !\n");

	try
	{
		Mutex1.lock();

		// Caka sa 2 sekundy.
		this_thread::sleep_for(duration<int,ratio<1,1>>(2));

		// !!!!! Niektore implementacie mozu hodit EXCEPTION, ak detekuju DEADLOCK.
		// !!!!! VC 2015 NEROBI tuto detekciu a PROGRAM skonci v DEADLOCK.
		// !!!!! GCC sposobi DEADLOCK.
		Mutex2.lock();

		// Caka sa 2 sekundy.
		this_thread::sleep_for(duration<int,ratio<1,1>>(2));

		Mutex2.unlock();

		Mutex1.unlock();
	}
	catch(const system_error& E)
	{
		printf_s("MUTEX EXCEPTION - CODE [%d], WHAT [%s] !\n",E.code().value(),E.what());

		Mutex1.unlock();
	}

	wprintf_s(L"THREAD [1] FINISHED !\n");
}
//-----------------------------------------------------------------------------
void DeadlockThread2(mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [2] STARTED !\n");

	try
	{
		Mutex2.lock();

		// Caka sa 2 sekundy.
		this_thread::sleep_for(duration<int,ratio<1,1>>(2));

		// !!!!! Niektore implementacie mozu hodit EXCEPTION, ak detekuju DEADLOCK.
		// !!!!! VC 2015 NEROBI tuto detekciu a PROGRAM skonci v DEADLOCK.
		// !!!!! GCC sposobi DEADLOCK.
		Mutex1.lock();

		// Caka sa 2 sekundy.
		this_thread::sleep_for(duration<int,ratio<1,1>>(2));

		Mutex1.unlock();

		Mutex2.unlock();
	}
	catch(const system_error& E)
	{
		printf_s("MUTEX EXCEPTION - CODE [%d], WHAT [%s] !\n",E.code().value(),E.what());

		Mutex2.unlock();
	}

	wprintf_s(L"THREAD [2] FINISHED !\n");
}
//-----------------------------------------------------------------------------
// !!!!! Vo VC 2015 CODE sposobi DEADLOCK.
// !!! V GCC sposobi CODE DEADLOCK.
void TestMutexErrorDeadlock(void)
{
	PrintLineSeparator();

	mutex														Mutex1;
	mutex														Mutex2;

	thread														Thread1;
	thread														Thread2;

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread1=thread(DeadlockThread1,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wprintf_s(L"MAIN THREAD [1] was NOT STARTED !\n");
	}

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread2=thread(DeadlockThread2,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wprintf_s(L"MAIN THREAD [2] was NOT STARTED !\n");
	}

	try
	{
		if (Thread1.joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Thread1.join();
		}
	}
	catch(system_error)
	{
		wprintf_s(L"THREAD [1] was NOT FINISHED !\n");
	}

	try
	{
		if (Thread2.joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Thread2.join();
		}
	}
	catch(system_error)
	{
		wprintf_s(L"THREAD [2] was NOT FINISHED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TriedForTimedMutexThread(int Index, timed_mutex& Mutex)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	// !!! Vykona sa pokus o LOCKING.
	while(Mutex.try_lock_for(duration<int,ratio<1,1>>(1))==false)
	{
		wprintf_s(L"!!! THREAD [%d] was NOT ABLE to ACQUIRE LOCK !\n",Index);
	}

	wprintf_s(L"THREAD [%d] ACQUIRED LOCK !\n",Index);

	// !!! LOCK bol ziskany.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"THREAD [%d] RELEASING LOCK !\n",Index);

	// !!! Vykona sa UNLOCKING.
	Mutex.unlock();

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestTriedForTimedMutex(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	timed_mutex													Mutex;

	{
		const int												NUMBER_OF_THREADS=3;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(TriedForTimedMutexThread,(Index+1),ref(Mutex));
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TriedUntilTimedMutexThread(int Index, timed_mutex& Mutex)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	// !!! Vykona sa pokus o LOCKING.
	while(Mutex.try_lock_until(system_clock::now()+duration<int,ratio<1,1>>(1))==false)
	{
		wprintf_s(L"!!! THREAD [%d] was NOT ABLE to ACQUIRE LOCK !\n",Index);
	}

	wprintf_s(L"THREAD [%d] ACQUIRED LOCK !\n",Index);

	// !!! LOCK bol ziskany.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"THREAD [%d] RELEASING LOCK !\n",Index);

	// !!! Vykona sa UNLOCKING.
	Mutex.unlock();

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestTriedUntilTimedMutex(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	timed_mutex													Mutex;

	{
		const int												NUMBER_OF_THREADS=3;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(TriedUntilTimedMutexThread,(Index+1),ref(Mutex));
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void LockFunctionThread(int Index, int* Counter, mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<100;Index++)
	{
		// !!! Ziskaju sa 2 MUTEXES.
		lock(Mutex1,Mutex2);

		*Counter=*Counter+1;

		wprintf_s(L"THREAD [%d] ACQUIRED LOCKS !\n",Index);

		// !!! LOCK bol ziskany.
		this_thread::sleep_for(duration<int,ratio<1,100>>(1));

		wprintf_s(L"THREAD [%d] RELEASING LOCKS !\n",Index);

		// !!! Vykona sa UNLOCKING.
		Mutex1.unlock();
		// !!! Vykona sa UNLOCKING.
		Mutex2.unlock();
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestLockFunction(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	int															Counter=0;
	mutex														Mutex1;
	mutex														Mutex2;

	{
		const int												NUMBER_OF_THREADS=2;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// !!!!! Do THREADS sa zaslu MUTEXES v ROZLICNOM PORADI, aby sa demonstrovalo, ze FUNCTION lock() ma mechanizmus, ktory zabranuje vzniku DEADLOCKS.

				if ((Index % 2)==0)
				{
					// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
					Threads[Index]=thread(LockFunctionThread,(Index+1),&Counter,ref(Mutex1),ref(Mutex2));
				}
				else
				{
					// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
					Threads[Index]=thread(LockFunctionThread,(Index+1),&Counter,ref(Mutex2),ref(Mutex1));
				}
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	wprintf_s(L"COUNTER [%d] !\n",Counter);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void LockFunctionUsingLockThread(int Index, int* Counter, mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<100;Index++)
	{
		// !!! Ziskaju sa 2 MUTEXES.
		lock(Mutex1,Mutex2);

		{
			// !!! Pre MUTEXES sa vytvoria instancie CLASS [lock_guard<TMutex>], aby nebolo potrebne MANUALNE robit UNLOCK.
			// !!!!! Kedze LOCKS uz BOLI ZISKANE volanim FUNCTION lock() je NUTNE zavolat OVERLOADED verziu CONSTRUCTOR, ktora NEZISKA LOCKS iba UZ ZISKANE LOCKS adaptuje.
			lock_guard<mutex>									Lock1(Mutex1,adopt_lock);
			lock_guard<mutex>									Lock2(Mutex2,adopt_lock);

			*Counter=*Counter+1;

			wprintf_s(L"THREAD [%d] ACQUIRED LOCKS !\n",Index);

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,100>>(1));

			wprintf_s(L"THREAD [%d] RELEASING LOCKS !\n",Index);

			// !!! DESTRUCTOR CLASSES [lock_guard<TMutex>] AUTOMATICKY uvolnia LOCKS.
		}
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestLockFunctionUsingLock(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	int															Counter=0;
	mutex														Mutex1;
	mutex														Mutex2;

	{
		const int												NUMBER_OF_THREADS=2;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// !!!!! Do THREADS sa zaslu MUTEXES v ROZLICNOM PORADI, aby sa demonstrovalo, ze FUNCTION lock() ma mechanizmus, ktory zabranuje vzniku DEADLOCKS.

				if ((Index % 2)==0)
				{
					// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
					Threads[Index]=thread(LockFunctionUsingLockThread,(Index+1),&Counter,ref(Mutex1),ref(Mutex2));
				}
				else
				{
					// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
					Threads[Index]=thread(LockFunctionUsingLockThread,(Index+1),&Counter,ref(Mutex2),ref(Mutex1));
				}
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	wprintf_s(L"COUNTER [%d] !\n",Counter);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TryLockFunctionThread(int Index, mutex& Mutex1, mutex& Mutex2, mutex& LockFailureMutex, int& Lock1Failures, int& Lock2Failures)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	while(true)
	{
		// !!! Ziskaju sa 2 MUTEXES.
		int														Result=try_lock(Mutex1,Mutex2);

		if (Result==-1)
		{
			wprintf_s(L"THREAD [%d] ACQUIRED LOCKS !\n",Index);

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,1>>(3));

			wprintf_s(L"THREAD [%d] RELEASING LOCKS !\n",Index);

			break;
		}
		else
		{
			wprintf_s(L"!!! THREAD [%d] was NOT ABLE to ACQUIRE LOCK [%d] !\n",Index,Result);

			if (Result==1)
			{
				lock_guard<mutex>								LockFailure(LockFailureMutex);

				Lock1Failures++;
			}
			else
			{
				lock_guard<mutex>								LockFailure(LockFailureMutex);

				Lock2Failures++;
			}

			this_thread::sleep_for(duration<int,ratio<1,1>>(1));
		}
	}

	// !!! Vykona sa UNLOCKING.
	Mutex1.unlock();
	// !!! Vykona sa UNLOCKING.
	Mutex2.unlock();

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestTryLockFunction(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	int															Lock1Failures=0;
	int															Lock2Failures=0;
	mutex														LockFailureMutex;
	mutex														Mutex1;
	mutex														Mutex2;

	{
		const int												NUMBER_OF_THREADS=10;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// !!!!! Ak ked FUNCTION try_lock() NEMA mechanizmus, ktory zabranuje vzniku DEADLOCKS, kedze FUNCTION NEVYKONAVA CURRENT THREAD BLOCKING, NEMOZE sposobit DEADLOCK.
				if ((Index % 2)==0)
				{
					// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
					Threads[Index]=thread(TryLockFunctionThread,(Index+1),ref(Mutex1),ref(Mutex2),ref(LockFailureMutex),ref(Lock1Failures),ref(Lock2Failures));
				}
				else
				{
					// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
					Threads[Index]=thread(TryLockFunctionThread,(Index+1),ref(Mutex2),ref(Mutex1),ref(LockFailureMutex),ref(Lock1Failures),ref(Lock2Failures));
				}
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	wprintf_s(L"LOCK 1 FAILURES [%d] !\n",Lock1Failures);
	wprintf_s(L"LOCK 2 FAILURES [%d] !\n",Lock2Failures);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementUniqueLock(int Index, mutex& Mutex, int* Counter)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! CONSTRUCTOR vykona LOCKING a DESTRUCTOR UNLOCKING.
		unique_lock<mutex>										Lock(Mutex);

		*Counter=*Counter+1;
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestUniqueLock(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	int															Counter=0;
	mutex														Mutex;

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(IncrementUniqueLock,(Index+1),ref(Mutex),&Counter);
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	wprintf_s(L"COUNTER [%d] !\n",Counter);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementDeferredUniqueLock(int Index, mutex& Mutex, int* Counter)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! CONSTRUCTOR NEVYKONA LOCKING.
		// !!! Casto sa tento CONSTRUCTOR pouziva spolu s volanim FUNCTION lock(), alebo FUNCTION try_lock().
		unique_lock<mutex>										Lock(Mutex,defer_lock);

		// !!!!! Kedze sa v CONSTRUCTOR zadala VALUE [defer_lock], je NUTNE vykonat LOCKING MANUALNE.
		Lock.lock();

		*Counter=*Counter+1;

		// Vykona sa MANUALNY UNLOCKING.
		Lock.unlock();
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestDeferredUniqueLock(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	int															Counter=0;
	mutex														Mutex;

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(IncrementDeferredUniqueLock,(Index+1),ref(Mutex),&Counter);
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	wprintf_s(L"COUNTER [%d] !\n",Counter);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TryLockUniqueLockThread(int Index, mutex& Mutex)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	while(true)
	{
		// !!! Kedze sa pouzil CONSTRUCTOR, ktory prijima TYPE [try_to_lock_t], tak LOCK NEBUDE prideleny CURRENT THREAD, ak ho INY THREAD drzi.
		unique_lock<mutex>										Lock(Mutex,try_to_lock);

		if (Lock.owns_lock()==true)
		{
			wprintf_s(L"THREAD [%d] ACQUIRED LOCKS !\n",Index);

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,1>>(3));

			wprintf_s(L"THREAD [%d] RELEASING LOCKS !\n",Index);

			break;
		}
		else
		{
			wprintf_s(L"!!! THREAD [%d] was NOT ABLE to ACQUIRE LOCK !\n",Index);

			this_thread::sleep_for(duration<int,ratio<1,1>>(1));
		}
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestTryLockUniqueLockFunction(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	mutex														Mutex;

	{
		const int												NUMBER_OF_THREADS=2;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(TryLockUniqueLockThread,(Index+1),ref(Mutex));
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DurationUniqueLockThread(int Index, recursive_timed_mutex& Mutex)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	while(true)
	{
		// !!! CONSTRUCTOR caka zadany cas na ziskanie LOCK.
		unique_lock<recursive_timed_mutex>						Lock(Mutex,duration<int,ratio<1,1>>(1));

		if (Lock.owns_lock()==true)
		{
			wprintf_s(L"THREAD [%d] ACQUIRED LOCKS !\n",Index);

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,1>>(3));

			wprintf_s(L"THREAD [%d] RELEASING LOCKS !\n",Index);

			break;
		}
		else
		{
			wprintf_s(L"!!! THREAD [%d] was NOT ABLE to ACQUIRE LOCK !\n",Index);
		}
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestDurationUniqueLockFunction(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	recursive_timed_mutex										Mutex;

	{
		const int												NUMBER_OF_THREADS=2;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(DurationUniqueLockThread,(Index+1),ref(Mutex));
			}
			catch(system_error)
			{
				wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
				wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
			}
		}

		wprintf_s(L"MAIN FINISHED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DeadlockLockThread1(mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [1] STARTED !\n");

	try
	{
		for(int Index=0;Index<1000*1000*10;Index++)
		{
			// !!!!! FUNCTION lock() vykonava algoritmus, ktory zabranuje vzniku DEADLOCK.
			lock(Mutex1,Mutex2);

			Mutex2.unlock();

			Mutex1.unlock();
		}
	}
	catch(const system_error& E)
	{
		printf_s("MUTEX EXCEPTION - CODE [%d], WHAT [%s] !\n",E.code().value(),E.what());

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wprintf_s(L"THREAD [1] FINISHED !\n");
}
//-----------------------------------------------------------------------------
void DeadlockLockThread2(mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [2] STARTED !\n");

	try
	{
		for(int Index=0;Index<1000*1000*10;Index++)
		{
			// !!!!! FUNCTION lock() vykonava algoritmus, ktory zabranuje vzniku DEADLOCK.
			lock(Mutex2,Mutex1);

			Mutex1.unlock();

			Mutex2.unlock();
		}
	}
	catch(const system_error& E)
	{
		printf_s("MUTEX EXCEPTION - CODE [%d], WHAT [%s] !\n",E.code().value(),E.what());

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wprintf_s(L"THREAD [2] FINISHED !\n");
}
//-----------------------------------------------------------------------------
void TestMutexErrorDeadlockLock(void)
{
	PrintLineSeparator();

	mutex														Mutex1;
	mutex														Mutex2;

	thread														Thread1;
	thread														Thread2;

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread1=thread(DeadlockLockThread1,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wprintf_s(L"MAIN THREAD [1] was NOT STARTED !\n");
	}

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread2=thread(DeadlockLockThread2,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wprintf_s(L"MAIN THREAD [2] was NOT STARTED !\n");
	}

	try
	{
		if (Thread1.joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Thread1.join();
		}
	}
	catch(system_error)
	{
		wprintf_s(L"THREAD [1] was NOT FINISHED !\n");
	}

	try
	{
		if (Thread2.joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Thread2.join();
		}
	}
	catch(system_error)
	{
		wprintf_s(L"THREAD [2] was NOT FINISHED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DeadlockTryLockThread1(mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [1] STARTED !\n");

	try
	{
		for(int Index=0;Index<1000*1000*10;Index++)
		{
			// !!!!! FUNCTION try_lock() vykonava algoritmus, ktory zabranuje vzniku DEADLOCK. V pripade, ze DEADLOCK je detekovany, FUNCTION vracia INDEX LOCKABLE OBJECT pre ktory sa LOCK nepodarilo ziskat. V pripade uspesneho ziskania vsetkych LOCKS FUNCTION vracia -1.
			int													NonLockedObject=try_lock(Mutex1,Mutex2);

			if (NonLockedObject==-1)
			{
				Mutex2.unlock();

				Mutex1.unlock();
			}
			else
			{
				if (NonLockedObject==0)
				{
					// !!! FUNCTION try_lock() UVOLNI VSETKY LOCKS, takze uz sa NESMU v CODE uvolnit.

					wprintf_s(L"THREAD [1] - DEADLOCK DETECTED - INDEX 0 !\n");
					break;
				}
				else if (NonLockedObject==1)
				{
					// !!! FUNCTION try_lock() UVOLNI VSETKY LOCKS, takze uz sa NESMU v CODE uvolnit.

					wprintf_s(L"THREAD [1] - DEADLOCK DETECTED - INDEX 1 !\n");
					break;
				}
				else
				{
					wprintf_s(L"THREAD [1] - DEADLOCK DETECTED - ERROR because CODE should NEVER get there !\n");
					break;
				}
			}
		}
	}
	catch(const system_error& E)
	{
		printf_s("THREAD [1] - MUTEX EXCEPTION - CODE [%d], WHAT [%s] !\n",E.code().value(),E.what());

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION try_lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wprintf_s(L"THREAD [1] FINISHED !\n");
}
//-----------------------------------------------------------------------------
void DeadlockTryLockThread2(mutex& Mutex1, mutex& Mutex2)
{
	wprintf_s(L"THREAD [2] STARTED !\n");

	try
	{
		for(int Index=0;Index<1000*1000*10;Index++)
		{
			// !!!!! FUNCTION try_lock() vykonava algoritmus, ktory zabranuje vzniku DEADLOCK. V pripade, ze DEADLOCK je detekovany, FUNCTION vracia INDEX LOCKABLE OBJECT pre ktory sa LOCK nepodarilo ziskat. V pripade uspesneho ziskania vsetkych LOCKS FUNCTION vracia -1.
			int													NonLockedObject=try_lock(Mutex2,Mutex1);

			if (NonLockedObject==-1)
			{
				Mutex1.unlock();

				Mutex2.unlock();
			}
			else
			{
				if (NonLockedObject==0)
				{
					// !!! FUNCTION try_lock() UVOLNI VSETKY LOCKS, takze uz sa NESMU v CODE uvolnit.

					wprintf_s(L"THREAD [2] - DEADLOCK DETECTED - INDEX 0 !\n");
					break;
				}
				else if (NonLockedObject==1)
				{
					// !!! FUNCTION try_lock() UVOLNI VSETKY LOCKS, takze uz sa NESMU v CODE uvolnit.

					wprintf_s(L"THREAD [2] - DEADLOCK DETECTED - INDEX 0 !\n");
					break;
				}
				else
				{
					wprintf_s(L"THREAD [2] - DEADLOCK DETECTED - ERROR because CODE should NEVER get there !\n");
					break;
				}
			}
		}
	}
	catch(const system_error& E)
	{
		printf_s("THREAD [2] - MUTEX EXCEPTION - CODE [%d], WHAT [%s] !\n",E.code().value(),E.what());

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION try_lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wprintf_s(L"THREAD [2] FINISHED !\n");
}
//-----------------------------------------------------------------------------
void TestMutexErrorDeadlockTryLock(void)
{
	PrintLineSeparator();

	mutex														Mutex1;
	mutex														Mutex2;

	thread														Thread1;
	thread														Thread2;

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread1=thread(DeadlockTryLockThread1,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wprintf_s(L"MAIN THREAD [1] was NOT STARTED !\n");
	}

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread2=thread(DeadlockTryLockThread2,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wprintf_s(L"MAIN THREAD [2] was NOT STARTED !\n");
	}

	try
	{
		if (Thread1.joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Thread1.join();
		}
	}
	catch(system_error)
	{
		wprintf_s(L"THREAD [1] was NOT FINISHED !\n");
	}

	try
	{
		if (Thread2.joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Thread2.join();
		}
	}
	catch(system_error)
	{
		wprintf_s(L"THREAD [2] was NOT FINISHED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CallOnceFunction1(int Index)
{
	wprintf_s(L"!!! THREAD [%d] CALLED FUNCTION CallOnceFunction1() by call_once() FUNCTION !\n",Index);
}
//-----------------------------------------------------------------------------
void CallOnceFunction2(int Index1, int Index2)
{
	wprintf_s(L"!!! THREAD [%d,%d] CALLED FUNCTION CallOnceFunction1() by call_once() FUNCTION !\n",Index1,Index2);
}
//-----------------------------------------------------------------------------
void CallOnceCallback(int Index, once_flag& Flag)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	// Caka sa 1 sekundu.
	this_thread::sleep_until(system_clock::now()+duration<int,ratio<1,1>>(1));

	// CODE demonstruje, ze je mozne volat pomocou FUNCTION call_once() v 1 GROUP aj FUNCTIONS s ROZLICNYM PROTOTYPE.
	if ((Index % 2)==1)
	{
		call_once(Flag,CallOnceFunction1,Index);
	}
	else
	{
		call_once(Flag,CallOnceFunction2,Index,Index);
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestCallOnce(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// !!! Identifikator GROUP vsetkych FUNCTION spomedzi, ktorej sa ma zavolat iba 1 z nich.
	once_flag													Flag;
	const int													NUMBER_OF_THREADS=10;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(CallOnceCallback,(Index+1),ref(Flag));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SingleThreadCallOnceFunction1(int Index)
{
	wprintf_s(L"!!! FUNCTION SingleThreadCallOnceFunction1() with PARAMETER [%d] CALLED by call_once() FUNCTION !\n",Index);
}
//-----------------------------------------------------------------------------
void SingleThreadCallOnceFunction2(int Index1, int Index2)
{
	wprintf_s(L"!!! FUNCTION SingleThreadCallOnceFunction2() with PARAMETERS [%d,%d] CALLED by call_once() FUNCTION !\n",Index1,Index2);
}
//-----------------------------------------------------------------------------
void TestCallOnceInSingleThread(void)
{
	PrintLineSeparator();

	once_flag													Flag;

	// CODE demonstruje, ze je mozne FUNCTION once_call() zavolat aj v 1 THREAD, pricom sa uskutocni VZDY (pokial CALLABLE OBJECT nehodil EXCEPTION) iba pre PRVY zavolany CALLABLE OBJECT.
	call_once(Flag,SingleThreadCallOnceFunction1,10);

	// !!! FUNCTION SingleThreadCallOnceFunction1() sa NEZAVOLA.
	call_once(Flag,SingleThreadCallOnceFunction1,20);

	// !!! FUNCTION SingleThreadCallOnceFunction2() sa NEZAVOLA.
	call_once(Flag,SingleThreadCallOnceFunction2,30,40);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CallOnceFunctionWithoutException(int Index)
{
	wprintf_s(L"!!! THREAD [%d] CALLED this FUNCTION by call_once() FUNCTION !\n",Index);
}
//-----------------------------------------------------------------------------
void CallOnceFunctionWithException(int Index)
{
	wprintf_s(L"!!! THREAD [%d] CALLED this FUNCTION by call_once() FUNCTION ! EXCEPTION will be THROWN !\n",Index);

	throw(CException(L"Some EXCEPTION !"));
}
//-----------------------------------------------------------------------------
void CallOnceWithExceptionCallback(int Index, once_flag& Flag)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	// Caka sa 1 sekundu.
	this_thread::sleep_until(system_clock::now()+duration<int,ratio<1,1>>(1));

	try
	{
		if ((Index % 2)==1)
		{
			call_once(Flag,CallOnceFunctionWithoutException,Index);
		}
		else
		{
			// !!!!! Ak CALLABLE OBJECT hodi EXCEPTION, potom sa zavola DALSI CALLABLE OBJECT z danej GROUP.
			call_once(Flag,CallOnceFunctionWithException,Index);
		}
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"!!! THREAD [%d] DETECTED EXCEPTION [%ls] !\n",Index,Exception.GetMessage().c_str());
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestCallOnceWithException(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// !!! Identifikator GROUP vsetkych FUNCTION spomedzi, ktorej sa ma zavolat iba 1 z nich.
	once_flag													Flag;
	const int													NUMBER_OF_THREADS=6;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(CallOnceWithExceptionCallback,(Index+1),ref(Flag));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD [%d] was NOT STARTED !\n",(Index+1));
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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SingleThreadCallOnceWithoutExceptionFunction(int Index)
{
	wprintf_s(L"!!! FUNCTION SingleThreadCallOnceWithoutExceptionFunction() with PARAMETER [%d] CALLED by call_once() FUNCTION !\n",Index);
}
//-----------------------------------------------------------------------------
void SingleThreadCallOnceWithExceptionFunction(int Index)
{
	wprintf_s(L"!!! FUNCTION SingleThreadCallOnceWithExceptionFunction() with PARAMETER [%d] CALLED by call_once() FUNCTION ! EXCEPTION will be THROWN !\n",Index);

	throw(CException(L"Some EXCEPTION !"));
}
//-----------------------------------------------------------------------------
void TestCallOnceWithExceptionInSingleThread(void)
{
	PrintLineSeparator();

	once_flag													Flag;

	try
	{
		// !!! Kedze FUNCTION SingleThreadCallOnceWithExceptionFunction() hodi EXCEPTION, CALLABLE OBJECT sa povazuje za NEZAVOLANY.
		call_once(Flag,SingleThreadCallOnceWithExceptionFunction,10);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"EXCEPTION DETECTED [%ls] !\n",Exception.GetMessage().c_str());
	}

	try
	{
		// !!! Kedze FUNCTION SingleThreadCallOnceWithExceptionFunction() hodi EXCEPTION, CALLABLE OBJECT sa povazuje za NEZAVOLANY.
		call_once(Flag,SingleThreadCallOnceWithExceptionFunction,20);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"EXCEPTION DETECTED [%ls] !\n",Exception.GetMessage().c_str());
	}

	try
	{
		// !!! Kedze FUNCTION SingleThreadCallOnceWithoutExceptionFunction() NEHODI EXCEPTION, CALLABLE OBJECT sa povazuje za ZAVOLANY.
		call_once(Flag,SingleThreadCallOnceWithoutExceptionFunction,30);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"EXCEPTION DETECTED [%ls] !\n",Exception.GetMessage().c_str());
	}

	try
	{
		// !!! FUNCTION SingleThreadCallOnceWithoutExceptionFunction() sa NEZAVOLA, pretoze CALLABLE OBJECT uz BOL ZAVOLANY.
		call_once(Flag,SingleThreadCallOnceWithoutExceptionFunction,40);
	}
	catch(const CException& Exception)
	{
		wprintf_s(L"EXCEPTION DETECTED [%ls] !\n",Exception.GetMessage().c_str());
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableSetThread1(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION ineho THREADU o tom, ze CONDITIONAL VARIABLE bola nastavena.
	// !!!!! Tento CODE moze bezat s LOCKED, alebo UNLOCKED MUTEX.
	ConditionalVariable.notify_one();

	wprintf_s(L"SET THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableWaitThread1(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD STARTED !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD is WAITING !\n");

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wprintf_s(L"WAIT THREAD detected that CONDITIONAL VARIABLE has been SET !\n");
	}

	wprintf_s(L"WAIT THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
void TestNotifyOneConditionalVariable1(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=2;
	thread														Threads[NUMBER_OF_THREADS]{thread(NotifyOneConditionalVariableSetThread1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyOneConditionalVariableWaitThread1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableSetThread2(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;

		// !!! Vykona sa NOTIFICATION ineho THREADU o tom, ze CONDITIONAL VARIABLE bola nastavena.
		// !!!!! Tento CODE moze bezat s LOCKED, alebo UNLOCKED MUTEX.
		ConditionalVariable.notify_one();
	}

	wprintf_s(L"SET THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableWaitThread2(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD STARTED !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD is WAITING !\n");

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wprintf_s(L"WAIT THREAD detected that CONDITIONAL VARIABLE has been SET !\n");
	}

	wprintf_s(L"WAIT THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
void TestNotifyOneConditionalVariable2(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=2;
	thread														Threads[NUMBER_OF_THREADS]{thread(NotifyOneConditionalVariableSetThread2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyOneConditionalVariableWaitThread2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION VSETKYCH OSTATNYCH THREADS o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_all();

	wprintf_s(L"SET THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wprintf_s(L"WAIT THREAD [%d] detected that CONDITIONAL VARIABLE has been SET !\n",Index);
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestNotifyAllConditionalVariable(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=4;
	thread														Threads[NUMBER_OF_THREADS]{thread(NotifyAllConditionalVariableSetThread,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyAllConditionalVariableWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyAllConditionalVariableWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyAllConditionalVariableWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION 1. THREAD o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_one();

	wprintf_s(L"SET THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!!!! METHOD condition_variable::wait_for() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_for() VZDY vrati TRUE, pretoze aj ked TIMEOUT EXPIROVAL, tak CONDITION VARIABLE uz BOLA NASTAVENA a CALLABLE OBJECT vratil TRUE.
		bool													LockAcquired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wprintf_s(L"WAIT THREAD [%d] detected that CONDITIONAL VARIABLE has been SET !\n",Index);
		}
		else
		{
			wprintf_s(L"!!!!! WAIT THREAD [%d] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !\n",Index);
		}
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestWaitForConditionalVariable(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=4;
	thread														Threads[NUMBER_OF_THREADS]{thread(WaitForConditionalVariableSetThread,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitForConditionalVariableWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitForConditionalVariableWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitForConditionalVariableWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NoWakeUpWaitForConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!!!! METHOD condition_variable::wait_for() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_for() VZDY vrati FALSE, pretoze THREAD, ktory by nastavoval CONDITIONAL VARIABLE NEBOL VYTVORENY a tak CONDITIONAL VARIABLE NIKDY NEMOZE byt SIGNALIZED.
		bool													LockAcquired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wprintf_s(L"WAIT THREAD [%d] detected that CONDITIONAL VARIABLE has been SET !\n",Index);
		}
		else
		{
			wprintf_s(L"!!!!! WAIT THREAD [%d] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !\n",Index);
		}
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestNoWakeUpWaitForConditionalVariable(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=3;
	thread														Threads[NUMBER_OF_THREADS]{thread(NoWakeUpWaitForConditionalVariableWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NoWakeUpWaitForConditionalVariableWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NoWakeUpWaitForConditionalVariableWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForWithSpuriousWakeupsConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION 1. THREAD o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_one();

	wprintf_s(L"SET THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForWithSpuriousWakeupsConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!!!! Tato OVERLOADED verzia METHOD condition_variable::wait_for() kedze NEMA ako PARAMETER CALLABLE OBJECT, ktory by detekoval vznik SPURIOUS CALLS, moze byt ukocena aj ked CONDITIONAL VARIABLE NEBOLA NASTAVENA.
		// !!!!! Vdaka SPURIOUS WAKEUPS je RETURN VALUE znacne NESPOLAHLIVA a niekedy vracala FALSE, aj ked REALNE TIMEOUT EXPIROVAL. V CYGWIN naopak RETURN VALUE mala VZDY SPRAVNU hodnotu.
		bool													TimeoutExpired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6))==cv_status::timeout;

		wprintf_s(L"WAIT THREAD [%d] FINISHED WAITING ! ConditionalVariableFlag [%ls], TimeoutExpired [%ls] !\n",Index,(ConditionalVariableFlag) ? L"TRUE" : L"FALSE",(TimeoutExpired) ? L"TRUE" : L"FALSE");
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestWaitForWithSpuriousWakeupsConditionalVariable(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=4;
	thread														Threads[NUMBER_OF_THREADS]{thread(WaitForWithSpuriousWakeupsConditionalVariableSetThread,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitForWithSpuriousWakeupsConditionalVariableWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitForWithSpuriousWakeupsConditionalVariableWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitForWithSpuriousWakeupsConditionalVariableWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void WaitUntilConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION 1. THREAD o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_one();

	wprintf_s(L"SET THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void WaitUntilConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!!!! METHOD condition_variable::wait_until() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_until() VZDY vrati TRUE, pretoze aj ked TIMEOUT EXPIROVAL, tak CONDITION VARIABLE uz BOLA NASTAVENA a CALLABLE OBJECT vratil TRUE.
		bool													LockAcquired=ConditionalVariable.wait_until(Lock,system_clock::now()+duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wprintf_s(L"WAIT THREAD [%d] detected that CONDITIONAL VARIABLE has been SET !\n",Index);
		}
		else
		{
			wprintf_s(L"!!!!! WAIT THREAD [%d] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !\n",Index);
		}
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestWaitUntilConditionalVariable(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=4;
	thread														Threads[NUMBER_OF_THREADS]{thread(WaitUntilConditionalVariableSetThread,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitUntilConditionalVariableWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitUntilConditionalVariableWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(WaitUntilConditionalVariableWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NoWakeUpWaitUntilConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!!!! METHOD condition_variable::wait_until() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_until() VZDY vrati FALSE, pretoze THREAD, ktory by nastavoval CONDITIONAL VARIABLE NEBOL VYTVORENY a tak CONDITIONAL VARIABLE NIKDY NEMOZE byt SIGNALIZED.
		bool													LockAcquired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wprintf_s(L"WAIT THREAD [%d] detected that CONDITIONAL VARIABLE has been SET !\n",Index);
		}
		else
		{
			wprintf_s(L"!!!!! WAIT THREAD [%d] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !\n",Index);
		}
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestNoWakeUpWaitUntilConditionalVariable(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=3;
	thread														Threads[NUMBER_OF_THREADS]{thread(NoWakeUpWaitUntilConditionalVariableWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NoWakeUpWaitUntilConditionalVariableWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NoWakeUpWaitUntilConditionalVariableWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllAtThreadExitConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;

		// !!! Na KONCI THREAD sa vykona NOTIFICATION VSETKYCH OSTATNYCH THREADS o tom, ze CONDITIONAL VARIABLE bola nastavena.
		// !!!!! 2. PARAMETER je NUTNE cez MOVE SEMANTICS pomocou FUNCTION move(), pretoze FUNCTION notify_all_at_thread_exit() na konci THREAD zavola CODE, ktory pouzivat LOCK a tento NESMIE byt UVOLNENY.
		// !!!!! Vdaka pouzitiu MOVE SEMANTICS, LOCK NEBUDE na konci tohto SCOPE ODSTRANENY, ale az na KONCI THREAD.
		notify_all_at_thread_exit(ConditionalVariable,move(Lock));
	}

	wprintf_s(L"!!! SET THREAD SET CONDITIONAL VARIABLE !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD FINISHED !\n");

	// !!! Az PO SKONCENI THREAD budu WAIT THREADS prebudene.
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllAtThreadExitConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wprintf_s(L"WAIT THREAD [%d] detected that CONDITIONAL VARIABLE has been SET !\n",Index);
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestNotifyAllAtThreadExitConditionalVariable(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable											ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=4;
	thread														Threads[NUMBER_OF_THREADS]{thread(NotifyAllAtThreadExitConditionalVariableSetThread,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyAllAtThreadExitConditionalVariableWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyAllAtThreadExitConditionalVariableWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(NotifyAllAtThreadExitConditionalVariableWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void ConditionalVariableAnySetThread(mutex& Mutex, condition_variable_any& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"SET THREAD STARTED !\n");

	wprintf_s(L"SET THREAD is SLEEPING !\n");

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"SET THREAD WOKE UP !\n");

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION VSETKYCH OSTATNYCH THREADS o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_all();

	wprintf_s(L"SET THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void ConditionalVariableAnyWaitThread(int Index, mutex& Mutex, condition_variable_any& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wprintf_s(L"WAIT THREAD [%d] STARTED !\n",Index);

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wprintf_s(L"WAIT THREAD [%d] is WAITING !\n",Index);

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wprintf_s(L"WAIT THREAD [%d] detected that CONDITIONAL VARIABLE has been SET !\n",Index);
	}

	wprintf_s(L"WAIT THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestConditionalVariableAny(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// MUTEX pre CONDITIONAL VARIABLE.
	mutex														Mutex;
	// CONDITIONAL VARIABLE.
	condition_variable_any										ConditionalVariable;
	// VARIABLE vyjadrujuca podmienku, kedy je CONDITIONAL VARIABLE SIGNALIZED.
	bool														ConditionalVariableFlag=false;

	const int													NUMBER_OF_THREADS=4;
	thread														Threads[NUMBER_OF_THREADS]{thread(ConditionalVariableAnySetThread,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(ConditionalVariableAnyWaitThread,1,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(ConditionalVariableAnyWaitThread,2,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag)),thread(ConditionalVariableAnyWaitThread,3,ref(Mutex),ref(ConditionalVariable),ref(ConditionalVariableFlag))};

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
			wprintf_s(L"MAIN THREAD [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring GetTime(void)
{
	time_t														CurrentTime=time(nullptr);
	tm															LocalTime=*localtime(&CurrentTime);
	const int													BUFFER_SIZE=200;
	wchar_t														Buffer[BUFFER_SIZE];
	
	swprintf(Buffer,BUFFER_SIZE,L"TIME [%02d:%02d:%02d]",LocalTime.tm_hour,LocalTime.tm_min,LocalTime.tm_sec);

	wstring														Result(Buffer);

	return(Result);
}
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackReturningResultAndSignalizing(promise<int>& Promise, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	int															Result=Index*2;

	wprintf_s(L"%ls THREAD [%d] SET RESULT !\n",GetTime().c_str(),Index);

	// !!! OKAMZITE po nastaveni RESULT je PROMISE SIGNALIZED.
	Promise.set_value(Result);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls THREAD [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseReturningResultAndSignalizing(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

	const int													NUMBER_OF_THREADS=3;
	promise<int>												Promises[NUMBER_OF_THREADS];
	// !!!!! FUTURE vytvorena z daneho PROMISE spolocne zdiela TEN ISTY SHARED STATE. Tento SHARED STATE je mozne pouzit na prenos VALUE, alebo EXCEPTION medzi TASKS.
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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT STARTED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

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

					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
				}
				catch(const CException& E)
				{
					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with EXCEPTION [%ls] !\n",GetTime().c_str(),(Index+1),E.GetMessage().c_str());
				}
			}
		}
		catch(system_error)
		{
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackThrowingExceptionAndSignalizing(promise<int>& Promise, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	try
	{
		throw(CException(L"SOME EXCEPTION !"));
	}
	catch(CException)
	{
		wprintf_s(L"%ls THREAD [%d] SET EXCEPTION !\n",GetTime().c_str(),Index);

		// !!! FUNCTION current_exception() vracia EXCEPTION asociovanu s EXCEPTION BLOCK.
		// !!! OKAMZITE po nastaveni EXCEPTION je PROMISE SIGNALIZED.
		Promise.set_exception(current_exception());
	}

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls THREAD [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseThrowingExceptionAndSignalizing(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT STARTED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

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

					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
				}
				catch(const CException& E)
				{
					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with EXCEPTION [%ls] !\n",GetTime().c_str(),(Index+1),E.GetMessage().c_str());
				}
			}
		}
		catch(system_error)
		{
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackReturningResultButNotSignalizing(promise<int>& Promise, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	int															Result=Index*2;

	wprintf_s(L"%ls THREAD [%d] SET RESULT !\n",GetTime().c_str(),Index);

	// !!! Nastavi RESULT, ale PROMISE NIE JE SIGNALIZED az kym sa CURRENT THREAD NESKONCI.
	Promise.set_value_at_thread_exit(Result);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls THREAD [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseReturningResultButNotSignalizing(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT STARTED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

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

					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
				}
				catch(const CException& E)
				{
					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with EXCEPTION [%ls] !\n",GetTime().c_str(),(Index+1),E.GetMessage().c_str());
				}
			}
		}
		catch(system_error)
		{
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! PROMISES sa MUSIA prenasat ako BY-REFERENCE PARAMETERS.
void PromiseCallbackThrowingExceptionButNotSignalizing(promise<int>& Promise, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	try
	{
		throw(CException(L"SOME EXCEPTION !"));
	}
	catch(CException)
	{
		wprintf_s(L"%ls THREAD [%d] SET EXCEPTION !\n",GetTime().c_str(),Index);

		// !!! FUNCTION current_exception() vracia EXCEPTION asociovanu s EXCEPTION BLOCK.
		// !!! Nastavi EXCEPTION, ale PROMISE NIE JE SIGNALIZED az kym sa CURRENT THREAD NESKONCI.
		Promise.set_exception_at_thread_exit(current_exception());
	}

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls THREAD [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestThreadsWithPromiseThrowingExceptionButNotSignalizing(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT STARTED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

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

					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
				}
				catch(const CException& E)
				{
					wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with EXCEPTION [%ls] !\n",GetTime().c_str(),(Index+1),E.GetMessage().c_str());
				}
			}
		}
		catch(system_error)
		{
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
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
			wprintf_s(L"%ls MAIN THREAD [%d] was NOT FINISHED !\n",GetTime().c_str(),(Index+1));
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PackagedTaskCallback(int Index)
{
	wprintf_s(L"%ls PACKAGED TASK [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls PACKAGED TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskCallback(packaged_task<void(int)>& PackagedTask, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou OPERATOR().
	PackagedTask(Index);

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] PACKAGED TASK FINISHED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestPackagedTasks(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wprintf_s(L"%ls MAIN AFTER GET !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithResultCallback(int Index)
{
	wprintf_s(L"%ls PACKAGED TASK [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls PACKAGED TASK [%d] FINISHED !\n",GetTime().c_str(),Index);

	int															Result=Index*2;

	return(Result);
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskWithResultCallback(packaged_task<int(int)>& PackagedTask, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou OPERATOR().
	PackagedTask(Index);

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] PACKAGED TASK FINISHED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithResult(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		int														Result=Tasks[Index].get();

		wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
	}

	wprintf_s(L"%ls MAIN AFTER GET !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithExceptionCallback(int Index)
{
	wprintf_s(L"%ls PACKAGED TASK [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls PACKAGED TASK [%d] FINISHED !\n",GetTime().c_str(),Index);

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
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou OPERATOR().
	PackagedTask(Index);

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] PACKAGED TASK FINISHED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithException(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
			int													Result=Tasks[Index].get();

			wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
		}
		catch(const CException& E)
		{
			wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with EXCEPTION [%ls] !\n",GetTime().c_str(),(Index+1),E.GetMessage().c_str());
		}
	}

	wprintf_s(L"%ls MAIN AFTER GET !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void PackagedTaskAtAndOfThreadCallback(int Index)
{
	wprintf_s(L"%ls PACKAGED TASK [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls PACKAGED TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskAtAndOfThreadCallback(packaged_task<void(int)>& PackagedTask, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou METHOD packaged_task::make_ready_at_thread_exit().
	PackagedTask.make_ready_at_thread_exit(Index);

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] PACKAGED TASK FINISHED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestPackagedTasksAtAndOfThread(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wprintf_s(L"%ls MAIN AFTER GET !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithResultAtAndOfThreadCallback(int Index)
{
	wprintf_s(L"%ls PACKAGED TASK [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls PACKAGED TASK [%d] FINISHED !\n",GetTime().c_str(),Index);

	int															Result=Index*2;

	return(Result);
}
//-----------------------------------------------------------------------------
// !!! Toto je THREAD CODE. THREAD je nutne EXPLICITNE vytvorit v CODE.
void ThreadCodePackagedTaskWithResultAtAndOfThreadCallback(packaged_task<int(int)>& PackagedTask, int Index)
{
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou METHOD packaged_task::make_ready_at_thread_exit().
	PackagedTask.make_ready_at_thread_exit(Index);

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] PACKAGED TASK FINISHED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithResultAtAndOfThread(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		int														Result=Tasks[Index].get();

		wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
	}

	wprintf_s(L"%ls MAIN AFTER GET !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PackagedTaskWithExceptionAtAndOfThreadCallback(int Index)
{
	wprintf_s(L"%ls PACKAGED TASK [%d] STARTED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"%ls PACKAGED TASK [%d] FINISHED !\n",GetTime().c_str(),Index);

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
	wprintf_s(L"%ls THREAD [%d] STARTED !\n",GetTime().c_str(),Index);

	// !!!!! PACKAGED TASK je NUTNE spustit EXPLICITNE pomocou METHOD packaged_task::make_ready_at_thread_exit().
	PackagedTask.make_ready_at_thread_exit(Index);

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] PACKAGED TASK FINISHED !\n",GetTime().c_str(),Index);

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"!!!!! %ls THREAD TASK [%d] FINISHED !\n",GetTime().c_str(),Index);
}
//-----------------------------------------------------------------------------
void TestPackagedTasksWithExceptionAtAndOfThread(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

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

	wprintf_s(L"%ls MAIN BEFORE WAIT !\n",GetTime().c_str());

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"%ls MAIN AFTER WAIT !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// !!! Pocka sa kym THREAD nenastavi cez PROMISE RESULT, alebo EXCEPTION.
			int													Result=Tasks[Index].get();

			wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",GetTime().c_str(),(Index+1),Result);
		}
		catch(const CException& E)
		{
			wprintf_s(L"%ls MAIN - TASK [%d] FINISHED with EXCEPTION [%ls] !\n",GetTime().c_str(),(Index+1),E.GetMessage().c_str());
		}
	}

	wprintf_s(L"%ls MAIN AFTER GET !\n",GetTime().c_str());

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		if (Threads[Index].joinable()==true)
		{
			// !!! Pocka sa na skoncenie THREAD.
			Threads[Index].join();
		}
	}

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int MyTask1(void)
{
	wprintf_s(L"TASK [1] STARTED !\n");

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"TASK [1] FINISHED !\n");

	return(100);
}
//-----------------------------------------------------------------------------
int MyTask2(void)
{
	wprintf_s(L"TASK [2] STARTED !\n");

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wprintf_s(L"TASK [2] FINISHED !\n");

	return(100);
}
//-----------------------------------------------------------------------------
// !!!!! CODE UMYSELNE sposobuje NEKONECNE CAKANIE.
void TestRunPackagedTasks(void)
{
	PrintLineSeparator();

	wprintf_s(L"%ls MAIN STARTED !\n",GetTime().c_str());

	packaged_task<int(void)>									PackagedTask1(MyTask1);

	wprintf_s(L"PACKAGED TASK CREATED !\n");

	// !!! Spusti TASK CODE v CURRENT THREAD.
	PackagedTask1();

	wprintf_s(L"PACKAGED TASK AFTER OPERATOR() CALLED !\n");

	future<int>													ResultTask1=PackagedTask1.get_future();

	wprintf_s(L"PACKAGED TASK AFTER FUTURE CREATED !\n");

	// !!! Caka na ukoncenie TASK CODE.
	wprintf_s(L"PACKAGED TASK RESULT [%d] !\n",ResultTask1.get());

	wprintf_s(L"PACKAGED TASK AFTER FUTURE::GET() CALLED !\n");

	/*
	PrintLineSeparator();

	packaged_task<int(void)>									PackagedTask2(MyTask2);

	wprintf_s(L"PACKAGED TASK CREATED !\n");

	future<int>													ResultTask2=PackagedTask2.get_future();

	wprintf_s(L"PACKAGED TASK AFTER FUTURE CREATED !\n");

	// !!! Caka na ukoncenie TASK CODE.
	// !!!!! Kedze TASK CODE NEBOL EXPLICITNE SPUSTENY volanim OPERATOR(), tak sa TASK CODE NIKDY NEVYKONA a CURRENT THREAD ostane TRVALO BLOCKED.
	wprintf_s(L"PACKAGED TASK RESULT [%d] !\n",ResultTask2.get());

	wprintf_s(L"PACKAGED TASK AFTER FUTURE::GET() CALLED !\n");

	wprintf_s(L"%ls MAIN FINISHED !\n",GetTime().c_str());
	*/

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TaskCallback(int Index)
{
	wprintf_s(L"TASK [%d] STARTED !\n",Index);

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wprintf_s(L"TASK [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestMultipleTasks(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_TASKS=10;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallback,(Index+1));
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int TaskCallbackWithResult(int Index)
{
	int															Result=Index*2;

	wprintf_s(L"TASK [%d] STARTED !\n",Index);

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wprintf_s(L"TASK [%d] FINISHED !\n",Index);

	return(Result);
}
//-----------------------------------------------------------------------------
void TestMultipleTasksWithResult(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_TASKS=5;
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallbackWithResult,(Index+1));
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		int														Result=Tasks[Index].get();

		wprintf_s(L"MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",(Index+1),Result);
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int TaskCallbackWithResultOrException(int Index)
{
	int															Result=Index*2;

	wprintf_s(L"TASK [%d] STARTED !\n",Index);

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	if ((Index%2)!=0)
	{
		wprintf_s(L"TASK [%d] FINISHED !\n",Index);
	}
	else
	{
		wprintf_s(L"!!! TASK [%d] FINISHED throwing EXCEPTION !\n",Index);

		throw(CException(L"SOME EXCEPTION !"));
	}

	return(Result);
}
//-----------------------------------------------------------------------------
void TestMultipleTasksWithResultOrException(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_TASKS=5;
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallbackWithResultOrException,(Index+1));
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
			int													Result=Tasks[Index].get();

			wprintf_s(L"MAIN - TASK [%d] FINISHED with RESULT [%d] !\n",(Index+1),Result);
		}
		catch(const CException& E)
		{
			wprintf_s(L"MAIN - TASK [%d] FINISHED with EXCEPTION [%ls] !\n",(Index+1),E.GetMessage().c_str());
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleTaskFunctors(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_TASKS=5;
	future<void>												Tasks[NUMBER_OF_TASKS];
	CTaskFunctor												TaskObjects[NUMBER_OF_TASKS]{CTaskFunctor(1001),CTaskFunctor(1002),CTaskFunctor(1003),CTaskFunctor(1004),CTaskFunctor(1005)};

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!!!! Ak sa pouziva OPERATOR() ako CALLBACK FUNCTION, je NUTNE ako 2. PARAMETER preniest THIS OBJECT.
		Tasks[Index]=async(&CTaskFunctor::operator(),&TaskObjects[Index],(Index+1));
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWait(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	future<int>													TaskWithResult=async(TaskCallbackWithResult,100);
	future<int>													TaskWithException=async(TaskCallbackWithResultOrException,200);

	try
	{
		TaskWithResult.wait();

		wprintf_s(L"MAIN - TASK with RESULT FINISHED SUCCESSFULLY !\n");
	}
	catch(const CException& E)
	{
		wprintf_s(L"MAIN - TASK with RESULT FINISHED with EXCEPTION [%ls] !\n",E.GetMessage().c_str());
	}

	try
	{
		// !!!!! Ak TASK hodi EXCEPTION, potom METHOD future<T>::wait() tuto EXCEPTION NEHODI.
		TaskWithException.wait();

		// !!! CODE SKONCI v tomto mieste.
		wprintf_s(L"MAIN - TASK with EXCEPTION FINISHED SUCCESSFULLY !\n");
	}
	catch(const CException& E)
	{
		// !!! Sem sa CODE NIKDY NEDOSTANE.
		wprintf_s(L"MAIN - TASK with EXCEPTION FINISHED with EXCEPTION [%ls] !\n",E.GetMessage().c_str());
	}

	wprintf_s(L"BEFORE GET - TASK with RESULT VALIDITY [%ls] !\n",(TaskWithResult.valid()==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"BEFORE GET - TASK with EXCEPTION VALIDITY [%ls] !\n",(TaskWithException.valid()==true) ? L"TRUE" : L"FALSE");

	try
	{
		int														Result=TaskWithResult.get();

		wprintf_s(L"MAIN - METHOD GET - TASK with RESULT has RESULT [%d] !\n",Result);
	}
	catch(const CException& E)
	{
		wprintf_s(L"MAIN - METHOD GET - TASK with RESULT FINISHED with EXCEPTION [%ls] !\n",E.GetMessage().c_str());
	}

	try
	{
		int														Result=TaskWithException.get();

		wprintf_s(L"MAIN - METHOD GET - TASK with EXCEPTION has RESULT [%d] !\n",Result);
	}
	catch(const CException& E)
	{
		wprintf_s(L"MAIN - METHOD GET - TASK with EXCEPTION FINISHED with EXCEPTION [%ls] !\n",E.GetMessage().c_str());
	}

	wprintf_s(L"AFTER GET - TASK with RESULT VALIDITY [%ls] !\n",(TaskWithResult.valid()==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"AFTER GET - TASK with EXCEPTION VALIDITY [%ls] !\n",(TaskWithException.valid()==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitFor1(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	future<void>												TaskAsync=async(launch::async,TaskCallback,100);
	future<void>												TaskDeferred=async(launch::deferred,TaskCallback,200);
	future_status												TaskAsyncStatus=TaskAsync.wait_for(duration<int,ratio<1,1000>>(500));

	if (TaskAsyncStatus==future_status::ready)
	{
		wprintf_s(L"TASK [100] (ASYNC) FINISHED !\n");
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wprintf_s(L"TASK [100] (ASYNC) hasn't STARTED !\n");
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wprintf_s(L"TASK [100] (ASYNC) STARTED but hasn't FINISHED !\n");
	}

	future_status												TaskDeferredStatus=TaskDeferred.wait_for(duration<int,ratio<1,1000>>(500));

	if (TaskDeferredStatus==future_status::ready)
	{
		wprintf_s(L"TASK [200] (DEFERRED) FINISHED !\n");
	}
	else if (TaskDeferredStatus==future_status::deferred)
	{
		wprintf_s(L"TASK [200] (DEFERRED) hasn't STARTED !\n");
	}
	else if (TaskDeferredStatus==future_status::timeout)
	{
		wprintf_s(L"TASK [200] (DEFERRED) STARTED but hasn't FINISHED !\n");
	}

	TaskAsync.get();
	TaskDeferred.get();

	// !!!!! Po zavolani METHOD future<T>::get() uz NIE JE MOZNE volat METHOD future<T>::wait_for(), pretoze TASK uz NIE JE VALIDNY.

	wprintf_s(L"AFTER GET - TASK [100] (ASYNC) VALIDITY [%ls] !\n",(TaskAsync.valid()==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"AFTER GET - TASK [200] (DEFERRED) VALIDITY [%ls] !\n",(TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitFor2(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	future<int>													TaskWithException=async(TaskCallbackWithResultOrException,100);

	// !!! Pocka sa dostatocne dlhu dobu na skoncenie TASK.
	// !!! Aj ked TASK HODIL EXCEPTION, METHOD future<T>::wait_for() EXCEPTION NEHADZE.
	future_status												TaskAsyncStatus=TaskWithException.wait_for(duration<int,ratio<1,1>>(10));

	if (TaskAsyncStatus==future_status::ready)
	{
		wprintf_s(L"TASK [100] FINISHED !\n");
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wprintf_s(L"TASK [100] hasn't STARTED !\n");
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wprintf_s(L"TASK [100] STARTED but hasn't FINISHED !\n");
	}

	try
	{
		int														Result=TaskWithException.get();

		wprintf_s(L"MAIN - METHOD GET - TASK [100] has RESULT [%d] !\n",Result);
	}
	catch(const CException& E)
	{
		wprintf_s(L"MAIN - METHOD GET - TASK [100] FINISHED with EXCEPTION [%ls] !\n",E.GetMessage().c_str());
	}

	wprintf_s(L"AFTER GET - TASK [100] VALIDITY [%ls] !\n",(TaskWithException.valid()==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitUntil1(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	future<void>												TaskAsync=async(launch::async,TaskCallback,100);
	future<void>												TaskDeferred=async(launch::deferred,TaskCallback,200);
	future_status												TaskAsyncStatus=TaskAsync.wait_until(system_clock::now()+duration<int,ratio<1,1000>>(500));
	
	if (TaskAsyncStatus==future_status::ready)
	{
		wprintf_s(L"TASK [100] (ASYNC) FINISHED !\n");
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wprintf_s(L"TASK [100] (ASYNC) hasn't STARTED !\n");
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wprintf_s(L"TASK [100] (ASYNC) STARTED but hasn't FINISHED !\n");
	}

	future_status												TaskDeferredStatus=TaskDeferred.wait_until(system_clock::now()+duration<int,ratio<1,1000>>(500));

	if (TaskDeferredStatus==future_status::ready)
	{
		wprintf_s(L"TASK [200] (DEFERRED) FINISHED !\n");
	}
	else if (TaskDeferredStatus==future_status::deferred)
	{
		wprintf_s(L"TASK [200] (DEFERRED) hasn't STARTED !\n");
	}
	else if (TaskDeferredStatus==future_status::timeout)
	{
		wprintf_s(L"TASK [200] (DEFERRED) STARTED but hasn't FINISHED !\n");
	}

	TaskAsync.get();
	TaskDeferred.get();

	// !!!!! Po zavolani METHOD future<T>::get() uz NIE JE MOZNE volat METHOD future<T>::wait_until(), pretoze TASK uz NIE JE VALIDNY.

	wprintf_s(L"AFTER GET - TASK [100] (ASYNC) VALIDITY [%ls] !\n",(TaskAsync.valid()==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"AFTER GET - TASK [200] (DEFERRED) VALIDITY [%ls] !\n",(TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitUntil2(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	future<int>													TaskWithException=async(TaskCallbackWithResultOrException,100);

	// !!! Pocka sa dostatocne dlhu dobu na skoncenie TASK.
	// !!! Aj ked TASK HODIL EXCEPTION, METHOD future<T>::wait_until() EXCEPTION NEHADZE.
	future_status												TaskAsyncStatus=TaskWithException.wait_until(system_clock::now()+duration<int,ratio<1,1>>(10));

	if (TaskAsyncStatus==future_status::ready)
	{
		wprintf_s(L"TASK [100] FINISHED !\n");
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wprintf_s(L"TASK [100] hasn't STARTED !\n");
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wprintf_s(L"TASK [100] STARTED but hasn't FINISHED !\n");
	}

	try
	{
		int														Result=TaskWithException.get();

		wprintf_s(L"MAIN - METHOD GET - TASK [100] has RESULT [%d] !\n",Result);
	}
	catch(const CException& E)
	{
		wprintf_s(L"MAIN - METHOD GET - TASK [100] FINISHED with EXCEPTION [%ls] !\n",E.GetMessage().c_str());
	}

	wprintf_s(L"AFTER GET - TASK [100] VALIDITY [%ls] !\n",(TaskWithException.valid()==true) ? L"TRUE" : L"FALSE");

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring TaskSharedFutureCallback(wstring Text)
{
	wprintf_s(L"SHARED FUTURE TASK [%ls] STARTED !\n",Text.c_str());

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wprintf_s(L"SHARED FUTURE TASK [%ls] FINISHED !\n",Text.c_str());

	return(Text);
}
//-----------------------------------------------------------------------------
// !!! SHARED FUTURE sa prenasa BY-VALUE a NIE BY-REFERENCE.
void TaskFutureCallback(shared_future<wstring> SharedFuture, int Index)
{
	wprintf_s(L"TASK [%d] STARTED !\n",Index);

	// !!! Caka sa na ukoncenie SHARED FUTURE. Kedze sa pouzila SHARED FUTURE je METHOD shared_future<wstring>::get() mozne volat VIACKRAT.
	wstring														Text=SharedFuture.get();

	wprintf_s(L"TASK [%d] FINISHED with RESULT [%ls] !\n",Index,Text.c_str());
}
//-----------------------------------------------------------------------------
void TestSharedFutures(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// !!! Vytvori sa SHARED FUTURE.
	shared_future<wstring>										SharedFuture=async(TaskSharedFutureCallback,L"Timmy Anderson").share();

	const int													NUMBER_OF_TASKS=5;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskFutureCallback,SharedFuture,(Index+1));
	}

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskDestructor(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_TASKS=10;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallback,(Index+1));
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN FINISHED !\n");

	// !!! PROGRAM NESKONCI SKOR, kym NESKONCIA VSETKY TASKS.

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTasksLaunchAsync(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_TASKS=10000;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// Vytvori TASK.
			// !!! FLAG [launch::async] PRIKAZUJE C++ spustit TASK OKAMZITE.
			// !!!!! Ak SYSTEM nema dost RESOURCES, mal byt hodit EXCEPTION [system_error].
			// !!!!! WINDOWS akceptoval vsetkych 10000 TASKS, zatial co v G++ po spusteni 1024 TASKS doslo k hodeniu EXCEPTIONS [system_error] pre dalsie TASKS.
			Tasks[Index]=async(launch::async,TaskCallback,(Index+1));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN TASK [%d] was NOT STARTED !\n",(Index+1));
		}
		catch(exception)
		{
			wprintf_s(L"MAIN TASK [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
			// !!!!! Ak TASK NEBOL STARTED, pretoze CONSTRUCTOR hodil EXCEPTION, hodi aj METHOD future<T>::get() EXCEPTION [system_error].
			Tasks[Index].get();
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN TASK [%d] was NOT FINISHED !\n",(Index+1));
		}
		catch(exception)
		{
			wprintf_s(L"MAIN TASK [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTasksLaunchDeferred(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	const int													NUMBER_OF_TASKS=5;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// Vytvori TASK.
			// !!! FLAG [launch::deferred] zabranuje C++ spustit TASK OKAMZITE. Ten sa spusti AZ pri volani METHOD future<T>::get().
			Tasks[Index]=async(launch::deferred,TaskCallback,(Index+1));
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN TASK [%d] was NOT STARTED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN BEFORE WAIT !\n");

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wprintf_s(L"MAIN AFTER WAIT !\n");

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// !!! Kedze TASK NEBOL vdaka pouzitiu VALUE [launch::deferred] SPUSTENY, tak sa spusti az TERAZ.
			// !!!!! Ak by sa METHOD future<T>::get() VOBEC NEZAVOLALA, potom by DESTRUCTOR CLASS [future<T>] iba uvolnil tuto instanciu, BEZ vykonania THREAD BLOCKING. TASK by sa jednoducho NIKDY NESPUSTIL.
			Tasks[Index].get();
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN TASK [%d] was NOT FINISHED !\n",(Index+1));
		}
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskValidity(void)
{
	PrintLineSeparator();

	future<void>												TaskAsync=async(launch::async,TaskCallback,100);
	future<void>												TaskDeferred=async(launch::deferred,TaskCallback,200);

	wprintf_s(L"BEFORE GET - TASK ASYNC VALIDITY [%ls] !\n",(TaskAsync.valid()==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"BEFORE GET - TASK DEFERRED VALIDITY [%ls] !\n",(TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE");

	TaskAsync.get();
	TaskDeferred.get();

	wprintf_s(L"AFTER GET - TASK ASYNC VALIDITY [%ls] !\n",(TaskAsync.valid()==true) ? L"TRUE" : L"FALSE");
	wprintf_s(L"AFTER GET - TASK DEFERRED VALIDITY [%ls] !\n",(TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE");

	// !!!!! Pokus o volanie METHOD future<T>::get() by viedol k UNDEFINED BEHAVIOR.

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
	//TestThreadIDs();
	//TestBackgroundThreads();
	//TestBackgroundThreadsExit();
	//TestBackgroundThreadsQuickExit();
	//TestClassThreadLocal();
	//TestFunctionThreadLocal();
	//TestGlobalThreadLocal();
	//TestComplexClassThreadLocal();
	//TestMutex();
	//TestRecursiveMutex();
	//TestMutexErrorRecursiveLock();
	//TestMutexErrorDeadlock();
	//TestTriedForTimedMutex();
	//TestTriedUntilTimedMutex();
	//TestLockFunction();
	//TestLockFunctionUsingLock();
	//TestTryLockFunction();
	//TestUniqueLock();
	//TestDeferredUniqueLock();
	//TestTryLockUniqueLockFunction();
	//TestDurationUniqueLockFunction();
	//TestMutexErrorDeadlockLock();
	//TestMutexErrorDeadlockTryLock();
	//TestCallOnce();
	//TestCallOnceInSingleThread();
	//TestCallOnceWithException();
	//TestCallOnceWithExceptionInSingleThread();
	//TestNotifyOneConditionalVariable1();
	//TestNotifyOneConditionalVariable2();
	//TestNotifyAllConditionalVariable();
	//TestWaitForConditionalVariable();
	//TestNoWakeUpWaitForConditionalVariable();
	//TestWaitForWithSpuriousWakeupsConditionalVariable();
	//TestWaitUntilConditionalVariable();
	//TestWaitUntilConditionalVariable();
	//TestNoWakeUpWaitUntilConditionalVariable();
	//TestNotifyAllAtThreadExitConditionalVariable();
	//TestConditionalVariableAny();
	//TestThreadsWithPromiseReturningResultAndSignalizing();
	//TestThreadsWithPromiseThrowingExceptionAndSignalizing();
	//TestThreadsWithPromiseReturningResultButNotSignalizing();
	//TestThreadsWithPromiseThrowingExceptionButNotSignalizing();
	//TestPackagedTasks();
	//TestPackagedTasksWithResult();
	//TestPackagedTasksWithException();
	//TestPackagedTasksAtAndOfThread();
	//TestPackagedTasksWithResultAtAndOfThread();
	//TestPackagedTasksWithExceptionAtAndOfThread();
	//TestRunPackagedTasks();
	//TestMultipleTasks();
	//TestMultipleTasksWithResult();
	//TestMultipleTasksWithResultOrException();
	//TestMultipleTaskFunctors();
	//TestTaskMethodWait();
	//TestTaskMethodWaitFor1();
	//TestTaskMethodWaitFor2();
	//TestTaskMethodWaitUntil1();
	//TestTaskMethodWaitUntil2();
	//TestSharedFutures();
	//TestTasksLaunchAsync();
	//TestTasksLaunchDeferred();
	TestTaskValidity();

	ShowExitLine();

    return(0);
}
//-----------------------------------------------------------------------------