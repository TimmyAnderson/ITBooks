//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\CallbacksInCOMServer\CallbacksInCOMServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "MyServerCallback.h"
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM(void)
{
	CSmartCOMPointer<IMyServer>									Interface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_CallbacksInCOMObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IMyServer),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<IMyServerCallback>						Callback=new CMyServerCallback();

		Interface->RegisterCallback(Callback.GetInterface());

		Interface->SendMessageToServer(bstr_t("Timmy Anderson !"));
		Interface->SendMessageToServer(bstr_t("Jenny Thompson !"));

		Interface->UnRegisterCallback();

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECTS !\n");
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		TestCOM();
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------