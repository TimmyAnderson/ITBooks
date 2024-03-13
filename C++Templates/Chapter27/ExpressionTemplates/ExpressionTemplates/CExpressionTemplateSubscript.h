//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TArray1, typename TArray2>
class CExpressionTemplateSubscript
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TArray1&												MArray1;
		const TArray2&											MArray2;

	public:
		decltype(auto) operator[](size_t Index) const;
		TType& operator[](size_t Index);

	public:
		size_t Size(void) const;

	public:
		CExpressionTemplateSubscript(TArray1& Array1, const TArray2& Array2);
		virtual ~CExpressionTemplateSubscript(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TArray1, typename TArray2>
CExpressionTemplateSubscript<TType,TArray1,TArray2>::CExpressionTemplateSubscript(TArray1& Array1, const TArray2& Array2)
	: MArray1(Array1), MArray2(Array2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TArray1, typename TArray2>
CExpressionTemplateSubscript<TType,TArray1,TArray2>::~CExpressionTemplateSubscript(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TArray1, typename TArray2>
decltype(auto) CExpressionTemplateSubscript<TType,TArray1,TArray2>::operator[](size_t Index) const
{
	// !!!!! Pre OPERAND [MArray2[Index]] sa AUTOMATICKY vola CONVERSION OPERATOR na TYPE [size_t].
	return(MArray1[MArray2[Index]]);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TArray1, typename TArray2>
TType& CExpressionTemplateSubscript<TType,TArray1,TArray2>::operator[](size_t Index)
{
	// !!!!! Pre OPERAND [MArray2[Index]] sa AUTOMATICKY vola CONVERSION OPERATOR na TYPE [size_t].
	return(MArray1[MArray2[Index]]);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TArray1, typename TArray2>
size_t CExpressionTemplateSubscript<TType,TArray1,TArray2>::Size(void) const
{
	return(MArray2.Size());
}
//----------------------------------------------------------------------------------------------------------------------