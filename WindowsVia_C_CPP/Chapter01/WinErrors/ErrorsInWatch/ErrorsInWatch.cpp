#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
void Test(void)
{
	// Zavolam nejaku funkciu, ktora zlyha.
	BOOL			Ret1=AddAccessAllowedAce(NULL,1,2,NULL);
	DWORD			ErrorCode1=GetLastError();

	printf("Ret: [%d], EC: [%d] ! Look at Watch window in breakpoint and type '$err,hr' !",Ret1,ErrorCode1);
	_getch();

	BOOL			Ret2=CreateCaret((HWND) 4000,(HBITMAP) 6000,12,23);
	DWORD			ErrorCode2=GetLastError();
	
	printf("Ret: [%d], EC: [%d] ! Look at Watch window in breakpoint and type '$err,hr' !",Ret2,ErrorCode2);
	_getch();

	SetLastError(2);

	DWORD			ErrorCode3=GetLastError();
	
	printf("EC: [%d] ! Look at Watch window in breakpoint and type '$err,hr' !",ErrorCode3);
	_getch();
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