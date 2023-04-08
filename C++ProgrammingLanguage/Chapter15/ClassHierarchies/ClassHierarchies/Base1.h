//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "Base.h"
//-------------------------------------------------------------------------------------------------------
class CBase1 : public CBase
{
	private:
		std::wstring											MSharedName;

	public:
		virtual void NotOverrided(void);
		virtual void Overrided(void);

	public:
		virtual void Ambiguity1(int Value);
		virtual void Ambiguity2(int Value);

	public:
		// Metoda je pretazena v CBase1 a CBase2.
		virtual void Virtual2(void);
		// Metoda je pretazena v CBase1, CBase2 a CBase3.
		virtual void Virtual3(void);

	public:
		CBase1(std::wstring SharedName);
		virtual ~CBase1(void);
};
//-------------------------------------------------------------------------------------------------------