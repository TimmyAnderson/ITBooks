//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "Base1.h"
#include "Base2.h"
//-------------------------------------------------------------------------------------------------------
// !!! Nepouziva sa VIRTUALNA INHERITANCE.
class CNonVirtualDerived : public CBase1, public CBase2
{
	private:
		std::wstring											MSharedName;

	public:
		virtual void Overrided(void);

	public:
		// !!!!! Specialna SYNTAX - USING DECLARATION - umoznujuca pouzitie OVERLOADED VERZII METHODS Ambiguity2() z CBase1 a CBase2. Bez pouzitia USING by boli metody CBase1::Ambiguity2(int) a CBase2::Ambiguity2(double) boli NEPRISTUPNE a NAMIESTO NICH by sa volala metoda CNonVirtualDerived::Ambiguity2(wchar_t).
		using CBase1::Ambiguity2;
		using CBase2::Ambiguity2;

	public:
		virtual void Ambiguity1(wchar_t Value);
		virtual void Ambiguity2(wchar_t Value);

	public:
		// Metoda je pretazena v CBase1, CBase2 a CBase3.
		virtual void Virtual3(void);

	public:
		CNonVirtualDerived(std::wstring SharedNameClass1, std::wstring SharedNameClass2, std::wstring SharedNameDerived);
		virtual ~CNonVirtualDerived(void);
};
//-------------------------------------------------------------------------------------------------------