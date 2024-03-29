//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE UNION.
template<typename TType1, typename TType2>
union UTemplateUnion
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;

	public:
		TType1 GetField1(void) const;
		TType2 GetField2(void) const;

	public:
		UTemplateUnion(TType1 Value);
		UTemplateUnion(TType2 Value);
		~UTemplateUnion(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
UTemplateUnion<TType1,TType2>::UTemplateUnion(TType1 Value)
	: MField1(Value)
{
	std::wcout << L"UNION CONSTRUCTOR 1 CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
UTemplateUnion<TType1,TType2>::UTemplateUnion(TType2 Value)
	: MField2(Value)
{
	std::wcout << L"UNION CONSTRUCTOR 2 CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
UTemplateUnion<TType1,TType2>::~UTemplateUnion(void) noexcept
{
	std::wcout << L"UNION DESTRUCTOR CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType1 UTemplateUnion<TType1,TType2>::GetField1(void) const
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2 UTemplateUnion<TType1,TType2>::GetField2(void) const
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------