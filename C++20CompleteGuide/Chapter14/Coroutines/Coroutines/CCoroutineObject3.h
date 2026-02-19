//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SCoroutineObject3PromiseType final
{
//----------------------------------------------------------------------------------------------------------------------
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
TCoroutineObject SCoroutineObject3PromiseType<TCoroutineObject>::get_return_object(void)
{
	// !!! Vytvori sa COROUTINE HANDLE.
	std::coroutine_handle										Handle=std::coroutine_handle<SCoroutineObject3PromiseType>::from_promise(*this);

	// !!! Vytvori sa instancia COROUTINE OBJECT.
	return(TCoroutineObject(Handle));
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom spusteni.
template<typename TCoroutineObject>
std::suspend_always SCoroutineObject3PromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD je volana pri vzniku UNHANDLED EXCEPTION v COROUTINE.
template<typename TCoroutineObject>
void SCoroutineObject3PromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE skoncila, alebo vykonala CODE [co_return;].
// !!!!! METHOD sa vola IBA ak COROUTINE nevracia ziadnu RETURN VALUE.
template<typename TCoroutineObject>
void SCoroutineObject3PromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom ukonceni.
// !!! METHOD MUSI byt definovana ako NO EXCEPT.
// !!! Pre CORUTINES sa odporuca, aby pri ukonceni boli VZDY SUSPENDED.
template<typename TCoroutineObject>
std::suspend_always SCoroutineObject3PromiseType<TCoroutineObject>::SCoroutineObject3PromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CCoroutineObject3 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SCoroutineObject3PromiseType<CCoroutineObject3>;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<SCoroutineObject3PromiseType<CCoroutineObject3>>	MHandle;

	public:
		CCoroutineObject3& operator=(const CCoroutineObject3&)=delete;
		CCoroutineObject3& operator=(CCoroutineObject3&& Other) noexcept=delete;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;

	public:
		CCoroutineObject3(std::coroutine_handle<SCoroutineObject3PromiseType<CCoroutineObject3>> Handle);
		CCoroutineObject3(const CCoroutineObject3&)=delete;
		CCoroutineObject3(CCoroutineObject3&& Other) noexcept=delete;
		~CCoroutineObject3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------