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
	BYTE*				Buffer1;
	BYTE*				Buffer2;
	HANDLE				FileHandle;
	wchar_t				FileName[]={L"Timmy.txt"};
	DWORD				SectorSize;
	DWORD				Size;
	HANDLE				EventHandle1=CreateEvent(NULL,FALSE,FALSE,NULL);
	HANDLE				EventHandle2=CreateEvent(NULL,FALSE,FALSE,NULL);
	wchar_t				CurrentDirectory[1024];

	// Musim nastavit flag FILE_FLAG_OVERLAPPED.
	// !!!!! Pre DEBUG ucely VYPNEM CACHE - FILE_FLAG_NO_BUFFERING.
	// !!!!! Pri vypnutej Cache plati, ze mozem citat IBA data o NASOBKU VELKOSTI SEKTORA.
	// !!!!! Pri vypnutej Cache plati, ze BUFFER musi by ZAROVNANY na VELKOST SEKTORA.
	// !!!!! Pri vypnutej Cache plati, ze OFFSET odkial zacinam IO operaciu MUSI MAT NASOBOK VELKOSTI SEKTORA.
	FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);
	// Ked AKTIVUJEM CACHE (vyhodenim FILE_FLAG_NO_BUFFERING) je VYSOKA PRAVDEPODOBNOST, ze operacie prebehen SYNCHRONNE, lebo subor bude v Cache.
	//FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

	GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory);
	GetDiskFreeSpace(CurrentDirectory,NULL,&SectorSize,NULL,NULL);

	Size=SectorSize;

	// Pripravim si buffers - jeden pre KAZDU OPERACIU.
	// !!!!! Pri vypnutej Cache plati, ze BUFFER musi by ZAROVNANY na VELKOST SEKTORA.
	Buffer1=(PBYTE) _aligned_malloc(Size,SectorSize);
	Buffer2=(PBYTE) _aligned_malloc(Size,SectorSize);

	// Pre KAZDU IO OPERACIU MUSIM VYTVORIT VLASTNU OVERLAPPED STRUKTURU.
	OVERLAPPED			Op1;
	OVERLAPPED			Op2;
	bool				Ret1;
	bool				Ret2;

	// !!!!! Pri vypnutej Cache plati, ze OFFSET odkial zacinam IO operaciu MUSI MAT NASOBOK VELKOSTI SEKTORA.
	Ret1=DoOperation(0,FileHandle, Size, Buffer1, Op1, EventHandle1);
	Ret2=DoOperation(0,FileHandle, Size, Buffer2, Op2, EventHandle2);

	if (Ret1==true)
	{
		WaitForSingleObject(EventHandle1,INFINITE);
		ProcessResults(L"Operation 1: ",Buffer1,Op1);
	}

	if (Ret2==true)
	{
		WaitForSingleObject(EventHandle2,INFINITE);
		ProcessResults(L"Operation 2: ",Buffer2,Op2);
	}

	// Pamat musim uvolnit volanim _aligned_free().
	_aligned_free(Buffer1);
	Buffer1=NULL;

	_aligned_free(Buffer2);
	Buffer2=NULL;

	CloseHandle(FileHandle);
	CloseHandle(EventHandle1);
	CloseHandle(EventHandle2);
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