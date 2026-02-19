//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObject1.h"
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObject1::CCoroutineObject1(coroutine_handle<SCoroutineObject1PromiseType> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObject1::~CCoroutineObject1(void) noexcept
{
	if (((bool)MHandle)==true)
	{
		// !!! Uvolni sa instancia COROUTINE HANDLE.
		MHandle.destroy();
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObject1::Resume(void) const
{
	// !!! Vykona sa kontrola, ci COROUTINE HANDLE nie je uvolneny, alebo COROUTINE uz neskoncila.
	if (((bool)MHandle)==false || MHandle.done()==true)
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObject1 CCoroutineObject1::SCoroutineObject1PromiseType::get_return_object(void)
{
	// !!! Vytvori sa COROUTINE HANDLE.
	coroutine_handle											Handle=coroutine_handle<SCoroutineObject1PromiseType>::from_promise(*this);

	// !!! Vytvori sa instancia COROUTINE OBJECT.
	return(CCoroutineObject1(Handle));
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom spusteni.
suspend_always CCoroutineObject1::SCoroutineObject1PromiseType::initial_suspend(void)
{
	suspend_always												Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD je volana pri vzniku UNHANDLED EXCEPTION v COROUTINE.
void CCoroutineObject1::SCoroutineObject1PromiseType::unhandled_exception(void)
{
	terminate();
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE skoncila, alebo vykonala CODE [co_return;].
// !!!!! METHOD sa vola IBA ak COROUTINE nevracia ziadnu RETURN VALUE.
void CCoroutineObject1::SCoroutineObject1PromiseType::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom ukonceni.
// !!! METHOD MUSI byt definovana ako NO EXCEPT.
// !!! Pre CORUTINES sa odporuca, aby pri ukonceni boli VZDY SUSPENDED.
suspend_always CCoroutineObject1::SCoroutineObject1PromiseType::final_suspend(void) noexcept
{
	suspend_always												Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------