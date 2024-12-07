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
#include "..\MyHook\SharedHeader.h"
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
#define IOCTL_SET_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SET_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CLEAR_DEVICE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_CLEAR_DEVICE,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintUsage(void)
{
	wcout << L"USE [" MY_DRIVER_NAME L"Client.exe {set DRIVER_NAME} {clear}]." << endl;
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

		if (OperationName==L"set")
		{
			if (argc<3)
			{
				wcout << L"DEVICE NAME NOT SPECIFIED." << endl;
				PrintUsage();
				break;
			}

			DeviceName=ConvertStringToWideString(argv[2]);
			Operation=EOperation::E_SET_DEVICE;
		}
		else if (OperationName==L"clear")
		{
			Operation=EOperation::E_CLEAR_DEVICE;
		}
		else
		{
			wcout << L"INVALID OPERATION." << endl;
			PrintUsage();
			break;
		}

		if (Operation==EOperation::E_SET_DEVICE)
		{
			DWORD												Code=IOCTL_SET_DEVICE;
			BYTE*												InputBuffer=((BYTE*)DeviceName.data());
			DWORD												InputBufferSize=((DWORD)((DeviceName.length()+1)*sizeof(wchar_t)));
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"FILTER DRIVER SET DEVICE [" << DeviceName << L"]." << endl;
			}
			else
			{
				wcout << L"!!!!! FILTER DRIVED FAILED to ADD DEVICE [" << DeviceName << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_CLEAR_DEVICE)
		{
			DWORD												Code=IOCTL_CLEAR_DEVICE;
			BYTE*												InputBuffer=nullptr;
			DWORD												InputBufferSize=0;
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;
			
			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"FILTER DRIVER CLEARED DEVICE." << endl;
			}
			else
			{
				wcout << L"!!!!! FILTER DRIVED FAILED to CLEAR DEVICE." << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------