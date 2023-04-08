//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
// !!! LITERAL TYPES NESMU obsahovat CUSTOM CONSTRUCTORS a CUSTOM DESTRUCTORS s vynimkou CONSTEXPR CONSTRUCTORS.
class CLiteralType
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
		constexpr const int& GetValue(void) const noexcept
		{
			return(MValue);
		}

		const int& GetValueNonConstExpr(void) const noexcept
		{
			return(MValue);
		}

	public:
		constexpr CLiteralType(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------