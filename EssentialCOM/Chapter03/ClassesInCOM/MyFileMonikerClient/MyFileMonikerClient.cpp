//------------------------------------------------------------------------------------------------------
#pragma warning(disable:4995)
//------------------------------------------------------------------------------------------------------
#include <tchar.h>
#include <Windows.h>
#include <comdef.h>
#include <conio.h>
#include <crtdbg.h>
#include <process.h>
#include "..\MyFileMonikerServer\MyFileMonikerObject_h.h"
#include "Helpers\Helpers.h"
#include "Helpers\Lock.h"
#include "Helpers\CriticalSectionWrapper.h"
#include "Helpers\SmartCOMPointer.h"
#include "Helpers\SmartCOMPointer.cpp"
//------------------------------------------------------------------------------------------------------
void GetName(CSmartCOMPointer<IMyFileMonikerName> Interface)
{
	wchar_t														Buffer1[1024]={'\0'};
	wchar_t														Buffer2[1024]={'\0'};

	wchar_t*													FirstName=(wchar_t*) &Buffer1;
	wchar_t*													LastName=(wchar_t*) &Buffer2;
	int															Age=0;

	Interface->GetFirstName(_countof(Buffer1),(wchar_t**) &FirstName);
	Interface->GetLastName(_countof(Buffer2),(wchar_t**) &LastName);
	Interface->GetAge(&Age);

	wprintf_s(L"CLIENT - FirstName: [%s] !\n",FirstName);
	wprintf_s(L"CLIENT - LastName: [%s] !\n",LastName);
	wprintf_s(L"CLIENT - Age: [%d] !\n",Age);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void TestCOM(void)
{
	HRESULT														HR=E_FAIL;
	IMyFileMonikerName*											Interface11=NULL;
	IMyFileMonikerName*											Interface12=NULL;
	IMyFileMonikerName*											Interface21=NULL;
	IMyFileMonikerName*											Interface22=NULL;

	CLSID														ID11=CLSID_MyFileMonikerObject;
	CLSID														ID12=CLSID_MyFileMonikerObject;
	CLSID														ID21=CLSID_MyFileMonikerObject;
	CLSID														ID22=CLSID_MyFileMonikerObject;

	MULTI_QI													QI11={&IID_IMyFileMonikerName,0,0};
	MULTI_QI													QI12={&IID_IMyFileMonikerName,0,0};
	MULTI_QI													QI21={&IID_IMyFileMonikerName,0,0};
	MULTI_QI													QI22={&IID_IMyFileMonikerName,0,0};

	// 1. volanie FILE [Timmy.txt].
	if (SUCCEEDED(HR=CoGetInstanceFromFile(NULL,&ID11,NULL,CLSCTX_INPROC_SERVER,STGM_READWRITE,L"D:\\Programy\\.NET\\CSharp\\EssentialCOM\\Chapter03\\ClassesInCOM\\MyFileMonikerClient\\!Files\\Timmy.txt",1,&QI11)))
	{
		Interface11=(IMyFileMonikerName*) QI11.pItf;

		GetName(Interface11);

		ULONG													Counter=Interface11->Release();

		wprintf_s(L"COUNTER [%d] !\n",Counter);

		Interface11=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
	}

	// 2. volanie FILE [Timmy.txt].
	if (SUCCEEDED(HR=CoGetInstanceFromFile(NULL,&ID12,NULL,CLSCTX_INPROC_SERVER,STGM_READWRITE,L"D:\\Programy\\.NET\\CSharp\\EssentialCOM\\Chapter03\\ClassesInCOM\\MyFileMonikerClient\\!Files\\Timmy.txt",1,&QI12)))
	{
		Interface12=(IMyFileMonikerName*) QI12.pItf;

		GetName(Interface12);

		ULONG													Counter=Interface12->Release();

		wprintf_s(L"COUNTER [%d] !\n",Counter);

		Interface12=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
	}

	// 1. volanie FILE [Jenny.txt].
	if (SUCCEEDED(HR=CoGetInstanceFromFile(NULL,&ID21,NULL,CLSCTX_INPROC_SERVER,STGM_READWRITE,L"D:\\Programy\\.NET\\CSharp\\EssentialCOM\\Chapter03\\ClassesInCOM\\MyFileMonikerClient\\!Files\\Jenny.txt",1,&QI21)))
	{
		Interface21=(IMyFileMonikerName*) QI21.pItf;

		GetName(Interface21);

		ULONG													Counter=Interface21->Release();

		wprintf_s(L"COUNTER [%d] !\n",Counter);

		Interface21=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
	}

	// 2. volanie FILE [Jenny.txt].
	if (SUCCEEDED(HR=CoGetInstanceFromFile(NULL,&ID22,NULL,CLSCTX_INPROC_SERVER,STGM_READWRITE,L"D:\\Programy\\.NET\\CSharp\\EssentialCOM\\Chapter03\\ClassesInCOM\\MyFileMonikerClient\\!Files\\Jenny.txt",1,&QI22)))
	{
		Interface22=(IMyFileMonikerName*) QI22.pItf;

		GetName(Interface22);

		ULONG													Counter=Interface22->Release();

		wprintf_s(L"COUNTER [%d] !\n",Counter);

		Interface22=NULL;
	}
	else
	{
		wprintf_s(L"Can't create COM OBJECT [%s] !\n",CHelpers::PrepareLogMessage(L"ERROR",HR).c_str());
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
		TestCOM();
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