//----------------------------------------------------------------------------------------------------------------------
#include "CResumeCoroutineTask.h"
#include <iostream>
#include <exception>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CResumeCoroutineTask::CResumeCoroutineTask(coroutine_handle<SPromiseType> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CResumeCoroutineTask::~CResumeCoroutineTask(void) noexcept
{
	if (((bool)MHandle)==true)
	{
		void*													CoroutinePointer=MHandle.address();

		// !!! Uvolni sa instancia COROUTINE HANDLE.
		MHandle.destroy();
		MHandle=nullptr;

		wcout << L"COROUTINE HANDLE [" << CoroutinePointer << L"] DESTROYED." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CResumeCoroutineTask::Resume(void) const
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
CResumeCoroutineTask CResumeCoroutineTask::SPromiseType::get_return_object(void)
{
	// !!! Vytvori sa COROUTINE HANDLE.
	coroutine_handle											Handle=coroutine_handle<SPromiseType>::from_promise(*this);

	// !!! Vytvori sa instancia COROUTINE OBJECT.
	return(CResumeCoroutineTask(Handle));
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom spusteni.
suspend_always CResumeCoroutineTask::SPromiseType::initial_suspend(void)
{
	suspend_always												Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD je volana pri vzniku UNHANDLED EXCEPTION v COROUTINE.
void CResumeCoroutineTask::SPromiseType::unhandled_exception(void)
{
	terminate();
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD sa vola, ak COROUTINE skoncila, alebo vykonala CODE [co_return;].
// !!!!! METHOD sa vola IBA ak COROUTINE nevracia ziadnu RETURN VALUE.
void CResumeCoroutineTask::SPromiseType::return_void(void)
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------
// !!! METHOD urcuje ci COROUTINE ma byt SUSPENDED pri svojom ukonceni.
// !!! METHOD MUSI byt definovana ako NO EXCEPT.
// !!! Pre CORUTINES sa odporuca, aby pri ukonceni boli VZDY SUSPENDED.
suspend_always CResumeCoroutineTask::SPromiseType::final_suspend(void) noexcept
{
	suspend_always												Result{};

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------