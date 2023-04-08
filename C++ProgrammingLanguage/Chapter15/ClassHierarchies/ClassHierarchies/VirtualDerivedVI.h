//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "BaseVI1.h"
#include "BaseVI2.h"
//-------------------------------------------------------------------------------------------------------
// !!! Pouziva sa VIRTUALNA INHERITANCE medzi CBaseVI1 a CBaseVI a CBaseVI2 a CBaseVI.
class CVirtualDerivedVI : public CBaseVI1, public CBaseVI2
{
	public:
		// !!!!! Kedze sa pouziva VIRTUAL INHERITANCE, tak MUSI sa pretazit aj metoda Virtual1(), kedze v CBaseVI1 a CBaseVI2 je TIEZ PRETAZENA.
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual1(void);
		// !!!!! Kedze sa pouziva VIRTUAL INHERITANCE, tak MUSI sa pretazit aj metoda Virtual2(), kedze v CBaseVI1 a CBaseVI2 je TIEZ PRETAZENA.
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual2(void);


		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual3(void);

	public:
		CVirtualDerivedVI(std::wstring SharedNameClass1, std::wstring SharedNameClass2, std::wstring SharedNameDerived);
		virtual ~CVirtualDerivedVI(void);
};
//-------------------------------------------------------------------------------------------------------