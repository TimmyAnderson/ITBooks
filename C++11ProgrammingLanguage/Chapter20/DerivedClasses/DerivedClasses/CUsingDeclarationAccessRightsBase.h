//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CUsingDeclarationAccessRightsBase
{
//-----------------------------------------------------------------------------
	private:
		void PrivateMethod(void)
		{
			std::wcout << L"METHOD CUsingDeclarationAccessRightsBase::PrivateMethod() CALLED !" << std::endl;
		}
		
	protected:
		void ProtectedMethod(void)
		{
			std::wcout << L"METHOD CUsingDeclarationAccessRightsBase::ProtectedMethod() CALLED !" << std::endl;
		}

	public:
		void PublicMethod(void)
		{
			std::wcout << L"METHOD CUsingDeclarationAccessRightsBase::PublicMethod() CALLED !" << std::endl;
		}

	public:
		CUsingDeclarationAccessRightsBase(void)
		{
		}

		virtual ~CUsingDeclarationAccessRightsBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------