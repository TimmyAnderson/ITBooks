//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectWithAwaiterInterfaceFaulty.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterfaceFaulty::CCoroutineObjectWithAwaiterInterfaceFaulty(coroutine_handle<CCoroutineObjectWithAwaiterInterfaceFaulty::promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterfaceFaulty::CCoroutineObjectWithAwaiterInterfaceFaulty(CCoroutineObjectWithAwaiterInterfaceFaulty&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectWithAwaiterInterfaceFaulty::~CCoroutineObjectWithAwaiterInterfaceFaulty(void) noexcept
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
CCoroutineObjectWithAwaiterInterfaceFaulty& CCoroutineObjectWithAwaiterInterfaceFaulty::operator=(CCoroutineObjectWithAwaiterInterfaceFaulty&& Other) noexcept
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
bool CCoroutineObjectWithAwaiterInterfaceFaulty::Resume(void) const
{
	if (static_cast<bool>(MHandle)==false || MHandle.done()==true)
	{
		return(false);
	}

	coroutine_handle<promise_type>								HandleIterator=MHandle;

	// !!!!! Vykona sa RESUME VZDY iba NAJVYSSEJ COROUTINE v COROUTINE CALLING HIERARCHY cim sa NIKDY nevykona RESUME INNER COROUTINES.
	HandleIterator.resume();

	CCoroutineObjectWithAwaiterInterfaceFaulty::promise_type	PromiseType=HandleIterator.promise();

	wcout << L"!!!!! RESUME for COROUTINE " << PromiseType.GetCoroutineName() << L" CALLED." << endl;

	HandleIterator.resume();

	bool														CanResume=(!MHandle.done());

	return(CanResume);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CCoroutineObjectWithAwaiterInterfaceFaulty::await_ready(void) const noexcept
{
	return(false);
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectWithAwaiterInterfaceFaulty::await_resume(void) const noexcept
{
	// EMPTY.
}
//----------------------------------------------------------------------------------------------------------------------