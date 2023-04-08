#include "stdafx.h"
#include <windows.h>
#include "MyDebug.h"
#include <Psapi.h>
#include <process.h>
#include <conio.h>
#include <tchar.h>
#include <stdio.h>
//------------------------------------------------------------------------------
void Test1(void)
{
	SYSTEM_INFO		SI;

	GetSystemInfo(&SI);

	wprintf_s(L"PageSize: [%d] !\n",SI.dwPageSize);
	wprintf_s(L"AllocationGranularity: [%d] !\n",SI.dwAllocationGranularity);
	wprintf_s(L"NumberOfProcessors: [%d] !\n",SI.dwNumberOfProcessors);
}
//------------------------------------------------------------------------------
void Test2(void)
{
	MEMORYSTATUSEX		MemStatus;

	MemStatus.dwLength=sizeof(MEMORYSTATUSEX);

	GlobalMemoryStatusEx(&MemStatus);

	wprintf_s(L"TotalPhys: [%d] !\n",MemStatus.ullTotalPhys);

	DWORDLONG			TotalPhysMB=MemStatus.ullTotalPhys/1024/1024;

	wprintf_s(L"TotalPhys in MB: [%d] !\n",TotalPhysMB);
}
//------------------------------------------------------------------------------
void Test3(void)
{
	SYSTEM_INFO					SI;

	GetSystemInfo(&SI);

	PROCESS_MEMORY_COUNTERS_EX	Mem;

	Mem.cb=sizeof(PROCESS_MEMORY_COUNTERS_EX);

	// Mnozstvo alokovanej pamete funkciami VirtualAlloc(), malloc() a operatorom new.
	GetProcessMemoryInfo(GetCurrentProcess(),(PPROCESS_MEMORY_COUNTERS) &Mem,Mem.cb);
	wprintf_s(L"PrivateUsage: [%d] BYTES !\n",Mem.PrivateUsage);
	wprintf_s(L"PrivateUsage: [%d] KB !\n",Mem.PrivateUsage/1024);
	wprintf_s(L"PrivateUsage: [%d] MB !\n",Mem.PrivateUsage/1024/1024);

	// Alokujem aspon 1 PAGE.
	BYTE*			Dummy=new BYTE[SI.dwPageSize];

	GetProcessMemoryInfo(GetCurrentProcess(),(PPROCESS_MEMORY_COUNTERS) &Mem,Mem.cb);
	wprintf_s(L"PrivateUsage: [%d] BYTES !\n",Mem.PrivateUsage);
	wprintf_s(L"PrivateUsage: [%d] KB !\n",Mem.PrivateUsage/1024);
	wprintf_s(L"PrivateUsage: [%d] MB !\n",Mem.PrivateUsage/1024/1024);

	delete[](Dummy);

	GetProcessMemoryInfo(GetCurrentProcess(),(PPROCESS_MEMORY_COUNTERS) &Mem,Mem.cb);
	wprintf_s(L"PrivateUsage: [%d] BYTES !\n",Mem.PrivateUsage);
	wprintf_s(L"PrivateUsage: [%d] KB !\n",Mem.PrivateUsage/1024);
	wprintf_s(L"PrivateUsage: [%d] MB !\n",Mem.PrivateUsage/1024/1024);
}
//------------------------------------------------------------------------------
void Test4(void)
{
	MEMORY_BASIC_INFORMATION	MBI;
	// Data na stacku.
	int							DummyStack=100;
	int*						DummyHeap=new int;

	VirtualQuery(&DummyStack,&MBI,sizeof(MBI));
	wprintf_s(L"STACK - AllocationBase: [%p] !\n",MBI.AllocationBase);
	wprintf_s(L"STACK - Type: [%d] !\n",MBI.Type);
	wprintf_s(L"STACK - State: [%d] !\n",MBI.State);
	wprintf_s(L"STACK - Protect: [%d] !\n",MBI.Protect);
	wprintf_s(L"\n");

	VirtualQuery(DummyHeap,&MBI,sizeof(MBI));
	wprintf_s(L"HEAP - AllocationBase: [%p] !\n",MBI.AllocationBase);
	wprintf_s(L"HEAP - Type: [%d] !\n",MBI.Type);
	wprintf_s(L"HEAP - State: [%d] !\n",MBI.State);
	wprintf_s(L"HEAP - Protect: [%d] !\n",MBI.Protect);
	wprintf_s(L"\n");

	VirtualQuery(NULL,&MBI,sizeof(MBI));
	wprintf_s(L"NULL - AllocationBase: [%p] !\n",MBI.AllocationBase);
	wprintf_s(L"NULL - Type: [%d] !\n",MBI.Type);
	wprintf_s(L"NULL - State: [%d] !\n",MBI.State);
	wprintf_s(L"NULL - Protect: [%d] !\n",MBI.Protect);
	wprintf_s(L"\n");

	delete(DummyHeap);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	SafeMain();
	
	Test1();
	//Test2();
	//Test3();
	//Test4();

	ShowExitLine();

	return(0);
}
//------------------------------------------------------------------------------