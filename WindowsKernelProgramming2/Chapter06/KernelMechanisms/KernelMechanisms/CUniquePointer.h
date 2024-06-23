//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
#include "MyKernelHelpers.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType=void>
struct CUniquePointer
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType*													MPointer;

	public:
		operator bool(void) const
		{
			bool												Result=(MPointer!=nullptr);

			return(Result);
		}

		TType* operator->(void) const
		{
			return(MPointer);
		}

		TType& operator*(void) const
		{
			return(*MPointer);
		}

		CUniquePointer& operator=(const CUniquePointer&)=delete;

	private:
		void Release(void)
		{
			if (MPointer!=nullptr)
			{
				ExFreePoolWithTag(MPointer,MY_TAG);
				MPointer=nullptr;
			}
		}

	public:
		explicit CUniquePointer(TType* Pointer=nullptr)
			: MPointer(Pointer)
		{
		}

		CUniquePointer(const CUniquePointer&) = delete;

		CUniquePointer(CUniquePointer&& Other)
			: MPointer(Other.MPointer)
		{
			Other.MPointer=nullptr;
		}
		
		CUniquePointer& operator=(CUniquePointer&& Other)
		{
			if (&Other!=this)
			{
				Release();

				MPointer=Other.MPointer;
				Other.MPointer=nullptr;
			}

			return(*this);
		}

		~CUniquePointer(void)
		{
			Release();
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------