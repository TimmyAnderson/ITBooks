//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CThisPointer final
{
//-----------------------------------------------------------------------------
	private:
		int														MField;

	public:
		int GetField(void) const noexcept
		{
			// !!! V CONST METHODS je THIS POINTER definovany ako CONST THIS POINTER, a preto nasledujuce CODE hodi ERROR.
			//CThisPointer*										ThisPointer=this;
			const CThisPointer*									ThisPointer=this;

			return(ThisPointer->MField);
		}

		void SetField(int Value) noexcept
		{
			// !!! V NON-CONST METHODS je THIS POINTER definovany ako NON-CONST THIS POINTER.
			CThisPointer*										ThisPointer=this;

			ThisPointer->MField=Value;
		}

	public:
		// Ak METHOD vracia ako RETURN VALUE REFERENCE na THIS OBJECT, potom je mozne vykonat METHOD CHAINING.
		const CThisPointer& MethodChaining1(void) const
		{
			std::wcout << L"METHOD MethodChaining1() CALLED !" << std::endl;

			return(*this);
		}

		// Ak METHOD vracia ako RETURN VALUE REFERENCE na THIS OBJECT, potom je mozne vykonat METHOD CHAINING.
		const CThisPointer& MethodChaining2(void) const
		{
			std::wcout << L"METHOD MethodChaining2() CALLED !" << std::endl;

			return(*this);
		}

		// Ak METHOD vracia ako RETURN VALUE REFERENCE na THIS OBJECT, potom je mozne vykonat METHOD CHAINING.
		const CThisPointer& MethodChaining3(void) const
		{
			std::wcout << L"METHOD MethodChaining3() CALLED !" << std::endl;

			return(*this);
		}

	public:
		CThisPointer(int Value)
			: MField(Value)
		{
		}

		~CThisPointer(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------