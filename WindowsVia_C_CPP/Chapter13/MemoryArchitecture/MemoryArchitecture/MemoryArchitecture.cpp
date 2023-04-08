#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
void Test(void)
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