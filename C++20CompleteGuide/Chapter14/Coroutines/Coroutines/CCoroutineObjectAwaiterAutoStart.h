//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectAwaiterAutoStartPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													PromiseType=SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>;

	private:
		int														MID;
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
		int GetID(void) const noexcept;

	public:
		SCoroutineObjectAwaiterAutoStartPromiseType(int ID);
		~SCoroutineObjectAwaiterAutoStartPromiseType(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::SCoroutineObjectAwaiterAutoStartPromiseType(int ID)
	// !!! PROMISE TYPE na zaciatku neobsahuje HANDLE na SUB COROUTINE.
	: MID(ID), MHandle(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::~SCoroutineObjectAwaiterAutoStartPromiseType(void)
{
	// !!!!! METHOD NESMIE vykonat DESTROY COROUTINE HANDLE, pretoze DESTROY COROUTINE HANDLE sa robi az v samotnom COROUTINE OBJECT [CCoroutineObjectAwaiterAutoStart].
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectAwaiterAutoStartPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::SCoroutineObjectAwaiterAutoStartPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
const std::coroutine_handle<typename SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::PromiseType>& SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::GetHandle(void) const noexcept
{
	return(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::SetHandle(const std::coroutine_handle<typename SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::PromiseType>& Handle) noexcept
{
	MHandle=Handle;

	typename TCoroutineObject::promise_type&					ParameterPromise=Handle.promise();

	std:: wcout << L"!!!!! COROUTINE [" << MID << L"] - SET HANDLE CALLED. PARAMETER COROUTINE [" << ParameterPromise.GetID() << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
int SCoroutineObjectAwaiterAutoStartPromiseType<TCoroutineObject>::GetID(void) const noexcept
{
	return(MID);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je COROUTINE OBJECT.
class [[nodiscard]] CCoroutineObjectAwaiterAutoStart final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectAwaiterAutoStartPromiseType<CCoroutineObjectAwaiterAutoStart>;

	private:
		// !!! HANDLE na COROUTINE.
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectAwaiterAutoStart& operator=(const CCoroutineObjectAwaiterAutoStart&)=delete;
		CCoroutineObjectAwaiterAutoStart& operator=(CCoroutineObjectAwaiterAutoStart&& Other) noexcept;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		// !!!!! METHOD kontroluje ci PROMISE TYPE neobsahuje HANDLE na SUB COROUTINE a ak ano a ta je SUSPENDED, tak vrati tento jej stav.
		bool Resume(void) const;

	public:
		// !!!!! METHODS implementuju AWAITER INTERFACE.
		bool await_ready(void) const noexcept;
		template<typename TPromiseType>
		std::coroutine_handle<promise_type> await_suspend(std::coroutine_handle<TPromiseType> Handle) const noexcept;
		void await_resume(void) const noexcept;

	public:
		CCoroutineObjectAwaiterAutoStart(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectAwaiterAutoStart(const CCoroutineObjectAwaiterAutoStart&)=delete;
		CCoroutineObjectAwaiterAutoStart(CCoroutineObjectAwaiterAutoStart&& Other) noexcept;
		~CCoroutineObjectAwaiterAutoStart(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PARAMETER obsahuje COROUTINE HANDLE na CURRENT COROUTINE v ktorej sa pouzil OPERATOR [OPERATOR co_await], alebo OPERATOR [OPERATOR co_yield].
template<typename TPromiseType>
std::coroutine_handle<CCoroutineObjectAwaiterAutoStart::promise_type> CCoroutineObjectAwaiterAutoStart::await_suspend(std::coroutine_handle<TPromiseType> Handle) const noexcept
{
	promise_type&												ThisPromise=MHandle.promise();
	promise_type&												ParameterPromise=Handle.promise();

	std:: wcout << L"!!!!! COROUTINE [" << ThisPromise.GetID() << L"] - AWAIT SUSPEND CALLED. PARAMETER COROUTINE [" << ParameterPromise.GetID() << L"]." << std::endl;

	// !!!!! Do CURRENT COROUTINE PROMISE sa ulozi HANDLE na SUB COROUTINE.
	ParameterPromise.SetHandle(MHandle);

	// !!!!! Vrati sa COROUTINE HANDLE, ktora ma byt okamzite spustena bez toho, aby doslo ku COROUTINE SUSPEND.
	// !!!!! COROUTINE teda NEBUDE SUSPENDED a METHOD [void await_resume(void)] sa nezavola.
	return(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------