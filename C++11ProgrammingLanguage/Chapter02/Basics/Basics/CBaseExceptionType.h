//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
class CBaseExceptionType
{
//-----------------------------------------------------------------------------
	private:
		int														MBaseValue;

	public:
		int GetBaseValue(void) const noexcept
		{
			return(MBaseValue);
		}

	public:
		CBaseExceptionType(int BaseValue)
			: MBaseValue(BaseValue)
		{
		}

		virtual ~CBaseExceptionType(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------