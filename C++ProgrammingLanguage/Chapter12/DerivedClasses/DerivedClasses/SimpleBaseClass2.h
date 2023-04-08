//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Text.h"
//-------------------------------------------------------------------------------------------------------
class CSimpleBaseClass2
{
	private:
		// Unikatne meno VARIABLE v celej dedicskej hierarchii.
		std::wstring											MSimpleBaseClass2Name;

	public:
		virtual void PrintAbstractWithImplementation(void)=0;
		void PrintNonVirtual(void);

	public:
		CSimpleBaseClass2(std::wstring Text);
		virtual ~CSimpleBaseClass2(void);
};
//-------------------------------------------------------------------------------------------------------