//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
enum class EPoolType : ULONG64
{
//----------------------------------------------------------------------------------------------------------------------
	Paged=POOL_FLAG_PAGED,
	NonPaged=POOL_FLAG_NON_PAGED,
	NonPagedExecute=POOL_FLAG_NON_PAGED_EXECUTE,
	CacheAligned=POOL_FLAG_CACHE_ALIGNED,
	Uninitialized=POOL_FLAG_CACHE_ALIGNED,
	ChargeQuota=POOL_FLAG_USE_QUOTA,
	RaiseOnFailure=POOL_FLAG_RAISE_ON_FAILURE,
	Session=POOL_FLAG_SESSION,
	SpecialPool=POOL_FLAG_SPECIAL_POOL,
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
DEFINE_ENUM_FLAG_OPERATORS(EPoolType);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
void* __cdecl operator new(size_t Size, EPoolType Pool, ULONG Tag);
void* __cdecl operator new[](size_t Size, EPoolType Pool, ULONG Tag);
void* __cdecl operator new(size_t Size, void* Address);
//----------------------------------------------------------------------------------------------------------------------
void __cdecl  operator delete(void* Pointer, size_t Size);
void __cdecl  operator delete[](void* Pointer, size_t Size);
//----------------------------------------------------------------------------------------------------------------------