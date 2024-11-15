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
#include "..\DeleteProtector\SharedHeader.h"
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
#define IOCTL_SET_EXTENSIONS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SET_EXTENSIONS,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void PrintUsage(void)
{
	wcout << L"USE [" MY_DRIVER_NAME L"Client.exe {1 EXTENSIONS} {2 FILE_NAME} {3 FILE_NAME} {4 FILE_NAME}]." << endl;
	wcout << L"1 - SET EXTENSIONS, 2 - DELETE FILE by FUNCTION [DeleteFile()], 3 - DELETE FILE by FUNCTION [CreateFile()], 4 - DELETE FILE by FUNCTION [SetFileInformationByHandle()]." << endl;
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
		if (argc<3)
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

		if (Operation==EOperation::E_SET_EXTENSION)
		{
			wstring												Extensions=ConvertStringToWideString(argv[2]);

			if (Extensions.back()!=L';')
			{
				Extensions+=L";";
			}

			const wchar_t*										SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;
			DWORD												Code=IOCTL_SET_EXTENSIONS;
			BYTE*												InputBuffer=((BYTE*)Extensions.data());
			DWORD												InputBufferSize=((DWORD)((Extensions.length()+1)*sizeof(wchar_t)));
			BYTE*												OutputBuffer=nullptr;
			DWORD												OutputBufferSize=0;
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
			{
				wcout << L"EXTENSIONS [" << Extensions << L"] are PROTECTED." << endl;
			}
			else
			{
				wcout << L"!!!!! EXTENSIONS [" << Extensions << L"] FAILED to be PROTECTED." << endl;
			}
		}
		else if (Operation==EOperation::E_DELETE_FILE_BY_DELETE_FILE)
		{
			wstring												FileName=ConvertStringToWideString(argv[2]);

			// !!! FILE sa vymaze volanim FUNCTION [DeleteFile()].
			BOOL												Success=DeleteFile(FileName.c_str());

			if (Success==TRUE)
			{
				wcout << L"FILE [" << FileName << L"] was SUCCESSFULLY DELETED." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"FILE [" << FileName << L"] FAILED to DELETE with ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_DELETE_FILE_BY_CREATE_FILE)
		{
			wstring												FileName=ConvertStringToWideString(argv[2]);

			// !!! Pri nastaveni FLAG [FILE_FLAG_DELETE_ON_CLOSE] bude FILE DELETED pri uzatvoreni HANDLE.
			HANDLE												Handle=CreateFile(FileName.c_str(),DELETE,0,nullptr,OPEN_EXISTING,FILE_FLAG_DELETE_ON_CLOSE,nullptr);

			if (Handle!=INVALID_HANDLE_VALUE)
			{
				CloseHandle(Handle);

				wcout << L"FILE [" << FileName << L"] was SUCCESSFULLY DELETED." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"FILE [" << FileName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_DELETE_FILE_BY_SET_FILE_INFORMATION_BY_HANDLE)
		{
			wstring												FileName=ConvertStringToWideString(argv[2]);

			FILE_DISPOSITION_INFO								Info;

			Info.DeleteFile=TRUE;

			HANDLE												Handle=CreateFile(FileName.c_str(),DELETE,0,nullptr,OPEN_EXISTING,0,nullptr);

			if (Handle!=INVALID_HANDLE_VALUE)
			{
				// !!! FILE sa vymaze volanim FUNCTION [SetFileInformationByHandle()].
				BOOL											Success=SetFileInformationByHandle(Handle,FileDispositionInfo,&Info,sizeof(Info));

				if (Success==TRUE)
				{
					wcout << L"FILE [" << FileName << L"] was SUCCESSFULLY DELETED." << endl;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"FILE [" << FileName << L"] FAILED to DELETE with ERROR [" << Error << L"]." << endl;
				}

				CloseHandle(Handle);
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"FILE [" << FileName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
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