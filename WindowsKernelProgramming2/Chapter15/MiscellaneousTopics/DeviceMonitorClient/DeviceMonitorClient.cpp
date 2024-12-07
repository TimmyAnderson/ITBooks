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
#include "..\DeviceMonitor\SharedHeader.h"
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
#define IOCTL_DEVMON_ADD_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_DEVMON_ADD_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DEVMON_REMOVE_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_DEVMON_REMOVE_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_DEVMON_REMOVE_ALL_DEVICES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_DEVMON_REMOVE_ALL_DEVICES,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintUsage(void)
{
	wcout << L"USE [" MY_DRIVER_NAME L"Client.exe {add DEVICE_NAME} {remove DEVICE_NAME} {clear}]." << endl;
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
			wcout << L"INVALID COMMAND." << endl;
			PrintUsage();
			break;
		}

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;
		EOperation												Operation;
		wstring													OperationName=ConvertStringToWideString(argv[1]);
		wstring													DeviceName;

		if (OperationName==L"add")
		{
			if (argc<3)
			{
				wcout << L"DEVICE NAME NOT SPECIFIED." << endl;
				PrintUsage();
				break;
			}

			DeviceName=ConvertStringToWideString(argv[2]);
			Operation=EOperation::E_ADD_DEVICE;
		}
		else if (OperationName==L"remove")
		{
			if (argc<3)
			{
				wcout << L"DEVICE NAME NOT SPECIFIED." << endl;
				PrintUsage();
				break;
			}

			DeviceName=ConvertStringToWideString(argv[2]);
			Operation=EOperation::E_REMOVE_DEVICE;
		}
		else if (OperationName==L"clear")
		{
			Operation=EOperation::E_REMOVE_ALL_DEVICES;
		}
		else
		{
			wcout << L"INVALID OPERATION." << endl;
			PrintUsage();
			break;
		}

		if (Operation==EOperation::E_ADD_DEVICE)
		{
			DWORD												Code=IOCTL_DEVMON_ADD_DEVICE;
			BYTE*												InputBuffer=((BYTE*)DeviceName.data());
			DWORD												InputBufferSize=((DWORD)((DeviceName.length()+1)*sizeof(wchar_t)));
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"FILTER DRIVER ADDED DEVICE [" << DeviceName << L"]." << endl;
			}
			else
			{
				wcout << L"!!!!! FILTER DRIVED FAILED to ADD DEVICE [" << DeviceName << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_REMOVE_DEVICE)
		{
			DWORD												Code=IOCTL_DEVMON_REMOVE_DEVICE;
			BYTE*												InputBuffer=((BYTE*)DeviceName.data());
			DWORD												InputBufferSize=((DWORD)((DeviceName.length()+1)*sizeof(wchar_t)));
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"FILTER DRIVER REMOVED DEVICE [" << DeviceName << L"]." << endl;
			}
			else
			{
				wcout << L"!!!!! FILTER DRIVED FAILED to REMOVE DEVICE [" << DeviceName << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_REMOVE_ALL_DEVICES)
		{
			DWORD												Code=IOCTL_DEVMON_REMOVE_ALL_DEVICES;
			BYTE*												InputBuffer=nullptr;
			DWORD												InputBufferSize=0;
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;
			
			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"FILTER DRIVER REMOVED ALL DEVICES." << endl;
			}
			else
			{
				wcout << L"!!!!! FILTER DRIVED FAILED to REMOVE ALL DEVICES." << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------