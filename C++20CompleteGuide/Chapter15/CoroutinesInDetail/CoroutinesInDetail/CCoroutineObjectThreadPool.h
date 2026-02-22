//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <semaphore>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! AWAITER OBJECT, ktory spusti dalsiu COROUTINE.
template<typename TCoroutineObject>
struct SCoroutineObjectThreadPoolFinalAwaiter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		bool await_ready(void) noexcept;
		std::coroutine_handle<void> await_suspend(std::coroutine_handle<typename TCoroutineObject::promise_type> Handle) noexcept;
		void await_resume(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
bool SCoroutineObjectThreadPoolFinalAwaiter<TCoroutineObject>::await_ready(void) noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER [Handle] je COROUTINE HANDLE na COROUTINE, v ktorej bol volany OPERATOR [OPERATOR co_await].
template<typename TCoroutineObject>
std::coroutine_handle<void> SCoroutineObjectThreadPoolFinalAwaiter<TCoroutineObject>::await_suspend(std::coroutine_handle<typename TCoroutineObject::promise_type> Handle) noexcept
{
	// !!! Ziska sa PROMISE TYPE OBJECT pre COROUTINE, v ktorej bol volany OPERATOR [OPERATOR co_await].
	typename TCoroutineObject::promise_type&					PromiseObject=Handle.promise();

	// !!! Ziska sa COROUTINE HANDLE na nasledujucu COROUTINE HANDLE.
	// !!! C++ vykonava CONVERSION TYPE [coroutine_handle<TCoroutineObject::promise_type>] na TYPE volanim CONVERSION OPERATOR [OPERATOR coroutine_handle<void>].
	std::coroutine_handle<void>									CoroutineHandle=PromiseObject.GetNextCoroutineHandle();

	if (static_cast<bool>(CoroutineHandle)==true)
	{
		// !!!!! Vracia sa COROUTINE HANDLE na nasledujucu COROUTINE, ktora sa ma spustit po skonceni CURRENT COROUTINE.
		return(CoroutineHandle);
	}
	else
	{
		// !!! C++ vykonava CONVERSION TYPE [coroutine_handle<noop_coroutine_promise>] na TYPE volanim CONVERSION OPERATOR [OPERATOR coroutine_handle<void>].
		std::coroutine_handle<void>								NoOperationCoroutineHandle=std::noop_coroutine();

		return(NoOperationCoroutineHandle);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectThreadPoolFinalAwaiter<TCoroutineObject>::await_resume(void) noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!!! CLASS reprezentuje SYNCHRONOUS WAIT AWAITER pre SYNCHRONOUS WAIT.
struct SCoroutineObjectThreadPoolSynchronousWaitAwaiter final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::binary_semaphore&									MSemaphore;

	public:
		bool await_ready(void) noexcept;
		bool await_suspend(std::coroutine_handle<void> Handle) noexcept;
		void await_resume(void) noexcept;

	public:
		SCoroutineObjectThreadPoolSynchronousWaitAwaiter(std::binary_semaphore& Semaphore);
		~SCoroutineObjectThreadPoolSynchronousWaitAwaiter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCoroutineObjectThreadPoolThreadPool;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! STRUCTURE reprezentuje PROMISE TYPE COROUTINE OBJECT.
template<typename TCoroutineObject>
struct SCoroutineObjectThreadPoolPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! FIELD obsahuje COROUTINE HANDLE na COROUTINE, ktora sa ma spustit po skonceni vykonavania COROUTINE, ktoru reprezentuje PROMISE TYPE.
		std::coroutine_handle<SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>>	MNextCoroutineHandle;
		CCoroutineObjectThreadPoolThreadPool*					MThreadPool;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void) noexcept;
		void return_void(void) noexcept;
		SCoroutineObjectThreadPoolFinalAwaiter<TCoroutineObject> final_suspend(void) noexcept;

	public:
		std::coroutine_handle<SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>> GetNextCoroutineHandle(void);
		void SetNextCoroutineHandle(std::coroutine_handle<SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>> NextCoroutineHandle);
		CCoroutineObjectThreadPoolThreadPool* GetThreadPool(void);
		void SetThreadPool(CCoroutineObjectThreadPoolThreadPool* ThreadPool);

	public:
		SCoroutineObjectThreadPoolPromiseType(void);
		~SCoroutineObjectThreadPoolPromiseType(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::SCoroutineObjectThreadPoolPromiseType(void)
	: MNextCoroutineHandle(nullptr), MThreadPool(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::~SCoroutineObjectThreadPoolPromiseType(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectThreadPoolPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Awaiter{};

	return(Awaiter);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::unhandled_exception(void) noexcept
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::return_void(void) noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectThreadPoolFinalAwaiter<TCoroutineObject> SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::final_suspend(void) noexcept
{
	// !!! Pri skonceni COROUTINE sa vrati FINAL AWAITER, ktory spusti dalsiu COROUTINE.
	// !!!!! FINAL AWAITER ziskava COROUTINE HANDLE na dalsiu COROUTINE tak, ze C++ vola FINAL AWAITER METHOD [coroutine_handle<void> await_suspend(coroutine_handle<typename TCoroutineObject::promise_type> Handle) noexcept], ktora ziska COROUTINE HANDLE nasledujuce COROUTINE z PROMISE TYPE aktualne ukoncenej COROUTINE.
	SCoroutineObjectThreadPoolFinalAwaiter<TCoroutineObject>	FinalAwaiter{};

	return(FinalAwaiter);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::coroutine_handle<SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>> SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::GetNextCoroutineHandle(void)
{
	return(MNextCoroutineHandle);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::SetNextCoroutineHandle(std::coroutine_handle<SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>> NextCoroutineHandle)
{
	MNextCoroutineHandle=NextCoroutineHandle;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
CCoroutineObjectThreadPoolThreadPool* SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::GetThreadPool(void)
{
	return(MThreadPool);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectThreadPoolPromiseType<TCoroutineObject>::SetThreadPool(CCoroutineObjectThreadPoolThreadPool* ThreadPool)
{
	MThreadPool=ThreadPool;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! STRUCTURE reprezentuje AWAITER, ktory je pouzivany pre spustanie COROUTINES v rozlicnych THREADS.
template<typename TPromiseType>
struct SCoroutineObjectThreadPoolAwaiter final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::coroutine_handle<TPromiseType>						MHandle;

	public:
		bool await_ready(void) noexcept;
		void await_suspend(std::coroutine_handle<TPromiseType> AwaitingHandle) noexcept;
		void await_resume(void) noexcept;

	public:
		SCoroutineObjectThreadPoolAwaiter(std::coroutine_handle<TPromiseType> Handle);
		~SCoroutineObjectThreadPoolAwaiter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType>
SCoroutineObjectThreadPoolAwaiter<TPromiseType>::SCoroutineObjectThreadPoolAwaiter(std::coroutine_handle<TPromiseType> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType>
SCoroutineObjectThreadPoolAwaiter<TPromiseType>::~SCoroutineObjectThreadPoolAwaiter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType>
bool SCoroutineObjectThreadPoolAwaiter<TPromiseType>::await_ready(void) noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType>
void SCoroutineObjectThreadPoolAwaiter<TPromiseType>::await_resume(void) noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje COROUTINE OBJECT.
class [[nodiscard]] CCoroutineObjectThreadPool final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectThreadPoolPromiseType<CCoroutineObjectThreadPool>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectThreadPool& operator=(const CCoroutineObjectThreadPool&)=delete;
		CCoroutineObjectThreadPool& operator=(CCoroutineObjectThreadPool&& Other) noexcept;

	public:
		// !!!!! OVERLOADED OPERATOR sa vola ked COROUTINE pouzivajuca THREAD POOL zavola OPERATOR [OPERATOR co_await].
		// !!!!! OVERLOADED OPERATOR vracia AWAITER OBJECT TYPE [SCoroutineObjectThreadPoolAwaiter<promise_type>].
		SCoroutineObjectThreadPoolAwaiter<promise_type> operator co_await(void) noexcept;

	public:
		std::coroutine_handle<promise_type>& GetHandle(void);

	public:
		explicit CCoroutineObjectThreadPool(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectThreadPool(const CCoroutineObjectThreadPool&)=delete;
		CCoroutineObjectThreadPool(CCoroutineObjectThreadPool&& Other) noexcept;
		~CCoroutineObjectThreadPool(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje THREAD POOL pracujuci s COROUTINE OBJECTS.
class CCoroutineObjectThreadPoolThreadPool final
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TPromiseType>
	friend struct SCoroutineObjectThreadPoolAwaiter;

	private:
		// !!! FIELD obsahuje MUTEX, ktory chrani pristup k FIELD [MCorutineHandles].
		std::mutex												MMutex;
		// !!! FIELD obsahuje CONDITONAL VARIABLE, ktora spolu s MUTEX chrani pristup k FIELD [MCorutineHandles].
		std::condition_variable_any								MConditionalVariable;
		// !!! FIELD obsahuje pocet NEUKONCENYCH COROUTINES vo FIELD [MCorutineHandles].
		std::atomic<int>										MNumberOfCoroutines;
		// !!! FIELD obsahuje pocet THREADS THREAD POOL, ktore vykonavaju COROUTINES.
		// !!!!! Pocet THREADS je KONSTATNTNY.
		std::list<std::jthread>									MThreads;
		// !!! FIELD obsahuje COROUTINE HANDLES na COROUTINES, ktore maju byt vykonane v THREAD POOL.
		std::list<std::coroutine_handle<CCoroutineObjectThreadPool::promise_type>>	MCorutineHandles;

	private:
		// !!! METHOD spusta COROUTINE.
		void RunCoroutine(std::coroutine_handle<CCoroutineObjectThreadPool::promise_type> CoroutineHandle);
		// !!!!! METHOD predstavuje THREAD METHOD THREAD POOL THREAD.
		// !!!!! PARAMETER [stop_token StopToken] umoznuje signalizaciu danemu THREAD, ze ma byt ukonceny.
		void ThreadLoop(std::stop_token StopToken);

	public:
		// !!! METHOD vlozi COROUTINE do THREAD POOL.
		void RunTask(CCoroutineObjectThreadPool&& CoroutineObject);
		// !!! METHOD vlozi COROUTINE do THREAD POOL a SYNCHRONNE caka na jej koniec.
		void RunTaskSynchronously(CCoroutineObjectThreadPool&& CoroutineObject);
		// !!!!! METHOD vykonava BLOCKING CURRENT THREAD, az kym vsetky COROUTINES nie su skoncene.
		void WaitUntilAllCoroutinesFinished(void);

	public:
		CCoroutineObjectThreadPoolThreadPool& operator=(CCoroutineObjectThreadPoolThreadPool&)=delete;
		CCoroutineObjectThreadPoolThreadPool& operator=(CCoroutineObjectThreadPoolThreadPool&&)=delete;

	public:
		CCoroutineObjectThreadPoolThreadPool(int ThreadPoolSize);
		CCoroutineObjectThreadPoolThreadPool(CCoroutineObjectThreadPoolThreadPool&)=delete;
		CCoroutineObjectThreadPoolThreadPool(CCoroutineObjectThreadPoolThreadPool&&)=delete;
		~CCoroutineObjectThreadPoolThreadPool(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PARAMETER [AwaitingHandle] je COROUTINE HANDLE na COROUTINE, v ktorej bol volany OPERATOR [OPERATOR co_await].
template<typename TPromiseType>
void SCoroutineObjectThreadPoolAwaiter<TPromiseType>::await_suspend(std::coroutine_handle<TPromiseType> AwaitingHandle) noexcept
{
	// !!! Ziska sa PROMISE TYPE na COROUTINE, v ktorej bol volany OPERATOR [OPERATOR co_await].
	TPromiseType&												HandleAwaitingPromise=AwaitingHandle.promise();

	// !!! Ziska sa PROMISE TYPE na COROUTINE, ktora ma byt spustena po skonceni aktualnej COROUTINE.
	TPromiseType&												HandlePromise=MHandle.promise();

	// !!! Pre CURRENT COROUTINE sa nastavi COROUTINE HANDLE na COROUTINE, ktora ma byt spustena po skonceni CURRENT COROUTINE.
	HandlePromise.SetNextCoroutineHandle(AwaitingHandle);

	CCoroutineObjectThreadPoolThreadPool*						ThreadPool=HandleAwaitingPromise.GetThreadPool();

	// !!! COROUTINE spusti vykonanie COROUTINE v separatnom THREAD.
	ThreadPool->RunCoroutine(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------