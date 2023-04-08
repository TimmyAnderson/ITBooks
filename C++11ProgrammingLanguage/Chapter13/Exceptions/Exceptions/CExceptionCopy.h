//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CExceptionCopy final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		CExceptionCopy& operator=(const CExceptionCopy& Value);
		CExceptionCopy& operator=(CExceptionCopy&& Value) noexcept=delete;

	public:
		virtual std::wstring GetTextMessage(void) const noexcept;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CExceptionCopy(const std::wstring& Value);
		CExceptionCopy(const CExceptionCopy& Value);
		CExceptionCopy(CExceptionCopy&& Value) noexcept=delete;
		virtual ~CExceptionCopy(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------