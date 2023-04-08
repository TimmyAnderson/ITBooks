//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <stdio.h>
#include "OutOfProcessObject_h.h"
#include "OutOfProcessObjectFactory.h"
#include "Helpers\Registry.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"OutOfProcessServer.exe";
const wchar_t													TypeLibraryName[]=L"OutOfProcessServer.tlb";
const wchar_t													FriendlyName[]=L"OutOfProcessServer COM object";
const wchar_t													VerIndProgID[]=L"OutOfProcessObject";
const wchar_t													ProgID[]=L"OutOfProcessObject.1";
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void RunServer(void)
{
	//MessageBox(NULL,L"Attach to process !!!",L"Debug",MB_OK);

	// !!! EVENT na ktory MAIN THREAD CAKA. Jeho SIGNALIZACIA znamena, ze OUT-OF-PROCESS moze byt UKONCENY.
	HANDLE													ProcessExitEvent=CreateEvent(NULL,FALSE,FALSE,NULL);
	DWORD													RegistrationID=0;

	// !!! Vytvori sa instancia FACTORY CLASS.
	IClassFactory*											Factory=new COutOfProcessObjectFactory(ProcessExitEvent);

	Factory->AddRef();

	if (SUCCEEDED(CoRegisterClassObject(CLSID_OutOfProcessObject,Factory,CLSCTX_LOCAL_SERVER,REGCLS_SUSPENDED | REGCLS_MULTIPLEUSE,&RegistrationID)))
	{
		CoResumeClassObjects();

		wprintf_s(L"Server was STARTED !\n");

		// !!!!! Caka sa na uzatvorenie vsetkych instancii COM OBJECT, ktora nastava ak FUNCTION CoReleaseServerProcess() vrati hodnotu 0.
		WaitForSingleObject(ProcessExitEvent,INFINITE);
		CloseHandle(ProcessExitEvent);

		// !!! Odregistruje FACTORY CLASS.
		CoRevokeClassObject(RegistrationID);

		// !!! Odstrani sa instancia FACTORY CLASS.
		Factory->Release();
	}
	else
	{
		wprintf_s(L"Server FAILED to START !\n");
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int Argc, _TCHAR* CmdLine[])
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	if (Argc<2)
	{
		wprintf_s(L"Not ENOUGH PARAMETERS !\n");
		return(-1);
	}

	if (wcsstr(CmdLine[1],L"RegServer")!=NULL)
	{
		// !!! Zaregistruje COM SERVER.
		if (SUCCEEDED(RegisterServer(ModuleName,CLSID_OutOfProcessObject,FriendlyName,VerIndProgID,ProgID,NULL)))
		{
			wprintf_s(L"Server was REGISTERED !\n");
		}
		else
		{
			wprintf_s(L"Server FAILED to REGISTER !\n");
		}
	}
	else if (wcsstr(CmdLine[1],L"UnregServer")!=NULL)
	{
		// !!! Odregistruje COM SERVER.
		if (SUCCEEDED(UnregisterServer(CLSID_OutOfProcessObject,VerIndProgID,ProgID,LIBID_OutOfProcessServerLib)))
		{
			wprintf_s(L"Server was UNREGISTERED !\n");
		}
		else
		{
			wprintf_s(L"Server FAILED to UNREGISTER !\n");
		}
	}
	else
	{
		RunServer();
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------