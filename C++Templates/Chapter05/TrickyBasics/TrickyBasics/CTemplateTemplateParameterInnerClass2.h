//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateTemplateParameterInnerClass2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;

	public:
		CTemplateTemplateParameterInnerClass2(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateTemplateParameterInnerClass2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateTemplateParameterInnerClass2<TType1,TType2>::CTemplateTemplateParameterInnerClass2(const TType1& Value1, const TType2& Value2)
	: MValue1(Value1), MValue2(Value2)
{
	std::wcout << L"CONSTRUCTOR [CTemplateTemplateParameterInnerClass2] CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateTemplateParameterInnerClass2<TType1,TType2>::~CTemplateTemplateParameterInnerClass2(void) noexcept
{
	std::wcout << L"DESTRUCTOR [~CTemplateTemplateParameterInnerClass2] CALLED !" << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateTemplateParameterInnerClass2<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateTemplateParameterInnerClass2<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------