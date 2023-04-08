//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Text.h"
#include "BaseClass1.h"
#include "BaseClass2.h"
//-------------------------------------------------------------------------------------------------------
class CDerivedClass : public CBaseClass1, public CBaseClass2
{
	private:
		// Unikatne meno VARIABLE v celej dedicskej hierarchii.
		CText													MDerivedClassName;

	public:
		virtual void PrintAbstractWithImplementation(void);
		void PrintNonVirtual(void);

	public:
		CDerivedClass(CText& BaseClass1Name, CText& BaseClass2Name, CText& DerivedClassName);
		virtual ~CDerivedClass(void);
};
//-------------------------------------------------------------------------------------------------------