//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>
// !!! Obsahuje STRUCTURES a FUNCTIONS NATIVE API.
#include <winternl.h>
// !!! Obsahuje STRUCTURES a FUNCTIONS BEEP DRIVER.
#include <ntddbeep.h>
#include "MyDebug.h"
#include "CString.h"
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Vlozi sa LIBRARY na NATIVE API.
#pragma comment(lib, "ntdll")
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
int main(void)
{
	SafeMain();

	PrintLineSeparator();

	{
		constexpr int											FREQUENCY=800;
		constexpr int											DURATION=1000;
		constexpr int											DURATION_SLEEP=DURATION+200;

		HANDLE													DeviceObjectHandle;
		OBJECT_ATTRIBUTES										Attributes;
		UNICODE_STRING											Name;

		// !!!! Toto je DEVICE OBJECT NAME, ktory NEPOUZIVA SYMBOLIC LINK.
		//RtlInitUnicodeString(&Name,L"\\Device\\Beep");

		// !!!! Toto je DEVICE OBJECT NAME, definovany priamo v HEADER [ntddbeep.H].
		RtlInitUnicodeString(&Name,DD_BEEP_DEVICE_NAME_U);

		InitializeObjectAttributes(&Attributes,&Name,OBJ_CASE_INSENSITIVE,nullptr,nullptr);

		IO_STATUS_BLOCK											IOStatus;

		// !!! Otvori sa DEVICE OBJECT BEEP DRIVER.
		NTSTATUS												Status=NtOpenFile(&DeviceObjectHandle,GENERIC_WRITE,&Attributes,&IOStatus,0,0);

		if (NT_SUCCESS(Status)==true)
		{
			BEEP_SET_PARAMETERS									BeepParameters;

			BeepParameters.Frequency=FREQUENCY;
			BeepParameters.Duration=DURATION;

			DWORD												BytesReturned;

			wcout << L"DEVICE [" << Name.Buffer << L"] SUCCESSFULLY OPENED." << endl;

			// !!! Prehra SOUND zaslanim IO CONTROL COMMAND.
			DeviceIoControl(DeviceObjectHandle,IOCTL_BEEP_SET,&BeepParameters,sizeof(BeepParameters),nullptr,0,&BytesReturned,nullptr);

			wcout << L"DEVICE [" << Name.Buffer << L"] PLAYING a SOUND." << endl;

			Sleep(DURATION_SLEEP);

			wcout << L"DEVICE [" << Name.Buffer << L"] PLAYED a SOUND. BYTES RETURNED [" << BytesReturned << L"]." << endl;

			CloseHandle(DeviceObjectHandle);
		}
		else
		{
			wcout << L"DEVICE [" << Name.Buffer << L"] FAILED to OPEN." << endl;
		}
	}

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------