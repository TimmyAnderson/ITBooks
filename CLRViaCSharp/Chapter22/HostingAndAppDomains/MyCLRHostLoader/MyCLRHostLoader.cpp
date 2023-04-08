//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include "MyDebug.h"
#include <metahost.h>
#include <string>
//-------------------------------------------------------------------------------------------------------
// Zavedie SHIM a CLR HOSTING API.
#pragma comment(lib, "mscoree.lib")
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	HRESULT														HR;
	ICLRMetaHost												*MetaHost=NULL;
	ICLRRuntimeInfo												*RuntimeInfo=NULL;
	ICLRRuntimeHost												*RuntimeHost=NULL;
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost))==TRUE)
		{
			throw(GetStringFromHR(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo))==TRUE)
		{
			throw(GetStringFromHR(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost))==TRUE)
		{
			throw(GetStringFromHR(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		DWORD													RetValue=0;

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start())==TRUE)
		{
			throw(GetStringFromHR(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod1",L"Timmy Anderson",&RetValue))==TRUE)
		{
			throw(GetStringFromHR(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

		// Zastavim CLR HOST, pricom sa vypnut VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop())==TRUE)
		{
			throw(GetStringFromHR(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	if (RuntimeHost!=NULL)
	{
		RuntimeHost->Release();
		RuntimeHost=NULL;
	}

	if (RuntimeInfo!=NULL)
	{
		RuntimeInfo->Release();
		RuntimeInfo=NULL;
	}

	if (MetaHost!=NULL)
	{
		MetaHost->Release();
		MetaHost=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	HRESULT														HR;
	ICLRMetaHost												*MetaHost=NULL;
	ICLRRuntimeInfo												*RuntimeInfo=NULL;
	ICLRRuntimeHost												*RuntimeHost=NULL;

	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost))==TRUE)
		{
			throw(GetStringFromHR(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo))==TRUE)
		{
			throw(GetStringFromHR(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost))==TRUE)
		{
			throw(GetStringFromHR(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		DWORD													RetValue=0;

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start())==TRUE)
		{
			throw(GetStringFromHR(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		// !!!!! Kedze vsak ENTRY POINT FUNCTION vytvori novy MANAGED THREAD a skonci OKAMZITE, tak je volanie FUNCTION _getch() umoznuje zastavenie CLR a tym aj vytvoreneho MANAGED THREAD.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod2",L"Timmy Anderson",&RetValue))==TRUE)
		{
			throw(GetStringFromHR(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

		wprintf_s(L"Press any key to STOP CLR !\n");
		// !!!!! Kedze ENTRY POINT FUNCTION vytvori novy MANAGED THREAD a skonci OKAMZITE, tak je volanie FUNCTION _getch() umoznuje zastavenie CLR a tym aj vytvoreneho MANAGED THREAD.
		_getch();

		// Zastavim CLR HOST, pricom sa vypnut VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop())==TRUE)
		{
			throw(GetStringFromHR(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	if (RuntimeHost!=NULL)
	{
		RuntimeHost->Release();
		RuntimeHost=NULL;
	}

	if (RuntimeInfo!=NULL)
	{
		RuntimeInfo->Release();
		RuntimeInfo=NULL;
	}

	if (MetaHost!=NULL)
	{
		MetaHost->Release();
		MetaHost=NULL;
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	//Test1();
	Test2();

	ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------