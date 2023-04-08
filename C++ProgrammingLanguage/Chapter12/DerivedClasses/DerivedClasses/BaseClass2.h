//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "Text.h"
//-------------------------------------------------------------------------------------------------------
class CBaseClass2
{
	private:
		// Unikatne meno VARIABLE v celej dedicskej hierarchii.
		CText													MBaseClass2Name;

	public:
		virtual void PrintAbstractWithImplementation(void)=0;
		void PrintNonVirtual(void);

	public:
		CBaseClass2(CText& Text);
		virtual ~CBaseClass2(void);
};
//-------------------------------------------------------------------------------------------------------