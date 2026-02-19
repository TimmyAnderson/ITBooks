//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectStandardAwaiterPromiseType final
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
TCoroutineObject SCoroutineObjectStandardAwaiterPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle<SCoroutineObjectStandardAwaiterPromiseType>	Handle=std::coroutine_handle<SCoroutineObjectStandardAwaiterPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectStandardAwaiterPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectStandardAwaiterPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectStandardAwaiterPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectStandardAwaiterPromiseType<TCoroutineObject>::SCoroutineObjectStandardAwaiterPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectStandardAwaiter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectStandardAwaiterPromiseType<CCoroutineObjectStandardAwaiter>;

	private:
		std::coroutine_handle<SCoroutineObjectStandardAwaiterPromiseType<CCoroutineObjectStandardAwaiter>>	MHandle;

	public:
		CCoroutineObjectStandardAwaiter& operator=(const CCoroutineObjectStandardAwaiter&)=delete;
		CCoroutineObjectStandardAwaiter& operator=(CCoroutineObjectStandardAwaiter&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectStandardAwaiter(std::coroutine_handle<SCoroutineObjectStandardAwaiterPromiseType<CCoroutineObjectStandardAwaiter>> Handle);
		CCoroutineObjectStandardAwaiter(const CCoroutineObjectStandardAwaiter&)=delete;
		CCoroutineObjectStandardAwaiter(CCoroutineObjectStandardAwaiter&& Other) noexcept;
		~CCoroutineObjectStandardAwaiter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------