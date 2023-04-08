#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
BYTE			*Buffer=NULL;
//------------------------------------------------------------------------------
void WINAPI MyCallback(DWORD ErrorCode, DWORD NumberOfBytesTransfered, LPOVERLAPPED Overlapped)
{
	// !!!!! Kod sa vykonava v TOM ISTOM THREADE co inicializoval Overlapped IO.

	int			Size=min(NumberOfBytesTransfered,200);

	Buffer[Size]='\0';
	Buffer[Size+1]='\0';

	wprintf(L"Thread: %d - Operation finished ASYNCHRONOUSLY - BytesRead: [%d], ErrorCode: [%d], Some Data [%s] !\n",GetCurrentThreadId(),NumberOfBytesTransfered,ErrorCode,Buffer);
}
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE			hFile=CreateFile(L"..\\TestFile.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,NULL);

	if (hFile==INVALID_HANDLE_VALUE)
	{
		wprintf(L"Can't find file !\n");
		return;
	}

	LARGE_INTEGER	Size;

	GetFileSizeEx(hFile,&Size);

	OVERLAPPED		OLAP;
	
	OLAP.Offset=0;
	OLAP.OffsetHigh=0;
	OLAP.hEvent=NULL;

	Buffer=new BYTE[Size.LowPart+sizeof(wchar_t)];

	if (ReadFileEx(hFile, Buffer, Size.LowPart*sizeof(BYTE), &OLAP, &MyCallback)==TRUE)
	{
		wprintf(L"Thread: %d - IO started - waiting for ALERTABLE wait !\n",GetCurrentThreadId());

		// !!! Cakam sam na seba - dal som tam iba nejaky DUMMY HANDLE - aby som SPOSOBIL ALERTABLE WAIT.
		DWORD		Ret=WaitForSingleObjectEx(GetCurrentThread(),3*1000,TRUE);

		// !!!!! Ak NEDAM ALERTABLE WAIT, tak sa CALLBACK NEVYKONA.
		//DWORD		Ret=WaitForSingleObjectEx(GetCurrentThread(),3*1000,FALSE);

		if (Ret==WAIT_TIMEOUT)
			wprintf(L"Thread: %d - after ALERTABLE wait - IO DIDN'T COMPLETED !\n",GetCurrentThreadId());
		else
			wprintf(L"Thread: %d - after ALERTABLE wait - IO DONE !\n",GetCurrentThreadId());
	}
	else
	{
		DWORD		LastError=GetLastError();

		wprintf(L"Some other error: %d !\n",LastError);
	}

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