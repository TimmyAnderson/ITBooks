//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectUnhandledExceptionPromiseType final
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
TCoroutineObject SCoroutineObjectUnhandledExceptionPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectUnhandledExceptionPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectUnhandledExceptionPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectUnhandledExceptionPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectUnhandledExceptionPromiseType<TCoroutineObject>::return_void(void)
{
	std::wcout << L"METHOD [void return_void(void)] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectUnhandledExceptionPromiseType<TCoroutineObject>::SCoroutineObjectUnhandledExceptionPromiseType::final_suspend(void) noexcept
{
	std::wcout << L"METHOD [TAwaiter final_suspend(void)] CALLED." << std::endl;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectUnhandledException final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectUnhandledExceptionPromiseType<CCoroutineObjectUnhandledException>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectUnhandledException& operator=(const CCoroutineObjectUnhandledException&)=delete;
		CCoroutineObjectUnhandledException& operator=(CCoroutineObjectUnhandledException&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectUnhandledException(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectUnhandledException(const CCoroutineObjectUnhandledException&)=delete;
		CCoroutineObjectUnhandledException(CCoroutineObjectUnhandledException&& Other) noexcept;
		~CCoroutineObjectUnhandledException(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------