//----------------------------------------------------------------------------------------------------------------------
#include <ntifs.h>
#include <ntddk.h>
#include "MyKernelHelpers.h"
#include "SharedHeader.h"
#include "CRAIIDump.h"
#include "CSimpleStructure.h"
#include "CUniquePointer.h"
#include "TestSystemThreads.h"
#include "TestInterlocked.h"
#include "TestInterlockedLockFree.h"
#include "TestWaitForSingleObject.h"
#include "TestWaitForMultipleObjects.h"
#include "TestMutexes.h"
#include "TestMutexesRecursive.h"
#include "TestMutexesLocker.h"
#include "TestMutexesAbandoned.h"
#include "TestMutexesState.h"
#include "TestFastMutexes.h"
#include "TestSemaphores.h"
#include "TestManualResetEvents.h"
#include "TestAutoResetEvents.h"
#include "TestNamedManualResetEvents.h"
#include "TestNamedAutoResetEvents.h"
#include "TestExecutiveResourcesReadersFirst.h"
#include "TestExecutiveResourcesWritersFirst.h"
#include "TestExecutiveResourcesAutoReadersFirst.h"
#include "TestExecutiveResourcesAutoWritersFirst.h"
#include "TestSpinLocks.h"
#include "TestSpinLocksIRQL.h"
#include "TestQueuedSpinLocks.h"
#include "TestWorkItemsStatic.h"
#include "TestWorkItemsDynamic.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#define IOCTL_TEST_IRQL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_IRQL,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_DPC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_DPC,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_TIMER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_TIMER,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_CRITICAL_REGION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_CRITICAL_REGION,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_GUARDED_REGION CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_GUARDED_REGION,METHOD_BUFFERED,FILE_ANY_ACCESS)
// !!!!! MODE MUSI byt nastaveny na VALUE [METHOD_NEITHER], aby BUFFER NEBOL MAPPED a tak do KERNEL MODE mohol byt zaslany INVALID BUFFER.
#define IOCTL_TEST_SEH_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_1,METHOD_NEITHER,FILE_ANY_ACCESS)
// !!!!! MODE MUSI byt nastaveny na VALUE [METHOD_NEITHER], aby BUFFER NEBOL MAPPED a tak do KERNEL MODE mohol byt zaslany INVALID BUFFER.
#define IOCTL_TEST_SEH_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_2,METHOD_NEITHER,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_3 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_3,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_4 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_4,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_5 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_5,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEH_6 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_SEH_6,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_RAII_1 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_RAII_1,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_RAII_2 CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_RAII_2,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_UNIQUE_POINTER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_TEST_UNIQUE_POINTER,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SYSTEM_CRASH CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SYSTEM_CRASH,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SYSTEM_THREADS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SYSTEM_THREADS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_INTERLOCKED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_INTERLOCKED,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_INTERLOCKED_LOCK_FREE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_INTERLOCKED_LOCK_FREE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WAIT_FOR_SINGLE_OBJECT CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WAIT_FOR_SINGLE_OBJECT,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WAIT_FOR_MULTIPLE_OBJECTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WAIT_FOR_MULTIPLE_OBJECTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_RECURSIVE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_RECURSIVE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_LOCKER CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_LOCKER,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_ABANDONED CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_ABANDONED,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MUTEXES_STATE CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MUTEXES_STATE,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_FAST_MUTEXES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_FAST_MUTEXES,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SEMAPHORES CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SEMAPHORES,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_MANUAL_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_MANUAL_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_AUTO_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_AUTO_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_NAMED_MANUAL_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_NAMED_MANUAL_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_NAMED_AUTO_RESET_EVENTS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_NAMED_AUTO_RESET_EVENTS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_READERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_READERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_WRITERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_WRITERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_READERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_AUTO_READERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_WRITERS_FIRST CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_EXECUTIVE_RESOURCES_AUTO_WRITERS_FIRST,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCKS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SPIN_LOCKS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_SPIN_LOCKS_IRQL CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_SPIN_LOCKS_IRQL,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_QUEUED_SPIN_LOCKS CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_QUEUED_SPIN_LOCKS,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WORK_ITEMS_STATIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WORK_ITEMS_STATIC,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_TEST_WORK_ITEMS_DYNAMIC CTL_CODE(FILE_DEVICE_UNKNOWN,CODE_WORK_ITEMS_DYNAMIC,METHOD_BUFFERED,FILE_ANY_ACCESS)
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
KDPC*															GlobalDpc=nullptr;
KTIMER*															GlobalTimer=nullptr;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
VOID MyDpcRoutine(_KDPC* Dpc, PVOID DeferredContext, PVOID SystemArgument1, PVOID SystemArgument2)
{
	UNREFERENCED_PARAMETER(Dpc);

	const char*													FunctionName=__FUNCTION__;

	KIRQL														CurrentIrql=KeGetCurrentIrql();

	KdPrint(("!!!!!!!!!! DRIVER EXECUTING DPC ROUTINE [%s] !!! CURRENT IRQL [%hhu] DEFERRED CONTEXT [%p] SYSTEM ARGUMENT 1 [%p] SYSTEM ARGUMENT 2 [%p].\n",FunctionName,CurrentIrql,DeferredContext,SystemArgument1,SystemArgument2));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestIrql(void)
{
	KIRQL														CurrentIrql1=KeGetCurrentIrql();
	
	KdPrint(("!!!!! CURRENT IRQL [%hhu] !!!\n",CurrentIrql1));

	KIRQL														OldIrql;

	// !!! Zmeni IRQL.
	OldIrql=KfRaiseIrql(DISPATCH_LEVEL);

	KIRQL														CurrentIrql2=KeGetCurrentIrql();

	KdPrint(("!!!!! CURRENT IRQL [%hhu] OLD IRQL [%hhu] !!!\n",CurrentIrql2,OldIrql));

	// !!! IRQL sa vrati na povodnu uroven.
	KeLowerIrql(OldIrql);

	KIRQL														CurrentIrql3=KeGetCurrentIrql();
	
	KdPrint(("!!!!! CURRENT IRQL [%hhu] !!!\n",CurrentIrql3));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestDpc(void)
{
	// !!! Prida novy REQUEST do DEFERRED PROCEDURE CALLS QUEUE.
	BOOLEAN														Result=KeInsertQueueDpc(GlobalDpc,reinterpret_cast<PVOID>(100),reinterpret_cast<PVOID>(200));

	KdPrint(("!!!!! DPC REQUEST ADDED to DEFERRED PROCEDURE CALLS QUEUE with RESULT [%hhu] !!!\n",Result));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestTimer(void)
{
	constexpr LONGLONG											TIMEOUT_IN_SECONDS=5;

	LARGE_INTEGER												Interval;

	Interval.QuadPart=(-10000000LL*TIMEOUT_IN_SECONDS);

	// !!! Prida novy REQUEST do TIMER QUEUE.
	BOOLEAN														Result=KeSetTimer(GlobalTimer,Interval,GlobalDpc);

	KdPrint(("!!!!! TIMER REQUEST ADDED to TIMER QUEUE with RESULT [%hhu] !!!\n",Result));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestCriticalRegion(void)
{
	KeEnterCriticalRegion();

	KIRQL														CurrentIrql=KeGetCurrentIrql();

	KdPrint(("!!!!!!!!!! DRIVER is INSIDE CRITICAL REGION !!! CURRENT IRQL [%hhu].\n",CurrentIrql));

	KeLeaveCriticalRegion();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestGuardedRegion(void)
{
	KeEnterGuardedRegion();

	KIRQL														CurrentIrql=KeGetCurrentIrql();

	KdPrint(("!!!!!!!!!! DRIVER is INSIDE GUARDED REGION !!! CURRENT IRQL [%hhu].\n",CurrentIrql));

	KeLeaveGuardedRegion();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSeh1(PVOID Buffer, SIZE_T BufferSize)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	wchar_t*													LocalBuffer=(wchar_t*)ExAllocatePool2(POOL_FLAG_NON_PAGED,BufferSize,MY_TAG);

	if (LocalBuffer!=nullptr)
	{
		__try
		{
			wchar_t*											TypedBuffer=reinterpret_cast<wchar_t*>(Buffer);

			// !!!!! Ak CLIENT z USER MODE zasle INVALID BUFFER, tak CODE hodi EXCEPTION.
			RtlCopyMemory(LocalBuffer,TypedBuffer,BufferSize);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - BUFFER [%S].\n",FunctionName,LocalBuffer));
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
		}

		ExFreePoolWithTag(LocalBuffer,MY_TAG);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - DRIVER FAILED to ALLOCATE STRUCTURE [LOCAL BUFFER] !!!\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSeh2(PVOID Buffer, SIZE_T BufferSize)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	wchar_t*													LocalBuffer=(wchar_t*)ExAllocatePool2(POOL_FLAG_NON_PAGED,BufferSize,MY_TAG);

	if (LocalBuffer!=nullptr)
	{
		__try
		{
			wchar_t*											TypedBuffer=reinterpret_cast<wchar_t*>(Buffer);

			// !!!!! Ak CLIENT z USER MODE zasle INVALID BUFFER, tak CODE hodi EXCEPTION.
			RtlCopyMemory(LocalBuffer,TypedBuffer,BufferSize);

			KdPrint(("!!!!!!!!!! ROUTINE [%s] - BUFFER [%S].\n",FunctionName,LocalBuffer));
		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{
			KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
		}

		ExFreePoolWithTag(LocalBuffer,MY_TAG);
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - DRIVER FAILED to ALLOCATE STRUCTURE [LOCAL BUFFER] !!!\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSeh3(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION WILL BE THROWN.\n",FunctionName));

		ExRaiseStatus(STATUS_ACCESS_VIOLATION);
	}
	// !!!!! Ak vznikne EXCEPTION TYPE [STATUS_ACCESS_VIOLATION], tak EXCEPTION sa zachyti.
	__except(((GetExceptionCode()==STATUS_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH))
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InnerSeh4(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION WILL BE THROWN.\n",FunctionName));

		ExRaiseStatus(STATUS_ACCESS_VIOLATION);
	}
	// !!!!! Ak vznikne EXCEPTION TYPE [STATUS_UNSUCCESSFUL], tak EXCEPTION sa zachyti, inak sa pokracuje v hladani EXCEPTION VYSSIE v CALL STACK.
	__except(((GetExceptionCode()==STATUS_UNSUCCESSFUL) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH))
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	// !!!!! Tento CODE sa NEZAVOLA, ak EXCEPTION NIE JE CAUGHT.
	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void TestSeh4(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INNER FUNCTION IS CALLED.\n",FunctionName));

		InnerSeh4();
	}
	// !!!!! Ak vznikne EXCEPTION TYPE [STATUS_ACCESS_VIOLATION], tak EXCEPTION sa zachyti.
	__except(((GetExceptionCode()==STATUS_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH))
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InnerSeh5(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE TRY BLOCK.\n",FunctionName));

		//ExRaiseStatus(STATUS_ACCESS_VIOLATION);
	}
	__finally
	{
		// !!!!! Tento CODE sa ZAVOLA bez ohladu na to ci vznikne EXCEPTION.
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE FINALLY BLOCK.\n",FunctionName));
	}

	// !!!!! Tento CODE sa NEZAVOLA, ak vznikne EXCEPTION.
	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void TestSeh5(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INNER FUNCTION IS CALLED.\n",FunctionName));

		InnerSeh5();
	}
	// !!!!! Ak vznikne EXCEPTION TYPE [STATUS_ACCESS_VIOLATION], tak EXCEPTION sa zachyti.
	__except(((GetExceptionCode()==STATUS_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH))
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InnerSeh6(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE TRY BLOCK.\n",FunctionName));

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION WILL BE THROWN.\n",FunctionName));

		ExRaiseStatus(STATUS_ACCESS_VIOLATION);
	}
	__finally
	{
		// !!!!! Tento CODE sa ZAVOLA bez ohladu na to ci vznikne EXCEPTION.
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE FINALLY BLOCK.\n",FunctionName));
	}

	// !!!!! Tento CODE sa NEZAVOLA, ak vznikne EXCEPTION.
	//KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void TestSeh6(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INNER FUNCTION IS CALLED.\n",FunctionName));

		InnerSeh6();
	}
	// !!!!! Ak vznikne EXCEPTION TYPE [STATUS_ACCESS_VIOLATION], tak EXCEPTION sa zachyti.
	__except(((GetExceptionCode()==STATUS_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH))
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InnerRAII1(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		// !!! V CONSTRUCTOR a DESTRUCTOR sa vypisuje text do LOGU.
		CRAIIDump												Object;

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE TRY BLOCK.\n",FunctionName));

		//ExRaiseStatus(STATUS_ACCESS_VIOLATION);
	}
	__finally
	{
		// !!!!! Tento CODE sa ZAVOLA bez ohladu na to ci vznikne EXCEPTION.
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE FINALLY BLOCK.\n",FunctionName));
	}

	// !!!!! Tento CODE sa NEZAVOLA, ak vznikne EXCEPTION.
	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void TestRAII1(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INNER FUNCTION IS CALLED.\n",FunctionName));

		InnerRAII1();
	}
	// !!!!! Ak vznikne EXCEPTION TYPE [STATUS_ACCESS_VIOLATION], tak EXCEPTION sa zachyti.
	__except(((GetExceptionCode()==STATUS_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH))
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void InnerRAII2(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		// !!! V CONSTRUCTOR a DESTRUCTOR sa vypisuje text do LOGU.
		// !!!!! Pri vzniku EXCEPTION sa DESTRUCTOR NEVYVOLA, pretoze v KERNEL MODE nie je aktivny C++ RUNTIME.
		CRAIIDump												Object;

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE TRY BLOCK.\n",FunctionName));

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION WILL BE THROWN.\n",FunctionName));

		ExRaiseStatus(STATUS_ACCESS_VIOLATION);
	}
	__finally
	{
		// !!!!! Tento CODE sa ZAVOLA bez ohladu na to ci vznikne EXCEPTION.
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INSIDE FINALLY BLOCK.\n",FunctionName));
	}

	// !!!!! Tento CODE sa NEZAVOLA, ak vznikne EXCEPTION.
	//KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
void TestRAII2(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	__try
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - INNER FUNCTION IS CALLED.\n",FunctionName));

		InnerRAII2();
	}
	// !!!!! Ak vznikne EXCEPTION TYPE [STATUS_ACCESS_VIOLATION], tak EXCEPTION sa zachyti.
	__except(((GetExceptionCode()==STATUS_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH))
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] - EXCEPTION CAUGHT.\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestUniquePointer(void)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - START.\n",FunctionName));

	CSimpleStructure*											Buffer=(CSimpleStructure*)ExAllocatePool2(POOL_FLAG_NON_PAGED,sizeof(CSimpleStructure),MY_TAG);

	if (Buffer!=nullptr)
	{
		// !!!!! MEMORY sa AUTOMATICKY uvolni v DESTRUCTOR.
		CUniquePointer<CSimpleStructure>						Object(Buffer);

		Object->Value1=100;
		Object->Value2=123456789;

		KdPrint(("!!!!!!!!!! ROUTINE [%s] - STRUCTURE [CSimpleStructure] - VALUE 1 [%hd] VALUE 2 [%ld].\n",FunctionName,Object->Value1,Object->Value2));
	}
	else
	{
		KdPrint(("!!!!!!!!!! ROUTINE [%s] FAILED to ALLOCATE STRUCTURE [CSimpleStructure] !!!\n",FunctionName));
	}

	KdPrint(("!!!!!!!!!! ROUTINE [%s] - END.\n",FunctionName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void TestSystemCrash(void)
{
	// !!!!! CODE sposobi SYSTEM CRASH.
	KeBugCheckEx(MANUALLY_INITIATED_CRASH1,0x10,0x20,0x30,0x40);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineCreate(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	Irp->IoStatus.Status=STATUS_SUCCESS;
	Irp->IoStatus.Information=0;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineClose(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	UNREFERENCED_PARAMETER(DeviceObject);

	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	Irp->IoStatus.Status=STATUS_SUCCESS;
	Irp->IoStatus.Information=0;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
NTSTATUS DispatchRoutineDeviceControl(DEVICE_OBJECT* DeviceObject, IRP* Irp)
{
	const char*													FunctionName=__FUNCTION__;

	KdPrint(("!!!!! DRIVER EXECUTING DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	NTSTATUS													Status=STATUS_SUCCESS;
	ULONG_PTR													Information=0;
	
	// !!! FUNCTION vrati CURRENT STACK LOCATION.
	IO_STACK_LOCATION*											CurrentStackLocation=IoGetCurrentIrpStackLocation(Irp);
	ULONG														Code=CurrentStackLocation->Parameters.DeviceIoControl.IoControlCode;
	ULONG														InputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.InputBufferLength;
	ULONG														OutputBufferLength=CurrentStackLocation->Parameters.DeviceIoControl.OutputBufferLength;
	
	KdPrint(("!!!!! CODE [%lu] INPUT BUFFER LENGTH [%lu] OUTPUT BUFFER LENGTH [%lu] !!!\n",Code,InputBufferLength,OutputBufferLength));

	switch(Code)
	{
		case IOCTL_TEST_IRQL:
		{
			TestIrql();
		}
		break;

		case IOCTL_TEST_DPC:
		{
			TestDpc();
		}
		break;

		case IOCTL_TEST_TIMER:
		{
			TestTimer();
		}
		break;

		case IOCTL_TEST_CRITICAL_REGION:
		{
			TestCriticalRegion();
		}
		break;

		case IOCTL_TEST_GUARDED_REGION:
		{
			TestGuardedRegion();
		}
		break;

		case IOCTL_TEST_SEH_1:
		{
			TestSeh1(CurrentStackLocation->Parameters.DeviceIoControl.Type3InputBuffer,InputBufferLength);
		}
		break;

		case IOCTL_TEST_SEH_2:
		{
			TestSeh2(CurrentStackLocation->Parameters.DeviceIoControl.Type3InputBuffer,InputBufferLength);
		}
		break;

		case IOCTL_TEST_SEH_3:
		{
			TestSeh3();
		}
		break;

		case IOCTL_TEST_SEH_4:
		{
			TestSeh4();
		}
		break;

		case IOCTL_TEST_SEH_5:
		{
			TestSeh5();
		}
		break;

		case IOCTL_TEST_SEH_6:
		{
			TestSeh6();
		}
		break;

		case IOCTL_TEST_RAII_1:
		{
			TestRAII1();
		}
		break;

		case IOCTL_TEST_RAII_2:
		{
			TestRAII2();
		}
		break;

		case IOCTL_TEST_UNIQUE_POINTER:
		{
			TestUniquePointer();
		}
		break;

		case IOCTL_TEST_SYSTEM_CRASH:
		{
			TestSystemCrash();
		}
		break;

		case IOCTL_TEST_SYSTEM_THREADS:
		{
			TestSystemThreads();
		}
		break;

		case IOCTL_TEST_INTERLOCKED:
		{
			TestInterlocked();
		}
		break;

		case IOCTL_TEST_INTERLOCKED_LOCK_FREE:
		{
			TestInterlockedLockFree();
		}
		break;

		case IOCTL_TEST_WAIT_FOR_SINGLE_OBJECT:
		{
			TestWaitForSingleObject();
		}
		break;

		case IOCTL_TEST_WAIT_FOR_MULTIPLE_OBJECTS:
		{
			TestWaitForMultipleObjects();
		}
		break;

		case IOCTL_TEST_MUTEXES:
		{
			TestMutexes();
		}
		break;

		case IOCTL_TEST_MUTEXES_RECURSIVE:
		{
			TestMutexesRecursive();
		}
		break;

		case IOCTL_TEST_MUTEXES_LOCKER:
		{
			TestMutexesLocker();
		}
		break;

		case IOCTL_TEST_MUTEXES_ABANDONED:
		{
			TestMutexesAbandoned();
		}
		break;

		case IOCTL_TEST_MUTEXES_STATE:
		{
			TestMutexesState();
		}
		break;

		case IOCTL_TEST_FAST_MUTEXES:
		{
			TestFastMutexes();
		}
		break;

		case IOCTL_TEST_SEMAPHORES:
		{
			TestSemaphores();
		}
		break;

		case IOCTL_TEST_MANUAL_RESET_EVENTS:
		{
			TestManualResetEvents();
		}
		break;

		case IOCTL_TEST_AUTO_RESET_EVENTS:
		{
			TestAutoResetEvents();
		}
		break;

		case IOCTL_TEST_NAMED_MANUAL_RESET_EVENTS:
		{
			TestNamedManualResetEvents();
		}
		break;

		case IOCTL_TEST_NAMED_AUTO_RESET_EVENTS:
		{
			TestNamedAutoResetEvents();
		}
		break;

		case IOCTL_TEST_EXECUTIVE_RESOURCES_READERS_FIRST:
		{
			TestExecutiveResourcesReadersFirst();
		}
		break;

		case IOCTL_TEST_EXECUTIVE_RESOURCES_WRITERS_FIRST:
		{
			TestExecutiveResourcesWritersFirst();
		}
		break;

		case IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_READERS_FIRST:
		{
			TestExecutiveResourcesAutoReadersFirst();
		}
		break;

		case IOCTL_TEST_EXECUTIVE_RESOURCES_AUTO_WRITERS_FIRST:
		{
			TestExecutiveResourcesAutoWritersFirst();
		}
		break;

		case IOCTL_TEST_SPIN_LOCKS:
		{
			TestSpinLocks();
		}
		break;

		case IOCTL_TEST_SPIN_LOCKS_IRQL:
		{
			TestSpinLocksIRQL();
		}
		break;

		case IOCTL_TEST_QUEUED_SPIN_LOCKS:
		{
			TestQueuedSpinLocks();
		}
		break;

		case IOCTL_TEST_WORK_ITEMS_STATIC:
		{
			TestWorkItemsStatic(DeviceObject);
		}
		break;

		case IOCTL_TEST_WORK_ITEMS_DYNAMIC:
		{
			TestWorkItemsDynamic(DeviceObject);
		}
		break;

		default:
		{
			Status=STATUS_INVALID_DEVICE_REQUEST;
		}
		break;
	}

	Irp->IoStatus.Status=Status;
	Irp->IoStatus.Information=Information;

	// !!! FUNCTION ukonci IRP.
	IofCompleteRequest(Irp,IO_NO_INCREMENT);

	KdPrint(("!!!!! DRIVER EXECUTED DISPATCH ROUTINE [%s] !!!\n",FunctionName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void FunctionDriverUnload(PDRIVER_OBJECT DriverObject)
{
	KdPrint(("!!!!! DRIVER [%wZ] STOPPING !!!\n",DriverObject->DriverName));

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\KernelMechanisms");

	// !!! Z TIMER QUEUE sa odstrani OBJECT [KTIMER].
	BOOLEAN														Result1=KeCancelTimer(GlobalTimer);

	KdPrint(("!!!!! DRIVER [%wZ] CANCELLED TIMER with RESULT [%hhu] !!!\n",DriverObject->DriverName,Result1));

	// !!! Z DEFERRED PROCEDURE CALLS QUEUE sa odstrani OBJECT [KDPC].
	BOOLEAN														Result2=KeRemoveQueueDpc(GlobalDpc);

	KdPrint(("!!!!! DRIVER [%wZ] CANCELLED DPC with RESULT [%hhu] !!!\n",DriverObject->DriverName,Result2));

	ExFreePoolWithTag(GlobalTimer,MY_TAG);

	ExFreePoolWithTag(GlobalDpc,MY_TAG);

	IoDeleteSymbolicLink(&SymbolicLink);

	IoDeleteDevice(DriverObject->DeviceObject);

	KdPrint(("!!!!! DRIVER [%wZ] STOPPED !!!\n",DriverObject->DriverName));
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(RegistryPath);

	KdPrint(("!!!!! DRIVER [%wZ] STARTING !!!\n",DriverObject->DriverName));

	DriverObject->DriverUnload=FunctionDriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE]=DispatchRoutineCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]=DispatchRoutineClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]=DispatchRoutineDeviceControl;

	UNICODE_STRING												DeviceName;

	// !!! DEVICE NAME by mal mat PREFIX [\Device].
	RtlInitUnicodeString(&DeviceName,L"\\Device\\KernelMechanisms");

	PDEVICE_OBJECT												DeviceObject;

	NTSTATUS													Status1=IoCreateDevice(DriverObject,0,&DeviceName,FILE_DEVICE_UNKNOWN,0,FALSE,&DeviceObject);

	if (NT_SUCCESS(Status1)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE DEVICE OBJECT with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status1));
		return(Status1);
	}

	UNICODE_STRING												SymbolicLink;
		
	RtlInitUnicodeString(&SymbolicLink,L"\\??\\KernelMechanisms");

	NTSTATUS													Status2=IoCreateSymbolicLink(&SymbolicLink,&DeviceName);

	if (NT_SUCCESS(Status2)==false)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to CREATE SYMBOLIC LINK with ERROR CODE [%lX] !!!\n",DriverObject->DriverName,Status2));

		IoDeleteDevice(DeviceObject);
		return(Status2);
	}

	// !!! Alokuje sa MEMORY pre OBJECT [KDPC]. MUSI byt v NON-PAGED MEMORY.
	GlobalDpc=(KDPC*)ExAllocatePool2(POOL_FLAG_NON_PAGED,sizeof(KDPC),MY_TAG);

	if (GlobalDpc==nullptr)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to ALLOCATE STRUCTURE [KDPC] !!!\n",DriverObject->DriverName));

		IoDeleteSymbolicLink(&SymbolicLink);

		IoDeleteDevice(DeviceObject);

		return(STATUS_INSUFFICIENT_RESOURCES);
	}

	// !!! Alokuje sa MEMORY pre OBJECT [KTIMER]. MUSI byt v NON-PAGED MEMORY.
	GlobalTimer=(KTIMER*)ExAllocatePool2(POOL_FLAG_NON_PAGED,sizeof(KTIMER),MY_TAG);

	if (GlobalTimer==nullptr)
	{
		KdPrint(("!!!!! DRIVER [%wZ] FAILED to ALLOCATE STRUCTURE [KTIMER] !!!\n",DriverObject->DriverName));

		ExFreePoolWithTag(GlobalDpc,MY_TAG);

		IoDeleteSymbolicLink(&SymbolicLink);

		IoDeleteDevice(DeviceObject);

		return(STATUS_INSUFFICIENT_RESOURCES);
	}

	// !!! Inicializuje sa DPC.
	KeInitializeDpc(GlobalDpc,MyDpcRoutine,nullptr);

	// !!! Inicializuje sa TIMER.
	KeInitializeTimer(GlobalTimer);

	KdPrint(("!!!!! DRIVER [%wZ] STARTED !!!\n",DriverObject->DriverName));

	return(STATUS_SUCCESS);
}
//----------------------------------------------------------------------------------------------------------------------