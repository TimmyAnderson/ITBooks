//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning (disable : 4996)
#endif
//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <stdio.h>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <future>
#include <condition_variable>
#include <numeric>
#include <regex>
#include <sstream>
#include <cmath>
#include <complex>
#include <random>
#include <valarray>
#include "MyDebug.h"
#include "CCustomClass.h"
#include "CType1.h"
#include "CType2.h"
//-----------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning (disable : 4996)
#undef min
#undef max
#endif
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
using namespace std::regex_constants;
//-----------------------------------------------------------------------------
template<typename TIteratorType>
void PrintIteratorTraits(const wstring& TypeName)
{
	wcout << L"TYPE [" << TypeName << L"] !" << endl;

	wcout << L"CATEGORY [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::iterator_category).name()) << L"] !" << endl;
	wcout << L"VALUE TYPE [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::value_type).name()) << L"] !" << endl;
	wcout << L"POINTER [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::pointer).name()) << L"] !" << endl;
	wcout << L"REFERENCE [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::reference).name()) << L"] !" << endl;
	wcout << L"DIFFERENCE TYPE [" << ConvertStringToWideString(typeid(typename iterator_traits<TIteratorType>::difference_type).name()) << L"] !" << endl;
}
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
void SharedPointerInner(shared_ptr<CCustomClass> Pointer)
{
	wcout << L"SharedPointerInner() - VALUE [" << Pointer->GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void SharedPointerOuter(shared_ptr<CCustomClass> Pointer)
{
	wcout << L"SharedPointerOuter() - VALUE [" << Pointer->GetValue() << L"] !" << endl;

	SharedPointerInner(Pointer);
}
//-----------------------------------------------------------------------------
void TestSharedPointer1(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"TestSharedPointer() - VALUE [" << Pointer->GetValue() << L"] !" << endl;

		SharedPointerOuter(Pointer);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerPrintVector(vector<shared_ptr<CCustomClass>> Vector)
{
	for(const shared_ptr<CCustomClass>& Item : Vector)
	{
		wcout << L"VALUE [" << Item->GetValue() << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestSharedPointer2(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer1(new CCustomClass(L"Timmy Anderson"));
		shared_ptr<CCustomClass>								Pointer2(new CCustomClass(L"Jenny Thompson"));
		vector<shared_ptr<CCustomClass>>						Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void SharedPointerPrintVector(vector<shared_ptr<wstring>> Vector)
{
	for(const shared_ptr<wstring>& Item : Vector)
	{
		wcout << L"VALUE [" << *Item << L"] !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestSharedPointer3(void)
{
	PrintLineSeparator();

	{
		shared_ptr<wstring>										Pointer1(new wstring(L"Timmy Anderson"));
		shared_ptr<wstring>										Pointer2(new wstring(L"Jenny Thompson"));
		vector<shared_ptr<wstring>>								Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);

		PrintLineSeparator();

		// !!! Zmeni sa hodnota oboch OBJECTS na ktore SHARED SMART POINTER referuju pricom tato zmena sa premietne do vsetkych SHARED SMART POINTER, kedze referuju na tieto OBJECTS.
		*Pointer1=L"Timothy Anderson";
		(*Pointer2)[0]=L'Y';

		SharedPointerPrintVector(Vector);
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointer4(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"BEFORE RESET !" << endl;

		// Uvolni sa predchadzajuci OBJECT a zavola sa pred DESTRUCTOR.
		Pointer.reset(new CCustomClass(L"Jenny Thompson"));

		wcout << L"BEFORE NULL POINTER ASSIGNMENT !" << endl;

		// !!! OPERATR= NIE JE PRETAZENY pre POINTER. Preto COMPILER hodi na tento CODE ERROR.
		//Pointer=new CCustomClass(L"Jenny Thompson");

		// Uvolni sa OBJECT a zavola sa pred DESTRUCTOR.
		Pointer=nullptr;

		wcout << L"AFTER NULL POINTER ASSIGNMENT !" << endl;

		// !!! Kedze tu uz 'Pointer' NEOBSAHUJE ziaden OBJECT, tak sa DESTRUCTOR NEVOLA.
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSharedPointer5(void)
{
	PrintLineSeparator();

	{
		// !!! FUNCTION make_shared() predstavuje EFEKTIVNEJSI sposob vytvorenia SHARED SMART POINTER.
		shared_ptr<CCustomClass>								Pointer1=make_shared<CCustomClass>(L"Timmy Anderson");
		shared_ptr<CCustomClass>								Pointer2=make_shared<CCustomClass>(L"Jenny Thompson");
		vector<shared_ptr<CCustomClass>>						Vector;

		Vector.push_back(Pointer1);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer2);
		Vector.push_back(Pointer1);
		Vector.push_back(Pointer1);

		SharedPointerPrintVector(Vector);

		wcout << L"REFERENCE COUNTER POINTER 1 [" << Pointer1.use_count() << L"] !" << endl;
		wcout << L"REFERENCE COUNTER POINTER 2 [" << Pointer2.use_count() << L"] !" << endl;

		wcout << L"BEFORE CLEAR !" << endl;

		// !!! DESTRUCTORS sa NEVOLAJU, pretoze VARIABLES 'Pointer1' a 'Pointer2' sa referuju na OBJECTS.
		Vector.clear();

		wcout << L"AFTER CLEAR !" << endl;

		wcout << L"REFERENCE COUNTER POINTER 1 [" << Pointer1.use_count() << L"] !" << endl;
		wcout << L"REFERENCE COUNTER POINTER 2 [" << Pointer2.use_count() << L"] !" << endl;

		Pointer1=nullptr;
		Pointer2=nullptr;

		wcout << L"AFTER NULL POINTER ASSIGMENT !" << endl;

		wcout << L"REFERENCE COUNTER POINTER 1 [" << Pointer1.use_count() << L"] !" << endl;
		wcout << L"REFERENCE COUNTER POINTER 2 [" << Pointer2.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomDeleter(CCustomClass* ObjectToDelete) noexcept
{
	wcout << L"CUSTOM DELETER was CALLED !" << endl;

	delete(ObjectToDelete);
}
//-----------------------------------------------------------------------------
void TestSharedPointerCustomDeleter(void)
{
	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"),CustomDeleter);

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		shared_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"),[](CCustomClass* ObjectToDelete){wcout << L"CUSTOM DELETER was CALLED !" << endl; delete(ObjectToDelete);});

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomArrayDeleter1(int* ObjectToDelete) noexcept
{
	wcout << L"CUSTOM ARRAY DELETER was CALLED !" << endl;

	delete[](ObjectToDelete);
}
//-----------------------------------------------------------------------------
// !!! CUSTOM DELETE FUNCTION NESMIE hadzat EXCEPTIONS.
void CustomArrayDeleter2(CCustomClass* ObjectToDelete) noexcept
{
	wcout << L"CUSTOM ARRAY DELETER was CALLED !" << endl;

	delete[](ObjectToDelete);
}
//-----------------------------------------------------------------------------
void TestSharedPointerArrays(void)
{
	PrintLineSeparator();

	{
		// !!!!! Ak sa SHARED SMART POINTERS pouzivaju pre ulozenie ARRAYS, je NEVYHNUTNE definovat CUSTOM DELETE FUNCTION v ktorej sa zavola OPERATOR DELETE[].
		shared_ptr<int>											Pointer(new int[10],CustomArrayDeleter1);

		wcout << L"REFERENCE COUNTER [" << Pointer.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();

	{
		// !!!!! Ak sa SHARED SMART POINTERS pouzivaju pre ulozenie ARRAYS, je NEVYHNUTNE definovat CUSTOM DELETE FUNCTION v ktorej sa zavola OPERATOR DELETE[].
		shared_ptr<CCustomClass>								Pointer(new CCustomClass[5],CustomArrayDeleter2);

		wcout << L"REFERENCE COUNTER [" << Pointer.use_count() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer1(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		// !!! OPERATR= NIE JE PRETAZENY pre POINTER. Preto COMPILER hodi na tento CODE ERROR.
		//Pointer=new CCustomClass(L"Jenny Thompson");

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer2(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;

		// !!! Zavola DESTRUCTOR.
		Pointer.reset();

		if (Pointer!=nullptr)
		{
			wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"VALUE is NULL !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer3(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;

		// !!! NEZAVOLA sa DESTRUCTOR, iba instancia CLASS unique_ptr<CCustomClass> uz NEBUDE odkazovat na povodny POINTER.
		CCustomClass*											InnerPointer=Pointer.release();

		if (Pointer!=nullptr)
		{
			wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"VALUE is NULL !" << endl;
		}

		if (InnerPointer!=nullptr)
		{
			wcout << L"INNER VALUE [" << InnerPointer->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"INNER VALUE is NULL !" << endl;
		}

		delete(InnerPointer);
		InnerPointer=nullptr;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointer4(void)
{
	PrintLineSeparator();

	{
		unique_ptr<wstring>										Pointer(new wstring(L"Timmy Anderson"));

		wcout << L"VALUE [" << *Pointer << L"] !" << endl;

		(*Pointer)[2]=L'M';

		wcout << L"VALUE [" << *Pointer << L"] !" << endl;

		// !!! FUNCTION unique_ptr<T>.get() vracia POINTER na referovany OBJECT.
		wstring*												InnerPointer=Pointer.get();

		wcout << L"INNER VALUE [" << *InnerPointer << L"] !" << endl;

		wcout << L"INNER VALUE " << *InnerPointer << L" !" << endl;;

		// Pouzitie OPERATOR BOOL.
		if (Pointer!=nullptr)
		{
			wcout << L"POINTER is VALID !" << endl;
		}
		else
		{
			wcout << L"POINTER is NULL !" << endl;
		}

		Pointer.reset();

		// Pouzitie OPERATOR BOOL.
		if (Pointer!=nullptr)
		{
			wcout << L"POINTER is VALID !" << endl;
		}
		else
		{
			wcout << L"POINTER is NULL !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerAssignment1(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!! Povodny OBJECT sa UVOLNI a nahradi sa NOVYM OBJECT.
		Pointer=unique_ptr<CCustomClass>(new CCustomClass(L"Jenny Thompson"));

		wcout << L"VALUE [" << Pointer->GetValue() << L"] !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestUniquePointerAssignment2(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer1(new CCustomClass(L"Timmy Anderson"));

		wcout << L"POINTER 1 [" << Pointer1->GetValue() << L"] !" << endl;

		PrintLineSeparator();

		// !!!!! COMPILER hodi ERROR, pretoze OPERATOR= s COPY CONSTRUCTOR NIE JE PODPOROVANY.
		//unique_ptr<CCustomClass>								Pointer2(Pointer1);

		unique_ptr<CCustomClass>								Pointer2;

		// !!!!! COMPILER hodi ERROR, pretoze OPERATOR= s COPY SEMANTICS NIE JE PODPOROVANY.
		//Pointer2=Pointer1;

		// !!!!! COMPILER OPERATOR= pre MOVE SEMANTICS PODPORUJE.
		// !!!!! Hodnota 'Pointer1' bude rovna NULL.
		Pointer2=move(Pointer1);

		wcout << L"POINTER 2 [" << Pointer2->GetValue() << L"] !" << endl;

		if (Pointer1!=nullptr)
		{
			wcout << L"POINTER 1 [" << Pointer1->GetValue() << L"] !" << endl;
		}
		else
		{
			wcout << L"POINTER 1 is NULL !" << endl;
		}
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! UNIQUE POINTERS je mozne bez problemov prenasat pomocou REFERENCES.
void UniquePointerByReference(unique_ptr<CCustomClass>& Pointer)
{
	wcout << L"INSIDE UniquePointerByReference() [" << Pointer->GetValue() << L"] !" << endl;
}
//-----------------------------------------------------------------------------
// !!!!! FUNCTION preberie OBJECT ulozeny v PARAMETER 'Pointer'.
void UniquePointerByValue(unique_ptr<CCustomClass> Pointer)
{
	wcout << L"INSIDE UniquePointerByValue() [" << Pointer->GetValue() << L"] !" << endl;

	// !!!!! Tu sa zavola DESTRUCTOR pre OBJECT ulozeny v PARAMETER 'Pointer'.
}
//-----------------------------------------------------------------------------
void TestUniquePointerFunctionCalling(void)
{
	PrintLineSeparator();

	{
		unique_ptr<CCustomClass>								Pointer(new CCustomClass(L"Timmy Anderson"));

		PrintLineSeparator();

		wcout << L"BEFORE CALL by REFERENCE !" << endl;

		UniquePointerByReference(Pointer);

		wcout << L"AFTER CALL by REFERENCE !" << endl;

		PrintLineSeparator();

		/*
		wcout << L"BEFORE CALL by VALUE !" << endl;

		// !!!!! COMPILER hodi ERROR, pretoze COPY SEMANTICS NIE JE PODPOROVANA.
		UniquePointerByValue(Pointer);

		wcout << L"AFTER CALL by VALUE !" << endl;
		*/

		wcout << L"BEFORE CALL by VALUE !" << endl;

		// !!!!! Tento CODE COMPILER akceptuje, pretoze MOVE SEMANTICS je POVOLENA.
		// !!!!! Kedze sa pouzila MOVE SEMANTICS, tak OBJECT ulozeny vo VARIABLE 'Pointer' bude PRENESENY do FUNCTION UniquePointerByValue(), ktora tento OBJECT uvolni z MEMORY. To znaci, ze VOLANA FUNCTION UVOLNI OBJECT z MEMORY.
		UniquePointerByValue(move(Pointer));

		wcout << L"AFTER CALL by VALUE !" << endl;
	}

	PrintLineSeparator();
}
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
			wcout << GetTime() << L"MAIN THREAD [" << (Index+1) << L"] was NOT FINISHED !" << endl;
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

	wcout << L"!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] PACKAGED TASK FINISHED !" << endl;

	// Caka sa 3 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(3));

	wcout << L"!!!!! " << GetTime() << L" THREAD TASK [" << Index << L"] FINISHED !" << endl;
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
void TaskCallback(int Index)
{
	wcout << L"TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wcout << L"TASK [" << Index << L"] FINISHED !" << endl;
}
//-----------------------------------------------------------------------------
void TestTasksLaunchAsync(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=1000;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		try
		{
			// Vytvori TASK.
			// !!! FLAG [launch::async] PRIKAZUJE C++ spustit TASK OKAMZITE.
			// !!!!! Ak SYSTEM nema dost RESOURCES, mal byt hodit EXCEPTION [system_error].
			Tasks[Index]=async(launch::async,TaskCallback,(Index+1));
		}
		catch(system_error)
		{
			wcout << L"MAIN TASK [" << (Index+1) << L"] was NOT STARTED !" << endl;
		}
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

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
			wcout << L"MAIN TASK [" << (Index+1) << L"] was NOT FINISHED !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

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
void TestTypeFunctions(void)
{
	PrintLineSeparator();

	wcout << L"INT MIN [" << numeric_limits<int>::min() << L"] !" << endl;
	wcout << L"INT MAX [" << numeric_limits<int>::max() << L"] !" << endl;
	wcout << L"INT SIZEOF [" << sizeof(int) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! Emulacia pouzitia ITERATOR TRAITS v GENERIC ALGORITHM.
template<typename TIterator>
void PrintItemsAlgorithm(TIterator Begin, TIterator End)
{
	using														TValueType=typename iterator_traits<TIterator>::value_type;

	TIterator													Iterator=Begin;

	wcout << L"VALUES [";

	while(Iterator!=End)
	{
		// TEMPORARY VARIABLE sluzi iba na simulaciu pouzitia ITERATOR TRAITS.
		TValueType												TemporaryValue=*Iterator;

		if (Iterator!=Begin)
		{
			wcout << L" ";
		}

		wcout << TemporaryValue;

		Iterator++;
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestUseIteratorTraits(void)
{
	PrintLineSeparator();

	vector<int>													Vector({10,20,30,40,50});

	PrintItemsAlgorithm(Vector.cbegin(),Vector.cend());

	PrintLineSeparator();
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestTypeTraits(void)
{
	PrintLineSeparator();

	wcout << L"IS_CLASS<int> [" << is_class<int>::value << L"] !" << endl;
	wcout << L"IS_CLASS<wstring> [" << is_class<wstring>::value << L"] !" << endl;
	wcout << L"IS_CLASS<CType1> [" << is_class<CType1>::value << L"] !" << endl;
	wcout << L"IS_ABSTRACT<int> [" << is_abstract<int>::value << L"] !" << endl;
	wcout << L"IS_ABSTRACT<wstring> [" << is_abstract<wstring>::value << L"] !" << endl;
	wcout << L"IS_ABSTRACT<CType1> [" << is_abstract<CType1>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DESTRUCTIBLE<CType1> [" << is_trivially_destructible<CType1>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DESTRUCTIBLE<CType2> [" << is_trivially_destructible<CType2>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType1> [" << is_trivially_default_constructible<CType1>::value << L"] !" << endl;
	wcout << L"IS_TRIVIALLY_DEFAULT_CONSTRUCTIBLE<CType2> [" << is_trivially_default_constructible<CType2>::value << L"] !" << endl;
	wcout << L"IS_FUNCTION<CType2> [" << is_function<CType2>::value << L"] !" << endl;
	wcout << L"IS_FUNCTION<decltype(TestTypeTraits)> [" << is_function<decltype(TestTypeTraits)>::value << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimplePairs(void)
{
	PrintLineSeparator();

	pair<wstring,int>											Pair(L"Timmy Anderson",12);

	wcout << L"VALUE 1 [" << Pair.first << L"], VALUE 2 [" << Pair.second << L"] !" << endl;
	wcout << L"VALUE 1 [" << get<0>(Pair) << L"], VALUE 2 [" << get<1>(Pair) << L"] !" << endl;

	wcout << L"TUPLE SIZE [" << tuple_size<pair<wstring,int>>::value << L"] !" << endl;

	wcout << L"TYPE 1 [" << ConvertStringToWideString(typeid(tuple_element<0,pair<wstring,int>>::type).name()) << L"], TYPE 2 [" << ConvertStringToWideString(typeid(tuple_element<1,pair<wstring,int>>::type).name()) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestSimpleTuples(void)
{
	PrintLineSeparator();

	tuple<wstring,wstring,int>									Tuple(L"Timmy",L"Anderson",12);

	wcout << L"VALUE 1 [" << get<0>(Tuple) << L"], VALUE 2 [" << get<1>(Tuple) << L"], VALUE 3 [" << get<2>(Tuple) << L"] !" << endl;

	wcout << L"TUPLE SIZE [" << tuple_size<tuple<wstring,wstring,int>>::value << L"] !" << endl;

	PrintLineSeparator();

	wcout << L"TYPE 1 [" << ConvertStringToWideString(typeid(tuple_element<0,tuple<wstring,wstring,int>>::type).name()) << L"], TYPE 2 [" << ConvertStringToWideString(typeid(tuple_element<1,tuple<wstring,wstring,int>>::type).name()) << L"], TYPE 3 [" << ConvertStringToWideString(typeid(tuple_element<2,tuple<wstring,wstring,int>>::type).name()) << L"] !" << endl;

	PrintLineSeparator();

	// !!! Pouzitie sa INITIALIZER LIST.
	tuple<wstring,wstring,int>									TupleInitialized{L"Timmy",L"Anderson",12};

	wcout << L"VALUE 1 [" << get<0>(TupleInitialized) << L"], VALUE 2 [" << get<1>(TupleInitialized) << L"], VALUE 3 [" << get<2>(TupleInitialized) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TBidirectionalIterator>
void PrintSubMatch(const wstring& Prefix, match_results<TBidirectionalIterator> MatchResults, const sub_match<TBidirectionalIterator>& SubMatch)
{
	wcout << Prefix;
	wcout << L" MATCHED [";
	wcout << SubMatch.matched;
	wcout << L"] POSITION [";
	wcout << distance(MatchResults[0].first,SubMatch.first);
	wcout << L"] LENGTH [";
	wcout << SubMatch.length();
	wcout << L"] STRING [";
	wcout << SubMatch.str();
	wcout << L"] !";
	wcout << endl;
}
//-----------------------------------------------------------------------------
template<typename TBidirectionalIterator>
void PrintMatchResults(const wstring& String, const wstring& Pattern, const match_results<TBidirectionalIterator>& MatchResults)
{
	using														Size=typename match_results<TBidirectionalIterator>::size_type;

	wcout << L"STRING     [" << String << L"] !" << endl;
	wcout << L"PATTERN    [" << Pattern << L"] !" << endl;

	PrintSubMatch(L"FULL MATCH",MatchResults,MatchResults[0]);

	for(Size Index=1;Index<MatchResults.size();Index++)
	{
		wstringstream											Prefix;

		Prefix << L"SUBMATCH ";
		Prefix << Index;
		
		PrintSubMatch(Prefix.str(),MatchResults,MatchResults[Index]);
	}

	PrintSubMatch(L"UNMATCHED ",MatchResults,MatchResults[MatchResults.size()]);

	PrintSubMatch(L"PREFIX    ",MatchResults,MatchResults.prefix());
	PrintSubMatch(L"SUFIX     ",MatchResults,MatchResults.suffix());
}
//-----------------------------------------------------------------------------
void RegularExpressionSearch(const wstring& String, const wstring& Pattern, match_flag_type Flags=match_default, syntax_option_type Options=ECMAScript)
{
	wregex														RegEx(Pattern,Options);
	wsmatch														Match;
	
	if (regex_search(String,Match,RegEx,Flags)==true)
	{
		PrintMatchResults(String,Pattern,Match);
	}
	else
	{
		wcout << L"REGULAR EXPRESSION SEARCHING FAILED !" << endl;
	}
}
//-----------------------------------------------------------------------------
void TestRegularExpressions(void)
{
	PrintLineSeparator();

	RegularExpressionSearch(L"AAAABBBAAAABBB",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	// !!! SUBMATCHES NIE SU zaradene do MATCH RESULTS.
	RegularExpressionSearch(L"AAAABBBAAAABBB",L"((AAAA)(BBB))*",match_default,nosubs);

	PrintLineSeparator();

	RegularExpressionSearch(L"AAAABBBAAAABBBAAAA",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	RegularExpressionSearch(L"CCC",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	// !!! Nenajde ZIADEN MATCH.
	RegularExpressionSearch(L"CCCAAAABBBAAAABBBAAAA",L"((AAAA)(BBB))*");

	PrintLineSeparator();

	RegularExpressionSearch(L"CCCAAAABBBAAAABBBAAAA",L"((AAAA)(BBB))");

	PrintLineSeparator();

	// !!! SUBMATCH repreznetuje vyskyt KAZDEJ SUBEXPRESSION v ZATVORKACH () v najdenom MATCH.
	// !!!!! Kedze tento REGULAR EXPRESSION obsahuje 5 SUBEXPRESSIONS v ZATVORKACH (), tak REGULAR EXPRESSION MATCH obsahuje 5 SUBEXPRESSIONS.
	RegularExpressionSearch(L"CCCAAAABBBAAAABBBAAAA",L"((((AAAA)(BBB))))");

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestCMathFunctions(void)
{
	PrintLineSeparator();

	double														Number=5.4;

	wcout << L"EXP() [" << exp(Number) << L"] !" << endl;
	wcout << L"SQRT() [" << sqrt(Number) << L"] !" << endl;
	wcout << L"LOG() [" << log(Number) << L"] !" << endl;
	wcout << L"LOG10() [" << log10(Number) << L"] !" << endl;
	wcout << L"SIN() [" << sin(Number) << L"] !" << endl;
	wcout << L"COS() [" << cos(Number) << L"] !" << endl;
	wcout << L"TAN() [" << tan(Number) << L"] !" << endl;
	wcout << L"SINH() [" << sinh(Number) << L"] !" << endl;
	wcout << L"COSH() [" << cosh(Number) << L"] !" << endl;
	wcout << L"TANH() [" << tanh(Number) << L"] !" << endl;
	wcout << L"ASIN() [" << asin(Number) << L"] !" << endl;
	wcout << L"ACOS() [" << acos(Number) << L"] !" << endl;
	wcout << L"ATAN() [" << atan(Number) << L"] !" << endl;
	wcout << L"ASINH() [" << asinh(Number) << L"] !" << endl;
	wcout << L"ACOSH() [" << acosh(Number) << L"] !" << endl;
	wcout << L"ATANH() [" << atanh(Number) << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestComplexNumbers(void)
{
	PrintLineSeparator();

	complex<double>												Number1(4,3);
	complex<double>												Number2(polar(5.0,0.75));

	wcout << L"NUMBER 1 [" << Number1 << L"] !" << endl;
	wcout << L"NUMBER 2 [" << Number2 << L"] !" << endl;

	wcout << L"NUMBER 1 - ABSOLUTE [" << abs(Number1) << L"] MAGNITUDE [" << norm(Number1) << L"] PHASE ANGLE [" << arg(Number1) << L"] CONJUGATE [" << conj(Number1) << L"] !" << endl;
	wcout << L"NUMBER 2 - ABSOLUTE [" << abs(Number2) << L"] MAGNITUDE [" << norm(Number2) << L"] PHASE ANGLE [" << arg(Number2) << L"] CONJUGATE [" << conj(Number2) << L"] !" << endl;

	PrintLineSeparator();

	complex<double>												Number3=Number1+Number2;

	wcout << L"NUMBER 3 [" << Number3 << L"] !" << endl;

	complex<double>												Number4=Number1-Number2;

	wcout << L"NUMBER 4 [" << Number4 << L"] !" << endl;

	complex<double>												Number5=Number1*Number2;

	wcout << L"NUMBER 5 [" << Number5 << L"] !" << endl;

	complex<double>												Number6=Number1/Number2;

	wcout << L"NUMBER 6 [" << Number6 << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestRandomGenerator(void)
{
	PrintLineSeparator();

	default_random_engine										Engine;

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10,20>.
	uniform_int_distribution<int>								Distribution1(10,20);

	wcout << L"UNIFORM INT DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution1(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();

	// !!! UNIFORM DISTRIBUTION zabezpecuje, ze VALUES budu UNIFORMNE distribuovane v zadanom rozsahu <10.0,20.0). Hodnota 20.0 nie je NIKDY generovana.
	uniform_real_distribution<double>							Distribution2(10,20);

	wcout << L"UNIFORM REAL DISTRIBUTION [";

	for(int Index=0;Index<10;Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Distribution2(Engine);
	}

	wcout << L"] !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void PrintValarray(const wstring& Prefix, const valarray<TType>& Valarray)
{
	wcout << Prefix;
	wcout << L" [";

	for(size_t Index=0;Index<Valarray.size();Index++)
	{
		if (Index>0)
		{
			wcout << L" ";
		}

		wcout << Valarray[Index];
	}

	wcout << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestValarray(void)
{
	PrintLineSeparator();

	// Vytvori VALARRAY s 5 ITEMS obsahujucimi hodnotu 0.
	valarray<int>												Valarray1(5);

	PrintValarray(L"VALARRAY 1",Valarray1);

	PrintLineSeparator();

	// Vytvori VALARRAY s 5 ITEMS obsahujucimi hodnotu 3.14.
	valarray<double>											Valarray2(3.14,5);

	PrintValarray(L"VALARRAY 2",Valarray2);

	PrintLineSeparator();

	valarray<int>												Valarray3({1,2,3,4,5,6,7});

	PrintValarray(L"VALARRAY 3",Valarray3);

	PrintLineSeparator();

	int															Array[]{10,20,30,40,50};

	// Inicializacia VALARRAY z ARRAY.
	valarray<int>												Valarray4(Array,sizeof(Array)/sizeof(Array[0]));

	PrintValarray(L"VALARRAY 4",Valarray4);

	PrintLineSeparator();

	// Inicializacia VALARRAY z ARRAY.
	valarray<int>												Valarray5(Array+1,3);

	PrintValarray(L"VALARRAY 5",Valarray5);

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename TType>
void TestDumpNumericLimits(void)
{
	PrintLineSeparator();

	bool														HasSpecialization=numeric_limits<TType>::is_specialized;

	wcout << L"TYPE [" << ConvertStringToWideString(typeid(TType).name()) << L"] !" << endl;

	if (HasSpecialization==true)
	{
		wcout << L"VALUE numeric_limits<TType>::is_integer [" << ((numeric_limits<TType>::is_integer==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_signed [" << ((numeric_limits<TType>::is_signed==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_iec559 [" << ((numeric_limits<TType>::is_iec559==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::min() [" << numeric_limits<TType>::min() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max() [" << numeric_limits<TType>::max() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::lowest() [" << numeric_limits<TType>::lowest() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::epsilon() [" << numeric_limits<TType>::epsilon() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::round_error() [" << numeric_limits<TType>::round_error() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::infinity() [" << numeric_limits<TType>::infinity() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::quiet_NaN() [" << numeric_limits<TType>::quiet_NaN() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::signaling_NaN() [" << numeric_limits<TType>::signaling_NaN() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::denorm_min() [" << numeric_limits<TType>::denorm_min() << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_exact [" << ((numeric_limits<TType>::is_exact==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_infinity [" << ((numeric_limits<TType>::has_infinity==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_quiet_NaN [" << ((numeric_limits<TType>::has_quiet_NaN==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_signaling_NaN [" << ((numeric_limits<TType>::has_signaling_NaN==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_denorm [" << numeric_limits<TType>::has_denorm << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::has_denorm_loss [" << ((numeric_limits<TType>::has_denorm_loss==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::round_style [" << numeric_limits<TType>::round_style << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_bounded [" << ((numeric_limits<TType>::is_bounded==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::is_modulo [" << ((numeric_limits<TType>::is_modulo==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::digits [" << numeric_limits<TType>::digits << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::digits10 [" << numeric_limits<TType>::digits10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max_digits10 [" << numeric_limits<TType>::max_digits10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::radix [" << numeric_limits<TType>::radix << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::min_exponent [" << numeric_limits<TType>::min_exponent << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::min_exponent10 [" << numeric_limits<TType>::min_exponent10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max_exponent [" << numeric_limits<TType>::max_exponent << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::max_exponent10 [" << numeric_limits<TType>::max_exponent10 << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::traps [" << ((numeric_limits<TType>::traps==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
		wcout << L"VALUE numeric_limits<TType>::tinyness_before [" << ((numeric_limits<TType>::tinyness_before==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	}
	else
	{
		wcout << L"TYPE has NO SPECIALIZATION !" << endl;
	}

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestSharedPointer1();
	//TestSharedPointer2();
	//TestSharedPointer3();
	//TestSharedPointer4();
	//TestSharedPointer5();
	//TestSharedPointerCustomDeleter();
	//TestSharedPointerArrays();
	//TestUniquePointer1();
	//TestUniquePointer2();
	//TestUniquePointer3();
	//TestUniquePointer4();
	//TestUniquePointerAssignment1();
	//TestUniquePointerAssignment2();
	//TestUniquePointerFunctionCalling();
	//TestMultipleThreads();
	//TestMutex();
	//TestRecursiveMutex();
	//TestLockFunction();
	//TestWaitForConditionalVariable();
	//TestThreadsWithPromiseReturningResultAndSignalizing();
	//TestThreadsWithPromiseThrowingExceptionAndSignalizing();
	//TestPackagedTasks();
	//TestTasksLaunchAsync();
	//TestSystemClock();
	//TestDurationConversions();
	//TestTypeFunctions();
	//TestUseIteratorTraits();
	//TestTypeTraits();
	//TestSimplePairs();
	//TestSimpleTuples();
	//TestRegularExpressions();
	//TestCMathFunctions();
	//TestComplexNumbers();
	//TestRandomGenerator();
	//TestValarray();
	TestDumpNumericLimits<int32_t>();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------