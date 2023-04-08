#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <process.h>
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable: 4996)
//-------------------------------------------------------------------------------------------------------
CRITICAL_SECTION												MCritSec;
BOOL															MBInitialized=FALSE;
// !!! Must be SAME VALUE as in C# code.
int const														TABLE_SIZE=50;
//-------------------------------------------------------------------------------------------------------
class CNode
{
//-------------------------------------------------------------------------------------------------------
	public:
		char*													First;
        char*													Last;
        char*													Social;
        DWORD													Age;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
class CTable
{
//-------------------------------------------------------------------------------------------------------
	public:
		CNode*													Nodes[TABLE_SIZE];
		int*													Aux;
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
extern "C"
{
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) void InitBuffer(BYTE* Ptr, INT Size);
	// Pouziva sa CALLBACK==STDCALL CONVENTION.
	VOID CALLBACK MyCallback(__in  int Result);
	typedef VOID (CALLBACK* LPMyCallback)(int);
//-------------------------------------------------------------------------------------------------------
unsigned int WINAPI ThreadFunction(void* Param)
{
	LPMyCallback		Callback=(LPMyCallback) Param;

	wprintf_s(L"WORKER THREAD STATED !\n");

	Sleep(2*1000);

	Callback(10);

	wprintf_s(L"WORKER THREAD FINISHED !\n");

	return(0);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) VOID InitBuffer(BYTE* Ptr, INT Size)
	{
		Sleep(2000);

		for(int i=0;i<255;i++)
			Ptr[i]=i;
	}
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) VOID Init()
	{
		// Dummy.
	}
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) VOID Process(BYTE* Ptr)
	{
		// Dummy.
	}
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) VOID UnInit()
	{
		// Dummy.
	}
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) void AsyncProcess(LPMyCallback Callback)
	{
		_beginthreadex(NULL,0,ThreadFunction,Callback,0,NULL);
	}
//-------------------------------------------------------------------------------------------------------
    __declspec(dllexport) void GetDate(wchar_t* DateString)
	{
		SYSTEMTIME			Time;

		// Umyselne alokujem pamat, ktoru uz nevycistim.
		wchar_t*			Temp=new wchar_t[100];

		GetSystemTime(&Time);

		wprintf_s(Temp,L"%02d-%02d-%04d",Time.wDay,Time.wMonth,Time.wYear);

		// Prekopirujem pamat do navratovej hodnoty (premenna DateString), ale TEMP nezmazem.
		// !!! Tu sa NEDA pouzit wcscpy_s(), lebo velkost pamate je manageovana P/Invoke a C++ nema sancu zistit jej velkost - ktora je aj tak vdaka pouzitiu StringBuilder ??? asi dynamicka.
		wcscpy(DateString,Temp);
		
		//delete[](Temp);	
	}
//-------------------------------------------------------------------------------------------------------
    __declspec(dllexport) void MyFunc(BYTE* Pointer)
	{
		CTable*		Table=(CTable*) Pointer;

		if (Table==NULL)
		{
			wprintf_s(L"NATIVE CODE: [%d] !\n","NULL");
			return;
		}

		for (int i=0;i<TABLE_SIZE;i++)
		{
			CNode*			Node=Table->Nodes[i];

			if (Node==NULL)
				return;

			printf_s("Name: [%s %s], Social: [%s], Age: [%d] !\n",Node->First,Node->Last,Node->Social,Node->Age);
		}
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------