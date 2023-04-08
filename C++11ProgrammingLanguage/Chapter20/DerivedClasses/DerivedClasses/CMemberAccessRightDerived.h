//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CMemberAccessRightBase.h"
//-----------------------------------------------------------------------------
class CMemberAccessRightDerived : public CMemberAccessRightBase
{
//-----------------------------------------------------------------------------
	public:
		void Test(void)
		{
			std::wcout << L"METHOD CMemberAccessRightDerived::Test() STARTED !" << std::endl;

			// !!! COMPILER hodi ERROR, pretoze PRIVATE METHODS NIE JE mozne volat z DERIVED CLASSES.
			//PrivateMethod();

			ProtectedMethod();

			PublicMethod();

			std::wcout << L"METHOD CMemberAccessRightDerived::Test() FINISHED !" << std::endl;
		}

	public:
		CMemberAccessRightDerived(void)
		{
		}

		virtual ~CMemberAccessRightDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------