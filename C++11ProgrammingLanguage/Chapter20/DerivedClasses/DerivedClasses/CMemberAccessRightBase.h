//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CMemberAccessRightBase
{
//-----------------------------------------------------------------------------
	private:
		void PrivateMethod(void)
		{
			std::wcout << L"METHOD CMemberAccessRightBase::PrivateMethod() CALLED !" << std::endl;
		}
		
	protected:
		void ProtectedMethod(void)
		{
			std::wcout << L"METHOD CMemberAccessRightBase::ProtectedMethod() CALLED !" << std::endl;
		}

	public:
		void PublicMethod(void)
		{
			std::wcout << L"METHOD CMemberAccessRightBase::PublicMethod() CALLED !" << std::endl;
		}

	public:
		CMemberAccessRightBase(void)
		{
		}

		virtual ~CMemberAccessRightBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------