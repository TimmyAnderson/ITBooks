#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include "COVERLAPPEDWithData.h"
//------------------------------------------------------------------------------
const int		KEY_EXIT=-1;
HANDLE			HCP;
volatile long	CPThreadCounter=0;
volatile long	CPThreadCounterMax=0;
volatile long	CPThreadCounterMax1=0;
volatile long	CPThreadCounterMax2=0;
volatile long	CPThreadCounterMax3=0;
volatile long	CPThreadCounterMax4=0;
// Urcuje ci sa v Completion thread bude vypisovat na konzolu.
bool			DoPrint=true;
// Urcuje ci sa v Completion thread bude simulovat dlha operacia.
bool			SimulateLongOperation=true;
// Urcuje ci sa v Completion thread vyvola Sleep().
bool			SimulateWait=false;
//------------------------------------------------------------------------------
unsigned int WINAPI MyCPThread(void* Param)
{
	WriteDebugText(L"Thread STARTED !\n");

	LONG							Dummy=0;

	while(true)
	{
		DWORD						NumberOfBytesTransferred=0;
		ULONG_PTR					Key;
		OVERLAPPED*					O;

		if (DoPrint==true)
			WriteDebugText(L"BEFORE GetQueuedCompletionStatus() !\n");

		// !!! Zavolanim tejto funkcie spravim THREAD - COMPLETION PORT THREADOM.
		BOOL						Ret=GetQueuedCompletionStatus(HCP,&NumberOfBytesTransferred,&Key,&O,INFINITE);

		InterlockedIncrement(&CPThreadCounter);

		if (CPThreadCounter>CPThreadCounterMax1)
			CPThreadCounterMax1=CPThreadCounter;

		if (DoPrint==true)
			WriteDebugText(L"AFTER GetQueuedCompletionStatus() !\n");

		if (CPThreadCounter>CPThreadCounterMax2)
			CPThreadCounterMax2=CPThreadCounter;

		// Odporucane spracovanie chyby.
		if (Ret==FALSE)
		{
			DWORD					Err=GetLastError();

			if (Ret==WAIT_TIMEOUT)
				WriteDebugText(L"TIMEOUT EXPIRED !\n");
			else
				PrintErrorCodeToConsole(L"GetQueuedCompletionStatus()",Err);
		}
		else
		{
			if (Key==((ULONG_PTR) KEY_EXIT))
			{
				InterlockedDecrement(&CPThreadCounter);
				WriteDebugText(L"Thread received EXIT MESSAGE !\n");
				break;
			}

			// Simulujem nejaku cinnost na spomalenie CPU.
			if (SimulateLongOperation==true)
			{
				for (int i=0;i<1000*1000;i++)
					InterlockedIncrement(&Dummy);
			}

			// Konvertujem OVERLAPPED na COVERLAPPEDWithData.
			COVERLAPPEDWithData*	TypedData=(COVERLAPPEDWithData*) O;

			wchar_t					PrintBuffer[4096];
			wchar_t*				Text=new wchar_t[NumberOfBytesTransferred+1];

			// Pocitadlo po NEW.
			if (CPThreadCounter>CPThreadCounterMax3)
				CPThreadCounterMax3=CPThreadCounter;

			for(DWORD i=0;i<NumberOfBytesTransferred;i++)
				Text[i]=TypedData->Data[i];

			Text[NumberOfBytesTransferred]='\0';

			StringCchPrintf(PrintBuffer,_countof(PrintBuffer),L"!!! Read [%d] bytes, Key: [%d], Data: [%s] !\n",NumberOfBytesTransferred,Key,Text);

			if (DoPrint==true)
				WriteDebugText(PrintBuffer);

			delete[](Text);

			// Pocitadlo po DELETE.
			if (CPThreadCounter>CPThreadCounterMax4)
				CPThreadCounterMax4=CPThreadCounter;

			// Simulacia WAIT.
			if (SimulateWait==true)
			{
				WriteDebugText(L"????? Thread is going to WAIT !\n");
				Sleep(1000);
				WriteDebugText(L"????? Thread FINISHED WAIT !\n");
			}

			InterlockedDecrement(&CPThreadCounter);
		}
	}

	WriteDebugText(L"Thread will FINISH !\n");

	return(0);
}
//------------------------------------------------------------------------------
// NEPOUZIVA VYPIS na KONZOLU, pretoze ten sposoboval HODENIE THREADU do PAUSED LIST a preto moze i VIAC THREADS ako je stanoveny limit v CreateIoCompletionPort() vykonavat kod.
unsigned int WINAPI MyCPThreadCounter(void* Param)
{
	WriteDebugText(L"Thread STARTED !\n");

	LONG							Dummy=0;

	while(true)
	{
		DWORD						NumberOfBytesTransferred=0;
		ULONG_PTR					Key;
		OVERLAPPED*					O;

		// !!! Zavolanim tejto funkcie spravim THREAD - COMPLETION PORT THREADOM.
		BOOL						Ret=GetQueuedCompletionStatus(HCP,&NumberOfBytesTransferred,&Key,&O,INFINITE);

		InterlockedIncrement(&CPThreadCounter);

		if (CPThreadCounter>CPThreadCounterMax)
			CPThreadCounterMax=CPThreadCounter;

		// Odporucane spracovanie chyby.
		if (Ret==FALSE)
		{
			DWORD					Err=GetLastError();

			if (Ret==WAIT_TIMEOUT)
				WriteDebugText(L"TIMEOUT EXPIRED !\n");
			else
				PrintErrorCodeToConsole(L"GetQueuedCompletionStatus()",Err);
		}
		else
		{
			if (Key==((ULONG_PTR) KEY_EXIT))
			{
				InterlockedDecrement(&CPThreadCounter);
				WriteDebugText(L"Thread received EXIT MESSAGE !\n");
				break;
			}

			// Simulujem nejaku cinnost na spomalenie CPU.
			if (SimulateLongOperation==true)
			{
				for (int i=0;i<1000*1000;i++)
					InterlockedIncrement(&Dummy);
			}

			// Konvertujem OVERLAPPED na COVERLAPPEDWithData.
			COVERLAPPEDWithData*	TypedData=(COVERLAPPEDWithData*) O;

			// Simulacia WAIT.
			if (SimulateWait==true)
			{
				WriteDebugText(L"????? Thread is going to WAIT !\n");
				Sleep(1000);
				WriteDebugText(L"????? Thread FINISHED WAIT !\n");
			}

			InterlockedDecrement(&CPThreadCounter);
		}
	}

	WriteDebugText(L"Thread will FINISH !\n");

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test1(void)
{
	const int			MAX_NUMBER_OF_CONCURRENT_OPERATIONS=3;
	const int			NUMBER_OF_OPERATION=20;
	const int			NUMBER_OF_THREADS=10;
	HANDLE				Threads[NUMBER_OF_THREADS];
	HANDLE				FileHandle;
	wchar_t				FileName[]={L"Timmy.txt"};
	DWORD				SectorSize;
	DWORD				Size;
	wchar_t				CurrentDirectory[1024];

	// Maximalna priorita pre thread, aby VSETKY IO OPERACIE boliz aslane SKOR ako sa co i len prva z nich stihne vykonat.
	SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST);

	FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);
	//FileHandle=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

	// Vytvorim Completion Port.
	HCP=CreateIoCompletionPort(FileHandle,NULL,(ULONG_PTR) 0,MAX_NUMBER_OF_CONCURRENT_OPERATIONS);
	//HCP=CreateIoCompletionPort(FileHandle,NULL,(ULONG_PTR) 0,1);

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

	// Spustim threads.
	for (int i=0;i<NUMBER_OF_THREADS;i++)
		Threads[i]=(HANDLE)_beginthreadex(NULL,0,MyCPThread,(void*) (i+1),0,NULL);

	// Pockam kym sa ostatne threads spustia.
	Sleep(500);

	// Spustim IO operacie.
	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		DWORD					Ret=ReadFile(FileHandle,Op[i]->Data,Size,NULL,Op[i]);

		if (Ret==TRUE)
			wprintf_s(L"Data was read SYNCHRONOUSLY !\n");
		else
		{
			DWORD				LE=GetLastError();

			if (LE==ERROR_IO_PENDING)
				wprintf_s(L"ASYNCHRONOUS operation STARTED !\n");
			else
				PrintErrorCodeToConsole(L"ReadFile()",LE);
		}
	}

	_getch();

	for (int i=0;i<NUMBER_OF_THREADS;i++)
		PostQueuedCompletionStatus(HCP,0,(ULONG_PTR) KEY_EXIT,NULL);

	// Pockam na ukoncenie vsetkych Threads.
	WaitForMultipleObjects(NUMBER_OF_THREADS,Threads,TRUE,INFINITE);

	for (int i=0;i<NUMBER_OF_THREADS;i++)
	{
		CloseHandle(Threads[i]);
		Threads[i]=NULL;
	}

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		_aligned_free(Op[i]->Data);
		Op[i]->Data=NULL;

		_aligned_free(Op[i]);
		Op[i]=NULL;
	}

	CloseHandle(HCP);

	CloseHandle(FileHandle);

	wprintf_s(L"\nCOUNTER 1: [%d] !\n",CPThreadCounterMax1);
	wprintf_s(L"\nCOUNTER 2: [%d] !\n",CPThreadCounterMax2);
	wprintf_s(L"\nCOUNTER 3: [%d] !\n",CPThreadCounterMax3);
	wprintf_s(L"\nCOUNTER 4: [%d] !\n",CPThreadCounterMax4);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	const int					MAX_NUMBER_OF_CONCURRENT_OPERATIONS=3;
	const int					NUMBER_OF_OPERATION=20;
	const int					NUMBER_OF_THREADS=10;
	const int					NUMBER_OF_FILES=5;

	HANDLE						Threads[NUMBER_OF_THREADS];
	HANDLE						FileHandles[NUMBER_OF_FILES];
	DWORD						SectorSize;
	DWORD						Size;
	wchar_t						CurrentDirectory[1024];

	// Maximalna priorita pre thread, aby VSETKY IO OPERACIE boliz aslane SKOR ako sa co i len prva z nich stihne vykonat.
	SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST);

	// Vytvorim Completion Port.
	HCP=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,MAX_NUMBER_OF_CONCURRENT_OPERATIONS);
	//HCP=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);

	wprintf_s(L"HPC: [%d] !\n",HCP);

	for (int i=0;i<NUMBER_OF_FILES;i++)
	{
		wchar_t					FileName[1024];
		
		StringCchPrintf(FileName,_countof(FileName),L"File%d.txt",i+1);

		FileHandles[i]=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);
		//FileHandles[i]=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

		// Zaradim FILE HANDLE do CompletionPort.
		HCP=CreateIoCompletionPort(FileHandles[i],HCP,(ULONG_PTR) (i+1),0);

		wprintf_s(L"HPC: [%d] !\n",HCP);
	}

	GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory);
	GetDiskFreeSpace(CurrentDirectory,NULL,&SectorSize,NULL,NULL);

	Size=SectorSize;

	LPCOVERLAPPEDWithData		Op[NUMBER_OF_OPERATION];

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		Op[i]=(LPCOVERLAPPEDWithData) _aligned_malloc(sizeof(COVERLAPPEDWithData),SectorSize);

		ZeroMemory(Op[i],sizeof(COVERLAPPEDWithData));
		Op[i]->Offset=0;
		Op[i]->Data=(PBYTE) _aligned_malloc(Size,SectorSize);
	}

	// Spustim threads.
	for (int i=0;i<NUMBER_OF_THREADS;i++)
		Threads[i]=(HANDLE)_beginthreadex(NULL,0,MyCPThread,(void*) (i+1),0,NULL);

	// Pockam kym sa ostatne threads spustia.
	Sleep(500);

	// Spustim IO operacie.
	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		HANDLE					FileHandle=FileHandles[i%NUMBER_OF_FILES];
		DWORD					Ret=ReadFile(FileHandle,Op[i]->Data,Size,NULL,Op[i]);

		if (Ret==TRUE)
			wprintf_s(L"Data was read SYNCHRONOUSLY !\n");
		else
		{
			DWORD				LE=GetLastError();

			if (LE==ERROR_IO_PENDING)
				wprintf_s(L"ASYNCHRONOUS operation STARTED !\n");
			else
				PrintErrorCodeToConsole(L"ReadFile()",LE);
		}
	}

	_getch();

	for (int i=0;i<NUMBER_OF_THREADS;i++)
		PostQueuedCompletionStatus(HCP,0,(ULONG_PTR) KEY_EXIT,NULL);

	// Pockam na ukoncenie vsetkych Threads.
	WaitForMultipleObjects(NUMBER_OF_THREADS,Threads,TRUE,INFINITE);

	for (int i=0;i<NUMBER_OF_THREADS;i++)
	{
		CloseHandle(Threads[i]);
		Threads[i]=NULL;
	}

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		_aligned_free(Op[i]->Data);
		Op[i]->Data=NULL;

		_aligned_free(Op[i]);
		Op[i]=NULL;
	}

	CloseHandle(HCP);

	for (int i=0;i<NUMBER_OF_FILES;i++)
	{
		CloseHandle(FileHandles[i]);
		FileHandles[i]=NULL;
	}

	wprintf_s(L"\nCOUNTER 1: [%d] !\n",CPThreadCounterMax1);
	wprintf_s(L"\nCOUNTER 2: [%d] !\n",CPThreadCounterMax2);
	wprintf_s(L"\nCOUNTER 3: [%d] !\n",CPThreadCounterMax3);
	wprintf_s(L"\nCOUNTER 4: [%d] !\n",CPThreadCounterMax4);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	const int					MAX_NUMBER_OF_CONCURRENT_OPERATIONS=3;
	const int					NUMBER_OF_OPERATION=100;
	const int					NUMBER_OF_THREADS=20;
	const int					NUMBER_OF_FILES=5;

	HANDLE						Threads[NUMBER_OF_THREADS];
	HANDLE						FileHandles[NUMBER_OF_FILES];
	DWORD						SectorSize;
	DWORD						Size;
	wchar_t						CurrentDirectory[1024];

	// Maximalna priorita pre thread, aby VSETKY IO OPERACIE boliz aslane SKOR ako sa co i len prva z nich stihne vykonat.
	SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST);

	// Vytvorim Completion Port.
	HCP=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,MAX_NUMBER_OF_CONCURRENT_OPERATIONS);
	//HCP=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);

	wprintf_s(L"HPC: [%d] !\n",HCP);

	for (int i=0;i<NUMBER_OF_FILES;i++)
	{
		wchar_t					FileName[1024];
		
		StringCchPrintf(FileName,_countof(FileName),L"File%d.txt",i+1);

		FileHandles[i]=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);
		//FileHandles[i]=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

		// Zaradim FILE HANDLE do CompletionPort.
		HCP=CreateIoCompletionPort(FileHandles[i],HCP,(ULONG_PTR) (i+1),0);

		wprintf_s(L"HPC: [%d] !\n",HCP);
	}

	GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory);
	GetDiskFreeSpace(CurrentDirectory,NULL,&SectorSize,NULL,NULL);

	Size=SectorSize;

	LPCOVERLAPPEDWithData		Op[NUMBER_OF_OPERATION];

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		Op[i]=(LPCOVERLAPPEDWithData) _aligned_malloc(sizeof(COVERLAPPEDWithData),SectorSize);

		ZeroMemory(Op[i],sizeof(COVERLAPPEDWithData));
		Op[i]->Offset=0;
		Op[i]->Data=(PBYTE) _aligned_malloc(Size,SectorSize);
	}

	// Spustim threads.
	for (int i=0;i<NUMBER_OF_THREADS;i++)
		Threads[i]=(HANDLE)_beginthreadex(NULL,0,MyCPThreadCounter,(void*) (i+1),0,NULL);

	// Pockam kym sa ostatne threads spustia.
	Sleep(500);

	// Spustim IO operacie.
	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		HANDLE					FileHandle=FileHandles[i%NUMBER_OF_FILES];
		DWORD					Ret=ReadFile(FileHandle,Op[i]->Data,Size,NULL,Op[i]);

		if (Ret==TRUE)
			wprintf_s(L"Data was read SYNCHRONOUSLY !\n");
		else
		{
			DWORD				LE=GetLastError();

			if (LE==ERROR_IO_PENDING)
				wprintf_s(L"ASYNCHRONOUS operation STARTED !\n");
			else
				PrintErrorCodeToConsole(L"ReadFile()",LE);
		}
	}

	_getch();

	for (int i=0;i<NUMBER_OF_THREADS;i++)
		PostQueuedCompletionStatus(HCP,0,(ULONG_PTR) KEY_EXIT,NULL);

	// Pockam na ukoncenie vsetkych Threads.
	WaitForMultipleObjects(NUMBER_OF_THREADS,Threads,TRUE,INFINITE);

	for (int i=0;i<NUMBER_OF_THREADS;i++)
	{
		CloseHandle(Threads[i]);
		Threads[i]=NULL;
	}

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		_aligned_free(Op[i]->Data);
		Op[i]->Data=NULL;

		_aligned_free(Op[i]);
		Op[i]=NULL;
	}

	CloseHandle(HCP);

	for (int i=0;i<NUMBER_OF_FILES;i++)
	{
		CloseHandle(FileHandles[i]);
		FileHandles[i]=NULL;
	}

	wprintf_s(L"\nMAX COUNTER: [%d] !\n",CPThreadCounterMax);
}
//------------------------------------------------------------------------------
// Funkcia spusta ONE-WAY volanie, kde NESPUSTA CP.
void Test4(void)
{
	const int					MAX_NUMBER_OF_CONCURRENT_OPERATIONS=2;
	const int					NUMBER_OF_OPERATION=10;
	const int					NUMBER_OF_THREADS=4;
	const int					NUMBER_OF_FILES=5;

	HANDLE						Threads[NUMBER_OF_THREADS];
	HANDLE						FileHandles[NUMBER_OF_FILES];
	DWORD						SectorSize;
	DWORD						Size;
	wchar_t						CurrentDirectory[1024];

	// Maximalna priorita pre thread, aby VSETKY IO OPERACIE boliz aslane SKOR ako sa co i len prva z nich stihne vykonat.
	SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_HIGHEST);

	// Vytvorim Completion Port.
	HCP=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,MAX_NUMBER_OF_CONCURRENT_OPERATIONS);
	//HCP=CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,0,0);

	wprintf_s(L"HPC: [%d] !\n",HCP);

	for (int i=0;i<NUMBER_OF_FILES;i++)
	{
		wchar_t					FileName[1024];
		
		StringCchPrintf(FileName,_countof(FileName),L"File%d.txt",i+1);

		FileHandles[i]=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING,NULL);
		//FileHandles[i]=CreateFile(FileName,GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_FLAG_OVERLAPPED,NULL);

		// Zaradim FILE HANDLE do CompletionPort.
		HCP=CreateIoCompletionPort(FileHandles[i],HCP,(ULONG_PTR) (i+1),0);

		wprintf_s(L"HPC: [%d] !\n",HCP);
	}

	GetCurrentDirectory(_countof(CurrentDirectory),CurrentDirectory);
	GetDiskFreeSpace(CurrentDirectory,NULL,&SectorSize,NULL,NULL);

	Size=SectorSize;

	LPCOVERLAPPEDWithData		Op[NUMBER_OF_OPERATION];

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		Op[i]=(LPCOVERLAPPEDWithData) _aligned_malloc(sizeof(COVERLAPPEDWithData),SectorSize);

		ZeroMemory(Op[i],sizeof(COVERLAPPEDWithData));
		Op[i]->Offset=0;
		Op[i]->Data=(PBYTE) _aligned_malloc(Size,SectorSize);

		HANDLE					Event=CreateEvent(NULL,FALSE,FALSE,NULL);

		// !!!!! Nastavenim Event + spodneho byte docielim, ze sa NEROBI POTVRDENIE o KONCI OPERACIE a NEVOLA SA CP. Toto ma zmysel samozrejme iba pri WRITE.
		Op[i]->hEvent=(HANDLE) ((DWORD_PTR) Event | 1);
	}

	// Spustim threads.
	for (int i=0;i<NUMBER_OF_THREADS;i++)
		Threads[i]=(HANDLE)_beginthreadex(NULL,0,MyCPThread,(void*) (i+1),0,NULL);

	// Pockam kym sa ostatne threads spustia.
	Sleep(500);

	// Spustim IO operacie.
	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		HANDLE					FileHandle=FileHandles[i%NUMBER_OF_FILES];
		DWORD					Ret=ReadFile(FileHandle,Op[i]->Data,Size,NULL,Op[i]);

		if (Ret==TRUE)
			wprintf_s(L"Data was read SYNCHRONOUSLY !\n");
		else
		{
			DWORD				LE=GetLastError();

			if (LE==ERROR_IO_PENDING)
				wprintf_s(L"ASYNCHRONOUS operation STARTED !\n");
			else
				PrintErrorCodeToConsole(L"ReadFile()",LE);
		}
	}

	_getch();

	for (int i=0;i<NUMBER_OF_THREADS;i++)
		PostQueuedCompletionStatus(HCP,0,(ULONG_PTR) KEY_EXIT,NULL);

	// Pockam na ukoncenie vsetkych Threads.
	WaitForMultipleObjects(NUMBER_OF_THREADS,Threads,TRUE,INFINITE);

	for (int i=0;i<NUMBER_OF_THREADS;i++)
	{
		CloseHandle(Threads[i]);
		Threads[i]=NULL;
	}

	for (int i=0;i<NUMBER_OF_OPERATION;i++)
	{
		HANDLE			Event=(HANDLE) ((DWORD_PTR) Op[i]->hEvent & ~1);

		// Korektne uvolnim Event.
		CloseHandle(Event);

		_aligned_free(Op[i]->Data);
		Op[i]->Data=NULL;

		_aligned_free(Op[i]);
		Op[i]=NULL;
	}

	CloseHandle(HCP);

	for (int i=0;i<NUMBER_OF_FILES;i++)
	{
		CloseHandle(FileHandles[i]);
		FileHandles[i]=NULL;
	}
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	//Test2();
	Test3();
	//Test4();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------