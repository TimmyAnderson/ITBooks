#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
//------------------------------------------------------------------------------
void Test1(void)
{
	wprintf_s(L"PARENT ID: [%d] !\n",GetCurrentProcessId());

	BOOL					BInJob=FALSE;

	// Zistim ci proces uz nie je v JOB.
	IsProcessInJob(GetCurrentProcess(), NULL, &BInJob);

	if (BInJob==TRUE)
	{
		wprintf_s(L"Process is ALREADY IN JOB !\n");
		return;
	}

	// Vytvorim JOB.
	HANDLE			HJOB=CreateJobObject(NULL, L"TIMMY");

	// !!! Definujem ZAKLADNE omedzenia pre JOB.
	JOBOBJECT_BASIC_LIMIT_INFORMATION	JOBLI={ 0 };

	// Definujem obmedzenie na PRIORITU.
	JOBLI.PriorityClass=IDLE_PRIORITY_CLASS;

	// Defnujme ombedzenie na 5 skund ako MAXIMUM, ktore proces dostane.
	JOBLI.PerJobUserTimeLimit.QuadPart=50000;

	// A este nastavim FLAGS.
	JOBLI.LimitFlags=JOB_OBJECT_LIMIT_PRIORITY_CLASS | JOB_OBJECT_LIMIT_JOB_TIME;

	// Zaradim zoznam obmedzeni pre JOB.
	SetInformationJobObject(HJOB, JobObjectBasicLimitInformation, &JOBLI, sizeof(JOBLI));

	// !!! Definujem omedzenia na GUI pre JOB.
	JOBOBJECT_BASIC_UI_RESTRICTIONS		JOBUIR;

	JOBUIR.UIRestrictionsClass=JOB_OBJECT_UILIMIT_NONE;

	// Definujem obmedzenie, ze proces nemoze spravit LOG-OFF.
	JOBUIR.UIRestrictionsClass|=JOB_OBJECT_UILIMIT_EXITWINDOWS;

	// Definujem obmedzenie, ze proces nemoze pristupovat k USER objektom.
	JOBUIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_HANDLES;

	// Zaradim zoznam obmedzeni pre JOB.
	SetInformationJobObject(HJOB, JobObjectBasicUIRestrictions, &JOBUIR, sizeof(JOBUIR));

	STARTUPINFO				SI={sizeof(SI)};
	PROCESS_INFORMATION		PI;
	BOOL					BResult=FALSE;
	wchar_t					CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter05\\Jobs\\Child\\Debug\\Child.exe";

	// Vytvorim CHILD process.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI)!=FALSE)
	//if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, 0 | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI)!=FALSE)
	{
		wprintf_s(L"Child proces CREATED - ID: [%d] !\n",PI.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// Spustim SUSPENDED program.
		ResumeThread(PI.hThread);

		CloseHandle(PI.hThread);
	}

	// Pockam kym proces neskonci.
	HANDLE					Handles[2]={HJOB,PI.hProcess};
	DWORD					Ret=WaitForMultipleObjects(2, Handles, FALSE, INFINITE);

	if (Ret==WAIT_FAILED)
		wprintf(L"WAIT FAILED !\n");
	// !!! Skoci sem, ked sa JOB UKONCI a JOB sa skonci ked CHILD PROCES pracuje DLHSIE AKO 5 SEKUND - OMBEZDENIE JOBU.
	else if (Ret==(WAIT_OBJECT_0+0))
		wprintf(L"JOB FINISHED !\n");
	// Ak ukoncim CHILD proces, tak skoci sem.
	else if (Ret==(WAIT_OBJECT_0+1))
		wprintf(L"PROCESS FINISHED !\n");

	CloseHandle(PI.hProcess);
	CloseHandle(HJOB);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	wprintf_s(L"PARENT ID: [%d] !\n",GetCurrentProcessId());

	BOOL					BInJob=FALSE;

	// Zistim ci proces uz nie je v JOB.
	IsProcessInJob(GetCurrentProcess(), NULL, &BInJob);

	if (BInJob==TRUE)
	{
		wprintf_s(L"Process is ALREADY IN JOB !\n");
		return;
	}

	// Vytvorim JOB.
	HANDLE			HJOB=CreateJobObject(NULL, L"TIMMY");

	// !!! Definujem ZAKLADNE omedzenia pre JOB.
	JOBOBJECT_BASIC_LIMIT_INFORMATION	JOBLI={ 0 };

	// Definujem obmedzenie na PRIORITU.
	JOBLI.PriorityClass=IDLE_PRIORITY_CLASS;

	// A este nastavim FLAGS.
	JOBLI.LimitFlags=JOB_OBJECT_LIMIT_PRIORITY_CLASS;

	// Zaradim zoznam obmedzeni pre JOB.
	SetInformationJobObject(HJOB, JobObjectBasicLimitInformation, &JOBLI, sizeof(JOBLI));

	// !!! Definujem omedzenia na GUI pre JOB.
	JOBOBJECT_BASIC_UI_RESTRICTIONS		JOBUIR;

	JOBUIR.UIRestrictionsClass=JOB_OBJECT_UILIMIT_NONE;

	// Definujem obmedzenie, ze proces nemoze spravit LOG-OFF.
	JOBUIR.UIRestrictionsClass|=JOB_OBJECT_UILIMIT_EXITWINDOWS;

	// Definujem obmedzenie, ze proces nemoze pristupovat k USER objektom.
	JOBUIR.UIRestrictionsClass|=JOB_OBJECT_UILIMIT_HANDLES;

	// Zaradim zoznam obmedzeni pre JOB.
	SetInformationJobObject(HJOB, JobObjectBasicUIRestrictions, &JOBUIR, sizeof(JOBUIR));

	STARTUPINFO				SI={sizeof(SI)};
	PROCESS_INFORMATION		PI;
	BOOL					BResult=FALSE;
	wchar_t					CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter05\\Jobs\\Child\\Debug\\Child.exe";

	// Vytvorim CHILD process.
	// !!! Nato, aby mohol byt zaradeny do JOB musi byt NAJPRV VYTVORENY a SUSPENDED mode a az POTOM k nemu ASOCIOVANY JOB a nasledne moze proces pokracovat vo vykonavani.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI)!=FALSE)
	{
		wprintf_s(L"Child proces CREATED - ID: [%d] !\n",PI.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// !!! OKAMZITE UKONCI JOB.
		CloseHandle(HJOB);

		// Spustim SUSPENDED program.
		ResumeThread(PI.hThread);

		CloseHandle(PI.hThread);
	}

	// Pockam kym proces neskonci.
	HANDLE					Handles[1]={PI.hProcess};
	DWORD					Ret=WaitForMultipleObjects(1, Handles, FALSE, INFINITE);

	if (Ret==WAIT_FAILED)
		wprintf(L"WAIT FAILED !\n");
	else if (Ret==(WAIT_OBJECT_0))
		wprintf(L"PROCESS FINISHED !\n");

	CloseHandle(PI.hProcess);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	wprintf_s(L"PARENT ID: [%d] !\n",GetCurrentProcessId());

	BOOL					BInJob=FALSE;

	// Zistim ci proces uz nie je v JOB.
	IsProcessInJob(GetCurrentProcess(), NULL, &BInJob);

	if (BInJob==TRUE)
	{
		wprintf_s(L"Process is ALREADY IN JOB !\n");
		return;
	}

	// Vytvorim JOB.
	HANDLE			HJOB=CreateJobObject(NULL, L"TIMMY");

	// !!! Definujem ZAKLADNE omedzenia pre JOB.
	JOBOBJECT_BASIC_LIMIT_INFORMATION	JOBLI={ 0 };

	// Definujem obmedzenie na PRIORITU.
	JOBLI.PriorityClass=IDLE_PRIORITY_CLASS;

	// Defnujme ombedzenie na 5 skund ako MAXIMUM, ktore proces dostane.
	JOBLI.PerJobUserTimeLimit.QuadPart=50000;

	// A este nastavim FLAGS.
	JOBLI.LimitFlags=JOB_OBJECT_LIMIT_PRIORITY_CLASS | JOB_OBJECT_LIMIT_JOB_TIME;

	// Zaradim zoznam obmedzeni pre JOB.
	SetInformationJobObject(HJOB, JobObjectBasicLimitInformation, &JOBLI, sizeof(JOBLI));

	// !!! Definujem omedzenia na GUI pre JOB.
	JOBOBJECT_BASIC_UI_RESTRICTIONS		JOBUIR;

	JOBUIR.UIRestrictionsClass=JOB_OBJECT_UILIMIT_NONE;

	// Definujem obmedzenie, ze proces nemoze spravit LOG-OFF.
	JOBUIR.UIRestrictionsClass|=JOB_OBJECT_UILIMIT_EXITWINDOWS;

	// Definujem obmedzenie, ze proces nemoze pristupovat k USER objektom.
	JOBUIR.UIRestrictionsClass |= JOB_OBJECT_UILIMIT_HANDLES;

	// Zaradim zoznam obmedzeni pre JOB.
	SetInformationJobObject(HJOB, JobObjectBasicUIRestrictions, &JOBUIR, sizeof(JOBUIR));

	STARTUPINFO				SI={sizeof(SI)};
	PROCESS_INFORMATION		PI1;
	PROCESS_INFORMATION		PI2;
	BOOL					BResult=FALSE;
	wchar_t					CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter05\\Jobs\\Child\\Debug\\Child.exe";

	// Vytvorim CHILD process.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI1)!=FALSE)
	{
		wprintf_s(L"Child proces 1 CREATED - ID: [%d] !\n",PI1.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI1.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// Spustim SUSPENDED program.
		ResumeThread(PI1.hThread);

		CloseHandle(PI1.hThread);
	}

	// Vytvorim CHILD process.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI2)!=FALSE)
	{
		wprintf_s(L"Child proces 2 CREATED - ID: [%d] !\n",PI2.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI2.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// Spustim SUSPENDED program.
		ResumeThread(PI2.hThread);

		CloseHandle(PI2.hThread);
	}

	// Pockam kym proces neskonci.
	HANDLE					Handles[3]={HJOB,PI1.hProcess,PI2.hProcess};
	DWORD					Ret=WaitForMultipleObjects(3, Handles, FALSE, INFINITE);

	if (Ret==WAIT_FAILED)
		wprintf(L"WAIT FAILED !\n");
	// !!! Skoci sem, ked sa JOB UKONCI a JOB sa skonci ked CHILD PROCES pracuje DLHSIE AKO 5 SEKUND - OMBEZDENIE JOBU.
	else if (Ret==(WAIT_OBJECT_0+0))
		wprintf(L"JOB FINISHED !\n");
	// Ak ukoncim CHILD proces, tak skoci sem.
	else if (Ret==(WAIT_OBJECT_0+1))
		wprintf(L"PROCESS 1 FINISHED !\n");
	else if (Ret==(WAIT_OBJECT_0+2))
		wprintf(L"PROCESS 2 FINISHED !\n");

	CloseHandle(PI1.hProcess);
	CloseHandle(PI2.hProcess);
	CloseHandle(HJOB);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	BOOL					BInJob=FALSE;

	// Zistim ci proces uz nie je v JOB.
	IsProcessInJob(GetCurrentProcess(), NULL, &BInJob);

	if (BInJob==TRUE)
	{
		wprintf_s(L"Process is ALREADY IN JOB !\n");
		return;
	}

	// Vytvorim JOB.
	HANDLE			HJOB=CreateJobObject(NULL, L"TIMMY");

	if (AssignProcessToJobObject(HJOB,GetCurrentProcess())==FALSE)
		wprintf_s(L"FAILED to assign JOB to MYSELF !\n");

	if (OpenJobObject(JOB_OBJECT_ALL_ACCESS,FALSE,L"TIMMY")==FALSE)
		wprintf_s(L"PROCESS IS NOT IN JOB !\n");
	else
		wprintf_s(L"PROCESS IS IN JOB !\n");

	CloseHandle(HJOB);
}
//------------------------------------------------------------------------------
void Test5(void)
{
	wprintf_s(L"PARENT ID: [%d] !\n",GetCurrentProcessId());

	BOOL					BInJob=FALSE;

	// Zistim ci proces uz nie je v JOB.
	IsProcessInJob(GetCurrentProcess(), NULL, &BInJob);

	if (BInJob==TRUE)
	{
		wprintf_s(L"Process is ALREADY IN JOB !\n");
		return;
	}

	// Vytvorim JOB.
	HANDLE					HJOB=CreateJobObject(NULL, L"TIMMY");
	STARTUPINFO				SI={sizeof(SI)};
	PROCESS_INFORMATION		PI1;
	PROCESS_INFORMATION		PI2;
	BOOL					BResult=FALSE;
	wchar_t					CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter05\\Jobs\\Child\\Debug\\Child.exe";

	// Vytvorim CHILD process.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI1)!=FALSE)
	{
		wprintf_s(L"Child proces 1 CREATED - ID: [%d] !\n",PI1.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI1.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// Spustim SUSPENDED program.
		ResumeThread(PI1.hThread);

		CloseHandle(PI1.hThread);
	}

	// Vytvorim CHILD process.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI2)!=FALSE)
	{
		wprintf_s(L"Child proces 2 CREATED - ID: [%d] !\n",PI2.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI2.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// Spustim SUSPENDED program.
		ResumeThread(PI2.hThread);

		CloseHandle(PI2.hThread);
	}

	// Zaradim i seba sameho do JOBU.
	/*
	AssignProcessToJobObject(HJOB,GetCurrentProcess());

	if (OpenJobObject(JOB_OBJECT_ALL_ACCESS,FALSE,L"TIMMY")==FALSE)
		wprintf_s(L"PROCESS IS NOT IN JOB !\n");
	else
		wprintf_s(L"PROCESS IS IN JOB !\n");
	*/

	wprintf_s(L"Press any key to TERMINATE JOB !\n");
	_getch();

	TerminateJobObject(HJOB,0);

	CloseHandle(PI1.hProcess);
	CloseHandle(PI2.hProcess);
	CloseHandle(HJOB);
}
//------------------------------------------------------------------------------
void Test6(void)
{
	wprintf_s(L"PARENT ID: [%d] !\n",GetCurrentProcessId());

	BOOL					BInJob=FALSE;

	// Zistim ci proces uz nie je v JOB.
	IsProcessInJob(GetCurrentProcess(), NULL, &BInJob);

	if (BInJob==TRUE)
	{
		wprintf_s(L"Process is ALREADY IN JOB !\n");
		return;
	}

	// Vytvorim JOB.
	HANDLE					HJOB=CreateJobObject(NULL, L"TIMMY");
	STARTUPINFO				SI={sizeof(SI)};
	PROCESS_INFORMATION		PI1;
	PROCESS_INFORMATION		PI2;
	BOOL					BResult=FALSE;
	wchar_t					CommandLine[]=L"D:\\Programy\\.NET\\CSharp\\WindowsVia_C_CPP\\Chapter05\\Jobs\\Child\\Debug\\Child.exe";

	// Vytvorim CHILD process.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI1)!=FALSE)
	{
		wprintf_s(L"Child proces 1 CREATED - ID: [%d] !\n",PI1.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI1.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// Spustim SUSPENDED program.
		ResumeThread(PI1.hThread);

		CloseHandle(PI1.hThread);
	}

	// Vytvorim CHILD process.
	if (CreateProcess(NULL, CommandLine, NULL, NULL, FALSE, CREATE_SUSPENDED | CREATE_NEW_CONSOLE, NULL, NULL, &SI, &PI2)!=FALSE)
	{
		wprintf_s(L"Child proces 2 CREATED - ID: [%d] !\n",PI2.dwProcessId);

		// Priradim procesu JOB.
		if (AssignProcessToJobObject(HJOB, PI2.hProcess)==FALSE)
			wprintf_s(L"!!!!! Can't ASSING JOB !\n");

		// Spustim SUSPENDED program.
		ResumeThread(PI2.hThread);

		CloseHandle(PI2.hThread);
	}

	// Zaradim i seba sameho do JOBU.
	AssignProcessToJobObject(HJOB,GetCurrentProcess());

	if (OpenJobObject(JOB_OBJECT_ALL_ACCESS,FALSE,L"TIMMY")==FALSE)
		wprintf_s(L"PROCESS IS NOT IN JOB !\n");
	else
		wprintf_s(L"PROCESS IS IN JOB !\n");

	JOBOBJECT_BASIC_ACCOUNTING_INFORMATION	JI;
	DWORD									Size=0;

	// Ziskam informacie o JOBE.
	QueryInformationJobObject(HJOB,JobObjectBasicAccountingInformation,&JI,sizeof(JI),&Size);

	wprintf_s(L"\nActiveProcesses [%d] !\n\n",JI.ActiveProcesses);

	int										BufSize=10;
	int										ByteSize=sizeof(JOBOBJECT_BASIC_PROCESS_ID_LIST)+((BufSize-1)*sizeof(DWORD));
	BYTE*									Buffer=new BYTE[ByteSize];
	JOBOBJECT_BASIC_PROCESS_ID_LIST*		IDLIST=(JOBOBJECT_BASIC_PROCESS_ID_LIST*) Buffer;

	IDLIST->NumberOfAssignedProcesses=BufSize;
	IDLIST->NumberOfProcessIdsInList=BufSize;

	// Ziskam ID procesov v JOBE.
	BOOL RET=QueryInformationJobObject(HJOB,JobObjectBasicProcessIdList,IDLIST,ByteSize,&Size);

	for (DWORD i=0;i<IDLIST->NumberOfProcessIdsInList;i++)
		wprintf_s(L"\tProcess [%d] - ID: [%d] !\n",i+1,IDLIST->ProcessIdList[i]);

	delete[](Buffer);
	Buffer=NULL;

	wprintf_s(L"Press any key to TERMINATE JOB !\n");
	_getch();

	TerminateJobObject(HJOB,0);

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
	
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	//Test5();
	Test6();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------