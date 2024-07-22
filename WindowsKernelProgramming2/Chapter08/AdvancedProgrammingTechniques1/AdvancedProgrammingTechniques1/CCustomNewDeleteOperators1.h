//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <ntddk.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CCustomNewDeleteOperators1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		SHORT													MValue1;
		LONG													MValue2;

	public:
		// !!! Je to PLACEMENT OPERATOR NEW, ktory vsak NEALOKUJE MEMORY, pretoze ta je akolovana EXTERNE.
		void* operator new(size_t Size, void* Buffer);

	public:
		// !!! Je to OPERATOR DELETE, ktory vsak NEDEALOKUJE MEMORY, pretoze ta je akolovana EXTERNE.
		void operator delete(void* Buffer);

	public:
		SHORT GetValue1(void) const noexcept;
		LONG GetValue2(void) const noexcept;

	public:
		CCustomNewDeleteOperators1(void);
		CCustomNewDeleteOperators1(SHORT Value1, LONG Value2);
		~CCustomNewDeleteOperators1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------