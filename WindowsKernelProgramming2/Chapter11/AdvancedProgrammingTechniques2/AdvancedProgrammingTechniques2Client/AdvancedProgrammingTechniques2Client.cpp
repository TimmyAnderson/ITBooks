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
#include "..\AdvancedProgrammingTechniques2\SharedHeader.h"
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
#define IOCTL_TEST_KERNEL_TIMERS_LONG_TIME CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_LONG_TIME,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_NOTIFICATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_NOTIFICATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_SYNCHRONIZATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_SYNCHRONIZATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_CANCEL_BY_SET_TIMER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_CANCEL_BY_SET_TIMER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_DPC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_DPC,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_PERIODIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_PERIODIC,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_COALESCABLE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_COALESCABLE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_KERNEL_TIMERS_RESOLUTION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_KERNEL_TIMERS_RESOLUTION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_DELETE_WAIT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_DELETE_WAIT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_DELETE_CANCEL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_DELETE_CANCEL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_NOTIFICATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_NOTIFICATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_SYNCHRONIZATION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_SYNCHRONIZATION,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_CANCEL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_CANCEL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_NO_WAKE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_NO_WAKE,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXTENDED_TIMERS_PERIODIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXTENDED_TIMERS_PERIODIC,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_IO_TIMERS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IO_TIMERS,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPLAY_TREES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPLAY_TREES,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_AVL_TREES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_AVL_TREES,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SINGLY_LINKED_LISTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SINGLY_LINKED_LISTS,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_1,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEQUENCED_SINGLY_LINKED_LISTS_1,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEQUENCED_SINGLY_LINKED_LISTS_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_CALLBACK_OBJECTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_CALLBACK_OBJECTS,METHOD_NEITHER,FILE_ANY_ACCESS)
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
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_LONG_TIME);
		}
		else if (Code==2)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_NOTIFICATION);
		}
		else if (Code==3)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_SYNCHRONIZATION);
		}
		else if (Code==4)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_CANCEL_BY_SET_TIMER);
		}
		else if (Code==5)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_DPC);
		}
		else if (Code==6)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_PERIODIC);
		}
		else if (Code==7)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_COALESCABLE);
		}
		else if (Code==8)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_KERNEL_TIMERS_RESOLUTION);
		}
		else if (Code==9)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS);
		}
		else if (Code==10)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS_DELETE_WAIT);
		}
		else if (Code==11)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS_DELETE_CANCEL);
		}
		else if (Code==12)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS_NOTIFICATION);
		}
		else if (Code==13)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS_SYNCHRONIZATION);
		}
		else if (Code==14)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS_CANCEL);
		}
		else if (Code==15)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS_NO_WAKE);
		}
		else if (Code==16)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXTENDED_TIMERS_PERIODIC);
		}
		else if (Code==17)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_IO_TIMERS);
		}
		else if (Code==18)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPLAY_TREES);
		}
		else if (Code==19)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_AVL_TREES);
		}
		else if (Code==20)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SINGLY_LINKED_LISTS);
		}
		else if (Code==21)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_1);
		}
		else if (Code==22)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_2);
		}
		else if (Code==23)
		{
			for(ULONG Index=0;Index<100;Index++)
			{
				CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SINGLY_LINKED_LISTS_THREAD_SAFE_2);
			}
		}
		else if (Code==24)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_1);
		}
		else if (Code==25)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_2);
		}
		else if (Code==26)
		{
			for(ULONG Index=0;Index<100;Index++)
			{
				CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SEQUENCED_SINGLY_LINKED_LISTS_2);
			}
		}
		else if (Code==27)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_CALLBACK_OBJECTS);
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------