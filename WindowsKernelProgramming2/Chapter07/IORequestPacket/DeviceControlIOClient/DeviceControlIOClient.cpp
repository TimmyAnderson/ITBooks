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
#include "..\DeviceControlIO\SharedHeader.h"
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
#define IOCTL_TEST_DEBUG_DEVICE_CONTROL_METHOD_NEITHER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DEVICE_CONTROL_METHOD_NEITHER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_DEVICE_CONTROL_METHOD_BUFFERED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DEVICE_CONTROL_METHOD_BUFFERED,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_DEVICE_CONTROL_METHOD_IN_DIRECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DEVICE_CONTROL_METHOD_IN_DIRECT,METHOD_IN_DIRECT,FILE_ANY_ACCESS)
#define IOCTL_TEST_DEVICE_CONTROL_METHOD_OUT_DIRECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DEVICE_CONTROL_METHOD_OUT_DIRECT,METHOD_OUT_DIRECT,FILE_ANY_ACCESS)
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
			wcout << L"USE [DeviceControlIO.exe CODE]." << endl;
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

		const wchar_t*											SymbolicLinkName=LR"(\\.\DeviceControlIO)";

		if (Code==1)
		{
			wchar_t												Buffer[]=L"Timmy WRITE - NEITHER.";

			constexpr DWORD										INPUT_BUFFER_SIZE=sizeof(Buffer);

			BYTE*												InputBuffer=reinterpret_cast<BYTE*>(Buffer);

			constexpr size_t									OUTPUT_BUFFER_SIZE=1024;

			BYTE												OutputBuffer[OUTPUT_BUFFER_SIZE];
			DWORD												BytesReturned=0;

			ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_TEST_DEBUG_DEVICE_CONTROL_METHOD_NEITHER,InputBuffer,INPUT_BUFFER_SIZE,OutputBuffer,OUTPUT_BUFFER_SIZE,&BytesReturned)==true)
			{
				wchar_t*										TypedOutputBuffer=reinterpret_cast<wchar_t*>(OutputBuffer);

				wcout << L"BUFFER [" << TypedOutputBuffer << L"] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
			}
		}
		else if (Code==2)
		{
			wchar_t												Buffer[]=L"Timmy WRITE - BUFFERED.";

			constexpr DWORD										INPUT_BUFFER_SIZE=sizeof(Buffer);

			BYTE*												InputBuffer=reinterpret_cast<BYTE*>(Buffer);

			constexpr size_t									OUTPUT_BUFFER_SIZE=1024;

			BYTE												OutputBuffer[OUTPUT_BUFFER_SIZE];
			DWORD												BytesReturned=0;

			ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_TEST_DEVICE_CONTROL_METHOD_BUFFERED,InputBuffer,INPUT_BUFFER_SIZE,OutputBuffer,OUTPUT_BUFFER_SIZE,&BytesReturned)==true)
			{
				wchar_t*										TypedOutputBuffer=reinterpret_cast<wchar_t*>(OutputBuffer);

				wcout << L"BUFFER [" << TypedOutputBuffer << L"] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
			}
		}
		else if (Code==3)
		{
			wchar_t												Buffer[]=L"Timmy WRITE - IN DIRECT.";

			constexpr DWORD										INPUT_BUFFER_SIZE=sizeof(Buffer);

			BYTE*												InputBuffer=reinterpret_cast<BYTE*>(Buffer);

			constexpr size_t									OUTPUT_BUFFER_SIZE=1024;

			BYTE												OutputBuffer[OUTPUT_BUFFER_SIZE];
			DWORD												BytesReturned=0;

			ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

			wchar_t												OutputBufferData[]=L"Jenny Thompson WRITE - IN DIRECT.";

			// !!!!! V MODE [METHOD_IN_DIRECT] OUTPUT BUFFER zaroven sluzi aj ako INPUT BUFFER.
			CopyMemory(OutputBuffer,OutputBufferData,sizeof(OutputBufferData));

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_TEST_DEVICE_CONTROL_METHOD_IN_DIRECT,InputBuffer,INPUT_BUFFER_SIZE,OutputBuffer,OUTPUT_BUFFER_SIZE,&BytesReturned)==true)
			{
				wchar_t*										TypedOutputBuffer=reinterpret_cast<wchar_t*>(OutputBuffer);

				wcout << L"BUFFER [" << TypedOutputBuffer << L"] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
			}
		}
		else if (Code==4)
		{
			wchar_t												Buffer[]=L"Timmy WRITE - OUT DIRECT.";

			constexpr DWORD										INPUT_BUFFER_SIZE=sizeof(Buffer);

			BYTE*												InputBuffer=reinterpret_cast<BYTE*>(Buffer);

			constexpr size_t									OUTPUT_BUFFER_SIZE=1024;

			BYTE												OutputBuffer[OUTPUT_BUFFER_SIZE];
			DWORD												BytesReturned=0;

			ZeroMemory(OutputBuffer,sizeof(OutputBuffer));

			if (CHelpers::SendSynchronousDeviceIoControlRequest(SymbolicLinkName,IOCTL_TEST_DEVICE_CONTROL_METHOD_OUT_DIRECT,InputBuffer,INPUT_BUFFER_SIZE,OutputBuffer,OUTPUT_BUFFER_SIZE,&BytesReturned)==true)
			{
				wchar_t*										TypedOutputBuffer=reinterpret_cast<wchar_t*>(OutputBuffer);

				wcout << L"BUFFER [" << TypedOutputBuffer << L"] BYTES RETURNED [" << BytesReturned << L"] !" << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------