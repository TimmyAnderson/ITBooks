#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
BYTE*				Buffer;
//------------------------------------------------------------------------------
void PrintArray(wchar_t* Header, BYTE *Data, int Size)
{
	wprintf_s(Header);
	wprintf_s(L"TID: [%d] ",GetCurrentThreadId());
	wprintf_s(L"[");

	for(int i=0;i<Size;i++)
		printf_s("%c",Data[i]);

	wprintf_s(L"] !\n");
}
//------------------------------------------------------------------------------
void ProcessResults(wchar_t* Text, BYTE* Buffer, OVERLAPPED& Op)
{
	const int			BUF_SIZE=1024;
	wchar_t				TextBuf[BUF_SIZE];
	int					DataSize=Op.InternalHigh;

	StringCchPrintf(TextBuf,BUF_SIZE,L"%s - EC: [%d], Bytes read: [%d], Data: ",Text,Op.Internal,DataSize);
	PrintArray(TextBuf,Buffer,DataSize);
}
//------------------------------------------------------------------------------
void WINAPI OverlappedFinished(DWORD ErrorCode, DWORD NumberOfBytesTransfered, OVERLAPPED* Overlapped)
{
	wprintf_s(L"TID: [%d] - INSIDE APC !\n",GetCurrentThreadId());
	ProcessResults(L"Operation: ",Buffer,*Overlapped);
}
//------------------------------------------------------------------------------
bool DoOperation(int Offset, HANDLE FileHandle, DWORD Size, BYTE* Buffer, OVERLAPPED& Op)
{
	// Musim pripravit strukturu OVERLAPPED.
	ZeroMemory(&Op,sizeof(OVERLAPPED));

	// Citam od zaciatku suboru.
	Op.Offset=Offset;

	// Pre APC musim pouzit ReadFileEx().
	DWORD			Ret=ReadFileEx(FileHandle,Buffer,Size,&Op,OverlappedFinished);

	if (Ret==TRUE)
	{
		wprintf_s(L"ASYNCHRONOUS operation STARTED !\n");
		return(true);
	}
	else
	{
		DWORD		LE=GetLastError();

		PrintErrorCodeToConsole(L"ReadFile()",LE);
		return(false);
	}
}
//------------------------------------------------------------------------------
void Test(void)
{
	HANDLE				FileHandle;
	wchar_t				FileName[]={L"Timmy.txt"};
	DWORD				SectorSize;
	DWORD				Size;
	wchar_t				CurrentDirectory[1024];

	FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);
	// Ked AKTIVUJEM CACHE (vyhodenim FILE_FLAG_NO_BUFFERING) je VYSOKA PRAVDEPODOBNOST, ze operacie prebehne SYNCHRONNE, lebo subor bude v Cache.
	//FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

	GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory);
	GetDiskFreeSpace(CurrentDirectory,NULL,&SectorSize,NULL,NULL);

	Size=SectorSize;

	Buffer=(PBYTE) _aligned_malloc(Size,SectorSize);

	OVERLAPPED			Op;
	bool				Ret;

	wprintf_s(L"Main TID: [%d] !\n",GetCurrentThreadId());

	Ret=DoOperation(0,FileHandle, Size, Buffer, Op);

	if (Ret==true)
	{
		wprintf_s(L"TID: [%d] - BEFORE SleepEx() !\n",GetCurrentThreadId());

		// Vykonam APC wait.
		// Ked sa skonci APC volanie, tak SleepEx() HNED SKONCI.
		SleepEx(INFINITE,TRUE);

		wprintf_s(L"TID: [%d] - AFTER SleepEx() !\n",GetCurrentThreadId());
	}

	_aligned_free(Buffer);
	Buffer=NULL;

	CloseHandle(FileHandle);
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