//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "BaseVI.h"
//-------------------------------------------------------------------------------------------------------
// !!! Pouziva sa VIRTUAL INHERITANCE.
class CBaseVI1 : public virtual CBaseVI
{
	public:
		// !!!!! Kedze sa pouziva VIRTUAL INHERITANCE, tak MUSI sa pretazit aj metoda Virtual1(), kedze v CBaseVI2 je TIEZ PRETAZENA.
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual1(void);

		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual2(void);
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual3(void);

	public:
		CBaseVI1(std::wstring SharedName);
		virtual ~CBaseVI1(void);
};
//-------------------------------------------------------------------------------------------------------