//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <coroutine>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TCoroutineObject>
struct SMovableCoroutineObjectPromiseType final
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
TCoroutineObject SMovableCoroutineObjectPromiseType<TCoroutineObject>::get_return_object(void)
{
	// !!! Vytvori sa COROUTINE HANDLE.
	std::coroutine_handle										Handle=std::coroutine_handle<SMovableCoroutineObjectPromiseType>::from_promise(*this);

	TCoroutineObject											CoroutineObject(Handle);

	// !!! Vytvori sa instancia COROUTINE OBJECT.
	return(CoroutineObject);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom spusteni.
template<typename TCoroutineObject>
std::suspend_always SMovableCoroutineObjectPromiseType<TCoroutineObject>::initial_suspend(void)
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD je volana pri vzniku UNHANDLED EXCEPTION v COROUTINE.
template<typename TCoroutineObject>
void SMovableCoroutineObjectPromiseType<TCoroutineObject>::unhandled_exception(void)
{
	std::terminate();
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE skoncila, alebo vykonala CODE [co_return;].
// !!!!! METHOD sa vola IBA ak COROUTINE nevracia ziadnu RETURN VALUE.
template<typename TCoroutineObject>
void SMovableCoroutineObjectPromiseType<TCoroutineObject>::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom ukonceni.
// !!! METHOD MUSI byt definovana ako NO EXCEPT.
// !!! Pre CORUTINES sa odporuca, aby pri ukonceni boli VZDY SUSPENDED.
template<typename TCoroutineObject>
std::suspend_always SMovableCoroutineObjectPromiseType<TCoroutineObject>::SMovableCoroutineObjectPromiseType::final_suspend(void) noexcept
{
	std::suspend_always											Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class [[nodiscard]] CMovableCoroutineObject final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		// !!! COROUTINE OBJECT musi definovat TYPE s NAME [promise_type].
		using													promise_type=SMovableCoroutineObjectPromiseType<CMovableCoroutineObject>;

	private:
		// !!! FIELD reprezentuje COROUTINE HANDLE, ktorym reprezentuje COROUTINE. COROUTINE HANDLE umoznuje ovladat beh COROUTINES.
		std::coroutine_handle<SMovableCoroutineObjectPromiseType<CMovableCoroutineObject>>	MHandle;

	public:
		CMovableCoroutineObject& operator=(const CMovableCoroutineObject&)=delete;
		CMovableCoroutineObject& operator=(CMovableCoroutineObject&& Other) noexcept;

	public:
		// !!! CUSTOM METHOD vykonava RESUME danej COROUTINE a zaroven vracia informaciu ci COROUTINE uz skoncila.
		bool Resume(void) const;

	public:
		CMovableCoroutineObject(std::coroutine_handle<SMovableCoroutineObjectPromiseType<CMovableCoroutineObject>> Handle);
		CMovableCoroutineObject(const CMovableCoroutineObject&)=delete;
		CMovableCoroutineObject(CMovableCoroutineObject&& Other) noexcept;
		~CMovableCoroutineObject(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------