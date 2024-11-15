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
#include "..\FileSystemMiniFilters\SharedHeader.h"
#include "..\FileSystemMiniFilters\SPortClientToDriverNoReplyRequest.h"
#include "..\FileSystemMiniFilters\SPortClientToDriverRequestReplyRequest.h"
#include "..\FileSystemMiniFilters\SPortClientToDriverRequestReplyReply.h"
#include "..\FileSystemMiniFilters\SPortDriverToClientNoReplyRequest.h"
#include "..\FileSystemMiniFilters\SPortDriverToClientRequestReplyRequest.h"
#include "..\FileSystemMiniFilters\SPortDriverToClientRequestReplyReply.h"
#include "..\FileSystemMiniFilters\SPortDriverToClientRequestReplyReplyWithHeader.h"
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

		wstring													Text;

		if (Code==1)
		{
			wstring												FileName=L"FileWithMultipleStreams.txt";
			wstring												StreamNameDefault=L"::$DATA";
			wstring												StreamName1=L":MyStream1";
			wstring												StreamName2=L":MyStream2";
			wstring												FullNameDefault=(FileName+StreamNameDefault);
			wstring												FullName1=(FileName+StreamName1);
			wstring												FullName2=(FileName+StreamName2);

			if (CHelpers::WriteTextFile(FullNameDefault.c_str(),L"This is DEFAULT STREAM.")==true)
			{
				wcout << L"STREAM [" << StreamNameDefault << L"] WRITTEN to FILE [" << FileName << L"]." << endl;
			}

			if (CHelpers::WriteTextFile(FullName1.c_str(),L"This is STREAM 1.")==true)
			{
				wcout << L"STREAM [" << StreamName1 << L"] WRITTEN to FILE [" << FileName << L"]." << endl;
			}

			if (CHelpers::WriteTextFile(FullName2.c_str(),L"This is STREAM 2.")==true)
			{
				wcout << L"STREAM [" << StreamName2 << L"] WRITTEN to FILE [" << FileName << L"]." << endl;
			}
		}
		else if (Code==2)
		{
			wstring												FileName=L"FileWithMultipleStreams.txt";
			wstring												StreamNameDefault=L"::$DATA";
			wstring												StreamName1=L":MyStream1";
			wstring												StreamName2=L":MyStream2";
			wstring												FullNameDefault=(FileName+StreamNameDefault);
			wstring												FullName1=(FileName+StreamName1);
			wstring												FullName2=(FileName+StreamName2);
			wstring												StreamContentDefault;
			wstring												StreamContent1;
			wstring												StreamContent2;

			if (CHelpers::ReadTextFile(FullNameDefault.c_str(),StreamContentDefault)==true)
			{
				wcout << L"STREAM [" << StreamNameDefault << L"] READ from FILE [" << FileName << L"] CONTENT [" << StreamContentDefault << L"]." << endl;
			}

			if (CHelpers::ReadTextFile(FullName1.c_str(),StreamContent1)==true)
			{
				wcout << L"STREAM [" << StreamName1 << L"] READ from FILE [" << FileName << L"] CONTENT [" << StreamContent1 << L"]." << endl;
			}

			if (CHelpers::ReadTextFile(FullName2.c_str(),StreamContent2)==true)
			{
				wcout << L"STREAM [" << StreamName2 << L"] READ from FILE [" << FileName << L"] CONTENT [" << StreamContent2 << L"]." << endl;
			}
		}
		else if (Code==3)
		{
			wstring												FileName=L"FileWithMultipleStreams.txt";
			WIN32_FIND_STREAM_DATA								StreamData;
			HANDLE												StreamHandle=FindFirstStreamW(FileName.c_str(),STREAM_INFO_LEVELS::FindStreamInfoStandard,&StreamData,0);

			if (StreamHandle!=INVALID_HANDLE_VALUE)
			{
				wcout << L"FILE [" << FileName << L"] has FILE STREAM [" << StreamData.cStreamName << L"] with SIZE [" << StreamData.StreamSize.LowPart << L"]." << endl;

				while(true)
				{
					if (FindNextStreamW(StreamHandle,&StreamData)!=FALSE)
					{
						wcout << L"FILE [" << FileName << L"] has FILE STREAM [" << StreamData.cStreamName << L"] with SIZE [" << StreamData.StreamSize.LowPart << L"]." << endl;
					}
					else
					{
						DWORD									Error=GetLastError();

						if (Error!=ERROR_HANDLE_EOF)
						{
							wcout << L"FILE [" << FileName << L"] FAILED to FIND NEXT STREAM with ERROR [" << Error << L"]." << endl;
						}

						break;
					}
				}

				FindClose(StreamHandle);
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"FILE [" << FileName << L"] FAILED to FIND FIRST STREAM with ERROR [" << Error << L"]." << endl;
			}
		}
		else if (Code==4)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_CALLBACKS_NO_POST_OPERATION,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==5)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_CALLBACKS_WITH_POST_OPERATION,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==6)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_CALLBACKS_PENDING_PRE_OPERATION,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==7)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_CALLBACKS_PENDING_SAFE_POST_OPERATION,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==8)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_CALLBACKS_PENDING_WORK_ITEM_POST_OPERATION,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==9)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_FILE_OPERATIONS,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==10)
		{
			wstring												CommunicationPortName=L"\\" COMMUNICATION_PORT_NAME;
			HANDLE												CommunicationPortHandle;
			HRESULT												Result=FilterConnectCommunicationPort(CommunicationPortName.c_str(),0,nullptr,0,nullptr,&CommunicationPortHandle);
				
			if (FAILED(Result)==false)
			{
				wcout << L"COMMUNICATION PORT CONNECTED." << endl;

				Sleep(1*1000);

				{
					SPortClientToDriverNoReplyRequest			InputData(100);
					DWORD										OutputBufferBytesReturned;
					HRESULT										Result=FilterSendMessage(CommunicationPortHandle,&InputData,sizeof(InputData),nullptr,0,&OutputBufferBytesReturned);

					if (FAILED(Result)==false)
					{
						wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] SUCESSFULLY SENT MESSAGE. BYTES RETURNED [" << OutputBufferBytesReturned << L"]." << endl;
					}
					else
					{
						wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to SEND MESSAGE with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
					}
				}

				Sleep(1*1000);

				CloseHandle(CommunicationPortHandle);
			}
			else
			{
				wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to OPEN with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
			}
		}
		else if (Code==11)
		{
			wstring												CommunicationPortName=L"\\" COMMUNICATION_PORT_NAME;
			HANDLE												CommunicationPortHandle;
			HRESULT												Result=FilterConnectCommunicationPort(CommunicationPortName.c_str(),0,nullptr,0,nullptr,&CommunicationPortHandle);
				
			if (FAILED(Result)==false)
			{
				wcout << L"COMMUNICATION PORT CONNECTED." << endl;

				Sleep(1*1000);

				{
					SPortClientToDriverRequestReplyRequest		InputData(100);
					SPortClientToDriverRequestReplyReply		OutputData{0,0};
					DWORD										OutputBufferBytesReturned;
					HRESULT										Result=FilterSendMessage(CommunicationPortHandle,&InputData,sizeof(InputData),&OutputData,sizeof(OutputData),&OutputBufferBytesReturned);

					if (FAILED(Result)==false)
					{
						wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] SUCESSFULLY SENT MESSAGE. BYTES RETURNED [" << OutputBufferBytesReturned << L"] VALUE 1 [" << OutputData.MValue1 << L"] VALUE 2 [" << OutputData.MValue2 << L"]." << endl;
					}
					else
					{
						wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to SEND MESSAGE with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
					}
				}

				Sleep(1*1000);

				CloseHandle(CommunicationPortHandle);
			}
			else
			{
				wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to OPEN with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
			}
		}
		else if (Code==12)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_SEND_NO_REPLY_MESSAGE,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==13)
		{
			if (CHelpers::ReadTextFile(L"!FILES\\" TEST_FILE_NAME_SEND_REQUEST_REPLY_MESSAGE,Text)==true)
			{
				wcout << L"FILE CONTENT [" << Text << L"]." << endl;
			}
		}
		else if (Code==14)
		{
			wstring												CommunicationPortName=L"\\" COMMUNICATION_PORT_NAME;
			HANDLE												CommunicationPortHandle;
			HRESULT												Result=FilterConnectCommunicationPort(CommunicationPortName.c_str(),0,nullptr,0,nullptr,&CommunicationPortHandle);
				
			if (FAILED(Result)==false)
			{
				wcout << L"COMMUNICATION PORT CONNECTED." << endl;

				wcout << L"RUN COMMAND [" MY_DRIVER_NAME L"Client.exe 12] or COMMAND [" MY_DRIVER_NAME L"Client.exe 13] to RECEIVE MESSAGE from DRIVER." << endl;

				BYTE											RawRequestMessageBuffer[1000];

				ZeroMemory(RawRequestMessageBuffer,sizeof(RawRequestMessageBuffer));

				PFILTER_MESSAGE_HEADER							RequestMessageBuffer=PFILTER_MESSAGE_HEADER(RawRequestMessageBuffer);
				HRESULT											Result=FilterGetMessage(CommunicationPortHandle,RequestMessageBuffer,sizeof(RawRequestMessageBuffer),nullptr);
				
				if (FAILED(Result)==false)
				{
					wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] SUCCESSFULLY GET MESSAGE." << endl;

					BYTE*										RawMessageDataBuffer=&RawRequestMessageBuffer[sizeof(FILTER_MESSAGE_HEADER)];
					SPortDriverToClientBase*					MessageDataBuffer=(SPortDriverToClientBase*) RawMessageDataBuffer;

					if (MessageDataBuffer->MMessageType==EPortDriverToClientMessageType::E_NO_REPLY)
					{
						SPortDriverToClientNoReplyRequest*		TypedMessageDataBuffer=(SPortDriverToClientNoReplyRequest*) MessageDataBuffer;

						wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] SUCCESSFULLY GET NO REPLY MESSAGE with VALUE [" << TypedMessageDataBuffer->MValue << L"]." << endl;
					}
					else if (MessageDataBuffer->MMessageType==EPortDriverToClientMessageType::E_REQUEST_REPLY)
					{
						SPortDriverToClientRequestReplyRequest*	TypedMessageDataBuffer=(SPortDriverToClientRequestReplyRequest*) MessageDataBuffer;

						wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] SUCCESSFULLY GET REQUEST REPLY MESSAGE with VALUE [" << TypedMessageDataBuffer->MValue << L"] REPLY MESSAGE ID [" << RequestMessageBuffer->MessageId << L"] REPLY MESSAGE LENGTH [" << RequestMessageBuffer->ReplyLength << L"]." << endl;

						// !!!!! REPLY MESSAGE SIZE musi byt vypocivavana pomocou EXPRESSION [sizeof(FILTER_REPLY_HEADER)+sizeof(CUSTOM_DATA)].
						DWORD									ReplyMessageLength=(sizeof(FILTER_REPLY_HEADER)+sizeof(SPortDriverToClientRequestReplyReply));

						if (RequestMessageBuffer->ReplyLength>=ReplyMessageLength)
						{
							SPortDriverToClientRequestReplyReplyWithHeader	ReplyMessage;

							ZeroMemory(&ReplyMessage,sizeof(ReplyMessage));

							ReplyMessage.MHeader.MessageId=RequestMessageBuffer->MessageId;

							ReplyMessage.MReply.MValue1=TypedMessageDataBuffer->MValue;
							ReplyMessage.MReply.MValue2=(ReplyMessage.MReply.MValue1*2);

							Result=FilterReplyMessage(CommunicationPortHandle,(PFILTER_REPLY_HEADER)&ReplyMessage,ReplyMessageLength);

							if (FAILED(Result)==false)
							{
								wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] SUCCESSFULLY SEND REPLY MESSAGE. VALUE 1 [" << ReplyMessage.MReply.MValue1 << L"] VALUE 2 [" << ReplyMessage.MReply.MValue2 << L"]." << endl;
							}
							else
							{
								wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to SEND REPLY MESSAGE with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
							}
						}
						else
						{
							wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] CAN'T SEND REPLY MESSAGE because REPLY BUFFER is TOO SHORT." << endl;
						}
					}
				}
				else
				{
					wcout << L"COMMUNICATION PORT [" << CommunicationPortName << L"] FAILED to GET MESSAGE with ERROR [" << format(L"0x{:08X}",(unsigned long)Result) << L"]." << endl;
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