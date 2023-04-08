//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
char			Buffer[1024];
//------------------------------------------------------------------------------
void CALLBACK MyIOCallback(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO Timer)
{
	wchar_t			*Message=(wchar_t*) Context;
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d, Result: %d, Bytes Transferred: %d  - [%s],  BEGIN !\n",GetTickCount(),TID,IoResult,NumberOfBytesTransferred,Message);

	if (IoResult==NO_ERROR)
		// Musi byt printf() lebo text je v ASNI a ie UNICODE.
		printf("OPERATION FINISHED SUCESSFULLY, Data: %s !\n",Buffer);
	else
		wprintf(L"OPERATION FAILED !!!\n");

	Sleep(5*1000);

	wprintf(L"Time: %d, TID: %d - [%s] END !\n",GetTickCount(),TID,Message);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	ZeroMemory(Buffer,sizeof(Buffer));

	PTP_IO				IO;
	HANDLE				MyFile;
		
	MyFile=CreateFile(L"TEST.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

	if (MyFile==INVALID_HANDLE_VALUE)
	{
		wprintf(L"Can't OPEN FILE !\n");
		return;
	}

	IO=CreateThreadpoolIo(MyFile,&MyIOCallback,L"SOME CONTEXT",NULL);

	wprintf(L"Time: %d, STARTING IO !\n",GetTickCount());

	StartThreadpoolIo(IO);

	OVERLAPPED			OP;

	ZeroMemory(&OP,sizeof(OP));
	
	// !!!!! Az teraz mozem zacat IO operaciu.
	ReadFile(MyFile,Buffer,1024,NULL,&OP);

	wprintf(L"Time: %d, WAITING for IO to COMPLETE !\n",GetTickCount());

	// CAKA NA SKONCENIE CELEJ ZACATEJ IO OPERACIE a NIE CALLBACK.
	WaitForThreadpoolIoCallbacks(IO,FALSE);

	CloseThreadpoolIo(IO);

	wprintf(L"Time: %d, IO FINISHED !\n",GetTickCount());
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