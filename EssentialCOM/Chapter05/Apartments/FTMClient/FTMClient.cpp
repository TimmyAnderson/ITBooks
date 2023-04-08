//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\FTMServer\FTMServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
const int														NUMBER_OF_ITERATIONS=10000;
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
		CSmartCOMPointer<IFTMTest>			Interface=NULL;

		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IFTMTest),(void**) &Interface)))
		{
			// !!!!! Kedze sa pouziva FTM, tak POINTER bude VZDY TEN ISTY.
			wprintf_s(L"THREAD - POINTER [%p] !\n",Interface.GetInterface());

			for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
			{
				if (FAILED(HR=Interface->IncrementValue()))
				{
					wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
					break;
				}

				// !!!!! Toto volanie bude fungovat IBA ak IObjectUsedByFTMTest bude ulozeny do GIT.
	
				// !!!!! Ak sa GIT (alebo iny MARSHALLING mechanizmus) NEPOUZIJE, tak volanie vrati hodnotu RPC_E_WRONG_THREAD. To preto, lebo COM OBJECT je IObjectUsedByFTMTest, avsak COM OBJECT IFTMTest, ktory ho obaluje bol vytvoreny v MTA. Na IObjectUsedByFTMTest bol teda vytvoreny PROXY OBJECT a ten DETEKUJE, ze IncrementValueToRemoteObject() je volana z NESPRAVNEHO APARTMENTU.
				if (FAILED(HR=Interface->IncrementValueToRemoteObject()))
				{
					wprintf_s(L"FUNCTION IncrementValueToRemoteObject() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
					break;
				}
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create STREAM from HGLOBAL HR: [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IFTMTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_FTMObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IFTMTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IFTMTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
				{
					ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,TestThread,&ThreadParams[Index],0,NULL);
				}
				else
				{
					wprintf_s(L"Can't MARSHAL INTERFACE !\n");
				}
			}

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				if (ThreadHandles[Index]!=NULL)
				{
					WaitForSingleObject(ThreadHandles[Index],INFINITE);
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

			long												ValueFTM=0;
			long												ValueObjectUsedByFTM=0;

			Interface->GetValue(&ValueFTM);
			Interface->GetValueFromRemoteObject(&ValueObjectUsedByFTM);

			wprintf_s(L"!!!!! CLIENT VALUE [CFTMObject]: [%d] !\n",ValueFTM);
			wprintf_s(L"!!!!! CLIENT VALUE [CObjectUsedByFTMObject]: [%d] !\n",ValueObjectUsedByFTM);

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