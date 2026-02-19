//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectAwaiterAutoStart.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiterAutoStart::CCoroutineObjectAwaiterAutoStart(coroutine_handle<CCoroutineObjectAwaiterAutoStart::promise_type> Handle)
	: MHandle(Handle)
{
	CCoroutineObjectAwaiterAutoStart::promise_type&				Promise=MHandle.promise();

	wcout << L"COROUTINE [" << Promise.GetID() << L"] - COROUTINE HANDLE CREATED." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiterAutoStart::CCoroutineObjectAwaiterAutoStart(CCoroutineObjectAwaiterAutoStart&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiterAutoStart::~CCoroutineObjectAwaiterAutoStart(void) noexcept
{
	if (static_cast<bool>(MHandle)==true)
	{
		CCoroutineObjectAwaiterAutoStart::promise_type&			Promise=MHandle.promise();
		int														ID=Promise.GetID();

		MHandle.destroy();
		MHandle=nullptr;

		wcout << L"COROUTINE [" << ID << L"] - COROUTINE HANDLE DESTROYED." << endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectAwaiterAutoStart& CCoroutineObjectAwaiterAutoStart::operator=(CCoroutineObjectAwaiterAutoStart&& Other) noexcept
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
bool CCoroutineObjectAwaiterAutoStart::Resume(void) const
{
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	coroutine_handle<promise_type>							HandleIterator=MHandle;

	// !!!!! Cyklus hlada najvnorenejsiu SUB COROUTINE, ktora este nebola ukoncena a ma sa spravit jej SUSPEND.
	while(true)
	{
		coroutine_handle<promise_type>						SubCoroutineHandle=HandleIterator.promise().GetHandle();

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
bool CCoroutineObjectAwaiterAutoStart::await_ready(void) const noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectAwaiterAutoStart::await_resume(void) const noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------