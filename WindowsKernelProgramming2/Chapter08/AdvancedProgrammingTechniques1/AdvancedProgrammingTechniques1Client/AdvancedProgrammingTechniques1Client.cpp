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
#include "..\AdvancedProgrammingTechniques1\SharedHeader.h"
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
#define IOCTL_TEST_PS_CREATE_SYSTEM_THREAD CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_PS_CREATE_SYSTEM_THREAD,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_IO_CREATE_SYSTEM_THREAD CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IO_CREATE_SYSTEM_THREAD,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EX_ALLOCATE_POOL_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EX_ALLOCATE_POOL_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EX_ALLOCATE_POOL_3 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EX_ALLOCATE_POOL_3,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SECURE_POOL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SECURE_POOL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_GLOBAL_OPERATORS_NEW_DELETE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_GLOBAL_OPERATORS_NEW_DELETE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPECIFIC_TYPE_OPERATORS_NEW_DELETE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPECIFIC_TYPE_OPERATORS_NEW_DELETE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_OLD_LOOKASIDE_LIST_PAGED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_OLD_LOOKASIDE_LIST_PAGED,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_OLD_LOOKASIDE_LIST_NON_PAGED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_OLD_LOOKASIDE_LIST_NON_PAGED,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_NEW_LOOKASIDE_LIST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_NEW_LOOKASIDE_LIST,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEND_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEND_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEND_INTERNAL_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEND_INTERNAL_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_ZW_QUERY_SYSTEM_INFORMATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_ZW_QUERY_SYSTEM_INFORMATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_ZW_QUERY_INFORMATION_PROCESS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_ZW_QUERY_INFORMATION_PROCESS,METHOD_NEITHER,FILE_ANY_ACCESS)
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
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_PS_CREATE_SYSTEM_THREAD);
		}
		else if (Code==2)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_IO_CREATE_SYSTEM_THREAD);
		}
		else if (Code==3)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EX_ALLOCATE_POOL_2);
		}
		else if (Code==4)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EX_ALLOCATE_POOL_3);
		}
		else if (Code==5)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SECURE_POOL);
		}
		else if (Code==6)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_GLOBAL_OPERATORS_NEW_DELETE);
		}
		else if (Code==7)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPECIFIC_TYPE_OPERATORS_NEW_DELETE);
		}
		else if (Code==8)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_OLD_LOOKASIDE_LIST_PAGED);
		}
		else if (Code==9)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_OLD_LOOKASIDE_LIST_NON_PAGED);
		}
		else if (Code==10)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_NEW_LOOKASIDE_LIST);
		}
		else if (Code==11)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SEND_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP);
		}
		else if (Code==12)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SEND_INTERNAL_DEVICE_CONTROL_IRP_TO_RECEIVING_IRP);
		}
		else if (Code==13)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_ZW_QUERY_SYSTEM_INFORMATION);
		}
		else if (Code==14)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_ZW_QUERY_INFORMATION_PROCESS);
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------