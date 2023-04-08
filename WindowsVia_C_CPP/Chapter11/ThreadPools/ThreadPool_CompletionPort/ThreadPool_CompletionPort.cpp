#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "COVERLAPPEDWithData.h"
//------------------------------------------------------------------------------
const int		KEY_EXIT=-1;
// Urcuje ci sa v Completion thread bude vypisovat na konzolu.
bool			DoPrint=true;
//------------------------------------------------------------------------------
void CALLBACK CPFunction(PTP_CALLBACK_INSTANCE Instance, PVOID Context, PVOID Overlapped, ULONG IoResult, ULONG_PTR NumberOfBytesTransferred, PTP_IO IO)
{
	WriteDebugText(L"Thread STARTED !\n");

	wchar_t							PrintBuffer[4096];
	const int						MAX_TO_PRINT=50;
	ULONG_PTR						BytesToPrint=NumberOfBytesTransferred;

	if (BytesToPrint>MAX_TO_PRINT)
		BytesToPrint=MAX_TO_PRINT;

	// Konvertujem OVERLAPPED na COVERLAPPEDWithData.
	COVERLAPPEDWithData*			TypedData=(COVERLAPPEDWithData*) Overlapped;
	wchar_t*						Text=new wchar_t[BytesToPrint+1];

	for(DWORD i=0;i<BytesToPrint;i++)
		Text[i]=TypedData->Data[i];

	Text[BytesToPrint]='\0';

	StringCchPrintf(PrintBuffer,_countof(PrintBuffer),L"Bytes: [%d], Result: [%d], Data: [%s] !\n",NumberOfBytesTransferred,IoResult,Text);
	WriteDebugText(PrintBuffer);

	delete[](Text);

	WriteDebugText(L"Thread STOPPED !\n");
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	const int			NUMBER_OF_OPERATION=10;
	HANDLE				FileHandle=NULL;
	wchar_t				FileName[]={L"Timmy.txt"};
	DWORD				SectorSize;
	DWORD				Size;
	wchar_t				CurrentDirectory[1024];
	PTP_IO				IO;

	FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);

	GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory);
	GetDiskFreeSpace(CurrentDirectory,NULL,&SectorSize,NULL,NULL);

	Size=SectorSize;

	LPCOVERLAPPEDWithData	Op[NUMBER_OF_OPERATION];

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		Op[i]=(LPCOVERLAPPEDWithData) _aligned_malloc(sizeof(COVERLAPPEDWithData),SectorSize);

		ZeroMemory(Op[i],sizeof(COVERLAPPEDWithData));
		Op[i]->Offset=0;
		Op[i]->Data=(PBYTE) _aligned_malloc(Size,SectorSize);
	}

	IO=CreateThreadpoolIo(FileHandle,CPFunction,L"Timmy.txt",NULL);

	// Spustim IO operacie.
	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		// !!!!! MUSI BYT VOLANA PRED KAZDOU IO OPERACIOU.
		// !!!!! Ak to nespravim, tak PRORGAM ZLYHA.
		// !!!!! Z MSND - Failure to do so will cause the thread pool to ignore an I/O operation when it completes and will cause StartThreadpoolIo(IO).
		StartThreadpoolIo(IO);

		DWORD					Ret=ReadFile(FileHandle,Op[i]->Data,Size,NULL,Op[i]);

		if (Ret==TRUE)
			wprintf_s(L"Data was read SYNCHRONOUSLY !\n");
		else
		{
			DWORD				LE=GetLastError();

			if (LE==ERROR_IO_PENDING)
				wprintf_s(L"ASYNCHRONOUS operation STARTED !\n");
			else
			{
				PrintErrorCodeToConsole(L"ReadFile()",LE);

				// !!! Ak zlyha IO operacia MUSIM zavolat CancelThreadpoolIo().
				CancelThreadpoolIo(IO);
			}
		}
	}

	_getch();

	WaitForThreadpoolIoCallbacks(IO,FALSE);

	CloseThreadpoolIo(IO);

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		_aligned_free(Op[i]->Data);
		Op[i]->Data=NULL;

		_aligned_free(Op[i]);
		Op[i]=NULL;
	}

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