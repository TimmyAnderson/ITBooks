//-------------------------------------------------------------------------------------------------------
// !!! HEADER [Ntddk.h] MUSI BYT PRED HEADER [wdm.h].
#include <Ntddk.h>
#include <wdm.h>
#include <initguid.h>
#include <Ntstrsafe.h>
//-------------------------------------------------------------------------------------------------------
#include "Driver.h"
#include "GUIDS.h"
#include "Macros.h"
//-------------------------------------------------------------------------------------------------------
#pragma warning(disable:4127)
//-------------------------------------------------------------------------------------------------------
// !!!!! DRIVER sa sice FORMALNE NENAINSTALUJE - pocas DRIVER DEPLOY (vyvolany REBUILD [MySimpleProgrammingTechniquesDriver Package]) vyhlasi DEPLOYMENT proces CHYBU, ale v skutocnosti DRIVER je NAINSTALOVANY. Kedze vsak AddDevice() vrati STATUS_UNSUCCESSFUL, tak INSTALLER to vyhodnoti ako NEUSPESNE NAINSTALOVANIE DRIVER. Avsak LOGY sa ZAPISU a je ich mozne citat cez TOOL [DebugView.exe].
//-------------------------------------------------------------------------------------------------------
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PDO);
NTSTATUS DispatchPNP(PDEVICE_OBJECT FDO, PIRP IRP);
NTSTATUS DispatchPower(PDEVICE_OBJECT FDO, PIRP IRP);
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT FDO, PIRP IRP);
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
extern "C" void MyDummyTest(void);
//-------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION MyDummyTest() bude ulozena v PAGED MEMORY.
// !!!!! PRAGMA ALLOC_TEXT() MUSI byt MEDZI DECLARATION a DEFINITION FUNCTION MyDummyTest().
// !!!!! FUNCTION MyDummyTest() MUSI mat LINKAGE [extern "C"].
#pragma alloc_text(PAGE,"MyDummyTest")
//-------------------------------------------------------------------------------------------------------
extern "C" void MyDummyTest(void)
{
	// EMPTY.
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Pouzitie PRAGMA CODE_SEG() znamena, ze sa CODE VSETKYCH NIZSIE DEKLAROVANYCH FUNCTIONS ulozia do PAGED MEMORY.
#pragma code_seg("DATA")
extern "C" void FunctionInPagedMemory1(void)
{
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Pouzitie PRAGMA CODE_SEG() znamena, ze sa CODE VSETKYCH NIZSIE DEKLAROVANYCH FUNCTIONS ulozia do NON-PAGED MEMORY.
#pragma code_seg()
extern "C" void FunctionInNonPagedMemory(void)
{
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Pouzitie PRAGMA CODE_SEG() znamena, ze sa CODE VSETKYCH NIZSIE DEKLAROVANYCH FUNCTIONS ulozia do PAGED MEMORY.
#pragma code_seg("DATA")
extern "C" void FunctionInPagedMemory2(void)
{
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Pouzitie PRAGMA DATA_SEG() znamena, ze sa VSETKY NIZSIE DEKLAROVANE STATIC VARIABLES ulozia do PAGED MEMORY.
#pragma data_seg("PAGEDATA")
//-------------------------------------------------------------------------------------------------------
int																InPagedMemory;
//-------------------------------------------------------------------------------------------------------
// !!!!! Pouzitie PRAGMA DATA_SEG() znamena, ze sa VSETKY NIZSIE DEKLAROVANE STATIC VARIABLES ulozia do NON-PAGED MEMORY.
#pragma data_seg()
int																InMemory;
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestStatusCode(char* StatusName, NTSTATUS Status)
{
	if (NT_SUCCESS(Status)==true)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_SUCCESS(%08X) [%s] !\n",StatusName,Status,"TRUE"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_SUCCESS(%08X) [%s] !\n",StatusName,Status,"FALSE"));
	}

	if (NT_INFORMATION(Status)==true)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_INFORMATION(%08X) [%s] !\n",StatusName,Status,"TRUE"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_INFORMATION(%08X) [%s] !\n",StatusName,Status,"FALSE"));
	}

	if (NT_WARNING(Status)==true)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_WARNING(%08X) [%s] !\n",StatusName,Status,"TRUE"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_WARNING(%08X) [%s] !\n",StatusName,Status,"FALSE"));
	}

	if (NT_ERROR(Status)==true)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_ERROR(%08X) [%s] !\n",StatusName,Status,"TRUE"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION TestStatusCode(): %s - NT_ERROR(%08X) [%s] !\n",StatusName,Status,"FALSE"));
	}
}
//-------------------------------------------------------------------------------------------------------
void TestStatusCodes(void)
{
	NTSTATUS													Status1=ERROR_SEVERITY_SUCCESS | APPLICATION_ERROR_MASK | 100;
	NTSTATUS													Status2=ERROR_SEVERITY_INFORMATIONAL | APPLICATION_ERROR_MASK | 200;
	NTSTATUS													Status3=ERROR_SEVERITY_WARNING | APPLICATION_ERROR_MASK | 300;
	NTSTATUS													Status4=ERROR_SEVERITY_ERROR | APPLICATION_ERROR_MASK | 400;

	TestStatusCode("Status1",Status1);
	TestStatusCode("Status2",Status2);
	TestStatusCode("Status3",Status3);
	TestStatusCode("Status4",Status4);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void ThrowSEH(void)
{
	PVOID														InvalidPointer=(PVOID) 1;

	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION ThrowSEH(): BEFORE EXCEPTION !\n"));

		// !!! Otestuje ci POINTER odkazujuci na USER MODE ADDRESS SPACE je VALIDNY. Ak nie HODI sa EXCEPTION.
		ProbeForWrite(InvalidPointer,4,4);

		KdPrint((DRIVERNAME " - FUNCTION ThrowSEH(): AFTER EXCEPTION !\n"));
	}
	__finally
	{
		KdPrint((DRIVERNAME " - FUNCTION ThrowSEH(): FINALLY BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION ThrowSEH(): AFTER FINALLY BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void ContinueSearchSEH(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION ContinueSearchSEH(): BEFORE EXCEPTION !\n"));

		// !!! Hodi EXCEPTION.
		ThrowSEH();

		KdPrint((DRIVERNAME " - FUNCTION ContinueSearchSEH(): AFTER EXCEPTION !\n"));
	}
	// !!! Dam EXCEPTION_CONTINUE_SEARCH - aby sa hladal dalsi EXCEPTION BLOCK.
	__except(EXCEPTION_CONTINUE_SEARCH)
	{
		KdPrint((DRIVERNAME " - FUNCTION ContinueSearchSEH(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION ContinueSearchSEH(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
LONG EvaluateException(NTSTATUS Status, PEXCEPTION_POINTERS ExceptionPointers)
{
	KdPrint((DRIVERNAME " - FUNCTION EvaluateException(): Status - STATUS [%X] !\n",Status));
	KdPrint((DRIVERNAME " - FUNCTION EvaluateException(): ExceptionPointers - EXCEPTION CODE [%08X], FLAGS [%08X] !\n",ExceptionPointers->ExceptionRecord->ExceptionCode,ExceptionPointers->ExceptionRecord->ExceptionFlags));

	return(EXCEPTION_EXECUTE_HANDLER);
}
//-------------------------------------------------------------------------------------------------------
void TestSEH1(void)
{
	PVOID														InvalidPointer=(PVOID) 1;

	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH1(): BEFORE EXCEPTION !\n"));

		// !!! Otestuje ci POINTER odkazujuci na USER MODE ADDRESS SPACE je VALIDNY. Ak nie HODI sa EXCEPTION.
		ProbeForWrite(InvalidPointer,4,4);

		KdPrint((DRIVERNAME " - FUNCTION TestSEH1(): AFTER EXCEPTION !\n"));
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH1(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH1(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH2(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH2(): BEFORE EXCEPTION !\n"));

		// !!! Hodi EXCEPTION.
		ThrowSEH();

		KdPrint((DRIVERNAME " - FUNCTION TestSEH2(): AFTER EXCEPTION !\n"));
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH2(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH2(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
// !!!!! Sposobi BLUE SCREEN.
void TestSEH3(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH3(): BEFORE EXCEPTION !\n"));

		// !!! Hodi EXCEPTION.
		ThrowSEH();

		KdPrint((DRIVERNAME " - FUNCTION TestSEH3(): AFTER EXCEPTION !\n"));
	}
	// !!! Dam EXCEPTION_CONTINUE_EXECUTION - aby EXECUTION POKRACOVAL DALEJ.
	__except(EXCEPTION_CONTINUE_EXECUTION)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH3(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH3(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH4(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH4(): BEFORE EXCEPTION !\n"));

		// !!! Hodi EXCEPTION.
		ContinueSearchSEH();

		KdPrint((DRIVERNAME " - FUNCTION TestSEH4(): AFTER EXCEPTION !\n"));
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH4(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH4(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH5(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH5(): BEFORE EXCEPTION !\n"));

		int														Value=0;

		// !!!!! NESPOSOBI PAD SYSTEMU, lebo DIVIDE by ZERO JE v KERNEL MODE zachytavane SEH.
		// !!!!! Je to ROZDIEL oproti KNIHE, kde sa pise, ze DIVIDE by ZERO nie je spracovavane SEH.
		int														Result=10/Value;

		if (Result>0)
		{
			// Toto sa samozrejme NIKDY NEZOBRAZI. Je to iba aby COMPILER nehlasil, ze VARIABLE Result nie je pouzita.
			KdPrint((DRIVERNAME " - FUNCTION TestSEH5(): ????????????????? !\n"));
		}

		KdPrint((DRIVERNAME " - FUNCTION TestSEH5(): AFTER EXCEPTION !\n"));
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH5(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH5(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH6(void)
{
	PVOID														InvalidPointer=(PVOID) 1;

	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH6(): BEFORE EXCEPTION !\n"));

		// !!! Otestuje ci POINTER odkazujuci na USER MODE ADDRESS SPACE je VALIDNY. Ak nie HODI sa EXCEPTION.
		ProbeForWrite(InvalidPointer,4,4);

		KdPrint((DRIVERNAME " - FUNCTION TestSEH6(): AFTER EXCEPTION !\n"));
	}
	// !!! VALUE pre '__except' sa zoberie z POSLEDNEJ EXPRESSION (tu EXCEPTION_EXECUTE_HANDLER).
	// !!! FUNCTION KdPrint() v '__except' EXPRESSION sa VYKONA.
	__except(KdPrint((DRIVERNAME " - FUNCTION TestSEH6(): INSIDE __except EXPRESSION !\n")),EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH6(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH6(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH7(void)
{
	int															Value=0;

	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH7(): BEFORE EXCEPTION !\n"));

		int														Result=10/Value;

		if (Result!=0)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestSEH7(): We have RESULT !\n"));
		}

		KdPrint((DRIVERNAME " - FUNCTION TestSEH7(): AFTER EXCEPTION !\n"));
	}
	// !!!!! Skusim OPRAVIT hodnotu.
	// !!!!! Tento CODE sposobuje VYRAZNE SPOMALENIE WINDOWS a vytocenie CPU na testovacom WINDOWS.
	__except(Value=5,EXCEPTION_CONTINUE_EXECUTION)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH7(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH7(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH8(void)
{
	PVOID														InvalidPointer=(PVOID) 1;

	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH8(): BEFORE EXCEPTION !\n"));

		ProbeForWrite(InvalidPointer,4,4);

		KdPrint((DRIVERNAME " - FUNCTION TestSEH8(): AFTER EXCEPTION !\n"));
	}
	// !!!!! Vyvolaju sa FUNCTIONS, ktore vracaju STAV EXCEPTION.
	__except(EvaluateException(GetExceptionCode(),GetExceptionInformation()))
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH8(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH8(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH9(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH9(): BEFORE EXCEPTION !\n"));

		// !!! HODI EXCEPTION a obsahuje aj FINALLY BLOCK.
		ThrowSEH();

		KdPrint((DRIVERNAME " - FUNCTION TestSEH9(): AFTER EXCEPTION !\n"));
	}
	// !!!!! EvaluateException() sa vykona SKOR ako FINALLY BLOCK v ThrowSEH().
	__except(EvaluateException(GetExceptionCode(),GetExceptionInformation()))
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH9(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH9(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH10(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH10(): BEFORE EXCEPTION !\n"));

		NTSTATUS												Status=ERROR_SEVERITY_ERROR | APPLICATION_ERROR_MASK | 400;

		// !!! HODI EXCEPTION.
		ExRaiseStatus(Status);

		// !!!!! COMPILER hodi UNREACHABLE CODE WARNING.
		//KdPrint((DRIVERNAME " - FUNCTION TestSEH10(): AFTER EXCEPTION !\n"));
	}
	// !!!!! EvaluateException() sa vykona SKOR ako FINALLY BLOCK v ThrowSEH().
	__except(EvaluateException(GetExceptionCode(),GetExceptionInformation()))
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH10(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH10(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSEH11(void)
{
	__try
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH11(): BEFORE EXCEPTION !\n"));

		NTSTATUS												Status=ERROR_SEVERITY_SUCCESS | APPLICATION_ERROR_MASK | 100;

		// !!! HODI EXCEPTION.
		ExRaiseStatus(Status);

		// !!!!! COMPILER hodi UNREACHABLE CODE WARNING.
		//KdPrint((DRIVERNAME " - FUNCTION TestSEH11(): AFTER EXCEPTION !\n"));
	}
	// !!!!! EvaluateException() sa vykona SKOR ako FINALLY BLOCK v ThrowSEH().
	__except(EvaluateException(GetExceptionCode(),GetExceptionInformation()))
	{
		KdPrint((DRIVERNAME " - FUNCTION TestSEH11(): EXCEPTION BLOCK !\n"));
	}
	
	KdPrint((DRIVERNAME " - FUNCTION TestSEH11(): AFTER EXCEPTION BLOCK !\n"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void BugCheck(void)
{
	KdPrint((DRIVERNAME " - FUNCTION BugCheck(): BEFORE BUG CHECK !\n"));

	ULONG														ErrorCode=ERROR_SEVERITY_ERROR | APPLICATION_ERROR_MASK | 400;

	// !!!!! SPOSOBI PAD SYSTEMU.
	KeBugCheckEx(ErrorCode,100,200,300,400);

	// !!!!! Tu sa uz CODE NIKDY NEDOSTANE.
	// !!!!! COMPILER hodi UNREACHABLE CODE WARNING.
	//KdPrint((DRIVERNAME " - FUNCTION BugCheck(): BEFORE BUG CHECK !\n"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void PrintPageMacros(void)
{
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): PAGE_SIZE [%d] !\n",PAGE_SIZE));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): PAGE_SHIFT [%d] !\n",PAGE_SHIFT));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): ROUND_TO_PAGES(100) [%d] !\n",ROUND_TO_PAGES(100)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): ROUND_TO_PAGES(1000) [%d] !\n",ROUND_TO_PAGES(1000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): ROUND_TO_PAGES(10000) [%d] !\n",ROUND_TO_PAGES(10000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): PAGE_ALIGN(100) [%d] !\n",PAGE_ALIGN(100)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): PAGE_ALIGN(1000) [%d] !\n",PAGE_ALIGN(1000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): PAGE_ALIGN(10000) [%d] !\n",PAGE_ALIGN(10000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): BYTES_TO_PAGES(1000) [%d] !\n",BYTES_TO_PAGES(1000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): BYTES_TO_PAGES(10000) [%d] !\n",BYTES_TO_PAGES(10000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): BYTES_TO_PAGES(100000) [%d] !\n",BYTES_TO_PAGES(100000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): BYTE_OFFSET(1000) [%d] !\n",BYTE_OFFSET(1000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): BYTE_OFFSET(5000) [%d] !\n",BYTE_OFFSET(5000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): BYTE_OFFSET(10000) [%d] !\n",BYTE_OFFSET(10000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): ADDRESS_AND_SIZE_TO_SPAN_PAGES(10000,3000) [%d] !\n",ADDRESS_AND_SIZE_TO_SPAN_PAGES(10000,3000)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): ADDRESS_AND_SIZE_TO_SPAN_PAGES(4090,10) [%d] !\n",ADDRESS_AND_SIZE_TO_SPAN_PAGES(4090,10)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): ADDRESS_AND_SIZE_TO_SPAN_PAGES(8190,10) [%d] !\n",ADDRESS_AND_SIZE_TO_SPAN_PAGES(8190,10)));
	KdPrint((DRIVERNAME " - FUNCTION PrintPageMacros(): ADDRESS_AND_SIZE_TO_SPAN_PAGES(10,8192) [%d] !\n",ADDRESS_AND_SIZE_TO_SPAN_PAGES(10,8192)));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void LockUnlockPages(void)
{
	// FUNCTION DispatchSystemControl() sa premiestni do NON-PAGED CODE SECTION.
	PVOID														Handle=MmLockPagableCodeSection(DispatchSystemControl);

	KdPrint((DRIVERNAME " - FUNCTION LockUnlockPages(): LOCKING CODE PAGE [%p] !\n",Handle));

	// FUNCTION DispatchSystemControl() sa premiestni do PAGED CODE SECTION.
	MmUnlockPagableImageSection(Handle);

	KdPrint((DRIVERNAME " - FUNCTION LockUnlockPages(): UNLOCKING CODE PAGE [%p] !\n",Handle));

	// FUNCTION DispatchSystemControl() sa premiestni do NON-PAGED CODE SECTION.
	MmLockPagableSectionByHandle(Handle);

	KdPrint((DRIVERNAME " - FUNCTION LockUnlockPages(): LOCKING CODE PAGE [%p] !\n",Handle));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void AllocateMemoryFromHeapTest(void)
{
	// TAG sa v X86 a X64 architekturach pri LITTLE ENDIAN OBRATI NAOPAK.
	PVOID														Pointer=ExAllocatePoolWithTag(NonPagedPool,10*1000,'DCBA');
	
	if (Pointer!=NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateMemoryFromHeapTest(): MEMORY at ADDRESS [%p] was ALLOCATED !\n",Pointer));

		/*
		CHAR*													CharPointer=(CHAR*) Pointer;

		// TAG zacina na pozicii (Pointer-4).
		// ??? Vypisalo mi namiesto TAG hodnotu 0.
		KdPrint((DRIVERNAME " - FUNCTION AllocateMemoryFromHeapTest(): BYTE at ADDRESS [%p] is [%x] !\n",CharPointer-1,*(CharPointer-1)));
		KdPrint((DRIVERNAME " - FUNCTION AllocateMemoryFromHeapTest(): BYTE at ADDRESS [%p] is [%x] !\n",CharPointer-2,*(CharPointer-2)));
		KdPrint((DRIVERNAME " - FUNCTION AllocateMemoryFromHeapTest(): BYTE at ADDRESS [%p] is [%x] !\n",CharPointer-3,*(CharPointer-3)));
		KdPrint((DRIVERNAME " - FUNCTION AllocateMemoryFromHeapTest(): BYTE at ADDRESS [%p] is [%x] !\n",CharPointer-4,*(CharPointer-4)));
		*/

		// MUSIM dat TEN ISTY TAG.
		ExFreePoolWithTag(Pointer,'DCBA');
		Pointer=NULL;

		KdPrint((DRIVERNAME " - FUNCTION AllocateMemoryFromHeapTest(): MEMORY RELEASED !\n"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateMemoryFromHeapTest(): MEMORY was NOT ALLOCATED !\n"));
	}
}
//-------------------------------------------------------------------------------------------------------
void AllocateNotEnoughMemoryTest1(void)
{
	SIZE_T														MemorySize=1024*1024*1024;

	MemorySize*=1024;

	// Pokusim sa o alokovanie 1 TB MEMORY.
	PVOID														Pointer=ExAllocatePoolWithTag(NonPagedPool,MemorySize,'DCBA');

	// !!! V pripade NEDOSTATKU MEMORY je vratena hodnota NULL.
	if (Pointer!=NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest1(): MEMORY at ADDRESS [%p] was ALLOCATED !\n",Pointer));

		// MUSIM dat TEN ISTY TAG.
		ExFreePoolWithTag(Pointer,'DCBA');
		Pointer=NULL;

		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest1(): MEMORY RELEASED !\n"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest1(): MEMORY with SIZE [%I64d] was NOT ALLOCATED !\n",MemorySize));
	}
}
//-------------------------------------------------------------------------------------------------------
void AllocateNotEnoughMemoryTest2(void)
{
	SIZE_T														MemorySize=1024*1024*1024;

	MemorySize*=1024;

	__try
	{
		// Pokusim sa o alokovanie 1 TB MEMORY s FLAG POOL_RAISE_IF_ALLOCATION_FAILURE.
		// !!! V pripade NEDOSTATKU MEMORY hodi SEH EXCEPTION.
		PVOID													Pointer=ExAllocatePoolWithTag((POOL_TYPE) (NonPagedPool | POOL_RAISE_IF_ALLOCATION_FAILURE),MemorySize,'DCBA');

		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest2(): MEMORY at ADDRESS [%p] was ALLOCATED !\n",Pointer));

		// MUSIM dat TEN ISTY TAG.
		ExFreePoolWithTag(Pointer,'DCBA');
		Pointer=NULL;

		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest2(): MEMORY RELEASED !\n"));
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest2(): MEMORY with SIZE [%I64d] was NOT ALLOCATED !\n",MemorySize));
	}
}
//-------------------------------------------------------------------------------------------------------
void AllocateNotEnoughMemoryTest3(void)
{
	SIZE_T														MemorySize=1024*1024*1024;

	MemorySize*=1024;

	// Pokusim sa o alokovanie 1 TB MEMORY s PARAMETEROM 'NonPagedPoolMustSucceed'.
	// !!!!! V pripade NEDOSTATKU MEMORY sa vykona BUG CHECK.
	PVOID														Pointer=ExAllocatePoolWithTag(NonPagedPoolMustSucceed,MemorySize,'DCBA');

	if (Pointer!=NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest3(): MEMORY at ADDRESS [%p] was ALLOCATED !\n",Pointer));

		// MUSIM dat TEN ISTY TAG.
		ExFreePoolWithTag(Pointer,'DCBA');
		Pointer=NULL;

		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest3(): MEMORY RELEASED !\n"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateNotEnoughMemoryTest3(): MEMORY with SIZE [%I64d] was NOT ALLOCATED !\n",MemorySize));
	}
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! STRUCTURE reprezentuje LIST ITEM, ktory sa bude vkladat do LIST.
struct SMyDoubleListItem
{
	// CUSTOM FIELDS.
	INT32														MValue1;

	// !!! POVINY FIELD reprezentujuci LINK na dalsie LIST ITEMS.
	LIST_ENTRY													MLink;

	// CUSTOM FIELDS.
	INT32														MValue2;
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! STRUCTURE reprezentuje LIST ITEM, ktory sa bude vkladat do LIST.
struct SMySingleListItem
{
	// CUSTOM FIELDS.
	INT32														MValue1;

	// !!! POVINY FIELD reprezentujuci LINK na dalsi LIST ITEM.
	SINGLE_LIST_ENTRY											MLink;

	// CUSTOM FIELDS.
	INT32														MValue2;
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
SMyDoubleListItem* AllocateDoubleListItem(INT32 Value1, INT32 Value2)
{
	SMyDoubleListItem*											MyDoubleListItem=(SMyDoubleListItem*) ExAllocatePool(PagedPool,sizeof(SMyDoubleListItem));

	if (MyDoubleListItem==NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateDoubleListItem(): Can't ALLOCATE DOUBLE LIST ITEM !\n"));
	}
	else
	{
		MyDoubleListItem->MValue1=Value1;
		MyDoubleListItem->MValue2=Value2;
	}

	return(MyDoubleListItem);
}
//-------------------------------------------------------------------------------------------------------
void DumpDoubleListForward(LIST_ENTRY* List)
{
	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListForward(): BEGIN !\n"));

	if (IsListEmpty(List)==false)
	{
		// !!!!! MUSIM sa presunut na Flink, lebo HEAD NIKDY NEOBSAHUJE LIST ITEM.
		LIST_ENTRY*												Iterator=List->Flink;

		for(;;)
		{
			SMyDoubleListItem*									ListItem=CONTAINING_RECORD(Iterator,SMyDoubleListItem,MLink);

			KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListForward(): ITEM [%d, %d] !\n",ListItem->MValue1,ListItem->MValue2));

			Iterator=Iterator->Flink;

			if (Iterator==List)
			{
				break;
			}
		}
	}

	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListForward(): END !\n"));
}
//-------------------------------------------------------------------------------------------------------
void DumpDoubleListBackward(LIST_ENTRY* List)
{
	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListBackward(): BEGIN !\n"));

	if (IsListEmpty(List)==false)
	{
		// !!!!! MUSIM sa presunut na Blink, lebo HEAD NIKDY NEOBSAHUJE LIST ITEM.
		LIST_ENTRY*												Iterator=List->Blink;

		for(;;)
		{
			SMyDoubleListItem*									ListItem=CONTAINING_RECORD(Iterator,SMyDoubleListItem,MLink);

			KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListBackward(): ITEM [%d, %d] !\n",ListItem->MValue1,ListItem->MValue2));

			Iterator=Iterator->Blink;

			if (Iterator==List)
			{
				break;
			}
		}
	}

	KdPrint((DRIVERNAME " - FUNCTION DumpDoubleListBackward(): END !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestDoublyLinkedList(void)
{
	// !!! Reprezentuje HEAD, ktory NEOBSAHUJE LIST ITEM.
	LIST_ENTRY													List;

	// Nainicailizuje sa LIST.
	InitializeListHead(&List);

	KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): AFTER INITIALIZATION - IS LIST EMPTY [%d] !\n",IsListEmpty(&List)));

	for(;;)
	{
		SMyDoubleListItem*										MyDoubleListItem;
	
		// Alokuje sa ITEM.
		if ((MyDoubleListItem=AllocateDoubleListItem(1,101))==NULL)
		{
			break;
		}

		// ITEM sa prida ako POSLEDNY ITEM.
		InsertTailList(&List,&MyDoubleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): AFTER INSERT - IS LIST EMPTY [%d] !\n",IsListEmpty(&List)));
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
		DumpDoubleListForward(&List);

		// Alokuje sa ITEM.
		if ((MyDoubleListItem=AllocateDoubleListItem(2,102))==NULL)
		{
			break;
		}

		// ITEM sa prida ako POSLEDNY ITEM.
		InsertTailList(&List,&MyDoubleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
		DumpDoubleListForward(&List);

		// Alokuje sa ITEM.
		if ((MyDoubleListItem=AllocateDoubleListItem(3,103))==NULL)
		{
			break;
		}

		// ITEM sa prida ako PRVY ITEM.
		InsertHeadList(&List,&MyDoubleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
		DumpDoubleListForward(&List);

		// Alokuje sa ITEM.
		if ((MyDoubleListItem=AllocateDoubleListItem(4,104))==NULL)
		{
			break;
		}

		// ITEM sa prida ako PRVY ITEM.
		InsertHeadList(&List,&MyDoubleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
		DumpDoubleListForward(&List);

		// Alokuje sa ITEM.
		if ((MyDoubleListItem=AllocateDoubleListItem(5,105))==NULL)
		{
			break;
		}

		// ITEM sa prida ako POSLEDNY ITEM.
		InsertTailList(&List,&MyDoubleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): INSERTING ITEM [%d, %d] !\n",MyDoubleListItem->MValue1,MyDoubleListItem->MValue2));
		DumpDoubleListForward(&List);

		DumpDoubleListBackward(&List);

		// Odstrani sa PRVY ITEM z LIST.
		LIST_ENTRY*												RemovedListEntry1=RemoveHeadList(&List);
		SMyDoubleListItem*										RemovedListItem1=CONTAINING_RECORD(RemovedListEntry1,SMyDoubleListItem,MLink);
		
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): REMOVING ITEM [%d, %d] !\n",RemovedListItem1->MValue1,RemovedListItem1->MValue2));
		ExFreePool(RemovedListItem1);
		RemovedListItem1=NULL;
		DumpDoubleListForward(&List);

		// Odstrani sa POSLEDNY ITEM z LIST.
		LIST_ENTRY*												RemovedListEntry2=RemoveTailList(&List);
		SMyDoubleListItem*										RemovedListItem2=CONTAINING_RECORD(RemovedListEntry2,SMyDoubleListItem,MLink);
		
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): REMOVING ITEM [%d, %d] !\n",RemovedListItem2->MValue1,RemovedListItem2->MValue2));
		ExFreePool(RemovedListItem2);
		RemovedListItem2=NULL;
		DumpDoubleListForward(&List);

		// Odstrani sa DRUHY ITEM z LIST.
		LIST_ENTRY*												RemovedListEntry3=List.Flink->Flink;

		RemoveEntryList(RemovedListEntry3);

		SMyDoubleListItem*										RemovedListItem3=CONTAINING_RECORD(RemovedListEntry3,SMyDoubleListItem,MLink);
		
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): REMOVING ITEM [%d, %d] !\n",RemovedListItem3->MValue1,RemovedListItem3->MValue2));
		ExFreePool(RemovedListItem3);
		RemovedListItem3=NULL;
		DumpDoubleListForward(&List);

		DumpDoubleListBackward(&List);

		break;
	}

	// Odstrania sa VSETKY ITEMS z LIST.
	while(IsListEmpty(&List)==false)
	{
		LIST_ENTRY*												RemovedListEntry=RemoveHeadList(&List);
		SMyDoubleListItem*										RemovedListItem=CONTAINING_RECORD(RemovedListEntry,SMyDoubleListItem,MLink);
		
		KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): REMOVING ITEM [%d, %d] !\n",RemovedListItem->MValue1,RemovedListItem->MValue2));

		ExFreePool(RemovedListItem);
		RemovedListItem=NULL;
	}

	KdPrint((DRIVERNAME " - FUNCTION TestDoublyLinkedList(): AFTER CLEAR - IS LIST EMPTY [%d] !\n",IsListEmpty(&List)));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
SMySingleListItem* AllocateSingleListItem(INT32 Value1, INT32 Value2)
{
	SMySingleListItem*											MySingleListItem=(SMySingleListItem*) ExAllocatePool(PagedPool,sizeof(SMySingleListItem));

	if (MySingleListItem==NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION AllocateSingleListItem(): Can't ALLOCATE SINGLY LIST ITEM !\n"));
	}
	else
	{
		MySingleListItem->MValue1=Value1;
		MySingleListItem->MValue2=Value2;
	}

	return(MySingleListItem);
}
//-------------------------------------------------------------------------------------------------------
void DumpSinglyList(SINGLE_LIST_ENTRY* List)
{
	KdPrint((DRIVERNAME " - FUNCTION DumpSinglyList(): BEGIN !\n"));

	if (List->Next!=NULL)
	{
		// !!!!! MUSIM sa presunut na Next, lebo HEAD NIKDY NEOBSAHUJE LIST ITEM.
		SINGLE_LIST_ENTRY*										Iterator=List->Next;

		for(;;)
		{
			SMySingleListItem*									ListItem=CONTAINING_RECORD(Iterator,SMySingleListItem,MLink);

			KdPrint((DRIVERNAME " - FUNCTION DumpSinglyList(): ITEM [%d, %d] !\n",ListItem->MValue1,ListItem->MValue2));

			Iterator=Iterator->Next;

			if (Iterator==NULL)
			{
				break;
			}
		}
	}

	KdPrint((DRIVERNAME " - FUNCTION DumpSinglyList(): END !\n"));
}
//-------------------------------------------------------------------------------------------------------
void TestSinglyLinkedList(void)
{
	// !!! Reprezentuje HEAD, ktory NEOBSAHUJE LIST ITEM.
	SINGLE_LIST_ENTRY											List;

	// Nainicailizuje sa LIST.
	List.Next=NULL;

	KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): AFTER INITIALIZATION - IS LIST EMPTY [%d] !\n",(List.Next==NULL)));

	for(;;)
	{
		SMySingleListItem*										MySingleListItem;
	
		// Alokuje sa ITEM.
		if ((MySingleListItem=AllocateSingleListItem(1,101))==NULL)
		{
			break;
		}

		// Prida ITEM na VRCHOL STACKU.
		PushEntryList(&List,&MySingleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): AFTER INSERT - IS LIST EMPTY [%d] !\n",(List.Next==NULL)));
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
		DumpSinglyList(&List);

		// Alokuje sa ITEM.
		if ((MySingleListItem=AllocateSingleListItem(2,102))==NULL)
		{
			break;
		}

		// Prida ITEM na VRCHOL STACKU.
		PushEntryList(&List,&MySingleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
		DumpSinglyList(&List);

		// Alokuje sa ITEM.
		if ((MySingleListItem=AllocateSingleListItem(3,103))==NULL)
		{
			break;
		}

		// Prida ITEM na VRCHOL STACKU.
		PushEntryList(&List,&MySingleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
		DumpSinglyList(&List);

		// Alokuje sa ITEM.
		if ((MySingleListItem=AllocateSingleListItem(4,104))==NULL)
		{
			break;
		}

		// Prida ITEM na VRCHOL STACKU.
		PushEntryList(&List,&MySingleListItem->MLink);
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): INSERTING ITEM [%d, %d] !\n",MySingleListItem->MValue1,MySingleListItem->MValue2));
		DumpSinglyList(&List);

		// Odstrani sa ITEM z VRCHOLA LIST.
		SINGLE_LIST_ENTRY*										RemovedListEntry1=PopEntryList(&List);
		SMySingleListItem*										RemovedListItem1=CONTAINING_RECORD(RemovedListEntry1,SMySingleListItem,MLink);
		
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): REMOVING ITEM [%d, %d] !\n",RemovedListItem1->MValue1,RemovedListItem1->MValue2));
		ExFreePool(RemovedListItem1);
		RemovedListItem1=NULL;
		DumpSinglyList(&List);

		// Odstrani sa ITEM z VRCHOLA LIST.
		SINGLE_LIST_ENTRY*										RemovedListEntry2=PopEntryList(&List);
		SMySingleListItem*										RemovedListItem2=CONTAINING_RECORD(RemovedListEntry2,SMySingleListItem,MLink);
		
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): REMOVING ITEM [%d, %d] !\n",RemovedListItem2->MValue1,RemovedListItem2->MValue2));
		ExFreePool(RemovedListItem2);
		RemovedListItem2=NULL;
		DumpSinglyList(&List);

		break;
	}

	// Odstrania sa VSETKY ITEMS z LIST.
	while((List.Next!=NULL))
	{
		SINGLE_LIST_ENTRY*										RemovedListEntry=PopEntryList(&List);
		SMySingleListItem*										RemovedListItem=CONTAINING_RECORD(RemovedListEntry,SMySingleListItem,MLink);
		
		KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): REMOVING ITEM [%d, %d] !\n",RemovedListItem->MValue1,RemovedListItem->MValue2));

		ExFreePool(RemovedListItem);
		RemovedListItem=NULL;
	}

	KdPrint((DRIVERNAME " - FUNCTION TestSinglyLinkedList(): AFTER CLEAR - IS LIST EMPTY [%d] !\n",(List.Next==NULL)));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestLookasideList(void)
{
	// !!!!! MEMORY pre LOOKASIDE LIST BEZ OHLADU na to ci bude ukladat PAGED, alebo NON-PAGED MEMORY MUSI byt VZDY v NON-PAGED MEMORY.
	PAGED_LOOKASIDE_LIST*										List=(PAGED_LOOKASIDE_LIST*) ExAllocatePool(NonPagedPool,sizeof(PAGED_LOOKASIDE_LIST));

	if (List!=NULL)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestLookasideList(): PAGED_LOOKASIDE_LIST ALLOCATED !\n"));

		// LOOKASIDE LIST bude v PAGED MEMORY a bude mat dlkzu bloku 10000 BYTES.
		// !!! Pouziju sa DEFAULT FUNCTION pre ALLOCATION i FREE, ktore sa volaju ak je LOOKASIDE LIST PLNY a je nutne alokovat MEMORY BLOCK z GLOBAL MEMORY POOL.
		ExInitializePagedLookasideList(List,NULL,NULL,0,10000,'DCBA',0);

		// Alokuje sa 1. BLOCK PAGED MEMORY.
		CHAR*													Block1=(CHAR*) ExAllocateFromPagedLookasideList(List);
		// Alokuje sa 2. BLOCK PAGED MEMORY.
		CHAR*													Block2=(CHAR*) ExAllocateFromPagedLookasideList(List);
		
		if (Block1!=NULL && Block2!=NULL)
		{
			strcpy_s(Block1,10000,"Timmy");
			strcpy_s(Block2,10000,"Anderson");

			KdPrint((DRIVERNAME " - FUNCTION TestLookasideList(): DATA from BLOCKS [%s %s] !\n",Block1,Block2));
		}

		if (Block1!=NULL)
		{
			// Uvolni sa 1. BLOCK PAGED MEMORY.
			ExFreeToPagedLookasideList(List,Block1);
			Block1=NULL;
		}

		if (Block2!=NULL)
		{
			// Uvolni sa 2. BLOCK PAGED MEMORY.
			ExFreeToPagedLookasideList(List,Block2);
			Block2=NULL;
		}

		// !!!!! EXTREMNE DOLEZITE je UVOLNIT LOOKASIDE POOL, inak SYSTEM pri spusteni OPTIMALIZACIE ho bude povazovat za VALIDNY LOOKASIDE POOL a SPADNE.
		ExDeletePagedLookasideList(List);

		// !!! Uvolni sa STRUCTURE PAGED_LOOKASIDE_LIST.
		ExFreePool(List);
		List=NULL;

		KdPrint((DRIVERNAME " - FUNCTION TestLookasideList(): PAGED_LOOKASIDE_LIST FREED !\n"));
	}
	else
	{
		KdPrint((DRIVERNAME " - FUNCTION TestLookasideList(): Can't ALLOCATE LOOKASIDE LIST !\n"));
	}
}
//-------------------------------------------------------------------------------------------------------
void TestNullTerminatedStringFunctions(void)
{
	CHAR														Buffer1[1000];
	CHAR														Buffer2[1000];

	RtlZeroMemory(Buffer1,sizeof(Buffer1));
	RtlZeroMemory(Buffer2,sizeof(Buffer2));

	RtlStringCchPrintfA(Buffer1,_countof(Buffer1),"My name is [%s %s] ! I'm [%d] years old !","Timmy","Anderson",12);

	KdPrint((DRIVERNAME " - FUNCTION TestNullTerminatedStringFunctions(): BUFFER 1 [%s] !\n",Buffer1));

	RtlStringCchCatA(Buffer1,_countof(Buffer1)," I live in Minneapolis !");
	
	KdPrint((DRIVERNAME " - FUNCTION TestNullTerminatedStringFunctions(): BUFFER 1 [%s] !\n",Buffer1));

	size_t														Length;

	RtlStringCchLengthA(Buffer1,_countof(Buffer1),&Length);

	KdPrint((DRIVERNAME " - FUNCTION TestNullTerminatedStringFunctions(): BUFFER 1 LENGTH [%d] !\n",Length));

	RtlStringCchCopyA(Buffer2,_countof(Buffer2),Buffer1);

	KdPrint((DRIVERNAME " - FUNCTION TestNullTerminatedStringFunctions(): BUFFER 2 [%s] !\n",Buffer2));
}
//-------------------------------------------------------------------------------------------------------
void TestAnsiString1(void)
{
	ANSI_STRING													String;

	// !!!!! NEALOKUJE MEMORY, iba inicializuje STRUCTURE ANSI_STRING.
	RtlInitString(&String,"Timmy Anderson");
	
	KdPrint((DRIVERNAME " - FUNCTION TestAnsiString1(): STRING [%s], LENGTH [%d], MAXIMUM LENGTH [%d] !\n",String.Buffer,String.Length,String.MaximumLength));

	// !!!!! NESMIE sa VOLAT, lebo String1 odkazuje na CONSTANT 'Timmy Anderson'.
	// !!!!! Ak by sa zavolala tato FUNCTION - dojde k PADU SYSTEMU.
	//RtlFreeAnsiString(&String);
}
//-------------------------------------------------------------------------------------------------------
void TestAnsiString2(void)
{
	UNICODE_STRING												UnicodeString;

	// !!!!! NEALOKUJE MEMORY, iba inicializuje STRUCTURE ANSI_STRING.
	RtlInitUnicodeString(&UnicodeString,L"Timmy Anderson");

	ANSI_STRING													String;

	// !!! Konverzia sposobi ALOKACIU MEMORY.
	RtlUnicodeStringToAnsiString(&String,&UnicodeString,TRUE);

	KdPrint((DRIVERNAME " - FUNCTION TestAnsiString2(): STRING [%s], LENGTH [%d], MAXIMUM LENGTH [%d] !\n",String.Buffer,String.Length,String.MaximumLength));

	// !!!!! MUSI sa VOLAT, lebo String obsahuje ALOKOVANY BUFFER.
	RtlFreeAnsiString(&String);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestRegistry1(DEVICE_OBJECT* PhysicalDeviceObject)
{
	NTSTATUS													Status;
	HANDLE														HKey=NULL;

	for(;;)
	{
		// !!! Otvori REGISTRY KEY asicovany s REGISTRED INTERFACE.
		if (NT_SUCCESS(Status=IoOpenDeviceRegistryKey(PhysicalDeviceObject,PLUGPLAY_REGKEY_DEVICE,KEY_READ,&HKey))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry1(): Can't OPEN REGISTRY KEY, STATUS [%X] !\n",Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestRegistry1(): REGISTRY KEY SUCCESSFULLY OPENED !\n"));
		break;
	}
	if (HKey!=NULL)
	{
		if (NT_SUCCESS(ZwClose(HKey))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry1(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
		}
	}
}
//-------------------------------------------------------------------------------------------------------
void TestRegistry2(UNICODE_STRING* InterfaceName)
{
	NTSTATUS													Status;
	ANSI_STRING													InterfaceNameANSI;
	HANDLE														HKey=NULL;

	RtlUnicodeStringToAnsiString(&InterfaceNameANSI,InterfaceName,TRUE);

	for(;;)
	{
		// !!! Otvori REGISTRY KEY asicovany s REGISTRED INTERFACE.
		if (NT_SUCCESS(Status=IoOpenDeviceInterfaceRegistryKey(InterfaceName,KEY_READ,&HKey))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry2(): Can't OPEN REGISTRY KEY, STATUS [%X] !\n",Status));
			break;
		}
		
		KdPrint((DRIVERNAME " - FUNCTION TestRegistry2(): REGISTRY KEY [%s] SUCCESSFULLY OPENED !\n",InterfaceNameANSI.Buffer));
		break;
	}
	if (HKey!=NULL)
	{
		if (NT_SUCCESS(ZwClose(HKey))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry2(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
		}
	}

	RtlFreeAnsiString(&InterfaceNameANSI);
}
//-------------------------------------------------------------------------------------------------------
void TestRegistry3(void)
{
	NTSTATUS													Status;
	OBJECT_ATTRIBUTES											Attributes;
	UNICODE_STRING												RegistryPath;
	UNICODE_STRING												ValueName;
	ANSI_STRING													RegistryPathANSI;
	ANSI_STRING													ValueNameANSI;
	KEY_VALUE_PARTIAL_INFORMATION*								PartialInformation=NULL;

	RtlInitUnicodeString(&RegistryPath,L"\\Registry\\Machine\\Software");
	RtlInitUnicodeString(&ValueName,L"MyName");

	RtlUnicodeStringToAnsiString(&RegistryPathANSI,&RegistryPath,TRUE);
	RtlUnicodeStringToAnsiString(&ValueNameANSI,&ValueName,TRUE);

	// Inicializuje OBJECT_ATTRIBUTES na REGISTRY PATH.
	// !!! FLAG OBJ_KERNEL_HANDLE je VELMI DOLEZITY, pretoze bez neho by HANDLE na REGISTRY KEY bol pristupny aj v USER MODE, kde by ho PROCESS mohol napriklad ZMAZAT.
	InitializeObjectAttributes(&Attributes,&RegistryPath,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,NULL,NULL);

	HANDLE														HKey=NULL;

	for(;;)
	{
		if (NT_SUCCESS(Status=ZwOpenKey(&HKey,KEY_ALL_ACCESS,&Attributes))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): Can't OPEN REGISTRY KEY, STATUS [%X] !\n",Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): REGISTRY KEY [%s] SUCCESSFULLY OPENED !\n",RegistryPathANSI.Buffer));

		wchar_t													Value[]=L"Timmy Anderson";

		// Zapise sa KEY do REGISTRY.
		if (NT_SUCCESS(Status=ZwSetValueKey(HKey,&ValueName,0,REG_SZ,Value,sizeof(Value)))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): Can't write REGISTRY KEY [%s], STATUS [%X] !\n",ValueNameANSI.Buffer,Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): REGISTRY KEY [%s] SUCCESSFULLY WRITTEN !\n",ValueNameANSI.Buffer));

		ULONG													KeySize=0;

		// !!! Vycitam DLZKU potrebnu pre ulozenie PARTIAL INFORMATION o REGISTRY KEY.
		// !!! FUNCTION vrati ERROR CODE, ale to je OK, lebo som zistoval len mnozstvo potrebnej pamate.
		if (NT_SUCCESS(Status=ZwQueryValueKey(HKey,&ValueName,KeyValuePartialInformation,NULL,0,&KeySize))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): REGISTRY KEY [%s] needs [%d] BYTES to STORE, STATUS [%X] !\n",ValueNameANSI.Buffer,KeySize,Status));
		}

		if ((PartialInformation=(KEY_VALUE_PARTIAL_INFORMATION*)ExAllocatePool(PagedPool,KeySize))==NULL)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): Can't ALLOCATE MEMORY, STATUS [%X] !\n",Status));
			break;
		}

		if (NT_SUCCESS(Status=ZwQueryValueKey(HKey,&ValueName,KeyValuePartialInformation,PartialInformation,KeySize,&KeySize))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): Can't read REGISTRY KEY [%s], STATUS [%X] !\n",ValueNameANSI.Buffer,Status));
			break;
		}

		// Vytiahnem KEY VALUE z KEY_VALUE_PARTIAL_INFORMATION.
		wchar_t*												KeyValueReadFromRegistry=(wchar_t*) PartialInformation->Data;
		UNICODE_STRING											ValueUNICODE;
		ANSI_STRING												ValueANSI;

		RtlInitUnicodeString(&ValueUNICODE,KeyValueReadFromRegistry);
		RtlUnicodeStringToAnsiString(&ValueANSI,&ValueUNICODE,true);
		
		KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): REGISTRY KEY [%s] contains VALUE [%s], TYPE [%d] !\n",ValueNameANSI.Buffer,ValueANSI.Buffer,PartialInformation->Type));

		RtlFreeAnsiString(&ValueANSI);

		// !!! Odstrani VALUE z REGISTRY KEY.
		if (NT_SUCCESS(Status=ZwDeleteValueKey(HKey,&ValueName))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): Can't delete REGISTRY KEY [%s], STATUS [%X] !\n",ValueNameANSI.Buffer,Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): REGISTRY KEY [%s] was DELETED !\n",ValueNameANSI.Buffer));

		break;
	}

	if (HKey!=NULL)
	{
		if (NT_SUCCESS(ZwClose(HKey))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry3(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
		}
	}

	if (PartialInformation!=NULL)
	{
		ExFreePool(PartialInformation);
		PartialInformation=NULL;
	}

	RtlFreeAnsiString(&RegistryPathANSI);
	RtlFreeAnsiString(&ValueNameANSI);
}
//-------------------------------------------------------------------------------------------------------
void TestRegistry4(void)
{
	NTSTATUS													Status;
	OBJECT_ATTRIBUTES											Attributes;
	UNICODE_STRING												RegistryPath;
	ANSI_STRING													RegistryPathANSI;
	KEY_FULL_INFORMATION*										FullInformation=NULL;

	RtlInitUnicodeString(&RegistryPath,L"\\Registry\\Machine");
	RtlUnicodeStringToAnsiString(&RegistryPathANSI,&RegistryPath,TRUE);

	// Inicializuje OBJECT_ATTRIBUTES na REGISTRY PATH.
	// !!! FLAG OBJ_KERNEL_HANDLE je VELMI DOLEZITY, pretoze bez neho by HANDLE na REGISTRY KEY bol pristupny aj v USER MODE, kde by ho PROCESS mohol napriklad ZMAZAT.
	InitializeObjectAttributes(&Attributes,&RegistryPath,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,NULL,NULL);

	HANDLE														HKey=NULL;

	for(;;)
	{
		if (NT_SUCCESS(Status=ZwOpenKey(&HKey,KEY_ALL_ACCESS,&Attributes))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): Can't OPEN REGISTRY KEY, STATUS [%X] !\n",Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): REGISTRY KEY [%s] SUCCESSFULLY OPENED !\n",RegistryPathANSI.Buffer));

		ULONG													SoftwareKeyFullInformationSize=0;

		// !!! Vyziadam si DLZKU FULL INFORMATION o KEY.
		if (NT_SUCCESS(Status=ZwQueryKey(HKey,KeyFullInformation,NULL,0,&SoftwareKeyFullInformationSize))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): REGISTRY KEY [%s] needs [%d] BYTES to STORE KEY, STATUS [%X] !\n",RegistryPathANSI.Buffer,SoftwareKeyFullInformationSize,Status));
		}

		if ((FullInformation=(KEY_FULL_INFORMATION*)ExAllocatePool(PagedPool,SoftwareKeyFullInformationSize))==NULL)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): Can't ALLOCATE MEMORY, STATUS [%X] !\n",Status));
			break;
		}

		// !!! Nacitam FULL INFORMATION o KEY.
		if (NT_SUCCESS(Status=ZwQueryKey(HKey,KeyFullInformation,FullInformation,SoftwareKeyFullInformationSize,&SoftwareKeyFullInformationSize))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): Can't read REGISTRY KEY [%s] FULL INFORMATION, STATUS [%X] !\n",RegistryPathANSI.Buffer,Status));
			break;
		}
		
		KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): REGISTRY KEY [%s] contains [%d] VALUES and [%d] KEYS !\n",RegistryPathANSI.Buffer,FullInformation->Values,FullInformation->SubKeys));

		// !!! ENUMERUJEM vsetky SUBKEYS.
		for (ULONG Index=0;Index<FullInformation->SubKeys;Index++)
		{
			ULONG												SubkeyKeyBasicInformationSize=0;
			KEY_BASIC_INFORMATION*								BasicInformation=NULL;

			// !!! Vyziadam si DLZKU BASIC INFORMATION o SUBKEY.
			if (NT_SUCCESS(Status=ZwEnumerateKey(HKey,Index,KeyBasicInformation,NULL,0,&SubkeyKeyBasicInformationSize))==false)
			{
				KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): REGISTRY SUBKEY needs [%d] BYTES to STORE SUBKEY, STATUS [%X] !\n",SubkeyKeyBasicInformationSize,Status));
			}

			if ((BasicInformation=(KEY_BASIC_INFORMATION*)ExAllocatePool(PagedPool,SubkeyKeyBasicInformationSize))==NULL)
			{
				KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): Can't ALLOCATE MEMORY, STATUS [%X] !\n",Status));
				break;
			}

			// !!! Nacitam BASIC INFORMATION o SUBKEY.
			if (NT_SUCCESS(Status=ZwEnumerateKey(HKey,Index,KeyBasicInformation,BasicInformation,SubkeyKeyBasicInformationSize,&SubkeyKeyBasicInformationSize))==false)
			{
				KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): Can't read REGISTRY SUBKEY BASIC INFORMATION, STATUS [%X] !\n",Status));

				if (BasicInformation!=NULL)
				{
					ExFreePool(BasicInformation);
					BasicInformation=NULL;
				}

				break;
			}

			UNICODE_STRING										SubKeyNameUNICODE;
			ANSI_STRING											SubKeyNameANSI;
			wchar_t												Buffer[1000];

			// !!! FILED BasicInformation->Name NIE JE UKONCENY NULL TERMINATOR.
			RtlStringCbCopyNW(Buffer,sizeof(Buffer),BasicInformation->Name,BasicInformation->NameLength);
			Buffer[BasicInformation->NameLength/sizeof(wchar_t)]='\0';

			RtlInitUnicodeString(&SubKeyNameUNICODE,Buffer);
			RtlUnicodeStringToAnsiString(&SubKeyNameANSI,&SubKeyNameUNICODE,TRUE);
			
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): REGISTRY SUBKEY[%d] has NAME [%s] !\n",Index,SubKeyNameANSI.Buffer));

			RtlFreeAnsiString(&SubKeyNameANSI);

			if (BasicInformation!=NULL)
			{
				ExFreePool(BasicInformation);
				BasicInformation=NULL;
			}
		}

		break;
	}

	if (HKey!=NULL)
	{
		if (NT_SUCCESS(ZwClose(HKey))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestRegistry4(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
		}
	}

	if (FullInformation!=NULL)
	{
		ExFreePool(FullInformation);
		FullInformation=NULL;
	}

	RtlFreeAnsiString(&RegistryPathANSI);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
void TestWriteFile(void)
{
	NTSTATUS													Status;
	OBJECT_ATTRIBUTES											Attributes;
	UNICODE_STRING												FilePath;
	ANSI_STRING													FilePathANSI;

	// !!!!! ABSOLUTE PATH MUSI obsahovat PREFIX '\\??\\', alebo sa moze pouzit RELATIVE PATH s PREFIX '\SystemRoot' je je FILE vo WINDOWS SYSTEM ROOT DIRECTORY.
	// !!!!! PREFIX '\\??\\C:' oznacuje DISK 'C:' pomenovany cez MS DOS NAMING CONVENTION. Namiesto toho by sa dala pouzit aj PATH obsahujuca NAZOV DISKU.
	RtlInitUnicodeString(&FilePath,L"\\??\\C:\\MyTest.txt");

	// Nazov DISK DRIVE bol zisteny pomocou TOOL [WinObj.EXE] od SYS INTERNALS.
	//RtlInitUnicodeString(&FilePath,L"\\Device\\HarddiskVolume2\\MyTest.txt");

	RtlUnicodeStringToAnsiString(&FilePathANSI,&FilePath,TRUE);

	// Inicializuje OBJECT_ATTRIBUTES na FILE PATH.
	// !!! FLAG OBJ_KERNEL_HANDLE je VELMI DOLEZITY, pretoze bez neho by HANDLE bol asociovany s PROCESSOM, v ktoreho THREAD vykonavam tento kod. Pri ukonceni PROCESSU, alebo pouziti THREADU s INEHO PROCESSU by doslo k PADU SYSTEMU.
	InitializeObjectAttributes(&Attributes,&FilePath,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,NULL,NULL);

	HANDLE														HFile=NULL;

	for(;;)
	{
		IO_STATUS_BLOCK											IoStatusBlock;

		// Otvorim FILE pre WRITE.
		if (NT_SUCCESS(Status=ZwCreateFile(&HFile,GENERIC_WRITE,&Attributes,&IoStatusBlock,NULL,FILE_ATTRIBUTE_NORMAL,0,FILE_OVERWRITE_IF,FILE_SYNCHRONOUS_IO_NONALERT,NULL,0))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): Can't OPEN FILE [%s], STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): FILE [%s] SUCCESSFULLY OPENED, IO STATUS [%X] !\n",FilePathANSI.Buffer,IoStatusBlock.Status));

		CHAR													DataToWrite[]="My name is Timmy Anderson !";

		// Zapisem DATA do FILE.
		if (NT_SUCCESS(Status=ZwWriteFile(HFile,NULL,NULL,NULL,&IoStatusBlock,DataToWrite,sizeof(DataToWrite),NULL,NULL))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): Can't WRITE to FILE [%s], STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): DATA WRITTEN to FILE [%s], IO STATUS [%X] !\n",FilePathANSI.Buffer,IoStatusBlock.Status));

		break;
	}

	if (HFile!=NULL)
	{
		// Uzatvorim HANDLE.
		if (NT_SUCCESS(ZwClose(HFile))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
		}
	}

	RtlFreeAnsiString(&FilePathANSI);
}
//-------------------------------------------------------------------------------------------------------
// !!! FUNCTION predpoklada, ze predtym bola zavolana FUNCTION TestWriteFile(), ktora vytvori na DISKU potrebny FILE.
void TestReadFile(void)
{
	NTSTATUS													Status;
	OBJECT_ATTRIBUTES											Attributes;
	UNICODE_STRING												FilePath;
	ANSI_STRING													FilePathANSI;
	CHAR*														Buffer=NULL;

	// !!!!! PREFIX '\\??\\C:' oznacuje DISK 'C:' pomenovany cez MS DOS NAMING CONVENTION. Namiesto toho by sa dala pouzit aj PATH obsahujuca NAZOV DISKU.
	RtlInitUnicodeString(&FilePath,L"\\??\\C:\\MyTest.txt");

	RtlUnicodeStringToAnsiString(&FilePathANSI,&FilePath,TRUE);

	// Inicializuje OBJECT_ATTRIBUTES na FILE PATH.
	// !!! FLAG OBJ_KERNEL_HANDLE je VELMI DOLEZITY, pretoze bez neho by HANDLE bol asociovany s PROCESSOM, v ktoreho THREAD vykonavam tento kod. Pri ukonceni PROCESSU, alebo pouziti THREADU s INEHO PROCESSU by doslo k PADU SYSTEMU.
	InitializeObjectAttributes(&Attributes,&FilePath,OBJ_KERNEL_HANDLE | OBJ_CASE_INSENSITIVE,NULL,NULL);

	HANDLE														HFile=NULL;

	for(;;)
	{
		IO_STATUS_BLOCK											IoStatusBlock;

		// Otvorim FILE pre WRITE.
		if (NT_SUCCESS(Status=ZwCreateFile(&HFile,GENERIC_READ,&Attributes,&IoStatusBlock,NULL,0,FILE_SHARE_READ,FILE_OPEN,FILE_SYNCHRONOUS_IO_NONALERT,NULL,0))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): Can't OPEN FILE [%s], STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): FILE [%s] SUCCESSFULLY OPENED, IO STATUS [%X] !\n",FilePathANSI.Buffer,IoStatusBlock.Status));

		FILE_STANDARD_INFORMATION								FileInfo;

		// Ziskam velkost FILE.
		if (NT_SUCCESS(Status=ZwQueryInformationFile(HFile,&IoStatusBlock,&FileInfo,sizeof(FileInfo),FileStandardInformation))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): Can't GET FILE [%s] INFO DATA, STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		ULONG													FileLength=FileInfo.EndOfFile.LowPart;

		KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): FILE [%s] contains [%d] BYTES, IO STATUS [%X] !\n",FilePathANSI.Buffer,FileLength,IoStatusBlock.Status));

		Buffer=(CHAR*) ExAllocatePool(PagedPool,FileLength);

		// Nacitam DATA z FILE.
		if (NT_SUCCESS(Status=ZwReadFile(HFile,NULL,NULL,NULL,&IoStatusBlock,Buffer,FileLength,NULL,NULL))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): Can't READ to FILE [%s], STATUS [%X], IO STATUS [%X] !\n",FilePathANSI.Buffer,Status,IoStatusBlock.Status));
			break;
		}

		KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): FILE [%s] contains DATA [%s], IO STATUS [%X] !\n",FilePathANSI.Buffer,Buffer,IoStatusBlock.Status));

		break;
	}

	if (HFile!=NULL)
	{
		// Uzatvorim HANDLE.
		if (NT_SUCCESS(ZwClose(HFile))==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION TestFileIOs(): Can't CLOSE HANDLE, STATUS [%X] !\n",Status));
		}
	}

	if (Buffer!=NULL)
	{
		ExFreePool(Buffer);
		Buffer=NULL;
	}

	RtlFreeAnsiString(&FilePathANSI);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Na to, aby LINKER akceptoval FLOATING POINT CALCULATIONS je NUTNE pridat nasledujuci SYMBOL.
extern "C"
{
	int															_fltused=0x9875;
}
//-------------------------------------------------------------------------------------------------------
void TestFloatingPoint(void)
{
	NTSTATUS													Status;
	KFLOATING_SAVE												FloatingState;

	// !!! MUSIM si ULOZIT STATE FLOATING POINT COPROCESSOR.
	if (NT_SUCCESS(Status=KeSaveFloatingPointState(&FloatingState))==false)
	{
		KdPrint((DRIVERNAME " - FUNCTION TestFloatingPoint(): Can't USE FLOATING POINT CALCULATIONS, STATUS [%X] !\n",Status));
	}
	else
	{
		DOUBLE													X=9.6;
		DOUBLE													Y=2.2;
		DOUBLE													Result=X/Y;
		CHAR													Buffer[1000];

		// !!!!! MATEMATICKA OPERACIA KOREKTNE PREBEHNE (skontrolovane cez DEBUGGER), ale KONVERZNA FUNCTIONS RtlStringCbPrintfA() NEPOZNA FLOATING POINT NUMBERS.
		// !!!!! Je to aj OVERENE v KNIHE, kde sa pise, ze konverzne FUNCTIONS NEPODPORUJU FLOATING POINT ESCAPE SEQUENTIONS.
		RtlStringCbPrintfA(Buffer,sizeof(Buffer),"%f/%f=%f",X,Y,Result);

		KdPrint((DRIVERNAME " - FUNCTION TestFloatingPoint(): FLOATING POINT CALCULATION [%s] !\n",Buffer));

		// !!! MUSIM OBNOVIT STATE FLOATING POINT COPROCESSOR.
		KeRestoreFloatingPointState(&FloatingState);
	}
}
//-------------------------------------------------------------------------------------------------------
void DebuggingSupport(void)
{
	// !!! MACRO IDENTIFIER 'DBG' je aktivne IBA pre DEUBG (CHECKED) BUILDS.
#ifdef DBG
	KdPrint((DRIVERNAME " - FUNCTION DebuggingSupport(): DBG MACRO IDENTIFIER is ENABLED !\n"));
#else
	KdPrint((DRIVERNAME " - FUNCTION DebuggingSupport(): DBG MACRO IDENTIFIER is DISABLED !\n"));
#endif

	ASSERT(TRUE);
	KdPrint((DRIVERNAME " - FUNCTION DebuggingSupport(): ASSERT(TRUE) PASSED !\n"));

	ASSERT(FALSE);
	KdPrint((DRIVERNAME " - FUNCTION DebuggingSupport(): ASSERT(FALSE) PASSED !\n"));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryKey)
{
	ANSI_STRING													RegistryKeyANSI;

	RtlUnicodeStringToAnsiString(&RegistryKeyANSI,RegistryKey,TRUE);

	KdPrint((DRIVERNAME " - FUNCTION DriverEntry(): DriverObject [%p], RegistryKey [%s] !\n",DriverObject,RegistryKeyANSI.Buffer));
	
	RtlFreeAnsiString(&RegistryKeyANSI);

	DriverObject->DriverUnload=DriverUnload;
	DriverObject->DriverExtension->AddDevice=AddDevice;

	DriverObject->MajorFunction[IRP_MJ_PNP]=DispatchPNP;
	DriverObject->MajorFunction[IRP_MJ_POWER]=DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL]=DispatchSystemControl;

	return(STATUS_SUCCESS);
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - FUNCTION DriverUnload(): DriverObject [%p] !\n",DriverObject));
}
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT PhysicalDeviceObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - FUNCTION AddDevice(): DriverObject [%p], PhysicalDeviceObject [%p] !\n",DriverObject,PhysicalDeviceObject));

	NTSTATUS													Status;
	PDEVICE_OBJECT												NewDeviceObject=NULL;

	Status=IoCreateDevice(DriverObject,sizeof(DEVICE_EXTENSION),NULL,FILE_DEVICE_UNKNOWN,FILE_DEVICE_SECURE_OPEN,FALSE,&NewDeviceObject);

	if (NT_SUCCESS(Status)==false)
	{
		KdPrint((DRIVERNAME " - FUNCTION AddDevice(): IoCreateDevice() FAILED [%X] !\n",Status));
		return(Status);
	}
	
	PDEVICE_EXTENSION											DeviceExtensionData=(PDEVICE_EXTENSION) NewDeviceObject->DeviceExtension;

	do
	{
		DeviceExtensionData->DeviceObject=NewDeviceObject;
		DeviceExtensionData->PDO=PhysicalDeviceObject;

		DeviceExtensionData->LowerDeviceObject=IoAttachDeviceToDeviceStack(NewDeviceObject,PhysicalDeviceObject);

		if (DeviceExtensionData->LowerDeviceObject==NULL)
		{
			KdPrint((DRIVERNAME " - FUNCTION AddDevice(): IoAttachDeviceToDeviceStack() FAILED !\n"));
			Status=STATUS_DEVICE_REMOVED;
			break;
		}

		NewDeviceObject->Flags|=DO_POWER_PAGABLE;

		Status=IoRegisterDeviceInterface(PhysicalDeviceObject,&GUID_DEVINTERFACE_SIMPLE_PROGRAMMING_TECHNIQUES_DRIVER,NULL,&DeviceExtensionData->InterfaceName);

		if (NT_SUCCESS(Status)==false)
		{
			KdPrint((DRIVERNAME " - FUNCTION AddDevice(): IoRegisterDeviceInterface() FAILED [%X] !\n",Status));
			break;
		}

		IoInitializeRemoveLock(&DeviceExtensionData->RemoveLock,0,0,0);

		NewDeviceObject->Flags&=~DO_DEVICE_INITIALIZING;

		KdPrint((DRIVERNAME " - FUNCTION AddDevice(): DEVICE_OBJECT INITIALIZED, Flags [%X], Characteristics [%X], AlignmentRequirement [%X] !\n",NewDeviceObject->Flags,NewDeviceObject->Characteristics,NewDeviceObject->AlignmentRequirement));

		//TestStatusCodes();
		//TestSEH1();
		//TestSEH2();
		// !!!!! POZOR - sposobi PAD SYSTEMU.
		//TestSEH3();
		//TestSEH4();
		//TestSEH5();
		//TestSEH6();
		// !!!!! Tento CODE sposobuje VYRAZNE SPOMALENIE WINDOWS a vytocenie CPU na testovacom WINDOWS.
		//TestSEH7();
		//TestSEH8();
		//TestSEH9();
		//TestSEH10();
		//TestSEH11();
		// !!!!! Sposobi PAD SYSTEMU.
		//BugCheck();
		//PrintPageMacros();
		//LockUnlockPages();
		//AllocateMemoryFromHeapTest();
		//AllocateNotEnoughMemoryTest1();
		//AllocateNotEnoughMemoryTest2();
		// !!!!! Sposobi PAD SYSTEMU.
		//AllocateNotEnoughMemoryTest3();
		//TestDoublyLinkedList();
		//TestSinglyLinkedList();
		//TestLookasideList();
		//TestNullTerminatedStringFunctions();
		//TestAnsiString1();
		//TestAnsiString2();
		//TestRegistry1(PhysicalDeviceObject);
		//TestRegistry2(&DeviceExtensionData->InterfaceName);
		//TestRegistry3();
		//TestRegistry4();
		//TestWriteFile();
		//TestReadFile();
		//TestFloatingPoint();
		DebuggingSupport();

		// !!!!! Simulacia NEUSPESNEJ incializacie DRIVER.
		// !!!!! Kedze tento DRIVER nie je kompletne implementovany, tak sa vrati UMYSELNE ERROR.
		Status=STATUS_UNSUCCESSFUL;
	}
	while(FALSE);

	if (NT_SUCCESS(Status)==false)
	{
		if (DeviceExtensionData->InterfaceName.Buffer!=NULL)
		{
			RtlFreeUnicodeString(&DeviceExtensionData->InterfaceName);
		}

		if (DeviceExtensionData->LowerDeviceObject!=NULL)
		{
			IoDetachDevice(DeviceExtensionData->LowerDeviceObject);
		}

		if (NewDeviceObject!=NULL)
		{
			IoDeleteDevice(NewDeviceObject);
			NewDeviceObject=NULL;
		}
	}

	return(Status);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchPNP(PDEVICE_OBJECT FDO, PIRP IRP)
{
	PAGED_CODE();
	
	KdPrint((DRIVERNAME " - FUNCTION DispatchPNP(): DeviceObject [%p], IRP [%p] !\n",FDO,IRP));

	return(STATUS_UNSUCCESSFUL);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchPower(PDEVICE_OBJECT FDO, PIRP IRP)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - FUNCTION DispatchPower(): DeviceObject [%p], IRP [%p] !\n",FDO,IRP));

	return(STATUS_UNSUCCESSFUL);
}
//-------------------------------------------------------------------------------------------------------
#pragma PAGEDCODE
NTSTATUS DispatchSystemControl(PDEVICE_OBJECT FDO, PIRP IRP)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - FUNCTION DispatchSystemControl(): DeviceObject [%p], IRP [%p] !\n",FDO,IRP));

	return(STATUS_UNSUCCESSFUL);
}
//-------------------------------------------------------------------------------------------------------