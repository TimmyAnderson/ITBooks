#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE			H1=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE			H2=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE			H3=CreateEvent(NULL,FALSE,FALSE,NULL);

	wprintf(L"H1: [%d], H2: [%d], H3: [%d] !\n",H1,H2,H3);

	// Otvorim 2 HANDLES na TEN ISTY KO.
	HANDLE			H4=CreateEvent(NULL,FALSE,FALSE,L"Test");
	HANDLE			H5=CreateEvent(NULL,FALSE,FALSE,L"Test");
	HANDLE			H6=CreateEvent(NULL,FALSE,FALSE,L"Test");

	wprintf(L"H4: [%d], H5: [%d], H6: [%d] !\n",H4,H5,H6);

	CloseHandle(H1);
	CloseHandle(H2);
	CloseHandle(H3);
	CloseHandle(H4);
	CloseHandle(H5);
	CloseHandle(H6);
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