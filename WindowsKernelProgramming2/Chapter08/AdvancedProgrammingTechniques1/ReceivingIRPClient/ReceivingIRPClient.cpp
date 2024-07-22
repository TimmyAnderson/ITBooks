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
#include "..\ReceivingIRP\SharedHeader.h"
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
#define IOCTL_TEST_RECEIVING_IRP CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_RECEIVING_IRP,METHOD_NEITHER,FILE_ANY_ACCESS)
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
			CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(SymbolicLinkName,IOCTL_TEST_RECEIVING_IRP);
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------