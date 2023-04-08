//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\ExternalConnectionServer\ExternalConnectionServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
const int														NUMBER_OF_ITERATIONS=10000;
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
unsigned int __stdcall ThreadStrongTableMarshaling(void* Param)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	HRESULT														HR;
	STableStrongThreadParams*									TypedParam=(STableStrongThreadParams*) Param;

	{
		CSmartCOMPointer<IExternalConnectionTest>			Interface=NULL;

		if (SUCCEEDED(HR=CoUnmarshalInterface(TypedParam->MStream.GetInterface(),__uuidof(IExternalConnectionTest),(void**) &Interface)))
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
void ExternalConnectionTest(void)
{
	// !!! Vytvara sa APARTMENT THREAD.
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IExternalConnectionTest>				Interface=NULL;

		// !!!!! Vytvori sa COM OBJECT. Kedze APARTMENT COM OBJECT a THREADU su KOMPATIBILNE, vracia sa PRIAMY POINTER na COM OBJECT.
		HRESULT													HR=CoCreateInstance(CLSID_ExternalConnectionObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IExternalConnectionTest),(void**) &Interface);
		CSmartCOMPointer<IStream>								Stream;

		if (SUCCEEDED(HR))
		{
			wprintf_s(L"MAIN - POINTER [%p] !\n",Interface.GetInterface());

			const int											NUMBER_OF_THREADS=10;
			HANDLE												ThreadExitHandles[NUMBER_OF_THREADS];
			HANDLE												ThreadHandles[NUMBER_OF_THREADS];
			STableStrongThreadParams							ThreadParams[NUMBER_OF_THREADS];

			ZeroMemory(ThreadExitHandles,sizeof(ThreadExitHandles));
			ZeroMemory(ThreadHandles,sizeof(ThreadHandles));

			if (SUCCEEDED(CreateStreamOnHGlobal(NULL,FALSE,&Stream)))
			{
				// !!!!! Pouziva sa FLAG MSHLFLAGS_TABLESTRONG.
				if (SUCCEEDED(CoMarshalInterface(Stream.GetInterface(),__uuidof(IExternalConnectionTest),Interface.GetInterface(),MSHCTX_DIFFERENTMACHINE,NULL,MSHLFLAGS_TABLESTRONG)))
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

	ExternalConnectionTest();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------