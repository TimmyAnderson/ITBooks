//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! PRIMARY TEMPLATE.
template<typename TType>
class CParsingDependentNamesTypes1 final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		enum
		{
			TYPE_OR_VALUE=100
		};
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CParsingDependentNamesTypes2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		void Test(void);

	public:
		CParsingDependentNamesTypes2(int Value);
		virtual ~CParsingDependentNamesTypes2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CParsingDependentNamesTypes2<TType>::CParsingDependentNamesTypes2(int Value)
	: MValue(Value)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CParsingDependentNamesTypes2<TType>::~CParsingDependentNamesTypes2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CParsingDependentNamesTypes2<TType>::Test(void)
{
	// !!! Pouzije sa PRIMARY TEMPLATE.
	if constexpr (std::is_same<TType,void>::value==false)
	{
		// !!!!! CODE sa interpretuje ako BINARY OPERATOR [OPERATOR*].
		//CParsingDependentNamesTypes1<TType>::TYPE_OR_VALUE*	MValue;

		// !!!!! CODE sa interpretuje ako BINARY OPERATOR [OPERATOR*].
		std::wcout << L"VALUE (NON-VOID) [" << (CParsingDependentNamesTypes1<TType>::TYPE_OR_VALUE*MValue) << L"]." << std::endl;
	}
	// !!! Pouzije sa TEMPLATE SPECIALIZATION.
	else
	{
		// !!!!! CODE sa interpretuje ako VARIABLE DECLARATION.
		typename CParsingDependentNamesTypes1<TType>::TYPE_OR_VALUE*	MValue=nullptr;

		std::wcout << L"VALUE (VOID) [" << (MValue) << L"]." << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE SPECIALIZATION.
template<>
class CParsingDependentNamesTypes1<void> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE_OR_VALUE=int;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------