#include "stdafx.h"
#include <windows.h>
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <TlHelp32.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
wchar_t				InjectionDLL[]={L"C:\\RemoteThreadInjectionDLL.dll"};
//------------------------------------------------------------------------------
// Vracia HMODULE na REMOTE DLL.
HMODULE GetRemoteDLLModuleHandle(DWORD ProcessID)
{
	HANDLE					HSnapshot=NULL;
	HMODULE					Ret=(HMODULE) 0;

	if ((HSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,ProcessID))!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"Snapshot of REMOTE PROCESS CREATED !\n");

		MODULEENTRY32W		ME={sizeof(ME)};
		BOOL				MoreMods=Module32FirstW(HSnapshot,&ME);

		while(MoreMods==TRUE)
		{
			if (_wcsicmp(InjectionDLL,ME.szModule)==0 || _wcsicmp(InjectionDLL,ME.szExePath)==0)
			{
				Ret=(HMODULE) ME.modBaseAddr;
				break;
			}

			MoreMods=Module32NextW(HSnapshot,&ME);
		}
	}
	else
		wprintf_s(L"Snapshot of REMOTE PROCESS FAILED to CREATE !\n");

	return(Ret);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	wchar_t			Buf[1024];
	int				RemotePID=0;
	HANDLE			HRemoteProcess;

	while(true)
	{
		wprintf_s(L"Write process ID !\n");
		_getws_s(Buf,_countof(Buf));
		
		if (swscanf_s(Buf,L"%d",&RemotePID)==1)
			break;
	}

	// Ak nemam potrebne Permissions, tak sa HANDLE na proces neotvori.
	if ((HRemoteProcess=OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_CREATE_THREAD | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_VM_WRITE,FALSE,RemotePID))!=NULL)
	{
		wprintf_s(L"Process successfully OPENED !\n");

		int				StringSize=sizeof(InjectionDLL);

		// Alokujem pamat v remote process.
		wchar_t*		AddressInRemoteProcess=(wchar_t*) VirtualAllocEx(HRemoteProcess, NULL, StringSize, MEM_COMMIT, PAGE_READWRITE);

		if (AddressInRemoteProcess!=NULL)
		{
			wprintf_s(L"Memory at address [%p] successfully allocated in REMOTE PROCESS !\n",AddressInRemoteProcess);

			// Do pamate v REMOTE PROCESE zapisem meno DLL, ktora ma byt injektovana do REMOTE PROCESU.
			if (WriteProcessMemory(HRemoteProcess,AddressInRemoteProcess,(LPCVOID)InjectionDLL, StringSize,NULL)!=0)
			{
				wprintf_s(L"DLL name was successfully written to REMOTE PROCESS !\n");

				wchar_t	DLLNameFromRemoteProcess[1024];

				// Pre istotu precitam pamat v REMOTE PROCESS, aby som zistil, ci sa pamat skutocne zapisala. Nie je to potrebne - robim to iba pre zaujimavost.
				if (ReadProcessMemory(HRemoteProcess,AddressInRemoteProcess,(LPVOID)DLLNameFromRemoteProcess,StringSize,NULL)!=0)
				{
					wprintf_s(L"DLL name [%s] was successfully read to REMOTE PROCESS !\n",DLLNameFromRemoteProcess);

					PTHREAD_START_ROUTINE		LoadLibraryFunction=(PTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryW");
					PTHREAD_START_ROUTINE		FreeLibraryFunction=(PTHREAD_START_ROUTINE) GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "FreeLibrary");

					// !!! Adresy su rovnake, hoci kniha tvrdi, ze by mali byt ROZNE (strana 622,623) a aj preto vraj je treba adresy funkcii zistovat volanim GetProcAddress().
					wprintf_s(L"LoadLibrary() - function address - STATIC: [%p], DYNAMIC: [%p] !\n",LoadLibrary,LoadLibraryFunction);
					wprintf_s(L"FreeLibrary() - function address - STATIC: [%p], DYNAMIC: [%p] !\n",FreeLibrary,FreeLibraryFunction);

					if (LoadLibraryFunction!=NULL && FreeLibraryFunction!=NULL)
					{
						wprintf_s(L"DLL name successfully got LoadLibrary() or FreeLibrary() function addresses !\n");

						// Ako adresu THREAD FUNKCIE dam adresu LoadLibrary().
						// !!! Ako parameter THREAD FUNKCIE dam REMOTE ADDRESS na meno DLL.
						HANDLE					HRemoteThreadLoadLibrary=CreateRemoteThread(HRemoteProcess,NULL,0,LoadLibraryFunction,AddressInRemoteProcess,0,NULL);

						if (HRemoteThreadLoadLibrary!=NULL)
						{
							wprintf_s(L"REMOTE THREAD [LoadLibrary()] successfully CREATED !\n");

							WaitForSingleObject(HRemoteThreadLoadLibrary,INFINITE);
							
							wprintf_s(L"REMOTE THREAD [LoadLibrary()] successfully FINISHED !\n");

							HMODULE				ModuleDLL=GetRemoteDLLModuleHandle(RemotePID);

							if (ModuleDLL!=((HMODULE)0))
							{
								wprintf_s(L"DLL HMODULE in REMOTE PROCESS successfully FOUND !\n");

								// Ako adresu THREAD FUNKCIE dam adresu FreeLibrary().
								// !!! Ako parameter THREAD FUNKCIE dam HMODULE na DLL.
								HANDLE			HRemoteThreadFreeLibrary=CreateRemoteThread(HRemoteProcess,NULL,0,FreeLibraryFunction,ModuleDLL,0,NULL);

								if (HRemoteThreadFreeLibrary!=NULL)
								{
									wprintf_s(L"REMOTE THREAD [FreeLibrary()] successfully CREATED !\n");

									WaitForSingleObject(HRemoteThreadFreeLibrary,INFINITE);
									
									wprintf_s(L"REMOTE THREAD [FreeLibrary()] successfully FINISHED !\n");

									CloseHandle(HRemoteThreadFreeLibrary);
								}
								else
									wprintf_s(L"REMOTE THREAD [FreeLibrary()] FAILED to CREATE !\n");
							}
							else
								wprintf_s(L"DLL HMODULE in REMOTE PROCESS FAILED to be FOUND !\n");

							CloseHandle(HRemoteThreadLoadLibrary);
						}
						else
							wprintf_s(L"REMOTE THREAD [LoadLibrary()] FAILED to CREATE !\n");
					}
					else
						wprintf_s(L"DLL name FAILED to get LoadLibrary() or FreeLibrary() function addresses !\n");
				}
				else
					wprintf_s(L"DLL name FAILED to read REMOTE PROCESS !\n");
			}
			else
				wprintf_s(L"DLL name FAILED to write REMOTE PROCESS !\n");

	        VirtualFreeEx(HRemoteProcess,AddressInRemoteProcess,0,MEM_RELEASE);
		}
		else
			wprintf_s(L"Can't allocate memory in REMOTE PROCESS !\n");

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