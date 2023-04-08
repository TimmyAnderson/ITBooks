#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <TlHelp32.h>
#include "MyDebug.h"
#include "../CreateRemoteThreadDLL/CreateRemoteThreadDLL.h"
//------------------------------------------------------------------------------
// Vypise vsetky DLL.
HMODULE GetRemoteDLLModuleHandle(DWORD ProcessID)
{
	HANDLE					HSnapshot=NULL;
	HMODULE					Ret=(HMODULE) 0;

	if ((HSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,ProcessID))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"Snapshot CREATED !\n");

		MODULEENTRY32W		ME={sizeof(ME)};
		BOOL				MoreMods=Module32FirstW(HSnapshot,&ME);

		while(MoreMods==TRUE)
		{
			wprintf_s(L"Module: [%s], ExePaht: [%s] !\n",ME.szModule,ME.szExePath);
			MoreMods=Module32NextW(HSnapshot,&ME);
		}
	}
	else
		wprintf_s(L"Snapshot FAILED to CREATE !\n");

	return(Ret);
}
//------------------------------------------------------------------------------
void Test(void)
{
	wchar_t			Buf[1024];
	int				RemotePID=0;
	HANDLE			HRemoteProcess;

	wprintf_s(L"PID: [%d] - MASTER !\n",GetCurrentProcessId());

	DLLLoadTest();

	while(true)
	{
		wprintf_s(L"Run SLAVE process and write its process ID !\n");
		_getws_s(Buf,_countof(Buf));
		
		if (swscanf_s(Buf,L"%d",&RemotePID)==1)
			break;
	}

	// Ak nemam potrebne Permissions, tak sa HANDLE na proces neotvori.
	if ((HRemoteProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE,FALSE,RemotePID))!=NULL)
	{
		wprintf_s(L"Process successfully OPENED !\n");

		HMODULE						HModule=NULL;
			
		if ((HModule=GetModuleHandle(L"CreateRemoteThreadDLL.dll"))!=NULL)
		{
			wprintf_s(L"DLL MODULE successfully FOUND !\n");

			// !!!!! Nazov je MANGLED, pretoze funkcie pouziva priznak 'WINAPI'.
			PTHREAD_START_ROUTINE		RemoteThreadFunctionAddress=(PTHREAD_START_ROUTINE) GetProcAddress(HModule,"_RemoteThreadFunction@4");

			// !!! Adresy su zhodne.
			wprintf_s(L"Function address - STATIC: [%p], DYNAMIC: [%p] !\n",RemoteThreadFunction,RemoteThreadFunctionAddress);

			if (RemoteThreadFunctionAddress!=NULL)
			{
				wprintf_s(L"RemoteThreadFunction() ADDRESS was successfully FOUND !\n");

				// !!!!! Davam smernik na FUNKCIU RemoteThreadFunction() definovanu v DLL, ktora sa stava THREAD FUNKCIOU v REMOTE THREAD.
				// !!!!! Funguje to IBA PRETO, lebo DLL je FIXED a teda v OBOCH PROCESOCH (Master, Slave) je NAMAPOVANA na ROVNAKU ADRESU.
				HANDLE					HRemoteThreadFunction=CreateRemoteThread(HRemoteProcess,NULL,0,RemoteThreadFunctionAddress,NULL,0,NULL);

				if (HRemoteThreadFunction!=NULL)
				{
					wprintf_s(L"REMOTE THREAD [RemoteThreadFunction()] successfully CREATED !\n");

					WaitForSingleObject(HRemoteThreadFunction,INFINITE);
					
					wprintf_s(L"REMOTE THREAD [RemoteThreadFunction()] successfully FINISHED !\n");

					CloseHandle(HRemoteThreadFunction);
				}
			}
			else
				wprintf_s(L"RemoteThreadFunction() ADDRESS FAILED to be FOUND !\n");
		}
		else
			wprintf_s(L"Can't load DLL MODULE !\n");

		CloseHandle(HRemoteProcess);
	}
	else
		wprintf_s(L"Process FAILED to OPEN !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------