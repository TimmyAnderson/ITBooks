//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//-------------------------------------------------------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include <metahost.h>
#include <mscoree.h>
#include <CorError.h>
#include <string>
#include "Helpers\Helpers.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "MyHostControl.h"
#include "CLREventHandler.h"
//-------------------------------------------------------------------------------------------------------
// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
//-------------------------------------------------------------------------------------------------------
// !!! Prida [mscoree.lib] do PROJECTU.
#pragma comment(lib, "mscoree.lib")
//-------------------------------------------------------------------------------------------------------
using namespace std;
//-------------------------------------------------------------------------------------------------------
// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
void StandardTest(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	CSmartCOMPointer<ICLRControl>								CLRControl=NULL;
	CSmartCOMPointer<ICLRPolicyManager>							CLRPolicyManager=NULL;
	CMyHostControl*												MyHostControl=new CMyHostControl();
	CCLREventHandler*											CLREventHandler=new CCLREventHandler();
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IHostControl.
	CSmartCOMPointer<IHostControl>								HostControl=MyHostControl;
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IActionOnCLREvent.
	CSmartCOMPointer<IActionOnCLREvent>							ActionOnCLREvent=CLREventHandler;
	CSmartCOMPointer<ICLROnEventManager>						CLROnEventManager=NULL;
	
	try
	{
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

		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		if (FAILED(HR=RuntimeHost->GetCLRControl(&CLRControl)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRControl() FAILED.",HR));
		}

		wprintf_s(L"CLR CONTROL RETRIEVED !\n");

		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLRPolicyManager),(void**) &CLRPolicyManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!! Zaregistrujem CUSTOM IMPLEMENTACIU IHostControl.
		if (FAILED(HR=RuntimeHost->SetHostControl(HostControl.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"SetHostControl() FAILED.",HR));
		}

		// !!!!! Nastavi nazov CLASS implementujucej CUSTOM APP DOMAIN MANAGER, ktory sa pouzije na vytvaranie APP DOMAINS.
		if (FAILED(HR=CLRControl->SetAppDomainManagerType(L"MyDomainManager, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null",L"MyDomainManager.CMyDomainAppManager")))
		{
			throw(CHelpers::PrepareLogMessage(L"SetAppDomainManagerType() FAILED.",HR));
		}

		// !!!!! Volanie Start() sposobuje, ze sa OKAMZITE vytvara DEFAULT APP DOMAIN pomocou zaregistrovaneho CUSTOM APP DOMAIN MANAGER.
		// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"CLR STARTED !\n");

		const map<DWORD,IMyDomainAppManager*>&					AppDomainManagerMap=MyHostControl->GetAppDomainManagerMap();

		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			// !!!!! Z UNMANAGED CODE zavolam MANAGED CODE.
			(*Iterator).second->PrintAppCurrentDomainName();
		}

		// !!! Ziskam POINTER na DEFAULT APP DOMAIN.
		IMyDomainAppManager*									DefaultAppDomain=MyHostControl->GetDefaultAppDomainManager();

		// !!! Vytvorim 2 APP DOMAINS.
		DefaultAppDomain->CreateNewDomain(bstr_t(L"My DOMAIN 1"));
		DefaultAppDomain->CreateNewDomain(bstr_t(L"My DOMAIN 2"));

		// !!! Ziskam instanciu ICLROnEventManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLROnEventManager),(void**) &CLROnEventManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!! Zaregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->RegisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"RegisterActionOnEvent() FAILED.",HR));
		}
		
		// !!! Vykonam UNLOAD APP DOMAIN, pricom PRESKOCIM DEFAULT APP DOMAIN.
		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=++AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			DWORD												AppDomainID=(*Iterator).first;

			if (SUCCEEDED(HR=RuntimeHost->UnloadAppDomain(AppDomainID,TRUE)))
			{
				wprintf_s(L"APP DOMAIN [%d] was SUCCESSFULLY UNLOADED !\n",AppDomainID);
			}
			else
			{
				wprintf_s(L"APP DOMAIN [%d] FAILED to UNLOAD !\n",AppDomainID);
			}
		}

		// !!! Odregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->UnregisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"UnregisterActionOnEvent() FAILED.",HR));
		}

		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"CLR STOPPED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	// !!!!! Ak Start() ZLYHA, tak z neznameho dovodu HOSTING API NEZAVOLA Release() na HostControl (aj ked pri volani SetHostControl() zavolal AddRef()) a tym padom sa instancia VARIABLE HostControl NEUVOLNI z PAMATE.

	CLRControl=NULL;
	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
void FailureTest(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	CSmartCOMPointer<ICLRControl>								CLRControl=NULL;
	CSmartCOMPointer<ICLRPolicyManager>							CLRPolicyManager=NULL;
	CMyHostControl*												MyHostControl=new CMyHostControl();
	CCLREventHandler*											CLREventHandler=new CCLREventHandler();
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IHostControl.
	CSmartCOMPointer<IHostControl>								HostControl=MyHostControl;
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IActionOnCLREvent.
	CSmartCOMPointer<IActionOnCLREvent>							ActionOnCLREvent=CLREventHandler;
	CSmartCOMPointer<ICLROnEventManager>						CLROnEventManager=NULL;
	
	try
	{
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

		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		if (FAILED(HR=RuntimeHost->GetCLRControl(&CLRControl)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRControl() FAILED.",HR));
		}

		wprintf_s(L"CLR CONTROL RETRIEVED !\n");

		// !!!!! Ziskam instanciu ICLRPolicyManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLRPolicyManager),(void**) &CLRPolicyManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!!!! Nastavim FAILURE POLICY pre ORPHANED LOCK, aby ak k nemu dojde doslo k EXIT PROCESS.
		// !!!!! PROCESS sa NAOZAJ UKONCI, kedze k ORPHANED LOCK UMYSELNE DOJDE.
		if (FAILED(HR=CLRPolicyManager->SetActionOnFailure(EClrFailure::FAIL_OrphanedLock,EPolicyAction::eExitProcess)))
		{
			throw(CHelpers::PrepareLogMessage(L"SetActionOnFailure() FAILED.",HR));
		}

		// !!! Zaregistrujem CUSTOM IMPLEMENTACIU IHostControl.
		if (FAILED(HR=RuntimeHost->SetHostControl(HostControl.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"SetHostControl() FAILED.",HR));
		}

		// !!!!! Nastavi nazov CLASS implementujucej CUSTOM APP DOMAIN MANAGER, ktory sa pouzije na vytvaranie APP DOMAINS.
		if (FAILED(HR=CLRControl->SetAppDomainManagerType(L"MyDomainManager, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null",L"MyDomainManager.CMyDomainAppManager")))
		{
			throw(CHelpers::PrepareLogMessage(L"SetAppDomainManagerType() FAILED.",HR));
		}

		// !!!!! Volanie Start() sposobuje, ze sa OKAMZITE vytvara DEFAULT APP DOMAIN pomocou zaregistrovaneho CUSTOM APP DOMAIN MANAGER.
		// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"CLR STARTED !\n");

		const map<DWORD,IMyDomainAppManager*>&					AppDomainManagerMap=MyHostControl->GetAppDomainManagerMap();

		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			// !!!!! Z UNMANAGED CODE zavolam MANAGED CODE.
			(*Iterator).second->PrintAppCurrentDomainName();
		}

		// !!! Ziskam POINTER na DEFAULT APP DOMAIN.
		IMyDomainAppManager*									DefaultAppDomain=MyHostControl->GetDefaultAppDomainManager();

		// !!! Vytvorim 2 APP DOMAINS.
		DefaultAppDomain->CreateNewDomainAndGenerateOrphanedLock(bstr_t(L"My DOMAIN 1"));
		DefaultAppDomain->CreateNewDomainAndGenerateOrphanedLock(bstr_t(L"My DOMAIN 2"));

		// !!! Ziskam instanciu ICLROnEventManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLROnEventManager),(void**) &CLROnEventManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!! Zaregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->RegisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"RegisterActionOnEvent() FAILED.",HR));
		}
		
		// !!! Vykonam UNLOAD APP DOMAIN, pricom PRESKOCIM DEFAULT APP DOMAIN.
		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=++AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			DWORD												AppDomainID=(*Iterator).first;

			if (SUCCEEDED(HR=RuntimeHost->UnloadAppDomain(AppDomainID,TRUE)))
			{
				wprintf_s(L"APP DOMAIN [%d] was SUCCESSFULLY UNLOADED !\n",AppDomainID);
			}
			else
			{
				wprintf_s(L"APP DOMAIN [%d] FAILED to UNLOAD !\n",AppDomainID);
			}
		}

		// !!! Odregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->UnregisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"UnregisterActionOnEvent() FAILED.",HR));
		}

		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"CLR STOPPED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	// !!!!! Ak Start() ZLYHA, tak z neznameho dovodu HOSTING API NEZAVOLA Release() na HostControl (aj ked pri volani SetHostControl() zavolal AddRef()) a tym padom sa instancia VARIABLE HostControl NEUVOLNI z PAMATE.

	CLRControl=NULL;
	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
void TimeoutTest(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	CSmartCOMPointer<ICLRControl>								CLRControl=NULL;
	CSmartCOMPointer<ICLRPolicyManager>							CLRPolicyManager=NULL;
	CMyHostControl*												MyHostControl=new CMyHostControl();
	CCLREventHandler*											CLREventHandler=new CCLREventHandler();
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IHostControl.
	CSmartCOMPointer<IHostControl>								HostControl=MyHostControl;
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IActionOnCLREvent.
	CSmartCOMPointer<IActionOnCLREvent>							ActionOnCLREvent=CLREventHandler;
	CSmartCOMPointer<ICLROnEventManager>						CLROnEventManager=NULL;
	
	try
	{
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

		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		if (FAILED(HR=RuntimeHost->GetCLRControl(&CLRControl)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRControl() FAILED.",HR));
		}

		wprintf_s(L"CLR CONTROL RETRIEVED !\n");

		// !!!!! Ziskam instanciu ICLRPolicyManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLRPolicyManager),(void**) &CLRPolicyManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!!!! Nastavim TIMEOUT pre THREAD ABORT na 3 sekundy a ACTION RUDE EXIT PROCESS.
		// !!!!! PROCESS sa NAOZAJ po 3 sekundach UKONCI, pretoze som SIMULOVAT 30 SEKUNDOVY THREAD ABORT.
		if (FAILED(HR=CLRPolicyManager->SetTimeoutAndAction(EClrOperation::OPR_ThreadAbort,3000,EPolicyAction::eExitProcess)))
		{
			throw(CHelpers::PrepareLogMessage(L"SetTimeoutAndAction() FAILED.",HR));
		}

		// !!! Zaregistrujem CUSTOM IMPLEMENTACIU IHostControl.
		if (FAILED(HR=RuntimeHost->SetHostControl(HostControl.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"SetHostControl() FAILED.",HR));
		}

		// !!!!! Nastavi nazov CLASS implementujucej CUSTOM APP DOMAIN MANAGER, ktory sa pouzije na vytvaranie APP DOMAINS.
		if (FAILED(HR=CLRControl->SetAppDomainManagerType(L"MyDomainManager, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null",L"MyDomainManager.CMyDomainAppManager")))
		{
			throw(CHelpers::PrepareLogMessage(L"SetAppDomainManagerType() FAILED.",HR));
		}

		// !!!!! Volanie Start() sposobuje, ze sa OKAMZITE vytvara DEFAULT APP DOMAIN pomocou zaregistrovaneho CUSTOM APP DOMAIN MANAGER.
		// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"CLR STARTED !\n");

		const map<DWORD,IMyDomainAppManager*>&					AppDomainManagerMap=MyHostControl->GetAppDomainManagerMap();

		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			// !!!!! Z UNMANAGED CODE zavolam MANAGED CODE.
			(*Iterator).second->PrintAppCurrentDomainName();
		}

		// !!! Ziskam POINTER na DEFAULT APP DOMAIN.
		IMyDomainAppManager*									DefaultAppDomain=MyHostControl->GetDefaultAppDomainManager();

		// !!! Vytvorim 2 APP DOMAINS.
		DefaultAppDomain->CreateNewDomainAndGenerateSlowThreadAbort(bstr_t(L"My DOMAIN 1"));
		DefaultAppDomain->CreateNewDomainAndGenerateSlowThreadAbort(bstr_t(L"My DOMAIN 2"));

		// !!! Ziskam instanciu ICLROnEventManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLROnEventManager),(void**) &CLROnEventManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!! Zaregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->RegisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"RegisterActionOnEvent() FAILED.",HR));
		}
		
		// !!! Vykonam UNLOAD APP DOMAIN, pricom PRESKOCIM DEFAULT APP DOMAIN.
		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=++AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			DWORD												AppDomainID=(*Iterator).first;

			if (SUCCEEDED(HR=RuntimeHost->UnloadAppDomain(AppDomainID,TRUE)))
			{
				wprintf_s(L"APP DOMAIN [%d] was SUCCESSFULLY UNLOADED !\n",AppDomainID);
			}
			else
			{
				wprintf_s(L"APP DOMAIN [%d] FAILED to UNLOAD !\n",AppDomainID);
			}
		}

		// !!! Odregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->UnregisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"UnregisterActionOnEvent() FAILED.",HR));
		}

		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"CLR STOPPED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	// !!!!! Ak Start() ZLYHA, tak z neznameho dovodu HOSTING API NEZAVOLA Release() na HostControl (aj ked pri volani SetHostControl() zavolal AddRef()) a tym padom sa instancia VARIABLE HostControl NEUVOLNI z PAMATE.

	CLRControl=NULL;
	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
void DefaultActionTest(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	CSmartCOMPointer<ICLRControl>								CLRControl=NULL;
	CSmartCOMPointer<ICLRPolicyManager>							CLRPolicyManager=NULL;
	CMyHostControl*												MyHostControl=new CMyHostControl();
	CCLREventHandler*											CLREventHandler=new CCLREventHandler();
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IHostControl.
	CSmartCOMPointer<IHostControl>								HostControl=MyHostControl;
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IActionOnCLREvent.
	CSmartCOMPointer<IActionOnCLREvent>							ActionOnCLREvent=CLREventHandler;
	CSmartCOMPointer<ICLROnEventManager>						CLROnEventManager=NULL;
	
	try
	{
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

		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		if (FAILED(HR=RuntimeHost->GetCLRControl(&CLRControl)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRControl() FAILED.",HR));
		}

		wprintf_s(L"CLR CONTROL RETRIEVED !\n");

		// !!!!! Ziskam instanciu ICLRPolicyManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLRPolicyManager),(void**) &CLRPolicyManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!!!! Nastavim DEFAULT ACTION, aby pri pokuse o THREAD ABORT doslo k EXIT PROCESS.
		if (FAILED(HR=CLRPolicyManager->SetDefaultAction(EClrOperation::OPR_ThreadAbort,EPolicyAction::eExitProcess)))
		{
			throw(CHelpers::PrepareLogMessage(L"SetDefaultAction() FAILED.",HR));
		}

		// !!! Zaregistrujem CUSTOM IMPLEMENTACIU IHostControl.
		if (FAILED(HR=RuntimeHost->SetHostControl(HostControl.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"SetHostControl() FAILED.",HR));
		}

		// !!!!! Nastavi nazov CLASS implementujucej CUSTOM APP DOMAIN MANAGER, ktory sa pouzije na vytvaranie APP DOMAINS.
		if (FAILED(HR=CLRControl->SetAppDomainManagerType(L"MyDomainManager, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null",L"MyDomainManager.CMyDomainAppManager")))
		{
			throw(CHelpers::PrepareLogMessage(L"SetAppDomainManagerType() FAILED.",HR));
		}

		// !!!!! Volanie Start() sposobuje, ze sa OKAMZITE vytvara DEFAULT APP DOMAIN pomocou zaregistrovaneho CUSTOM APP DOMAIN MANAGER.
		// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"CLR STARTED !\n");

		const map<DWORD,IMyDomainAppManager*>&					AppDomainManagerMap=MyHostControl->GetAppDomainManagerMap();

		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			// !!!!! Z UNMANAGED CODE zavolam MANAGED CODE.
			(*Iterator).second->PrintAppCurrentDomainName();
		}

		// !!! Ziskam POINTER na DEFAULT APP DOMAIN.
		IMyDomainAppManager*									DefaultAppDomain=MyHostControl->GetDefaultAppDomainManager();

		// !!! Vytvorim 2 APP DOMAINS.
		DefaultAppDomain->CreateNewDomainAndGenerateSlowThreadAbort(bstr_t(L"My DOMAIN 1"));
		DefaultAppDomain->CreateNewDomainAndGenerateSlowThreadAbort(bstr_t(L"My DOMAIN 2"));

		// !!! Ziskam instanciu ICLROnEventManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLROnEventManager),(void**) &CLROnEventManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!! Zaregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->RegisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"RegisterActionOnEvent() FAILED.",HR));
		}
		
		// !!! Vykonam UNLOAD APP DOMAIN, pricom PRESKOCIM DEFAULT APP DOMAIN.
		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=++AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			DWORD												AppDomainID=(*Iterator).first;

			if (SUCCEEDED(HR=RuntimeHost->UnloadAppDomain(AppDomainID,TRUE)))
			{
				wprintf_s(L"APP DOMAIN [%d] was SUCCESSFULLY UNLOADED !\n",AppDomainID);
			}
			else
			{
				wprintf_s(L"APP DOMAIN [%d] FAILED to UNLOAD !\n",AppDomainID);
			}
		}

		// !!! Odregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->UnregisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"UnregisterActionOnEvent() FAILED.",HR));
		}

		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"CLR STOPPED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	// !!!!! Ak Start() ZLYHA, tak z neznameho dovodu HOSTING API NEZAVOLA Release() na HostControl (aj ked pri volani SetHostControl() zavolal AddRef()) a tym padom sa instancia VARIABLE HostControl NEUVOLNI z PAMATE.

	CLRControl=NULL;
	RuntimeHost=NULL;
	RuntimeInfo=NULL;
	MetaHost=NULL;
}
//-------------------------------------------------------------------------------------------------------
// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
void UnhandledExceptionTest(void)
{
	HRESULT														HR;
	CSmartCOMPointer<ICLRMetaHost>								MetaHost=NULL;
	CSmartCOMPointer<ICLRRuntimeInfo>							RuntimeInfo=NULL;
	CSmartCOMPointer<ICLRRuntimeHost>							RuntimeHost=NULL;
	CSmartCOMPointer<ICLRControl>								CLRControl=NULL;
	CSmartCOMPointer<ICLRPolicyManager>							CLRPolicyManager=NULL;
	CMyHostControl*												MyHostControl=new CMyHostControl();
	CCLREventHandler*											CLREventHandler=new CCLREventHandler();
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IHostControl.
	CSmartCOMPointer<IHostControl>								HostControl=MyHostControl;
	// !!! Vytvorim instanciu CUSTOM IMPLEMENTACIE IActionOnCLREvent.
	CSmartCOMPointer<IActionOnCLREvent>							ActionOnCLREvent=CLREventHandler;
	CSmartCOMPointer<ICLROnEventManager>						CLROnEventManager=NULL;
	
	try
	{
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

		if (FAILED(HR=RuntimeInfo->GetInterface(CLSID_CLRRuntimeHost,IID_ICLRRuntimeHost,(LPVOID*) &RuntimeHost)))
		{
			throw(CHelpers::PrepareLogMessage(L"Can't create RUNTIME HOST.",HR));
		}
		
		wprintf_s(L"RUNTIME HOST CREATED !\n");

		if (FAILED(HR=RuntimeHost->GetCLRControl(&CLRControl)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRControl() FAILED.",HR));
		}

		wprintf_s(L"CLR CONTROL RETRIEVED !\n");

		// !!!!! Ziskam instanciu ICLRPolicyManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLRPolicyManager),(void**) &CLRPolicyManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!!!! Nastavim UNHANDLED EXCEPTION BEHAVIOR, aby NEDOSLO k EXIT PROCESSU.
		// !!!!! PROCESS NAOZAJ NEBUDE EXITED, aj ked doslo k UNHANDLED EXCEPTION vo WORKER THREAD.
		if (FAILED(HR=CLRPolicyManager->SetUnhandledExceptionPolicy(EClrUnhandledException::eHostDeterminedPolicy)))
		{
			throw(CHelpers::PrepareLogMessage(L"SetUnhandledExceptionPolicy() FAILED.",HR));
		}

		// !!! Zaregistrujem CUSTOM IMPLEMENTACIU IHostControl.
		if (FAILED(HR=RuntimeHost->SetHostControl(HostControl.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"SetHostControl() FAILED.",HR));
		}

		// !!!!! Nastavi nazov CLASS implementujucej CUSTOM APP DOMAIN MANAGER, ktory sa pouzije na vytvaranie APP DOMAINS.
		if (FAILED(HR=CLRControl->SetAppDomainManagerType(L"MyDomainManager, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null",L"MyDomainManager.CMyDomainAppManager")))
		{
			throw(CHelpers::PrepareLogMessage(L"SetAppDomainManagerType() FAILED.",HR));
		}

		// !!!!! Volanie Start() sposobuje, ze sa OKAMZITE vytvara DEFAULT APP DOMAIN pomocou zaregistrovaneho CUSTOM APP DOMAIN MANAGER.
		// !!!!! LIBRARY MyDomainManager.dll MUSI byt NAKOPIROVANA do TOHO ISTEHO DIRECTORY ako .EXE FILE.
		if (FAILED(HR=RuntimeHost->Start()))
		{
			throw(CHelpers::PrepareLogMessage(L"Start() FAILED.",HR));
		}

		wprintf_s(L"CLR STARTED !\n");

		const map<DWORD,IMyDomainAppManager*>&					AppDomainManagerMap=MyHostControl->GetAppDomainManagerMap();

		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			// !!!!! Z UNMANAGED CODE zavolam MANAGED CODE.
			(*Iterator).second->PrintAppCurrentDomainName();
		}

		// !!! Ziskam POINTER na DEFAULT APP DOMAIN.
		IMyDomainAppManager*									DefaultAppDomain=MyHostControl->GetDefaultAppDomainManager();

		// !!! Vytvorim 2 APP DOMAINS.
		DefaultAppDomain->CreateNewDomainAndGenerateUnhandledException(bstr_t(L"My DOMAIN 1"));
		DefaultAppDomain->CreateNewDomainAndGenerateUnhandledException(bstr_t(L"My DOMAIN 2"));

		// !!! Ziskam instanciu ICLROnEventManager.
		if (FAILED(HR=CLRControl->GetCLRManager(__uuidof(ICLROnEventManager),(void**) &CLROnEventManager)))
		{
			throw(CHelpers::PrepareLogMessage(L"GetCLRManager() FAILED.",HR));
		}

		// !!! Zaregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->RegisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"RegisterActionOnEvent() FAILED.",HR));
		}
		
		// !!! Vykonam UNLOAD APP DOMAIN, pricom PRESKOCIM DEFAULT APP DOMAIN.
		for (map<DWORD,IMyDomainAppManager*>::const_iterator Iterator=++AppDomainManagerMap.begin();Iterator!=AppDomainManagerMap.end();Iterator++)
		{
			DWORD												AppDomainID=(*Iterator).first;

			if (SUCCEEDED(HR=RuntimeHost->UnloadAppDomain(AppDomainID,TRUE)))
			{
				wprintf_s(L"APP DOMAIN [%d] was SUCCESSFULLY UNLOADED !\n",AppDomainID);
			}
			else
			{
				wprintf_s(L"APP DOMAIN [%d] FAILED to UNLOAD !\n",AppDomainID);
			}
		}

		// !!! Odregistrujem zaregistrovany EVENT HANDLER typu IActionOnCLREvent.
		if (FAILED(HR=CLROnEventManager->UnregisterActionOnEvent(Event_DomainUnload,ActionOnCLREvent.GetInterface())))
		{
			throw(CHelpers::PrepareLogMessage(L"UnregisterActionOnEvent() FAILED.",HR));
		}

		if (FAILED(HR=RuntimeHost->Stop()))
		{
			throw(CHelpers::PrepareLogMessage(L"Stop() FAILED.",HR));
		}

		wprintf_s(L"CLR STOPPED !\n");
	}
	catch(wstring Error)
	{
		wprintf_s(L"EXCEPTION: [%s] !\n",Error.c_str());
	}

	// !!!!! Ak Start() ZLYHA, tak z neznameho dovodu HOSTING API NEZAVOLA Release() na HostControl (aj ked pri volani SetHostControl() zavolal AddRef()) a tym padom sa instancia VARIABLE HostControl NEUVOLNI z PAMATE.

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

	//StandardTest();
	//FailureTest();
	//TimeoutTest();
	//DefaultActionTest();
	UnhandledExceptionTest();

	CHelpers::ShowExitLine();

	return(0);
}
//-------------------------------------------------------------------------------------------------------