//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include "stdafx.h"
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\MultiInterfaceCOMServer\MultiInterfaceCOM_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void PrintName(CSmartCOMPointer<IName> Interface)
{
	wchar_t														Buffer1[1024]={'\0'};
	wchar_t														Buffer2[1024]={'\0'};

	wchar_t*													FirstName=(wchar_t*) &Buffer1;
	wchar_t*													LastName=(wchar_t*) &Buffer2;
	int															Age=0;

	Interface->SetFirstName(L"Timmy");
	Interface->SetLastName(L"Anderson");
	Interface->SetAge(12);

	Interface->GetFirstName(_countof(Buffer1),(wchar_t**) &FirstName);
	Interface->GetLastName(_countof(Buffer2),(wchar_t**) &LastName);
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
void PrintToString(CSmartCOMPointer<IToString> Interface)
{
	Interface->ToString();
}
//------------------------------------------------------------------------------------------------------
void PrintTest(CSmartCOMPointer<ITest> Interface)
{
	bstr_t														Buffer1;
	bstr_t														Buffer2;
	bstr_t														Buffer3;
	BSTR*														Pointer1=Buffer1.GetAddress();
	BSTR*														Pointer2=Buffer2.GetAddress();
	BSTR*														Pointer3=Buffer3.GetAddress();

	Interface->SetString(bstr_t(L"Timmy Anderson"));
	Interface->GetString(Pointer1);
	Interface->GetString(Pointer2);
	Interface->GetString(Pointer3);

	wprintf_s(L"Name [%s] !\n",Buffer1.operator const wchar_t *());
	wprintf_s(L"Name [%s] !\n",Buffer2.operator const wchar_t *());
	wprintf_s(L"Name [%s] !\n",Buffer3.operator const wchar_t *());

	SName														NameIn={L"Timmy",L"Anderson",12};
	SName														NameOut;

	Interface->SetName(NameIn);
	Interface->GetName(&NameOut);

	wprintf_s(L"STRUCT - FirstName: [%s] !\n",NameOut.MFirstName);
	wprintf_s(L"STRUCT - LastName: [%s] !\n",NameOut.MLastName);
	wprintf_s(L"STRUCT - Age: [%d] !\n",NameOut.MAge);

	union UAge													AgeIn;
	union UAge													AgeOut1;
	union UAge													AgeOut2;
	union UAge													AgeOut3;

	AgeIn.MIntAge=12;

	Interface->SetUnion(1,AgeIn);
	Interface->GetUnion(1,&AgeOut1);

	AgeIn.MLongAge=12;

	Interface->SetUnion(2,AgeIn);
	Interface->GetUnion(2,&AgeOut2);

	AgeIn.MDouble=12.0;

	Interface->SetUnion(3,AgeIn);
	Interface->GetUnion(3,&AgeOut3);

	wprintf_s(L"AgeOut1.MIntAge: [%d] !\n",AgeOut1.MIntAge);
	wprintf_s(L"AgeOut2.MLongAge: [%d] !\n",AgeOut2.MLongAge);
	wprintf_s(L"AgeOut3.MDouble: [%f] !\n",AgeOut3.MDouble);

	variant_t													In1=100;
	variant_t													In2(L"Timmy Anderson");
	variant_t													Out1;
	variant_t													Out2;

	Interface->SetVariant(In1);
	Interface->GetVariant(Out1.GetAddress());
	Interface->SetVariant(In2);
	Interface->GetVariant(Out2.GetAddress());

	wprintf_s(L"Out1: [%d] !\n",Out1.intVal);
	wprintf_s(L"Out2: [%s] !\n",Out2.bstrVal);

	Interface->put_MyProperty(123);

	int															Property;

	Interface->get_MyProperty(&Property);

	wprintf_s(L"PROPERTY: [%d] !\n",Property);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
unsigned int __stdcall TestThread(void* Param)
{
	CCriticalSectionWrapper*									CriticalSectionWrapper=(CCriticalSectionWrapper*) Param;

	wprintf_s(L"THREAD [%d] STARTED !\n",GetCurrentThreadId());

	{
		CLock													Lock(*CriticalSectionWrapper);

		wprintf_s(L"THREAD [%d] IN LOCK !\n",GetCurrentThreadId());

		Sleep(2000);
	}

	wprintf_s(L"THREAD [%d] FINISHED !\n",GetCurrentThreadId());

	return(0);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void ThreadTest(void)
{
	CCriticalSectionWrapper										CriticalSectionWrapper;

	HANDLE														Thread1=(HANDLE) _beginthreadex(NULL,0,TestThread,&CriticalSectionWrapper,0,NULL);
	HANDLE														Thread2=(HANDLE) _beginthreadex(NULL,0,TestThread,&CriticalSectionWrapper,0,NULL);
	HANDLE														Threads[]={Thread1,Thread2};

	WaitForMultipleObjects(_countof(Threads),Threads,TRUE,INFINITE);
}
//------------------------------------------------------------------------------------------------------
void TestCOM1(void)
{
	ULONG														ReleaseCount;
	IName*														Interface=NULL;
	HRESULT														HR=CoCreateInstance(CLSID_MultiInterfaceCOM,NULL,CLSCTX_INPROC_SERVER,__uuidof(IName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		wchar_t													Buffer1[1024]={'\0'};
		wchar_t													Buffer2[1024]={'\0'};

		wchar_t*												FirstName=(wchar_t*) &Buffer1;
		wchar_t*												LastName=(wchar_t*) &Buffer2;
		int														Age=0;

		Interface->SetFirstName(L"Timmy");
		Interface->SetLastName(L"Anderson");
		Interface->SetAge(12);

		Interface->GetFirstName(_countof(Buffer1),(wchar_t**) &FirstName);
		Interface->GetLastName(_countof(Buffer2),(wchar_t**) &LastName);
		Interface->GetAge(&Age);

		wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
		wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
		wprintf_s(L"CLIENT - Age: [%d] !\n",Age);

		IToString*												InterfaceToString=NULL;

		HR=Interface->QueryInterface(__uuidof(IToString),(void**) &InterfaceToString);

		if (SUCCEEDED(HR))
		{
			InterfaceToString->ToString();

			ReleaseCount=InterfaceToString->Release();
			InterfaceToString=NULL;
			wprintf_s(L"ReleaseCount: [%d] !\n",ReleaseCount);
		}

		ReleaseCount=Interface->Release();
		Interface=NULL;
		wprintf_s(L"ReleaseCount: [%d] !\n",ReleaseCount);
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM2(void)
{
	CSmartCOMPointer<IName>										Interface=NULL;
	HRESULT														HR=CoCreateInstance(CLSID_MultiInterfaceCOM,NULL,CLSCTX_INPROC_SERVER,__uuidof(IName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		wchar_t													Buffer1[1024]={'\0'};
		wchar_t													Buffer2[1024]={'\0'};

		wchar_t*												FirstName=(wchar_t*) &Buffer1;
		wchar_t*												LastName=(wchar_t*) &Buffer2;
		int														Age=0;

		Interface->SetFirstName(L"Timmy");
		Interface->SetLastName(L"Anderson");
		Interface->SetAge(12);

		Interface->GetFirstName(_countof(Buffer1),(wchar_t**) &FirstName);
		Interface->GetLastName(_countof(Buffer2),(wchar_t**) &LastName);
		Interface->GetAge(&Age);

		wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
		wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
		wprintf_s(L"CLIENT - Age: [%d] !\n",Age);

		CSmartCOMPointer<IToString>								InterfaceToString=NULL;

		HR=Interface->QueryInterface(__uuidof(IToString),(void**) &InterfaceToString);

		if (SUCCEEDED(HR))
		{
			InterfaceToString->ToString();

			InterfaceToString=NULL;
		}

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM3(void)
{
	CSmartCOMPointer<IName>										Interface=NULL;
	HRESULT														HR=CoCreateInstance(CLSID_MultiInterfaceCOM,NULL,CLSCTX_INPROC_SERVER,__uuidof(IName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		PrintName(Interface);

		CSmartCOMPointer<IToString>								InterfaceToString=NULL;

		HR=Interface->QueryInterface(__uuidof(IToString),(void**) &InterfaceToString);

		if (SUCCEEDED(HR))
		{
			PrintToString(InterfaceToString);
			InterfaceToString=NULL;
		}

		CSmartCOMPointer<ITest>									InterfaceToTest=NULL;

		HR=Interface->QueryInterface(__uuidof(ITest),(void**) &InterfaceToTest);

		if (SUCCEEDED(HR))
		{
			PrintTest(InterfaceToTest);
			InterfaceToTest=NULL;
		}

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM4(void)
{
	CSmartCOMPointer<IName>										Interface=NULL;
	HRESULT														HR=CoCreateInstance(CLSID_MultiInterfaceCOM,NULL,CLSCTX_INPROC_SERVER,__uuidof(IName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		Interface->SetFirstName(L"Timmy");
		Interface->SetLastName(L"Anderson");
		Interface->SetAge(12);

		CSmartCOMPointer<IToString>								InterfaceToString=NULL;

		HR=Interface->QueryInterface(__uuidof(IToString),(void**) &InterfaceToString);

		if (SUCCEEDED(HR))
		{
			CSmartCOMPointer<ITest>								InterfaceToTest=NULL;

			HR=Interface->QueryInterface(__uuidof(ITest),(void**) &InterfaceToTest);

			if (SUCCEEDED(HR))
			{
				InterfaceToTest->Print1(InterfaceToString.GetInterface());

				InterfaceToTest->Print2(__uuidof(IToString),InterfaceToString.GetInterface());

				InterfaceToTest->Print2(__uuidof(ITest),InterfaceToTest.GetInterface());

				InterfaceToTest=NULL;
			}
			
			InterfaceToString=NULL;
		}

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
void TestCOM5(void)
{
	CSmartCOMPointer<IName>										Interface=NULL;
	HRESULT														HR=CoCreateInstance(CLSID_MultiInterfaceCOM,NULL,CLSCTX_INPROC_SERVER,__uuidof(IName),(void**) &Interface);

	if (SUCCEEDED(HR))
	{
		CSmartCOMPointer<IExceptionTest>						InterfaceExceptionTest=NULL;

		HR=Interface->QueryInterface(__uuidof(IExceptionTest),(void**) &InterfaceExceptionTest);

		if (SUCCEEDED(HR))
		{
			if (FAILED(InterfaceExceptionTest->ThrowException(1)))
			{
				CSmartCOMPointer<ISupportErrorInfo>				InterfaceISupportErrorInfo=NULL;

				// Ziskam INTERFACE pomocou, ktoreho mozem zistit ci dany INTERFACE podporuje EXCEPTIONS.
				HR=Interface->QueryInterface(__uuidof(ISupportErrorInfo),(void**) &InterfaceISupportErrorInfo);

				if (SUCCEEDED(HR))
				{
					// !!! Zistim ci INTERFACE IExceptionTest podporuje EXCEPTIONS.
					if (SUCCEEDED(InterfaceISupportErrorInfo->InterfaceSupportsErrorInfo(__uuidof(IExceptionTest))))
					{
						CSmartCOMPointer<IErrorInfo>			InterfaceIErrorInfo1=NULL;

						// !!! Vycita ERROR INFO a zaroven ODSTRANI EXCEPTION INFO z aktualne LOGICAL THREAD.
						if (GetErrorInfo(0,&InterfaceIErrorInfo1)!=S_FALSE)
						{
							bstr_t								Error;

							InterfaceIErrorInfo1->GetDescription(Error.GetAddress());

							wprintf_s(L"ERROR [%s] !\n",Error.operator const wchar_t *());

							InterfaceIErrorInfo1=NULL;
						}
						else
						{
							wprintf_s(L"Error info CAN'T be READ !\n");
						}

						CSmartCOMPointer<IErrorInfo>			InterfaceIErrorInfo2=NULL;

						// !!! Pokus o 2. vycitanie ERROR INFO hodi S_FALSE.
						if (GetErrorInfo(0,&InterfaceIErrorInfo2)!=S_FALSE)
						{
							bstr_t								Error;

							InterfaceIErrorInfo1->GetDescription(Error.GetAddress());

							wprintf_s(L"ERROR [%s] !\n",Error.operator const wchar_t *());

							InterfaceIErrorInfo2=NULL;
						}
						else
						{
							wprintf_s(L"Error info CAN'T be READ !\n");
						}
					}

					InterfaceISupportErrorInfo=NULL;
				}
			}

			InterfaceExceptionTest=NULL;
		}

		Interface=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT !\n");
	}
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	CHelpers::SafeMain();

	CoInitialize(NULL);

	try
	{
		//ThreadTest();
		//TestCOM1();
		//TestCOM2();
		//TestCOM3();
		//TestCOM4();
		TestCOM5();
	}
	catch(...)
	{
		wprintf_s(L"FATAL EXCEPTION !!!\n");
	}

	CoUninitialize();

	CHelpers::ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------------------------------