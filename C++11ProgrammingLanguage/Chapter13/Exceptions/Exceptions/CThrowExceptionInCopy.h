//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CThrowExceptionInCopy final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		CThrowExceptionInCopy& operator=(const CThrowExceptionInCopy& Value);

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CThrowExceptionInCopy(const std::wstring& Value);
		CThrowExceptionInCopy(const CThrowExceptionInCopy& Value);
		virtual ~CThrowExceptionInCopy(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------