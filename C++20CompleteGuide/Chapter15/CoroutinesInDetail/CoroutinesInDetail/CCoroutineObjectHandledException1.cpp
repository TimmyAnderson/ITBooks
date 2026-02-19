//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectHandledException1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectHandledException1::CCoroutineObjectHandledException1(coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectHandledException1::CCoroutineObjectHandledException1(CCoroutineObjectHandledException1&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectHandledException1::~CCoroutineObjectHandledException1(void) noexcept
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
CCoroutineObjectHandledException1& CCoroutineObjectHandledException1::operator=(CCoroutineObjectHandledException1&& Other) noexcept
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
bool CCoroutineObjectHandledException1::Resume(void) const
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
void CCoroutineObjectHandledException1::ThrowUnhandledException(void) const
{
	if (static_cast<bool>(MHandle)==false)
	{
		return;
	}

	const promise_type&											Promise=MHandle.promise();
	const exception_ptr&										ExceptionPointer=Promise.GetExceptionPointer();

	if (static_cast<bool>(ExceptionPointer)==true)
	{
		rethrow_exception(ExceptionPointer);
	}
}
//----------------------------------------------------------------------------------------------------------------------