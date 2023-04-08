//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CBaseExceptionType.h"
//-----------------------------------------------------------------------------
class CDerivedExceptionType : public CBaseExceptionType
{
//-----------------------------------------------------------------------------
	private:
		int														MDerivedValue;

	public:
		int GetDerivedValue(void) const noexcept
		{
			return(MDerivedValue);
		}

	public:
		CDerivedExceptionType(int BaseValue, int DerivedValue)
			: CBaseExceptionType(BaseValue), MDerivedValue(DerivedValue)
		{
		}

		virtual ~CDerivedExceptionType(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------