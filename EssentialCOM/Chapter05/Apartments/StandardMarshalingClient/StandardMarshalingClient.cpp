//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\StandardMarshalingServer\StandardMarshalingServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
struct SThreadParams
{
	HANDLE														MThreadExitHandle;
	IStandardMarshalingTest*									MCOMPointer;
};
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall TestThreadApartmentThread(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SThreadParams*												TypedParam=(SThreadParams*) Param;

	{
		CSmartCOMPointer<IStandardMarshalingTest>				Interface=(IStandardMarshalingTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<1000;Index++)
		{
			// !!!!! Hodi CHYBU MARSHALINGU, kedze sa pokusam o volanie METHOD APARTMENT COM OBJECT z INEHO THREADU pre ktory bol vytvoreny a to BEZ POUZITIA INTER PROCESS MARSHALINGU.
			if (FAILED(HR=Interface->IncrementValue()))
			{
				wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall TestThreadFreeThread(void* Param)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	HRESULT														HR;
	SThreadParams*												TypedParam=(SThreadParams*) Param;

	{
		CSmartCOMPointer<IStandardMarshalingTest>				Interface=(IStandardMarshalingTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<1000;Index++)
		{
			if (FAILED(HR=Interface->IncrementValue()))
			{
				wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM(void)
{
	// 1. COM OBJECT je MULTI-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IStandardMarshalingTest>				Interface=NULL;

		HRESULT													HR=CoCreateInstance(CLSID_StandardMarshalingObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IStandardMarshalingTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,FALSE,FALSE,NULL);
				ThreadParams[Index].MCOMPointer=Interface.GetInterface();
				ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,TestThreadFreeThread,&ThreadParams[Index],0,NULL);
			}

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				WaitForSingleObject(ThreadHandles[Index],INFINITE);
			}

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				CloseHandle(ThreadHandles[Index]);
				CloseHandle(ThreadExitHandles[Index]);
			}

			long												Value=0;

			Interface->GetValue(&Value);

			wprintf_s(L"VALUE: [%d] !\n",Value);

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

	TestCOM();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------