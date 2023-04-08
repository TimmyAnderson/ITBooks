//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CFuctionTryBlocksMember final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CFuctionTryBlocksMember(const std::wstring& Value);
		virtual ~CFuctionTryBlocksMember(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------