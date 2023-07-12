//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
//-----------------------------------------------------------------------------
class CBase
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CBase(const std::wstring& Value)
			: MValue(Value)
		{
		}

		virtual ~CBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------