//----------------------------------------------------------------------------------------------------------------------
#include "CCoroutineObjectCustomAllocationSection.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationSection::CCoroutineObjectCustomAllocationSection(coroutine_handle<promise_type> Handle)
	: MHandle(Handle)
{
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationSection::CCoroutineObjectCustomAllocationSection(CCoroutineObjectCustomAllocationSection&& Other) noexcept
	: MHandle(move(Other.MHandle))
{
	Other.MHandle=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
CCoroutineObjectCustomAllocationSection::~CCoroutineObjectCustomAllocationSection(void) noexcept
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
CCoroutineObjectCustomAllocationSection& CCoroutineObjectCustomAllocationSection::operator=(CCoroutineObjectCustomAllocationSection&& Other) noexcept
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
bool CCoroutineObjectCustomAllocationSection::Resume(void) const
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