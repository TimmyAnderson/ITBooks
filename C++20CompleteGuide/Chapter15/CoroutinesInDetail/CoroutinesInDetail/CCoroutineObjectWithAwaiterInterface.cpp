//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectWithAwaiterInterface.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterface::CCoroutineObjectWithAwaiterInterface(coroutine_handle<CCoroutineObjectWithAwaiterInterface::promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterface::CCoroutineObjectWithAwaiterInterface(CCoroutineObjectWithAwaiterInterface&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterface::~CCoroutineObjectWithAwaiterInterface(void) noexcept
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
CCoroutineObjectWithAwaiterInterface& CCoroutineObjectWithAwaiterInterface::operator=(CCoroutineObjectWithAwaiterInterface&& Other) noexcept
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
bool CCoroutineObjectWithAwaiterInterface::Resume(void) const
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

	CCoroutineObjectWithAwaiterInterface::promise_type			PromiseType=HandleIterator.promise();

	wcout << L"!!!!! RESUME for COROUTINE " << PromiseType.GetCoroutineName() << L" CALLED." << endl;

	HandleIterator.resume();

	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObjectWithAwaiterInterface::await_ready(void) const noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectWithAwaiterInterface::await_resume(void) const noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------