#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include "StrSafe.h"
//------------------------------------------------------------------------------
void Test(int Argc, wchar_t* Argv[])
{
	if (Argc<3)
	{
		wprintf(L"Invalid parameters !\n");
		return;
	}

	wchar_t*		StringParam1=Argv[1];
	wchar_t*		StringParam2=Argv[2];
	HANDLE			Handle1;
	HANDLE			Handle2;

	swscanf_s(StringParam1,L"%d",&Handle1);
	swscanf_s(StringParam2,L"%d",&Handle2);

	wprintf(L"Waiting for handles [%d] and [%d] !\n",Handle1,Handle2);

	HANDLE			Events[]={Handle1,Handle2};

	if (WaitForMultipleObjects(_countof(Events),Events,TRUE,INFINITE)!=WAIT_FAILED)
	{
		wprintf(L"Waiting FINISHED !\n");

		CloseHandle(Handle1);
		Handle1=NULL;

		CloseHandle(Handle2);
		Handle2=NULL;
	}
	else
	{
		wprintf(L"Waiting FAILED - possibly INVALID HANDLES !!!\n");

		Handle1=NULL;
		Handle2=NULL;
	}
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test(argc,argv);

	ShowExitLine();

	return(0);
}
//-----------------------------------------------------------------------------