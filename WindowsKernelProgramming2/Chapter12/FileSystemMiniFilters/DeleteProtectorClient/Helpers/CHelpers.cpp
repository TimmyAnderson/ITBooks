//----------------------------------------------------------------------------------------------------------------------
#include "CHelpers.h"
#include <iostream>
#include "MyDebug.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::SendSynchronousDeviceIoControlRequest(const wchar_t* SymbolicLinkName, DWORD Code, BYTE* InputBuffer, DWORD InputBufferSize, BYTE* OutputBuffer, DWORD OutputBufferSize, DWORD* BytesReturned)
{
	bool														Result=false;
	HANDLE														DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

	if (DeviceHandle!=INVALID_HANDLE_VALUE)
	{
		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

		wcout << L"OPERATION DEVICE IO CONTROL - INPUT BUFFER [" << InputBuffer << L"] INPUT BUFFER SIZE [" << InputBufferSize << L"] OUTPUT BUFFER [" << OutputBuffer << L"] OUTPUT BUFFER SIZE [" << OutputBufferSize << L"] !" << endl;

		if (DeviceIoControl(DeviceHandle,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,BytesReturned,NULL)!=FALSE)
		{
			wcout << L"OPERATION DEVICE IO CONTROL SUCCEEDED - BYTES RETURNED [" << (*BytesReturned) << L"] !" << endl;

			Result=true;
		}
		else
		{
			DWORD												Error=GetLastError();

			wcout << L"OPERATION DEVICE IO CONTROL FAILED - ERROR [" << Error << L"] !" << endl;
		}

		CloseHandle(DeviceHandle);
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::SendAsynchronousDeviceIoControlRequest(const wchar_t* SymbolicLinkName, DWORD Code, BYTE* InputBuffer, DWORD InputBufferSize, BYTE* OutputBuffer, DWORD OutputBufferSize, DWORD* BytesReturned)
{
	bool														Result=false;
	HANDLE														DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE,0,nullptr,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,nullptr);

	if (DeviceHandle!=INVALID_HANDLE_VALUE)
	{
		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

		OVERLAPPED												Overlapped{};

		ZeroMemory(&Overlapped,sizeof(Overlapped));

		Overlapped.hEvent=CreateEvent(nullptr,TRUE,FALSE,nullptr);
		
		if (Overlapped.hEvent!=nullptr)
		{
			wcout << L"OPERATION DEVICE IO CONTROL - INPUT BUFFER [" << InputBuffer << L"] INPUT BUFFER SIZE [" << InputBufferSize << L"] OUTPUT BUFFER [" << OutputBuffer << L"] OUTPUT BUFFER SIZE [" << OutputBufferSize << L"] !" << endl;

			if (DeviceIoControl(DeviceHandle,Code,InputBuffer,InputBufferSize,OutputBuffer,OutputBufferSize,nullptr,&Overlapped)!=FALSE)
			{
				wcout << L"OPERATION DEVICE IO CONTROL SUCCEEDED !" << endl;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"OPERATION DEVICE IO CONTROL FAILED - ERROR [" << Error << L"] !" << endl;
			}

			if (GetOverlappedResult(DeviceHandle,&Overlapped,BytesReturned,TRUE)!=FALSE)
			{
				wcout << L"OVERLAPPED RESULT - BYTES RETURNED [" << (*BytesReturned) << L"] !" << endl;

				Result=true;
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"Can't GET OVERLAPPED RESULT - ERROR [" << Error << L"] !" << endl;
			}

			CloseHandle(Overlapped.hEvent);
		}
		else
		{
			DWORD												Error=GetLastError();

			wcout << L"Can't CREATE EVENT - ERROR [" << Error << L"] !" << endl;
		}

		CloseHandle(DeviceHandle);
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::SendSynchronousDeviceIoControlRequestEmptyArrays(const wchar_t* SymbolicLinkName, DWORD Code)
{
	DWORD														BytesReturned=0;
	bool														Result=SendSynchronousDeviceIoControlRequest(SymbolicLinkName,Code,nullptr,0,nullptr,0,&BytesReturned);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::SendAsynchronousDeviceIoControlRequestEmptyArrays(const wchar_t* SymbolicLinkName, DWORD Code)
{
	DWORD														BytesReturned=0;
	bool														Result=SendAsynchronousDeviceIoControlRequest(SymbolicLinkName,Code,nullptr,0,nullptr,0,&BytesReturned);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::SendSynchronousReadRequest(const wchar_t* SymbolicLinkName, BYTE* ReadBuffer, DWORD ReadBufferSize, DWORD* NumberOfBytesRead)
{
	bool														Result=false;
	HANDLE														DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);

	if (DeviceHandle!=INVALID_HANDLE_VALUE)
	{
		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

		if (ReadFile(DeviceHandle,ReadBuffer,ReadBufferSize,NumberOfBytesRead,NULL)!=FALSE)
		{
			wcout << L"OPERATION READ SUCCEEDED - READ BUFFER [" << ReadBuffer << L"] NUMBER OF BYTES READ [" << (*NumberOfBytesRead) << L"] !" << endl;

			Result=true;
		}
		else
		{
			DWORD												Error=GetLastError();

			wcout << L"OPERATION READ FAILED - ERROR [" << Error << L"] !" << endl;
		}

		CloseHandle(DeviceHandle);
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::SendSynchronousWriteRequest(const wchar_t* SymbolicLinkName, const BYTE* WriteBuffer, DWORD WriteBufferSize, DWORD* NumberOfBytesWritten)
{
	bool														Result=false;
	HANDLE														DeviceHandle=CreateFile(SymbolicLinkName,GENERIC_WRITE,0,nullptr,OPEN_EXISTING,0,nullptr);

	if (DeviceHandle!=INVALID_HANDLE_VALUE)
	{
		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] OPENED SUCCESSFULLY." << endl;

		if (WriteFile(DeviceHandle,WriteBuffer,WriteBufferSize,NumberOfBytesWritten,NULL)!=FALSE)
		{
			wcout << L"OPERATION WRITE SUCCEEDED - WRITE BUFFER [" << WriteBuffer << L"] NUMBER OF BYTES WRITTEN [" << (*NumberOfBytesWritten) << L"] !" << endl;

			Result=true;
		}
		else
		{
			DWORD												Error=GetLastError();

			wcout << L"OPERATION WRITE FAILED - ERROR [" << Error << L"] !" << endl;
		}

		CloseHandle(DeviceHandle);
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"DEVICE OBJECT with SYMBOLIC LINK [" << SymbolicLinkName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::ReadTextFile(const wchar_t* FileName, std::wstring& Text)
{
	bool														Result=false;
	HANDLE														DeviceHandle=CreateFile(FileName,GENERIC_READ,0,nullptr,OPEN_EXISTING,0,nullptr);
	
	if (DeviceHandle!=INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER											FileSize;

		if (GetFileSizeEx(DeviceHandle,&FileSize)!=FALSE)
		{
			DWORD												ReadBufferSize=FileSize.LowPart;
			char*												ReadBuffer=new char[ReadBufferSize+1];

			ReadBuffer[ReadBufferSize]='\0';

			DWORD												NumberOfBytesRead;

			if (ReadFile(DeviceHandle,ReadBuffer,ReadBufferSize,&NumberOfBytesRead,NULL)!=FALSE)
			{
				if (ReadBufferSize==NumberOfBytesRead)
				{
					string										TextRaw(ReadBuffer);

					Text=ConvertStringToWideString(TextRaw);

					Result=true;
				}
				else
				{
					DWORD										Error=GetLastError();

					wcout << L"FILE [" << FileName << L"] FAILED to READ ALL BYTES with ERROR [" << Error << L"]." << endl;
				}
			}
			else
			{
				DWORD											Error=GetLastError();

				wcout << L"FILE [" << FileName << L"] FAILED to READ with ERROR [" << Error << L"]." << endl;
			}

			delete[](ReadBuffer);
			ReadBuffer=nullptr;
		}
		else
		{
			DWORD												Error=GetLastError();

			wcout << L"FILE [" << FileName << L"] FAILED to GET FILE SIZE with ERROR [" << Error << L"]." << endl;
		}

		CloseHandle(DeviceHandle);
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"FILE [" << FileName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
bool CHelpers::WriteTextFile(const wchar_t* FileName, const std::wstring& Text)
{
	bool														Result=false;
	HANDLE														DeviceHandle=CreateFile(FileName,GENERIC_WRITE,0,nullptr,OPEN_ALWAYS,0,nullptr);
	
	if (DeviceHandle!=INVALID_HANDLE_VALUE)
	{
		DWORD													NumberOfBytesWritten;
		string													TextRaw=ConvertWideStringToString(Text);
		char*													WriteBuffer=TextRaw.data();
		DWORD													WriteBufferSize=static_cast<DWORD>(TextRaw.length());

		if (WriteFile(DeviceHandle,WriteBuffer,WriteBufferSize,&NumberOfBytesWritten,NULL)!=FALSE)
		{
			wcout << L"OPERATION WRITE SUCCEEDED - WRITE BUFFER [" << WriteBuffer << L"] NUMBER OF BYTES WRITTEN [" << NumberOfBytesWritten << L"] !" << endl;

			Result=true;
		}
		else
		{
			DWORD												Error=GetLastError();

			wcout << L"FILE [" << FileName << L"] FAILED to WRITE with ERROR [" << Error << L"]." << endl;
		}

		CloseHandle(DeviceHandle);
	}
	else
	{
		DWORD													Error=GetLastError();

		wcout << L"FILE [" << FileName << L"] FAILED to OPEN with ERROR [" << Error << L"]." << endl;
	}

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------