//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\BothThreadingModelServer\BothThreadingModelServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
const int														NUMBER_OF_ITERATIONS=10000;
//------------------------------------------------------------------------------------------------------
struct SThreadParams
{
	HANDLE														MThreadExitHandle;
	IBothThreadingModelTest*									MCOMPointer;
};
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
unsigned int __stdcall ThreadNoMarshalingTestCOM1(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SThreadParams*												TypedParam=(SThreadParams*) Param;

	{
		// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT sa prenasa do INEHO THREADU (INY STA APARTMENT) BEZ VYKONANIA MARSHALINGU.
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=(IBothThreadingModelTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			// !!!!! Kedze ku COM OBJECT pristupujem cez PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU), tak COM NEMA SANCU DETEKOVAT CHYBU PREKROCENIA HRANICE APARTMENT a METHOD sa KOREKTNE ZAVOLA. Avsak volanie uz NEBUDE THREAD-SAFE. Kedze vsak COM OBJECT je THREAD-SAFE, vysledkom je, ze COUNTER bude obsahovat SPRAVNU HODNOTU.
			if (FAILED(HR=Interface->IncrementValue()))
			{
				wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				break;
			}
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadNoMarshalingTestCOM2(void* Param)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	HRESULT														HR;
	SThreadParams*												TypedParam=(SThreadParams*) Param;

	{
		// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT sa prenasa do INEHO THREADU (MTA APARTMENT) BEZ VYKONANIA MARSHALINGU.
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=(IBothThreadingModelTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			// !!!!! Kedze ku COM OBJECT pristupujem cez PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU), tak COM NEMA SANCU DETEKOVAT CHYBU PREKROCENIA HRANICE APARTMENT a METHOD sa KOREKTNE ZAVOLA. Avsak volanie uz NEBUDE THREAD-SAFE. Kedze vsak COM OBJECT je THREAD-SAFE, vysledkom je, ze COUNTER bude obsahovat SPRAVNU HODNOTU.
			if (FAILED(HR=Interface->IncrementValue()))
			{
				wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				break;
			}
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadNoMarshalingTestCOM3(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SThreadParams*												TypedParam=(SThreadParams*) Param;

	{
		// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU) prenasam do THREADU s NEKOPMATIBILNYM APARTMENT (STA).
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=(IBothThreadingModelTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			// !!!!! Kedze ku COM OBJECT pristupujem cez PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU), tak COM NEMA SANCU DETEKOVAT CHYBU PREKROCENIA HRANICE APARTMENT a METHOD sa KOREKTNE ZAVOLA. Avsak volanie uz NEBUDE THREAD-SAFE. Kedze vsak COM OBJECT je THREAD-SAFE, vysledkom je, ze COUNTER bude obsahovat SPRAVNU HODNOTU.
			if (FAILED(HR=Interface->IncrementValue()))
			{
				wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				break;
			}
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadNoMarshalingTestCOM4(void* Param)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	HRESULT														HR;
	SThreadParams*												TypedParam=(SThreadParams*) Param;

	{
		// !!!!! OK. Prenasa sa PRIAMY POINTER na COM OBJECT do INEHO KOMPATIBILNEHO APARTMENT.
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=(IBothThreadingModelTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			// !!!!! Volanie prebehne KOREKTNE.
			if (FAILED(HR=Interface->IncrementValue()))
			{
				wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				break;
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
unsigned int __stdcall ThreadMarshalingTestCOM1(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SMarshalingThreadParams*									TypedParam=(SMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IStream>								Stream;

		if (SUCCEEDED(HR=CreateStreamOnHGlobal(TypedParam->MByteStream,FALSE,&Stream)))
		{
			CSmartCOMPointer<IBothThreadingModelTest>			Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, STA - WORKER THREAD, BOTH (STA) - COM OBJECT), vytvara sa PROXY na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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

			Stream=NULL;
		}
		else
		{
			wprintf_s(L"Can't create STREAM from HGLOBAL HR: [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}

		if (GlobalFree(TypedParam->MByteStream)!=NULL)
		{
			wprintf_s(L"Can't RELEASE HGLOBAL MEMORY !\n");
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadMarshalingTestCOM2(void* Param)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	HRESULT														HR;
	SMarshalingThreadParams*									TypedParam=(SMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IStream>								Stream;

		if (SUCCEEDED(HR=CreateStreamOnHGlobal(TypedParam->MByteStream,FALSE,&Stream)))
		{
			CSmartCOMPointer<IBothThreadingModelTest>			Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, MTA - WORKER THREAD, BOTH (STA) - COM OBJECT), vytvara sa PROXY na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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

			Stream=NULL;
		}
		else
		{
			wprintf_s(L"Can't create STREAM from HGLOBAL HR: [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}

		if (GlobalFree(TypedParam->MByteStream)!=NULL)
		{
			wprintf_s(L"Can't RELEASE HGLOBAL MEMORY !\n");
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadMarshalingTestCOM3(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SMarshalingThreadParams*									TypedParam=(SMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IStream>								Stream;

		if (SUCCEEDED(HR=CreateStreamOnHGlobal(TypedParam->MByteStream,FALSE,&Stream)))
		{
			CSmartCOMPointer<IBothThreadingModelTest>			Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (MTA - MAIN THREAD, STA - WORKER THREAD, BOTH (MTA) - COM OBJECT), vytvara sa PROXY na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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

			Stream=NULL;
		}
		else
		{
			wprintf_s(L"Can't create STREAM from HGLOBAL HR: [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}

		if (GlobalFree(TypedParam->MByteStream)!=NULL)
		{
			wprintf_s(L"Can't RELEASE HGLOBAL MEMORY !\n");
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadMarshalingTestCOM4(void* Param)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	HRESULT														HR;
	SMarshalingThreadParams*									TypedParam=(SMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IStream>								Stream;

		if (SUCCEEDED(HR=CreateStreamOnHGlobal(TypedParam->MByteStream,FALSE,&Stream)))
		{
			CSmartCOMPointer<IBothThreadingModelTest>			Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS SU KOMPATIBILNE (MTA - MAIN THREAD, BOTH (MTA) - WORKER THREAD, MTA - COM OBJECT), ziskava sa PRIAMY POINTER na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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

			Stream=NULL;
		}
		else
		{
			wprintf_s(L"Can't create STREAM from HGLOBAL HR: [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}

		if (GlobalFree(TypedParam->MByteStream)!=NULL)
		{
			wprintf_s(L"Can't RELEASE HGLOBAL MEMORY !\n");
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall InterThreadMarshalingTestCOM1(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SInterMarshalingThreadParams*								TypedParam=(SInterMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, STA - WORKER THREAD, BOTH (STA) - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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
unsigned int __stdcall InterThreadMarshalingTestCOM2(void* Param)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	HRESULT														HR;
	SInterMarshalingThreadParams*								TypedParam=(SInterMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, MTA - WORKER THREAD, BOTH (STA) - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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
unsigned int __stdcall InterThreadMarshalingTestCOM3(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SInterMarshalingThreadParams*								TypedParam=(SInterMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (MTA - MAIN THREAD, STA - WORKER THREAD, BOTH (MTA) - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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
unsigned int __stdcall InterThreadMarshalingTestCOM4(void* Param)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	HRESULT														HR;
	SInterMarshalingThreadParams*								TypedParam=(SInterMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS SU KOMPATIBILNE (MTA - MAIN THREAD, BOTH (MTA) - WORKER THREAD, MTA - COM OBJECT), ziskava sa PRIAMY POINTER na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IBothThreadingModelTest),(void**) &Interface)))
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
void NoMarshalingTestCOM1(void)
{
	// 1. COM OBJECT je BOTH-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT sa prenasa do INEHO THREADU (INY STA APARTMENT) BEZ VYKONANIA MARSHALINGU.
				ThreadParams[Index].MCOMPointer=Interface.GetInterface();
				ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadNoMarshalingTestCOM1,&ThreadParams[Index],0,NULL);
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
void NoMarshalingTestCOM2(void)
{
	// 1. COM OBJECT je BOTH-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT sa prenasa do INEHO THREADU (MTA APARTMENT) BEZ VYKONANIA MARSHALINGU.
				ThreadParams[Index].MCOMPointer=Interface.GetInterface();
				ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadNoMarshalingTestCOM2,&ThreadParams[Index],0,NULL);
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
void NoMarshalingTestCOM3(void)
{
	// 1. COM OBJECT je BOTH-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU) prenasam do THREADU s NEKOPMATIBILNYM APARTMENT (STA).
				ThreadParams[Index].MCOMPointer=Interface.GetInterface();
				ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadNoMarshalingTestCOM3,&ThreadParams[Index],0,NULL);
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
void NoMarshalingTestCOM4(void)
{
	// 1. COM OBJECT je BOTH-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! OK. Prenasa sa PRIAMY POINTER na COM OBJECT do INEHO KOMPATIBILNEHO APARTMENT.
				ThreadParams[Index].MCOMPointer=Interface.GetInterface();
				ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadNoMarshalingTestCOM4,&ThreadParams[Index],0,NULL);
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
void MarshalingTestCOM1(void)
{
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SMarshalingThreadParams								ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));
			ZeroMemory(ThreadParams,sizeof(ThreadParams));

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);

				CSmartCOMPointer<IStream>						Stream;

				if (SUCCEEDED(CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
				{
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
					{
						if (SUCCEEDED(HR=GetHGlobalFromStream(Stream.GetInterface(),&ThreadParams[Index].MByteStream)))
						{
							ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadMarshalingTestCOM1,&ThreadParams[Index],0,NULL);
						}
						else
						{
							wprintf_s(L"Can't get HGLOBAL from STREAM !\n");
						}
					}
					else
					{
						wprintf_s(L"Can't MARSHAL INTERFACE !\n");
					}

					Stream=NULL;
				}
				else
				{
					wprintf_s(L"Can't create STREAM !\n");
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
void MarshalingTestCOM2(void)
{
	// 1. COM OBJECT je MULTI-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SMarshalingThreadParams								ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));
			ZeroMemory(ThreadParams,sizeof(ThreadParams));

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);

				CSmartCOMPointer<IStream>						Stream;

				if (SUCCEEDED(CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
				{
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
					{
						if (SUCCEEDED(HR=GetHGlobalFromStream(Stream.GetInterface(),&ThreadParams[Index].MByteStream)))
						{
							ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadMarshalingTestCOM2,&ThreadParams[Index],0,NULL);
						}
						else
						{
							wprintf_s(L"Can't get HGLOBAL from STREAM !\n");
						}
					}
					else
					{
						wprintf_s(L"Can't MARSHAL INTERFACE !\n");
					}

					Stream=NULL;
				}
				else
				{
					wprintf_s(L"Can't create STREAM !\n");
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
void MarshalingTestCOM3(void)
{
	// 1. COM OBJECT je MULTI-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SMarshalingThreadParams								ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));
			ZeroMemory(ThreadParams,sizeof(ThreadParams));

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);

				CSmartCOMPointer<IStream>						Stream;

				if (SUCCEEDED(CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
				{
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
					{
						if (SUCCEEDED(HR=GetHGlobalFromStream(Stream.GetInterface(),&ThreadParams[Index].MByteStream)))
						{
							ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadMarshalingTestCOM3,&ThreadParams[Index],0,NULL);
						}
						else
						{
							wprintf_s(L"Can't get HGLOBAL from STREAM !\n");
						}
					}
					else
					{
						wprintf_s(L"Can't MARSHAL INTERFACE !\n");
					}

					Stream=NULL;
				}
				else
				{
					wprintf_s(L"Can't create STREAM !\n");
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
void MarshalingTestCOM4(void)
{
	// 1. COM OBJECT je MULTI-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SMarshalingThreadParams								ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));
			ZeroMemory(ThreadParams,sizeof(ThreadParams));

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);

				CSmartCOMPointer<IStream>						Stream;

				if (SUCCEEDED(CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
				{
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IBothThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
					{
						if (SUCCEEDED(HR=GetHGlobalFromStream(Stream.GetInterface(),&ThreadParams[Index].MByteStream)))
						{
							ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadMarshalingTestCOM4,&ThreadParams[Index],0,NULL);
						}
						else
						{
							wprintf_s(L"Can't get HGLOBAL from STREAM !\n");
						}
					}
					else
					{
						wprintf_s(L"Can't MARSHAL INTERFACE !\n");
					}

					Stream=NULL;
				}
				else
				{
					wprintf_s(L"Can't create STREAM !\n");
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
void InterThreadMarshalingTestCOM1(void)
{
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IBothThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
				{
					ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,InterThreadMarshalingTestCOM1,&ThreadParams[Index],0,NULL);
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
void InterThreadMarshalingTestCOM2(void)
{
	// 1. COM OBJECT je MULTI-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IBothThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
				{
					ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,InterThreadMarshalingTestCOM2,&ThreadParams[Index],0,NULL);
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
void InterThreadMarshalingTestCOM3(void)
{
	// 1. COM OBJECT je MULTI-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IBothThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
				{
					ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,InterThreadMarshalingTestCOM3,&ThreadParams[Index],0,NULL);
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
void InterThreadMarshalingTestCOM4(void)
{
	// 1. COM OBJECT je MULTI-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je BOTH a bol vytvoreny v MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IBothThreadingModelTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su VZDY v BOTH APARTMENT KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_BothThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IBothThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IBothThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
				{
					ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,InterThreadMarshalingTestCOM4,&ThreadParams[Index],0,NULL);
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

	//NoMarshalingTestCOM1();
	//NoMarshalingTestCOM2();
	//NoMarshalingTestCOM3();
	//NoMarshalingTestCOM4();
	//MarshalingTestCOM1();
	//MarshalingTestCOM2();
	//MarshalingTestCOM3();
	//MarshalingTestCOM4();
	//InterThreadMarshalingTestCOM1();
	//InterThreadMarshalingTestCOM2();
	//InterThreadMarshalingTestCOM3();
	InterThreadMarshalingTestCOM4();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------