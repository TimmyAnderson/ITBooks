//------------------------------------------------------------------------------------------------------
#define _CRTDBG_MAP_ALLOC
//------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <conio.h>
#include <crtdbg.h>
#include <strsafe.h>
#include <string>
#include <sstream>
//------------------------------------------------------------------------------------------------------
class CHelpers
{
	private:
		static void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved);

	public:
		static void SafeMain(void);
		static void ShowExitLine(void);
		static void WriteTextWithTime(wchar_t* Text, bool Day, bool Miliseconds);
		static void WriteTextWithTime(wchar_t* Text);
		static void WriteDebugText(wchar_t* Text);
		static void PrintErrorCodeToConsole(wchar_t* Prefix, DWORD ErrorCode);
		static std::wstring PrepareLogMessage(std::wstring LogMessage, HRESULT HR);
		static void ThrowWString(HRESULT HR, std::wstring ErrorText);
		static std::wstring ConvertIntToString(int Value);
		static std::wstring ConvertGuidToString(GUID Value);
};
//------------------------------------------------------------------------------------------------------