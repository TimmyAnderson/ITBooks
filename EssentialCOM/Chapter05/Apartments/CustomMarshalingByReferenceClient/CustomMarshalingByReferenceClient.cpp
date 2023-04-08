//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\CustomMarshalingByReferenceServer\CustomMarshalingByReferenceServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
const int														NUMBER_OF_ITERATIONS=10000;
//------------------------------------------------------------------------------------------------------
struct SMarshalingThreadParams
{
	HANDLE														MThreadExitHandle;
	HGLOBAL														MByteStream;
};
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
unsigned int __stdcall CustomMarshalingThread(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SInterMarshalingThreadParams*								TypedParam=(SInterMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<ICustomMarshalingByReferenceTest>			Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, STA - WORKER THREAD, STA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(ICustomMarshalingByReferenceTest),(void**) &Interface)))
		{
			wprintf_s(L"THREAD - POINTER [%p] !\n",Interface.GetInterface());

			for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
			{
				if (FAILED(HR=Interface->IncrementValue()))
				{
					wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
					break;
				}
			}

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
void TestCustomMarshaling(void)
{
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v STA (COM OBJECT je STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<ICustomMarshalingByReferenceTest>		Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_CustomMarshalingByReferenceObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(ICustomMarshalingByReferenceTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SInterMarshalingThreadParams						ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));
			ZeroMemory(ThreadParams,sizeof(ThreadParams));

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(ICustomMarshalingByReferenceTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
				{
					ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,CustomMarshalingThread,&ThreadParams[Index],0,NULL);
				}
				else
				{
					wprintf_s(L"Can't MARSHAL INTERFACE !\n");
				}
			}

			// !!! MESSAGE PUMP.
			while(true)
			{
				if (MsgWaitForMultipleObjects(NUMBER_OF_THREADS,ThreadExitHandles,FALSE,INFINITE,QS_ALLINPUT)==(WAIT_OBJECT_0+NUMBER_OF_THREADS))
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

				for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
				{
					if (ThreadHandles[Index]!=NULL)
					{
						if (WaitForSingleObject(ThreadHandles[Index],0)==WAIT_TIMEOUT)
						{
							Exit=false;
							break;
						}
					}
				}

				if (Exit==true)
				{
					break;
				}
			}

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				if (ThreadHandles[Index]!=NULL)
				{
					CloseHandle(ThreadHandles[Index]);
				}

				if (ThreadExitHandles[Index]!=NULL)
				{
					CloseHandle(ThreadExitHandles[Index]);
				}
			}

			long												Value=0;

			Interface->GetValue(&Value);

			wprintf_s(L"!!!!! CLIENT VALUE: [%d] !\n",Value);

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

	TestCustomMarshaling();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------