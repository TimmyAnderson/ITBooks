//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <iostream>
#include <string>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! AWAITER OBJECT, ktory spusti dalsiu COROUTINE.
template<typename TCoroutineObject>
struct SCoroutineObjectSymmetricTransferAwaiter final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		bool await_ready(void) noexcept;
		std::coroutine_handle<void> await_suspend(std::coroutine_handle<typename TCoroutineObject::promise_type> Handle) noexcept;
		void await_resume(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
bool SCoroutineObjectSymmetricTransferAwaiter<TCoroutineObject>::await_ready(void) noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::coroutine_handle<void> SCoroutineObjectSymmetricTransferAwaiter<TCoroutineObject>::await_suspend(std::coroutine_handle<typename TCoroutineObject::promise_type> Handle) noexcept
{
	typename TCoroutineObject::promise_type&					PromiseObject=Handle.promise();

	// !!! C++ vykonava CONVERSION TYPE [coroutine_handle<TCoroutineObject::promise_type>] na TYPE volanim CONVERSION OPERATOR [OPERATOR coroutine_handle<void>].
	std::coroutine_handle<void>									CoroutineHandle=PromiseObject.GetNextCoroutineHandle();

	if (static_cast<bool>(CoroutineHandle)==true)
	{
		// !!!!! Vracia sa COROUTINE HANDLE na nasledujucu COROUTINE, ktora sa ma spustit po skonceni CURRENT COROUTINE.
		return(CoroutineHandle);
	}
	else
	{
		// !!! C++ vykonava CONVERSION TYPE [coroutine_handle<noop_coroutine_promise>] na TYPE volanim CONVERSION OPERATOR [OPERATOR coroutine_handle<void>].
		std::coroutine_handle<void>								NoOperationCoroutineHandle=std::noop_coroutine();

		return(NoOperationCoroutineHandle);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSymmetricTransferAwaiter<TCoroutineObject>::await_resume(void) noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObjectSymmetricTransferPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::wstring											MID;
		std::coroutine_handle<void>								MNextCoroutineHandle;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		SCoroutineObjectSymmetricTransferAwaiter<TCoroutineObject> final_suspend(void) noexcept;

	public:
		std::coroutine_handle<void> GetNextCoroutineHandle(void) noexcept;
		void SetNextCoroutineHandle(std::coroutine_handle<void> Handle);

	public:
		SCoroutineObjectSymmetricTransferPromiseType(std::wstring ID);
		~SCoroutineObjectSymmetricTransferPromiseType(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::SCoroutineObjectSymmetricTransferPromiseType(std::wstring ID)
	: MID(ID), MNextCoroutineHandle()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::~SCoroutineObjectSymmetricTransferPromiseType(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
TCoroutineObject SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::get_return_object(void)
{
	std::coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType>	Handle=std::coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::suspend_always SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::wcout << L"!!!!! UNHANDLED EXCEPTION DETECTED. !!!!!" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
SCoroutineObjectSymmetricTransferAwaiter<TCoroutineObject> SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::SCoroutineObjectSymmetricTransferPromiseType::final_suspend(void) noexcept
{
	// !!!!! FINAL AWAITER sposobi vyvolanie dalsej COROUTINE po skonceni aktualnej COROUTINE bez nutnosti alokacie noveho STACK FRAME.
	SCoroutineObjectSymmetricTransferAwaiter<TCoroutineObject>	Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
std::coroutine_handle<void> SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::GetNextCoroutineHandle(void) noexcept
{
	return(MNextCoroutineHandle);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
void SCoroutineObjectSymmetricTransferPromiseType<TCoroutineObject>::SetNextCoroutineHandle(std::coroutine_handle<void> Handle)
{
	MNextCoroutineHandle=Handle;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObjectSymmetricTransfer final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>;

	private:
		std::coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>>	MHandle;

	public:
		CCoroutineObjectSymmetricTransfer& operator=(const CCoroutineObjectSymmetricTransfer&)=delete;
		CCoroutineObjectSymmetricTransfer& operator=(CCoroutineObjectSymmetricTransfer&& Other) noexcept;

	public:
		bool Resume(void) const;
		std::coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>> GetCurrentHandle(void);
		void SetNextCoroutineHandle(std::coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>> Handle);

	public:
		CCoroutineObjectSymmetricTransfer(std::coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>> Handle);
		CCoroutineObjectSymmetricTransfer(const CCoroutineObjectSymmetricTransfer&)=delete;
		CCoroutineObjectSymmetricTransfer(CCoroutineObjectSymmetricTransfer&& Other) noexcept;
		~CCoroutineObjectSymmetricTransfer(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------