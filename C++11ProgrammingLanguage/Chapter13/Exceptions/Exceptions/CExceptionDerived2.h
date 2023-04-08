//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
#include "CExceptionBase.h"
//-----------------------------------------------------------------------------
class CExceptionDerived2 final : public CExceptionBase
{
//-----------------------------------------------------------------------------
	public:
		virtual std::wstring GetTextMessage(void) const noexcept override;

	public:
		CExceptionDerived2(const std::wstring& Value);
		~CExceptionDerived2(void) override;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------