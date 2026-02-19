//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
#include <iostream>
#include "Helpers/CException.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectHandledException1PromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		bool													MThrowExceptionInCoroutineBody;
		bool													MThrowExceptionInPromiseTypeMethodInitialSuspend;
		bool													MThrowExceptionInPromiseTypeMethodReturnVoid;
		std::exception_ptr										MExceptionPointer;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		const std::exception_ptr& GetExceptionPointer(void) const noexcept;

	public:
		SCoroutineObjectHandledException1PromiseType(bool ThrowExceptionInCoroutineBody, bool ThrowExceptionInPromiseTypeMethodInitialSuspend, bool ThrowExceptionInPromiseTypeMethodReturnVoid);
		SCoroutineObjectHandledException1PromiseType(const SCoroutineObjectHandledException1PromiseType&)=delete;
		SCoroutineObjectHandledException1PromiseType(SCoroutineObjectHandledException1PromiseType&&)=delete;
		~SCoroutineObjectHandledException1PromiseType(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::SCoroutineObjectHandledException1PromiseType(bool ThrowExceptionInCoroutineBody, bool ThrowExceptionInPromiseTypeMethodInitialSuspend, bool ThrowExceptionInPromiseTypeMethodReturnVoid)
	: MThrowExceptionInCoroutineBody(ThrowExceptionInCoroutineBody), MThrowExceptionInPromiseTypeMethodInitialSuspend(ThrowExceptionInPromiseTypeMethodInitialSuspend), MThrowExceptionInPromiseTypeMethodReturnVoid(ThrowExceptionInPromiseTypeMethodReturnVoid), MExceptionPointer()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::~SCoroutineObjectHandledException1PromiseType(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectHandledException1PromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::initial_suspend(void)
{
	if (MThrowExceptionInPromiseTypeMethodInitialSuspend==true)
	{
		// !!!!! EXCEPTION v METHOD [TAwaiter initial_suspend(void)] sposobi UNDEFINED BEHAVIOR.
		throw(CException(L"EXCEPTION in PROMISE TYPE METHOD [TAwaiter initial_suspend(void)]."));
	}

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;

	MExceptionPointer=std::current_exception();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::return_void(void)
{
	std::wcout << L"METHOD [void return_void(void)] CALLED." << std::endl;

	if (MThrowExceptionInPromiseTypeMethodReturnVoid==true)
	{
		throw(CException(L"EXCEPTION in PROMISE TYPE METHOD [void return_void(void)]."));
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::SCoroutineObjectHandledException1PromiseType::final_suspend(void) noexcept
{
	std::wcout << L"METHOD [TAwaiter final_suspend(void)] CALLED." << std::endl;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
const std::exception_ptr& SCoroutineObjectHandledException1PromiseType<TCoroutineObject>::GetExceptionPointer(void) const noexcept
{
	return(MExceptionPointer);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectHandledException1 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectHandledException1PromiseType<CCoroutineObjectHandledException1>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectHandledException1& operator=(const CCoroutineObjectHandledException1&)=delete;
		CCoroutineObjectHandledException1& operator=(CCoroutineObjectHandledException1&& Other) noexcept;

	public:
		bool Resume(void) const;
		void ThrowUnhandledException(void) const;

	public:
		CCoroutineObjectHandledException1(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectHandledException1(const CCoroutineObjectHandledException1&)=delete;
		CCoroutineObjectHandledException1(CCoroutineObjectHandledException1&& Other) noexcept;
		~CCoroutineObjectHandledException1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------