//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\PointersServer\PointersServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "MyMallocSpy.h"
//------------------------------------------------------------------------------------------------------
void Test(void)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IPointersTest>							Interface=NULL;
		HRESULT													HR=CoCreateInstance(CLSID_PointersObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IPointersTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			if (SUCCEEDED(Interface->Dummy()))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED !\n");
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
void PointersNoCrossApartment(void)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IPointersTest>							Interface=NULL;
		HRESULT													HR=CoCreateInstance(CLSID_PointersObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IPointersTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Value=100;
			int*												NonNULLPointer=&Value;
			int*												NULLPointer=NULL;
			int*												Pointer1=&Value;
			int*												Pointer2=&Value;

			if (SUCCEEDED(HR=Interface->NoAttributePointer(NonNULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			// !!! Kedze sa NEPRISTUPUJE cez PROXY, tak sa CHYBNE ZASLATIE NULL POINTER NEDETEKUJE.
			if (SUCCEEDED(HR=Interface->NoAttributePointer(NULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->RefAttributePointer(NonNULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			// !!! Kedze sa NEPRISTUPUJE cez PROXY, tak sa CHYBNE ZASLATIE NULL POINTER NEDETEKUJE.
			if (SUCCEEDED(HR=Interface->RefAttributePointer(NULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->UniqueAttributePointer(NonNULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->UniqueAttributePointer(NULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->NoPtrAttributePointer(Pointer1,Pointer2)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->PtrAttributePointer(Pointer1,Pointer2)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
void PointersCrossApartment(void)
{
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IPointersTest>							Interface=NULL;
		HRESULT													HR=CoCreateInstance(CLSID_PointersObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IPointersTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int													Value=100;
			int*												NonNULLPointer=&Value;
			int*												NULLPointer=NULL;
			int*												Pointer1=&Value;
			int*												Pointer2=&Value;

			if (SUCCEEDED(HR=Interface->NoAttributePointer(NonNULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			// !!! Kedze sa pristupuje cez PROXY a posiela sa NULL POINTER do METHOD, ktora to NEUMOZNUJE (ak nie je aplikovany [unique], tak DEFAULT ATTRIBUTE je [ref]), METHOD CALL vrati CHYBU.
			if (SUCCEEDED(HR=Interface->NoAttributePointer(NULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->RefAttributePointer(NonNULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			// !!! Kedze sa pristupuje cez PROXY a posiela sa NULL POINTER do METHOD, ktora to NEUMOZNUJE (aplikovany [ref] ATTRIBUTE), METHOD CALL vrati CHYBU.
			if (SUCCEEDED(HR=Interface->RefAttributePointer(NULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->UniqueAttributePointer(NonNULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->UniqueAttributePointer(NULLPointer)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			// !!! Kedze sa POUZIVA PROXY, ale NEPOUZIVA sa [ptr] ATTIRBUTE, tak AJ KED CLIENT zasiela IDENTICKE POINTERS, tak budu UNMARSHALED do ROZLICNYCH PAMATOVYCH MIEST a teda budu to ODLISNE POINTERS.
			if (SUCCEEDED(HR=Interface->NoPtrAttributePointer(Pointer1,Pointer2)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
			}

			if (SUCCEEDED(HR=Interface->PtrAttributePointer(Pointer1,Pointer2)))
			{
				wprintf_s(L"METHOD CALL SUCCEEDED !\n");
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
void MallocSpyNoCrossApartment(void)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IPointersTest>							Interface=NULL;
		HRESULT													HR=CoCreateInstance(CLSID_PointersObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IPointersTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int*												Pointer=NULL;
			int**												PointerToPointer=&Pointer;
			CSmartCOMPointer<IMallocSpy>						MallocSpy=new CMyMallocSpy();
			
			if (SUCCEEDED(HR=CoRegisterMallocSpy(MallocSpy.GetInterface())))
			{
				if (SUCCEEDED(HR=Interface->MallocSpyTest(PointerToPointer)))
				{
					wprintf_s(L"POINTER VALUE [%d] !\n",*Pointer);

					CSmartCOMPointer<IMalloc>					Malloc;

					if (SUCCEEDED(CoGetMalloc(1,&Malloc)))
					{
						Malloc->Free(Pointer);

						Malloc=NULL;
					}
				}
				else
				{
					wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				}

				if (FAILED(HR=CoRevokeMallocSpy()))
				{
					wprintf_s(L"Can't UNREGISTER MALLOC SPY [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				}
			}
			else
			{
				wprintf_s(L"Can't REGISTER MALLOC SPY [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
void MallocSpyCrossApartment(void)
{
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IPointersTest>							Interface=NULL;
		HRESULT													HR=CoCreateInstance(CLSID_PointersObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IPointersTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			int*												Pointer=NULL;
			int**												PointerToPointer=&Pointer;
			CSmartCOMPointer<IMallocSpy>						MallocSpy=new CMyMallocSpy();
			
			if (SUCCEEDED(HR=CoRegisterMallocSpy(MallocSpy.GetInterface())))
			{
				if (SUCCEEDED(HR=Interface->MallocSpyTest(PointerToPointer)))
				{
					wprintf_s(L"POINTER VALUE [%d] !\n",*Pointer);

					CSmartCOMPointer<IMalloc>					Malloc;

					if (SUCCEEDED(CoGetMalloc(1,&Malloc)))
					{
						Malloc->Free(Pointer);

						Malloc=NULL;
					}
				}
				else
				{
					wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				}

				if (FAILED(HR=CoRevokeMallocSpy()))
				{
					wprintf_s(L"Can't UNREGISTER MALLOC SPY [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
				}
			}
			else
			{
				wprintf_s(L"Can't REGISTER MALLOC SPY [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
void EmbeddedPointers(void)
{
	CoInitializeEx(NULL,COINIT_APARTMENTTHREADED);

	try
	{
		CSmartCOMPointer<IPointersTest>							Interface=NULL;
		HRESULT													HR=CoCreateInstance(CLSID_PointersObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IPointersTest),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			struct SName										Name;

			// !!!!! TOP-LEVEL POINTERS su ALOKOVANE VZDY na CLIENTOVI.
			if (SUCCEEDED(HR=Interface->MemoryAllocatedByServer(&Name)))
			{
				wprintf_s(L"NAME [%s] !\n",Name.MName);

				CSmartCOMPointer<IMalloc>						Malloc;

				if (SUCCEEDED(CoGetMalloc(1,&Malloc)))
				{
					if (Malloc->DidAlloc(Name.MName)==1)
					{
						wprintf_s(L"MEMORY WAS ALLOCATED by IMalloc !\n");
					}
					else
					{
						wprintf_s(L"!!! MEMORY WAS NOT ALLOCATED by IMalloc !\n");
					}

					// !!!!! Kedze EMBEDDED POINTER bol alokovany COM OBJECT cez IMalloc, CLIENT ho MUSI EXPLICITNE UVOLNIT.
					Malloc->Free(Name.MName);

					Malloc=NULL;
				}
			}
			else
			{
				wprintf_s(L"METHOD CALL FAILED [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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

	//Test();
	//PointersNoCrossApartment();
	//PointersCrossApartment();
	//MallocSpyNoCrossApartment();
	//MallocSpyCrossApartment();
	EmbeddedPointers();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------