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
#include "..\Tables\SharedHeader.h"
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
#define IOCTL_TABLES_GET_PROCESS_COUNT CTL_CODE(TABLES_DEVICE, TABLES_GET_PROCESS_COUNT, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TABLES_GET_PROCESS_BY_ID CTL_CODE(TABLES_DEVICE, TABLES_GET_PROCESS_BY_ID, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TABLES_GET_PROCESS_BY_INDEX CTL_CODE(TABLES_DEVICE, TABLES_GET_PROCESS_BY_INDEX, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_TABLES_DELETE_ALL CTL_CODE(TABLES_DEVICE, TABLES_DELETE_ALL, METHOD_NEITHER, FILE_ANY_ACCESS)
#define IOCTL_TABLES_GET_ALL CTL_CODE(TABLES_DEVICE, TABLES_GET_ALL, METHOD_OUT_DIRECT, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintUsage(void)
{
	wcout << L"USE [" MY_DRIVER_NAME L"Client.exe [count | get [PID] | geti [INDEX] | getall | delete | help]." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void DisplayProcessData(const SProcessData& ProcessData)
{
	wcout << L"PID [" << ProcessData.MID << L"]." << endl;
	wcout << L"\tREGISTRY SET VALUE [" << ProcessData.MRegistrySetValueOperations << L"]." << endl;
	wcout << L"\tREGISTRY DELETE [" << ProcessData.MRegistryDeleteOperations << L"]." << endl;
	wcout << L"\tREGISTRY CREATE KEY [" << ProcessData.MRegistryCreateKeyOperations << L"]." << endl;
	wcout << L"\tREGISTRY RENAME [" << ProcessData.MRegistryRenameOperations << L"]." << endl;
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
		if (argc<=1)
		{
			wcout << L"INVALID COMMAND." << endl;
			PrintUsage();
			break;
		}

		EOperation												Operation;
		ULONG													PID=0;
		ULONG													ProcessIndex=0;

		if (_stricmp(argv[1],"count")==0)
		{
			wcout << L"OPERATION [GET PROCESS COUNT]." << endl;

			Operation=EOperation::E_GET_PROCESS_COUNT;
		}
		else if (_stricmp(argv[1],"get")==0)
		{
			if (argc>2)
			{
				try
				{
					PID=stoi(argv[2]);
				}
				catch(...)
				{
					wcout << L"Can't parse PID." << endl;
					break;
				}
			}

			wcout << L"OPERATION [GET PROCESS BY ID]." << endl;

			Operation=EOperation::E_GET_PROCESS_BY_ID;
		}
		else if (_stricmp(argv[1],"geti")==0)
		{
			if (argc>2)
			{
				try
				{
					ProcessIndex=stoi(argv[2]);
				}
				catch(...)
				{
					wcout << L"Can't parse INDEX." << endl;
					break;
				}
			}

			wcout << L"OPERATION [GET PROCESS BY INDEX]." << endl;

			Operation=EOperation::E_GET_PROCESS_BY_INDEX;
		}
		else if (_stricmp(argv[1],"getall")==0)
		{
			wcout << L"OPERATION [GET ALL PROCESSES]." << endl;

			Operation=EOperation::E_GET_ALL_PROCESSES;
		}
		else if (_stricmp(argv[1],"delete")==0)
		{
			wcout << L"OPERATION [DELETE ALL]." << endl;

			Operation=EOperation::E_DELETE_ALL;
		}
		else if (_stricmp(argv[1],"help")==0)
		{
			wcout << L"OPERATION [HELP]." << endl;

			Operation=EOperation::E_HELP;
		}
		else
		{
			wcout << L"INVALID COMMAND." << endl;
			PrintUsage();
			break;
		}

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

		HANDLE													Device=CreateFile(SymbolicLinkName,GENERIC_READ | GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

		if (Device==INVALID_HANDLE_VALUE)
		{
			DWORD												Error=GetLastError();

			wcout << L"Can't OPEN DEVICE. ERROR [" << Error << L"]." << endl;
			break;
		}

		if (Operation==EOperation::E_GET_PROCESS_COUNT)
		{
			DWORD												Bytes;
			ULONG												Count;
			BOOL												Result=DeviceIoControl(Device,IOCTL_TABLES_GET_PROCESS_COUNT,nullptr,0,&Count,sizeof(Count),&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [GET PROCESS COUNT] SUCCEEDED. BYTES [" << Bytes << L"] PROCESS COUNT [" << Count << L"]." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [GET PROCESS COUNT] FAILED. ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_GET_PROCESS_BY_ID)
		{
			DWORD												Bytes;
			SProcessData										Data;
			BOOL												Result=DeviceIoControl(Device,IOCTL_TABLES_GET_PROCESS_BY_ID,&PID,sizeof(PID),&Data,sizeof(Data),&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [DELETE PROCESS BY ID] SUCCEEDED. BYTES [" << Bytes << L"]." << endl;

				DisplayProcessData(Data);
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [DELETE PROCESS BY ID] FAILED. ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_GET_PROCESS_BY_INDEX)
		{
			DWORD												Bytes;
			SProcessData										Data;
			BOOL												Result=DeviceIoControl(Device,IOCTL_TABLES_GET_PROCESS_BY_INDEX,&ProcessIndex,sizeof(ProcessIndex),&Data,sizeof(Data),&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [DELETE PROCESS BY INDEX] SUCCEEDED. BYTES [" << Bytes << L"]." << endl;

				DisplayProcessData(Data);
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [DELETE PROCESS BY INDEX] FAILED. ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_GET_ALL_PROCESSES)
		{
			DWORD												Bytes;
			DWORD												Count=0;
			BOOL												Result=DeviceIoControl(Device,IOCTL_TABLES_GET_PROCESS_COUNT,nullptr,0,&Count,sizeof(Count),&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [GET ALL PROCESSES] SUCCEEDED. BYTES [" << Bytes << L"] COUNT [" << Count << L"]." << endl;

				if (Count>0)
				{
					unique_ptr<SProcessData[]>					Data=make_unique<SProcessData[]>(Count);

					Result=DeviceIoControl(Device,IOCTL_TABLES_GET_ALL,nullptr,0,Data.get(),Count*sizeof(SProcessData),&Bytes,nullptr);

					if (Result==TRUE)
					{
						DWORD									RealCount=(Bytes/sizeof(SProcessData));

						wcout << L"OPERATION [GET ALL PROCESSES] SUCCEEDED. BYTES [" << Bytes << L"] PROCESS COUNT [" << RealCount << L"]." << endl;

						for(DWORD Index=0;Index<RealCount;Index++)
						{
							const SProcessData&					ProcessData=Data[Index];

							DisplayProcessData(ProcessData);
						}
					}
					else
					{
						DWORD									Error=GetLastError();
	
						wcout << L"OPERATION [GET ALL PROCESSES] FAILED. ERROR [" << Error << L"]." << endl;
					}
				}
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [GET ALL PROCESSES] FAILED. ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_DELETE_ALL)
		{
			DWORD												Bytes;
			BOOL												Result=DeviceIoControl(Device,IOCTL_TABLES_DELETE_ALL,nullptr,0,nullptr,0,&Bytes,nullptr);

			if (Result==TRUE)
			{
				wcout << L"OPERATION [DELETE ALL] SUCCEEDED. BYTES [" << Bytes << L"]." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION [DELETE ALL] FAILED. ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_HELP)
		{
			PrintUsage();
		}

		CloseHandle(Device);
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------