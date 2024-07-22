//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCustomNewDeleteOperators2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		SHORT													MValue1;
		LONG													MValue2;

	public:
		// !!! CUSTOM C++ OPERATOR [OPERATOR new], ktory umoznuje alokovat MEMORY z KERNEL POOL.
		// !!! Je to PLACEMENT OPERATOR NEW, ktory ALOKUJE MEMORY z KERNEL POOL.
		void* operator new(size_t Size, POOL_FLAGS Pool, ULONG Tag);

	public:
		// !!! CUSTOM C++ OPERATOR [OPERATOR new], ktory umoznuje dealokovat MEMORY z KERNEL POOL.
		// !!! Je to OPERATOR DELETE, ktory DEALOKUJE MEMORY z KERNEL POOL.
		void operator delete(void* Buffer);

	public:
		SHORT GetValue1(void) const noexcept;
		LONG GetValue2(void) const noexcept;

	public:
		CCustomNewDeleteOperators2(void);
		CCustomNewDeleteOperators2(SHORT Value1, LONG Value2);
		~CCustomNewDeleteOperators2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------