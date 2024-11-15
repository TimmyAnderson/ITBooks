//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <fltUser.h>
#include "Helpers\MyDebug.h"
#include "Helpers\CString.h"
#include "Helpers\CException.h"
#include "Helpers\CHelpers.h"
// !!!!! SHARED HEADER definovany v DRIVER.
#include "..\FileBackup\SharedHeader.h"
#include "..\FileBackup\SFileBackupPortMessage.h"
#include "EOperation.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FILE SYSTEM MINI FILTERS MUSIA mat vlozenu LIBRARY [FltLib.lib].
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
void PrintUsage(void)
{
	wcout << L"USE [" MY_DRIVER_NAME L"Client.exe {1 FILENAME CONTENT} {2 FILENAME} {3}]." << endl;
	wcout << L"1 - WRITE FILE, 1 - RESTORE FILE, 2 - GET BACKUP FILES." << endl;
}
//----------------------------------------------------------------------------------------------------------------------
void PrintMessage(const BYTE* Buffer)
{
	const SFileBackupPortMessage*								TypedBuffer=(SFileBackupPortMessage*) Buffer;
	wstring														Filename(TypedBuffer->MFileName,TypedBuffer->MFileNameLength);

	wcout << L"FILE [" << Filename << L"] is BACKED UP." << endl;
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
		if (argc<=1)
		{
			wcout << L"INVALID COMMAND." << endl;
			PrintUsage();
			break;
		}

		EOperation												Operation;
		wstring													DestinationFileName;
		wstring													FileContent;

		try
		{
			Operation=(EOperation)stoi(argv[1]);
		}
		catch(...)
		{
			wcout << L"INVALID COMMAND." << endl;
			PrintUsage();
			break;
		}

		if (Operation==EOperation::E_WRITE_FILE)
		{
			if (argc<=2)
			{
				wcout << L"NO FILENAME SPECIFIED." << endl;
				PrintUsage();
				break;
			}

			DestinationFileName=ConvertStringToWideString(argv[2]);

			if (argc<=3)
			{
				wcout << L"NO FILE CONTENT SPECIFIED." << endl;
				PrintUsage();
				break;
			}

			for(int Index=3;Index<argc;Index++)
			{
				if (Index>3)
				{
					FileContent+=L" ";
				}

				FileContent+=ConvertStringToWideString(argv[Index]);
			}
		}
		else if (Operation==EOperation::E_RESTORE_FILE)
		{
			if (argc<=2)
			{
				wcout << L"NO FILENAME SPECIFIED." << endl;
				PrintUsage();
				break;
			}

			DestinationFileName=ConvertStringToWideString(argv[2]);
		}
		else if (Operation==EOperation::E_GET_BACKUP_FILES)
		{
			// DO NOTHING.
		}
		else
		{
			wcout << L"INVALID COMMAND." << endl;
			PrintUsage();
			break;
		}

		if (Operation==EOperation::E_WRITE_FILE)
		{
			// !!!!! Tento COMMAD vykona BACKUP iba ak je povodny FILE OVERRIDEN. Nie ked je prvykrat vytvoreny. Co je aj logicke, kedze sa robi iba BACKUP uz vytvoreneho FILE.
			CHelpers::WriteTextFile(DestinationFileName.c_str(),FileContent);
		}
		else if (Operation==EOperation::E_RESTORE_FILE)
		{
			wstring												SourceFileName=DestinationFileName;

			SourceFileName+=BACKUP_STREAM_NAME;

			HANDLE												SoruceHandle=CreateFile(SourceFileName.c_str(),GENERIC_READ,FILE_SHARE_READ,nullptr,OPEN_EXISTING,0,nullptr);

			if (SoruceHandle!=INVALID_HANDLE_VALUE)
			{
				HANDLE											DestinationHandle=CreateFile(DestinationFileName.c_str(),GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

				if (DestinationHandle!=INVALID_HANDLE_VALUE)
				{
					LARGE_INTEGER								FileSize;

					if (GetFileSizeEx(SoruceHandle,&FileSize)==TRUE)
					{
						LONGLONG								Size1=LONGLONG(1 << 21);
						LONGLONG								Size2=FileSize.QuadPart;
						ULONG									BufferSize;
						
						if (Size1<Size2)
						{
							BufferSize=Size1;
						}
						else
						{
							BufferSize=Size2;
						}

						void*									Buffer=VirtualAlloc(nullptr,BufferSize,MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
						LARGE_INTEGER							RemainingFileSize=FileSize;

						if (Buffer!=nullptr)
						{
							bool								RestoreSucceeded=true;
							DWORD								Bytes;

							while(RemainingFileSize.QuadPart>0)
							{
								Size1=BufferSize;
								Size2=RemainingFileSize.QuadPart;

								if (Size1<Size2)
								{
									BufferSize=Size1;
								}
								else
								{
									BufferSize=Size2;
								}

								if (ReadFile(SoruceHandle,Buffer,BufferSize,&Bytes,nullptr)==FALSE)
								{
									DWORD						Error=GetLastError();

									wcout << L"SOURCE FILE [" << SourceFileName << L"] FAILED to READ with ERROR [" << Error << L"]." << endl;

									RestoreSucceeded=false;
									break;
								}

								if (WriteFile(DestinationHandle,Buffer,Bytes,&Bytes,nullptr)==FALSE)
								{
									DWORD						Error=GetLastError();

									wcout << L"DESTINATION FILE [" << DestinationFileName << L"] FAILED to WRITE with ERROR [" << Error << L"]." << endl;

									RestoreSucceeded=false;
									break;
								}

								RemainingFileSize.QuadPart-=Bytes;
							}

							if (RestoreSucceeded==true)
							{
								wcout << L"FILE [" << DestinationFileName << L"] was SUCCESSFULLY RESTORED." << endl;
							}
							else
							{
								wcout << L"FILE [" << DestinationFileName << L"] FAILED to RESTORE." << endl;
							}

							VirtualFree(Buffer,0,MEM_RELEASE);

							// !!! Ak bol BACKED UP FILE kratsi ako aktualny FILE SIZE, je nutne skratit dlzku FILE.
							FILE_END_OF_FILE_INFO				EndOfFileInfo;

							EndOfFileInfo.EndOfFile=FileSize;

							if (SetFileInformationByHandle(DestinationHandle,FILE_INFO_BY_HANDLE_CLASS::FileEndOfFileInfo,&EndOfFileInfo,sizeof(EndOfFileInfo))==FALSE)
							{
								DWORD							Error=GetLastError();

								wcout << L"DESTINATION FILE [" << DestinationFileName << L"] FAILED to SET END of FILE with ERROR [" << Error << L"]." << endl;
							}
						}
						else
						{
							wcout << L"FAILED ALLOCATE MEMORY." << endl;
						}
					}
					else
					{
						DWORD									Error=GetLastError();

						wcout << L"FAILED to GET FILE [" << SourceFileName << L"] SIZE with ERROR [" << Error << L"]." << endl;
					}

					CloseHandle(DestinationHandle);
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"DESTINATION FILE [" << DestinationFileName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
				}

				CloseHandle(SoruceHandle);
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"SOURCE FILE [" << SourceFileName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Operation==EOperation::E_GET_BACKUP_FILES)
		{
			wstring												CommunicationPortName=L"\\" COMMUNICATION_PORT_NAME;
			HANDLE												CommunicationPortHandle;
			HRESULT												Result=FilterConnectCommunicationPort(CommunicationPortName.c_str(),0,nullptr,0,nullptr,&CommunicationPortHandle);
				
			if (FAILED(Result)==false)
			{
				BYTE											Buffer[1 << 12];
				FILTER_MESSAGE_HEADER*							Message=(FILTER_MESSAGE_HEADER*)Buffer;

				for (;;)
				{
					// !!! Je to BLOCKING CALL.
					Result=FilterGetMessage(CommunicationPortHandle,Message,sizeof(Buffer),nullptr);

					if (FAILED(Result)==false)
					{
						PrintMessage(Buffer+sizeof(FILTER_MESSAGE_HEADER));
					}
					else
					{
						wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to GET MESSAGE with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
						break;
					}
				}

				CloseHandle(CommunicationPortHandle);
			}
			else
			{
				wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to OPEN with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------