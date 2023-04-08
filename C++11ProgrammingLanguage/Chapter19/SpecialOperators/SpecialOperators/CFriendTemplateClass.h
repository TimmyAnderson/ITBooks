//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CFriendTemplateClass
{
//-----------------------------------------------------------------------------
	friend TType1;

	// FRIEND KEYWORD moze byt aplikovany aj na METHODS.
	friend void TType2::TestTemplateClass1(void);

	private:
		void PrivateMethod(void)
		{
			std::wcout << L"METHOD CFriendTemplateClass::PrivateMethod() CALLED !" << std::endl;
		}
		
	protected:
		void ProtectedMethod(void)
		{
			std::wcout << L"METHOD CFriendTemplateClass::ProtectedMethod() CALLED !" << std::endl;
		}

	public:
		void PublicMethod(void)
		{
			std::wcout << L"METHOD CFriendTemplateClass::PublicMethod() CALLED !" << std::endl;
		}

	public:
		CFriendTemplateClass(void)
		{
		}

		virtual ~CFriendTemplateClass(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------