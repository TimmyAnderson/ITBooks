//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CBaseVI
{
	protected:
		std::wstring											MSharedName;

	public:
		void PrintSharedName(void);

	public:
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual1(void);
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual2(void);
		// Metoda je pretazena v CBaseVI1, CBaseVI2 a CVirtualDerivedVI.
		virtual void Virtual3(void);

	public:
		CBaseVI(std::wstring SharedName);
		virtual ~CBaseVI(void);
};
//-------------------------------------------------------------------------------------------------------