//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectSymmetricTransfer.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectSymmetricTransfer::CCoroutineObjectSymmetricTransfer(coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectSymmetricTransfer::CCoroutineObjectSymmetricTransfer(CCoroutineObjectSymmetricTransfer&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectSymmetricTransfer::~CCoroutineObjectSymmetricTransfer(void) noexcept
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
CCoroutineObjectSymmetricTransfer& CCoroutineObjectSymmetricTransfer::operator=(CCoroutineObjectSymmetricTransfer&& Other) noexcept
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
bool CCoroutineObjectSymmetricTransfer::Resume(void) const
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
coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>> CCoroutineObjectSymmetricTransfer::GetCurrentHandle(void)
{
	return(MHandle);
}
//----------------------------------------------------------------------------------------------------------------------
void CCoroutineObjectSymmetricTransfer::SetNextCoroutineHandle(coroutine_handle<SCoroutineObjectSymmetricTransferPromiseType<CCoroutineObjectSymmetricTransfer>> Handle)
{
	promise_type&												PromiseObject=MHandle.promise();

	PromiseObject.SetNextCoroutineHandle(Handle);
}
//----------------------------------------------------------------------------------------------------------------------