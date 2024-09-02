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
#include "..\ObjectAndRegistryNotifications\SharedHeader.h"
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
#define IOCTL_TEST_READ_OBJECT_NOTIFICATION_COUNTERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_READ_OBJECT_NOTIFICATION_COUNTERS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_READ_REGISTRY_NOTIFICATION_COUNTERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_READ_REGISTRY_NOTIFICATION_COUNTERS,METHOD_BUFFERED,FILE_ANY_ACCESS)
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
			wcout << L"USE [" MY_DRIVER_NAME L"Client.exe CODE]." << endl;
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

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

		if (Code==1)
		{
			SObjectNotificationStatistics						Buffer;
			constexpr DWORD										BufferSize=sizeof(Buffer);
			DWORD												BytesReturned;

			ZeroMemory(&Buffer,BufferSize);

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_TEST_READ_OBJECT_NOTIFICATION_COUNTERS,nullptr,0,reinterpret_cast<BYTE*>(&Buffer),BufferSize,&BytesReturned)==true)
			{
				wcout << L"PRE PROCESS CREATED [" << Buffer.MNumberOfPreProcessHandleCreatedCalled << L"] PRE PROCESS DUPLICATED [" << Buffer.MNumberOfPreProcessHandleDuplicatedCalled << L"] POST PROCESS CREATED [" << Buffer.MNumberOfPostProcessHandleCreatedCalled << L"] POST PROCESS DUPLICATED [" << Buffer.MNumberOfPostProcessHandleDuplicatedCalled << L"] PRE THREAD CREATED [" << Buffer.MNumberOfPreThreadHandleCreatedCalled << L"] PRE THREAD DUPLICATED [" << Buffer.MNumberOfPreThreadHandleDuplicatedCalled << L"] POST THREAD CREATED [" << Buffer.MNumberOfPostThreadHandleCreatedCalled << L"] POST THREAD DUPLICATED [" << Buffer.MNumberOfPostThreadHandleDuplicatedCalled << L"] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
			}
			else
			{
				wcout << L"Can't READ OBJECT NOTIFICATION STATISTICS !" << endl;
			}
		}
		else if (Code==2)
		{
			SRegistryNotificationStatistics						Buffer;
			constexpr DWORD										BufferSize=sizeof(Buffer);
			DWORD												BytesReturned;

			ZeroMemory(&Buffer,BufferSize);

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_TEST_READ_REGISTRY_NOTIFICATION_COUNTERS,nullptr,0,reinterpret_cast<BYTE*>(&Buffer),BufferSize,&BytesReturned)==true)
			{
				wcout << L"PRE CREATE KEY [" << Buffer.MNumberOfPreCreateKeyCalled << L"] POST CREATE KEY [" << Buffer.MNumberOfPostCreateKeyCalled << L"] PRE CREATE KEY EX [" << Buffer.MNumberOfPreCreateKeyExCalled << L"] POST CREATE KEY EX [" << Buffer.MNumberOfPostCreateKeyExCalled << L"] PRE DELETE VALUE KEY [" << Buffer.MNumberOfPreDeleteValueKeyCalled << L"] POST DELETE VALUE KEY [" << Buffer.MNumberOfPostDeleteValueKeyCalled << L"] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
			}
			else
			{
				wcout << L"Can't READ REGISTRY NOTIFICATION STATISTICS !" << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------