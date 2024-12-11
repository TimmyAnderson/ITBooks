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
#include "..\IntroductionToKMDF\SharedHeader.h"
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

		wstring													DeviceName;

		try
		{
			DeviceName=FindBoosterDevice(GUID_INTRODUCTION_TO_KDF_INTERFACE);
		}
		catch(const CException& E)
		{
			wcout << L"Can't FIND DEVICE NAME. ERROR [" << E.GetMessage() << L"]." << endl;
			break;
		}

		if (Code==1)
		{
			BYTE												Buffer[1000];
			constexpr DWORD										BufferSize=sizeof(Buffer);
			DWORD												BytesRead=0;

			ZeroMemory(Buffer,BufferSize);

			if (CHelpers::SendSynchronousReadRequest(DeviceName.c_str(),Buffer,BufferSize,&BytesRead)==true)
			{
				wchar_t*										TypedBuffer=reinterpret_cast<wchar_t*>(Buffer);

				wcout << L"BUFFER [" << TypedBuffer << L"] BYTES READ [" << BytesRead << L"] !" << endl;
			}
		}
		else if (Code==2)
		{
			wchar_t												Buffer[]=L"Timmy WRITE.";
			constexpr DWORD										BufferSize=sizeof(Buffer);
			DWORD												BytesWritten=0;
			const BYTE*											TypedBuffer=reinterpret_cast<const BYTE*>(Buffer);

			if (CHelpers::SendSynchronousWriteRequest(DeviceName.c_str(),TypedBuffer,BufferSize,&BytesWritten)==true)
			{
				wcout << L"BUFFER [" << Buffer << L"] BYTES WRITTEN [" << BytesWritten << L"] !" << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------