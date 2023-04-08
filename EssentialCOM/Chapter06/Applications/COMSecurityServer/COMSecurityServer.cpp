//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <stdio.h>
#include <conio.h>
#include <ObjIdl.h>
#include "COMSecurityServer_h.h"
#include "COMSecurityObjectFactory.h"
#include "Helpers\Registry.h"
#include "MyAccessControl.h"
//------------------------------------------------------------------------------------------------------
const wchar_t													ModuleName[]=L"COMSecurityServer.exe";
const wchar_t													TypeLibraryName[]=L"COMSecurityServer.tlb";
const wchar_t													FriendlyName[]=L"COMSecurityServer COM object";
const wchar_t													VerIndProgID[]=L"COMSecurityObject";
const wchar_t													ProgID[]=L"COMSecurityObject.1";
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
	IClassFactory*												Factory=new CCOMSecurityObjectFactory(ProcessExitEvent);

	Factory->AddRef();

	// !!!!! CLASS FACTORY sa zaregistruje do SCM, aby pomocou nej mohol SCM vytvarat instancie COM OBJECTS.
	// !!! CLASS FACTORY je REGCLS_SUSPENDED, to znamena, ze zatial este nie je mozne vytvarat pomocou nej instancie COM OBJECTS. Zaregistrovat CLASS FACTORY ako REGCLS_SUSPENDED ma zmysel, ak by za touto registraciou som chcel registrovat aj DALSIE CLASS FACTORIES, ktore su vzajomne ZAVISLE. Pouzitie REGCLS_SUSPENDED znamena, ze sa instancie COM OBJECTS este nebudu moct z tychto CLASS FACTORIES VYTVARAT.
	if (SUCCEEDED(CoRegisterClassObject(CLSID_COMSecurityObject,Factory,CLSCTX_LOCAL_SERVER,REGCLS_SUSPENDED | REGCLS_MULTIPLEUSE,&RegistrationID)))
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
		if (SUCCEEDED(RegisterServer(ModuleName,CLSID_COMSecurityObject,FriendlyName,VerIndProgID,ProgID,NULL)))
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
		if (SUCCEEDED(UnregisterServer(CLSID_COMSecurityObject,VerIndProgID,ProgID,LIBID_COMSecurityServerLib)))
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
		// !!! Vytvorim OBJECT, ktory je CUSTOM implementaciou IAccessControl.
		CMyAccessControl*										MyAccessControl=new CMyAccessControl();

		// !!! Nastavim SECURITY SETTINGS pre COM SERVER.
		// !!! Je nastaveny RPC_C_AUTHN_LEVEL_PKT_PRIVACY a RPC_C_IMP_LEVEL_DELEGATE.
		// !!! Je pouzita CUSTOM implementacia IAccessControl.
		HRESULT													HR=CoInitializeSecurity((IAccessControl*) MyAccessControl,-1,NULL,NULL,RPC_C_AUTHN_LEVEL_PKT_PRIVACY,RPC_C_IMP_LEVEL_DELEGATE,NULL,EOAC_ACCESS_CONTROL,NULL);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"COM SECURITY INITIALIZATION SUCCEEDED !\n");

			RunServer();
		}
		else
		{
			wprintf_s(L"COM SECURITY INITIALIZATION FAILED !\n");
		}
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------