//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Int.h"
//-------------------------------------------------------------------------------------------------------
class CPointerToClassDereferencing
{
	private:
		// !!! Vracia POINTER na CLASS.
		CInt*													MPointer;

	public:
		CInt* operator->(void);

	public:
		CPointerToClassDereferencing(CInt* Pointer);
		virtual ~CPointerToClassDereferencing(void);
};
//-------------------------------------------------------------------------------------------------------