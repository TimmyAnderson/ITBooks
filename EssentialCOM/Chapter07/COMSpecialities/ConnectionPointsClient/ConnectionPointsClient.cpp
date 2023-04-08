//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\ConnectionPointsServer\ConnectionPointsServer_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
#include "MyConnectionPointsCallback.h"
//------------------------------------------------------------------------------------------------------
void Test(void)
{
	// !!! Vytvara sa FREE THREAD.
	CoInitializeEx(NULL,COINIT_MULTITHREADED);

	try
	{
		CSmartCOMPointer<IMyConnectionPoints>					Interface=NULL;

		HRESULT													HR=CoCreateInstance(CLSID_ConnectionPointsObject,NULL,CLSCTX_INPROC_SERVER,__uuidof(IMyConnectionPoints),(void**) &Interface);

		if (SUCCEEDED(HR))
		{
			CSmartCOMPointer<IConnectionPointContainer>			ConnectionPointContainer=NULL;

			if (SUCCEEDED(Interface->QueryInterface(__uuidof(IConnectionPointContainer),(void**) &ConnectionPointContainer)))
			{
				// !!!!! COM OBJECT je naprogramovany tak, ze EVENTS sa odosielaju VSETKYM CALLBACK COM INTERFACES vo VSETKYCH CONNECTION POINTS.
				CSmartCOMPointer<IConnectionPoint>				ConnectionPoint1=NULL;
				CSmartCOMPointer<IConnectionPoint>				ConnectionPoint2=NULL;

				// !!! Najdem CONNECTION POINTS na CALLBACK COM INTERFACE IMyConnectionPointsCallback.
				HRESULT											HR1=ConnectionPointContainer->FindConnectionPoint(__uuidof(IMyConnectionPointsCallback),&ConnectionPoint1);
				HRESULT											HR2=ConnectionPointContainer->FindConnectionPoint(__uuidof(IMyConnectionPointsCallback),&ConnectionPoint2);

				if (SUCCEEDED(HR1) && SUCCEEDED(HR2))
				{
					CSmartCOMPointer<IMyConnectionPointsCallback>	Callback11=new CMyConnectionPointsCallback(L"Callback11");
					CSmartCOMPointer<IMyConnectionPointsCallback>	Callback12=new CMyConnectionPointsCallback(L"Callback12");
					CSmartCOMPointer<IMyConnectionPointsCallback>	Callback21=new CMyConnectionPointsCallback(L"Callback21");
					CSmartCOMPointer<IMyConnectionPointsCallback>	Callback22=new CMyConnectionPointsCallback(L"Callback22");

					DWORD										Cookie1=0;
					DWORD										Cookie2=0;
					DWORD										Cookie3=0;
					DWORD										Cookie4=0;

					HRESULT										HRegister1=ConnectionPoint1->Advise(Callback11.GetInterface(),&Cookie1);
					HRESULT										HRegister2=ConnectionPoint1->Advise(Callback12.GetInterface(),&Cookie2);
					HRESULT										HRegister3=ConnectionPoint2->Advise(Callback21.GetInterface(),&Cookie3);
					HRESULT										HRegister4=ConnectionPoint2->Advise(Callback12.GetInterface(),&Cookie4);

					if (SUCCEEDED(HRegister1) && SUCCEEDED(HRegister2) && SUCCEEDED(HRegister3) && SUCCEEDED(HRegister4))
					{
						DWORD									CookieTemp=0;
						CSmartCOMPointer<IMyConnectionPointsCallback>	CallbackTemp=new CMyConnectionPointsCallback(L"Temp");

						// !!! Kedze MAXIMALNY pocet CONNECTIONS je 4, toto volanie MUSI ZLYHAT.
						if (SUCCEEDED(ConnectionPoint2->Advise(Callback12.GetInterface(),&CookieTemp)))
						{
							wprintf_s(L"!!! ERROR - CONNECTION POINT was ADVISED byt SHOULD NOT !\n");
						}

						// !!! Odoslem MESSAGE na SERVER.
						Interface->SendMessageToServer(bstr_t(L"SUPER MESSAGE 1111111111 !!!"));

						// !!! Odoslem MESSAGE na SERVER.
						Interface->SendMessageToServer(bstr_t(L"SUPER MESSAGE 2222222222 !!!"));

						CallbackTemp=NULL;
						CookieTemp=0;
					}
					else
					{
						wprintf_s(L"Can't ADVISE ALL CONNECTION POINT !\n");
					}

					if (Cookie1!=0)
					{
						if (FAILED(ConnectionPoint1->Unadvise(Cookie1)))
						{
							wprintf_s(L"Can't UNADVISE CONNECTION POINT !\n");
						}

						Cookie1=0;
					}

					if (Cookie2!=0)
					{
						if (FAILED(ConnectionPoint1->Unadvise(Cookie2)))
						{
							wprintf_s(L"Can't UNADVISE CONNECTION POINT !\n");
						}

						Cookie2=0;
					}
					if (Cookie3!=0)
					{
						if (FAILED(ConnectionPoint2->Unadvise(Cookie3)))
						{
							wprintf_s(L"Can't UNADVISE CONNECTION POINT !\n");
						}

						Cookie3=0;
					}

					if (Cookie4!=0)
					{
						if (FAILED(ConnectionPoint2->Unadvise(Cookie4)))
						{
							wprintf_s(L"Can't UNADVISE CONNECTION POINT !\n");
						}

						Cookie4=0;
					}

					Callback11=NULL;
					Callback12=NULL;
					Callback21=NULL;
					Callback22=NULL;

					ConnectionPoint1=NULL;
					ConnectionPoint2=NULL;
				}
				else
				{
					wprintf_s(L"Can't create CONNECTION POINTS !\n");
				}

				ConnectionPointContainer=NULL;
			}
			else
			{
				wprintf_s(L"Can't create CONNECTION POINTS CONTAINER !\n");
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