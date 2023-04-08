#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
BOOL EnablePrivilege(PCTSTR Privilege, BOOL Enable)
{
	BOOL					OK=FALSE;
	HANDLE					Token;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES,&Token)==TRUE)
	{
		TOKEN_PRIVILEGES	TP;
		
		TP.PrivilegeCount=1;

		LookupPrivilegeValue(NULL, Privilege, &TP.Privileges[0].Luid);

		TP.Privileges[0].Attributes=Enable ? SE_PRIVILEGE_ENABLED : 0;

		// Nastavim dane privilegium.
		AdjustTokenPrivileges(Token, FALSE, &TP, sizeof(TP), NULL, NULL);

		OK=(GetLastError()==ERROR_SUCCESS);

		CloseHandle(Token);
	}

   return(OK);
}
//------------------------------------------------------------------------------
void Test1(void)
{
	const int		VIRTUAL_ADDRESS_SPACE_SIZE=50;
	const int		ALLOCATED_MEMORY_SPACE=sizeof(BYTE);
	void*			Memory=NULL;
	SYSTEM_INFO		SI;

	// Zistim velkost MEM PAGE.
	GetSystemInfo(&SI);


	// Alkoujem VIRTUALNY ADRESOVY PRIESTOR a NIE PAMAT.
	Memory=VirtualAlloc(NULL,VIRTUAL_ADDRESS_SPACE_SIZE,MEM_RESERVE,PAGE_READWRITE);

	wprintf_s(L"Virtual address space: [%p] !\n",Memory);

	/*
	BYTE*			Pointer=(BYTE*) Memory;

	// !!! Zatial je rezervovony iba adresovy preistor a NIE REALNA PAMAT a preto nasledujuci kod HODI SEH EXCEPTION.
	*Pointer=100;
	*/

	// Teraz uz ALOKUJEM REALNU PAMAT.
	// !!!!! Hoci ALOKUJEM iba 1 BYTE, v skutocnosti sa alokuje PageSize BYTES, lebo Windows alokuje pamet po blkoch velkosti PageSize.
	Memory=VirtualAlloc(Memory,ALLOCATED_MEMORY_SPACE,MEM_COMMIT,PAGE_READWRITE);

	wprintf_s(L"Memory address: [%p] !\n",Memory);

	BYTE*			BaseMemory=(BYTE*) Memory;
	BYTE*			Pointer=NULL;
		
	Pointer=BaseMemory+0;

	// Prebehne OK.
	*Pointer=100;

	wprintf_s(L"Value at address: [%p], MemDiff: [%d] is: [%d] !\n",Memory,Pointer-BaseMemory,*Pointer);

	// Teraz pristupim do pamate ZA ALOKOVANOU VELKOSTOU - 1 byte.
	Pointer=BaseMemory+1;

	// Prebehne OK - pretoze Windows v skutocnosti alokuje PageSize bytes.
	*Pointer=100;

	wprintf_s(L"Value at address: [%p], MemDiff: [%d] is: [%d] !\n",Memory,Pointer-BaseMemory,*Pointer);

	Pointer=(BYTE*) BaseMemory+SI.dwPageSize-1;

	// Prebehne OK - pretoze Windows v skutocnosti alokuje PageSize bytes.
	*Pointer=100;

	wprintf_s(L"Value at address: [%p], MemDiff: [%d] is: [%d] !\n",Memory,Pointer-BaseMemory,*Pointer);

	// Prekrocim velkost PageSize.
	Pointer=(BYTE*) BaseMemory+SI.dwPageSize;

	// ZLYHA.
	//*Pointer=100;

	// ZLYHA.
	//wprintf_s(L"Value at address: [%p], MemDiff: [%d] is: [%d] !\n",Memory,Pointer-BaseMemory,*Pointer);


	// UVOLNIM ALOKOVANU PAMAT.
	VirtualFree(Memory,ALLOCATED_MEMORY_SPACE,MEM_DECOMMIT);

	// UVOLNIM Address space.
	// 2. parameter MUSI BYT 0.
	VirtualFree(Memory,0,MEM_RELEASE);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	void*			Memory=NULL;
	void*			Position;
	SYSTEM_INFO		SI;

	GetSystemInfo(&SI);

	Position=NULL;
	Memory=VirtualAlloc(NULL,100,MEM_RESERVE,PAGE_READWRITE);
	wprintf_s(L"Reserved address: [%p], Desired position was: [%p] !\n",Memory,Position);
	VirtualFree(Memory,0,MEM_RELEASE);

	// Standardne sa pamat vyhradzuje v pozicii DELITELNEJ - ALLOCATION GRANULARITY BOUNDARY - 64 KB.
	// Skusim rezervovat pamat na pozicii 64 MB, ktora je delitalna 64 KB.
	Position=(void*) (SI.dwAllocationGranularity*1024*1024);
	Memory=VirtualAlloc(Position,100,MEM_RESERVE,PAGE_READWRITE);
	wprintf_s(L"Reserved address: [%p], Desired position was: [%p] !\n",Memory,Position);
	VirtualFree(Memory,0,MEM_RELEASE);

	// Adresu zaokruhli tak, aby bola delitalna 64 KB.
	Position=(void*) (64*1024*1024+100);
	Memory=VirtualAlloc(Position,100,MEM_RESERVE,PAGE_READWRITE);
	wprintf_s(L"Reserved address: [%p], Desired position was: [%p] !\n",Memory,Position);
	VirtualFree(Memory,0,MEM_RELEASE);

	Position=NULL;
	Memory=VirtualAlloc(Position,100,MEM_RESERVE | MEM_TOP_DOWN,PAGE_READWRITE);
	wprintf_s(L"MEM TOP - Reserved address: [%p] !\n",Memory);
	VirtualFree(Memory,0,MEM_RELEASE);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	BYTE*			ReservedAddressSpace=NULL;
	BYTE*			Memory1=NULL;
	BYTE*			Memory2=NULL;
	SYSTEM_INFO		SI;

	// Zistim velkost MEM PAGE.
	GetSystemInfo(&SI);

	// Reservujem 2 PAGES v ADDRESS SPACE.
	ReservedAddressSpace=(BYTE*) VirtualAlloc(NULL,2*SI.dwPageSize,MEM_RESERVE,PAGE_READWRITE);

	wprintf_s(L"Reserved address space: [%p] !\n",ReservedAddressSpace);

	// Alokujem 1 PAGE.
	Memory1=(BYTE*) VirtualAlloc(ReservedAddressSpace,SI.dwPageSize,MEM_COMMIT,PAGE_READWRITE);

	wprintf_s(L"Page 1: [%p] !\n",Memory1);

	// Zapis do pamate v PAGE 1 prebehne OK.
	*ReservedAddressSpace=100;

	// Zapis do pamate v PAGE 2 ZLYHA.
	//*(ReservedAddressSpace+SI.dwPageSize)=100;


	// Alokujem 2 PAGE.
	Memory2=(BYTE*) VirtualAlloc(ReservedAddressSpace+SI.dwPageSize,SI.dwPageSize,MEM_COMMIT,PAGE_READWRITE);

	wprintf_s(L"Page 2: [%p] !\n",Memory2);

	// Zapis do pamate v PAGE 1 prebehne OK.
	*ReservedAddressSpace=100;

	// Zapis do pamate v PAGE 2 prebehne OK.
	*(ReservedAddressSpace+SI.dwPageSize)=100;

	// Dealokujem 1. PAGE.
	VirtualFree(Memory1,SI.dwPageSize,MEM_DECOMMIT);
	// Dealokujem 2. PAGE.
	VirtualFree(Memory2,SI.dwPageSize,MEM_DECOMMIT);

	// ODREZERVUJEM OBE PAGES.
	VirtualFree(ReservedAddressSpace,0,MEM_RELEASE);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	BYTE*			Memory=NULL;
	SYSTEM_INFO		SI;

	// Zistim velkost MEM PAGE.
	GetSystemInfo(&SI);

	// Alkoujem VIRTUALNY ADRESOVY PRIESTOR i PAMAT.
	Memory=(BYTE*) VirtualAlloc(NULL,SI.dwPageSize*3,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);

	bool			HasNotNULL=false;

	for (DWORD i=0;i<SI.dwPageSize*3;i++)
		if (Memory[i]!=NULL)
		{
			HasNotNULL=true;
			break;
		}

	if (HasNotNULL==true)
		wprintf_s(L"Memory HAS NOT NULL value !\n");
	else
		wprintf_s(L"Memory HAS JUST NULL values !\n");

	*Memory=100;

	wprintf_s(L"Value at address: [%p] is: [%d] !\n",Memory,*Memory);

	// UVOLNIM ALOKOVANU PAMAT.
	VirtualFree(Memory,SI.dwPageSize*3,MEM_DECOMMIT);

	// UVOLNIM Address space.
	VirtualFree(Memory,0,MEM_RELEASE);
}
//------------------------------------------------------------------------------
void Test5(void)
{
	// Bezi to iba nad VISTA.

	// Musim povolit SE_LOCK_MEMORY_NAME privilege.
	// !!!!! Dane privilegium MUSI BYT POVOLENE v Group Policy.
	if (EnablePrivilege(SE_LOCK_MEMORY_NAME,TRUE)==FALSE)
	{
		wprintf_s(L"Can't set privilege !\n");
		return;
	}

	/*
	SIZE_T			LargePageSize=GetLargePageMinimum();
	BYTE*			Memory=NULL;

	wprintf_s(L"LargePageSize: [%d] !\n",LargePageSize);

	// Ak chcem alokovat LargePage, musim urobit i COMMIT.
	// Page musi byt PAGE_READWRITE.
	Memory=(BYTE*) VirtualAlloc(NULL,LargePageSize*10,MEM_RESERVE | MEM_COMMIT | MEM_LARGE_PAGES,PAGE_READWRITE);

	if (Memory==NULL)
	{
		wprintf_s(L"Error: [%d] !\n",GetLastError());
		return;
	}

	*Memory=100;

	wprintf_s(L"Value at address: [%p] is: [%d] !\n",Memory,*Memory);

	// UVOLNIM ALOKOVANU PAMAT.
	VirtualFree(Memory,LargePageSize*10,MEM_DECOMMIT);

	// UVOLNIM Address space.
	VirtualFree(Memory,0,MEM_RELEASE);
	*/
}
//------------------------------------------------------------------------------
void Test6(void)
{
	BYTE*			Memory=NULL;
	SYSTEM_INFO		SI;

	// Zistim velkost MEM PAGE.
	GetSystemInfo(&SI);

	// Alkoujem VIRTUALNY ADRESOVY PRIESTOR i PAMAT.
	Memory=(BYTE*) VirtualAlloc(NULL,SI.dwPageSize*3,MEM_RESERVE | MEM_COMMIT,PAGE_READWRITE);

	*Memory=100;

	wprintf_s(L"Value at address: [%p] is: [%d] !\n",Memory,*Memory);

	DWORD			OldProtect;
	
	// Zmenim PAGE na READONLY.
	VirtualProtect(Memory,SI.dwPageSize*3,PAGE_READONLY,&OldProtect);

	// Citat MOZEM.
	wprintf_s(L"Value at address: [%p] is: [%d] !\n",Memory,*Memory);

	// ZAPISOVTA NEMOZEM - sposobi ACCESS VIOLATION.
	*Memory=100;

	// UVOLNIM ALOKOVANU PAMAT.
	VirtualFree(Memory,SI.dwPageSize*3,MEM_DECOMMIT);

	// UVOLNIM Address space.
	VirtualFree(Memory,0,MEM_RELEASE);
}
//------------------------------------------------------------------------------
// Demonstruje pouzitie AWE.
void Test7(void)
{
	SYSTEM_INFO		SI;

	// Zistim velkost MEM PAGE.
	GetSystemInfo(&SI);

	// Musim povolit SE_LOCK_MEMORY_NAME privilege.
	// !!!!! Dane privilegium MUSI BYT POVOLENE v Group Policy.
	EnablePrivilege(SE_LOCK_MEMORY_NAME,TRUE);

	const int		TOTAL_PAGES_COUNT=1;
	const int		NUMBER_OF_RAM_BLOCKS=2;
	int				WindowSize=SI.dwPageSize;
	BYTE*			Memory;

	// Rezervujem REGION - musim nastavit MEM_PHYSICAL.
	Memory=(BYTE*) VirtualAlloc(NULL,WindowSize,MEM_RESERVE | MEM_PHYSICAL,PAGE_READWRITE);

	// Alokujem pamat s OPAQUE INDEXAMI RAM PAGES.
	// Toto pole je OPAQUE a pouziva ho Winodws pre svoje potreby.
	ULONG_PTR		RAMPages[NUMBER_OF_RAM_BLOCKS][TOTAL_PAGES_COUNT];
	ULONG_PTR		RAMPagesCount[NUMBER_OF_RAM_BLOCKS];

	// Alokujem vsetky RAM BLOCKS.
	for (int i=0;i<NUMBER_OF_RAM_BLOCKS;i++)
	{
		RAMPagesCount[i]=TOTAL_PAGES_COUNT;

		// Alokujem RAM BLOCK.
		AllocateUserPhysicalPages(GetCurrentProcess(),&RAMPagesCount[i],RAMPages[i]);
		wprintf_s(L"Allocated for [%d] BLOCK: [%d] pages !\n",i,RAMPagesCount[i]);
	}

	// Pouzijem pamatove bloky.
	for (int i=0;i<NUMBER_OF_RAM_BLOCKS;i++)
	{
		// Namapujem ADDRESS SPACE na RAM BLOCK.
		MapUserPhysicalPages(Memory,RAMPagesCount[i],RAMPages[i]);

		*Memory=1+i;
	}

	// Pouzijem pamatove bloky.
	for (int i=0;i<NUMBER_OF_RAM_BLOCKS;i++)
	{
		// Namapujem ADDRESS SPACE na RAM BLOCK.
		MapUserPhysicalPages(Memory,RAMPagesCount[i],RAMPages[i]);

		wprintf_s(L"Block [%d] at address: [%p] contains VALUE: [%d] !\n",i,Memory,*Memory);
	}

	// Uvolnim vsetky RAM BLOCK.
	for (int i=0;i<NUMBER_OF_RAM_BLOCKS;i++)
	{
		// Odstranim mapovanie.
		MapUserPhysicalPages(Memory,RAMPagesCount[i],NULL);

		// Uvolnim RAM BLOCK.
		FreeUserPhysicalPages(GetCurrentProcess(),&RAMPagesCount[i],RAMPages[i]);
		wprintf_s(L"Deallocated BLOCK: [%d] !\n",i);
	}

	// UVOLNIM Address space.
	VirtualFree(Memory,0,MEM_RELEASE);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	//Test1();
	Test2();
	//Test3();
	//Test4();
	//Test5();
	//Test6();
	//Test7();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------