//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassTwoParameters2 final
{
//----------------------------------------------------------------------------------------------------------------------
	template<typename TLocalType1, typename TLocalType2>
	friend std::wostream& operator<<(std::wostream& Stream, const CTemplateClassTwoParameters2<TLocalType1,TLocalType2>& Value);

	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;

	public:
		CTemplateClassTwoParameters2(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateClassTwoParameters2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassTwoParameters2<TType1,TType2>::CTemplateClassTwoParameters2(const TType1& Value1, const TType2& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassTwoParameters2<TType1,TType2>::~CTemplateClassTwoParameters2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassTwoParameters2<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassTwoParameters2<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
std::wostream& operator<<(std::wostream& Stream, const CTemplateClassTwoParameters2<TType1,TType2>& Value)
{
	Stream << L"VALUE 1 [" << Value.MValue1 << L"] VALUE 2 [" << Value.MValue2 << L"]";

	return(Stream);
}
//----------------------------------------------------------------------------------------------------------------------