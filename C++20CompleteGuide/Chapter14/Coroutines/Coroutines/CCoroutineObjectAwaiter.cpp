//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectAwaiter.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiter::CCoroutineObjectAwaiter(coroutine_handle<CCoroutineObjectAwaiter::promise_type> Handle)
	: MHandle(Handle)
{
	CCoroutineObjectAwaiter::promise_type&						Promise=MHandle.promise();

	wcout << L"COROUTINE [" << Promise.GetID() << L"] - COROUTINE HANDLE CREATED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiter::CCoroutineObjectAwaiter(CCoroutineObjectAwaiter&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiter::~CCoroutineObjectAwaiter(void) noexcept
{
	if (static_cast<bool>(MHandle)==true)
	{
		CCoroutineObjectAwaiter::promise_type&					Promise=MHandle.promise();
		int														ID=Promise.GetID();

		MHandle.destroy();
		MHandle=nullptr;

		wcout << L"COROUTINE [" << ID << L"] - COROUTINE HANDLE DESTROYED." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiter& CCoroutineObjectAwaiter::operator=(CCoroutineObjectAwaiter&& Other) noexcept
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
bool CCoroutineObjectAwaiter::Resume(void) const
{
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	coroutine_handle<promise_type>								HandleIterator=MHandle;

	// !!!!! Cyklus hlada najvnorenejsiu SUB COROUTINE, ktora este nebola ukoncena a ma sa spravit jej SUSPEND.
	while(true)
	{
		coroutine_handle<promise_type>							SubCoroutineHandle=HandleIterator.promise().GetHandle();

		if (SubCoroutineHandle==nullptr)
		{
			break;
		}

		bool													IsSubCoroutineHandleDone=SubCoroutineHandle.done();

		if (IsSubCoroutineHandleDone==true)
		{
			break;
		}

		// !!! Do HANDLE sa ulozi HANDLE na SUB COROUTINE.
		HandleIterator=SubCoroutineHandle;
	}

	HandleIterator.resume();

	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObjectAwaiter::await_ready(void) const noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectAwaiter::await_resume(void) const noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------