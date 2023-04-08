//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "PointerToClassDereferencing.h"
//-------------------------------------------------------------------------------------------------------
class CClassDereferencing
{
	private:
		// !!! Vracia CLASS, ktory ma PRETAZENY OPERATOR->().
		CPointerToClassDereferencing							MObject;

	public:
		CPointerToClassDereferencing operator->(void);

	public:
		CClassDereferencing(CPointerToClassDereferencing Object);
		virtual ~CClassDereferencing(void);
};
//-------------------------------------------------------------------------------------------------------