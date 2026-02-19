//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! CLASS implementuje BACK AWAITER TYPE, ktory umoznuje prenasat VALUE z COROUTINE do CALLER FUNCTION aj VALUE z CALLER FUNCTION do COROUTINE.
template<typename TPromiseType, typename TYieldValueToCoroutine>
class CCoroutineObjectDuplexCommunicationBackAwaiter final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		std::coroutine_handle<TPromiseType>						MHandle;

	public:
		bool await_ready(void) const noexcept;
		void await_suspend(std::coroutine_handle<TPromiseType> Handle) noexcept;
		TYieldValueToCoroutine await_resume(void) const noexcept;

	public:
		CCoroutineObjectDuplexCommunicationBackAwaiter(void);
		~CCoroutineObjectDuplexCommunicationBackAwaiter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TYieldValueToCoroutine>
CCoroutineObjectDuplexCommunicationBackAwaiter<TPromiseType,TYieldValueToCoroutine>::CCoroutineObjectDuplexCommunicationBackAwaiter(void)
	: MHandle(nullptr)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TYieldValueToCoroutine>
CCoroutineObjectDuplexCommunicationBackAwaiter<TPromiseType,TYieldValueToCoroutine>::~CCoroutineObjectDuplexCommunicationBackAwaiter(void) noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TYieldValueToCoroutine>
bool CCoroutineObjectDuplexCommunicationBackAwaiter<TPromiseType,TYieldValueToCoroutine>::await_ready(void) const noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TYieldValueToCoroutine>
void CCoroutineObjectDuplexCommunicationBackAwaiter<TPromiseType,TYieldValueToCoroutine>::await_suspend(std::coroutine_handle<TPromiseType> Handle) noexcept
{
	// !!! HANDLE CURRENT (SUSPENDED) COROUTINE sa ulozi do FIELD.
	MHandle=Handle;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TPromiseType, typename TYieldValueToCoroutine>
TYieldValueToCoroutine CCoroutineObjectDuplexCommunicationBackAwaiter<TPromiseType,TYieldValueToCoroutine>::await_resume(void) const noexcept
{
	TPromiseType												Promise=MHandle.promise();
	const TYieldValueToCoroutine&								YieldValueToCoroutine=Promise.GetYieldValueToCoroutine();

	return(YieldValueToCoroutine);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! STRUCTURE implementuje PROMISE TYPE, ktory umoznuje prenasat VALUE z COROUTINE do CALLER FUNCTION aj VALUE z CALLER FUNCTION do COROUTINE.
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
struct SCoroutineObjectDuplexCommunicationPromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!! FIELD obsahuje VALUE, ktora je prenasana z COROUTINE do CALLER FUNCION.
		TYieldValueFromCoroutine											MYieldValueFromCoroutine;
		// !!! FIELD obsahuje VALUE, ktora je prenasana z CALLER FUNCION do COROUTINE.
		TYieldValueToCoroutine												MYieldValueToCoroutine;

	public:
		TCoroutineObject get_return_object(void);
		std::suspend_always initial_suspend(void);
		std::suspend_always final_suspend(void) noexcept;
		CCoroutineObjectDuplexCommunicationBackAwaiter<SCoroutineObjectDuplexCommunicationPromiseType,TYieldValueToCoroutine> yield_value(TYieldValueFromCoroutine Value);
		void return_void(void);
		void unhandled_exception(void);

	public:
		const TYieldValueFromCoroutine& GetYieldValueFromCoroutine(void) const noexcept;
		const TYieldValueToCoroutine& GetYieldValueToCoroutine(void) const noexcept;
		void SetYieldValueToCoroutine(const TYieldValueToCoroutine& Value);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
TCoroutineObject SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::get_return_object(void)
{
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObjectDuplexCommunicationPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
std::suspend_always SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
std::suspend_always SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
CCoroutineObjectDuplexCommunicationBackAwaiter<SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>,TYieldValueToCoroutine> SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::yield_value(TYieldValueFromCoroutine Value)
{
	// !!! VALUE, ktoru COROUTINE posiela do CALLER FUNCTION sa ulozi do FIELD.
	MYieldValueFromCoroutine=Value;

	// !!! Vytvori sa instancia BACK AWAITER.
	CCoroutineObjectDuplexCommunicationBackAwaiter<SCoroutineObjectDuplexCommunicationPromiseType,TYieldValueToCoroutine>	Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
void SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
void SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
const TYieldValueFromCoroutine& SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::GetYieldValueFromCoroutine(void) const noexcept
{
	return(MYieldValueFromCoroutine);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
const TYieldValueToCoroutine& SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::GetYieldValueToCoroutine(void) const noexcept
{
	return(MYieldValueToCoroutine);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject, typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
void SCoroutineObjectDuplexCommunicationPromiseType<TCoroutineObject,TYieldValueFromCoroutine,TYieldValueToCoroutine>::SetYieldValueToCoroutine(const TYieldValueToCoroutine& Value)
{
	MYieldValueToCoroutine=Value;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Toto je COROUTINE OBJECT.
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
class [[nodiscard]] CCoroutineObjectDuplexCommunication final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													promise_type=SCoroutineObjectDuplexCommunicationPromiseType<CCoroutineObjectDuplexCommunication,int,double>;

	private:
		// !!! HANDLE na COROUTINE.
		std::coroutine_handle<promise_type>						MHandle;

	public:
		CCoroutineObjectDuplexCommunication& operator=(const CCoroutineObjectDuplexCommunication&)=delete;
		CCoroutineObjectDuplexCommunication& operator=(CCoroutineObjectDuplexCommunication&& Other) noexcept;

	public:
		bool Resume(void) const;
		TYieldValueFromCoroutine GetValueFromCoroutine(void) const noexcept;
		void SetValueToCoroutine(const TYieldValueToCoroutine& Value);

	public:
		CCoroutineObjectDuplexCommunication(std::coroutine_handle<promise_type> Handle);
		CCoroutineObjectDuplexCommunication(const CCoroutineObjectDuplexCommunication&)=delete;
		CCoroutineObjectDuplexCommunication(CCoroutineObjectDuplexCommunication&& Other) noexcept;
		~CCoroutineObjectDuplexCommunication(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>::CCoroutineObjectDuplexCommunication(std::coroutine_handle<CCoroutineObjectDuplexCommunication::promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>::CCoroutineObjectDuplexCommunication(CCoroutineObjectDuplexCommunication&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>::~CCoroutineObjectDuplexCommunication(void) noexcept
{
	if (static_cast<bool>(MHandle)==true)
	{
		MHandle.destroy();
		MHandle=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>& CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>::operator=(CCoroutineObjectDuplexCommunication&& Other) noexcept
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
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
bool CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>::Resume(void) const
{
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	MHandle.resume();

	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
TYieldValueFromCoroutine CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>::GetValueFromCoroutine(void) const noexcept
{
	TYieldValueFromCoroutine									ReturnValue=MHandle.promise().GetYieldValueFromCoroutine();

	return(ReturnValue);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TYieldValueFromCoroutine, typename TYieldValueToCoroutine>
void CCoroutineObjectDuplexCommunication<TYieldValueFromCoroutine,TYieldValueToCoroutine>::SetValueToCoroutine(const TYieldValueToCoroutine& Value)
{
	MHandle.promise().SetYieldValueToCoroutine(Value);
}
//----------------------------------------------------------------------------------------------------------------------