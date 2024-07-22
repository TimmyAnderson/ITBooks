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
#include "..\Melody\SharedHeader.h"
#include "..\Melody\SNote.h"
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
#define IOCTL_MELODY_PLAY CTL_CODE(MELODY_DEVICE, CODE_PLAY_MUSIC, METHOD_BUFFERED, FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void SendMusicToDriver(void)
{
	const wchar_t*												SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

	HANDLE														Device=CreateFile(SymbolicLinkName,GENERIC_WRITE,0,nullptr, OPEN_EXISTING,0,nullptr);

	if (Device!=INVALID_HANDLE_VALUE)
	{
		SNote													Notes1[10];

		for(size_t Index=0;Index<CountOf(Notes1);Index++)
		{
			Notes1[Index].Frequency=(400+(static_cast<unsigned long>(Index)*30));
			Notes1[Index].Duration=500;
		}

		DWORD													Bytes1;

		if (DeviceIoControl(Device,IOCTL_MELODY_PLAY,Notes1,sizeof(Notes1),nullptr,0,&Bytes1,nullptr)!=FALSE)
		{
			wcout << L"MUSIC IS PLAYED - BYTES [" << Bytes1 << L"] !" << endl;
		}
		else
		{
			wcout << L"Can't SEND DEVICE CONTROL to DEVICE !" << endl;
		}

		SNote													Notes2[10];

		for(size_t Index=0;Index<CountOf(Notes2);Index++)
		{
			Notes2[Index].Frequency=(1200-(static_cast<unsigned long>(Index)*100));
			Notes2[Index].Duration=300;
			Notes2[Index].Repeat=2;
			Notes2[Index].Delay=300;
		}

		DWORD													Bytes2;

		if (DeviceIoControl(Device,IOCTL_MELODY_PLAY,Notes2,sizeof(Notes2),nullptr,0,&Bytes2,nullptr)!=FALSE)
		{
			wcout << L"MUSIC IS PLAYED - BYTES [" << Bytes2 << L"] !" << endl;
		}
		else
		{
			wcout << L"Can't SEND DEVICE CONTROL to DEVICE !" << endl;
		}

		CloseHandle(Device);
		Device=INVALID_HANDLE_VALUE;
	}
	else
	{
		wcout << L"Can't OPEN DEVICE !" << endl;
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

		if (Code==1)
		{
			SendMusicToDriver();
		}
		else if (Code==2)
		{
			SendMusicToDriver();
			SendMusicToDriver();
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------