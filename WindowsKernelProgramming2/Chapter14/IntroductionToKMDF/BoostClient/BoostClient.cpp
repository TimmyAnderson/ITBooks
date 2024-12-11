//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <SetupAPI.h>
#include <initguid.h>
#include "Helpers\MyDebug.h"
#include "Helpers\CString.h"
#include "Helpers\CException.h"
#include "Helpers\CHelpers.h"
// !!!!! SHARED HEADER definovany v DRIVER.
#include "..\Boost\SharedHeader.h"
#include "..\Boost\SThreadData.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! PROGRAM musi mat vlozenu LIBRARY [Setupapi.lib].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
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
#define IOCTL_BOOSTER_SET_PRIORITY CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_BOOSTER_SET_PRIORITY,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
wstring FindBoosterDevice(CONST GUID& ClassGuid)
{
	wstring														Result;
	wstring														ExceptionMessage=L"";
	HDEVINFO													DeviceInfoHandle=SetupDiGetClassDevs(&ClassGuid,nullptr,nullptr,DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);

	if (DeviceInfoHandle!=INVALID_HANDLE_VALUE)
	{
		do
		{
			SP_DEVINFO_DATA										Data{sizeof(Data)};

			if (SetupDiEnumDeviceInfo(DeviceInfoHandle,0,&Data)==FALSE)
			{
				DWORD											Error=GetLastError();
				std::wstringstream								Stream;

				Stream << L"Can't FIND DEVICE INFORMATION ELEMENT. ERROR [" << Error << L"].";

				ExceptionMessage=Stream.str();
				break;
			}

			SP_DEVICE_INTERFACE_DATA							InterfaceData{sizeof(InterfaceData)};

			if (SetupDiEnumDeviceInterfaces(DeviceInfoHandle,&Data,&ClassGuid,0,&InterfaceData)==FALSE)
			{
				DWORD											Error=GetLastError();
				std::wstringstream								Stream;

				Stream << L"Can't ENUMERATRE DEVICE INTERFACES. ERROR [" << Error << L"].";

				ExceptionMessage=Stream.str();
				break;
			}

			BYTE												Buffer[1024];
			PSP_DEVICE_INTERFACE_DETAIL_DATA					Detail=(PSP_DEVICE_INTERFACE_DETAIL_DATA)Buffer;

			Detail->cbSize=sizeof(*Detail);

			if (SetupDiGetDeviceInterfaceDetail(DeviceInfoHandle,&InterfaceData,Detail,sizeof(Buffer),nullptr,&Data)==TRUE)
			{
				Result=Detail->DevicePath;
			}
			else
			{
				DWORD											Error=GetLastError();
				std::wstringstream								Stream;

				Stream << L"Can't GET DEVICE INTERFACE DETAILS. ERROR [" << Error << L"].";

				ExceptionMessage=Stream.str();
				break;
			}
		}
		while(false);

		SetupDiDestroyDeviceInfoList(DeviceInfoHandle);
	}
	else
	{
		DWORD													Error=GetLastError();
		wstringstream											Stream;

		Stream << L"Can't OPEN DEVICE INFORMATION SET. ERROR [" << Error << L"].";

		ExceptionMessage=Stream.str();
	}

	if (ExceptionMessage.size()==0)
	{
		return(Result);
	}
	else
	{
		CException												Exception(ExceptionMessage);

		throw(Exception);
	}
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
			wcout << L"USE [" MY_DRIVER_NAME L"Client.exe THREAD_ID PRIORITY]." << endl;
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

		wstring													DeviceName;

		try
		{
			DeviceName=FindBoosterDevice(GUID_BOOST_INTERFACE);
		}
		catch(const CException& E)
		{
			wcout << L"Can't FIND DEVICE NAME. ERROR [" << E.GetMessage() << L"]." << endl;
			break;
		}

		SThreadData												ThreadData;

		ThreadData.MThreadID=ThreadID;
		ThreadData.MPriority=Priority;

		DWORD													Code=IOCTL_BOOSTER_SET_PRIORITY;
		BYTE*													InputBuffer=(BYTE*)&ThreadData;
		DWORD													InputBufferSize=sizeof(ThreadData);
		BYTE*													OutputBuffer=nullptr;
		DWORD													OutputBufferSize=0;
		DWORD													BytesReturned;

		if (CHelpers::SendSynchronousDeviceIoControlRequest(DeviceName.c_str(),Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,&BytesReturned)==true)
		{
			wcout << L"DRIVER SET THREAD PRIORITY." << endl;
		}
		else
		{
			wcout << L"!!!!! DRIVER FAILED to SET THREAD PRIORITY." << endl;
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------