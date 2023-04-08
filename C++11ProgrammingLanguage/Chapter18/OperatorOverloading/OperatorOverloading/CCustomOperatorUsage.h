//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
class CCustomOperatorUsage final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int operator+(int Value) const
		{
			return(MValue+Value);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CCustomOperatorUsage(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------