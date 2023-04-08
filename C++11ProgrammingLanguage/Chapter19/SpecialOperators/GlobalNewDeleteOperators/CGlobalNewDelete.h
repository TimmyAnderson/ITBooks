//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
class CGlobalNewDelete
{
//-----------------------------------------------------------------------------
	protected:
		int														MDummyA;
		int														MDummyB;
		int														MDummyC;
		int														MDummyD;

	public:
		int GetDummyA(void) const noexcept
		{
			return(MDummyA);
		}

		void SetDummyA(int Value)
		{
			MDummyA=Value;
		}

		int GetDummyB(void) const noexcept
		{
			return(MDummyB);
		}

		void SetDummyB(int Value)
		{
			MDummyB=Value;
		}

		int GetDummyC(void) const noexcept
		{
			return(MDummyC);
		}

		void SetDummyC(int Value)
		{
			MDummyC=Value;
		}

		int GetDummyD(void) const noexcept
		{
			return(MDummyD);
		}

		void SetDummyD(int Value)
		{
			MDummyD=Value;
		}

	public:
		CGlobalNewDelete(void)
		{
			std::wcout << L"CONSTRUCTOR CGlobalNewDelete CALLED !" << std::endl;

			MDummyA=1;
			MDummyB=2;
			MDummyC=3;
			MDummyD=4;
		}

		// !!!!! Ak sa pretazuje OPERATOR NEW a OPERATOR DELETE pre CLASS a tato CLASS moze byt v DEDICSKEJ HIERARCHII, tak BASE CLASS MUSI MAT VIRTUAL DESTRUCTOR, inak PRETAZENY OPERATOR NEW a OPERATOR DELETE NEBUDU FUNGOVAT SPRAVNE.
		virtual ~CGlobalNewDelete(void)
		{
			std::wcout << L"!!!!! DESTRUCTOR CGlobalNewDelete with VALUES DUMMY A [" << MDummyA << L"] DUMMY B [" << MDummyB << L"] DUMMY C [" << MDummyC << L"] DUMMY D [" << MDummyD << L"] CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------