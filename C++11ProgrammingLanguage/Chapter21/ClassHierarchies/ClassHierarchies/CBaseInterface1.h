//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CBaseInterface1
{
//-------------------------------------------------------------------------------------------------------
	public:
		virtual const std::wstring& GetValue1(void) const noexcept=0;

	public:
		CBaseInterface1(void)
		{
		}

		virtual ~CBaseInterface1(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------