//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CFuctionTryBlocksMember.h"
//-----------------------------------------------------------------------------
class CFuctionTryBlocks
{
//-----------------------------------------------------------------------------
	private:
		CFuctionTryBlocksMember									MValue;

	public:
		const CFuctionTryBlocksMember& GetValue(void) const noexcept;

	public:
		CFuctionTryBlocks(const std::wstring& Value);
		virtual ~CFuctionTryBlocks(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------