//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <string>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													PromiseType=SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>;

	private:
		std::wstring											MCoroutineName;
		// !!! HANDLE na SUB COROUTINE.
		std::coroutine_handle<PromiseType>						MHandle;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		const std::coroutine_handle<PromiseType>& GetHandle(void) const noexcept;
		void SetHandle(const std::coroutine_handle<PromiseType>& Handle) noexcept;
		std::wstring GetCoroutineName(void) const noexcept;

	public:
		SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType(std::wstring CoroutineName);
		~SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType(std::wstring CoroutineName)
	// !!! PROMISE TYPE na zaciatku neobsahuje HANDLE na SUB COROUTINE.
	: MCoroutineName(CoroutineName), MHandle(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::~SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType(void)
{
	// !!!!! METHOD NESMIE vykonat DESTROY COROUTINE HANDLE, pretoze DESTROY COROUTINE HANDLE sa robi az v samotnom COROUTINE OBJECT [CCoroutineObjectWithAwaiterInterfaceFaulty].
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
const std::coroutine_handle<typename SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::PromiseType>& SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::GetHandle(void) const noexcept
{
	return(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::SetHandle(const std::coroutine_handle<typename SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::PromiseType>& Handle) noexcept
{
	MHandle=Handle;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::wstring SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<TCoroutineObject>::GetCoroutineName(void) const noexcept
{
	return(MCoroutineName);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je COROUTINE OBJECT.
class [[nodiscard]] CCoroutineObjectWithAwaiterInterfaceFaulty final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectWithAwaiterInterfaceFaultyPromiseType<CCoroutineObjectWithAwaiterInterfaceFaulty>;

	private:
		// !!! HANDLE na COROUTINE.
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectWithAwaiterInterfaceFaulty& operator=(const CCoroutineObjectWithAwaiterInterfaceFaulty&)=delete;
		CCoroutineObjectWithAwaiterInterfaceFaulty& operator=(CCoroutineObjectWithAwaiterInterfaceFaulty&& Other) noexcept;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		// !!!!! METHOD kontroluje ci PROMISE TYPE neobsahuje HANDLE na SUB COROUTINE a ak ano a ta je SUSPENDED, tak vrati tento jej stav.
		bool Resume(void) const;

	public:
		// !!!!! METHODS implementuju AWAITER INTERFACE.
		bool await_ready(void) const noexcept;
		template<typename TPromiseType>
		void await_suspend(std::coroutine_handle<TPromiseType> Handle) const noexcept;
		void await_resume(void) const noexcept;

	public:
		CCoroutineObjectWithAwaiterInterfaceFaulty(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectWithAwaiterInterfaceFaulty(const CCoroutineObjectWithAwaiterInterfaceFaulty&)=delete;
		CCoroutineObjectWithAwaiterInterfaceFaulty(CCoroutineObjectWithAwaiterInterfaceFaulty&& Other) noexcept;
		~CCoroutineObjectWithAwaiterInterfaceFaulty(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARAMETER obsahuje COROUTINE HANDLE na CURRENT COROUTINE v ktorej sa pouzil OPERATOR [OPERATOR co_await], alebo OPERATOR [OPERATOR co_yield].
template<typename TPromiseType>
void CCoroutineObjectWithAwaiterInterfaceFaulty::await_suspend(std::coroutine_handle<TPromiseType> Handle) const noexcept
{
	// !!!!! Do CURRENT COROUTINE PROMISE sa ulozi HANDLE na SUB COROUTINE.
	Handle.promise().SetHandle(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------