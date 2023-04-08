//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CExceptionBase
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		virtual std::wstring GetTextMessage(void) const noexcept;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CExceptionBase(const std::wstring& Value);
		virtual ~CExceptionBase(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------