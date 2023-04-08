#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <Wct.h>
//------------------------------------------------------------------------------
CRITICAL_SECTION	CS1;
CRITICAL_SECTION	CS2;
unsigned int		TID1;
unsigned int		TID2;
//------------------------------------------------------------------------------
unsigned int WINAPI DeadlockThread1(void* Param)
{
	wchar_t		Buffer[1024];
	int			Size=_countof(Buffer);

	StringCchPrintf(Buffer,Size,L"Before CS 1 !\n");
	WriteDebugText(Buffer);

	EnterCriticalSection(&CS1);

	// Na simulaciu DEAD-LOCK.
	Sleep(100);

	StringCchPrintf(Buffer,Size,L"Before CS 2 !\n");
	WriteDebugText(Buffer);

	EnterCriticalSection(&CS2);

	StringCchPrintf(Buffer,Size,L"INSIDE BOTH CS !\n");
	WriteDebugText(Buffer);

	LeaveCriticalSection(&CS2);

	LeaveCriticalSection(&CS1);

	StringCchPrintf(Buffer,Size,L"After BOTH LEAVES !\n");
	WriteDebugText(Buffer);

	return(0);
}
//------------------------------------------------------------------------------
unsigned int WINAPI DeadlockThread2(void* Param)
{
	wchar_t		Buffer[1024];
	int			Size=_countof(Buffer);

	StringCchPrintf(Buffer,Size,L"Before CS 2 !\n");
	WriteDebugText(Buffer);

	EnterCriticalSection(&CS2);

	// Na simulaciu DEAD-LOCK.
	Sleep(100);

	StringCchPrintf(Buffer,Size,L"Before CS 1 !\n");
	WriteDebugText(Buffer);

	EnterCriticalSection(&CS1);

	StringCchPrintf(Buffer,Size,L"INSIDE BOTH CS !\n");
	WriteDebugText(Buffer);

	LeaveCriticalSection(&CS2);

	LeaveCriticalSection(&CS1);

	StringCchPrintf(Buffer,Size,L"After BOTH LEAVES !\n");
	WriteDebugText(Buffer);

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void DetectDeadlocks(void)
{
	WriteDebugText(L"DEADLOCK DETECTION !");

	// Synchronna detekcia.
	HWCT			WCT=OpenThreadWaitChainSession(0,NULL);
	unsigned int	Handles[2]={TID1,TID2};
	wchar_t			Buffer[1024];
	int				Size=_countof(Buffer);

	if (WCT!=NULL)
	{
		WriteDebugText(L"OpenThreadWaitChainSession() SUCCEEDED !");

		for (int i=0;i<_countof(Handles);i++)
		{
			WAITCHAIN_NODE_INFO		Nodes[WCT_MAX_NODE_COUNT];
			DWORD					NodesCount=WCT_MAX_NODE_COUNT;
			BOOL					HasDeadlock=FALSE;

			// Pre dany TID ziskam informacie o DEADLOCK.
			if (GetThreadWaitChain(WCT,NULL,WCTP_GETINFO_ALL_FLAGS,Handles[i],&NodesCount,Nodes,&HasDeadlock)==TRUE)
			{
				StringCchPrintf(Buffer,Size,L"GetThreadWaitChain() SUCCEEDED for thread [%d] !\n",Handles[i]);
				WriteDebugText(Buffer);

				wprintf_s(L"\tHasDeadlock: [%d] !\n",HasDeadlock);
				wprintf_s(L"\tNodesCount: [%d] !\n",NodesCount);

				for (DWORD j=0;j<NodesCount;j++)
					wprintf_s(L"\t\tNodes[%d].ObjectType: [%d] !\n",j,Nodes[j].ObjectType);
			}
			else
			{
				StringCchPrintf(Buffer,Size,L"GetThreadWaitChain() FAILED for thread [%d] !\n",Handles[i]);
				WriteDebugText(Buffer);
			}
		}
	}
	else
		WriteDebugText(L"OpenThreadWaitChainSession() FAILED !");

	if (WCT!=NULL)
	{
		CloseThreadWaitChainSession(WCT);
		WriteDebugText(L"CloseThreadWaitChainSession() CALLED !");
		WCT=NULL;
	}
}
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				Handle1;
	HANDLE				Handle2;

	InitializeCriticalSection(&CS1);
	InitializeCriticalSection(&CS2);

	Handle1=(HANDLE)_beginthreadex(NULL,0,DeadlockThread1,NULL,0,&TID1);
	Handle2=(HANDLE)_beginthreadex(NULL,0,DeadlockThread2,NULL,0,&TID2);

	Sleep(1000);

	DetectDeadlocks();

	// !!! Nasilne ukoncim program.
	ShowExitLine();
	return;


	WaitForSingleObject(Handle1,INFINITE);
	WaitForSingleObject(Handle2,INFINITE);

	DeleteCriticalSection(&CS1);
	DeleteCriticalSection(&CS2);
	
	CloseHandle(Handle1);
	CloseHandle(Handle2);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	Test();

	return(0);
}
//------------------------------------------------------------------------------