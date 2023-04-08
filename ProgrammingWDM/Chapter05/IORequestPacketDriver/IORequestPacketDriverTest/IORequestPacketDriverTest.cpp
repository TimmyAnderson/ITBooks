//-------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <process.h>
#include <conio.h>
//-------------------------------------------------------------------------------------------------------
// Identifikatory IO OPERATIONS.
#define IOCTL_SIMPLE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_1_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_2_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x803,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_3_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x804,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_4_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x805,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_5_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x806,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_5_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x807,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_6_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x808,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_6_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x809,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_7_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x8010,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_7_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x811,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_8_FINISHED_SYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x812,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SCENARIO_8_FINISHED_ASYNCHRONOUSLY_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x813,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_IO_STACK_LOCATION_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x814,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_GET_DEVICE_OBJECT_POINTER_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x815,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_IRP_QUEUEING_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x816,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CANCEL_SAFE_IRP_QUEUE_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x817,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CANCEL_SYNCHRONOUS_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x818,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CANCEL_ASYNCHRONOUS_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x819,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_REMOTE_CANCEL_ASYNCHRONOUS_IRP_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x820,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DOUBLE_COMPLETION_ROUTINES_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x821,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x822,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_ASYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x823,METHOD_BUFFERED,FILE_ANY_ACCESS)
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void Test1(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

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

		if (DeviceIoControl(Handle,IOCTL_SIMPLE_TEST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		char													InputBuffer[]="My name is Timmy Anderson !";
		DWORD													NumberOfBytesWritten;

		if (WriteFile(Handle,InputBuffer,sizeof(InputBuffer),&NumberOfBytesWritten,NULL)!=FALSE)
		{
			wprintf_s(L"DATA SUCCESSFULLY WRITTEN - NumberOfBytesWritten [%d] !\n",NumberOfBytesWritten);
		}
		else
		{
			wprintf_s(L"Can't WRITE DATA - ERROR [%d] !\n",GetLastError());
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_1_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_2_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_3_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_4_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_5_FINISHED_SYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_5_FINISHED_ASYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_6_FINISHED_SYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_6_FINISHED_ASYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_7_FINISHED_SYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_7_FINISHED_ASYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_8_FINISHED_SYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SCENARIO_8_FINISHED_ASYNCHRONOUSLY_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_IO_STACK_LOCATION_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_GET_DEVICE_OBJECT_POINTER_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_IRP_QUEUEING_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
void Test18(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_CANCEL_SAFE_IRP_QUEUE_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_CANCEL_SYNCHRONOUS_IRP_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_CANCEL_ASYNCHRONOUS_IRP_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_REMOTE_CANCEL_ASYNCHRONOUS_IRP_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_DOUBLE_COMPLETION_ROUTINES_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_SYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
void Test24(void)
{
	HANDLE														Handle=CreateFile(L"\\\\.\\IORequestPacketDriver",GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);

	if (Handle!=INVALID_HANDLE_VALUE)
	{
		wprintf_s(L"DEVICE SUCCESSFULLY OPENED !\n");

		DWORD													BytesReturned=0;

		if (DeviceIoControl(Handle,IOCTL_ASYNCHRONOUS_IRP_COMPLETION_ROUTINE_NO_CALL_TEST,NULL,0,NULL,0,&BytesReturned,NULL)!=FALSE)
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
		else if (strcmp(Buffer,"24\n")==0)
		{
			Test24();
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
		else if (strcmp(Buffer,"x24\n")==0)
		{
			for (int Index=0;Index<1000;Index++)
			{
				printf_s("ITERATION [%d] !\n",Index);

				Test24();
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