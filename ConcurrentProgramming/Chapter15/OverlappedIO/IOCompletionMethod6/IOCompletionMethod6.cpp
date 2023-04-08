#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
BYTE			*Buffer=NULL;
//------------------------------------------------------------------------------
void CALLBACK MyIOCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Timer)
{
	LPOVERLAPPED		TypedOverlapped=(LPOVERLAPPED) Overlapped;

	// !!!!! Kod sa vykonava v INOM THREADE ako ten co inicializoval Overlapped IO.

	int			Size=min(NumberOfBytesTransferred,200);

	Buffer[Size]='\0';
	Buffer[Size+1]='\0';

	wprintf(L"Thread: %d - Operation finished ASYNCHRONOUSLY - BytesRead: [%d], ErrorCode: [%d], Overlapped.InternalHigh: [%d], Some Data [%s] !\n",GetCurrentThreadId(),NumberOfBytesTransferred,IoResult,TypedOverlapped->InternalHigh,Buffer);
}
//------------------------------------------------------------------------------
void Test(void)
{
	PTP_IO			IO;
	HANDLE			hFile=CreateFile(L"..\\TestFile.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,NULL);

	if (hFile==INVALID_HANDLE_VALUE)
	{
		wprintf(L"Can't find file !\n");
		return;
	}

	LARGE_INTEGER	Size;

	GetFileSizeEx(hFile,&Size);

	OVERLAPPED		OLAP;
	DWORD			NumberOfBytesRead;
	
	OLAP.Offset=0;
	OLAP.OffsetHigh=0;
	OLAP.hEvent=NULL;

	Buffer=new BYTE[Size.LowPart+sizeof(wchar_t)];

	// Vytvorim IO pool.
	IO=CreateThreadpoolIo(hFile,&MyIOCallback,L"SOME CONTEXT",NULL);

	// Spustim TP.
	StartThreadpoolIo(IO);

	// !!!!! Namiesto ReadFileEx() pouzivam klasicku ReadFile().
	if (ReadFile(hFile, Buffer, Size.LowPart*sizeof(BYTE), &NumberOfBytesRead, &OLAP)==TRUE)
	{
		Buffer[NumberOfBytesRead]='\0';
		Buffer[NumberOfBytesRead+1]='\0';
		wprintf(L"Data: [%s]\n",Buffer);
		wprintf(L"\n\n\nOperation finished SYNCHRONOUSLY - BytesRead: [%d] !\n",NumberOfBytesRead);
	}
	else
	{
		DWORD		LastError=GetLastError();

		if (LastError==ERROR_IO_PENDING)
		{
			wprintf(L"Thread: %d - IO started - waiting to FINISH - NumberOfBytesRead: [%d] !\n",GetCurrentThreadId(),NumberOfBytesRead);

			// CAKA NA SKONCENIE CELEJ ZACATEJ IO OPERACIE a NIE CALLBACK.
			WaitForThreadpoolIoCallbacks(IO,FALSE);

			wprintf(L"Thread: %d - IO FINISHED !\n",GetCurrentThreadId());
		}
		else
		{
			wprintf(L"Some other error: %d !\n",LastError);
		}
	}

	CloseThreadpoolIo(IO);

	if (Buffer!=NULL)
	{
		delete[](Buffer);
		Buffer=NULL;
	}

	CloseHandle(hFile);
	hFile=NULL;
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