//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <metahost.h>
#include <mscoree.h>
#include <string>
#include "Helpers\Helpers.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//-------------------------------------------------------------------------------------------------------
// !!! Prida [mscoree.lib] do PROJECTU.
#pragma comment(lib, "mscoree.lib")
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
void __stdcall CLRLoadedCallback(ICLRRuntimeInfo* RuntimeInfo, CallbackThreadSetFnPtr CallbackThreadSet, CallbackThreadUnsetFnPtr CallbackThreadUnset)
{
	wprintf_s(L"!!!!! CLRLoadedCallback() CALLED !\n");

	HRESULT														HR;

	// !!! Tu je mozne MODIFIKOVAT CLR volanim METHODS ICLRRuntimeInfo.

	// !!! Nastavim GC na SERVER MODE.
	if (FAILED(HR=RuntimeInfo->SetDefaultStartupFlags(STARTUP_SERVER_GC,NULL)))
	{
		throw(CHelpers::PrepareLogMessage(L"SetDefaultStartupFlags() FAILED.",HR));
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
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
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MySimpleMethod",L"Timmy Anderson",&RetValue)))
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

		// !!! Nastavim GC na WORKSTATION MODE - NON-CONCURRENT GC.
		if (FAILED(HR=RuntimeInfo->SetDefaultStartupFlags(0,NULL)))
		{
			throw(CHelpers::PrepareLogMessage(L"SetDefaultStartupFlags() FAILED.",HR));
		}

		DWORD													RetValue=0;

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		// !!! Kedze NEBOL NASTAVENY SERVER GC, tak SERVER GC NIE JE ZAPNUTY.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"PrintGCType",L"",&RetValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

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

		// !!! Nastavim GC na SERVER MODE.
		if (FAILED(HR=RuntimeInfo->SetDefaultStartupFlags(STARTUP_SERVER_GC,NULL)))
		{
			throw(CHelpers::PrepareLogMessage(L"SetDefaultStartupFlags() FAILED.",HR));
		}

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

		// !!! Kedze BOL NASTAVENY SERVER GC, tak SERVER GC bude ZAPNUTY.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"PrintGCType",L"",&RetValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

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

		// !!! Nastavim GC na WORKSTATION MODE - CONCURRENT GC.
		if (FAILED(HR=RuntimeInfo->SetDefaultStartupFlags(STARTUP_CONCURRENT_GC,NULL)))
		{
			throw(CHelpers::PrepareLogMessage(L"SetDefaultStartupFlags() FAILED.",HR));
		}

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

		// !!! Kedze BOL NASTAVENY WORKSTATION GC, tak SERVER GC bude VYPNUTY.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"PrintGCType",L"",&RetValue)))
		{
			throw(CHelpers::PrepareLogMessage(L"ExecuteInDefaultAppDomain() FAILED.",HR));
		}

		wprintf_s(L"ExecuteInDefaultAppDomain() CALLED and returned [%d] !\n",RetValue);

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
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost1=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost2=NULL;
	
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
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost1)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}

		wprintf_s(L"RuntimeHost1->GetInterface() - HR [%s] !\n",CHelpers::PrepareLogMessage(L"STATUS",HR).c_str());

		// Zavediem INTERFACE typu ICLRRuntimeHost.
		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost2)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}

		wprintf_s(L"RuntimeHost2->GetInterface() - HR [%s] !\n",CHelpers::PrepareLogMessage(L"STATUS",HR).c_str());

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost1->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start1() CALLED !\n");
		wprintf_s(L"RuntimeHost1->Start() - HR [%s] !\n",CHelpers::PrepareLogMessage(L"STATUS",HR).c_str());

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost2->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start2() CALLED !\n");
		wprintf_s(L"RuntimeHost2->Start() - HR [%s] !\n",CHelpers::PrepareLogMessage(L"STATUS",HR).c_str());

		if (FAILED(HR=RuntimeHost1->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop1() CALLED !\n");
		wprintf_s(L"RuntimeHost1->Stop() - HR [%s] !\n",CHelpers::PrepareLogMessage(L"STATUS",HR).c_str());

		if (FAILED(HR=RuntimeHost2->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"Stop2() CALLED !\n");
		wprintf_s(L"RuntimeHost2->Stop() - HR [%s] !\n",CHelpers::PrepareLogMessage(L"STATUS",HR).c_str());
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	RuntimeHost1=NULL;
	RuntimeHost2=NULL;
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

		// !!! Umyselne dam NEKOREKTNU VERZIU CLR
		if (FAILED(HR=MetaHost->GetRuntime(L"v7.6.54321",IID_ICLRRuntimeInfo,(LPVOID*) &RuntimeInfo)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME OBJECT.",HR));
		}
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
	
	try
	{
		// Zavediem INTERFACE typu ICLRMetaHost.
		if (FAILED(HR=CLRCreateInstance(CLSID_CLRMetaHost,IID_ICLRMetaHost,(LPVOID*) &MetaHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create HOST COM OBJECT.",HR));
		}

		wprintf_s(L"HOST COM OBJECT CREATED !\n");

		if (FAILED(HR=MetaHost->RequestRuntimeLoadedNotification(CLRLoadedCallback)))
		{
			throw(CHelpers::PrepareLogMessage(L"RequestRuntimeLoadedNotification() FAILED.",HR));
		}

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

		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"PrintGCType",L"",&RetValue)))
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
void Test8(void)
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
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MySimpleMethod",L"Timmy Anderson",&RetValue)))
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

		// !!!!! Pokus o OPATOVNE SPUSTENIE CLR ZLYHA, lebo CLR moze byt v PROCESSE spusteny IBA RAZ.

		// Spustim CLR HOST.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"Start() CALLED !\n");

		// Funkcia ExecuteInDefaultAppDomain() zavedie POZADOVANU DLL a spusi metodu s prototypom: 'int Method(string Argument)'.
		// !!! Funkcia ExecuteInDefaultAppDomain() skonci AZ KED SKONCI 'int Method(string Argument)'.
		if (FAILED(HR=RuntimeHost->ExecuteInDefaultAppDomain(L"..\\..\\..\\!ManagedDLL\\ManagedAssembly.dll",L"ManagedAssembly.CMyClass",L"MySimpleMethod",L"Timmy Anderson",&RetValue)))
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
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();
	Test8();

	CHelpers::ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------