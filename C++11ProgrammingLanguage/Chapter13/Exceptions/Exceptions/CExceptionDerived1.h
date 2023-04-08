//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CExceptionBase.h"
//-----------------------------------------------------------------------------
class CExceptionDerived1 final : public CExceptionBase
{
//-----------------------------------------------------------------------------
	public:
		virtual std::wstring GetTextMessage(void) const noexcept override;

	public:
		CExceptionDerived1(const std::wstring& Value);
		~CExceptionDerived1(void) override;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------