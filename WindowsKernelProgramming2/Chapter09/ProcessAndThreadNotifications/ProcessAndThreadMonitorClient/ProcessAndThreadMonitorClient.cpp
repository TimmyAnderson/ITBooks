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
#include "..\ProcessAndThreadMonitor\SharedHeader.h"
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
void DisplayTime(const LARGE_INTEGER& Time)
{
	// !!! LARGE_INTEGER and FILETIME have the same size representing the same format in our case.
	FILETIME													Local;

	// !!! Convert to local time first (KeQuerySystemTime(Procise) returns UTC).
	FileTimeToLocalFileTime((FILETIME*)&Time,&Local);

	SYSTEMTIME													ST;

	FileTimeToSystemTime(&Local,&ST);

	wstring														FormattedTime=format(L"TIME [{:02}:{:02}:{:02}.{:03}]:",ST.wHour,ST.wMinute,ST.wSecond,ST.wMilliseconds);

	wcout << FormattedTime;
}
//----------------------------------------------------------------------------------------------------------------------
void DisplayInfo(BYTE* Buffer, DWORD Size)
{
	while (Size>0)
	{
		SItemHeader*											Header=(SItemHeader*)Buffer;

		if (Header->MType==EItemType::E_PROCESS_CREATE)
		{
			DisplayTime(Header->MTime);

			SProcessCreateInfo*									Info=(SProcessCreateInfo*)Buffer;

			std::wstring										Commandline(Info->MCommandLine,Info->MCommandLineLength);

			wcout << L"PROCESS [" << Info->MProcessID << L"] CREATED. COMMAND LINE [" << Commandline << L"]." << endl;
		}
		else if (Header->MType==EItemType::E_PROCESS_EXIT)
		{
			DisplayTime(Header->MTime);

			SProcessExitInfo*									Info=(SProcessExitInfo*)Buffer;

			wcout << L"PROCESS [" << Info->MProcessID << L"] EXITED. EXIT CODE [" << Info->MExitCode << L"]." << endl;
		}
		else if (Header->MType==EItemType::E_THREAD_CREATE)
		{
			DisplayTime(Header->MTime);

			SThreadCreateInfo*									Info=(SThreadCreateInfo*)Buffer;

			wcout << L"THTREAD [" << Info->MThreadID << L"] CREATED in PROCESS [" << Info->MProcessID << L"]." << endl;

		}
		else if (Header->MType==EItemType::E_THREAD_EXIT)
		{
			DisplayTime(Header->MTime);

			SThreadExitInfo*									Info=(SThreadExitInfo*)Buffer;

			wcout << L"THTREAD [" << Info->MThreadID << L"] EXITED from PROCESS [" << Info->MProcessID << L"]. EXIT CODE [" << Info->MExitCode << L"]." << endl;
		}

		Buffer+=Header->MSize;
		Size-=Header->MSize;
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

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

		if (Code==1)
		{
			HANDLE												DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);

			if (DeviceHandle!=INVALID_HANDLE_VALUE)
			{
				wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

				DWORD											Size=(1 << 16);
				unique_ptr<BYTE[]>								Buffer=std::make_unique<BYTE[]>(Size);
				size_t											Counter=0;

				while(true)
				{
					DWORD										Bytes=0;

					if (ReadFile(DeviceHandle,Buffer.get(),Size,&Bytes,nullptr)!=FALSE)
					{
						wcout << L"OPERATION READ SUCCEEDED - READ BUFFER [" << Buffer.get() << L"] NUMBER OF BYTES READ [" << (Bytes) << L"] !" << endl;

						if (Bytes>0)
						{
							Counter=0;
							DisplayInfo(Buffer.get(),Bytes);
						}
						else
						{
							++Counter;

							if (Counter==3)
							{
								break;
							}
						}
					}
					else
					{
						DWORD									Error=GetLastError();

						wcout << L"OPERATION READ FAILED - ERROR [" << Error << L"] !" << endl;
						break;
					}

					Sleep(400);
				}

				CloseHandle(DeviceHandle);
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------