//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectCustomAllocationWithParametersPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!!!! OPERATOR [OPERATOR new] moze mat ako OPTIONAL PARAMETERS vsetky COROUTINE PARAMETERS, ktore su do OPERATOR [OPERATOR new] prenesene.
		void* operator new(std::size_t Count, int Value1, double Value2);
		// !!!!! OPERATOR [OPERATOR delete] moze mat ako OPTIONAL PARAMETER [Count] obsahujuci pocet alokovanych BYTES.
		void operator delete(void* Pointer, std::size_t Count);

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
// !!!!! OPERATOR [OPERATOR new] moze mat ako OPTIONAL PARAMETERS vsetky COROUTINE PARAMETERS, ktore su do OPERATOR [OPERATOR new] prenesene.
template<typename TCoroutineObject>
void* SCoroutineObjectCustomAllocationWithParametersPromiseType<TCoroutineObject>::operator new(std::size_t Count, int Value1, double Value2)
{
	void*														Pointer=std::malloc(Count);

	std::wcout << L"OPERATOR NEW CALLED. POINTER [" << Pointer << L"] COUNT [" << Count << L"]. VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;

	return(Pointer);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationWithParametersPromiseType<TCoroutineObject>::operator delete(void* Pointer, std::size_t Count)
{
	std::wcout << L"OPERATOR DELETE CALLED. POINTER [" << Pointer << L"] COUNT [" << Count << L"]." << std::endl;

	if (Pointer!=nullptr)
	{
		std::free(Pointer);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectCustomAllocationWithParametersPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectCustomAllocationWithParametersPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationWithParametersPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationWithParametersPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectCustomAllocationWithParametersPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectCustomAllocationWithParametersPromiseType<TCoroutineObject>::SCoroutineObjectCustomAllocationWithParametersPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectCustomAllocationWithParameters final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectCustomAllocationWithParametersPromiseType<CCoroutineObjectCustomAllocationWithParameters>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectCustomAllocationWithParameters& operator=(const CCoroutineObjectCustomAllocationWithParameters&)=delete;
		CCoroutineObjectCustomAllocationWithParameters& operator=(CCoroutineObjectCustomAllocationWithParameters&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CCoroutineObjectCustomAllocationWithParameters(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectCustomAllocationWithParameters(const CCoroutineObjectCustomAllocationWithParameters&)=delete;
		CCoroutineObjectCustomAllocationWithParameters(CCoroutineObjectCustomAllocationWithParameters&& Other) noexcept;
		~CCoroutineObjectCustomAllocationWithParameters(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------