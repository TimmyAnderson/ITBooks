//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CGlobalNewDeleteBase1.h"
#include "CGlobalNewDeleteBase2.h"
//-------------------------------------------------------------------------------------------------------
class CGlobalNewDeleteDerived : public CGlobalNewDeleteBase1, public CGlobalNewDeleteBase2
{
//-----------------------------------------------------------------------------
	protected:
		int														MDummyDerivedA;
		int														MDummyDerivedB;
		int														MDummyDerivedC;
		int														MDummyDerivedD;

	public:
		int GetDummyBase1A(void) const noexcept
		{
			return(MDummyBase1A);
		}

		void SetDummyBase1A(int Value)
		{
			MDummyBase1A=Value;
		}

		int GetDummyBase1B(void) const noexcept
		{
			return(MDummyBase1B);
		}

		void SetDummyBase1B(int Value)
		{
			MDummyBase1B=Value;
		}

		int GetDummyBase2A(void) const noexcept
		{
			return(MDummyBase2A);
		}

		void SetDummyBase2A(int Value)
		{
			MDummyBase2A=Value;
		}

		int GetDummyBase2B(void) const noexcept
		{
			return(MDummyBase2B);
		}

		void SetDummyBase2B(int Value)
		{
			MDummyBase2B=Value;
		}

		int GetDummyDerivedA(void) const noexcept
		{
			return(MDummyDerivedA);
		}

		void SetDummyDerivedA(int Value)
		{
			MDummyDerivedA=Value;
		}

		int GetDummyDerivedB(void) const noexcept
		{
			return(MDummyDerivedB);
		}

		void SetDummyDerivedB(int Value)
		{
			MDummyDerivedB=Value;
		}

		int GetDummyDerivedC(void) const noexcept
		{
			return(MDummyDerivedC);
		}

		void SetDummyDerivedC(int Value)
		{
			MDummyDerivedC=Value;
		}

		int GetDummyDerivedD(void) const noexcept
		{
			return(MDummyDerivedD);
		}

		void SetDummyDerivedD(int Value)
		{
			MDummyDerivedD=Value;
		}

	public:
		CGlobalNewDeleteDerived(void)
		{
			std::wcout << L"CONSTRUCTOR CGlobalNewDeleteDerived CALLED !" << std::endl;

			MDummyBase1A=1;
			MDummyBase1B=2;
			MDummyBase2A=3;
			MDummyBase2B=4;
			MDummyDerivedA=5;
			MDummyDerivedB=6;
			MDummyDerivedC=7;
			MDummyDerivedD=8;
		}

		// !!!!! Ak sa pretazuje OPERATOR NEW a OPERATOR DELETE pre CLASS a tato CLASS moze byt v DEDICSKEJ HIERARCHII, tak BASE CLASS MUSI MAT VIRTUAL DESTRUCTOR, inak PRETAZENY OPERATOR NEW a OPERATOR DELETE NEBUDU FUNGOVAT SPRAVNE.
		virtual ~CGlobalNewDeleteDerived(void) override
		{
			std::wcout << L"!!!!! DESTRUCTOR CGlobalNewDeleteDerived with VALUES DUMMY BASE 1A [" << MDummyBase1A << L"] DUMMY BASE 1B [" << MDummyBase1B << L"] DUMMY BASE 2A [" << MDummyBase2A << L"] DUMMY BASE 2B [" << MDummyBase2B << L"] DUMMY DERIVED A [" << MDummyDerivedA << L"] DUMMY DERIVED B [" << MDummyDerivedB << L"] DUMMY DERIVED C [" << MDummyDerivedC << L"] DUMMY DERIVED D [" << MDummyDerivedD << L"] CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------