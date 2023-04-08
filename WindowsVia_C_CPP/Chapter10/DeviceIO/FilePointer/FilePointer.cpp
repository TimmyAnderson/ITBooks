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
void Test(void)
{
	const int			BUFFER_SIZE=10;
	BYTE				Buffer[BUFFER_SIZE];
	HANDLE				Handle1;
	HANDLE				Handle2;
	HANDLE				DupHandle2;
	wchar_t				FileName[]={L"Timmy.txt"};
	ULARGE_INTEGER		Size;
	LARGE_INTEGER		LISize;
	DWORD				Read;

	Handle1=CreateFile(FileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	Size.LowPart=GetFileSize(Handle1,&Size.HighPart);
	GetFileSizeEx(Handle1,&LISize);

	wprintf_s(L"Size: [%d,%d] !\n",Size.HighPart,Size.LowPart);
	wprintf_s(L"LISize: [%d,%d] !\n",LISize.HighPart,LISize.LowPart);

	// Vytvorim HANDLE a NOVY KO na TEN ISTY SUBOR - maju KAZDY VLASTNY POINTER.
	Handle2=CreateFile(FileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	// Duplikujem HANDLE na TEN ISTY KO - MAJU SPOLOCNY POINTER.
	DuplicateHandle(GetCurrentProcess(),Handle2,GetCurrentProcess(),&DupHandle2,0,FALSE,DUPLICATE_SAME_ACCESS);

	ReadFile(Handle1,Buffer,BUFFER_SIZE,&Read,NULL);
	PrintArray(L"Handle1 - READ 1: ",Buffer,BUFFER_SIZE);
	ReadFile(Handle2,Buffer,BUFFER_SIZE,&Read,NULL);
	PrintArray(L"Handle2 - READ 1: ",Buffer,BUFFER_SIZE);
	ReadFile(DupHandle2,Buffer,BUFFER_SIZE,&Read,NULL);
	PrintArray(L"DupHandle2 - READ 1: ",Buffer,BUFFER_SIZE);

	ReadFile(Handle1,Buffer,BUFFER_SIZE,&Read,NULL);
	PrintArray(L"Handle1 - READ 2: ",Buffer,BUFFER_SIZE);
	ReadFile(Handle2,Buffer,BUFFER_SIZE,&Read,NULL);
	PrintArray(L"Handle2 - READ 2: ",Buffer,BUFFER_SIZE);
	ReadFile(DupHandle2,Buffer,BUFFER_SIZE,&Read,NULL);
	PrintArray(L"DupHandle2 - READ 2: ",Buffer,BUFFER_SIZE);

	CloseHandle(Handle1);
	CloseHandle(Handle2);
	CloseHandle(DupHandle2);
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