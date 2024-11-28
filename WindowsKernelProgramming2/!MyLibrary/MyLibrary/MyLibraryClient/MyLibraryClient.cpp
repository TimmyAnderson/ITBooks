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
#include "..\MyLibrary\SharedHeader.h"
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
#define IOCTL_TEST_MEMORY_OPERATORS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MEMORY_OPERATORS,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_GLOBAL_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_GLOBAL_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_MUTEX_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEX_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_MUTEX_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_FAST_MUTEX_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEX_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_FAST_MUTEX_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_LOOKASIDE_LIST_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_LOOKASIDE_LIST_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_EXECUTIVE_RESOURCE_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_SPLAY_TREES_GLOBAL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPLAY_TREES_GLOBAL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPLAY_TREES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPLAY_TREES,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_AVL_TREES_GLOBAL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_AVL_TREES_GLOBAL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_AVL_TREES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_AVL_TREES,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_TIMER_GLOBAL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_TIMER_GLOBAL,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_INTERLOCKED_GLOBAL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_INTERLOCKED_GLOBAL,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_INTERLOCKED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_INTERLOCKED,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_SPIN_LOCK_GLOBAL_GLOBAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPIN_LOCK_GLOBAL_GLOBAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCK_GLOBAL_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPIN_LOCK_GLOBAL_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCK_GLOBAL_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPIN_LOCK_GLOBAL_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCK_GLOBAL_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPIN_LOCK_GLOBAL_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_SPIN_LOCK_GLOBAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPIN_LOCK_GLOBAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCK_LOCAL_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPIN_LOCK_LOCAL_OBJECT,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCK_LOCAL_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SPIN_LOCK_LOCAL_POINTER,METHOD_NEITHER,FILE_ANY_ACCESS)
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
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MEMORY_OPERATORS);
		}
		else if (Code==2)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_OBJECT);
		}
		else if (Code==3)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MUTEX_GLOBAL_GLOBAL_POINTER);
		}
		else if (Code==4)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MUTEX_GLOBAL_LOCAL_OBJECT);
		}
		else if (Code==5)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MUTEX_GLOBAL_LOCAL_POINTER);
		}
		else if (Code==6)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MUTEX_GLOBAL_POINTER);
		}
		else if (Code==7)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MUTEX_LOCAL_OBJECT);
		}
		else if (Code==8)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_MUTEX_LOCAL_POINTER);
		}
		else if (Code==9)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_OBJECT);
		}
		else if (Code==10)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_FAST_MUTEX_GLOBAL_GLOBAL_POINTER);
		}
		else if (Code==11)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_OBJECT);
		}
		else if (Code==12)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_FAST_MUTEX_GLOBAL_LOCAL_POINTER);
		}
		else if (Code==13)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_FAST_MUTEX_GLOBAL_POINTER);
		}
		else if (Code==14)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_FAST_MUTEX_LOCAL_OBJECT);
		}
		else if (Code==15)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_FAST_MUTEX_LOCAL_POINTER);
		}
		else if (Code==16)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_OBJECT);
		}
		else if (Code==17)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_LOOKASIDE_LIST_GLOBAL_POINTER);
		}
		else if (Code==18)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_OBJECT);
		}
		else if (Code==19)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXECUTIVE_RESOURCE_GLOBAL_GLOBAL_POINTER);
		}
		else if (Code==20)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_OBJECT);
		}
		else if (Code==21)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_EXECUTIVE_RESOURCE_LOCAL_POINTER);
		}
		else if (Code==22)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPLAY_TREES_GLOBAL);
		}
		else if (Code==23)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPLAY_TREES);
		}
		else if (Code==24)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_AVL_TREES_GLOBAL);
		}
		else if (Code==25)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_AVL_TREES);
		}
		else if (Code==26)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_TIMER_GLOBAL);
		}
		else if (Code==27)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_INTERLOCKED_GLOBAL);
		}
		else if (Code==28)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_INTERLOCKED);
		}
		else if (Code==29)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPIN_LOCK_GLOBAL_GLOBAL_OBJECT);
		}
		else if (Code==30)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPIN_LOCK_GLOBAL_GLOBAL_POINTER);
		}
		else if (Code==31)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPIN_LOCK_GLOBAL_LOCAL_OBJECT);
		}
		else if (Code==32)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPIN_LOCK_GLOBAL_LOCAL_POINTER);
		}
		else if (Code==33)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPIN_LOCK_GLOBAL_POINTER);
		}
		else if (Code==34)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPIN_LOCK_LOCAL_OBJECT);
		}
		else if (Code==35)
		{
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_SPIN_LOCK_LOCAL_POINTER);
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------