//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <mutex>
#include <functional>
#include "MyDebug.h"
#include "CException.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementNoLock(int Index, int* Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000*100;Index++)
	{
		*Counter=*Counter+1;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestNoLock(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	int															Counter=0;
	const int													NUMBER_OF_THREADS=5;
	thread														Threads[NUMBER_OF_THREADS];

	for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
	{
		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Threads[Index]=thread(IncrementNoLock,(Index+1),&Counter);
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

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementMutex(int Index, mutex& Mutex, int* Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! Vykona sa LOCKING.
		Mutex.lock();

		*Counter=*Counter+1;

		// !!! Vykona sa UNLOCKING.
		Mutex.unlock();
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestMutex(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementLock(int Index, mutex& Mutex, int* Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! CONSTRUCTOR vykona LOCKING a DESTRUCTOR UNLOCKING.
		lock_guard<mutex>										Lock(Mutex);

		*Counter=*Counter+1;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestLock(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
				Threads[Index]=thread(IncrementLock,(Index+1),ref(Mutex),&Counter);
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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementRecursiveMutex(int Index, recursive_mutex& Mutex, int* Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

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

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestRecursiveMutex(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementRecursiveLock(int Index, recursive_mutex& Mutex, int* Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! CONSTRUCTOR vykona LOCKING a DESTRUCTOR UNLOCKING.
		lock_guard<recursive_mutex>								Lock1(Mutex);
		// !!! CONSTRUCTOR vykona RECURSIVE LOCKING a DESTRUCTOR RECURSIVE UNLOCKING.
		lock_guard<recursive_mutex>								Lock2(Mutex);

		*Counter=*Counter+1;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestRecursiveLock(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
				Threads[Index]=thread(IncrementRecursiveLock,(Index+1),ref(Mutex),&Counter);
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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TriedMutexThread(int Index, mutex& Mutex)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	// !!! Vykona sa pokus o LOCKING.
	while(Mutex.try_lock()==false)
	{
		wcout << L"!!! THREAD [" << Index << L"] was NOT ABLE to ACQUIRE LOCK !" << endl;

		this_thread::sleep_for(duration<int,ratio<1,1>>(1));
	}

	wcout << L"THREAD [" << Index << L"] ACQUIRED LOCK !" << endl;

	// !!! LOCK bol ziskany.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"THREAD [" << Index << L"] RELEASING LOCK !" << endl;

	// !!! Vykona sa UNLOCKING.
	Mutex.unlock();

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestTriedMutex(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	mutex														Mutex;

	{
		const int												NUMBER_OF_THREADS=3;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(TriedMutexThread,(Index+1),ref(Mutex));
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
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TriedLockThread(int Index, mutex& Mutex)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	// !!! Vykona sa pokus o LOCKING.
	while(Mutex.try_lock()==false)
	{
		wcout << L"!!! THREAD [" << Index << L"] was NOT ABLE to ACQUIRE LOCK !" << endl;

		this_thread::sleep_for(duration<int,ratio<1,1>>(1));
	}

	{
		// !!!!! Kedze LOCK uz BOL ZISKANY, je NUTNE pouzit OVERLOADED CONSTRUCTOR, ktory ma PARAMETER TYPE [adopt_lock_t]. Tento CONSTRUCTOR PREBERA UZ ZISKANY LOCK a v DESTRUCTOR ho UVOLNI.
		// !!! VALUE [adopt_lock] je GLOBAL CONST EXPRESSION.
		lock_guard<mutex>										Lock(Mutex,adopt_lock);

		wcout << L"THREAD [" << Index << L"] ACQUIRED LOCK !" << endl;

		// !!! LOCK bol ziskany.
		this_thread::sleep_for(duration<int,ratio<1,1>>(3));

		wcout << L"THREAD [" << Index << L"] RELEASING LOCK !" << endl;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestLockMutex(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	mutex														Mutex;

	{
		const int												NUMBER_OF_THREADS=3;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(TriedLockThread,(Index+1),ref(Mutex));
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
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TriedForTimedMutexThread(int Index, timed_mutex& Mutex)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	// !!! Vykona sa pokus o LOCKING.
	while(Mutex.try_lock_for(duration<int,ratio<1,1>>(1))==false)
	{
		wcout << L"!!! THREAD [" << Index << L"] was NOT ABLE to ACQUIRE LOCK !" << endl;
	}

	wcout << L"THREAD [" << Index << L"] ACQUIRED LOCK !" << endl;

	// !!! LOCK bol ziskany.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"THREAD [" << Index << L"] RELEASING LOCK !" << endl;

	// !!! Vykona sa UNLOCKING.
	Mutex.unlock();

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestTriedForTimedMutex(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TriedUntilTimedMutexThread(int Index, timed_mutex& Mutex)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	// !!! Vykona sa pokus o LOCKING.
	while(Mutex.try_lock_until(system_clock::now()+duration<int,ratio<1,1>>(1))==false)
	{
		wcout << L"!!! THREAD [" << Index << L"] was NOT ABLE to ACQUIRE LOCK !" << endl;
	}

	wcout << L"THREAD [" << Index << L"] ACQUIRED LOCK !" << endl;

	// !!! LOCK bol ziskany.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"THREAD [" << Index << L"] RELEASING LOCK !" << endl;

	// !!! Vykona sa UNLOCKING.
	Mutex.unlock();

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestTriedUntilTimedMutex(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void LockFunctionThread(int Index, int* Counter, mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<100;Index++)
	{
		// !!! Ziskaju sa 2 MUTEXES.
		lock(Mutex1,Mutex2);

		*Counter=*Counter+1;

		wcout << L"THREAD [" << Index << L"] ACQUIRED LOCKS !" << endl;

		// !!! LOCK bol ziskany.
		this_thread::sleep_for(duration<int,ratio<1,100>>(1));

		wcout << L"THREAD [" << Index << L"] RELEASING LOCKS !" << endl;

		// !!! Vykona sa UNLOCKING.
		Mutex1.unlock();
		// !!! Vykona sa UNLOCKING.
		Mutex2.unlock();
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestLockFunction(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void LockFunctionUsingLockThread(int Index, int* Counter, mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

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

			wcout << L"THREAD [" << Index << L"] ACQUIRED LOCKS !" << endl;

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,100>>(1));

			wcout << L"THREAD [" << Index << L"] RELEASING LOCKS !" << endl;

			// !!! DESTRUCTOR CLASSES [lock_guard<TMutex>] AUTOMATICKY uvolnia LOCKS.
		}
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestLockFunctionUsingLock(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TryLockFunctionThread(int Index, mutex& Mutex1, mutex& Mutex2, mutex& LockFailureMutex, int& Lock1Failures, int& Lock2Failures)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	while(true)
	{
		// !!! Ziskaju sa 2 MUTEXES.
		int														Result=try_lock(Mutex1,Mutex2);

		if (Result==-1)
		{
			wcout << L"THREAD [" << Index << L"] ACQUIRED LOCKS !" << endl;

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,1>>(3));

			wcout << L"THREAD [" << Index << L"] RELEASING LOCKS !" << endl;

			break;
		}
		else
		{
			wcout << L"!!! THREAD [" << Index << L"] was NOT ABLE to ACQUIRE LOCK [" << Result << L"] !" << endl;

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

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestTryLockFunction(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	wcout << L"LOCK 1 FAILURES [" << Lock1Failures << L"] !" << endl;
	wcout << L"LOCK 2 FAILURES [" << Lock2Failures << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementUniqueLock(int Index, mutex& Mutex, int* Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000;Index++)
	{
		// !!! CONSTRUCTOR vykona LOCKING a DESTRUCTOR UNLOCKING.
		unique_lock<mutex>										Lock(Mutex);

		*Counter=*Counter+1;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestUniqueLock(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void IncrementDeferredUniqueLock(int Index, mutex& Mutex, int* Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

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

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestDeferredUniqueLock(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	wcout << L"COUNTER [" << Counter << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TryLockUniqueLockThread(int Index, mutex& Mutex)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	while(true)
	{
		// !!! Kedze sa pouzil CONSTRUCTOR, ktory prijima TYPE [try_to_lock_t], tak LOCK NEBUDE prideleny CURRENT THREAD, ak ho INY THREAD drzi.
		unique_lock<mutex>										Lock(Mutex,try_to_lock);

		if (Lock.owns_lock()==true)
		{
			wcout << L"THREAD [" << Index << L"] ACQUIRED LOCKS !" << endl;

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,1>>(3));

			wcout << L"THREAD [" << Index << L"] RELEASING LOCKS !" << endl;

			break;
		}
		else
		{
			wcout << L"!!! THREAD [" << Index << L"] was NOT ABLE to ACQUIRE LOCK !" << endl;

			this_thread::sleep_for(duration<int,ratio<1,1>>(1));
		}
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestTryLockUniqueLockFunction(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DurationUniqueLockThread(int Index, recursive_timed_mutex& Mutex)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	while(true)
	{
		// !!! CONSTRUCTOR caka zadany cas na ziskanie LOCK.
		unique_lock<recursive_timed_mutex>						Lock(Mutex,duration<int,ratio<1,1>>(1));

		if (Lock.owns_lock()==true)
		{
			wcout << L"THREAD [" << Index << L"] ACQUIRED LOCKS !" << endl;

			// !!! LOCK bol ziskany.
			this_thread::sleep_for(duration<int,ratio<1,1>>(3));

			wcout << L"THREAD [" << Index << L"] RELEASING LOCKS !" << endl;

			break;
		}
		else
		{
			wcout << L"!!! THREAD [" << Index << L"] was NOT ABLE to ACQUIRE LOCK !" << endl;
		}
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestDurationUniqueLockFunction(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CallOnceFunction1(int Index)
{
	wcout << L"!!! THREAD [" << Index << L"] CALLED FUNCTION CallOnceFunction1() by call_once() FUNCTION !" << endl;
}
//-----------------------------------------------------------------------------
void CallOnceFunction2(int Index1, int Index2)
{
	wcout << L"!!! THREAD [" << Index1 << L"," << Index2 << L"] CALLED FUNCTION CallOnceFunction1() by call_once() FUNCTION !" << endl;
}
//-----------------------------------------------------------------------------
void CallOnceCallback(int Index, once_flag& Flag)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

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

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestCallOnce(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
void SingleThreadCallOnceFunction1(int Index)
{
	wcout << L"!!! FUNCTION SingleThreadCallOnceFunction1() with PARAMETER [" << Index << L"] CALLED by call_once() FUNCTION !" << endl;
}
//-----------------------------------------------------------------------------
void SingleThreadCallOnceFunction2(int Index1, int Index2)
{
	wcout << L"!!! FUNCTION SingleThreadCallOnceFunction2() with PARAMETERS [" << Index1 << L"," << Index2 << L"] CALLED by call_once() FUNCTION !" << endl;
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
	wcout << L"!!! THREAD [" << Index << L"] CALLED this FUNCTION by call_once() FUNCTION !" << endl;
}
//-----------------------------------------------------------------------------
void CallOnceFunctionWithException(int Index)
{
	wcout << L"!!! THREAD [" << Index << L"] CALLED this FUNCTION by call_once() FUNCTION ! EXCEPTION will be THROWN !" << endl;

	throw(CException(L"Some EXCEPTION !"));
}
//-----------------------------------------------------------------------------
void CallOnceWithExceptionCallback(int Index, once_flag& Flag)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

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
		wcout << L"!!! THREAD [" << Index << L"] DETECTED EXCEPTION [" << Exception.GetMessage() << L"] !" << endl;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestCallOnceWithException(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
void SingleThreadCallOnceWithoutExceptionFunction(int Index)
{
	wcout << L"!!! FUNCTION SingleThreadCallOnceWithoutExceptionFunction() with PARAMETER [" << Index << L"] CALLED by call_once() FUNCTION !" << endl;
}
//-----------------------------------------------------------------------------
void SingleThreadCallOnceWithExceptionFunction(int Index)
{
	wcout << L"!!! FUNCTION SingleThreadCallOnceWithExceptionFunction() with PARAMETER [" << Index << L"] CALLED by call_once() FUNCTION ! EXCEPTION will be THROWN !" << endl;

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
		wcout << L"EXCEPTION DETECTED [" << Exception.GetMessage() << L"] !" << endl;
	}

	try
	{
		// !!! Kedze FUNCTION SingleThreadCallOnceWithExceptionFunction() hodi EXCEPTION, CALLABLE OBJECT sa povazuje za NEZAVOLANY.
		call_once(Flag,SingleThreadCallOnceWithExceptionFunction,20);
	}
	catch(const CException& Exception)
	{
		wcout << L"EXCEPTION DETECTED [" << Exception.GetMessage() << L"] !" << endl;
	}

	try
	{
		// !!! Kedze FUNCTION SingleThreadCallOnceWithoutExceptionFunction() NEHODI EXCEPTION, CALLABLE OBJECT sa povazuje za ZAVOLANY.
		call_once(Flag,SingleThreadCallOnceWithoutExceptionFunction,30);
	}
	catch(const CException& Exception)
	{
		wcout << L"EXCEPTION DETECTED [" << Exception.GetMessage() << L"] !" << endl;
	}

	try
	{
		// !!! FUNCTION SingleThreadCallOnceWithoutExceptionFunction() sa NEZAVOLA, pretoze CALLABLE OBJECT uz BOL ZAVOLANY.
		call_once(Flag,SingleThreadCallOnceWithoutExceptionFunction,40);
	}
	catch(const CException& Exception)
	{
		wcout << L"EXCEPTION DETECTED [" << Exception.GetMessage() << L"] !" << endl;
	}

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
		wcout << L"LOCK ACQUIRED !" << endl;

		// !!!!! VC++ hodi EXCEPTION, pretoze LOCK uz bol ACQUIRED a MUTEX je NON-RECURSIVE.
		// !!!!! GCC sposobi DEADLOCK.
		Mutex.lock();
		wcout << L"LOCK ACQUIRED !" << endl;

		Mutex.unlock();
		wcout << L"LOCK RELEASED !" << endl;

		Mutex.unlock();
		wcout << L"LOCK RELEASED !" << endl;
	}
	catch(const system_error& E)
	{
		wcout << L"MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		wcout << L"MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		Mutex.unlock();
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DeadlockThread1(mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [1] STARTED !" << endl;

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
		wcout << L"MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		Mutex1.unlock();
	}

	wcout << L"THREAD [1] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void DeadlockThread2(mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [2] STARTED !" << endl;

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
		wcout << L"MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		Mutex2.unlock();
	}

	wcout << L"THREAD [2] FINISHED !" << endl;
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
		wcout << L"MAIN THREAD [1] was NOT STARTED !" << endl;
	}

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread2=thread(DeadlockThread2,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wcout << L"MAIN THREAD [2] was NOT STARTED !" << endl;
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
		wcout << L"THREAD [1] was NOT FINISHED !" << endl;
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
		wcout << L"THREAD [2] was NOT FINISHED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DeadlockLockThread1(mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [1] STARTED !" << endl;

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
		wcout << L"MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wcout << L"THREAD [1] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void DeadlockLockThread2(mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [2] STARTED !" << endl;

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
		wcout << L"MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wcout << L"THREAD [2] FINISHED !" << endl;
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
		wcout << L"MAIN THREAD [1] was NOT STARTED !" << endl;
	}

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread2=thread(DeadlockLockThread2,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wcout << L"MAIN THREAD [2] was NOT STARTED !" << endl;
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
		wcout << L"THREAD [1] was NOT FINISHED !" << endl;
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
		wcout << L"THREAD [2] was NOT FINISHED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DeadlockTryLockThread1(mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [1] STARTED !" << endl;

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

					wcout << L"THREAD [1] - DEADLOCK DETECTED - INDEX 0 !" << endl;
					break;
				}
				else if (NonLockedObject==1)
				{
					// !!! FUNCTION try_lock() UVOLNI VSETKY LOCKS, takze uz sa NESMU v CODE uvolnit.

					wcout << L"THREAD [1] - DEADLOCK DETECTED - INDEX 1 !" << endl;
					break;
				}
				else
				{
					wcout << L"THREAD [1] - DEADLOCK DETECTED - ERROR because CODE should NEVER get there !" << endl;
					break;
				}
			}
		}
	}
	catch(const system_error& E)
	{
		wcout << L"THREAD [1] - MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION try_lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wcout << L"THREAD [1] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void DeadlockTryLockThread2(mutex& Mutex1, mutex& Mutex2)
{
	wcout << L"THREAD [2] STARTED !" << endl;

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

					wcout << L"THREAD [2] - DEADLOCK DETECTED - INDEX 0 !" << endl;
					break;
				}
				else if (NonLockedObject==1)
				{
					// !!! FUNCTION try_lock() UVOLNI VSETKY LOCKS, takze uz sa NESMU v CODE uvolnit.

					wcout << L"THREAD [2] - DEADLOCK DETECTED - INDEX 0 !" << endl;
					break;
				}
				else
				{
					wcout << L"THREAD [2] - DEADLOCK DETECTED - ERROR because CODE should NEVER get there !" << endl;
					break;
				}
			}
		}
	}
	catch(const system_error& E)
	{
		wcout << L"THREAD [2] - MUTEX EXCEPTION - CODE [" << E.code().value() << L"], WHAT [" << ConvertStringToWideString(E.what()) << L"] !" << endl;

		// !!! NIE JE treba uvolnovat LOCK, lebo pri vzniku EXCEPTION vo FUNCTION try_lock() tato FUNCTION uvolni vsetky ziskane LOCKS.
	}

	wcout << L"THREAD [2] FINISHED !" << endl;
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
		wcout << L"MAIN THREAD [1] was NOT STARTED !" << endl;
	}

	try
	{
		// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
		Thread2=thread(DeadlockTryLockThread2,std::ref(Mutex1),std::ref(Mutex2));
	}
	catch(system_error)
	{
		wcout << L"MAIN THREAD [2] was NOT STARTED !" << endl;
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
		wcout << L"THREAD [1] was NOT FINISHED !" << endl;
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
		wcout << L"THREAD [2] was NOT FINISHED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestNoLock();
	//TestMutex();
	//TestLock();
	//TestRecursiveMutex();
	//TestRecursiveLock();
	//TestTriedMutex();
	//TestLockMutex();
	//TestTriedForTimedMutex();
	//TestTriedUntilTimedMutex();
	//TestLockFunction();
	//TestLockFunctionUsingLock();
	//TestTryLockFunction();
	//TestUniqueLock();
	//TestDeferredUniqueLock();
	//TestTryLockUniqueLockFunction();
	//TestTryLockUniqueLockFunction();
	//TestDurationUniqueLockFunction();
	//TestCallOnce();
	//TestCallOnceInSingleThread();
	//TestCallOnceWithException();
	//TestCallOnceWithExceptionInSingleThread();
	//TestMutexErrorRecursiveLock();
	//TestMutexErrorDeadlock();
	//TestMutexErrorDeadlockLock();
	TestMutexErrorDeadlockTryLock();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------