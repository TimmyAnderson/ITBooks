//----------------------------------------------------------------------------------------------------------------------
#include "SMyTreeKey.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
SMyTreeKey::SMyTreeKey(ULONG Key)
	: MKey(Key)
{
}
//----------------------------------------------------------------------------------------------------------------------
SMyTreeKey::~SMyTreeKey(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool SMyTreeKey::operator<(const SMyTreeKey& Other) const noexcept
{
	if (MKey<Other.MKey)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
ULONG SMyTreeKey::GetKey(void) const noexcept
{
	return(MKey);
}
//----------------------------------------------------------------------------------------------------------------------