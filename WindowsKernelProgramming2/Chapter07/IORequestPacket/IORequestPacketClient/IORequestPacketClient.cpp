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
#include "..\IORequestPacket\SharedHeader.h"
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
#define IOCTL_TEST_DEBUG_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DEBUG_IRP,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_GET_STATUS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_GET_STATUS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_CLEAR_STATUS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_CLEAR_STATUS,METHOD_NEITHER,FILE_ANY_ACCESS)
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
			wcout << L"USE [IORequestPacketClient.exe CODE]." << endl;
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

		const wchar_t*											SymbolicLinkName=LR"(\\.\IORequestPacket)";

		if (Code==1)
		{
			// !!!!! CODE vyvola BREAKPOINT. Ak NIE JE pripojeny DEBUGGER, dojde k BUG CHECK.

			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_DEBUG_IRP);
		}
		else if (Code==2)
		{
			BYTE												Buffer[1000];
			constexpr DWORD										BufferSize=sizeof(Buffer);
			DWORD												BytesRead=0;

			ZeroMemory(Buffer,BufferSize);

			if (CHelpers::SendSynchronousReadRequest(SymbolicLinkName,Buffer,BufferSize,&BytesRead)==true)
			{
				wchar_t*										TypedBuffer=reinterpret_cast<wchar_t*>(Buffer);

				wcout << L"BUFFER [" << TypedBuffer << L"] BYTES READ [" << BytesRead << L"] !" << endl;
			}
		}
		else if (Code==3)
		{
			wchar_t												Buffer[]=L"Timmy WRITE.";
			constexpr DWORD										BufferSize=sizeof(Buffer);
			DWORD												BytesWritten=0;
			const BYTE*											TypedBuffer=reinterpret_cast<const BYTE*>(Buffer);

			if (CHelpers::SendSynchronousWriteRequest(SymbolicLinkName,TypedBuffer,BufferSize,&BytesWritten)==true)
			{
				wcout << L"BUFFER [" << Buffer << L"] BYTES WRITTEN [" << BytesWritten << L"] !" << endl;
			}
		}
		else if (Code==4)
		{
			SReadWriteStatistics								ReadWriteStatistics;
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_GET_STATUS,nullptr,0,reinterpret_cast<BYTE*>(&ReadWriteStatistics),sizeof(ReadWriteStatistics),&BytesReturned)==true)
			{
				wcout << L"READ WRITE STATISTICS - BYTES RETURNED [" << BytesReturned << L"] TOTAL READ BYTES [" << ReadWriteStatistics.GetTotalReadBytes() << L"] TOTAL WRITE BYTES [" << ReadWriteStatistics.GetTotalWriteBytes() << L"] !" << endl;
			}
			else
			{
				wcout << L"Can't READ READ WRITE STATISTICS !" << endl;
			}
		}
		else if (Code==5)
		{
			DWORD												BytesReturned;

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_CLEAR_STATUS,nullptr,0,nullptr,0,&BytesReturned)==true)
			{
				wcout << L"READ WRITE STATISTICS CLEARED - BYTES RETURNED [" << BytesReturned << L"] !" << endl;
			}
			else
			{
				wcout << L"Can't CLEAR READ WRITE STATISTICS !" << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------