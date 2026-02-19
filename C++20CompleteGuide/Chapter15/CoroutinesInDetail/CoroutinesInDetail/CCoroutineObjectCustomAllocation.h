//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectCustomAllocationPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void* operator new(std::size_t Count);
		void operator delete(void* Pointer);

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
void* SCoroutineObjectCustomAllocationPromiseType<TCoroutineObject>::operator new(std::size_t Count)
{
	void*														Pointer=std::malloc(Count);

	std::wcout << L"OPERATOR NEW CALLED. POINTER [" << Pointer << L"] COUNT [" << Count << L"]." << std::endl;

	return(Pointer);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationPromiseType<TCoroutineObject>::operator delete(void* Pointer)
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
TCoroutineObject SCoroutineObjectCustomAllocationPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectCustomAllocationPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationPromiseType<TCoroutineObject>::SCoroutineObjectCustomAllocationPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectCustomAllocation final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectCustomAllocationPromiseType<CCoroutineObjectCustomAllocation>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectCustomAllocation& operator=(const CCoroutineObjectCustomAllocation&)=delete;
		CCoroutineObjectCustomAllocation& operator=(CCoroutineObjectCustomAllocation&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectCustomAllocation(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectCustomAllocation(const CCoroutineObjectCustomAllocation&)=delete;
		CCoroutineObjectCustomAllocation(CCoroutineObjectCustomAllocation&& Other) noexcept;
		~CCoroutineObjectCustomAllocation(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------