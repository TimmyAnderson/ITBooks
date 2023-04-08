//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Class1.h"
#include "Class2.h"
//-------------------------------------------------------------------------------------------------------
class CComposedClass
{
	private:
		CClass1													MField1;
		CClass2													MField2;

	public:
		void DoNothing(void);

	public:
		CComposedClass(void);
		CComposedClass(int Dummy);
		virtual ~CComposedClass(void);
};
//-------------------------------------------------------------------------------------------------------