//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
//-------------------------------------------------------------------------------------------------------
template<typename TTypeOnClass>
class CClassWithTemplateMethods
{
//-------------------------------------------------------------------------------------------------------
	private:
		TTypeOnClass											MValue;

	public:
		// TEMPLATE METHOD.
		template<typename TTypeOnMethod>
		TTypeOnMethod Convert(void)
		{
			TTypeOnMethod										Value=(TTypeOnMethod) MValue;

			return(Value);
		}

	public:
		CClassWithTemplateMethods(TTypeOnClass Value)
			: MValue(Value)
		{
			std::wcout << L"NON-TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
		}

		// TEMPLATE CONSTRUCTOR.
		template<typename TTypeOnConstructor>
		CClassWithTemplateMethods(TTypeOnConstructor Value)
			: MValue((TTypeOnClass) Value)
		{
			std::wcout << L"TEMPLATE CONSTRUCTOR CALLED !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------