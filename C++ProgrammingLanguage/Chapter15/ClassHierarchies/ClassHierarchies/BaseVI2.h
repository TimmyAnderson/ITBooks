//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "BaseVI.h"
//-------------------------------------------------------------------------------------------------------
// !!! Pouziva sa VIRTUAL INHERITANCE.
class CBaseVI2 : public virtual CBaseVI
{
	public:
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual1(void);
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual2(void);
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual3(void);

	public:
		CBaseVI2(std::wstring SharedName);
		virtual ~CBaseVI2(void);
};
//-------------------------------------------------------------------------------------------------------