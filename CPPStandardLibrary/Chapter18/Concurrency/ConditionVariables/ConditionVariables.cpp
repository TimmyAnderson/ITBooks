//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include "MyDebug.h"
#include "CException.h"
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
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableSetThread1(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION ineho THREADU o tom, ze CONDITIONAL VARIABLE bola nastavena.
	// !!!!! Tento CODE moze bezat s LOCKED, alebo UNLOCKED MUTEX.
	ConditionalVariable.notify_one();

	wcout << L"SET THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableWaitThread1(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD is WAITING !" << endl;

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wcout << L"WAIT THREAD detected that CONDITIONAL VARIABLE has been SET !" << endl;
	}

	wcout << L"WAIT THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestNotifyOneConditionalVariable1(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableSetThread2(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;

		// !!! Vykona sa NOTIFICATION ineho THREADU o tom, ze CONDITIONAL VARIABLE bola nastavena.
		// !!!!! Tento CODE moze bezat s LOCKED, alebo UNLOCKED MUTEX.
		ConditionalVariable.notify_one();
	}

	wcout << L"SET THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyOneConditionalVariableWaitThread2(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD is WAITING !" << endl;

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wcout << L"WAIT THREAD detected that CONDITIONAL VARIABLE has been SET !" << endl;
	}

	wcout << L"WAIT THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestNotifyOneConditionalVariable2(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION VSETKYCH OSTATNYCH THREADS o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_all();

	wcout << L"SET THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wcout << L"WAIT THREAD [" << Index << L"] detected that CONDITIONAL VARIABLE has been SET !" << endl;
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestNotifyAllConditionalVariable(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION 1. THREAD o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_one();

	wcout << L"SET THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!!!! METHOD condition_variable::wait_for() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_for() VZDY vrati TRUE, pretoze aj ked TIMEOUT EXPIROVAL, tak CONDITION VARIABLE uz BOLA NASTAVENA a CALLABLE OBJECT vratil TRUE.
		bool													LockAcquired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wcout << L"WAIT THREAD [" << Index << L"] detected that CONDITIONAL VARIABLE has been SET !" << endl;
		}
		else
		{
			wcout << L"!!!!! WAIT THREAD [" << Index << L"] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !" << endl;
		}
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestWaitForConditionalVariable(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NoWakeUpWaitForConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!!!! METHOD condition_variable::wait_for() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_for() VZDY vrati FALSE, pretoze THREAD, ktory by nastavoval CONDITIONAL VARIABLE NEBOL VYTVORENY a tak CONDITIONAL VARIABLE NIKDY NEMOZE byt SIGNALIZED.
		bool													LockAcquired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wcout << L"WAIT THREAD [" << Index << L"] detected that CONDITIONAL VARIABLE has been SET !" << endl;
		}
		else
		{
			wcout << L"!!!!! WAIT THREAD [" << Index << L"] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !" << endl;
		}
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestNoWakeUpWaitForConditionalVariable(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForWithSpuriousWakeupsConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION 1. THREAD o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_one();

	wcout << L"SET THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void WaitForWithSpuriousWakeupsConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!!!! Tato OVERLOADED verzia METHOD condition_variable::wait_for() kedze NEMA ako PARAMETER CALLABLE OBJECT, ktory by detekoval vznik SPURIOUS CALLS, moze byt ukocena aj ked CONDITIONAL VARIABLE NEBOLA NASTAVENA.
		// !!!!! Vdaka SPURIOUS WAKEUPS je RETURN VALUE znacne NESPOLAHLIVA a niekedy vracala FALSE, aj ked REALNE TIMEOUT EXPIROVAL. V CYGWIN naopak RETURN VALUE mala VZDY SPRAVNU hodnotu.
		bool													TimeoutExpired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6))==cv_status::timeout;

		wcout << L"WAIT THREAD [" << Index << L"] FINISHED WAITING ! ConditionalVariableFlag [" << ((ConditionalVariableFlag) ? L"TRUE" : L"FALSE") << L"], TimeoutExpired [" << ((TimeoutExpired) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestWaitForWithSpuriousWakeupsConditionalVariable(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void WaitUntilConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION 1. THREAD o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_one();

	wcout << L"SET THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void WaitUntilConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!!!! METHOD condition_variable::wait_until() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_until() VZDY vrati TRUE, pretoze aj ked TIMEOUT EXPIROVAL, tak CONDITION VARIABLE uz BOLA NASTAVENA a CALLABLE OBJECT vratil TRUE.
		bool													LockAcquired=ConditionalVariable.wait_until(Lock,system_clock::now()+duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wcout << L"WAIT THREAD [" << Index << L"] detected that CONDITIONAL VARIABLE has been SET !" << endl;
		}
		else
		{
			wcout << L"!!!!! WAIT THREAD [" << Index << L"] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !" << endl;
		}
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestWaitUntilConditionalVariable(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NoWakeUpWaitUntilConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!!!! METHOD condition_variable::wait_until() caka MAXIMALNE 6 sekund na pridelenie LOCK. Ak CONDITIONAL VARIABLE NIE JE PRIDELENY, po 6 SEKUNDACH prebudi CURRENT THREAD a spusti CALLABLE OBJECT, ktoreho RETURN VALUE, vrati ako RETURN VALUE METHOD.
		// !!!!! Toto volanie METHOD condition_variable::wait_until() VZDY vrati FALSE, pretoze THREAD, ktory by nastavoval CONDITIONAL VARIABLE NEBOL VYTVORENY a tak CONDITIONAL VARIABLE NIKDY NEMOZE byt SIGNALIZED.
		bool													LockAcquired=ConditionalVariable.wait_for(Lock,duration<int,ratio<1,1>>(6),[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		if (LockAcquired==true)
		{
			wcout << L"WAIT THREAD [" << Index << L"] detected that CONDITIONAL VARIABLE has been SET !" << endl;
		}
		else
		{
			wcout << L"!!!!! WAIT THREAD [" << Index << L"] detected TIMEOUT EXPIRATION while WAITING FOR CONDITIONAL VARIABLE to be SET !" << endl;
		}
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestNoWakeUpWaitUntilConditionalVariable(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllAtThreadExitConditionalVariableSetThread(mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

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

	wcout << L"!!! SET THREAD SET CONDITIONAL VARIABLE !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD FINISHED !" << endl;

	// !!! Az PO SKONCENI THREAD budu WAIT THREADS prebudene.
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void NotifyAllAtThreadExitConditionalVariableWaitThread(int Index, mutex& Mutex, condition_variable& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wcout << L"WAIT THREAD [" << Index << L"] detected that CONDITIONAL VARIABLE has been SET !" << endl;
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestNotifyAllAtThreadExitConditionalVariable(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			wcout << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// THREAD po nejakom case vykona SIGNALIZATION CONDITIONAL VARIABLE.
void ConditionalVariableAnySetThread(mutex& Mutex, condition_variable_any& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"SET THREAD STARTED !" << endl;

	wcout << L"SET THREAD is SLEEPING !" << endl;

	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"SET THREAD WOKE UP !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);
		
		// !!! Nastavi sa CONDITIONAL VARIABLE na TRUE.
		ConditionalVariableFlag=true;
	}

	// !!! Vykona sa NOTIFICATION VSETKYCH OSTATNYCH THREADS o tom, ze CONDITIONAL VARIABLE bola nastavena.
	ConditionalVariable.notify_all();

	wcout << L"SET THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// THREAD caka na SIGNALIZATION CONDITIONAL VARIABLE.
void ConditionalVariableAnyWaitThread(int Index, mutex& Mutex, condition_variable_any& ConditionalVariable, bool& ConditionalVariableFlag)
{
	wcout << L"WAIT THREAD [" << Index << L"] STARTED !" << endl;

	{
		// !!! Pri pouzivani CONDITIONAL VARIABLES je NUTNE pouzit CLASS [unique_lock<TMutex>].
		unique_lock<mutex>										Lock(Mutex);

		wcout << L"WAIT THREAD [" << Index << L"] is WAITING !" << endl;

		// !!! METHOD condition_variable::wait() INTERNE vola METHOD unique_lock<mutex>::lock() a METHOD unique_lock<mutex>::unlock().
		// !!!!! 2. PARAMETER je LAMBDA FUNCTION, ktora sluzi na PREVENCIU vzniku SPURIOUS WAKEUPS. LABMDA FUNCTION MUSI vrati TRUE, ak bol THREAD prebudeny a CONDITIONAL VARIABLE bola SKUTOCNE nastavena na TRUE.
		ConditionalVariable.wait(Lock,[&ConditionalVariableFlag](){return(ConditionalVariableFlag);});

		wcout << L"WAIT THREAD [" << Index << L"] detected that CONDITIONAL VARIABLE has been SET !" << endl;
	}

	wcout << L"WAIT THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestConditionalVariableAny(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	TestConditionalVariableAny();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------