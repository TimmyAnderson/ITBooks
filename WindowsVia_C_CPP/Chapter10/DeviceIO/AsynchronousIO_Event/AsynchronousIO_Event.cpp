#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
void PrintArray(wchar_t* Header, BYTE *Data, int Size)
{
	wprintf_s(Header);
	wprintf_s(L"[");

	for(int i=0;i<Size;i++)
		printf_s("%c",Data[i]);

	wprintf_s(L"] !\n");
}
//------------------------------------------------------------------------------
bool DoOperation(int Offset, HANDLE FileHandle, DWORD Size, BYTE* Buffer, OVERLAPPED& Op, HANDLE EventHandle)
{
	// Musim pripravit strukturu OVERLAPPED.
	ZeroMemory(&Op,sizeof(OVERLAPPED));

	// Citam od zaciatku suboru.
	Op.Offset=Offset;
	Op.hEvent=EventHandle;

	DWORD			Ret=ReadFile(FileHandle,Buffer,Size,NULL,&Op);

	if (Ret==TRUE)
	{
		wprintf_s(L"Data was read SYNCHRONOUSLY !\n");
		return(true);
	}
	else
	{
		DWORD		LE=GetLastError();

		if (LE==ERROR_IO_PENDING)
		{
			wprintf_s(L"ASYNCHRONOUS operation STARTED !\n");
			return(true);
		}
		else
		{
			PrintErrorCodeToConsole(L"ReadFile()",LE);
			return(false);
		}
	}
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
void Test(void)
{
	BYTE*				Buffer;
	HANDLE				FileHandle;
	wchar_t				FileName[]={L"Timmy.txt"};
	DWORD				SectorSize;
	DWORD				Size;
	HANDLE				EventHandle=CreateEvent(NULL,FALSE,FALSE,NULL);
	wchar_t				CurrentDirectory[1024];

	FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);
	//FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

	GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory);
	GetDiskFreeSpace(CurrentDirectory,NULL,&SectorSize,NULL,NULL);

	Size=SectorSize;

	Buffer=(PBYTE) _aligned_malloc(Size,SectorSize);

	OVERLAPPED			Op;
	bool				Ret;

	Ret=DoOperation(0,FileHandle, Size, Buffer, Op, EventHandle);

	if (Ret==true)
	{
		WaitForSingleObject(EventHandle,INFINITE);
		ProcessResults(L"Operation: ",Buffer,Op);
	}

	_aligned_free(Buffer);
	Buffer=NULL;

	CloseHandle(FileHandle);
	CloseHandle(EventHandle);
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