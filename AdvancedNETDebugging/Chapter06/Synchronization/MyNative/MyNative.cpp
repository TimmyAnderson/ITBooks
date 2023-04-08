#include "stdafx.h"
#include <windows.h>
//-------------------------------------------------------------------------------------------------------
CRITICAL_SECTION												MCritSec;
BOOL															MBInitialized=FALSE;
//-------------------------------------------------------------------------------------------------------
extern "C"
{
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) void InitBuffer(BYTE* Ptr, INT Size);
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
		if(MBInitialized==FALSE)
		{
			InitializeCriticalSection(&MCritSec);
			MBInitialized=TRUE;
		}
	}
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) VOID Process(BYTE* Ptr)
	{
		EnterCriticalSection(&MCritSec);
	}
//-------------------------------------------------------------------------------------------------------
	__declspec(dllexport) VOID UnInit()
	{
		if(MBInitialized==TRUE)
		{
			// Tak ako Process() aj tato funkcia VLEZIE do CRITICAL SECTION. Ak nahodou je volana z ineho THREADU (napriklad FINALIZER), dojde k DEADLOCK.
			EnterCriticalSection(&MCritSec);

			// Do some work.

			LeaveCriticalSection(&MCritSec);

			DeleteCriticalSection(&MCritSec);

			MBInitialized=FALSE;
		}
	}
//-------------------------------------------------------------------------------------------------------
}
//-------------------------------------------------------------------------------------------------------