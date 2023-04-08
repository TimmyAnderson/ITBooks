//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "SimpleBaseClass1.h"
#include "SimpleBaseClass2.h"
//-------------------------------------------------------------------------------------------------------
class CSimpleDerivedClass : public CSimpleBaseClass1, public CSimpleBaseClass2
{
	private:
		// Unikatne meno VARIABLE v celej dedicskej hierarchii.
		std::wstring											MSimpleDerivedClassName;

	public:
		virtual void PrintAbstractWithImplementation(void);
		void PrintNonVirtual(void);

	public:
		CSimpleDerivedClass(std::wstring BaseClass1Name, std::wstring BaseClass2Name, std::wstring SimpleDerivedClassName);
		virtual ~CSimpleDerivedClass(void);
};
//-------------------------------------------------------------------------------------------------------