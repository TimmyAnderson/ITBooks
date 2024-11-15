//----------------------------------------------------------------------------------------------------------------------
#include "KernelHeaders.h"
#include "KernelTemplateLibrary.h"
#include "EPoolType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
#ifdef KTL_TRACK_MEMORY
LONGLONG														TotalAllocated=0;
LONG															AllocationCount=0;
#endif
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void* __cdecl operator new(size_t Size, EPoolType Pool, ULONG Tag)
{
    void*														Pointer=ExAllocatePool2(static_cast<POOL_FLAGS>(Pool),Size,Tag);

#ifdef KTL_TRACK_MEMORY
    DbgPrint(KTL_PREFIX "Allocating [%I64u] bytes from pool [%I64u] with tag [0x%X]: [0x%p].\n",Size,Pool,Tag,Pointer);

	if (Pointer!=nullptr)
	{
        InterlockedIncrement(&AllocationCount);
        InterlockedAdd64(&TotalAllocated,Size);
    }
#endif

    return(Pointer);
}
//----------------------------------------------------------------------------------------------------------------------
void* __cdecl operator new[](size_t Size, EPoolType Pool, ULONG Tag)
{
    void*														Pointer = ExAllocatePool2((POOL_FLAGS)Pool,Size,Tag);

#ifdef KTL_TRACK_MEMORY
    DbgPrint(KTL_PREFIX "Allocating [%I64u] bytes from pool [%I64u] with tag [0x%X]: [0x%p].\n",Size,Pool,Tag,Pointer);

	if (Pointer!=nullptr)
	{
        InterlockedIncrement(&AllocationCount);
        InterlockedAdd64(&TotalAllocated,Size);
    }
#endif

    return(Pointer);
}
//----------------------------------------------------------------------------------------------------------------------
void* __cdecl operator new(size_t Size, void* Address)
{
    UNREFERENCED_PARAMETER(Size);

    return(Address);
}
//----------------------------------------------------------------------------------------------------------------------
void __cdecl operator delete(void* Pointer, size_t Size)
{
	UNREFERENCED_PARAMETER(Size);

    NT_ASSERT(Pointer);

    ExFreePool(Pointer);

#ifdef KTL_TRACK_MEMORY
    DbgPrint(KTL_PREFIX "Freeing [0x%I64X]: [0x%p].\n",Size,Pointer);

	if (InterlockedDecrement(&AllocationCount)<0)
	{
        NT_ASSERT(false);
    }
#endif
}
//----------------------------------------------------------------------------------------------------------------------
void __cdecl operator delete[](void* Pointer, size_t Size)
{
	UNREFERENCED_PARAMETER(Size);

    NT_ASSERT(Pointer);

    ExFreePool(Pointer);

#ifdef KTL_TRACK_MEMORY
    DbgPrint(KTL_PREFIX "Freeing [0x%I64X]: [0x%p].\n",Size,Pointer);

    if (InterlockedDecrement(&AllocationCount)<0)
	{
        NT_ASSERT(false);
    }
#endif
}
//----------------------------------------------------------------------------------------------------------------------