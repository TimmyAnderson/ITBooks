//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\UnmanagedCOMServer\UnmanagedCOMServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "UnmanagedCOMServerCallback.h"
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM(void)
{
	CSmartCOMPointer<IUnmanagedCOMServer>						Interface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_UnmanagedCOMObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IUnmanagedCOMServer),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<IUnmanagedCOMServerCallback>			Callback=new CUnmanagedCOMServerCallback();

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