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
#include "..\DirectoryHiding\SharedHeader.h"
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
#define IOCTL_HIDE_PATH CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_HIDE_PATH,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SHOW_ALL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SHOW_ALL,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintUsage(void)
{
	wcout << L"USE [" MY_DRIVER_NAME L"Client.exe {1 PATH} {2}]." << endl;
	wcout << L"1 - ADD PATH, 2 - CLEAR ALL PATHS." << endl;
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

		EOperation												Operation;

		try
		{
			Operation=static_cast<EOperation>(stoi(argv[1]));
		}
		catch(...)
		{
			wcout << L"Can't parse OPERATION." << endl;
			PrintUsage();
			break;
		}

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

		if (Operation==EOperation::E_ADD_PATH)
		{
			if (argc<3)
			{
				wcout << L"INVALID NUMBER of PARAMETERS." << endl;
				PrintUsage();
				break;
			}

			wstring												Path=ConvertStringToWideString(argv[2]);

			DWORD												Code=IOCTL_HIDE_PATH;
			BYTE*												InputBuffer=((BYTE*)Path.data());
			DWORD												InputBufferSize=((DWORD)((Path.length()+1)*sizeof(wchar_t)));
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"PATH [" << Path << L"] is HIDDEN." << endl;
			}
			else
			{
				wcout << L"!!!!! PATH [" << Path << L"] FAILED to be HIDDEN." << endl;
			}
		}
		else if (Operation==EOperation::E_CLEAR_ALL_PATHS)
		{
			DWORD												Code=IOCTL_SHOW_ALL;
			BYTE*												InputBuffer=nullptr;
			DWORD												InputBufferSize=0;
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"ALL PATHS are VISIBLE." << endl;
			}
			else
			{
				wcout << L"!!!!! ALL PATHS FAILED to be VISIBLE." << endl;
			}
		}
		else
		{
			wcout << L"INVALID OPERATION." << endl;
			PrintUsage();
			break;
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------