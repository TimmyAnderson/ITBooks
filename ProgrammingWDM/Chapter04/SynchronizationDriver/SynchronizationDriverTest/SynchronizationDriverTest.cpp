//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_READ_FILE CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_THREAD_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_IRQL_CHANGE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SPIN_LOCK_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SPIN_LOCK_WITH_THREADS_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x805,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_QUEUED_SPIN_LOCK_WITH_THREADS_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x806,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_WAIT_FOR_MULTIPLE_OBJECTS_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x807,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_MANUAL_RESET_EVENT_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x808,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_AUTO_RESET_EVENT_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x809,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SEMAPHORE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x810,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_MUTEX_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x811,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_MANUAL_RESET_TIMER_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x812,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_AUTO_RESET_TIMER_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x813,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DPC_TIMER_1_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x814,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DPC_TIMER_2_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x815,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DPC_TIMER_3_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x816,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_APC_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x817,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_FAST_MUTEX_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x818,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_EXECUTIVE_RESOURCE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x819,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_DOUBLY_LINKED_LIST CTL_CODE(FILE_DEVICE_UNKNOWN,0x820,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_SINGLY_LINKED_LIST CTL_CODE(FILE_DEVICE_UNKNOWN,0x821,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_ARITHMETIC_1 CTL_CODE(FILE_DEVICE_UNKNOWN,0x822,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_INTERLOCKED_ARITHMETIC_2 CTL_CODE(FILE_DEVICE_UNKNOWN,0x823,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
// !!! Moja CALLBACK FUNCTION, ktora sa vykona ako APC.
void CALLBACK MyAPCCallback(ULONG_PTR Param)
{
	wprintf_s(L"!!!!!!!!!! This is APC ROUTINE !!!!!!!!!!\n");
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
unsigned int WINAPI APCThreadFunction(void* Param)
{
	HANDLE														APCDestinationThreadHandle=(HANDLE) Param;

	wprintf_s(L"WORKER THREAD STARTED !\n");

	Sleep(5*1000);

	wprintf_s(L"WORKER THREAD is QUEUING APC to THREAD [%p] !\n",APCDestinationThreadHandle);

	// !!! Zaslem NORMAL USER MODE APC REQUEST do MAIN THREAD.
	// !!!!! Ako THREAD HANDLE sa NESMIE pouzivat PSEUDO THREAD HANDLE, ktory vracia FUNCTION GetCurrentThread(), ale SKUTOCNY THREAD HANDLE, ktory sa ziska pri vytvarani THREADU.
	QueueUserAPC(MyAPCCallback,APCDestinationThreadHandle,NULL);

	// !!!!! Aj volanie TerminateThread() sposobi prerusenie ALERTABLE WAIT v KERNEL MODE CODE.
	//TerminateThread(APCDestinationThreadHandle,0);

	wprintf_s(L"WORKER THREAD has QUEUED APC to THREAD [%p] !\n",APCDestinationThreadHandle);

	wprintf_s(L"WORKER THREAD FINISHED !\n");

	return(0);
}
//-------------------------------------------------------------------------------------------------------
unsigned int WINAPI CallDriverThreadFunction(void*)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	// !!!!! FUNCTION vracia PSEUDO THREAD HANDLE a NIE SKUTOCNY THREAD HANDLE.
	HANDLE														ThreadHandle=GetCurrentThread();

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		Sleep(1000);

		wprintf_s(L"DEVICE SUCCESSFULLY OPENED on THREAD [%p] !\n",ThreadHandle);

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_APC_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}

	return(0);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[512];
		BYTE													OutputBuffer[1024];
		DWORD													BytesReturned=0;

		ZeroMemory(InputBuffer,sizeof(InputBuffer));
		ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

		sprintf_s(InputBuffer,_countof(InputBuffer),"My name is Jenny Thompson !");
		wprintf_s(L"InputBuffer [%p], OutputBuffer [%p] !\n",InputBuffer,OutputBuffer);
		printf_s("InputBuffer [%s] !\n",InputBuffer);

		if (DeviceIoControl(Handle,IOCTL_READ_FILE,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT - BytesReturned [%d], OutputBuffer [%s] !\n",BytesReturned,(wchar_t*)OutputBuffer);
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test2(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_THREAD_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test3(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_IRQL_CHANGE_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test4(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SPIN_LOCK_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test5(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SPIN_LOCK_WITH_THREADS_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test6(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_QUEUED_SPIN_LOCK_WITH_THREADS_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test7(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_WAIT_FOR_MULTIPLE_OBJECTS_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test8(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_MANUAL_RESET_EVENT_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test9(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_AUTO_RESET_EVENT_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test10(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SEMAPHORE_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test11(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_MUTEX_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test12(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_MANUAL_RESET_TIMER_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test13(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_AUTO_RESET_TIMER_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test14(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_DPC_TIMER_1_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test15(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_DPC_TIMER_2_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test16(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_DPC_TIMER_3_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test17(void)
{
	HANDLE														ThreadHandle1=(HANDLE) _beginthreadex(NULL,0,CallDriverThreadFunction,NULL,0,NULL);
	// !!!!! CODE, ktory vola DRIVER som vytvoril v SEPARATNOM THREADE, aby som ziskal jeho SKUTOCNY THREAD HANDLE a NIE PSEUDO THREAD HANDLE, ktory vracia GetCurrentThread().
	HANDLE														ThreadHandle2=(HANDLE) _beginthreadex(NULL,0,APCThreadFunction,ThreadHandle1,0,NULL);

	wprintf_s(L"THREAD [%p] and THREAD [%p] CREATED !\n",ThreadHandle1,ThreadHandle2);

	WaitForSingleObject(ThreadHandle1,INFINITE);
	CloseHandle(ThreadHandle1);
	ThreadHandle1=NULL;

	WaitForSingleObject(ThreadHandle2,INFINITE);
	CloseHandle(ThreadHandle2);
	ThreadHandle2=NULL;

	wprintf_s(L"BOTH WORKER THREADS CLOSED !\n");
}
//-------------------------------------------------------------------------------------------------------
void Test18(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_FAST_MUTEX_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test19(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_EXECUTIVE_RESOURCE_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test20(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_INTERLOCKED_DOUBLY_LINKED_LIST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test21(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_INTERLOCKED_SINGLY_LINKED_LIST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test22(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_INTERLOCKED_ARITHMETIC_1,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
void Test23(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\SynchronizationDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_INTERLOCKED_ARITHMETIC_2,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
		{
			wprintf_s(L"IO CONTROL SUCCESSFULLY SENT !\n");
		}
		else
		{
			wprintf_s(L"Can't SEND IO CONTROL - ERROR [%d] !\n",GetLastError());
		}

		if (CloseHandle(Handle)!=FALSE)
		{
			wprintf_s(L"DEVICE SUCCESSFULLY CLOSED !\n");
		}
		else
		{
			wprintf_s(L"Can't CLOSE DEVICE - ERROR [%d] !\n",GetLastError());
		}
	}
	else
	{
		wprintf_s(L"Can't OPEN DEVICE - ERROR [%d] !\n",GetLastError());
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
int wmain(int argc, wchar_t* argv[])
{
	wprintf_s(L"ENTER VALUE (or 'q' to EXIT):\n");

	for(;;)
	{
		char													Buffer[100];

		fgets(Buffer,_countof(Buffer),stdin);

		if (strcmp(Buffer,"q\n")==0)
		{
			break;
		}
		else if (strcmp(Buffer,"1\n")==0)
		{
			Test1();
		}
		else if (strcmp(Buffer,"2\n")==0)
		{
			Test2();
		}
		else if (strcmp(Buffer,"3\n")==0)
		{
			Test3();
		}
		else if (strcmp(Buffer,"4\n")==0)
		{
			Test4();
		}
		else if (strcmp(Buffer,"5\n")==0)
		{
			Test5();
		}
		else if (strcmp(Buffer,"6\n")==0)
		{
			Test6();
		}
		else if (strcmp(Buffer,"7\n")==0)
		{
			Test7();
		}
		else if (strcmp(Buffer,"8\n")==0)
		{
			Test8();
		}
		else if (strcmp(Buffer,"9\n")==0)
		{
			Test9();
		}
		else if (strcmp(Buffer,"10\n")==0)
		{
			Test10();
		}
		else if (strcmp(Buffer,"11\n")==0)
		{
			Test11();
		}
		else if (strcmp(Buffer,"12\n")==0)
		{
			Test12();
		}
		else if (strcmp(Buffer,"13\n")==0)
		{
			Test13();
		}
		else if (strcmp(Buffer,"14\n")==0)
		{
			Test14();
		}
		else if (strcmp(Buffer,"15\n")==0)
		{
			Test15();
		}
		else if (strcmp(Buffer,"16\n")==0)
		{
			Test16();
		}
		else if (strcmp(Buffer,"17\n")==0)
		{
			Test17();
		}
		else if (strcmp(Buffer,"18\n")==0)
		{
			Test18();
		}
		else if (strcmp(Buffer,"19\n")==0)
		{
			Test19();
		}
		else if (strcmp(Buffer,"20\n")==0)
		{
			Test20();
		}
		else if (strcmp(Buffer,"21\n")==0)
		{
			Test21();
		}
		else if (strcmp(Buffer,"22\n")==0)
		{
			Test22();
		}
		else if (strcmp(Buffer,"23\n")==0)
		{
			Test23();
		}
		else if (strcmp(Buffer,"x1\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test1();
			}
		}
		else if (strcmp(Buffer,"x2\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test2();
			}
		}
		else if (strcmp(Buffer,"x3\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test3();
			}
		}
		else if (strcmp(Buffer,"x4\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test4();
			}
		}
		else if (strcmp(Buffer,"x5\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test5();
			}
		}
		else if (strcmp(Buffer,"x6\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test6();
			}
		}
		else if (strcmp(Buffer,"x7\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test7();
			}
		}
		else if (strcmp(Buffer,"x8\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test8();
			}
		}
		else if (strcmp(Buffer,"x9\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test9();
			}
		}
		else if (strcmp(Buffer,"x10\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test10();
			}
		}
		else if (strcmp(Buffer,"x11\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test11();
			}
		}
		else if (strcmp(Buffer,"x12\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test12();
			}
		}
		else if (strcmp(Buffer,"x13\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test13();
			}
		}
		else if (strcmp(Buffer,"x14\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test14();
			}
		}
		else if (strcmp(Buffer,"x15\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test15();
			}
		}
		else if (strcmp(Buffer,"x16\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test16();
			}
		}
		else if (strcmp(Buffer,"x17\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test17();
			}
		}
		else if (strcmp(Buffer,"x18\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test18();
			}
		}
		else if (strcmp(Buffer,"x19\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test19();
			}
		}
		else if (strcmp(Buffer,"x20\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test20();
			}
		}
		else if (strcmp(Buffer,"x21\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test21();
			}
		}
		else if (strcmp(Buffer,"x22\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test22();
			}
		}
		else if (strcmp(Buffer,"x23\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test23();
			}
		}
		else
		{
			system("cls");
			wprintf_s(L"ENTER VALUE (or 'q' to EXIT):\n");
		}
	}

	wprintf_s(L"Press any KEY to EXIT !\n");
	(void)_getch();

	return(0);
}
//-------------------------------------------------------------------------------------------------------