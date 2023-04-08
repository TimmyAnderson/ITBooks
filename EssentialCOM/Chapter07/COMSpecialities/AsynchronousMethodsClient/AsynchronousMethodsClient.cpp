//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\AsynchronousMethodsServer\AsynchronousMethodsServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void Test(void)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IAsynchronousMethodsTest>				SynchronousInterface=NULL;

		// !!! Vytvori sa COM OBJECT a vrati POINTER na SYNCHRONOUS COM INTERFACE.
		HRESULT													HR=CoCreateInstance(CLSID_AsynchronousMethodsObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IAsynchronousMethodsTest),(void**) &SynchronousInterface);

		if (SUCCEEDED(HR))
		{
			CSmartCOMPointer<AsyncIAsynchronousMethodsTest>		AsynchronousInterface=NULL;

			// !!!!! Vrati POINTER na ASYNCHRONOUS COM INTERFACE.
			if (SUCCEEDED(HR=SynchronousInterface->QueryInterface(__uuidof(AsyncIAsynchronousMethodsTest),(void**) &AsynchronousInterface)))
			{
				// Vola sa SYNCHRONNA METHOD.
				if (FAILED(SynchronousInterface->SetValue(bstr_t(L"Timmy Anderson"))))
				{
					wprintf_s(L"METHOD FAILED !\n");
				}

				// Spusti sa ASYNCHRONNA METHOD.
				if (FAILED(AsynchronousInterface->Begin_GetValue()))
				{
					wprintf_s(L"METHOD FAILED !\n");
				}

				bstr_t											Value1;

				// Dokonci sa volanie ASYNCHRONNEJ METHOD.
				if (FAILED(AsynchronousInterface->Finish_GetValue(Value1.GetAddress())))
				{
					wprintf_s(L"METHOD FAILED !\n");
				}

				// Spusti sa ASYNCHRONNA METHOD.
				if (FAILED(AsynchronousInterface->Begin_SetValue(bstr_t(L"Jenny Thompson"))))
				{
					wprintf_s(L"METHOD FAILED !\n");
				}

				// Dokonci sa volanie ASYNCHRONNEJ METHOD.
				if (FAILED(AsynchronousInterface->Finish_SetValue()))
				{
					wprintf_s(L"METHOD FAILED !\n");
				}

				bstr_t											Value2;

				// Vola sa SYNCHRONNA METHOD.
				if (FAILED(SynchronousInterface->GetValue(Value2.GetAddress())))
				{
					wprintf_s(L"METHOD FAILED !\n");
				}

				wprintf_s(L"!!!!! Value1: [%s] !\n",Value1.operator const wchar_t *());
				wprintf_s(L"!!!!! Value2: [%s] !\n",Value2.operator const wchar_t *());

				AsynchronousInterface=NULL;
			}
			else
			{
				wprintf_s(L"Can't get ASYNCHRONOUS COM INTERFACE !\n");
			}

			SynchronousInterface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	Test();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------