//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\ApartmentThreadingModelServer\ApartmentThreadingModelServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "MyMessageFilter.h"
//------------------------------------------------------------------------------------------------------
const int														NUMBER_OF_ITERATIONS=10000;
//------------------------------------------------------------------------------------------------------
struct SThreadParams
{
	HANDLE														MThreadExitHandle;
	IApartmentThreadingModelTest*								MCOMPointer;
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
struct SGITMarshalingThreadParams
{
	HANDLE														MThreadExitHandle;
	DWORD														MCookie;
};
//------------------------------------------------------------------------------------------------------
struct STableStrongThreadParams
{
	HANDLE														MThreadExitHandle;
	// !!!!! IStream aj ked je to COM INTERFACE, tak v pripade, ze je vrateny z RegisterInterfaceInGlobal(), tak je ho mozne prenasat medzi APARTMENTS.
	CSmartCOMPointer<IStream>									MStream;
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
		// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU) prenasam do THREADU s NEKOPMATIBILNYM APARTMENT (inym STA).
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=(IApartmentThreadingModelTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			// !!!!! Kedze ku COM OBJECT pristupujem cez PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU), tak COM NEMA SANCU DETEKOVAT CHYBU PREKROCENIA HRANICE APARTMENT a METHOD sa KOREKTNE ZAVOLA. Avsak volanie uz NEBUDE THREAD-SAFE. Vysledkom je, ze COUNTER bude obsahovat NESPRAVNU HODNOTU.
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
		// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU) prenasam do THREADU s NEKOPMATIBILNYM APARTMENT (inym STA).
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=(IApartmentThreadingModelTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			// !!!!! Kedze ko COM OBJECT pristupujem cez PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU), tak COM NEMA SANCU DETEKOVAT CHYBU PREKROCENIA HRANICE APARTMENT a METHOD sa KOREKTNE ZAVOLA. Avsak volanie uz NEBUDE THREAD-SAFE. Vysledkom je, ze COUNTER bude obsahovat NESPRAVNU HODNOTU.
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
		// !!!!! CHYBA !!! PROXY na COM OBJECT sa prenasa do INEHO THREADU (INY STA APARTMENT) BEZ VYKONANIA MARSHALINGU.
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=(IApartmentThreadingModelTest*) TypedParam->MCOMPointer;

		for (int Index=0;Index<NUMBER_OF_ITERATIONS;Index++)
		{
			// !!!!! Volanie METHOD hodi CHYBU RPC_E_WRONG_THREAD (0x8001010E). Je to dosledok toho, ze do THREADU sa preniesol PROXY OBJECT, ktory NEBOL MARSHALED a tento PROXY OBJECT DETEKOVAL NEKOREKTNE PREKROCENIE HRANICE APARTMENT.
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
		// !!!!! OK. Prenasa sa PROXY na COM OBJECT do INEHO KOMPATIBILNEHO APARTMENT.
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=(IApartmentThreadingModelTest*) TypedParam->MCOMPointer;

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
			CSmartCOMPointer<IApartmentThreadingModelTest>		Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, STA - WORKER THREAD, STA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
			CSmartCOMPointer<IApartmentThreadingModelTest>		Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, MTA - WORKER THREAD, STA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
			CSmartCOMPointer<IApartmentThreadingModelTest>		Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (MTA - MAIN THREAD, STA - WORKER THREAD, MTA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
			CSmartCOMPointer<IApartmentThreadingModelTest>		Interface=NULL;

			// !!!!! OK !!! Kedze APARTMENTS SU KOMPATIBILNE (MTA - MAIN THREAD, MTA - WORKER THREAD, MTA - COM OBJECT), ziskava sa PRIAMY POINTER na COM OBJECT.
			if (SUCCEEDED(HR=CoUnmarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, STA - WORKER THREAD, STA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, MTA - WORKER THREAD, STA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (MTA - MAIN THREAD, STA - WORKER THREAD, MTA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
			wprintf_s(L"Can't create STREAM from HGLOBAL HR: [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS SU KOMPATIBILNE (MTA - MAIN THREAD, MTA - WORKER THREAD, MTA - COM OBJECT), ziskava sa PRIAMY POINTER na COM OBJECT.
		if (SUCCEEDED(HR=CoGetInterfaceAndReleaseStream(TypedParam->MStream,__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
unsigned int __stdcall GITThread(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SGITMarshalingThreadParams*									TypedParam=(SGITMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IGlobalInterfaceTable>					GIT=NULL;

		if (SUCCEEDED(CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
		{
			CSmartCOMPointer<IApartmentThreadingModelTest>		Interface=NULL;

			if (SUCCEEDED(GIT->GetInterfaceFromGlobal(TypedParam->MCookie,__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
				wprintf_s(L"Can't UNMARSHAL COM INTERFACE !\n");
			}

			GIT=NULL;
		}
		else
		{
			wprintf_s(L"Can't create GIT !\n");
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall MessageFilterTestThread(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	SGITMarshalingThreadParams*									TypedParam=(SGITMarshalingThreadParams*) Param;

	{
		CSmartCOMPointer<IGlobalInterfaceTable>					GIT=NULL;

		if (SUCCEEDED(CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
		{
			CSmartCOMPointer<IApartmentThreadingModelTest>		Interface=NULL;

			if (SUCCEEDED(HR=GIT->GetInterfaceFromGlobal(TypedParam->MCookie,__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
			{
				wprintf_s(L"THREAD - POINTER [%p] !\n",Interface.GetInterface());

				for (int Index=0;Index<10;Index++)
				{
					if (FAILED(HR=Interface->IncrementValue()))
					{
						wprintf_s(L"FUNCTION IncrementValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
					}
				}

				Interface=NULL;
			}
			else
			{
				wprintf_s(L"Can't UNMARSHAL COM INTERFACE !\n");
			}

			GIT=NULL;
		}
		else
		{
			wprintf_s(L"Can't create GIT !\n");
		}
	}

	CoUninitialize();

	SetEvent(TypedParam->MThreadExitHandle);

	return(0);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall ThreadStrongTableMarshaling(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	//SInterMarshalingThreadParams*								TypedParam=(SInterMarshalingThreadParams*) Param;
	STableStrongThreadParams*									TypedParam=(STableStrongThreadParams*) Param;

	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! OK !!! Kedze APARTMENTS NIE SU KOMPATIBILNE (STA - MAIN THREAD, STA - WORKER THREAD, STA - COM OBJECT), vytvara sa PROXY na COM OBJECT.
		if (SUCCEEDED(HR=CoUnmarshalInterface(TypedParam->MStream.GetInterface(),__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
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
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void MultiSTATest1(void)
{
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. S THREAD sa asociuje STA APARTMENT.

	// !!! Vytvara sa STA.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	CSmartCOMPointer<IApartmentThreadingModelTest>				Interface=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		Interface->IncrementValue();
		Interface->IncrementValue();
		Interface->IncrementValue();

		long													Value1=0;

		Interface->GetValue(&Value1);

		wprintf_s(L"VALUE: [%d] !\n",Value1);

		// !!! Umyselne UKONCIM APARTMENT.
		// !!!!! Tu sa SKONCI platnost VSETKYCH COM OBJECTS vytvorenych v danom APARTMENT.
		CoUninitialize();

		// !!! Vytvara sa NOVY STA.
		CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

		long													Value2=0;

		// !!!!! Hodi CHYBNY PRISTUP k PAMATI, lebo sa pokusam o pristupovanie ku COM OBJECT, ktory bol vytvoreny v INOM STA APARTMENT.
		// !!!!! CHYBNY PRISTUP k PAMATI je doledok toho, ze CoUninitialize() SKONCI platnost VSETKYCH COM OBJECTS vytvorenych v danom APARTMENT.
		if (SUCCEEDED(HR=Interface->GetValue(&Value2)))
		{
			wprintf_s(L"VALUE: [%d] !\n",Value2);
		}
		else
		{
			wprintf_s(L"FUNCTION GetValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
		}

		Interface=NULL;
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void MultiSTATest2(void)
{
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. S THREAD sa asociuje STA APARTMENT.

	// !!! Vytvara sa STA.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	CSmartCOMPointer<IApartmentThreadingModelTest>				Interface1=NULL;

	HRESULT														HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface1);

	if (SUCCEEDED(HR))
	{
		Interface1->IncrementValue();
		Interface1->IncrementValue();
		Interface1->IncrementValue();

		long													Value1=0;

		Interface1->GetValue(&Value1);

		wprintf_s(L"VALUE: [%d] !\n",Value1);

		// !!!!! Kedze CoUninitialize() KONCI platnost VSETKYCH COM OBJECTS vytvorenych v danom APARTMENT, SMART POINTER MUSIM UVOLNIT ESTE PRED volanim CoUninitialize(). Ak to spravim PO zavolani CoUninitialize(), dojde k CHYNEMU PRISTUPU k PAMATI pri volani Release() z DESTRUCTORA SMART POINTER.
		Interface1=NULL;

		// !!! Umyselne UKONCIM APARTMENT.
		// !!!!! Tu sa SKONCI platnost VSETKYCH COM OBJECTS vytvorenych v danom APARTMENT.
		CoUninitialize();

		// !!! Vytvara sa NOVY STA.
		CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface2=NULL;

		// !!! Vytvori sa NOVY COM OBJECT v NOVOM STA APARTMENT.
		if (SUCCEEDED(HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface2)))
		{
			// !!!!! Kedze sa pristupuje k NOVEMU COM OBJECT vytvorenom v NOVOM APARTMENT, tak volanie prebehe KOREKTNE.
			Interface2->IncrementValue();
			Interface2->IncrementValue();
			Interface2->IncrementValue();
			Interface2->IncrementValue();
			Interface2->IncrementValue();

			long													Value2=0;

			// !!!!! Kedze sa pristupuje k NOVEMU COM OBJECT vytvorenom v NOVOM APARTMENT, tak volanie prebehe KOREKTNE.
			if (SUCCEEDED(HR=Interface2->GetValue(&Value2)))
			{
				wprintf_s(L"VALUE: [%d] !\n",Value2);
			}
			else
			{
				wprintf_s(L"FUNCTION GetValue() FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			Interface2=NULL;
		}
	}

	CoUninitialize();
}
//------------------------------------------------------------------------------------------------------
void StreamsTest(void)
{
	CSmartCOMPointer<IStream>									Stream;

	// !!! Ak je 1. PARAMETER NULL, tak HGLOBAL sa alokuje AUTOMATICKY.
	if (SUCCEEDED(CreateStreamOnHGlobal(NULL,TRUE,&Stream)))
	{
		wchar_t													BufferIn[]=L"Timmy Anderson";

		if (SUCCEEDED(Stream->Write(BufferIn,_countof(BufferIn)*sizeof(wchar_t),NULL)))
		{
			HGLOBAL												HGlobal=0;

			if (SUCCEEDED(GetHGlobalFromStream(Stream.GetInterface(),&HGlobal)))
			{
				wchar_t*										DataFromStream=NULL;

				if ((DataFromStream=(wchar_t*) GlobalLock(HGlobal))!=NULL)
				{
					wprintf_s(L"DataFromStream [%s] !\n",DataFromStream);

					GlobalUnlock(HGlobal);
				}
			}
		}

		Stream=NULL;
	}
}
//------------------------------------------------------------------------------------------------------
void ByteStreamDump(void)
{
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			CSmartCOMPointer<IStream>							Stream;

			if (SUCCEEDED(CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
			{
				if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
				{
					LARGE_INTEGER								LI;

					LI.QuadPart=0;

					if (SUCCEEDED(Stream->Seek(LI,STREAM_SEEK_SET,NULL)))
					{
						int										Counter=0;

						while(true)
						{
							ULONG								BytesRead=0;
							BYTE								Byte;

							if (Stream->Read(&Byte,1,&BytesRead)==S_OK && BytesRead>0)
							{
								wprintf_s(L"BYTE[%d]: [%02X] - [%c] !\n",Counter++,Byte,Byte);
							}
							else
							{
								break;
							}
						}
					}
				}
				else
				{
					wprintf_s(L"Can't create STREAM !\n");
				}
			}

			Stream=NULL;
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
void NoMarshalingTestCOM1(void)
{
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU) prenasam do THREADU s NEKOPMATIBILNYM APARTMENT (inym STA).
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! CHYBA !!! PRIAMY POINTER na COM OBJECT (BEZ VYKONANIA MARSHALINGU) prenasam do THREADU s NEKOPMATIBILNYM APARTMENT (MTA).
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! CHYBA !!! PROXY na COM OBJECT sa prenasa do INEHO THREADU (INY STA APARTMENT) BEZ VYKONANIA MARSHALINGU.
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SThreadParams										ThreadParams[NUMBER_OF_THREADS];

			for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
			{
				ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
				// !!!!! OK. Prenasa sa PROXY na COM OBJECT do INEHO KOMPATIBILNEHO APARTMENT.
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
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v STA (COM OBJECT je STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v STA (COM OBJECT je STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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
					if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_NORMAL)))
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
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v STA (COM OBJECT je STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori SINGLE-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v STA (COM OBJECT je STA) MESSAGE PUMP JE NUTNA.

	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa SINGLE-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
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
	// 1. COM OBJECT je SINGLE-THREAD APARTMENT.
	// 2. Vytvori MULTI-THREAD APARTMENT.
	// 3. Vytvoria sa MULTI-THREAD APARTMENT WORKER THREADS.
	// !!!!! 4. Kedze COM OBJECT bol vytvoreny v MTA (COM OBJECT je MTA) MESSAGE PUMP NIE JE POTREBNA.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

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

				if (SUCCEEDED(CoMarshalInterThreadInterfaceInStream(__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),&ThreadParams[Index].MStream)))
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
void MarshalingByGIT(void)
{
	// !!! Demonstruje sa MARSHALING cez GIT.

	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			SGITMarshalingThreadParams							ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));
			ZeroMemory(ThreadParams,sizeof(ThreadParams));

			CSmartCOMPointer<IGlobalInterfaceTable>				GIT=NULL;
			DWORD												Cookie=0;

			if (SUCCEEDED(CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
			{
				// !!! Vykonam MARSHALING do GIT.
				if (SUCCEEDED(GIT->RegisterInterfaceInGlobal(Interface.GetInterface(),__uuidof(IApartmentThreadingModelTest),&Cookie)))
				{
					for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
					{
						ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);
						ThreadParams[Index].MCookie=Cookie;
						ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,GITThread,&ThreadParams[Index],0,NULL);
					}

					// !!! MESSAGE PUMP.
					while(true)
					{
						if (MsgWaitForMultipleObjects(NUMBER_OF_THREADS,ThreadExitHandles,FALSE,INFINITE,QS_ALLINPUT)==(WAIT_OBJECT_0+NUMBER_OF_THREADS))
						{
							// !!!!! EXTREMNE DOLEZITE. Pri signalizacii MsgWaitForMultipleObjects() ze prisla WINDOW MESSAGE je treba pumpovat CELU QUEUE, NIE LEN 1 MESSAGE.
							while(true)
							{
								MSG								Message;

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

						bool									Exit=true;

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

					long											Value=0;

					Interface->GetValue(&Value);

					wprintf_s(L"!!!!! CLIENT VALUE: [%d] !\n",Value);

					Interface=NULL;

					if (Cookie!=0)
					{
						// !!! Odstranim zaznam z GIT.
						if (FAILED(GIT->RevokeInterfaceFromGlobal(Cookie)))
						{
							wprintf_s(L"Can't REVOKE COOKIE !\n");
						}

						Cookie=0;
					}
				}
				else
				{
					wprintf_s(L"Can't MARSHAL COM INTERFACE !\n");
				}

				GIT=NULL;
			}
			else
			{
				wprintf_s(L"Can't create GIT !\n");
			}
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
void MessageFilterTest(void)
{
	// !!!!! Na to aby fungoval MESSAGE FILTER, MUSI sa pouzit STA APARTMENT.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;
		CSmartCOMPointer<IMessageFilter>						MyMessageFiler=new CMyMessageFilter();
		CSmartCOMPointer<IMessageFilter>						OriginalMessageFiler=NULL;

		HRESULT													HR;

		if (SUCCEEDED(HR=CoRegisterMessageFilter(MyMessageFiler.GetInterface(),&OriginalMessageFiler)))
		{
			// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU NIE SU KOMPATIBILNE, vracia sa PROXY na COM OBJECT.
			if (SUCCEEDED(HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface)))
			{
				wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

				HANDLE											ThreadExitHandle;
				HANDLE											ThreadHandle;
				SGITMarshalingThreadParams						ThreadParams;

				ZeroMemory(&ThreadExitHandle,sizeof(ThreadExitHandle));
				ZeroMemory(&ThreadHandle,sizeof(ThreadHandle));
				ZeroMemory(&ThreadParams,sizeof(ThreadParams));

				CSmartCOMPointer<IGlobalInterfaceTable>			GIT=NULL;
				DWORD											Cookie=0;

				if (SUCCEEDED(CoCreateInstance(CLSID_StdGlobalInterfaceTable,NULL,CLSCTX_INPROC_SERVER,__uuidof(IGlobalInterfaceTable),(void**) &GIT)))
				{
					// !!! Vykonam MARSHALING do GIT.
					if (SUCCEEDED(GIT->RegisterInterfaceInGlobal(Interface.GetInterface(),__uuidof(IApartmentThreadingModelTest),&Cookie)))
					{
						ThreadParams.MThreadExitHandle=ThreadExitHandle=CreateEvent(NULL,TRUE,FALSE,NULL);
						ThreadParams.MCookie=Cookie;
						ThreadHandle=(HANDLE) _beginthreadex(NULL,0,MessageFilterTestThread,&ThreadParams,0,NULL);

						// !!! MESSAGE PUMP.
						while(true)
						{
							if (MsgWaitForMultipleObjects(1,&ThreadExitHandle,FALSE,INFINITE,QS_ALLINPUT)==(WAIT_OBJECT_0+1))
							{
								// !!!!! EXTREMNE DOLEZITE. Pri signalizacii MsgWaitForMultipleObjects() ze prisla WINDOW MESSAGE je treba pumpovat CELU QUEUE, NIE LEN 1 MESSAGE.
								while(true)
								{
									MSG							Message;

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

							bool								Exit=true;

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

						long											Value=0;

						Interface->GetValue(&Value);

						wprintf_s(L"!!!!! CLIENT VALUE: [%d] !\n",Value);

						Interface=NULL;

						if (Cookie!=0)
						{
							// !!! Odstranim zaznam z GIT.
							if (FAILED(GIT->RevokeInterfaceFromGlobal(Cookie)))
							{
								wprintf_s(L"Can't REVOKE COOKIE !\n");
							}

							Cookie=0;
						}
					}
					else
					{
						wprintf_s(L"Can't MARSHAL COM INTERFACE !\n");
					}

					GIT=NULL;
				}
				else
				{
					wprintf_s(L"Can't create GIT !\n");
				}

				Interface=NULL;
			}
			else
			{
				wprintf_s(L"Can't create COM OBJECT !\n");
			}
		}
		else
		{
			wprintf_s(L"Can't REGISTER MESSAGE FILTER !\n");
		}

		if (FAILED(CoRegisterMessageFilter(OriginalMessageFiler.GetInterface(),NULL)))
		{
			wprintf_s(L"Can't UNREGISTER MESSAGE FILTER !\n");
		}

		MyMessageFiler=NULL;
		OriginalMessageFiler=NULL;
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
void StrongTableMarshaling(void)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IApartmentThreadingModelTest>			Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ApartmentThreadingModelObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IApartmentThreadingModelTest),(void**) &Interface);
		CSmartCOMPointer<IStream>								Stream;

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			//SInterMarshalingThreadParams						ThreadParams[NUMBER_OF_THREADS];
			STableStrongThreadParams							ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));

			if (SUCCEEDED(CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
			{
				// !!!!! Pouziva sa FLAG MSHLFLAGS_TABLESTRONG.
				if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IApartmentThreadingModelTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_TABLESTRONG)))
				{
					LARGE_INTEGER								LI;

					LI.QuadPart=0;

					if (SUCCEEDED(Stream->Seek(LI,STREAM_SEEK_SET,NULL)))
					{
						for (int Index=0;Index<NUMBER_OF_THREADS;Index++)
						{
							ThreadParams[Index].MThreadExitHandle=ThreadExitHandles[Index]=CreateEvent(NULL,TRUE,FALSE,NULL);

							if (SUCCEEDED(Stream->Clone(&ThreadParams[Index].MStream)))
							{
								ThreadHandles[Index]=(HANDLE) _beginthreadex(NULL,0,ThreadStrongTableMarshaling,&ThreadParams[Index],0,NULL);
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
									MSG							Message;

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

							bool								Exit=true;

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

						long									Value=0;

						Interface->GetValue(&Value);

						wprintf_s(L"!!!!! CLIENT VALUE: [%d] !\n",Value);
					}
					else
					{
						wprintf_s(L"Can't MARSHAL INTERFACE !\n");
					}
				}
				else
				{
					wprintf_s(L"Can't SEEK STREAM !\n");
				}
			}
			else
			{
				wprintf_s(L"Can't create STREAM !\n");
			}

			Interface=NULL;
		}
		else
		{
			wprintf_s(L"Can't create COM OBJECT !\n");
		}

		wprintf_s(L"CoReleaseMarshalData() will be CALLED !\n");

		// !!! Kedze sa pouzil FLAG MSHLFLAGS_TABLESTRONG, je treba pouzit CoReleaseMarshalData().
		// !!!!! Zaroven sa uvolni COM OBJECT, co je vidiet na vypise v konzole. Ak by som tento riadok ZAKOMENTOVAL, tak COM OBJECT sa uvolni az pri UKONCENI APARTMENT.
		if (FAILED(CoReleaseMarshalData(Stream.GetInterface())))
		{
			wprintf_s(L"Can't RELEASE MARSHAL DATA !\n");
		}

		wprintf_s(L"CoReleaseMarshalData() was CALLED !\n");

		wprintf_s(L"Now REFERENCE to STREAM will be RELEASED !\n");

		Stream=NULL;

		wprintf_s(L"REFERENCE to STREAM was RELEASED !\n");
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	wprintf_s(L"Now APARTMENT will be RELEASED !\n");

	// !!!!! Ak by som NEVOLAL CoReleaseMarshalData(), tak sa COM OBJECT uzavrie AZ TU.
	CoUninitialize();

	wprintf_s(L"APARTMENT was RELEASED !\n");
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	//MultiSTATest1();
	//MultiSTATest2();
	//StreamsTest();
	//ByteStreamDump();
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
	//InterThreadMarshalingTestCOM4();
	//MarshalingByGIT();
	//MessageFilterTest();
	StrongTableMarshaling();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------