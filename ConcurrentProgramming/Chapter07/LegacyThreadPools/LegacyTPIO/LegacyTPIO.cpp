//------------------------------------------------------------------------------
#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
//------------------------------------------------------------------------------
char			Buffer[1024];
//------------------------------------------------------------------------------
void CALLBACK MyIOCallback(DWORD ErrorCode, DWORD NumberOfBytesTransfered, LPOVERLAPPED Overlapped)
{
	DWORD			TID=GetCurrentThreadId();

	wprintf(L"Time: %d, TID: %d, Result: %d, Bytes Transferred: %d - BEGIN !\n",GetTickCount(),TID,ErrorCode,NumberOfBytesTransfered);

	if (ErrorCode==S_OK)
		// Musi byt printf() lebo text je v ASNI a ie UNICODE.
		printf("OPERATION FINISHED SUCESSFULLY, Data: [%s] !\n",Buffer);
	else
		wprintf(L"OPERATION FAILED !!!\n");

	Sleep(5*1000);

	wprintf(L"Time: %d, TID: %d - END !\n",GetTickCount(),TID);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	ZeroMemory(Buffer,sizeof(Buffer));

	HANDLE				MyFile;
		
	MyFile=CreateFile(L"TEST.txt",GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

	if (MyFile==INVALID_HANDLE_VALUE)
	{
		wprintf(L"Can't OPEN FILE !\n");
		return;
	}

	BindIoCompletionCallback(MyFile,MyIOCallback,0);

	wprintf(L"Time: %d, IO REGISTRED !\n",GetTickCount());

	OVERLAPPED			OP;

	ZeroMemory(&OP,sizeof(OP));
	
	// !!!!! Az teraz mozem zacat IO operaciu.
	ReadFile(MyFile,Buffer,1024,NULL,&OP);

	wprintf(L"Time: %d, IO IN PROGRESS - press any key to STOP !\n",GetTickCount());
	_getch();
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