//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
class CIncrementFunctionObject final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int operator()(void)
		{
			return(MValue++);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CIncrementFunctionObject(int IntitialValue)
			: MValue(IntitialValue)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------