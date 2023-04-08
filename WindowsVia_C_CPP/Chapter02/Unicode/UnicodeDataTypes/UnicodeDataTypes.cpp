#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void Test(void)
{
	char			CharANSI='A';
	wchar_t			CharUNICODE='A';
	TCHAR			CharTCHAR='A';

	// To aky bude mat typ TCHAR zavisi od toho ci je nastaveny UNICODE.
	wprintf(L"CharANSI count: [%d], CharUNICODE count: [%d], CharTCHAR count: [%d] !",sizeof(CharANSI),sizeof(CharUNICODE),sizeof(CharTCHAR));
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