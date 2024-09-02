//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Helpers\MyDebug.h"
#include "Helpers\CString.h"
#include "Helpers\CException.h"
#include "Helpers\CHelpers.h"
// !!!!! SHARED HEADER definovany v DRIVER.
#include "..\ProcessProtector\SharedHeader.h"
#include "EOptions.h"
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
#define KPROTECT_DEVICE											0x8101
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_PROTECT_ADD_PID CTL_CODE(KPROTECT_DEVICE, CODE_PROTECT_ADD_PID, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PROTECT_REMOVE_PID CTL_CODE(KPROTECT_DEVICE, CODE_PROTECT_REMOVE_PID, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_PROTECT_REMOVE_ALL CTL_CODE(KPROTECT_DEVICE, CODE_PROTECT_REMOVE_ALL, METHOD_NEITHER, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool ParsePIDs(size_t NumberOfParameters, const char* Parameters[], vector<DWORD>& PIDs)
{
	for(size_t Index=0;Index<NumberOfParameters;++Index)
	{
		try
		{
			DWORD												PID;

			PID=stoi(Parameters[Index]);

			PIDs.push_back(PID);
		}
		catch(...)
		{
			return(false);
		}
	}

	return(true);
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
		if (argc<2)
		{
			wcout << L"USE [" MY_DRIVER_NAME L"Client.exe [add | remove | clear] [PID_1] ... [PID_N]]." << endl;
			break;
		}

		const char*												Command=argv[1];
		EOptions												Option=EOptions::E_UNKNOWN;
		vector<DWORD>											PIDs;

		if (_stricmp(Command,"add")==0)
		{
			Option=EOptions::E_ADD;
		}
		else if (_stricmp(Command,"remove")==0)
		{
			Option=EOptions::E_REMOVE;
		}
		else if (_stricmp(Command,"clear")==0)
		{
			Option=EOptions::E_CLEAR;
		}
		else
		{
			wcout << L"UNKNOWN OPTION. USE [" MY_DRIVER_NAME L"Client.exe [add | remove | clear] [PID_1] ... [PID_N]]." << endl;
			break;
		}

		if (Option==EOptions::E_ADD || Option==EOptions::E_REMOVE)
		{
			if (ParsePIDs(argc-2,argv+2,PIDs)==false)
			{
				wcout << L"Can't PARSE PID. USE [" MY_DRIVER_NAME L"Client.exe [add | remove | clear] [PID_1] ... [PID_N]]." << endl;
				break;
			}

			if (PIDs.size()==0)
			{
				wcout << L"No PIDs DEFINED. USE [" MY_DRIVER_NAME L"Client.exe [add | remove | clear] [PID_1] ... [PID_N]]." << endl;
				break;
			}
		}

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

		HANDLE													DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE | GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);

		if (DeviceHandle!=INVALID_HANDLE_VALUE)
		{
			if (Option==EOptions::E_ADD || Option==EOptions::E_REMOVE || Option==EOptions::E_CLEAR)
			{
				DWORD											BytesReturned=0;
				DWORD											Code=0;
				LPVOID											InputBuffer=nullptr;
				DWORD											InputBufferSize=0;

				if (Option==EOptions::E_ADD)
				{
					Code=IOCTL_PROTECT_ADD_PID;
					InputBuffer=PIDs.data();
					InputBufferSize=(static_cast<DWORD>(PIDs.size())*sizeof(DWORD));
				}
				else if (Option==EOptions::E_REMOVE)
				{
					Code=IOCTL_PROTECT_REMOVE_PID;
					InputBuffer=PIDs.data();
					InputBufferSize=(static_cast<DWORD>(PIDs.size())*sizeof(DWORD));
				}
				else if (Option==EOptions::E_CLEAR)
				{
					Code=IOCTL_PROTECT_REMOVE_ALL;
				}

				if (DeviceIoControl(DeviceHandle,Code,InputBuffer,InputBufferSize,nullptr,0,&BytesReturned,NULL)!=FALSE)
				{
					wcout << L"OPERATION DEVICE IO CONTROL SUCCEEDED - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
				}
				else
				{
					DWORD												Error=GetLastError();

					wcout << L"OPERATION DEVICE IO CONTROL FAILED - ERROR [" << Error << L"] !" << endl;
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