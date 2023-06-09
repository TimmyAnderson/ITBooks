//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CTemplateTemplateParameterInnerClass1.h"
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE CLASS obsahuje TEMPLATE TEMPLATE PARAMETER.
// !!!!! TEMPLATE TEMPLATE PARAMETER ma DEFAULT VALUE, ktorej DEFINITION vsak NESMIE obsahovat TEMPLATE PARAMETERS.
// !!!!! TEMPLATE PARAMETERS TEMPLATE TEMPLATE PARAMETER su ZBYTOCNE a je ich mozne odstranit.
//template<typename TType1, typename TType2, template<typename TLocalType1, typename TLocalType2> typename TInnerClass=CTemplateTemplateParameterInnerClass1>
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass=CTemplateTemplateParameterInnerClass1>
class CTemplateTemplateParameterOuterClass1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! Pouzije sa TEMPLATE TEMPLATE PARAMETER s TYPE PARAMETERS.
		TInnerClass<TType1,TType2>								MInnerObject;

	public:
		const TInnerClass<TType1,TType2>& GetInnerObject(void) const noexcept;

	public:
		CTemplateTemplateParameterOuterClass1(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateTemplateParameterOuterClass1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass>
CTemplateTemplateParameterOuterClass1<TType1,TType2,TInnerClass>::CTemplateTemplateParameterOuterClass1(const TType1& Value1, const TType2& Value2)
	: MInnerObject(Value1,Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass>
CTemplateTemplateParameterOuterClass1<TType1,TType2,TInnerClass>::~CTemplateTemplateParameterOuterClass1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! LOCAL TEMPLATE PARAMETERS sa NIKDY NEPOUZIVAJU a je ich mozne vyhodit.
//template<typename TType1, typename TType2, template<typename TLocalType1, typename TLocalType2> typename TInnerClass>
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass>
const TInnerClass<TType1,TType2>& CTemplateTemplateParameterOuterClass1<TType1,TType2,TInnerClass>::GetInnerObject(void) const noexcept
{
	return(MInnerObject);
}
//----------------------------------------------------------------------------------------------------------------------