//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\CustomMarshalingByValueServer\CustomMarshalingByValueServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
struct SInterMarshalingThreadParams
{
	HANDLE														MThreadExitHandle;
	// !!!!! IStream aj ked je to COM INTERFACE, tak v pripade, ze je vrateny z RegisterInterfaceInGlobal(), tak je ho mozne prenasat medzi APARTMENTS.
	IStream*													MStream;
};
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall TestThread(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SInterMarshalingThreadParams*								TypedParam=(SInterMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<ICustomMarshalingByValueTest>			Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, STA - WORKER THREAD, STA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(ICustomMarshalingByValueTest),(void**) &Interface)))
		{
			wprintf_s(L"THREAD - POINTER [%p] !\n",Interface.GetInterface());

			long												Value=0;

			Interface->GetValue(&Value);

			wprintf_s(L"!!!!! CLIENT VALUE: [%d] !\n",Value);

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't UNMARSHAL INTERFACE HR: [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void Test(void)
{
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v STA (COM OBJECT je STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<ICustomMarshalingByValueTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_CustomMarshalingByValueObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ICustomMarshalingByValueTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			HANDLE												ThreadExitHandle;
			HANDLE												ThreadHandle;
			SInterMarshalingThreadParams						ThreadParams;

			ZeroMemory(&ThreadExitHandle,sizeof(ThreadExitHandle));
			ZeroMemory(&ThreadHandle,sizeof(ThreadHandle));
			ZeroMemory(&ThreadParams,sizeof(ThreadParams));

			if (FAILED(HR=Interface->SetValue(999)))
			{
				wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			ThreadParams.MThreadExitHandle=ThreadExitHandle=CreateEvent(NULL,TRUE,FALSE,NULL);

			if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(ICustomMarshalingByValueTest),Interface.GetInterface(),&ThreadParams.MStream)))
			{
				ThreadHandle=(HANDLE) _beginthreadex(NULL,0,TestThread,&ThreadParams,0,NULL);
			}
			else
			{
				wprintf_s(L"Can't MARSHAL INTERFACE !\n");
			}

			// !!! MESSAGE PUMP.
			while(true)
			{
				if (MsgWaitForMultipleObjects(1,&ThreadExitHandle,FALSE,INFINITE,QS_ALLINPUT)==(WAIT_OBJECT_0+1))
				{
					// !!!!! EXTREMNE DOLEZITE. Pri signalizacii MsgWaitForMultipleObjects() ze prisla WINDOW MESSAGE je treba pumpovat CELU QUEUE, NIE LEN 1 MESSAGE.
					while(true)
					{
						MSG											Message;

						if (PeekMessage(&Message,NULL,0,0,PM_NOREMOVE)!=FALSE)
						{
							GetMessage(&Message,NULL,0,0);
							DispatchMessage(&Message);
						}
						else
						{
							break;
						}
					}
				}

				bool											Exit=true;

				if (ThreadHandle!=NULL)
				{
					if (WaitForSingleObject(ThreadHandle,0)==WAIT_TIMEOUT)
					{
						Exit=false;
					}
				}

				if (Exit==true)
				{
					break;
				}
			}

			if (ThreadHandle!=NULL)
			{
				CloseHandle(ThreadHandle);
			}

			if (ThreadExitHandle!=NULL)
			{
				CloseHandle(ThreadExitHandle);
			}

			Interface=NULL;
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