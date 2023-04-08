//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "ClassA.h"
#include "ClassB.h"
//-------------------------------------------------------------------------------------------------------
class CComplexClass
{
	private:
		// !!! V CONSTRUCTORS tychto FIELDS moze dojst k hodeniu EXCEPTION.
		CClassA													MClassA;
		CClassB													MClassB;

	public:
		void DoNothing(void);

	public:
		CComplexClass(bool ThrowExceptionInClassA, bool ThrowExceptionInClassB, bool ThrowExceptionInComplexClass);
		CComplexClass(bool ThrowExceptionInClassA, bool ThrowExceptionInClassB, bool ThrowExceptionInComplexClass, bool Dummy);
		virtual ~CComplexClass(void);
};
//-------------------------------------------------------------------------------------------------------