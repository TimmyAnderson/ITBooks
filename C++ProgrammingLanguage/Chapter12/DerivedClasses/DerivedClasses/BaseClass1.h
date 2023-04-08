//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Text.h"
//-------------------------------------------------------------------------------------------------------
class CBaseClass1
{
	private:
		// Unikatne meno VARIABLE v celej dedicskej hierarchii.
		CText													MBaseClass1Name;

	public:
		virtual void PrintAbstractWithImplementation(void)=0;
		void PrintNonVirtual(void);
		
	public:
		CBaseClass1(CText& Text);
		virtual ~CBaseClass1(void);
};
//-------------------------------------------------------------------------------------------------------