//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <string>
#include <sstream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TOuterTypes>
class CNestedParameterPacksExpansionOuter final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		template<typename TLocalOuterType, typename... TLocalOuterTypes>
		void InternalPrintParameter(size_t Index, const TLocalOuterType& OuterValue, const TLocalOuterTypes&... OuterValues) const;
		void InternalPrint(const TOuterTypes&... OuterValues) const;

	public:
		template<typename... TInnerTypes>
		void Print(const TInnerTypes&... InnerValues) const;

	public:
		CNestedParameterPacksExpansionOuter(void);
		virtual ~CNestedParameterPacksExpansionOuter(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TOuterTypes>
CNestedParameterPacksExpansionOuter<TOuterTypes...>::CNestedParameterPacksExpansionOuter(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TOuterTypes>
CNestedParameterPacksExpansionOuter<TOuterTypes...>::~CNestedParameterPacksExpansionOuter(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TOuterTypes>
template<typename TLocalOuterType, typename... TLocalOuterTypes>
void CNestedParameterPacksExpansionOuter<TOuterTypes...>::InternalPrintParameter(size_t Index, const TLocalOuterType& OuterValue, const TLocalOuterTypes&... OuterValues) const
{
	std::wstring												StringValue=OuterValue.ToString();

	std::wcout << L"INDEX [" << Index << L"] VALUE [" << StringValue << L"]." << std::endl;

	if constexpr (sizeof...(OuterValues))
	{
		InternalPrintParameter(Index+1,OuterValues...);
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename... TOuterTypes>
void CNestedParameterPacksExpansionOuter<TOuterTypes...>::InternalPrint(const TOuterTypes&... OuterValues) const
{
	InternalPrintParameter(1,OuterValues...);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename... TOuterTypes>
template<typename... TInnerTypes>
void CNestedParameterPacksExpansionOuter<TOuterTypes...>::Print(const TInnerTypes&... InnerValues) const
{
	// !!!!! CODE vykona nasledujuce cinnosti.
	// !!! 1. Kazda VALUE v PARAMETER PACK [InnerValues] je CONVERTED na prislusny TYPE s PARAMETER PACK [TInnerTypes].
	// !!! 2. Pre vsetky TYPES v PARAMETER PACK [TOuterTypes] je volany CONSTRUCTOR do ktoreho su ako PARAMETERS dosadene VALUES z kroku 1.
	// !!! 3. Zavola sa METHOD [void InternalPrint(const TOuterTypes&... OuterValues) const].
	InternalPrint(TOuterTypes(TInnerTypes(InnerValues)...)...);
}
//----------------------------------------------------------------------------------------------------------------------