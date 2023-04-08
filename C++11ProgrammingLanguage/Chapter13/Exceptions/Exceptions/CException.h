//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CException final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		virtual std::wstring GetTextMessage(void) const noexcept;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CException(const std::wstring& Value);
		virtual ~CException(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------