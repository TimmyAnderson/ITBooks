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
#include "..\DeviceObjectStacksLayer2\SharedHeader.h"
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
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Ak DRIVER [DeviceObjectStacksLayer1] je ZAPNUTY a vytvori DEVICE OBJECT STACK [DeviceObjectStacksLayer1+DeviceObjectStacksLayer2], tak WINDOWS posle VZDY IRP do DRIVER [DeviceObjectStacksLayer1], aj napriek tomu, ze je smerovany do DRIVER [DeviceObjectStacksLayer2]. IRP ma STACK SIZE [2].
// !!!!! Ak DRIVER [DeviceObjectStacksLayer1] je VYPNUTY a vytvori DEVICE OBJECT STACK [DeviceObjectStacksLayer2], tak WINDOWS posle VZDY IRP do DRIVER [DeviceObjectStacksLayer2]. IRP ma STACK SIZE [1].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_IRP_PROCESS_IMMEDIATELY CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PROCESS_IMMEDIATELY,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_COPY_STACK_LOCATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_COPY_STACK_LOCATION,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_SKIP_STACK_LOCATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_SKIP_STACK_LOCATION,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_WITH_COMPLETION_ROUTINE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_WITH_COMPLETION_ROUTINE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_IRP_PASS_DOWN_ASYNCHRONOUS_PROCESSING CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRP_PASS_DOWN_ASYNCHRONOUS_PROCESSING,METHOD_BUFFERED,FILE_ANY_ACCESS)
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
			wcout << L"USE [DeviceObjectStacksLayer2Client.exe CODE]." << endl;
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

		const wchar_t*											SymbolicLinkName=LR"(\\.\DeviceObjectStacksLayer2)";

		if (Code==1)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_IRP_PROCESS_IMMEDIATELY);
		}
		else if (Code==2)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_IRP_PASS_DOWN_COPY_STACK_LOCATION);
		}
		else if (Code==3)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_IRP_PASS_DOWN_SKIP_STACK_LOCATION);
		}
		else if (Code==4)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_IRP_PASS_DOWN_WITH_COMPLETION_ROUTINE);
		}
		else if (Code==5)
		{
			CHelpers::SendAsynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_IRP_PASS_DOWN_ASYNCHRONOUS_PROCESSING);
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------