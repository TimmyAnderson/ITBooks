//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
struct STracingCoroutineObjectPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		TCoroutineObject get_return_object(void);
		TInitialAwaiter initial_suspend(void);
		void unhandled_exception(void);
		void return_void(void);
		std::suspend_always final_suspend(void) noexcept;

	public:
		STracingCoroutineObjectPromiseType(void);
		~STracingCoroutineObjectPromiseType(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
STracingCoroutineObjectPromiseType<TCoroutineObject,TInitialAwaiter>::STracingCoroutineObjectPromiseType(void)
{
	std::wcout << L"CONSTRUCTOR [STracingCoroutineObjectPromiseType] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
STracingCoroutineObjectPromiseType<TCoroutineObject,TInitialAwaiter>::~STracingCoroutineObjectPromiseType(void) noexcept
{
	std::wcout << L"DESTRUCTOR [STracingCoroutineObjectPromiseType] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
TCoroutineObject STracingCoroutineObjectPromiseType<TCoroutineObject,TInitialAwaiter>::get_return_object(void)
{
	std::wcout << L"METHOD [get_return_object] CALLED." << std::endl;

	std::coroutine_handle										Handle=std::coroutine_handle<STracingCoroutineObjectPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
TInitialAwaiter STracingCoroutineObjectPromiseType<TCoroutineObject,TInitialAwaiter>::initial_suspend(void)
{
	std::wcout << L"METHOD [initial_suspend] CALLED." << std::endl;

	TInitialAwaiter												Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
void STracingCoroutineObjectPromiseType<TCoroutineObject,TInitialAwaiter>::unhandled_exception(void)
{
	std::wcout << L"METHOD [unhandled_exception] CALLED." << std::endl;

	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
void STracingCoroutineObjectPromiseType<TCoroutineObject,TInitialAwaiter>::return_void(void)
{
	std::wcout << L"METHOD [return_void] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TInitialAwaiter>
std::suspend_always STracingCoroutineObjectPromiseType<TCoroutineObject,TInitialAwaiter>::STracingCoroutineObjectPromiseType::final_suspend(void) noexcept
{
	std::wcout << L"METHOD [final_suspend] CALLED." << std::endl;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TInitialAwaiter>
class [[nodiscard]] CTracingCoroutineObject final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=STracingCoroutineObjectPromiseType<CTracingCoroutineObject,TInitialAwaiter>;

	private:
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CTracingCoroutineObject& operator=(const CTracingCoroutineObject&)=delete;
		CTracingCoroutineObject& operator=(CTracingCoroutineObject&& Other) noexcept;

	public:
		bool Resume(void) const;

	public:
		CTracingCoroutineObject(std::coroutine_handle<promise_type> Handle);
		CTracingCoroutineObject(const CTracingCoroutineObject&)=delete;
		CTracingCoroutineObject(CTracingCoroutineObject&& Other) noexcept;
		~CTracingCoroutineObject(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TInitialAwaiter>
CTracingCoroutineObject<TInitialAwaiter>::CTracingCoroutineObject(std::coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
	std::wcout << L"CONSTRUCTOR [CTracingCoroutineObject] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TInitialAwaiter>
CTracingCoroutineObject<TInitialAwaiter>::CTracingCoroutineObject(CTracingCoroutineObject&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	std::wcout << L"COPY CONSTRUCTOR [CTracingCoroutineObject] CALLED." << std::endl;

	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TInitialAwaiter>
CTracingCoroutineObject<TInitialAwaiter>::~CTracingCoroutineObject(void) noexcept
{
	std::wcout << L"DESTRUCTOR [CTracingCoroutineObject] CALLED." << std::endl;

	if (static_cast<bool>(MHandle)==true)
	{
		MHandle.destroy();
		MHandle=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TInitialAwaiter>
CTracingCoroutineObject<TInitialAwaiter>& CTracingCoroutineObject<TInitialAwaiter>::operator=(CTracingCoroutineObject&& Other) noexcept
{
	std::wcout << L"COPY OPERATOR [OPERATOR=] CALLED." << std::endl;

	if (this!=&Other)
	{
		if (static_cast<bool>(MHandle)==true)
		{
			MHandle.destroy();
			MHandle=nullptr;
		}

		MHandle=move(Other.MHandle);

		Other.MHandle=nullptr;
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TInitialAwaiter>
bool CTracingCoroutineObject<TInitialAwaiter>::Resume(void) const
{
	std::wcout << L"METHOD [Resume] CALLED." << std::endl;

	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	MHandle.resume();

	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------