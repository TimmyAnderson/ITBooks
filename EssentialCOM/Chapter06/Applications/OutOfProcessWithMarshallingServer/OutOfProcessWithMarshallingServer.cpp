//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <stdio.h>
#include <conio.h>
#include "OutOfProcessWithMarshallingServer_h.h"
#include "OutOfProcessWithMarshallingObjectFactory.h"
#include "Helpers\Registry.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"OutOfProcessWithMarshallingServer.exe";
const wchar_t													TypeLibraryName[]=L"OutOfProcessWithMarshallingServer.tlb";
const wchar_t													FriendlyName[]=L"OutOfProcessWithMarshallingServer COM object";
const wchar_t													VerIndProgID[]=L"OutOfProcessWithMarshallingObject";
const wchar_t													ProgID[]=L"OutOfProcessWithMarshallingObject.1";
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void RunServer(void)
{
	//MessageBox(NULL,L"Attach to process !!!",L"Debug",MB_OK);

	// !!! EVENT na ktory MAIN THREAD CAKA. Jeho SIGNALIZACIA znamena, ze OUT-OF-PROCESS moze byt UKONCENY.
	HANDLE														ProcessExitEvent=CreateEvent(NULL,FALSE,FALSE,NULL);
	DWORD														RegistrationID=0;

	// !!! Vytvori sa instancia FACTORY CLASS.
	IClassFactory*												Factory=new COutOfProcessWithMarshallingObjectFactory(ProcessExitEvent);

	Factory->AddRef();

	// !!!!! CLASS FACTORY sa zaregistruje do SCM, aby pomocou nej mohol SCM vytvarat instancie COM OBJECTS.
	// !!! CLASS FACTORY je REGCLS_SUSPENDED, to znamena, ze zatial este nie je mozne vytvarat pomocou nej instancie COM OBJECTS. Zaregistrovat CLASS FACTORY ako REGCLS_SUSPENDED ma zmysel, ak by za touto registraciou som chcel registrovat aj DALSIE CLASS FACTORIES, ktore su vzajomne ZAVISLE. Pouzitie REGCLS_SUSPENDED znamena, ze sa instancie COM OBJECTS este nebudu moct z tychto CLASS FACTORIES VYTVARAT.
	if (SUCCEEDED(CoRegisterClassObject(CLSID_OutOfProcessWithMarshallingObject,Factory,CLSCTX_LOCAL_SERVER,REGCLS_SUSPENDED | REGCLS_MULTIPLEUSE,&RegistrationID)))
	{
		// !!! Povoli sa vytvaranie INSTACNII COM OBJECT VSETKYCH ZAREGISTROVANYCH CLASS FACTORIES.
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

	// !!! Spusti sa proces REGISTRACIE COM SERVER.
	if (wcsstr(CmdLine[1],L"RegServer")!=NULL)
	{
		// !!! Zaregistruje COM SERVER.
		if (SUCCEEDED(RegisterServer(ModuleName,CLSID_OutOfProcessWithMarshallingObject,FriendlyName,VerIndProgID,ProgID,NULL)))
		{
			wprintf_s(L"Server was REGISTERED !\n");
		}
		else
		{
			wprintf_s(L"Server FAILED to REGISTER !\n");
		}
	}
	// !!! Spusti sa proces ODREGISTRACIE COM SERVER.
	else if (wcsstr(CmdLine[1],L"UnregServer")!=NULL)
	{
		// !!! Odregistruje COM SERVER.
		if (SUCCEEDED(UnregisterServer(CLSID_OutOfProcessWithMarshallingObject,VerIndProgID,ProgID,LIBID_OutOfProcessWithMarshallingServerLib)))
		{
			wprintf_s(L"Server was UNREGISTERED !\n");
		}
		else
		{
			wprintf_s(L"Server FAILED to UNREGISTER !\n");
		}
	}
	// !!!!! COM SERVER bol spusteny zo strany COM SYSTEM. COM SERVER musi zaregistrovat COM OBJECTS, ktore vystavuje do SCM.
	else
	{
		RunServer();
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------