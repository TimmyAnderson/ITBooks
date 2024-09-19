//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Helpers\MyDebug.h"
#include "Helpers\CString.h"
#include "Helpers\CException.h"
#include "Helpers\CHelpers.h"
// !!!!! SHARED HEADER definovany v DRIVER.
#include "..\Timers\SharedHeader.h"
#include "EOperation.h"
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
#define IOCTL_TIMERS_SET_ONESHOT CTL_CODE(TIMERS_DEVICE, TIMERS_SET_ONESHOT, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_SET_PERIODIC CTL_CODE(TIMERS_DEVICE, TIMERS_SET_PERIODIC, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_GET_RESOLUTION CTL_CODE(TIMERS_DEVICE, TIMERS_GET_RESOLUTION, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_SET_HIRES CTL_CODE(TIMERS_DEVICE, TIMERS_SET_HIRES, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TIMERS_STOP CTL_CODE(TIMERS_DEVICE, TIMERS_STOP, METHOD_NEITHER, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintUsage(void)
{
	wcout << L"USE [" MY_DRIVER_NAME L"Client.exe [query | stop | set [hires] [interval(ms)] [period(ms)]]]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
	SafeMain();

	PrintLineSeparator();

	do
	{
		EOperation												Operation;
		bool													HighResolution=false;
		ULONG													Interval=0;
		ULONG													Period=0;

		if (argc<2)
		{
			PrintUsage();
			break;
		}

		if (_stricmp(argv[1],"query")==0)
		{
			Operation=EOperation::E_QUERY;
		}
		else if (_stricmp(argv[1],"set")==0)
		{
			int													Index=2;

			if (argc>Index)
			{
				if (_stricmp(argv[Index],"hires")==0)
				{
					HighResolution=true;
					Index++;
				}
			}

			if (argc>Index)
			{
				try
				{
					Interval=stoi(argv[Index]);
					Index++;
				}
				catch(...)
				{
					wcout << L"Can't parse INTERVAL." << endl;
					break;
				}
			}

			if (argc>Index)
			{
				try
				{
					Period=stoi(argv[Index]);
					Index++;
				}
				catch(...)
				{
					wcout << L"Can't parse PERIOD." << endl;
					break;
				}
			}

			Operation=EOperation::E_SET;
		}
		else if (_stricmp(argv[1],"stop")==0)
		{
			Operation=EOperation::E_STOP;
		}
		else
		{
			wcout << L"INVALID COMMAND." << endl;
			PrintUsage();
			break;
		}

		if (Operation==EOperation::E_QUERY)
		{
			wcout << L"OPERATION [QUERY]." << endl;
		}
		else if (Operation==EOperation::E_SET)
		{
			wcout << L"OPERATION [SET] HIGH RESOLUTION [" << HighResolution << L"] INTERVAL [" << Interval << L"] PERIOD [" << Period << L"]." << endl;
		}
		else if (Operation==EOperation::E_STOP)
		{
			wcout << L"OPERATION [STOP]." << endl;
		}

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

		HANDLE													Device=CreateFile(SymbolicLinkName,GENERIC_READ | GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

		if (Device==INVALID_HANDLE_VALUE)
		{
			DWORD												Error=GetLastError();

			wcout << L"Can't OPEN DEVICE. ERROR [" << Error << L"]." << endl;
			break;
		}

		if (Operation==EOperation::E_QUERY)
		{
			STimerResolution									Resolution;
			DWORD												Bytes;
			BOOL												Result=DeviceIoControl(Device,IOCTL_TIMERS_GET_RESOLUTION,nullptr,0,&Resolution,sizeof(Resolution),&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [QUERY] SUCCEEDED. BYTES [" << Bytes << L"] CURRENT [" << Resolution.MCurrent << L"] MINIMUM [" << Resolution.MMinimum << L"] MAXIMUM [" << Resolution.MMaximum << L"] INCREMENT [" << Resolution.MIncrement << L"]." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [QUERY] FAILED. ERROR [" << Error << L"]." << endl;
			}

		}
		else if (Operation==EOperation::E_SET)
		{
			DWORD												Bytes;
			SPeriodicTimer										Timer;

			Timer.MInterval=Interval;
			Timer.MPeriod=Period;

			BOOL												Result=DeviceIoControl(Device,(HighResolution==true) ? IOCTL_TIMERS_SET_HIRES : IOCTL_TIMERS_SET_PERIODIC,&Timer,sizeof(Timer),nullptr,0,&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [SET] SUCCEEDED. BYTES [" << Bytes << L"]." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [SET] FAILED. ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_STOP)
		{
			DWORD												Bytes;
			BOOL												Result=DeviceIoControl(Device,IOCTL_TIMERS_STOP,nullptr,0,nullptr,0,&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [STOP] SUCCEEDED. BYTES [" << Bytes << L"]." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [STOP] FAILED. ERROR [" << Error << L"]." << endl;
			}
		}

		CloseHandle(Device);
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------