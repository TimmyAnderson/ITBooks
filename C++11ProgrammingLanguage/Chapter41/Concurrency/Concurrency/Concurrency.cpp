//-----------------------------------------------------------------------------
// Toto je nutne definovat kvoli VS 2017.
#define _ENABLE_ATOMIC_ALIGNMENT_FIX
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <utility>
#include <thread>
#include <mutex>
#include <atomic>
#include <iostream>
#include "MyDebug.h"
#include "SSmallStructure1.h"
#include "SSmallStructure2.h"
#include "SBigStructure.h"
//-------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning(disable:4700)
#endif
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Ak by NEEXISTOVALA GARANCIA nezavislosti pristupu k rozdielnym MEMORY LOCATIONS, potom by COMPILER mohol tieto 1 BYTE dlhe VARIABLES ulozit do 1 WORD.
// !!! Kedze vsak C++ GARANTUJE, ze ARITHMETIC VARIABLES su v ROZDIELNYCH MEMORY LOCATIONS, pristup k VARIABLES je NEZAVISLY a nehrozi, ze THREAD, ktory zapisuje do 'GlobalVariable1' by zmenil hodnotu VARIABLE 'GlobalVariable2' ku ktorej NEPRISTUPIL iba preto, ze LEZIA v TOM ISTOM WORD v MEMORY.
char															GlobalVariable1;
char															GlobalVariable2;
//-----------------------------------------------------------------------------
struct SBitFieldsStructure
{
//-----------------------------------------------------------------------------
	public:
		// MEMORY LOCATION 1.
		char													MVariable1;
		// MEMORY LOCATION 2.
		// !!!!! Pristup k FIELD 'MVariable2' a FIELD 'MVariable3', kedze su na tej istej MEMORY LOCATION tak GARANCIA nezavislosti pristupu k rozdielnym MEMORY LOCATIONS tu NEPLATI. To znaci, ze pristup k FIELD 'MVariable2' a FIELD 'MVariable3', ak je realizovany 2 THREADS MUSI byt SYNCHRONIZED.
		unsigned int											MVariable2:7;
		unsigned int											MVariable3:7;
		unsigned int											:0;
		// MEMORY LOCATION 3.
		unsigned int											MVariable4:8;

		// MEMORY LOCATION 4.
		struct SInnerStructure
		{
//-----------------------------------------------------------------------------
			public:
				int												MVariable:8;
//-----------------------------------------------------------------------------
		}														MVariable5;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MemoryLocationThread1(int Index)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		char													LocalVariable=GlobalVariable1;

		LocalVariable++;

		GlobalVariable1=LocalVariable;
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void MemoryLocationThread2(int Index)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		char													LocalVariable=GlobalVariable2;

		LocalVariable++;

		GlobalVariable2=LocalVariable;
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestMemoryLocation(void)
{
	PrintLineSeparator();

	thread														Thread1(MemoryLocationThread1,1);
	thread														Thread2(MemoryLocationThread2,2);

	Thread1.join();
	Thread2.join();

	PrintLineSeparator();

	wprintf_s(L"GlobalVariable1 [%d] !\n",GlobalVariable1);
	wprintf_s(L"GlobalVariable2 [%d] !\n",GlobalVariable2);

	if (GlobalVariable1==GlobalVariable2)
	{
		wprintf_s(L"TEST PASSED !\n");
	}
	else
	{
		wprintf_s(L"TEST FAILED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MemoryLocationBitFieldsNoSynchronizationThread1(int Index, SBitFieldsStructure& BitFieldsStructure)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// !!! THREAD zapisuje do FIELD 'MVariable2', ale NIE do FIELD 'MVariable3'.
		// !!!!! Kedze FIELD 'MVariable2' a FIELD 'MVariable3' zdielaju MEMORY LOCATION, tak pristup k nim MUSI byt SYNCHRONIZED.
		BitFieldsStructure.MVariable2++;
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void MemoryLocationBitFieldsNoSynchronizationThread2(int Index, SBitFieldsStructure& BitFieldsStructure)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// !!! THREAD zapisuje do FIELD 'MVariable3', ale NIE do FIELD 'MVariable2'.
		// !!!!! Kedze FIELD 'MVariable2' a FIELD 'MVariable3' zdielaju MEMORY LOCATION, tak pristup k nim MUSI byt SYNCHRONIZED.
		BitFieldsStructure.MVariable3++;
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestMemoryLocationBitFieldsNoSynchronization(void)
{
	PrintLineSeparator();

	SBitFieldsStructure											BitFieldsStructure;

	BitFieldsStructure.MVariable1=0;
	BitFieldsStructure.MVariable2=0;
	BitFieldsStructure.MVariable3=0;
	BitFieldsStructure.MVariable4=0;
	BitFieldsStructure.MVariable5.MVariable=0;

	thread														Thread1(MemoryLocationBitFieldsNoSynchronizationThread1,1,ref(BitFieldsStructure));
	thread														Thread2(MemoryLocationBitFieldsNoSynchronizationThread2,2,ref(BitFieldsStructure));

	Thread1.join();
	Thread2.join();

	PrintLineSeparator();

	wprintf_s(L"BitFieldsStructure.MVariable2 [%d] !\n",BitFieldsStructure.MVariable2);
	wprintf_s(L"BitFieldsStructure.MVariable3 [%d] !\n",BitFieldsStructure.MVariable3);

	PrintLineSeparator();

	// !!!!! Aj ked THREADS pristupuju k rozlicnym BIT FIELDS, kedze tieto zdielaju 1 MEMORY LOCATION, tak je NUTNA SYNCHRONIZATION. Kedze ta nebola vykonana, obe VALUES budu ROZDIELNE.
	if (BitFieldsStructure.MVariable2==BitFieldsStructure.MVariable3)
	{
		wprintf_s(L"TEST PASSED !\n");
	}
	else
	{
		wprintf_s(L"TEST FAILED ! ACCESS to FIELD 'MVariable2' and FIELD 'MVariable3' MUST be SYNCHRONIZED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void MemoryLocationBitFieldsWithSynchronizationThread1(int Index, SBitFieldsStructure& BitFieldsStructure, mutex& Mutex)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000;Index++)
	{
		Mutex.lock();

		// !!! THREAD zapisuje do FIELD 'MVariable2', ale NIE do FIELD 'MVariable3'.
		// !!!!! Kedze FIELD 'MVariable2' a FIELD 'MVariable3' zdielaju MEMORY LOCATION, tak pristup k nim MUSI byt SYNCHRONIZED.
		BitFieldsStructure.MVariable2++;

		Mutex.unlock();
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void MemoryLocationBitFieldsWithSynchronizationThread2(int Index, SBitFieldsStructure& BitFieldsStructure, mutex& Mutex)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000;Index++)
	{
		Mutex.lock();

		// !!! THREAD zapisuje do FIELD 'MVariable3', ale NIE do FIELD 'MVariable2'.
		// !!!!! Kedze FIELD 'MVariable2' a FIELD 'MVariable3' zdielaju MEMORY LOCATION, tak pristup k nim MUSI byt SYNCHRONIZED.
		BitFieldsStructure.MVariable3++;

		Mutex.unlock();
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestMemoryLocationBitFieldsWithSynchronization(void)
{
	PrintLineSeparator();

	SBitFieldsStructure											BitFieldsStructure;

	BitFieldsStructure.MVariable1=0;
	BitFieldsStructure.MVariable2=0;
	BitFieldsStructure.MVariable3=0;
	BitFieldsStructure.MVariable4=0;
	BitFieldsStructure.MVariable5.MVariable=0;

	mutex														Mutex;
	thread														Thread1(MemoryLocationBitFieldsWithSynchronizationThread1,1,ref(BitFieldsStructure),ref(Mutex));
	thread														Thread2(MemoryLocationBitFieldsWithSynchronizationThread2,2,ref(BitFieldsStructure),ref(Mutex));

	Thread1.join();
	Thread2.join();

	PrintLineSeparator();

	wprintf_s(L"BitFieldsStructure.MVariable2 [%d] !\n",BitFieldsStructure.MVariable2);
	wprintf_s(L"BitFieldsStructure.MVariable3 [%d] !\n",BitFieldsStructure.MVariable3);

	PrintLineSeparator();

	// !!!!!! Kedze pristup k BIT FIELDS je SYNCHRONIZED, obe vratia TU ISTU VALUE.
	if (BitFieldsStructure.MVariable2==BitFieldsStructure.MVariable3)
	{
		wprintf_s(L"TEST PASSED !\n");
	}
	else
	{
		wprintf_s(L"TEST FAILED !\n");
	}

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
			wprintf_s(L"TEST [%d] PASSED !\n",Index);

			Thread.join();
		}
		else
		{
			wprintf_s(L"TEST [%d] FAILED !\n",Index);
			TestFailed=true;

			Thread.join();

			break;
		}
	}

	if (TestFailed==false)
	{
		wprintf_s(L"TEST PASSED !\n");
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicLowLevelLoadStoreThread(atomic<bool>& Atomic, int& Value)
{
	// !!!!! Kedze CLASS [atomic<T>] funguje ako MEMORY BARRIER, vsetky OPERATIONS vykonane PO volani METHOD atomic<T>::load() budu REALNE zavolane az PO zavolani tejto METHOD a COMPILER ich NEMOZE OPTIMALIZOVAT tak, ze by ich PREDRADIL volaniu METHOD atomic<T>::load().
	Value=-1;

	// !!! ATOMICKY sa zapisuje VALUE.
	// !!!!! VALUE [memory_order_release] zabezpecuje, ze ZIADNU MEMORY ACCESS OPERATION nemoze COMPILER presunut ZA CURRENT STORE OPERATION.
	Atomic.store(1,memory_order_release);
}
//-----------------------------------------------------------------------------
void TestLowLevelAtomicLoadStore(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	bool														TestPassed=true;

	for(int Index=0;Index<100000;Index++)
	{
		wprintf_s(L"TEST [%d] !\n",Index+1);

		int														Value=0;
		atomic<bool>											Atomic(false);
		thread													Thread;

		try
		{
			// Vytvori THREAD, ktory sa OKAMZITE SPUSTI.
			Thread=thread(AtomicLowLevelLoadStoreThread,ref(Atomic),ref(Value));

			while(true)
			{
				// !!! ATOMICKY sa cita VALUE.
				// !!!!! VALUE [memory_order_acquire] zabezpecuje, ze ZIADNU MEMORY ACCESS OPERATION nemoze COMPILER presunut PRED CURRENT LOAD OPERATION.
				if (Atomic.load(memory_order_acquire)==true)
				{
					if (Value!=-1)
					{
						TestPassed=false;
					}

					break;
				}
			}
		}
		catch(system_error)
		{
			wprintf_s(L"MAIN THREAD was NOT STARTED !\n");
		}

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
			wprintf_s(L"MAIN THREAD was NOT FINISHED !\n");
		}

		if (TestPassed==false)
		{
			break;
		}
	}

	if (TestPassed==true)
	{
		wprintf_s(L"TEST PASSED !\n");
	}
	else
	{
		wprintf_s(L"TEST FAILED !\n");
	}

	wprintf_s(L"MAIN FINISHED !\n");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicLowLevelFunctionIncrementThread(int Index, atomic<int>& Atomic)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// Vykona sa THREAD SAFE INCREMENT.
		// !!!!! Pouzita VALUE [memory_order_relaxed] umoznuje COMPILER robit NEBEZPECNE OPERATION REORDERING, pricom vsak ATOMICITA OPERACII je ZACHOVANA. V tomto pripade VALUE [memory_order_relaxed] je MOZNE pouzit, pretoze sa VARIABLE 'Atomic' NEPOUZIVA na riadenie CODE a tym padom REORDERING inych OPERATION na nu NEMA ZIADEN VPLYV.
		// !!!!! Vdaka pouzitiu VALUE [memory_order_relaxed] je CODE asi o 20 PERCENT RYCHLEJSI ako CODE vo FUNCTION TestAtomicFunctionIncrement().
		atomic_fetch_add_explicit(&Atomic,1,memory_order_relaxed);
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
// !!!!! Vdaka pouzitiu VALUE [memory_order_relaxed] je CODE asi o 20 PERCENT RYCHLEJSI ako CODE vo FUNCTION TestAtomicFunctionIncrement().
void TestAtomicLowLevelFunctionIncrement(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	atomic<int>													Atomic(0);

	high_resolution_clock::rep									Start=high_resolution_clock::now().time_since_epoch().count();

	{
		const int												NUMBER_OF_THREADS=10;
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
	}

	high_resolution_clock::rep									End=high_resolution_clock::now().time_since_epoch().count();

	wprintf_s(L"MAIN FINISHED !\n");

	wprintf_s(L"COUNTER [%d] !\n",atomic_load(&Atomic));
	wcout << "TIME [" << ((End-Start)*1000/high_resolution_clock::period::den) << "] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicIncrementThread(int Index, atomic<int>& Atomic)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// Vykona sa THREAD SAFE INCREMENT.
		Atomic++;
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestAtomicIncrement1(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	// !!! Je NEVYHNUTNE pouzit NON-DEFAULT CONSTRUCTOR, aby sa INICIALIZOVAL LOCK v instancii CLASS [atomic<int>].
	atomic<int>													Atomic(0);

	wprintf_s(L"IS LOCK FREE [%d] !\n",Atomic.is_lock_free());

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

	wprintf_s(L"COUNTER [%d] !\n",Atomic.load());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestAtomicIncrement2(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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

	wprintf_s(L"COUNTER [%d] !\n",Atomic.load());

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicLoadStoreThread(atomic<bool>& Atomic, wstring& Value)
{
	wprintf_s(L"WORKER THREAD STARTED !\n");

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wprintf_s(L"WORKER THREAD si GOING to WRITE VALUE !\n");

	// !!!!! Kedze CLASS [atomic<T>] funguje ako MEMORY BARRIER, vsetky OPERATIONS vykonane PO volani METHOD atomic<T>::load() budu REALNE zavolane az PO zavolani tejto METHOD a COMPILER ich NEMOZE OPTIMALIZOVAT tak, ze by ich PREDRADIL volaniu METHOD atomic<T>::load().
	Value=L"Timmy Anderson";

	// !!! ATOMICKY sa zapisuje VALUE.
	Atomic.store(1);

	wprintf_s(L"WORKER THREAD FINISHED !\n");
}
//-----------------------------------------------------------------------------
void TestAtomicLoadStore(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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
			wprintf_s(L"MAIN THREAD was NOT STARTED !\n");
		}

		wprintf_s(L"MAIN BEFORE WAIT !\n");

		while(true)
		{
			// !!! ATOMICKY sa cita VALUE.
			// !!!!! Kedze CLASS [atomic<T>] funguje ako MEMORY BARRIER, vsetky OPERATIONS vykonane PO volani METHOD atomic<T>::load() budu REALNE zavolane az PO zavolani tejto METHOD a COMPILER ich NEMOZE OPTIMALIZOVAT tak, ze by ich PREDRADIL volaniu METHOD atomic<T>::load().
			if (Atomic.load()==true)
			{
				wprintf_s(L"MAIN VALUE [%ls] !\n",Value.c_str());

				break;
			}

			wprintf_s(L"MAIN is WAITING !\n");

			this_thread::sleep_for(duration<int,ratio<1,1>>(1));
		}

		wprintf_s(L"MAIN AFTER WAIT !\n");

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
			wprintf_s(L"MAIN THREAD was NOT FINISHED !\n");
		}

		wprintf_s(L"MAIN FINISHED !\n");
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
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		DoLock(Atomic);

		Counter++;

		DoUnlock(Atomic);
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestLockingWithCAS(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wprintf_s(L"COUNTER [%d], ELAPSED TIME [%lld ms] !\n",Counter,(TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void LockingWithMutexThread(int Index, mutex& Mutex, int& Counter)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		lock_guard<mutex>										Lock(Mutex);

		Counter++;
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestLockingWithMutex(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wprintf_s(L"COUNTER [%d], ELAPSED TIME [%lld ms] !\n",Counter,(TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Toto je len UMELY EXAMPLE, ktory ukazuje ako je mozne s vyuzitim CAS inkrementovat VALUE.
void IncrementWithCASThread(int Index, atomic<int>& Counter)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	int															ExpectedValue;

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		do
		{
			// !!! Hodnotu VARIABLE 'ExpectedValue' NIE je NUTNE NACITAVAT, pretoze METHOD atomic<T>.compare_exchange_strong() ju nastavuje na CURRENT VALUE.
			//ExpectedValue=Counter.load();
		}
		while(Counter.compare_exchange_strong(ExpectedValue,ExpectedValue+1)==false);
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestIncrementWithCAS(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wprintf_s(L"COUNTER [%d], ELAPSED TIME [%lld ms] !\n",Counter.load(),(TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)));

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
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

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

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestIncrementWithCASInFunction(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wprintf_s(L"COUNTER [%d], ELAPSED TIME [%lld ms] !\n",Counter.load(),(TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void AtomicFunctionIncrementThread(int Index, atomic<int>& Atomic)
{
	wprintf_s(L"THREAD [%d] STARTED !\n",Index);

	for(int Index=0;Index<1000*1000*10;Index++)
	{
		// Vykona sa THREAD SAFE INCREMENT.
		atomic_fetch_add(&Atomic,1);
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestAtomicFunctionIncrement(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

	atomic<int>													Atomic;

	atomic_init(&Atomic,0);

	wprintf_s(L"IS LOCK FREE [%d] !\n",atomic_is_lock_free(&Atomic));

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
	}

	high_resolution_clock::rep									End=high_resolution_clock::now().time_since_epoch().count();

	wprintf_s(L"MAIN FINISHED !\n");

	wprintf_s(L"COUNTER [%d] !\n",atomic_load(&Atomic));
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

	wprintf_s(L"SMALL STRUCTURE 1 - IS LOCK FREE [%d] !\n",AtomicSmallStructure1.is_lock_free());
	wprintf_s(L"SMALL STRUCTURE 1 - MField [%d] !\n",AtomicSmallStructure1.load().GetField());

	PrintLineSeparator();

	// !!! Kedze STRUCTURE NEPRESAHUJE velkost POINTER SIZE, tak CLASS [atomic<SBigStructure>] je LOCK FREE.
	atomic<SSmallStructure2>									AtomicSmallStructure2{SSmallStructure2(100,200)};

	wprintf_s(L"SMALL STRUCTURE 2 - IS LOCK FREE [%d] !\n",AtomicSmallStructure2.is_lock_free());
	wprintf_s(L"SMALL STRUCTURE 2 - MField1 [%d], MField2 [%d] !\n",AtomicSmallStructure2.load().GetField1(),AtomicSmallStructure2.load().GetField2());

	// !!!!! G++ 5 zatial NEPODPORUJE ATOMIC operacie nad VELKYMI STRUCTURES. LINKER hodi ERROR.
#ifdef _MSC_VER
	PrintLineSeparator();

	// !!!!! Kedze STRUCTURE PRESAHUJE velkost POINTER SIZE, tak CLASS [atomic<SBigStructure>] POUZIVA LOCKS.
	atomic<SBigStructure>										AtomicBigStructure{SBigStructure(100,200,300)};

	wprintf_s(L"BIG STRUCTURE - IS LOCK FREE [%d] !\n",AtomicBigStructure.is_lock_free());
	wprintf_s(L"BIG STRUCTURE - MField1 [%d], MField2 [%d], MField3 [%d] !\n",AtomicBigStructure.load().GetField1(),AtomicBigStructure.load().GetField2(),AtomicBigStructure.load().GetField3());
#endif

	PrintLineSeparator();
}
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
void AtomicFlagThread(atomic_flag& Atomic, int Index, int& Value)
{
	wprintf_s(L"WORKER THREAD [%d] STARTED !\n",Index);

	for (int Index=0;Index<1000*1000*10;Index++)
	{
		while(Atomic.test_and_set()==true)
		{
		}

		Value++;

		Atomic.clear();
	}

	wprintf_s(L"WORKER THREAD [%d] FINISHED !\n",Index);
}
//-----------------------------------------------------------------------------
void TestAtomicFlag(void)
{
	PrintLineSeparator();

	wprintf_s(L"MAIN STARTED !\n");

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

	high_resolution_clock::time_point							End=high_resolution_clock::now();
	high_resolution_clock::duration								TimeElapsed=End-Start;
	
	wprintf_s(L"COUNTER [%d], ELAPSED TIME [%lld ms] !\n",Value,(TimeElapsed.count()/(high_resolution_clock::duration::period::den/1000)));

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestMemoryLocation();
	//TestMemoryLocationBitFieldsNoSynchronization();
	//TestMemoryLocationBitFieldsWithSynchronization();
	//TestInstructionReording();
	//TestLowLevelAtomicLoadStore();
	//TestAtomicLowLevelFunctionIncrement();
	//TestAtomicIncrement1();
	//TestAtomicIncrement2();
	//TestAtomicLoadStore();
	//TestLockingWithCAS();
	//TestLockingWithMutex();
	//TestIncrementWithCAS();
	//TestIncrementWithCASInFunction();
	//TestAtomicFunctionIncrement();
	//TestLoadStoreStructures();
	//TestCallOnce();
	TestAtomicFlag();

	ShowExitLine();

    return(0);
}
//-----------------------------------------------------------------------------