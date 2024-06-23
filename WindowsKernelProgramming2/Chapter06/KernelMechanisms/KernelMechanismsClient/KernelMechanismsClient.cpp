//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
// !!!!! SHARED HEADER definovany v DRIVER.
#include "..\KernelMechanisms\SharedHeader.h"
//----------------------------------------------------------------------------------------------------------------------
#ifdef _MSC_VER
#pragma warning( disable : 4804 )
#pragma warning( disable : 6287 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 26478 )
#pragma warning( disable : 26498 )
#undef min
#undef max
#endif
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_IRQL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRQL,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_DPC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DPC,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_TIMER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_TIMER,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_CRITICAL_REGION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_CRITICAL_REGION,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_GUARDED_REGION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_GUARDED_REGION,METHOD_BUFFERED,FILE_ANY_ACCESS)
// !!!!! MODE MUSI byt nastaveny na VALUE [METHOD_NEITHER], aby BUFFER NEBOL MAPPED a tak do KERNEL MODE mohol byt zaslany INVALID BUFFER.
#define IOCTL_TEST_SEH_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_1,METHOD_NEITHER,FILE_ANY_ACCESS)
// !!!!! MODE MUSI byt nastaveny na VALUE [METHOD_NEITHER], aby BUFFER NEBOL MAPPED a tak do KERNEL MODE mohol byt zaslany INVALID BUFFER.
#define IOCTL_TEST_SEH_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_3 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_3,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_4 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_4,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_5 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_5,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_6 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_6,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_RAII_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_RAII_1,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_RAII_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_RAII_2,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_UNIQUE_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_UNIQUE_POINTER,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SYSTEM_CRASH CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SYSTEM_CRASH,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SYSTEM_THREADS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SYSTEM_THREADS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_INTERLOCKED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_INTERLOCKED,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_INTERLOCKED_LOCK_FREE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_INTERLOCKED_LOCK_FREE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WAIT_FOR_SINGLE_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WAIT_FOR_SINGLE_OBJECT,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WAIT_FOR_MULTIPLE_OBJECTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WAIT_FOR_MULTIPLE_OBJECTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_RECURSIVE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_RECURSIVE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_LOCKER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_LOCKER,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_ABANDONED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_ABANDONED,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_STATE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_STATE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEXES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_FAST_MUTEXES,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEMAPHORES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SEMAPHORES,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MANUAL_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MANUAL_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_AUTO_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_AUTO_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_NAMED_MANUAL_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_NAMED_MANUAL_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_NAMED_AUTO_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_NAMED_AUTO_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_READERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_READERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_WRITERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_WRITERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_READERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_AUTO_READERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_WRITERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_AUTO_WRITERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCKS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SPIN_LOCKS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCKS_IRQL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SPIN_LOCKS_IRQL,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_QUEUED_SPIN_LOCKS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_QUEUED_SPIN_LOCKS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WORK_ITEMS_STATIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WORK_ITEMS_STATIC,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WORK_ITEMS_DYNAMIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WORK_ITEMS_DYNAMIC,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	SafeMain();

	PrintLineSeparator();

	do
	{
		if (argc<2)
		{
			wcout << L"USE [KernelMechanismsClient.exe CODE]." << endl;
			break;
		}

		int														Code;

		try
		{
			Code=stoi(argv[1]);
		}
		catch(...)
		{
			wcout << L"Can't parse CODE." << endl;
			break;
		}

		wcout << L"CODE [" << Code << L"]." << endl;

		const wchar_t*											SymbolicLinkName=LR"(\\.\KernelMechanisms)";

		HANDLE													DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

		if (DeviceHandle!=INVALID_HANDLE_VALUE)
		{
			wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

			constexpr size_t									INPUT_BUFFER_SIZE=512;
			constexpr size_t									OUTPUT_BUFFER_SIZE=1024;

			BYTE												InputBuffer[INPUT_BUFFER_SIZE];
			BYTE												OutputBuffer[OUTPUT_BUFFER_SIZE];
			DWORD												BytesReturned=0;

			ZeroMemory(InputBuffer,sizeof(InputBuffer));
			ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

			if (Code==1)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_IRQL,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==2)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_DPC,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==3)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_TIMER,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==4)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_CRITICAL_REGION,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==5)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_GUARDED_REGION,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==6)
			{
				wchar_t											Text[]{L"Timmy Anderson"};
				const size_t									TextLengthInBytes=sizeof(Text);
				const size_t									TextLengthInChars=(TextLengthInBytes/sizeof(Text[0]));
				BYTE*											Buffer=new BYTE[TextLengthInBytes];

				wcscpy_s(reinterpret_cast<wchar_t*>(Buffer),TextLengthInChars,Text);

				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SEH_1,Buffer,TextLengthInBytes,OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BUFFER [" << reinterpret_cast<void*>(Buffer) << "] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}

				delete[](Buffer);
			}
			else if (Code==7)
			{
				wchar_t											Text[]{L"Timmy Anderson"};
				const size_t									TextLengthInBytes=sizeof(Text);
				const size_t									TextLengthInChars=(TextLengthInBytes/sizeof(Text[0]));
				BYTE*											Buffer=new BYTE[TextLengthInBytes];

				wcscpy_s(reinterpret_cast<wchar_t*>(Buffer),TextLengthInChars,Text);

				// !!!!! BUFFER sa UMYSELNE vymaze, aby bol do KERNEL MODE poslany NEPLATNY BUFFER.
				delete[](Buffer);

				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SEH_2,Buffer,TextLengthInBytes,OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BUFFER [" << reinterpret_cast<void*>(Buffer) << "] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==8)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SEH_3,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==9)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SEH_4,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==10)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SEH_5,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==11)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SEH_6,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==12)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_RAII_1,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==13)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_RAII_2,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==14)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_UNIQUE_POINTER,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			// !!!!! CODE vykona SYSTEM CRASH.
			else if (Code==15)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SYSTEM_CRASH,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==16)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SYSTEM_THREADS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==17)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_INTERLOCKED,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==18)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_INTERLOCKED_LOCK_FREE,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==19)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_WAIT_FOR_SINGLE_OBJECT,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==20)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_WAIT_FOR_MULTIPLE_OBJECTS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==21)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_MUTEXES,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==22)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_MUTEXES_RECURSIVE,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==23)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_MUTEXES_LOCKER,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==24)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_MUTEXES_ABANDONED,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==25)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_MUTEXES_STATE,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==26)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_FAST_MUTEXES,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==27)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SEMAPHORES,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==28)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_MANUAL_RESET_EVENTS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==29)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_AUTO_RESET_EVENTS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==30)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_NAMED_MANUAL_RESET_EVENTS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==31)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_NAMED_AUTO_RESET_EVENTS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==32)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_EXECUTIVE_RESOURCES_READERS_FIRST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==33)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_EXECUTIVE_RESOURCES_WRITERS_FIRST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==34)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_READERS_FIRST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==35)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_WRITERS_FIRST,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==36)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SPIN_LOCKS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==37)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_SPIN_LOCKS_IRQL,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==38)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_QUEUED_SPIN_LOCKS,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==39)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_WORK_ITEMS_STATIC,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}
			else if (Code==40)
			{
				if (DeviceIoControl(DeviceHandle,IOCTL_TEST_WORK_ITEMS_DYNAMIC,InputBuffer,sizeof(InputBuffer),OutputBuffer,sizeof(OutputBuffer),&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"IO CONTROL SUCCESSFULLY SENT - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"Can't SEND IO CONTROL - ERROR [" << Error << L"] !" << endl;
				}
			}

			CloseHandle(DeviceHandle);
		}
		else
		{
			DWORD												Error=GetLastError();

			wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------