//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <metahost.h>
#include <mscoree.h>
#include <string>
#include "Helpers\Helpers.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "MyHostControl.h"
//-------------------------------------------------------------------------------------------------------
// !!! Prida [mscoree.lib] do PROJECTU.
#pragma comment(lib, "mscoree.lib")
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		DWORD													RetValue=0;

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod1",L"Timmy Anderson",&RetValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

		// Zastavim CLR HOST, pricom sa vypnu VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;

	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		DWORD													RetValue=0;

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod2",L"Timmy Anderson",&RetValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

		wprintf_s(L"Press any key to STOP CLR !\n");
		_getch();

		// Zastavim CLR HOST, pricom sa vypnu VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	// !!! Vytvorim instanciu CUSOM IMPLEMENTACIE IHostControl.
	CSmartCOMPointer<IHostControl>								HostControl=new CMyHostControl();
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		// !!! Zaregistrujem CUSOM IMPLEMENTACIU IHostControl.
		if (FAILED(HR=RuntimeHost->SetHostControl(HostControl.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"SetHostControl() FAILED.",HR));
		}

		DWORD													RetValue=0;

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod1",L"Timmy Anderson",&RetValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

		// Zastavim CLR HOST, pricom sa vypnu VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	HostControl=NULL;
	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		wprintf_s(L"!!! NATIVE - METHOD STARTING !\n");

		DWORD													ReturnValue;

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod3",L"",&ReturnValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"!!! NATIVE - METHOD FINISHED !\n");

		// Zastavim CLR HOST, pricom sa vypnu VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		DWORD													ReturnValue;

		wprintf_s(L"!!! NATIVE - METHOD STARTING !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod3",L"",&ReturnValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"!!! NATIVE - METHOD FINISHED !\n");

		// !!! .NET METHOD sa vola 2 KRAT.

		wprintf_s(L"!!! NATIVE - METHOD STARTING !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MyMethod3",L"",&ReturnValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"!!! NATIVE - METHOD FINISHED !\n");

		// Zastavim CLR HOST, pricom sa vypnu VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		DWORD													ReturnValue;

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"StartThread",L"",&ReturnValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		Sleep(3000);

		wprintf_s(L"!!! NATIVE - NOW CLR THREAD will be STOPPED !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"StopThread",L"",&ReturnValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		// Zastavim CLR HOST, pricom sa vypnu VSETKY CLR THREADS, ktore bezia.
		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop() CALLED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	CSmartCOMPointer<ICLRControl>								CLRControl=NULL;
	CSmartCOMPointer<ICLRDebugManager>							CLRDebugManager=NULL;
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		// !!! Zavediem INTERFACE typu ICLRRuntimeInfo. Prvy parameter MUSI OBSAHOVAT PRESNY NAZOV CLR (zhodny nazov s nazvom adresaru v ktorom je umiestnena prislusna verzia CLR).
		if (FAILED(HR=MetaHost->GetRuntime(L"v4.0.30319",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}

		wprintf_s(L"RUNTIME OBJECT CREATED !\n");

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		// Ziskam ICLRControl.
		if (FAILED(HR=RuntimeHost->GetCLRControl(&CLRControl)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRControl() FAILED.",HR));
		}

		wprintf_s(L"CLR CONTROL RETRIEVED !\n");

		// !!! Pomocou ICLRControl ziskam CLR MANAGER.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLRDebugManager),(void**) &CLRDebugManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		wprintf_s(L"CLR DEBUG MANAGER RETRIEVED !\n");

		BOOL													IsDebuggerAttached=FALSE;

		if (FAILED(HR=CLRDebugManager->IsDebuggerAttached(&IsDebuggerAttached)))
		{
			throw(CHelpers::PrepareLogMessage(L"IsDebuggerAttached() FAILED.",HR));
		}
		
		wprintf_s(L"!!! IsDebuggerAttached [%d] !\n",IsDebuggerAttached);
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	CLRDebugManager=NULL;
	CLRControl=NULL;
	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();

	CHelpers::ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------