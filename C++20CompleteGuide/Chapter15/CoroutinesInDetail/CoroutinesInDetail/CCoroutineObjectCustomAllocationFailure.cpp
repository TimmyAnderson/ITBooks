//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectCustomAllocationFailure.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationFailure::CCoroutineObjectCustomAllocationFailure(coroutine_handle<void> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationFailure::CCoroutineObjectCustomAllocationFailure(CCoroutineObjectCustomAllocationFailure&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationFailure::~CCoroutineObjectCustomAllocationFailure(void) noexcept
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
CCoroutineObjectCustomAllocationFailure& CCoroutineObjectCustomAllocationFailure::operator=(CCoroutineObjectCustomAllocationFailure&& Other) noexcept
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
bool CCoroutineObjectCustomAllocationFailure::Resume(void) const
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