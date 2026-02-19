//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TReturnValue>
struct SCoroutineObjectYieldIteratorPromiseType final
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
TCoroutineObject SCoroutineObjectYieldIteratorPromiseType<TCoroutineObject,TReturnValue>::get_return_object(void)
{
	// !!! Vytvori sa COROUTINE HANDLE.
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectYieldIteratorPromiseType>::from_promise(*this);

	// !!! Vytvori sa instancia COROUTINE OBJECT.
	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom spusteni.
template<typename TCoroutineObject, typename TReturnValue>
std::suspend_always SCoroutineObjectYieldIteratorPromiseType<TCoroutineObject,TReturnValue>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom ukonceni.
// !!! METHOD MUSI byt definovana ako NO EXCEPT.
// !!! Pre CORUTINES sa odporuca, aby pri ukonceni boli VZDY SUSPENDED.
template<typename TCoroutineObject, typename TReturnValue>
std::suspend_always SCoroutineObjectYieldIteratorPromiseType<TCoroutineObject,TReturnValue>::SCoroutineObjectYieldIteratorPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE pouzila CODE [co_yield VALUE], pricom VALUE [VALUE] je PARAMETER tejto METHOD.
template<typename TCoroutineObject, typename TReturnValue>
std::suspend_always SCoroutineObjectYieldIteratorPromiseType<TCoroutineObject,TReturnValue>::yield_value(TReturnValue Value)
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
void SCoroutineObjectYieldIteratorPromiseType<TCoroutineObject,TReturnValue>::return_void(void)
{
	std::wcout << L"!!!!! METHOD [return_void()] CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD je volana pri vzniku UNHANDLED EXCEPTION v COROUTINE.
template<typename TCoroutineObject, typename TReturnValue>
void SCoroutineObjectYieldIteratorPromiseType<TCoroutineObject,TReturnValue>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD vracia RETURN VALUE, ktoru vrati CODE [co_yield VALUE].
template<typename TCoroutineObject, typename TReturnValue>
const TReturnValue& SCoroutineObjectYieldIteratorPromiseType<TCoroutineObject,TReturnValue>::GetReturnValue(void) const noexcept
{
	return(MReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TReturnValue>
struct SCoroutineObjectYieldIterator final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::coroutine_handle<TPromiseType>						MHandle;

	public:
		bool operator==(const SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>& Other) const;
		TReturnValue operator*(void) const;
		SCoroutineObjectYieldIterator operator++(void);

	public:
		void DoResume(void);

	public:
		SCoroutineObjectYieldIterator(std::coroutine_handle<TPromiseType> Handle);
		~SCoroutineObjectYieldIterator(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TReturnValue>
SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>::SCoroutineObjectYieldIterator(std::coroutine_handle<TPromiseType> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TReturnValue>
SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>::~SCoroutineObjectYieldIterator(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TReturnValue>
bool SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>::operator==(const SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>& Other) const
{
	if (static_cast<bool>(MHandle)==true && static_cast<bool>(Other.MHandle)==true)
	{
		if (MHandle.address()==Other.MHandle.address())
		{
			return(true);
		}
		else
		{
			return(false);
		}
	}
	else if (static_cast<bool>(MHandle)==false && static_cast<bool>(Other.MHandle)==false)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TReturnValue>
TReturnValue SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>::operator*(void) const
{
	TReturnValue												ReturnValue=MHandle.promise().GetReturnValue();

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TReturnValue>
SCoroutineObjectYieldIterator<TPromiseType,TReturnValue> SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>::operator++(void)
{
	DoResume();

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TReturnValue>
void SCoroutineObjectYieldIterator<TPromiseType,TReturnValue>::DoResume(void)
{
	if (static_cast<bool>(MHandle)==true)
	{
		MHandle.resume();

		if (MHandle.done()==true)
		{
			MHandle=nullptr;
		}
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
class CCoroutineObjectYieldIterator final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SCoroutineObjectYieldIteratorPromiseType<CCoroutineObjectYieldIterator,TReturnValue>;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectYieldIterator& operator=(const CCoroutineObjectYieldIterator&)=delete;

	public:
		CCoroutineObjectYieldIterator& operator=(CCoroutineObjectYieldIterator&& Other) noexcept;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;
		// !!! CUSTOM METHOD vracia RETURN VALUE, ktoru vracia CODE [co_yield VALUE].
		TReturnValue GetValue(void) const noexcept;

	public:
		SCoroutineObjectYieldIterator<promise_type,TReturnValue> begin(void) const;
		SCoroutineObjectYieldIterator<promise_type,TReturnValue> end(void) const;

	public:
		CCoroutineObjectYieldIterator(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectYieldIterator(const CCoroutineObjectYieldIterator&)=delete;
		CCoroutineObjectYieldIterator(CCoroutineObjectYieldIterator&& Other) noexcept;
		~CCoroutineObjectYieldIterator(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
CCoroutineObjectYieldIterator<TReturnValue>::CCoroutineObjectYieldIterator(std::coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
CCoroutineObjectYieldIterator<TReturnValue>::CCoroutineObjectYieldIterator(CCoroutineObjectYieldIterator&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
CCoroutineObjectYieldIterator<TReturnValue>::~CCoroutineObjectYieldIterator(void) noexcept
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
CCoroutineObjectYieldIterator<TReturnValue>& CCoroutineObjectYieldIterator<TReturnValue>::operator=(CCoroutineObjectYieldIterator<TReturnValue>&& Other) noexcept
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
bool CCoroutineObjectYieldIterator<TReturnValue>::Resume(void) const
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
TReturnValue CCoroutineObjectYieldIterator<TReturnValue>::GetValue(void) const noexcept
{
	TReturnValue												ReturnValue=MHandle.promise().GetReturnValue();

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
SCoroutineObjectYieldIterator<typename CCoroutineObjectYieldIterator<TReturnValue>::promise_type,TReturnValue> CCoroutineObjectYieldIterator<TReturnValue>::begin(void) const
{
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		SCoroutineObjectYieldIterator<typename CCoroutineObjectYieldIterator<TReturnValue>::promise_type,TReturnValue>	Iterator(nullptr);

		return(Iterator);
	}
	else
	{
		SCoroutineObjectYieldIterator<typename CCoroutineObjectYieldIterator<TReturnValue>::promise_type,TReturnValue>	Iterator(MHandle);

		Iterator.DoResume();

		return(Iterator);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TReturnValue>
SCoroutineObjectYieldIterator<typename CCoroutineObjectYieldIterator<TReturnValue>::promise_type,TReturnValue> CCoroutineObjectYieldIterator<TReturnValue>::end(void) const
{
	SCoroutineObjectYieldIterator<typename CCoroutineObjectYieldIterator<TReturnValue>::promise_type,TReturnValue>	Iterator(nullptr);

	return(Iterator);
}
//----------------------------------------------------------------------------------------------------------------------