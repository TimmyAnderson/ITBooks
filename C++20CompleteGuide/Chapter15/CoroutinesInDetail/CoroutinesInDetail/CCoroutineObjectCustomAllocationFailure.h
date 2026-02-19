//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectCustomAllocationFailurePromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! Ak je OPERATOR [OPERATOR new] oznaceny pomocou KEYWORD [noexcept] PROMISE TYPE MUSI definovat STATIC METHOD [TCoroutineObject get_return_object_on_allocation_failure(void)].
		void* operator new(std::size_t Count) noexcept;
		void operator delete(void* Pointer);

	public:
		static TCoroutineObject get_return_object_on_allocation_failure(void);

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
void* SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::operator new(std::size_t Count) noexcept
{
	(void) Count;

	// !!!!! Umyselne sa vracia VALUE [nullptr], aby sa volala STATIC METHOD [TCoroutineObject get_return_object_on_allocation_failure(void)].
	return(nullptr);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::operator delete(void* Pointer)
{
	std::wcout << L"OPERATOR DELETE CALLED. POINTER [" << Pointer << L"]." << std::endl;

	if (Pointer!=nullptr)
	{
		std::free(Pointer);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::get_return_object_on_allocation_failure(void)
{
	std::wcout << L"!!! ALLOCATION FAILURE DETECTED. !!!" << std::endl;

	// !!!!! Vrati sa COROUTINE OBJECT s EMPTY HANDLE, co znamena, ze COROUTINE sa nespusti.
	TCoroutineObject											CoroutineObject(nullptr);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectCustomAllocationFailurePromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationFailurePromiseType<TCoroutineObject>::SCoroutineObjectCustomAllocationFailurePromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectCustomAllocationFailure final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectCustomAllocationFailurePromiseType<CCoroutineObjectCustomAllocationFailure>;

	private:
		std::coroutine_handle<void>								MHandle;

	public:
		CCoroutineObjectCustomAllocationFailure& operator=(const CCoroutineObjectCustomAllocationFailure&)=delete;
		CCoroutineObjectCustomAllocationFailure& operator=(CCoroutineObjectCustomAllocationFailure&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectCustomAllocationFailure(std::coroutine_handle<void> Handle);
		CCoroutineObjectCustomAllocationFailure(const CCoroutineObjectCustomAllocationFailure&)=delete;
		CCoroutineObjectCustomAllocationFailure(CCoroutineObjectCustomAllocationFailure&& Other) noexcept;
		~CCoroutineObjectCustomAllocationFailure(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------