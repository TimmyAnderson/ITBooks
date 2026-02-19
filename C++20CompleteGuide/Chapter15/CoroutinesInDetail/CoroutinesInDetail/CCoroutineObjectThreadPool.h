//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
#include <list>
#include <mutex>
#include <condition_variable>
#include <thread>
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
template<typename TCoroutineObject>
std::coroutine_handle<void> SCoroutineObjectThreadPoolFinalAwaiter<TCoroutineObject>::await_suspend(std::coroutine_handle<typename TCoroutineObject::promise_type> Handle) noexcept
{
	typename TCoroutineObject::promise_type&					PromiseObject=Handle.promise();

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
// !!!!! STRUCTURE reprezentuje AWAITER.
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
		std::mutex												MMutex;
		std::condition_variable_any								MConditionalVariable;
		std::atomic<int>										MNumberOfCoroutines;
		std::list<std::jthread>									MThreads;
		std::list<std::coroutine_handle<CCoroutineObjectThreadPool::promise_type>>	MCorutineHandles;

	private:
		void RunCoroutine(std::coroutine_handle<CCoroutineObjectThreadPool::promise_type> CoroutineHandle);
		void ThreadLoop(std::stop_token StopToken);

	public:
		void RunTask(CCoroutineObjectThreadPool&& CoroutineObject);
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
template<typename TPromiseType>
void SCoroutineObjectThreadPoolAwaiter<TPromiseType>::await_suspend(std::coroutine_handle<TPromiseType> AwaitingHandle) noexcept
{
	TPromiseType&												HandlePromise=MHandle.promise();
	TPromiseType&												HandleAwaitingPromise=AwaitingHandle.promise();

	HandlePromise.SetNextCoroutineHandle(AwaitingHandle);

	CCoroutineObjectThreadPoolThreadPool*						ThreadPool=HandleAwaitingPromise.GetThreadPool();
	
	ThreadPool->RunCoroutine(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------