//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CUsingDeclarationAccessRightsBase.h"
//-----------------------------------------------------------------------------
class CUsingDeclarationAccessRightsDerived : public CUsingDeclarationAccessRightsBase
{
//-----------------------------------------------------------------------------
	public:
		// !!! PROTECTED METHOD CUsingDeclarationAccessRightsBase::ProtectedMethod() je spristupnena v CLASS 'CUsingDeclarationAccessRightsDerived' pomocou USING SYNTAX.
		using													CUsingDeclarationAccessRightsBase::ProtectedMethod;
		
	public:
		void Test(void)
		{
			std::wcout << L"METHOD CUsingDeclarationAccessRightsDerived::Test() STARTED !" << std::endl;

			ProtectedMethod();

			std::wcout << L"METHOD CUsingDeclarationAccessRightsDerived::Test() FINISHED !" << std::endl;
		}

	public:
		CUsingDeclarationAccessRightsDerived(void)
		{
		}

		virtual ~CUsingDeclarationAccessRightsDerived(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------