//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
// !!!!! SHARED HEADER definovany v DRIVER.
#include "..\DriverFromStartToFinish\SThreadData.h"
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
int main(int argc, const char* argv[])
{
	SafeMain();

	PrintLineSeparator();

	do
	{
		if (argc<3)
		{
			wcout << L"USE [DriverFromStartToFinishClient.exe THREAD_ID PRIORITY]." << endl;
			break;
		}

		int														ThreadID;
		int														Priority;

		try
		{
			ThreadID=stoi(argv[1]);
		}
		catch(...)
		{
			wcout << L"Can't parse THREAD ID." << endl;
			break;
		}

		try
		{
			Priority=stoi(argv[2]);
		}
		catch(...)
		{
			wcout << L"Can't parse PRIORITY." << endl;
			break;
		}

		wcout << L"THREAD ID [" << ThreadID << L"] PRIORITY [" << Priority << L"]." << endl;

		const wchar_t*											SymbolicLinkName=LR"(\\.\DriverFromStartToFinish)";

		HANDLE													DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

		if (DeviceHandle!=INVALID_HANDLE_VALUE)
		{
			wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

			SThreadData											ThreadData;

			ThreadData.ThreadID=ThreadID;
			ThreadData.Priority=Priority;

			DWORD												BytesWritten;
			BOOL												Status=WriteFile(DeviceHandle,&ThreadData,sizeof(ThreadData),&BytesWritten,nullptr);

			if (Status==TRUE)
			{
				wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] WRITTEN [" << BytesWritten << L"] BYTES." << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to WRITE DATA with ERROR [" << Error << L"]." << endl;
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