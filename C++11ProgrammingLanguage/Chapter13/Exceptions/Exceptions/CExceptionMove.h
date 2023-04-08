//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <string>
#include <iostream>
//-----------------------------------------------------------------------------
class CExceptionMove final
{
//-----------------------------------------------------------------------------
	private:
		std::wstring											MValue;

	public:
		CExceptionMove& operator=(const CExceptionMove& Value)=delete;
		CExceptionMove& operator=(CExceptionMove&& Value) noexcept;

	public:
		virtual std::wstring GetTextMessage(void) const noexcept;

	public:
		const std::wstring& GetValue(void) const noexcept;

	public:
		CExceptionMove(const std::wstring& Value);
		CExceptionMove(const CExceptionMove& Value)=delete;
		// !!! Pre pouzitie MOVE SEMANTICS je NUTNE definovat MOVE CONSTRUCTOR.
		CExceptionMove(CExceptionMove&& Value) noexcept;
		virtual ~CExceptionMove(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------