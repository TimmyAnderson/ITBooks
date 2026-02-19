//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TYPE ma OVERLOADED OPERATOR [OPERATOR co_await].
class CCoroutineObjectCustomOperatorCoAwaitAwaiter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		std::suspend_always operator co_await(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectCustomOperatorCoAwaitPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectCustomOperatorCoAwaitPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle<SCoroutineObjectCustomOperatorCoAwaitPromiseType>	Handle=std::coroutine_handle<SCoroutineObjectCustomOperatorCoAwaitPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomOperatorCoAwaitPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomOperatorCoAwaitPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomOperatorCoAwaitPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomOperatorCoAwaitPromiseType<TCoroutineObject>::SCoroutineObjectCustomOperatorCoAwaitPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectCustomOperatorCoAwait final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectCustomOperatorCoAwaitPromiseType<CCoroutineObjectCustomOperatorCoAwait>;

	private:
		std::coroutine_handle<SCoroutineObjectCustomOperatorCoAwaitPromiseType<CCoroutineObjectCustomOperatorCoAwait>>	MHandle;

	public:
		CCoroutineObjectCustomOperatorCoAwait& operator=(const CCoroutineObjectCustomOperatorCoAwait&)=delete;
		CCoroutineObjectCustomOperatorCoAwait& operator=(CCoroutineObjectCustomOperatorCoAwait&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectCustomOperatorCoAwait(std::coroutine_handle<SCoroutineObjectCustomOperatorCoAwaitPromiseType<CCoroutineObjectCustomOperatorCoAwait>> Handle);
		CCoroutineObjectCustomOperatorCoAwait(const CCoroutineObjectCustomOperatorCoAwait&)=delete;
		CCoroutineObjectCustomOperatorCoAwait(CCoroutineObjectCustomOperatorCoAwait&& Other) noexcept;
		~CCoroutineObjectCustomOperatorCoAwait(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------