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
		jthread													Worker_thread{[this](stop_token StopToken){ThreadLoop(StopToken);}};

		MThreads.push_back(move(Worker_thread));
	}
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectThreadPoolThreadPool::~CCoroutineObjectThreadPoolThreadPool(void) noexcept
{
	for(jthread& Thread : MThreads)
	{
		Thread.request_stop();
	}

	for(jthread& Thread : MThreads)
	{
		Thread.join();
	}

	for(coroutine_handle<CCoroutineObjectThreadPool::promise_type>& CorutineHandle : MCorutineHandles)
	{
		CorutineHandle.destroy();
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectThreadPoolThreadPool::RunCoroutine(coroutine_handle<CCoroutineObjectThreadPool::promise_type> CoroutineHandle)
{
    ++MNumberOfCoroutines;

	CCoroutineObjectThreadPool::promise_type&					Promise=CoroutineHandle.promise();

	Promise.SetThreadPool(this);

    {
		scoped_lock												Lock(MMutex);

		MCorutineHandles.push_front(CoroutineHandle);

		MConditionalVariable.notify_one();
    }
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectThreadPoolThreadPool::ThreadLoop(stop_token StopToken)
{
    while (StopToken.stop_requested()==false)
	{
		coroutine_handle<CCoroutineObjectThreadPool::promise_type>	CoroutineHandle;

		{
			unique_lock											Lock(MMutex);

			bool												IsNonEmpty=MConditionalVariable.wait(Lock,StopToken,[&]{return(!MCorutineHandles.empty());});

			if (IsNonEmpty==false)
			{
				return;
			}

			CoroutineHandle=MCorutineHandles.back();

			MCorutineHandles.pop_back();
		}

		CoroutineHandle.resume();

		function<void(coroutine_handle<CCoroutineObjectThreadPool::promise_type>)>	DestroyFunction;

		DestroyFunction=[&DestroyFunction,this](coroutine_handle<CCoroutineObjectThreadPool::promise_type> CoroutineHandle)
		{
			if (static_cast<bool>(CoroutineHandle)==true && CoroutineHandle.done()==true)
			{
				CCoroutineObjectThreadPool::promise_type&		PromiseType=CoroutineHandle.promise();

				coroutine_handle<CCoroutineObjectThreadPool::promise_type>	NextCoroutineHandle=PromiseType.GetNextCoroutineHandle();

				CoroutineHandle.destroy();

				--MNumberOfCoroutines;

				DestroyFunction(NextCoroutineHandle);
			}
		};

		DestroyFunction(CoroutineHandle);

		MNumberOfCoroutines.notify_all();

		milliseconds											Timeout(100);
		
		this_thread::sleep_for(milliseconds{100});
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectThreadPoolThreadPool::RunTask(CCoroutineObjectThreadPool&& CoroutineObject)
{
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
void CCoroutineObjectThreadPoolThreadPool::WaitUntilAllCoroutinesFinished(void)
{
	int															NumberOfCoroutines=MNumberOfCoroutines.load();

	while(NumberOfCoroutines>0)
	{
		MNumberOfCoroutines.wait(NumberOfCoroutines);

		NumberOfCoroutines=MNumberOfCoroutines.load();
	}
}
//----------------------------------------------------------------------------------------------------------------------