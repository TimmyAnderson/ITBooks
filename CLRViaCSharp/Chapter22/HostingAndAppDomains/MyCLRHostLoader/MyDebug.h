//-------------------------------------------------------------------------------------------------------
#include <conio.h>
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
wstring GetErrorCodeString(DWORD ErrorCode)
{
	// Buffer na ulozenie chybovej spravy.
	HLOCAL														HLocal=NULL;

	// Definujem systemovy jazyk.
	DWORD														SystemLocale=MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	// Ziskam Error Code.
	// !!! Funkcia SAMA ALOKUJE PAMET a vracia nan referenciu v HLocal.
	BOOL														IsOK=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, ErrorCode, SystemLocale, (PTSTR) &HLocal, 0, NULL);

	if (IsOK==FALSE)
	{
		// Skusim nacitat NetMsg.dll a zistit ci chyba nebola generovana totu DLL.
		HMODULE													HDLL=LoadLibraryEx(TEXT("netmsg.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);

		if (HDLL!=NULL)
		{
			// !!! Volanie demonstuje ako je mozne nacitat DLL a skontrolovat jej Error Codes a Messages.
			IsOK=FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, HDLL, ErrorCode, SystemLocale, (PTSTR) &HLocal, 0, NULL);
			FreeLibrary(HDLL);
		}
	}

	// !!! Tu je vidiet ako navratovu hodnotu FormatMessage(), ktora je typu BOOL radsej kontrolujem na NEROVNOST s FALSE a NIE na ROVNOST s TRUE.
	if (IsOK!=FALSE && (HLocal!=NULL))
	{
		PCTSTR													ErrorMsg=(PCTSTR) LocalLock(HLocal);
		wstring													Ret=wstring(ErrorMsg);

		// Uvolnim pamat alokovanu volanim FormatMessage().
		LocalFree(HLocal);

		return(Ret);
	}
	else
	{
		wstring													Ret=wstring(L"No text found for this error number.");

		return(Ret);
	}
}
//-------------------------------------------------------------------------------------------------------
void MyInvalidParameterHandler(const wchar_t* Expression, const wchar_t* Function, const wchar_t* File, unsigned int Line, uintptr_t pReserved)
{
   wprintf_s(L"\n\n\nInvalid parameter detected in function %s ! File: %s Line: %d !\n", Function, File, Line);
   wprintf_s(L"Expression: %s !\n\n\n", Expression);
}
//-------------------------------------------------------------------------------------------------------
void SafeMain()
{
	_set_invalid_parameter_handler(MyInvalidParameterHandler);

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ASSERT, 0);
}
//-------------------------------------------------------------------------------------------------------
void ShowExitLine()
{
	wprintf_s(L"\nPress any key to EXIT !\n");
	_getch();
}
//-------------------------------------------------------------------------------------------------------
wstring GetStringFromHR(const wchar_t* Message, HRESULT Error)
{
	wchar_t														HRMessage[1024];

	swprintf_s(HRMessage,L" HR: [%x], Text: [%s].",Error,GetErrorCodeString(Error).c_str());

	wstring														Ret=wstring(Message);

	Ret+=HRMessage;

	return(Ret);
}
//-------------------------------------------------------------------------------------------------------