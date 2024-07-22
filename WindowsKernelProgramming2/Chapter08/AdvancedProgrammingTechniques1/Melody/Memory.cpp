//----------------------------------------------------------------------------------------------------------------------
#include "Memory.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void* operator new(size_t Size, POOL_FLAGS Pool, ULONG Tag)
{
    void*														Buffer=ExAllocatePool2(Pool,Size,Tag);

    return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
void* operator new(size_t Size, POOL_FLAGS Pool, EX_POOL_PRIORITY Priority, ULONG Tag)
{
    POOL_EXTENDED_PARAMETER										ExtendedParameter;

    ExtendedParameter.Type=PoolExtendedParameterPriority;
    ExtendedParameter.Priority=Priority;

	void*														Buffer=ExAllocatePool3(Pool,Size,Tag,&ExtendedParameter,1);

    return(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
void operator delete(void* Buffer, size_t)
{
    ExFreePool(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------
void operator delete(void* Buffer, size_t, std::align_val_t)
{
    ExFreePool(Buffer);
}
//----------------------------------------------------------------------------------------------------------------------