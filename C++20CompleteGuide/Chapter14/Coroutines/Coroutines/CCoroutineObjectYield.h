//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue>
struct SCoroutineObjectYieldPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TReturnValue											MReturnValue;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		std::suspend_always final_suspend(void) noexcept;
		std::suspend_always yield_value(TReturnValue Value);
		void return_void(void);
		void unhandled_exception(void);

	public:
		const TReturnValue& GetReturnValue(void) const noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue>
TCoroutineObject SCoroutineObjectYieldPromiseType<TCoroutineObject,TReturnValue>::get_return_object(void)
{
	// !!! Vytvori sa COROUTINE HANDLE.
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectYieldPromiseType>::from_promise(*this);

	// !!! Vytvori sa instancia COROUTINE OBJECT.
	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom spusteni.
template<typename TCoroutineObject, typename TReturnValue>
std::suspend_always SCoroutineObjectYieldPromiseType<TCoroutineObject,TReturnValue>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom ukonceni.
// !!! METHOD MUSI byt definovana ako NO EXCEPT.
// !!! Pre CORUTINES sa odporuca, aby pri ukonceni boli VZDY SUSPENDED.
template<typename TCoroutineObject, typename TReturnValue>
std::suspend_always SCoroutineObjectYieldPromiseType<TCoroutineObject,TReturnValue>::SCoroutineObjectYieldPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE pouzila CODE [co_yield VALUE], pricom VALUE [VALUE] je PARAMETER tejto METHOD.
template<typename TCoroutineObject, typename TReturnValue>
std::suspend_always SCoroutineObjectYieldPromiseType<TCoroutineObject,TReturnValue>::yield_value(TReturnValue Value)
{
	std::wcout << L"!!!!! METHOD [yield_value()] CALLED." << std::endl;

	// !!! VALUE vratena OPERATOR [co_yield VALUE] je ulozena do LOCAL VARIABLE.
	MReturnValue=Value;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE skoncila, alebo vykonala CODE [co_return;].
// !!!!! METHOD sa vola IBA ak COROUTINE nevracia ziadnu RETURN VALUE.
template<typename TCoroutineObject, typename TReturnValue>
void SCoroutineObjectYieldPromiseType<TCoroutineObject,TReturnValue>::return_void(void)
{
	std::wcout << L"!!!!! METHOD [return_void()] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD je volana pri vzniku UNHANDLED EXCEPTION v COROUTINE.
template<typename TCoroutineObject, typename TReturnValue>
void SCoroutineObjectYieldPromiseType<TCoroutineObject,TReturnValue>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD vracia RETURN VALUE, ktoru vrati CODE [co_yield VALUE].
template<typename TCoroutineObject, typename TReturnValue>
const TReturnValue& SCoroutineObjectYieldPromiseType<TCoroutineObject,TReturnValue>::GetReturnValue(void) const noexcept
{
	return(MReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
class CCoroutineObjectYield final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SCoroutineObjectYieldPromiseType<CCoroutineObjectYield,TReturnValue>;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectYield& operator=(const CCoroutineObjectYield&)=delete;

	public:
		CCoroutineObjectYield& operator=(CCoroutineObjectYield&& Other) noexcept;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;
		// !!! CUSTOM METHOD vracia RETURN VALUE, ktoru vracia CODE [co_yield VALUE].
		TReturnValue GetValue(void) const noexcept;

	public:
		CCoroutineObjectYield(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectYield(const CCoroutineObjectYield&)=delete;
		CCoroutineObjectYield(CCoroutineObjectYield&& Other) noexcept;
		~CCoroutineObjectYield(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
CCoroutineObjectYield<TReturnValue>::CCoroutineObjectYield(std::coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
CCoroutineObjectYield<TReturnValue>::CCoroutineObjectYield(CCoroutineObjectYield&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
CCoroutineObjectYield<TReturnValue>::~CCoroutineObjectYield(void) noexcept
{
	if (static_cast<bool>(MHandle)==true)
	{
		// !!! Uvolni sa instancia COROUTINE HANDLE.
		MHandle.destroy();
		MHandle=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
CCoroutineObjectYield<TReturnValue>& CCoroutineObjectYield<TReturnValue>::operator=(CCoroutineObjectYield<TReturnValue>&& Other) noexcept
{
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
template<typename TReturnValue>
bool CCoroutineObjectYield<TReturnValue>::Resume(void) const
{
	// !!! Vykona sa kontrola, ci COROUTINE HANDLE nie je uvolneny, alebo COROUTINE uz neskoncila.
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	// !!! Vykona sa RESUME COROUTINE, ktoru reprezentuje COROUTINE HANDLE.
	// !!! Volanie METHOD [void coroutine_handle::resume(void) const] je BLOCKING. To znamena, ze METHOD sa neskonci, kym COROUTINE nevykona dalsi SUSPEND.
	MHandle.resume();

	// !!! Vykona sa kontrola ci COROUTINE uz neskoncila.
	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD vracia RETURN VALUE, ktoru vrati CODE [co_yield VALUE].
template<typename TReturnValue>
TReturnValue CCoroutineObjectYield<TReturnValue>::GetValue(void) const noexcept
{
	TReturnValue												ReturnValue=MHandle.promise().GetReturnValue();

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------