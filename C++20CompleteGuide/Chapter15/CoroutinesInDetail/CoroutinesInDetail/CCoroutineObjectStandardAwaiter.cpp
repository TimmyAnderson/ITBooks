//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectStandardAwaiter.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectStandardAwaiter::CCoroutineObjectStandardAwaiter(coroutine_handle<SCoroutineObjectStandardAwaiterPromiseType<CCoroutineObjectStandardAwaiter>> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectStandardAwaiter::CCoroutineObjectStandardAwaiter(CCoroutineObjectStandardAwaiter&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectStandardAwaiter::~CCoroutineObjectStandardAwaiter(void) noexcept
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
CCoroutineObjectStandardAwaiter& CCoroutineObjectStandardAwaiter::operator=(CCoroutineObjectStandardAwaiter&& Other) noexcept
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
bool CCoroutineObjectStandardAwaiter::Resume(void) const
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