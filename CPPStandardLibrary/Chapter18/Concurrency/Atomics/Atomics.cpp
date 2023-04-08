//-----------------------------------------------------------------------------
// Toto bolo NUTNE deklarovat pre chybu vo VS 2015, ktora bola opravena v UPDATE 2, no ten vyzaduje deklarovat tento nezmysel.
#define _ENABLE_ATOMIC_ALIGNMENT_FIX
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include "MyDebug.h"
#include "CException.h"
#include "SSmallStructure1.h"
#include "SSmallStructure2.h"
#include "SBigStructure.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicIncrementThread(int Index, atomic<int>& Atomic)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// Vykona sa THREAD SAFE INCREMENT.
		Atomic++;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestAtomicIncrement1(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	// !!! Je NEVYHNUTNE pouzit NON-DEFAULT CONSTRUCTOR, aby sa INICIALIZOVAL LOCK v instancii CLASS [atomic<int>].
	atomic<int>													Atomic(0);

	wcout << L"IS LOCK FREE [" << Atomic.is_lock_free() << L"] !" << endl;

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(AtomicIncrementThread,(Index+1),ref(Atomic));
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

	wcout << L"COUNTER [" << Atomic.load() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAtomicIncrement2(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	// !!! Ak sa pouzije DEFAULT-CONSTRUCTOR, je NUTNE zavolat FUNCTION atomic_init(), inak INTERNY LOCK NEBUDE inicializovany.
	atomic<int>													Atomic;

	atomic_init(&Atomic,0);

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(AtomicIncrementThread,(Index+1),ref(Atomic));
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

	wcout << L"COUNTER [" << Atomic.load() << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicLoadStoreThread(atomic<bool>& Atomic, wstring& Value)
{
	wcout << L"WORKER THREAD STARTED !" << endl;

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wcout << L"WORKER THREAD si GOING to WRITE VALUE !" << endl;

	// !!!!! Kedze CLASS [atomic<T>] funguje ako MEMORY BARRIER, vsetky OPERATIONS vykonane PO volani METHOD atomic<T>::load() budu REALNE zavolane az PO zavolani tejto METHOD a COMPILER ich NEMOZE OPTIMALIZOVAT tak, ze by ich PREDRADIL volaniu METHOD atomic<T>::load().
	Value=L"Timmy Anderson";

	// !!! ATOMICKY sa zapisuje VALUE.
	Atomic.store(1);

	wcout << L"WORKER THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestAtomicLoadStore(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	wstring														Value;
	atomic<bool>												Atomic(false);

	{
		thread													Thread;

		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Thread=thread(AtomicLoadStoreThread,ref(Atomic),ref(Value));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD was NOT STARTED !" << endl;
		}

		wcout << L"MAIN BEFORE WAIT !" << endl;

		while(true)
		{
			// !!! ATOMICKY sa cita VALUE.
			// !!!!! Kedze CLASS [atomic<T>] funguje ako MEMORY BARRIER, vsetky OPERATIONS vykonane PO volani METHOD atomic<T>::load() budu REALNE zavolane az PO zavolani tejto METHOD a COMPILER ich NEMOZE OPTIMALIZOVAT tak, ze by ich PREDRADIL volaniu METHOD atomic<T>::load().
			if (Atomic.load()==true)
			{
				wcout << L"MAIN VALUE [" << Value << L"] !" << endl;

				break;
			}

			wcout << L"MAIN is WAITING !" << endl;

			this_thread::sleep_for(duration<int,ratio<1,1>>(1));
		}

		wcout << L"MAIN AFTER WAIT !" << endl;

		try
		{
			if (Thread.joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Thread.join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD was NOT FINISHED !" << endl;
		}

		wcout << L"MAIN FINISHED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void DoLock(atomic<bool>& Atomic)
{
	bool														InternalLock;

	do
	{
		InternalLock=false;
	}
	// CODE vykonava SPINNING pokym VARIABLE 'Atomic' nema nastavanu hodnotu FALSE. Nasledne ju nastavi na TRUE.
	while(Atomic.compare_exchange_strong(InternalLock,true)==false);
}
//-----------------------------------------------------------------------------
void DoUnlock(atomic<bool>& Atomic)
{
	bool														InternalLock;

	do
	{
		InternalLock=true;
	}
	// CODE vykonava SPINNING pokym VARIABLE 'Atomic' nema nastavanu hodnotu TRUE. Nasledne ju nastavi na FALSE.
	while(Atomic.compare_exchange_strong(InternalLock,false)==false);
}
//-----------------------------------------------------------------------------
void LockingWithCASThread(int Index, atomic<bool>& Atomic, int& Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		DoLock(Atomic);

		Counter++;

		DoUnlock(Atomic);
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestLockingWithCAS(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	high_resolution_clock::time_point							Start=high_resolution_clock::now();

	// !!! Je NEVYHNUTNE pouzit NON-DEFAULT CONSTRUCTOR, aby sa INICIALIZOVAL LOCK v instancii CLASS [atomic<int>].
	int															Counter=0;
	atomic<bool>												Atomic(false);

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(LockingWithCASThread,(Index+1),ref(Atomic),ref(Counter));
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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wcout << L"COUNTER [" << Counter << L"], ELAPSED TIME [" << (TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)) << L" ms] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void LockingWithMutexThread(int Index, mutex& Mutex, int& Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		lock_guard<mutex>										Lock(Mutex);

		Counter++;
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestLockingWithMutex(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	high_resolution_clock::time_point							Start=high_resolution_clock::now();

	// !!! Je NEVYHNUTNE pouzit NON-DEFAULT CONSTRUCTOR, aby sa INICIALIZOVAL LOCK v instancii CLASS [atomic<int>].
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
				Threads[Index]=thread(LockingWithMutexThread,(Index+1),ref(Mutex),ref(Counter));
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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wcout << L"COUNTER [" << Counter << L"], ELAPSED TIME [" << (TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)) << L" ms] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Toto je len UMELY EXAMPLE, ktory ukazuje ako je mozne s vyuzitim CAS inkrementovat VALUE.
void IncrementWithCASThread(int Index, atomic<int>& Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	int															ExpectedValue=Counter.load();

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		do
		{
			// !!! Hodnotu VARIABLE 'ExpectedValue' NIE je NUTNE NACITAVAT, pretoze METHOD atomic<T>.compare_exchange_strong() ju nastavuje na CURRENT VALUE.
			//ExpectedValue=Counter.load();
		}
		while(Counter.compare_exchange_strong(ExpectedValue,ExpectedValue+1)==false);
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestIncrementWithCAS(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	high_resolution_clock::time_point							Start=high_resolution_clock::now();

	atomic<int>													Counter(0);

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(IncrementWithCASThread,(Index+1),ref(Counter));
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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wcout << L"COUNTER [" << Counter.load() << L"], ELAPSED TIME [" << (TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)) << L" ms] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int CalculateValue(int Value)
{
	return(++Value);
}
//-----------------------------------------------------------------------------
// Toto je len UMELY EXAMPLE, ktory ukazuje ako je mozne s vyuzitim CAS inkrementovat VALUE.
void IncrementWithCASInFunctionThread(int Index, atomic<int>& Counter)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	int															ExpectedValue=Counter.load();
	int															NextValue;

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		do
		{
			NextValue=CalculateValue(ExpectedValue);
		}
		// !!!!! Pri zlyhani podmienky bude VARIABLE 'ExpectedValue' nastavena na NOVU VALUE.
		while(Counter.compare_exchange_strong(ExpectedValue,NextValue)==false);
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestIncrementWithCASInFunction(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	high_resolution_clock::time_point							Start=high_resolution_clock::now();

	atomic<int>													Counter(0);

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(IncrementWithCASInFunctionThread,(Index+1),ref(Counter));
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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wcout << L"COUNTER [" << Counter.load() << L"], ELAPSED TIME [" << (TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)) << L" ms] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicFunctionIncrementThread(int Index, atomic<int>& Atomic)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// Vykona sa THREAD SAFE INCREMENT.
		atomic_fetch_add(&Atomic,1);
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestAtomicFunctionIncrement(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	atomic<int>													Atomic;

	atomic_init(&Atomic,0);

	wcout << L"IS LOCK FREE [" << atomic_is_lock_free(&Atomic) << L"] !" << endl;

	high_resolution_clock::rep									Start=high_resolution_clock::now().time_since_epoch().count();

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(AtomicFunctionIncrementThread,(Index+1),ref(Atomic));
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
	}

	high_resolution_clock::rep									End=high_resolution_clock::now().time_since_epoch().count();

	wcout << L"MAIN FINISHED !" << endl;

	wcout << L"COUNTER [" << atomic_load(&Atomic) << L"] !" << endl;
	wcout << "TIME [" << ((End-Start)*1000/high_resolution_clock::period::den) << "] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicLowLevelLoadStoreThread(atomic<bool>& Atomic, wstring& Value)
{
	wcout << L"WORKER THREAD STARTED !" << endl;

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wcout << L"WORKER THREAD si GOING to WRITE VALUE !" << endl;

	// !!!!! Kedze CLASS [atomic<T>] funguje ako MEMORY BARRIER, vsetky OPERATIONS vykonane PO volani METHOD atomic<T>::load() budu REALNE zavolane az PO zavolani tejto METHOD a COMPILER ich NEMOZE OPTIMALIZOVAT tak, ze by ich PREDRADIL volaniu METHOD atomic<T>::load().
	Value=L"Timmy Anderson";

	// !!! ATOMICKY sa zapisuje VALUE.
	// !!!!! VALUE [memory_order_release] zabezpecuje, ze ZIADNU MEMORY ACCESS OPERATION nemoze COMPILER presunut ZA CURRENT STORE OPERATION.
	Atomic.store(1,memory_order_release);

	wcout << L"WORKER THREAD FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestLowLevelAtomicLoadStore(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	wstring														Value;
	atomic<bool>												Atomic(false);

	{
		thread													Thread;

		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Thread=thread(AtomicLowLevelLoadStoreThread,ref(Atomic),ref(Value));
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD was NOT STARTED !" << endl;
		}

		wcout << L"MAIN BEFORE WAIT !" << endl;

		while(true)
		{
			// !!! ATOMICKY sa cita VALUE.
			// !!!!! VALUE [memory_order_acquire] zabezpecuje, ze ZIADNU MEMORY ACCESS OPERATION nemoze COMPILER presunut PRED CURRENT LOAD OPERATION.
			if (Atomic.load(memory_order_acquire)==true)
			{
				wcout << L"MAIN VALUE [" << Value << L"] !" << endl;

				break;
			}

			wcout << L"MAIN is WAITING !" << endl;

			this_thread::sleep_for(duration<int,ratio<1,1>>(1));
		}

		wcout << L"MAIN AFTER WAIT !" << endl;

		try
		{
			if (Thread.joinable()==true)
			{
				// !!! Pocka sa na skoncenie THREAD.
				Thread.join();
			}
		}
		catch(system_error)
		{
			wcout << L"MAIN THREAD was NOT FINISHED !" << endl;
		}

		wcout << L"MAIN FINISHED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicLowLevelFunctionIncrementThread(int Index, atomic<int>& Atomic)
{
	wcout << L"THREAD [" << Index << L"] STARTED !" << endl;

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// Vykona sa THREAD SAFE INCREMENT.
		// !!!!! Pouzita VALUE [memory_order_relaxed] umoznuje COMPILER robit NEBEZPECNE OPERATION REORDERING, pricom vsak ATOMICITA OPERACII je ZACHOVANA. V tomto pripade VALUE [memory_order_relaxed] je MOZNE pouzit, pretoze sa VARIABLE 'Atomic' NEPOUZIVA na riadenie CODE a tym padom REORDERING inych OPERATION na nu NEMA ZIADEN VPLYV.
		// !!!!! Vdaka pouzitiu VALUE [memory_order_relaxed] je CODE asi o 20 PERCENT RYCHLEJSI ako CODE vo FUNCTION TestAtomicFunctionIncrement().
		atomic_fetch_add_explicit(&Atomic,1,memory_order_relaxed);
	}

	wcout << L"THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! Vdaka pouzitiu VALUE [memory_order_relaxed] je CODE asi o 20 PERCENT RYCHLEJSI ako CODE vo FUNCTION TestAtomicFunctionIncrement().
void TestAtomicLowLevelFunctionIncrement(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	atomic<int>													Atomic(0);

	high_resolution_clock::rep									Start=high_resolution_clock::now().time_since_epoch().count();

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(AtomicLowLevelFunctionIncrementThread,(Index+1),ref(Atomic));
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
	}

	high_resolution_clock::rep									End=high_resolution_clock::now().time_since_epoch().count();

	wcout << L"MAIN FINISHED !" << endl;

	wcout << L"COUNTER [" << atomic_load(&Atomic) << L"] !" << endl;
	wcout << "TIME [" << ((End-Start)*1000/high_resolution_clock::period::den) << "] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestLoadStoreStructures(void)
{
	PrintLineSeparator();

	// !!! Kedze STRUCTURE NEPRESAHUJE velkost POINTER SIZE, tak CLASS [atomic<SBigStructure>] je LOCK FREE.
	atomic<SSmallStructure1>									AtomicSmallStructure1{SSmallStructure1(100)};

	wcout << L"SMALL STRUCTURE 1 - IS LOCK FREE [" << AtomicSmallStructure1.is_lock_free() << L"] !" << endl;
	wcout << L"SMALL STRUCTURE 1 - MField [" << AtomicSmallStructure1.load().GetField() << L"] !" << endl;

	PrintLineSeparator();

	// !!! Kedze STRUCTURE NEPRESAHUJE velkost POINTER SIZE, tak CLASS [atomic<SBigStructure>] je LOCK FREE.
	atomic<SSmallStructure2>									AtomicSmallStructure2{SSmallStructure2(100,200)};

	wcout << L"SMALL STRUCTURE 2 - IS LOCK FREE [" << AtomicSmallStructure2.is_lock_free() << L"] !" << endl;
	wcout << L"SMALL STRUCTURE 2 - MField1 [" << AtomicSmallStructure2.load().GetField1() << L"], MField2 [" << AtomicSmallStructure2.load().GetField2() << L"] !" << endl;

	// !!!!! G++ zatial NEPODPORUJE ATOMIC operacie nad VELKYMI STRUCTURES. LINKER hodi ERROR.
#ifdef _MSC_VER
	PrintLineSeparator();

	// !!!!! Kedze STRUCTURE PRESAHUJE velkost POINTER SIZE, tak CLASS [atomic<SBigStructure>] POUZIVA LOCKS.
	atomic<SBigStructure>										AtomicBigStructure{SBigStructure(100,200,300)};

	wcout << L"BIG STRUCTURE - IS LOCK FREE [" << AtomicBigStructure.is_lock_free() << L"] !" << endl;
	wcout << L"BIG STRUCTURE - MField1 [" << AtomicBigStructure.load().GetField1() << L"], MField2 [" << AtomicBigStructure.load().GetField2() << L"], MField3 [" << AtomicBigStructure.load().GetField3() << L"] !" << endl;
#endif

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicFlagThread(atomic_flag& Atomic, int Index, int& Value)
{
	wcout << L"WORKER THREAD [" << Index << L"] STARTED !" << endl;

	for (int Index=0;Index<1000*1000*10;Index++)
	{
		while(Atomic.test_and_set()==true)
		{
		}

		Value++;

		Atomic.clear();
	}

	wcout << L"WORKER THREAD [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestAtomicFlag(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	high_resolution_clock::time_point							Start=high_resolution_clock::now();

	int															Value=0;
	atomic_flag													AtomicFlag{ATOMIC_FLAG_INIT};

	{
		const int												NUMBER_OF_THREADS=5;
		thread													Threads[NUMBER_OF_THREADS];

		for(int Index=0;Index<NUMBER_OF_THREADS;Index++)
		{
			try
			{
				// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
				Threads[Index]=thread(AtomicFlagThread,ref(AtomicFlag),(Index+1),ref(Value));
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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wcout << L"COUNTER [" << Value << L"], ELAPSED TIME [" << (TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)) << L" ms] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void InstructionReordingThread(int& SomeVariable, volatile bool& VariableIsReady, mutex& Mutex)
{
	SomeVariable=-1;

	Mutex.lock();

	// !!! Kedze VARIABLE sa pouziva na RIADENIE PROGRAMU a C++ by mohol vykonat REORDEDING predchadzajuceho a nasleldujuceho riadu CODE, je NUTNE pouzit SYNCHRONIZATION.
	VariableIsReady=true;

	Mutex.unlock();
}
//-----------------------------------------------------------------------------
void TestInstructionReording(void)
{
	PrintLineSeparator();

	bool														TestFailed=false;
	int															SomeVariable;

	// !!!!! Ked VARIABLE sa pouziva na riadenie PROGRAMU, MUSI byt VOLATILE, aby ju COMPILER NEOPTIMALIZOVAL.
	// !!!!! Ak VARIABLE NIE je VOLATILE tak v RELEASE verzii PROGRAMU dochadza obcasne k zaseknutiu sa na WHILE cykle.
	volatile bool												VariableIsReady;
	mutex														Mutex;

	for(int Index=0;Index<100000;Index++)
	{
		SomeVariable=0;
		VariableIsReady=false;

		thread													Thread(InstructionReordingThread,ref(SomeVariable),ref(VariableIsReady),ref(Mutex));

		// !!!!! Ak VARIABLE 'VariableIsReady' NIE je VOLATILE, potom C++ generuje nasleduci CODE.
		/*
// !!!!! Nacita sa posledna znama hodnota VARIABLE 'VariableIsReady'.
  000b2	0f b6 45 a7	 movzx	 eax, BYTE PTR VariableIsReady$[rbp-137]
$LL5@TestInstru:

; 283  : 
// !!!!! Cyklus DONEKONECNA kontroluje IBA JEDINYKRAT nacitanu hodnotu VARIABLE 'VariableIsReady' v REGISTRY AL.
// !!!!! Ak teda SEKUNDARNY THREAD NESTIHOL zmenit hodnotu VARIABLE 'VariableIsReady' na hodnotu TRUE, potom v REGISTRY AL je NAVZDY hodnota FALSE a PROGRAM sa dostane do NEKONECNEHO CYKLU.
; 284  : 		while(VariableIsReady==false)

  000b6	84 c0		 test	 al, al
  000b8	74 fc		 je	 SHORT $LL5@TestInstru
		*/
		// !!!!! Ak VARIABLE 'VariableIsReady' JE VOLATILE, potom C++ generuje nasleduci CODE.
/*
$LL5@TestInstru:
; File d:\programy\.net\csharp\c++11programminglanguage\chapter41\concurrency\concurrency\concurrency.cpp

; 298  : 		while(VariableIsReady==false)

// !!!!! V cykle sa uz nevycitava hodnota REGISTRY ALE, ale NEUSTALE sa FYZICKY cita hodnota z VARIABLE 'VariableIsReady'. To znaci, ze ked SEKUNDARNY THREAD zmeni hodnotu VARIABLE 'VariableIsReady' na TRUE, tak MAIN THREAD tuto zmenu ZACHYTI a CYKLUS SKONCIT. Tym padom NEDOCHADZA k NEKONECNEMU CYKLU.
  000b2	0f b6 45 87	 movzx	 eax, BYTE PTR VariableIsReady$[rbp-169]
  000b6	84 c0		 test	 al, al
  000b8	74 f8		 je	 SHORT $LL5@TestInstru
*/
		while(VariableIsReady==false)
		{
		}

		if (SomeVariable==-1)
		{
			wcout << L"TEST [" << Index << L"] PASSED !" << endl;

			Thread.join();
		}
		else
		{
			wcout << L"TEST [" << Index << L"] FAILED !" << endl;
			TestFailed=true;

			Thread.join();

			break;
		}
	}

	if (TestFailed==false)
	{
		wcout << L"TEST PASSED !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestAtomicIncrement1();
	//TestAtomicIncrement2();
	//TestAtomicLoadStore();
	//TestLockingWithCAS();
	//TestLockingWithMutex();
	//TestIncrementWithCAS();
	//TestIncrementWithCASInFunction();
	//TestAtomicFunctionIncrement();
	//TestLowLevelAtomicLoadStore();
	//TestAtomicLowLevelFunctionIncrement();
	//TestLoadStoreStructures();
	//TestAtomicFlag();
	TestInstructionReording();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------