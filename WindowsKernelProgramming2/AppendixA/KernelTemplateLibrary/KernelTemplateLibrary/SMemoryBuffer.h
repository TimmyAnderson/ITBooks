//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "KernelHeaders.h"
#include "EPoolType.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType POOL=EPoolType::NonPaged, typename TType=UCHAR>
struct SMemoryBuffer final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType*													MBuffer;
		ULONG													MSize;

	public:
		SMemoryBuffer& operator=(const SMemoryBuffer&& Other);
		operator bool(void) const;

	private:
		void Free(void) noexcept;

	public:
		ULONG Size(void) const;
		ULONG SizeInBytes(void) const;
		TType* Get(void) const;

	public:
		SMemoryBuffer(ULONG Size, ULONG Tag);
		SMemoryBuffer(const SMemoryBuffer&)=delete;
		SMemoryBuffer& operator=(const SMemoryBuffer&)=delete;
		SMemoryBuffer(const SMemoryBuffer&& Other);
		~SMemoryBuffer(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType POOL, typename TType>
SMemoryBuffer<POOL,TType>::SMemoryBuffer(ULONG Size, ULONG Tag)
	: MBuffer(nullptr), MSize(Size)
{
	MBuffer=(TType*)ExAllocatePool2((POOL_FLAGS)POOL,Size*sizeof(TType),Tag);
}
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType POOL, typename TType>
SMemoryBuffer<POOL,TType>::SMemoryBuffer(const SMemoryBuffer&& Other)
	: MBuffer(Other.MBuffer), MSize(Other.MSize)
{
	Other.MBuffer=nullptr;
}
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType Pool, typename TType>
SMemoryBuffer<Pool,TType>::~SMemoryBuffer(void) noexcept
{
	Free();
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType Pool, typename TType>
SMemoryBuffer<Pool,TType>& SMemoryBuffer<Pool,TType>::operator=(const SMemoryBuffer&& Other)
{
	if (&Other!=this)
	{
		Free();

		MBuffer=Other.MBuffer;
		MSize=Other.MSize;

		Other.MBuffer=nullptr;
	}

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType Pool, typename TType>
SMemoryBuffer<Pool,TType>::operator bool(void) const
{
	bool														Result=(MBuffer!=nullptr);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType Pool, typename TType>
void SMemoryBuffer<Pool,TType>::Free(void) noexcept
{
	if (MBuffer!=nullptr)
	{
		ExFreePool(MBuffer);
		MBuffer=nullptr;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType Pool, typename TType>
ULONG SMemoryBuffer<Pool,TType>::Size(void) const
{
	return(MSize);
}
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType Pool, typename TType>
ULONG SMemoryBuffer<Pool,TType>::SizeInBytes(void) const
{
	ULONG														Result=(MSize*sizeof(TType));

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
template<EPoolType Pool, typename TType>
TType* SMemoryBuffer<Pool,TType>::Get(void) const
{
	return(MBuffer);
}
//----------------------------------------------------------------------------------------------------------------------