#include "stdafx.h"
#include <windows.h>
#include <process.h>
#include "MyDebug.h"
#include "SharedData.h"
//------------------------------------------------------------------------------
CSharedData			SD;
//------------------------------------------------------------------------------
void ProcessData(DWORD ErrorCode, DWORD NumberOfBytesTransfered, LPOVERLAPPED Overlapped, LPBYTE Buffer)
{
	int			Size=min(NumberOfBytesTransfered,200);

	Buffer[Size]='\0';
	Buffer[Size+1]='\0';

	wprintf(L"Thread: %d - Operation finished in COMPLETION PORT - BytesRead: [%d], ErrorCode: [%d], Some Data [%s] !\n",GetCurrentThreadId(),NumberOfBytesTransfered,ErrorCode,Buffer);
}
//------------------------------------------------------------------------------
// Simulujem nacitanie dat z DEVICE.
unsigned __stdcall ThreadProducer(void*)
{
	Sleep(3*1000);

	DWORD				NumberOfBytesRead=0;
	HANDLE				HFile=CreateFile(L"..\\TestFile.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if (ReadFile(HFile,SD.Buffer,SD.Size,&NumberOfBytesRead,NULL)==FALSE)
	{
		DWORD		LastError=GetLastError();
	
		wprintf(L"Thread: %d - Can't read DATA - Error: [%d] !\n",GetCurrentThreadId(),LastError);
	}
	else
		wprintf(L"Thread: %d - DATA READ - number: [%d] !\n",GetCurrentThreadId(),NumberOfBytesRead);

	CloseHandle(HFile);
	HFile=NULL;

	// ????? Vyzera to, ze Overlapped->hEvent musim RUCNE NASTAVIT.
	//SetEvent(SD.Overlapped.hEvent);

	// !!!!! Poslem data do CP.
	if (PostQueuedCompletionStatus(SD.CP,NumberOfBytesRead,(ULONG_PTR) &ProcessData,&SD.Overlapped)==FALSE)
	{
		DWORD		LastError=GetLastError();
	
		wprintf(L"Thread: %d - Can't POST DATA to CP - Error: [%d] !\n",GetCurrentThreadId(),LastError);
	}
	else
	{
		wprintf(L"Thread: %d - DATA POSTED to CP !\n",GetCurrentThreadId());
	}

	return(0);
}
//------------------------------------------------------------------------------
unsigned __stdcall ThreadConsumer(void*)
{
	wprintf(L"Thread: %d - Going to WAIT fo 10 seconds !\n",GetCurrentThreadId());

	DWORD				NumberOfBytesTransferred;
	ULONG_PTR			CompletionKey;
	LPOVERLAPPED		Overlapped;

	/*
	if (WaitForSingleObject(SD.Overlapped.hEvent,5*1000)==WAIT_TIMEOUT)
		wprintf(L"Overlapped->hEvent was NOT SET !\n");
	else
		wprintf(L"Overlapped->hEvent was SET !\n");
	*/

	BOOL				Ret=GetQueuedCompletionStatus(SD.CP,&NumberOfBytesTransferred,&CompletionKey,&Overlapped,10*1000);

	if (Ret==FALSE)
	{
		DWORD		LastError=GetLastError();

		if (LastError!=WAIT_TIMEOUT)
			wprintf(L"Thread: %d - Some other error: %d !\n",GetCurrentThreadId(),LastError);
		else
			wprintf(L"Thread: %d - IO Operation TIMED OUT !\n",GetCurrentThreadId());
	}
	else
	{
		wprintf(L"Thread: %d - IO Operation FINISHED - going to process data !\n",GetCurrentThreadId());

		void (*Callback)(DWORD, DWORD, LPOVERLAPPED, LPBYTE)=(void (*)(DWORD, DWORD, LPOVERLAPPED, LPBYTE)) CompletionKey;

		Callback(Overlapped->Internal,NumberOfBytesTransferred,Overlapped,SD.Buffer);

		wprintf(L"Thread: %d - IO Operation FINISHED - DATA PROCESSED !\n",GetCurrentThreadId());
	}

	if (WaitForSingleObject(SD.Overlapped.hEvent,0)==WAIT_TIMEOUT)
		wprintf(L"Overlapped->hEvent was NOT SET !\n");
	else
		wprintf(L"Overlapped->hEvent was SET !\n");

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE			ThreadP=NULL;
	HANDLE			ThreadC=NULL;

	ZeroMemory(&SD,sizeof(SD));

	SD.File=CreateFile(L"..\\TestFile.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,NULL);

	if (SD.File!=INVALID_HANDLE_VALUE)
	{
		SD.Overlapped.hEvent=CreateEvent(NULL,FALSE,FALSE,NULL);

		LARGE_INTEGER	Size;

		GetFileSizeEx(SD.File,&Size);

		SD.Size=Size.LowPart;

		SD.Buffer=new BYTE[Size.LowPart+sizeof(wchar_t)];

		if ((SD.CP=CreateIoCompletionPort(SD.File,NULL,(ULONG_PTR) &ProcessData,0))!=NULL)
		{
			ThreadC=(HANDLE) _beginthreadex(NULL,0,ThreadConsumer,NULL,0,NULL);
			ThreadP=(HANDLE) _beginthreadex(NULL,0,ThreadProducer,NULL,0,NULL);

			if (ThreadC!=NULL && ThreadP!=NULL)
			{
				HANDLE			ThreadHandles[]={ThreadC,ThreadP};

				WaitForMultipleObjects(2,ThreadHandles,TRUE,INFINITE);

				wprintf(L"Thread: %d - Both threads FINISHED !\n",GetCurrentThreadId());
			}

			if (ThreadC!=NULL)
			{
				CloseHandle(ThreadC);
				ThreadC=NULL;
			}

			if (ThreadP!=NULL)
			{
				CloseHandle(ThreadP);
				ThreadP=NULL;
			}
		}
		else
		{
			wprintf(L"Can't create CP !\n");
		}		
	}
	else
	{
		wprintf(L"Can't find file !\n");
	}

	if (SD.CP!=NULL)
	{
		CloseHandle(SD.CP);
		SD.CP=NULL;
	}

	if (SD.Buffer!=NULL)
	{
		delete[](SD.Buffer);
		SD.Buffer=NULL;
	}

	if (SD.Overlapped.hEvent!=NULL)
	{
		CloseHandle(SD.Overlapped.hEvent);
		SD.Overlapped.hEvent=NULL;
	}

	if (SD.File!=INVALID_HANDLE_VALUE && SD.File!=NULL)
	{
		CloseHandle(SD.File);
		SD.File=NULL;
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();

	Test();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------