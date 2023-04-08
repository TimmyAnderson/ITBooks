//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <list>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CInitializerListConstructor final
{
//-----------------------------------------------------------------------------
	private:
		std::list<double>										MField;

	public:
		const std::list<double>& GetField(void) const noexcept
		{
			return(MField);
		}

	public:
		CInitializerListConstructor(void)
			: MField()
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CInitializerListConstructor CALLED !" << std::endl;
		}

		CInitializerListConstructor(double Value1, double Value2)
			: MField()
		{
			MField.push_back(Value1);
			MField.push_back(Value2);

			std::wcout << L"PARAMETRIZED CONSTRUCTOR CInitializerListConstructor CALLED !" << std::endl;
		}

		CInitializerListConstructor(const std::initializer_list<double>& Field)
			: MField()
		{
			for(double Value : Field)
			{
				MField.push_back(Value);
			}

			std::wcout << L"INITIALIZER LIST CONSTRUCTOR CInitializerListConstructor CALLED !" << std::endl;
		}

		~CInitializerListConstructor(void)
		{
			std::wcout << L"DESTRUCTOR ~CInitializerListConstructor CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------