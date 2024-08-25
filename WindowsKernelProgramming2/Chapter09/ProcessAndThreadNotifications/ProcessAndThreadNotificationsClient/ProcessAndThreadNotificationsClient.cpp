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
#include "..\ProcessAndThreadNotifications\SharedHeader.h"
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

		const wchar_t*											SymbolicLinkName=L"\\\\.\\" MY_DRIVER_NAME;

		if (Code==1)
		{
			SNotificationStatistics								Buffer;
			constexpr DWORD										BufferSize=sizeof(Buffer);
			DWORD												BytesRead=0;

			ZeroMemory(&Buffer,BufferSize);

			if (CHelpers::SendSynchronousReadRequest(SymbolicLinkName,reinterpret_cast<BYTE*>(&Buffer),BufferSize,&BytesRead)==true)
			{
				wcout << L"PROCESSES CREATED [" << Buffer.MNumberOfProcesesCreated << L"] PROCESSES FINISHED [" << Buffer.MNumberOfProcesesFinished << L"] THREADS CREATED [" << Buffer.MNumberOfThreadsCreated << L"] THREADS FINISHED [" << Buffer.MNumberOfThreadsFinished << L"] LOADED IMAGES [" << Buffer.MNumberOfLoadedImages << L"] BYTES READ [" << BytesRead << L"] !" << endl;
			}
		}
	}
	while(false);

	PrintLineSeparator();

	ShowExitLine();

	return(0);
}
//----------------------------------------------------------------------------------------------------------------------