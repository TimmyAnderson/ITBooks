//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CBase
{
	private:
		std::wstring											MCBaseSharedName;

	public:
		void PrintCBaseSharedName(void);

	public:
		// Metoda je pretazena v CBase2.
		virtual void Virtual1(void);
		// Metoda je pretazena v CBase1 a CBase2.
		virtual void Virtual2(void);
		// Metoda je pretazena v CBase1, CBase2 a CBase3.
		virtual void Virtual3(void);

	public:
		CBase(std::wstring SharedName);
		virtual ~CBase(void);
};
//-------------------------------------------------------------------------------------------------------