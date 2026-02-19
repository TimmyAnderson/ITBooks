//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
struct SCoroutineObjectReturnPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TYieldValue											MYieldValue;
		TReturnValue										MReturnValue;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		std::suspend_always final_suspend(void) noexcept;
		std::suspend_always yield_value(TYieldValue Value);
		void return_value(const TReturnValue& Value);
		// !!!!! PROMISE TYPE NEMOZE zaroven obsahovat aj METHOD [void return_value(const TReturnValue& Value)], aj METHOD [void return_void(void)].
		//void return_void(void);
		void unhandled_exception(void);

	public:
		const TYieldValue& GetYieldValue(void) const noexcept;
		const TReturnValue& GetReturnValue(void) const noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
TCoroutineObject SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::get_return_object(void)
{
	// !!! Vytvori sa COROUTINE HANDLE.
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectReturnPromiseType>::from_promise(*this);

	// !!! Vytvori sa instancia COROUTINE OBJECT.
	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom spusteni.
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
std::suspend_always SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom ukonceni.
// !!! METHOD MUSI byt definovana ako NO EXCEPT.
// !!! Pre CORUTINES sa odporuca, aby pri ukonceni boli VZDY SUSPENDED.
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
std::suspend_always SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::SCoroutineObjectReturnPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE pouzila CODE [co_yield VALUE], pricom VALUE [VALUE] je PARAMETER tejto METHOD.
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
std::suspend_always SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::yield_value(TYieldValue Value)
{
	std::wcout << L"!!!!! METHOD [yield_value()] CALLED." << std::endl;

	// !!! VALUE vratena OPERATOR [co_yield VALUE] je ulozena do LOCAL VARIABLE.
	MYieldValue=Value;

	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE vykonala CODE [co_return VALUE;].
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
void SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::return_value(const TReturnValue& Value)
{
	std::wcout << L"!!!!! METHOD [return_value()] CALLED." << std::endl;

	MReturnValue=Value;
}
//----------------------------------------------------------------------------------------------------------------------
/*
// !!! METHOD sa vola, ak COROUTINE skoncila, alebo vykonala CODE [co_return;].
// !!!!! METHOD sa vola IBA ak COROUTINE nevracia ziadnu RETURN VALUE.
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
void SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::return_void(void)
{
	std::wcout << L"!!!!! METHOD [return_void()] CALLED." << std::endl;
}
*/
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD je volana pri vzniku UNHANDLED EXCEPTION v COROUTINE.
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
void SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD vracia YIELD VALUE, ktoru vrati CODE [co_yield VALUE].
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
const TYieldValue& SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::GetYieldValue(void) const noexcept
{
	return(MYieldValue);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD vracia RETURN VALUE, ktoru vrati CODE [co_return VALUE].
template<typename TCoroutineObject, typename TYieldValue, typename TReturnValue>
const TReturnValue& SCoroutineObjectReturnPromiseType<TCoroutineObject,TYieldValue,TReturnValue>::GetReturnValue(void) const noexcept
{
	return(MReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue, typename TReturnValue>
class CCoroutineObjectReturn final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SCoroutineObjectReturnPromiseType<CCoroutineObjectReturn,TYieldValue,TReturnValue>;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectReturn& operator=(const CCoroutineObjectReturn&)=delete;

	public:
		CCoroutineObjectReturn& operator=(CCoroutineObjectReturn&& Other) noexcept;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;
		// !!! CUSTOM METHOD vracia VALUE, ktoru vracia CODE [co_yield VALUE].
		TYieldValue GetYieldValue(void) const noexcept;
		// !!! CUSTOM METHOD vracia VALUE, ktoru vracia CODE [co_return VALUE].
		TReturnValue GetReturnValue(void) const noexcept;

	public:
		CCoroutineObjectReturn(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectReturn(const CCoroutineObjectReturn&)=delete;
		CCoroutineObjectReturn(CCoroutineObjectReturn&& Other) noexcept;
		~CCoroutineObjectReturn(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue, typename TReturnValue>
CCoroutineObjectReturn<TYieldValue,TReturnValue>::CCoroutineObjectReturn(std::coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue, typename TReturnValue>
CCoroutineObjectReturn<TYieldValue,TReturnValue>::CCoroutineObjectReturn(CCoroutineObjectReturn&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValue, typename TReturnValue>
CCoroutineObjectReturn<TYieldValue,TReturnValue>::~CCoroutineObjectReturn(void) noexcept
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
template<typename TYieldValue, typename TReturnValue>
CCoroutineObjectReturn<TYieldValue,TReturnValue>& CCoroutineObjectReturn<TYieldValue,TReturnValue>::operator=(CCoroutineObjectReturn<TYieldValue,TReturnValue>&& Other) noexcept
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
template<typename TYieldValue, typename TReturnValue>
bool CCoroutineObjectReturn<TYieldValue,TReturnValue>::Resume(void) const
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
// !!! METHOD vracia VALUE, ktoru vrati CODE [co_yield VALUE].
template<typename TYieldValue, typename TReturnValue>
TYieldValue CCoroutineObjectReturn<TYieldValue,TReturnValue>::GetYieldValue(void) const noexcept
{
	TYieldValue												YieldValue=MHandle.promise().GetYieldValue();

	return(YieldValue);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD vracia VALUE, ktoru vrati CODE [co_return VALUE].
template<typename TYieldValue, typename TReturnValue>
TReturnValue CCoroutineObjectReturn<TYieldValue,TReturnValue>::GetReturnValue(void) const noexcept
{
	TReturnValue											ReturnValue=MHandle.promise().GetReturnValue();

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------