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
	// Handle RELATIVNY na PARENT process.
	HANDLE			HandleParentKO;
	DWORD			ParentProcessID;

	swscanf_s(StringParam1,L"%d",&HandleParentKO);
	swscanf_s(StringParam2,L"%d",&ParentProcessID);

	wprintf(L"Parent KO handle [%d], Parent process ID [%d] !\n",HandleParentKO,ParentProcessID);

	HANDLE			ParentProcessHandle;
		
	if ((ParentProcessHandle=OpenProcess(PROCESS_DUP_HANDLE,FALSE,ParentProcessID))!=NULL)
	{
		wprintf(L"Parent process handle error [%d] !\n",ParentProcessHandle);

		HANDLE		HandleChildKO;

		if (DuplicateHandle(ParentProcessHandle,HandleParentKO,GetCurrentProcess(),&HandleChildKO,0,FALSE,DUPLICATE_SAME_ACCESS)!=0)
		{
			wprintf(L"HANDLE DUPLICATED and is set to value [%d] !\n",HandleChildKO);
			wprintf(L"WAITING FOR EVENT !\n");

			DWORD	Ret;
			
			if ((Ret=WaitForSingleObject(HandleChildKO,INFINITE))==WAIT_FAILED)
			{
				wprintf(L"WAITING FAILED with error [%d] !\n",GetLastError());
			}
			else
				wprintf(L"WAITING SUCCESSFULLY FINISHED !\n");

			CloseHandle(HandleChildKO);
		}
		else
			wprintf(L"FAILED to duplicate handle !\n");
		
		CloseHandle(ParentProcessHandle);
	}
	else
	{
		DWORD		Error=GetLastError();

		wprintf(L"Can't get PARENT PROCESS HANDLE %d !\n",Error);
	}



/*
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
	*/
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