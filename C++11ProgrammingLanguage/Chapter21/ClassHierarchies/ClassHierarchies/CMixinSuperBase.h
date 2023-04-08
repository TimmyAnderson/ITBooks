//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
//-------------------------------------------------------------------------------------------------------
class CMixinSuperBase
{
//-------------------------------------------------------------------------------------------------------
	public:
		// METHOD je DERIVED v CLASS 'CMixinBase1'.
		virtual void AAA(void) const
		{
			std::wcout << L"METHOD CMixinSuperBase::AAA() CALLED !" << std::endl;
		}

		// METHOD je DERIVED v CLASS 'CMixinBase2'.
		virtual void BBB(void) const
		{
			std::wcout << L"METHOD CMixinSuperBase::BBB() CALLED !" << std::endl;
		}

		// METHOD je DERIVED v CLASS 'CMixinBase1' a CLASS 'CMixinBase2'.
		// !!! Kedze METHOD je DERIVED v CLASS 'CMixinBase1' a CLASS 'CMixinBase2', MUSI byt DERIVED aj v CLASS 'CMixinDerived'.
		virtual void CCC(void) const
		{
			std::wcout << L"METHOD CMixinSuperBase::CCC() CALLED !" << std::endl;
		}

	public:
		CMixinSuperBase(void)
		{
		}

		virtual ~CMixinSuperBase(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------