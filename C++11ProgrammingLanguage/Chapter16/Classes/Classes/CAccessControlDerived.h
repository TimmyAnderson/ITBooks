//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include "CAccessControlBase.h"
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CAccessControlDerived : public CAccessControlBase
{
//-----------------------------------------------------------------------------
	private:
		void DerivedPrivateMethod(void) const
		{
			std::wcout << L"DERIVED PRIVATE METHOD CALLED !" << std::endl;
		}

	protected:
		void DerivedProtectedMethod(void) const
		{
			std::wcout << L"DERIVED PROTECTED METHOD CALLED !" << std::endl;
		}

	public:
		void DerivedPublicMethod(void) const
		{
			std::wcout << L"DERIVED PUBLIC METHOD CALLED !" << std::endl;
		}

	public:
		void Test(void) const
		{
			// !!! PRIVATE METHODS BASE CLASS NIE JE MOZNE volat v DERIVED CLASSES. Preto COMPILER hodi ERROR.
			//BasePrivateMethod();

			// PROTECTED METHODS BASE CLASS JE MOZNE volat v DERIVED CLASSES.
			BaseProtectedMethod();

			// PUBLIC METHODS BASE CLASS JE MOZNE volat v DERIVED CLASSES.
			BasePublicMethod();
		}

	public:
		CAccessControlDerived(void)
		{
		}

		virtual ~CAccessControlDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------