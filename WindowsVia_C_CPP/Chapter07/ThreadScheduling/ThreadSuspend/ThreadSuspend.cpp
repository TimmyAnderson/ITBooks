#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
//------------------------------------------------------------------------------
HANDLE		Exit;
//------------------------------------------------------------------------------
unsigned int WINAPI MyThread(void* Param)
{
	while(true)
	{
		if (WaitForSingleObject(Exit,0)==WAIT_OBJECT_0)
			break;

		// !!!!! Thread alokuje a dealokuje HEAP, aby C++ muselo PERIODICKY hadzat LOCK na HEAP.

		const int	ARRAY_SIZE=1000;
		const int	ALLOC_SIZE=1024*1024;
		int*		Array[ARRAY_SIZE];

		for (int i=0;i<ARRAY_SIZE;i++)
			Array[i]=new int[ARRAY_SIZE];

		for (int i=0;i<ARRAY_SIZE;i++)
			delete[](Array[i]);
	}

	return(0);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void Test(void)
{
	const int			TEST_COUNT=1000*1000;
	HANDLE				Handle;

	Exit=CreateEvent(NULL,FALSE,FALSE,NULL);
	
	Handle=(HANDLE)_beginthreadex(NULL,0,MyThread,NULL,0,NULL);

	for (int i=1;i<TEST_COUNT;i++)
	{
		// !!!!! Pozastavim thread, ktory PRAVE moze DRZAT LOCK NA HEAP.
		SuspendThread(Handle);

		wprintf(L"Iteration [%d] - TRYING to ALLOCATE MEMORY !\n",i);

		// Skusim alokovat pamat, ked C++ HADZE na HEAP LOCK.
		int*		Temp=new int;

		// !!!!! Ak worker thread DRZI LOCK NAD HEAP - tak tu sa PROGRAM NIKDY NEDOSTANE a VZNIKNE DEADLOCK.

		wprintf(L"Iteration [%d] - MEMORY was ALLOCATED !\n",i);

		delete(Temp);

		ResumeThread(Handle);
	}

	SetEvent(Exit);

	WaitForSingleObject(Handle,INFINITE);

	CloseHandle(Exit);
	CloseHandle(Handle);
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