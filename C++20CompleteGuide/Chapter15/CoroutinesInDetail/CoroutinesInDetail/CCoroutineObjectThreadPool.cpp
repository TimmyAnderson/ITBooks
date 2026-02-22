//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectThreadPool.h"
#include <functional>
#include <utility>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
using namespace std::chrono;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
SCoroutineObjectThreadPoolSynchronousWaitAwaiter::SCoroutineObjectThreadPoolSynchronousWaitAwaiter(binary_semaphore& Semaphore)
	: MSemaphore(Semaphore)
{
}
//----------------------------------------------------------------------------------------------------------------------
SCoroutineObjectThreadPoolSynchronousWaitAwaiter::~SCoroutineObjectThreadPoolSynchronousWaitAwaiter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool SCoroutineObjectThreadPoolSynchronousWaitAwaiter::await_ready(void) noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
bool SCoroutineObjectThreadPoolSynchronousWaitAwaiter::await_suspend(std::coroutine_handle<void> Handle) noexcept
{
	(void) Handle;

	// !!! Uvolni sa SEMAPHORE.
	MSemaphore.release();

	// !!! COROUTINE SUSPENSION nebude vykonana.
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
void SCoroutineObjectThreadPoolSynchronousWaitAwaiter::await_resume(void) noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPool::CCoroutineObjectThreadPool(coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPool::CCoroutineObjectThreadPool(CCoroutineObjectThreadPool&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPool::~CCoroutineObjectThreadPool(void) noexcept
{
	if (static_cast<bool>(MHandle)==true)
	{
		MHandle.destroy();
		MHandle=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPool& CCoroutineObjectThreadPool::operator=(CCoroutineObjectThreadPool&& Other) noexcept
{
	if (this!=&Other)
	{
		if (static_cast<bool>(MHandle)==true)
		{
			MHandle.destroy();
			MHandle=nullptr;
		}

		MHandle=move(Other.MHandle);

		Other.MHandle=nullptr;
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
coroutine_handle<CCoroutineObjectThreadPool::promise_type>& CCoroutineObjectThreadPool::GetHandle(void)
{
	return(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
SCoroutineObjectThreadPoolAwaiter<CCoroutineObjectThreadPool::promise_type> CCoroutineObjectThreadPool::operator co_await(void) noexcept
{
	// !!!!! METHOD [exchange()] vracia obsah PARAMETER [MHandle], a zaroven PARAMETER [MHandle] nastavi na VALUE [nullptr].
	// !!!!! Instancia [SCoroutineObjectThreadPoolAwaiter<promise_type>] bude obsahovat COROUTINE HANDLE, ktora reprezentuje COROUTINE, ktora sa ma spustit ako nasledujuca.
	// !!!!! Nastavenie FIELD [MHandle] na VALUE [nullptr] je korektne, pretoze OPERATOR [OPERATOR co_await] sa VZDY vola pri spusteni NOVEJ COROUTINE. NIKDY sa nevola pre tu istu COROUTINE VIACKRAT.
	SCoroutineObjectThreadPoolAwaiter<promise_type>				Awaiter{exchange(MHandle,nullptr)};

	return(Awaiter);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPoolThreadPool::CCoroutineObjectThreadPoolThreadPool(int ThreadPoolSize)
{
	for (int Index=0;Index<ThreadPoolSize;++Index)
	{
		// !!!!! LAMBDA FUNCTION spusta METHOD [ThreadLoop()].
		jthread													Worker_thread{[this](stop_token StopToken){ThreadLoop(StopToken);}};

		MThreads.push_back(move(Worker_thread));
	}
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPoolThreadPool::~CCoroutineObjectThreadPoolThreadPool(void) noexcept
{
	// !!! Vykonaju sa REQUESTS na zastavenie vsetkych THREADS.
	for(jthread& Thread : MThreads)
	{
		Thread.request_stop();
	}

	// !!! Vycka sa na zastavenie vsetkych THREADS.
	for(jthread& Thread : MThreads)
	{
		Thread.join();
	}

	// !!! Uvolnia sa COROUTINE HANDLES.
	for(coroutine_handle<CCoroutineObjectThreadPool::promise_type>& CorutineHandle : MCorutineHandles)
	{
		CorutineHandle.destroy();
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD spusta COROUTINE.
void CCoroutineObjectThreadPoolThreadPool::RunCoroutine(coroutine_handle<CCoroutineObjectThreadPool::promise_type> CoroutineHandle)
{
	// !!! Dvihne sa pocet beziacich COROUTINES.
    ++MNumberOfCoroutines;

	CCoroutineObjectThreadPool::promise_type&					Promise=CoroutineHandle.promise();

	Promise.SetThreadPool(this);

    {
		scoped_lock												Lock(MMutex);

		// !!! COROUTINE HANDLE sa vlozi do LIST COROUTINE HANDLES.
		MCorutineHandles.push_front(CoroutineHandle);

		// !!! Posle NOTIFICATION do THREAD LOOP ROUTINE.
		MConditionalVariable.notify_one();
    }
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD predstavuje THREAD METHOD THREAD POOL THREAD.
// !!!!! PARAMETER [stop_token StopToken] umoznuje signalizaciu danemu THREAD, ze ma byt ukonceny.
void CCoroutineObjectThreadPoolThreadPool::ThreadLoop(stop_token StopToken)
{
	// !!! Vykonava sa kontrola ci THREAD nebol poziadany o skoncenie vykonavania svojho CODE.
    while(StopToken.stop_requested()==false)
	{
		coroutine_handle<CCoroutineObjectThreadPool::promise_type>	CoroutineHandle;

		{
			unique_lock											Lock(MMutex);

			// !!!!! Caka sa na signalizaciu CONDITIONAL VARIABLE.
			bool												IsNonEmpty=MConditionalVariable.wait(Lock,StopToken,[&]{return(!MCorutineHandles.empty());});

			if (IsNonEmpty==false)
			{
				return;
			}

			// !!! COROUTINE HANDLE sa vyberie z LIST.
			CoroutineHandle=MCorutineHandles.back();

			// !!! COROUTINE HANDLE sa odstrani z LIST.
			MCorutineHandles.pop_back();
		}

		// !!!!! Vykona sa RESUME COROUTINE.
		CoroutineHandle.resume();

		function<void(coroutine_handle<CCoroutineObjectThreadPool::promise_type>)>	DestroyFunction;

		// !!!!! LAMBDA FUNCTION REKURZIVNE kontroluje ci CURRENT COROUTINE a CONTINUOUS COROUTINES nie su skoncene, a ak ano, tak ich uvolni volanim METHOD [void coroutine_handle<TPromiseType>::destroy(void) const noexcept].
		DestroyFunction=[&DestroyFunction,this](coroutine_handle<CCoroutineObjectThreadPool::promise_type> CoroutineHandle)
		{
			if (static_cast<bool>(CoroutineHandle)==true && CoroutineHandle.done()==true)
			{
				CCoroutineObjectThreadPool::promise_type&		PromiseType=CoroutineHandle.promise();

				coroutine_handle<CCoroutineObjectThreadPool::promise_type>	NextCoroutineHandle=PromiseType.GetNextCoroutineHandle();

				CoroutineHandle.destroy();

				--MNumberOfCoroutines;

				// !!!!! Rekurzivne sa uvolnuju COROUTINE HANDLES CONTINUOUS COROUTINES.
				DestroyFunction(NextCoroutineHandle);
			}
		};

		// !!! Vykona sa DESTROY COROUTINE HANDLES.
		DestroyFunction(CoroutineHandle);

		MNumberOfCoroutines.notify_all();

		milliseconds											Timeout(100);
		
		this_thread::sleep_for(milliseconds{100});
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD vlozi COROUTINE do THREAD POOL.
void CCoroutineObjectThreadPoolThreadPool::RunTask(CCoroutineObjectThreadPool&& CoroutineObject)
{
	// !!! Z COROUTINE OBJECT sa vyberie COROUTINE HANDLE pricom COROUTINE HANDLE sa v COROUTINE OBJECT nastavi na VALUE [nullptr].
	// !!!!! COROUTINE HANDLE uz NIE JE v COROUTINE OBJECT potrebny, pretoze COROUTINE OBJECT ho uz nikdy viac nepouzije. A preto moze byt nastaveny na VALUE [nullptr].
	// !!!!! Nastavenie COROUTINE HANDLE v COROUTINE OBJECT na VALUE [nullptr] je dolezite preto, aby COROUTINE OBJECT NEVOLAL vo svojom DESTRUCTOR METHOD [void coroutine_handle<TPromiseType>::destroy(void) const noexcept]. METHOD [void coroutine_handle<TPromiseType>::destroy(void) const noexcept] je volana priamo v THREAD POOL.
	coroutine_handle<CCoroutineObjectThreadPool::promise_type>	Handle=exchange(CoroutineObject.GetHandle(),nullptr);

	bool														IsDone=Handle.done();

	if (IsDone==true)
	{
		Handle.destroy();
    }
    else
	{
		RunCoroutine(Handle);
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectThreadPoolThreadPool::RunTaskSynchronously(CCoroutineObjectThreadPool&& CoroutineObject)
{
	binary_semaphore											Semaphore(0);

	auto														WaitingTask=[&](void)->CCoroutineObjectThreadPool
	{
		// !!! Caka sa na skoncenie COROUTINE.
		co_await CoroutineObject;

		// !!! AWAITER signalizuje SEMAPHORE.
		co_await SCoroutineObjectThreadPoolSynchronousWaitAwaiter{Semaphore};
	};

	// !!! Spusti sa COROUTINE, ktora bude cakat na skoncenie.
	RunTask(WaitingTask());

	Semaphore.acquire();
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! METHOD vykonava BLOCKING CURRENT THREAD, az kym vsetky COROUTINES nie su skoncene.
void CCoroutineObjectThreadPoolThreadPool::WaitUntilAllCoroutinesFinished(void)
{
	int															NumberOfCoroutines=MNumberOfCoroutines.load();

	// !!! Cyklus bezi, kym bezia nejake COROUTINES.
	while(NumberOfCoroutines>0)
	{
		// !!! THREAD je BLOCKED, az kym nedojde k zmene VALUE a ATOMIC VALUE je NOTIFIED.
		MNumberOfCoroutines.wait(NumberOfCoroutines);

		NumberOfCoroutines=MNumberOfCoroutines.load();
	}
}
//----------------------------------------------------------------------------------------------------------------------