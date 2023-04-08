//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
class CConstExprClass
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		constexpr operator int(void) const noexcept
		{
			return(MValue);
		}

	public:
		constexpr int ConstExprFunction1(void)
		{
			return(MValue);
		}

		constexpr int ConstExprFunction2(void) const
		{
			return(MValue);
		}

		constexpr int ConstExprFunctionChangingValue(void)
		{
			MValue=33;

			return(MValue);
		}

	public:
		constexpr CConstExprClass(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------