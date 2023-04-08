//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "Base.h"
//-------------------------------------------------------------------------------------------------------
class CBase2 : public CBase
{
	private:
		std::wstring											MSharedName;

	public:
		virtual void NotOverrided(void);
		virtual void Overrided(void);

	public:
		virtual void Ambiguity1(double Value);
		virtual void Ambiguity2(double Value);

	public:
		// Metoda je pretazena v CBase2.
		virtual void Virtual1(void);
		// Metoda je pretazena v CBase1 a CBase2.
		virtual void Virtual2(void);
		// Metoda je pretazena v CBase1, CBase2 a CBase3.
		virtual void Virtual3(void);

	public:
		CBase2(std::wstring SharedName);
		virtual ~CBase2(void);
};
//-------------------------------------------------------------------------------------------------------