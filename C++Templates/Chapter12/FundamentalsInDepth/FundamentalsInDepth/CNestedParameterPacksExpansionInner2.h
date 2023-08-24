//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3>
class CNestedParameterPacksExpansionInner2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;
		TType3													MField3;

	public:
		std::wstring ToString(void) const;

	public:
		CNestedParameterPacksExpansionInner2(TType1 Field1, TType2 Field2, TType3 Field3);
		virtual ~CNestedParameterPacksExpansionInner2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3>
CNestedParameterPacksExpansionInner2<TType1,TType2,TType3>::CNestedParameterPacksExpansionInner2(TType1 Field1, TType2 Field2, TType3 Field3)
	: MField1(Field1), MField2(Field2), MField3(Field3)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3>
CNestedParameterPacksExpansionInner2<TType1,TType2,TType3>::~CNestedParameterPacksExpansionInner2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3>
std::wstring CNestedParameterPacksExpansionInner2<TType1,TType2,TType3>::ToString(void) const
{
	std::wstringstream											Stream;

	Stream << "INNER CLASS 2 - FIELD 1 [" << MField1 << L"] FIELD 2 [" << MField2 << L"] FIELD 3 [" << MField3 << L"].";

	return(Stream.str());
}
//----------------------------------------------------------------------------------------------------------------------