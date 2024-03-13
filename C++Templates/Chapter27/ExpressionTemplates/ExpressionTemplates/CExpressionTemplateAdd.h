//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include "CExpressionTemplateTraits.h"
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TOperand1, typename TOperand2>
class CExpressionTemplateAdd final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! OBJECT ukladajuci LEFT OPERAND.
		typename CExpressionTemplateTraits<TOperand1>::TYPE		MOperand1;
		// !!!!! OBJECT ukladajuci RIGHT OPERAND.
		typename CExpressionTemplateTraits<TOperand2>::TYPE		MOperand2;

	public:
		TType operator[](size_t Index) const;

	public:
		size_t Size(void) const;

	public:
		CExpressionTemplateAdd(const TOperand1& Operand1, const TOperand2& Operand2);
		virtual ~CExpressionTemplateAdd(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TOperand1, typename TOperand2>
CExpressionTemplateAdd<TType,TOperand1,TOperand2>::CExpressionTemplateAdd(const TOperand1& Operand1, const TOperand2& Operand2)
	: MOperand1(Operand1), MOperand2(Operand2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TOperand1, typename TOperand2>
CExpressionTemplateAdd<TType,TOperand1,TOperand2>::~CExpressionTemplateAdd(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TOperand1, typename TOperand2>
TType CExpressionTemplateAdd<TType,TOperand1,TOperand2>::operator[](size_t Index) const
{
	TType														Result=(MOperand1[Index]+MOperand2[Index]);

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, typename TOperand1, typename TOperand2>
size_t CExpressionTemplateAdd<TType,TOperand1,TOperand2>::Size(void) const
{
	if ((MOperand1.Size()==0 || MOperand2.Size()==0 || MOperand1.Size()==MOperand2.Size())==false)
	{
		throw(CException(L"SIZES don't MATCH."));
	}

	size_t														Size=(MOperand1.Size()!=0 ? MOperand1.Size() : MOperand2.Size());

	return(Size);
}
//----------------------------------------------------------------------------------------------------------------------