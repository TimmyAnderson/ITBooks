//------------------------------------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <string>
//------------------------------------------------------------------------------------------------------
class CCOMException
{
	private:
		std::wstring											MMessage;
		HRESULT													MResult;

	public:
		std::wstring GetMessage(void);
		HRESULT GetResult(void);
		std::wstring GetFormattedMessageText(void);

	public:
		CCOMException(std::wstring Message);
		CCOMException(std::wstring Message, HRESULT Result);
};
//------------------------------------------------------------------------------------------------------