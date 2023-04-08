//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CExceptionCopyMove final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		CExceptionCopyMove& operator=(const CExceptionCopyMove& Value);
		CExceptionCopyMove& operator=(CExceptionCopyMove&& Value) noexcept;

	public:
		virtual std::wstring GetTextMessage(void) const noexcept;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CExceptionCopyMove(const std::wstring& Value);
		CExceptionCopyMove(const CExceptionCopyMove& Value);
		CExceptionCopyMove(CExceptionCopyMove&& Value) noexcept;
		virtual ~CExceptionCopyMove(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------