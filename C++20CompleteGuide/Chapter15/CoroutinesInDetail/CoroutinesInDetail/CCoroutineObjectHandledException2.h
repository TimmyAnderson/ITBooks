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
struct SCoroutineObjectHandledException2PromiseType final
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
TCoroutineObject SCoroutineObjectHandledException2PromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectHandledException2PromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectHandledException2PromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectHandledException2PromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;

	// !!!!! Kedze METHOD je vykonavana v CATCH BLOCK, moze sa pouzit KEYWORD [throw].
	throw;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectHandledException2PromiseType<TCoroutineObject>::return_void(void)
{
	std::wcout << L"METHOD [void return_void(void)] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectHandledException2PromiseType<TCoroutineObject>::SCoroutineObjectHandledException2PromiseType::final_suspend(void) noexcept
{
	std::wcout << L"METHOD [TAwaiter final_suspend(void)] CALLED." << std::endl;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectHandledException2 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectHandledException2PromiseType<CCoroutineObjectHandledException2>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectHandledException2& operator=(const CCoroutineObjectHandledException2&)=delete;
		CCoroutineObjectHandledException2& operator=(CCoroutineObjectHandledException2&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectHandledException2(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectHandledException2(const CCoroutineObjectHandledException2&)=delete;
		CCoroutineObjectHandledException2(CCoroutineObjectHandledException2&& Other) noexcept;
		~CCoroutineObjectHandledException2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------