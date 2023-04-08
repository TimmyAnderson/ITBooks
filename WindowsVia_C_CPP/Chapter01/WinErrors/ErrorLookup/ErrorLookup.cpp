#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void PrintErrorCodeToConsole(DWORD ErrorCode)
{
	// Buffer na ulozenie chybovej spravy.
	HLOCAL			HLocal=NULL;

	// Definujem systemovy jazyk.
	DWORD			SystemLocale=MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL);

	// Ziskam Error Code.
	// !!! Funkcia SAMA ALOKUJE PAMET a vracia nan referenciu v HLocal.
	BOOL			IsOK=FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, ErrorCode, SystemLocale, (PTSTR) &HLocal, 0, NULL);

	if (IsOK==FALSE)
	{
		// Skusim nacitat NetMsg.dll a zistit ci chyba nebola generovana totu DLL.
		HMODULE		HDLL=LoadLibraryEx(TEXT("netmsg.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);

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
		PCTSTR		ErrorMsg=(PCTSTR) LocalLock(HLocal);

		wprintf(ErrorMsg);

		// Uvolnim pamat alokovanu volanim FormatMessage().
		LocalFree(HLocal);
	}
	else
	{
		wprintf(TEXT("No text found for this error number."));
	}
}
//------------------------------------------------------------------------------
void Test(void)
{
	PrintErrorCodeToConsole(2);	
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------