//-----------------------------------------------------------------------------
#include <typeinfo>
#include <type_traits>
#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <system_error>
#include "MyDebug.h"
#include "CException.h"
#include "CTaskMethod.h"
#include "CTaskFunctor.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
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
void TestMultipleTasks(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=10;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallback,(Index+1));
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int TaskCallbackWithResult(int Index)
{
	int															Result=Index*2;

	wcout << L"TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wcout << L"TASK [" << Index << L"] FINISHED !" << endl;

	return(Result);
}
//-----------------------------------------------------------------------------
void TestMultipleTasksWithResult(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=5;
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallbackWithResult,(Index+1));
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		int														Result=Tasks[Index].get();

		wcout << L"MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int TaskCallbackWithResultOrException(int Index)
{
	int															Result=Index*2;

	wcout << L"TASK [" << Index << L"] STARTED !" << endl;

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	if ((Index%2)!=0)
	{
		wcout << L"TASK [" << Index << L"] FINISHED !" << endl;
	}
	else
	{
		wcout << L"!!! TASK [" << Index << L"] FINISHED throwing EXCEPTION !" << endl;

		throw(CException(L"SOME EXCEPTION !"));
	}

	return(Result);
}
//-----------------------------------------------------------------------------
void TestMultipleTasksWithResultOrException(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=5;
	future<int>													Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallbackWithResultOrException,(Index+1));
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
			int													Result=Tasks[Index].get();

			wcout << L"MAIN - TASK [" << (Index+1) << L"] FINISHED with RESULT [" << Result << L"] !" << endl;
		}
		catch(const CException& E)
		{
			wcout << L"MAIN - TASK [" << (Index+1) << L"] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
		}
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestMultipleTaskFunctors(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=5;
	future<void>												Tasks[NUMBER_OF_TASKS];
	CTaskFunctor												TaskObjects[NUMBER_OF_TASKS]{CTaskFunctor(1001),CTaskFunctor(1002),CTaskFunctor(1003),CTaskFunctor(1004),CTaskFunctor(1005)};

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!!!! Ak sa pouziva OPERATOR() ako CALLBACK FUNCTION, je NUTNE ako 2. PARAMETER preniest THIS OBJECT.
		Tasks[Index]=async(&CTaskFunctor::operator(),&TaskObjects[Index],(Index+1));
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
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

	const int													NUMBER_OF_TASKS=10;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! Ako CALLBACK FUNCTION sa pouziva LAMBDA EXPRESSION.
		Tasks[Index]=async([](int Index){wcout << L"LAMBDA TASK [" << Index << L"] STARTED !" << endl; this_thread::sleep_for(duration<int,ratio<1,1>>(5)); wcout << L"LAMBDA TASK [" << Index << L"] FINISHED !" << endl;},(Index+1));
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN AFTER WAIT !" << endl;

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// !!! Pocka sa na skoncenie TASK. Ak TASK este bezi, CURRENT THREAD je BLOCKED.
		Tasks[Index].get();
	}

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTasksLaunchAsync(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
void TestTasksLaunchDeferred(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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
			// !!! Kedze TASK NEBOL vdaka pouzitiu VALUE [launch::deferred] SPUSTENY, tak sa spusti az TERAZ.
			// !!!!! Ak by sa METHOD future<T>::get() VOBEC NEZAVOLALA, potom by DESTRUCTOR CLASS [future<T>] iba uvolnil tuto instanciu, BEZ vykonania THREAD BLOCKING. TASK by sa jednoducho NIKDY NESPUSTIL.
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
void TestTaskValidity(void)
{
	PrintLineSeparator();

	future<void>												TaskAsync=async(launch::async,TaskCallback,100);
	future<void>												TaskDeferred=async(launch::deferred,TaskCallback,200);

	wcout << L"BEFORE GET - TASK ASYNC VALIDITY [" << ((TaskAsync.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"BEFORE GET - TASK DEFERRED VALIDITY [" << ((TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	TaskAsync.get();
	TaskDeferred.get();

	wcout << L"AFTER GET - TASK ASYNC VALIDITY [" << ((TaskAsync.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"AFTER GET - TASK DEFERRED VALIDITY [" << ((TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	// !!!!! Pokus o volanie METHOD future<T>::get() by viedol k UNDEFINED BEHAVIOR.

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWait(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	future<int>													TaskWithResult=async(TaskCallbackWithResult,100);
	future<int>													TaskWithException=async(TaskCallbackWithResultOrException,200);

	try
	{
		TaskWithResult.wait();

		wcout << L"MAIN - TASK with RESULT FINISHED SUCCESSFULLY !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"MAIN - TASK with RESULT FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	try
	{
		// !!!!! Ak TASK hodi EXCEPTION, potom METHOD future<T>::wait() tuto EXCEPTION NEHODI.
		TaskWithException.wait();

		// !!! CODE SKONCI v tomto mieste.
		wcout << L"MAIN - TASK with EXCEPTION FINISHED SUCCESSFULLY !" << endl;
	}
	catch(const CException& E)
	{
		// !!! Sem sa CODE NIKDY NEDOSTANE.
		wcout << L"MAIN - TASK with EXCEPTION FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	wcout << L"BEFORE GET - TASK with RESULT VALIDITY [" << ((TaskWithResult.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"BEFORE GET - TASK with EXCEPTION VALIDITY [" << ((TaskWithException.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	try
	{
		int														Result=TaskWithResult.get();

		wcout << L"MAIN - METHOD GET - TASK with RESULT has RESULT [" << Result << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"MAIN - METHOD GET - TASK with RESULT FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	try
	{
		int														Result=TaskWithException.get();

		wcout << L"MAIN - METHOD GET - TASK with EXCEPTION has RESULT [" << Result << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"MAIN - METHOD GET - TASK with EXCEPTION FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	wcout << L"AFTER GET - TASK with RESULT VALIDITY [" << ((TaskWithResult.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"AFTER GET - TASK with EXCEPTION VALIDITY [" << ((TaskWithException.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitFor1(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	future<void>												TaskAsync=async(launch::async,TaskCallback,100);
	future<void>												TaskDeferred=async(launch::deferred,TaskCallback,200);
	future_status												TaskAsyncStatus=TaskAsync.wait_for(duration<int,ratio<1,1000>>(500));

	if (TaskAsyncStatus==future_status::ready)
	{
		wcout << L"TASK [100] (ASYNC) FINISHED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wcout << L"TASK [100] (ASYNC) hasn't STARTED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wcout << L"TASK [100] (ASYNC) STARTED but hasn't FINISHED !" << endl;
	}

	future_status												TaskDeferredStatus=TaskDeferred.wait_for(duration<int,ratio<1,1000>>(500));

	if (TaskDeferredStatus==future_status::ready)
	{
		wcout << L"TASK [200] (DEFERRED) FINISHED !" << endl;
	}
	else if (TaskDeferredStatus==future_status::deferred)
	{
		wcout << L"TASK [200] (DEFERRED) hasn't STARTED !" << endl;
	}
	else if (TaskDeferredStatus==future_status::timeout)
	{
		wcout << L"TASK [200] (DEFERRED) STARTED but hasn't FINISHED !" << endl;
	}

	TaskAsync.get();
	TaskDeferred.get();

	// !!!!! Po zavolani METHOD future<T>::get() uz NIE JE MOZNE volat METHOD future<T>::wait_for(), pretoze TASK uz NIE JE VALIDNY.

	wcout << L"AFTER GET - TASK [100] (ASYNC) VALIDITY [" << ((TaskAsync.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"AFTER GET - TASK [200] (DEFERRED) VALIDITY [" << ((TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitFor2(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	future<int>													TaskWithException=async(TaskCallbackWithResultOrException,100);

	// !!! Pocka sa dostatocne dlhu dobu na skoncenie TASK.
	// !!! Aj ked TASK HODIL EXCEPTION, METHOD future<T>::wait_for() EXCEPTION NEHADZE.
	future_status												TaskAsyncStatus=TaskWithException.wait_for(duration<int,ratio<1,1>>(10));

	if (TaskAsyncStatus==future_status::ready)
	{
		wcout << L"TASK [100] FINISHED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wcout << L"TASK [100] hasn't STARTED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wcout << L"TASK [100] STARTED but hasn't FINISHED !" << endl;
	}

	try
	{
		int														Result=TaskWithException.get();

		wcout << L"MAIN - METHOD GET - TASK [100] has RESULT [" << Result << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"MAIN - METHOD GET - TASK [100] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	wcout << L"AFTER GET - TASK [100] VALIDITY [" << ((TaskWithException.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitUntil1(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	future<void>												TaskAsync=async(launch::async,TaskCallback,100);
	future<void>												TaskDeferred=async(launch::deferred,TaskCallback,200);
	future_status												TaskAsyncStatus=TaskAsync.wait_until(system_clock::now()+duration<int,ratio<1,1000>>(500));
	
	if (TaskAsyncStatus==future_status::ready)
	{
		wcout << L"TASK [100] (ASYNC) FINISHED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wcout << L"TASK [100] (ASYNC) hasn't STARTED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wcout << L"TASK [100] (ASYNC) STARTED but hasn't FINISHED !" << endl;
	}

	future_status												TaskDeferredStatus=TaskDeferred.wait_until(system_clock::now()+duration<int,ratio<1,1000>>(500));

	if (TaskDeferredStatus==future_status::ready)
	{
		wcout << L"TASK [200] (DEFERRED) FINISHED !" << endl;
	}
	else if (TaskDeferredStatus==future_status::deferred)
	{
		wcout << L"TASK [200] (DEFERRED) hasn't STARTED !" << endl;
	}
	else if (TaskDeferredStatus==future_status::timeout)
	{
		wcout << L"TASK [200] (DEFERRED) STARTED but hasn't FINISHED !" << endl;
	}

	TaskAsync.get();
	TaskDeferred.get();

	// !!!!! Po zavolani METHOD future<T>::get() uz NIE JE MOZNE volat METHOD future<T>::wait_until(), pretoze TASK uz NIE JE VALIDNY.

	wcout << L"AFTER GET - TASK [100] (ASYNC) VALIDITY [" << ((TaskAsync.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;
	wcout << L"AFTER GET - TASK [200] (DEFERRED) VALIDITY [" << ((TaskDeferred.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskMethodWaitUntil2(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	future<int>													TaskWithException=async(TaskCallbackWithResultOrException,100);

	// !!! Pocka sa dostatocne dlhu dobu na skoncenie TASK.
	// !!! Aj ked TASK HODIL EXCEPTION, METHOD future<T>::wait_until() EXCEPTION NEHADZE.
	future_status												TaskAsyncStatus=TaskWithException.wait_until(system_clock::now()+duration<int,ratio<1,1>>(10));

	if (TaskAsyncStatus==future_status::ready)
	{
		wcout << L"TASK [100] FINISHED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::deferred)
	{
		wcout << L"TASK [100] hasn't STARTED !" << endl;
	}
	else if (TaskAsyncStatus==future_status::timeout)
	{
		wcout << L"TASK [100] STARTED but hasn't FINISHED !" << endl;
	}

	try
	{
		int														Result=TaskWithException.get();

		wcout << L"MAIN - METHOD GET - TASK [100] has RESULT [" << Result << L"] !" << endl;
	}
	catch(const CException& E)
	{
		wcout << L"MAIN - METHOD GET - TASK [100] FINISHED with EXCEPTION [" << E.GetMessage() << L"] !" << endl;
	}

	wcout << L"AFTER GET - TASK [100] VALIDITY [" << ((TaskWithException.valid()==true) ? L"TRUE" : L"FALSE") << L"] !" << endl;

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
wstring TaskSharedFutureCallback(wstring Text)
{
	wcout << L"SHARED FUTURE TASK [" << Text << L"] STARTED !" << endl;

	// Caka sa 5 sekund.
	this_thread::sleep_for(duration<int,ratio<1,1>>(5));

	wcout << L"SHARED FUTURE TASK [" << Text << L"] FINISHED !" << endl;

	return(Text);
}
//-----------------------------------------------------------------------------
// !!! SHARED FUTURE sa prenasa BY-VALUE a NIE BY-REFERENCE.
void TaskFutureCallback(shared_future<wstring> SharedFuture, int Index)
{
	wcout << L"TASK [" << Index << L"] STARTED !" << endl;

	// !!! Caka sa na ukoncenie SHARED FUTURE. Kedze sa pouzila SHARED FUTURE je METHOD shared_future<wstring>::get() mozne volat VIACKRAT.
	wstring														Text=SharedFuture.get();

	wcout << L"TASK [" << Index << L"] FINISHED with RESULT [" << Text << L"] !" << endl;
}
//-----------------------------------------------------------------------------
void TestSharedFutures(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

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

	wcout << L"MAIN FINISHED !" << endl;

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void TestTaskDestructor(void)
{
	PrintLineSeparator();

	wcout << L"MAIN STARTED !" << endl;

	const int													NUMBER_OF_TASKS=10;
	future<void>												Tasks[NUMBER_OF_TASKS];

	for(int Index=0;Index<NUMBER_OF_TASKS;Index++)
	{
		// Vytvori TASK.
		// !!! C++ MOZE, ale takisto NEMUSI OKAMZITE spustit TASK.
		Tasks[Index]=async(TaskCallback,(Index+1));
	}

	wcout << L"MAIN BEFORE WAIT !" << endl;

	// Caka sa 2 sekundy.
	this_thread::sleep_for(duration<int,ratio<1,1>>(2));

	wcout << L"MAIN FINISHED !" << endl;

	// !!! PROGRAM NESKONCI SKOR, kym NESKONCIA VSETKY TASKS.

	PrintLineSeparator();
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main(void)
{
	SafeMain();

	//TestMultipleTasks();
	//TestMultipleTasksWithResult();
	//TestMultipleTasksWithResultOrException();
	//TestMultipleTaskMethods();
	//TestMultipleTaskFunctors();
	//TestMultipleLambdaTasks();
	//TestTasksLaunchAsync();
	//TestTasksLaunchDeferred();
	//TestTaskValidity();
	//TestTaskMethodWait();
	//TestTaskMethodWaitFor1();
	//TestTaskMethodWaitFor2();
	//TestTaskMethodWaitUntil1();
	//TestTaskMethodWaitUntil2();
	//TestSharedFutures();
	TestTaskDestructor();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------