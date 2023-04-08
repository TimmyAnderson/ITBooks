//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CAccessControlBase
{
//-----------------------------------------------------------------------------
	private:
		void BasePrivateMethod(void) const
		{
			std::wcout << L"BASE PRIVATE METHOD CALLED !" << std::endl;
		}

	protected:
		void BaseProtectedMethod(void) const
		{
			std::wcout << L"BASE PROTECTED METHOD CALLED !" << std::endl;
		}

	public:
		void BasePublicMethod(void) const
		{
			std::wcout << L"BASE PUBLIC METHOD CALLED !" << std::endl;
		}

	public:
		CAccessControlBase(void)
		{
		}

		virtual ~CAccessControlBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------