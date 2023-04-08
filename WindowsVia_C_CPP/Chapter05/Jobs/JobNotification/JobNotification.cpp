#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
//------------------------------------------------------------------------------
void Test(void)
{
	wprintf_s(L"PARENT ID: [%d] !\n",GetCurrentProcessId());

	BOOL					BInJob=FALSE;

	IsProcessInJob(GetCurrentProcess(), NULL, &BInJob);

	if (BInJob==TRUE)
	{
		wprintf_s(L"Process is ALREADY IN JOB !\n");
		return;
	}

	HANDLE					CP=NULL;

	// Vytvorim Completition Port.
	if ((CP=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,0))==FALSE)
	{
		wprintf_s(L"ERROR - Can't create COMPLETION PORT !\n");
		return;
	}

	HANDLE									HJOB=CreateJobObject(NULL, L"TIMMY");
	JOBOBJECT_ASSOCIATE_COMPLETION_PORT		JOACP;

	JOACP.CompletionKey=NULL;
	JOACP.CompletionPort=CP;
                               
	// Asociujem Completion Port s JOB.
	if (SetInformationJobObject(HJOB, JobObjectAssociateCompletionPortInformation, &JOACP, sizeof(JOACP))==FALSE)
		wprintf_s(L"ERROR - Can't ASSOCIATE COMPLETION PORT !\n");

	STARTUPINFO				SI={sizeof(SI)};
	PROCESS_INFORMATION		PI1;
	PROCESS_INFORMATION		PI2;
	BOOL					BResult=FALSE;
	wchar_t					CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter05\\Jobs\\Child\\Debug\\Child.exe";

	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI1)!=FALSE)
	{
		wprintf_s(L"Child proces 1 CREATED - ID: [%d] !\n",PI1.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI1.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		ResumeThread(PI1.hThread);
		CloseHandle(PI1.hThread);
	}

	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI2)!=FALSE)
	{
		wprintf_s(L"Child proces 2 CREATED - ID: [%d] !\n",PI2.dwProcessId);

		if (AssignProcessToJobObject(HJOB, PI2.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		ResumeThread(PI2.hThread);
		CloseHandle(PI2.hThread);
	}

	/*
	// Zaradim i seba sameho do JOBU.
	AssignProcessToJobObject(HJOB,GetCurrentProcess());

	if (OpenJobObject(JOB_OBJECT_ALL_ACCESS,FALSE,L"TIMMY")==FALSE)
		wprintf_s(L"PROCESS IS NOT IN JOB !\n");
	else
		wprintf_s(L"PROCESS IS IN JOB !\n");
	*/

	int						Key;

	while(true)
	{
		BOOL				Ret;
		DWORD				NumberOfBytes=0;
		ULONG_PTR			Key;
		LPOVERLAPPED		O=NULL;
	
		// Skusim ci Completion Port neobsahuje EVENT.
		if ((Ret=GetQueuedCompletionStatus(CP,&NumberOfBytes,&Key,&O,100))==FALSE)
		{
			wprintf_s(L"Event NOT RECEIVED !\n");

			wprintf_s(L"Press 'X' to TERMINATE JOB, or KEY to RECEIVE event !\n");
			Key=_getch();

			if (Key=='x' || Key=='X')
				break;
		}
		else
		{
			// Parameter 'lpOverlapped' obsahuje ProcessID.
			DWORD			ProcessID=(DWORD) O;
			// Parameter 'lpOverlapped' obsahuje ProcessID.
			DWORD			Event=NumberOfBytes;

			wprintf_s(L"Event RECEIVED !!!\n");
			wprintf_s(L"\tProcess ID: [%d] !\n",ProcessID);
			wprintf_s(L"\tEvent: [%d] - ",Event);

			if (Event==JOB_OBJECT_MSG_END_OF_JOB_TIME)
				wprintf_s(L"JOB_OBJECT_MSG_END_OF_JOB_TIME !\n");
			else if (Event==JOB_OBJECT_MSG_END_OF_PROCESS_TIME)
				wprintf_s(L"JOB_OBJECT_MSG_END_OF_PROCESS_TIME !\n");
			else if (Event==JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT)
				wprintf_s(L"JOB_OBJECT_MSG_ACTIVE_PROCESS_LIMIT !\n");
			else if (Event==JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO)
				wprintf_s(L"JOB_OBJECT_MSG_ACTIVE_PROCESS_ZERO !\n");
			else if (Event==JOB_OBJECT_MSG_NEW_PROCESS)
				wprintf_s(L"JOB_OBJECT_MSG_NEW_PROCESS !\n");
			else if (Event==JOB_OBJECT_MSG_EXIT_PROCESS)
				wprintf_s(L"JOB_OBJECT_MSG_EXIT_PROCESS !\n");
			else
				wprintf_s(L"UNKNOWN !\n");
		}
	}

	TerminateJobObject(HJOB,0);

	CloseHandle(CP);
	CloseHandle(PI1.hProcess);
	CloseHandle(PI2.hProcess);
	CloseHandle(HJOB);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------