//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Text.h"
//-------------------------------------------------------------------------------------------------------
class CSimpleBaseClass1
{
	private:
		// Unikatne meno VARIABLE v celej dedicskej hierarchii.
		std::wstring											MSimpleBaseClass1Name;

	public:
		virtual void PrintAbstractWithImplementation(void)=0;
		void PrintNonVirtual(void);
		
	public:
		CSimpleBaseClass1(std::wstring Text);
		virtual ~CSimpleBaseClass1(void);
};
//-------------------------------------------------------------------------------------------------------