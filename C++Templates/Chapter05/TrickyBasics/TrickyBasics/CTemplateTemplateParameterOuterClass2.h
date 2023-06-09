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
class CTemplateTemplateParameterOuterClass2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! Pouzije sa TEMPLATE TEMPLATE PARAMETER s TYPE PARAMETERS.
		TInnerClass<TType1,TType2>								MInnerObject;

	public:
		// !!! CONVERSION OPERATOR, ktory ma zaroven vlastne TEMPLATE PARAMETERS, nezavisle na TEMPLATE PARAMETERS TEMPLATE CLASS.
		// !!!!! TEMPLATE PARAMETERS TEMPLATE TEMPLATE PARAMETER su ZBYTOCNE a je ich mozne odstranit.
		//template<typename TOtherType1,typename TOtherType2,template<typename TOtherLocalType1, typename TOtherLocalType2> typename TOtherInnerClass>
		template<typename TOtherType1,typename TOtherType2,template<typename,typename> typename TOtherInnerClass>
		CTemplateTemplateParameterOuterClass2<TType1,TType2,TInnerClass>& operator=(const CTemplateTemplateParameterOuterClass2<TOtherType1,TOtherType2,TOtherInnerClass>& Other);

	public:
		const TInnerClass<TType1,TType2>& GetInnerObject(void) const noexcept;

	public:
		CTemplateTemplateParameterOuterClass2(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateTemplateParameterOuterClass2(void) noexcept;

	// !!! Definuje sa FRIEND, aby OPERATOR [OPERATOR=] mohol pristupovat k PRIVATE MEMBERS.
	template<typename,typename,template<typename,typename> typename>
	friend class CTemplateTemplateParameterOuterClass2;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass>
CTemplateTemplateParameterOuterClass2<TType1,TType2,TInnerClass>::CTemplateTemplateParameterOuterClass2(const TType1& Value1, const TType2& Value2)
	: MInnerObject(Value1,Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass>
CTemplateTemplateParameterOuterClass2<TType1,TType2,TInnerClass>::~CTemplateTemplateParameterOuterClass2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass>
template<typename TOtherType1,typename TOtherType2,template<typename,typename> typename TOtherInnerClass>
CTemplateTemplateParameterOuterClass2<TType1,TType2,TInnerClass>& CTemplateTemplateParameterOuterClass2<TType1,TType2,TInnerClass>::operator=(const CTemplateTemplateParameterOuterClass2<TOtherType1,TOtherType2,TOtherInnerClass>& Other)
{
	const TOtherType1&											OriginalValue1=Other.MInnerObject.GetValue1();
	const TOtherType2&											OriginalValue2=Other.MInnerObject.GetValue2();
	TType1														ConvertedValue1=static_cast<TType1>(OriginalValue1);
	TType2														ConvertedValue2=static_cast<TType2>(OriginalValue2);

	MInnerObject=TInnerClass(ConvertedValue1,ConvertedValue2);

	return(*this);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! LOCAL TEMPLATE PARAMETERS sa NIKDY NEPOUZIVAJU a je ich mozne vyhodit.
//template<typename TType1, typename TType2, template<typename TLocalType1, typename TLocalType2> typename TInnerClass>
template<typename TType1, typename TType2, template<typename,typename> typename TInnerClass>
const TInnerClass<TType1,TType2>& CTemplateTemplateParameterOuterClass2<TType1,TType2,TInnerClass>::GetInnerObject(void) const noexcept
{
	return(MInnerObject);
}
//----------------------------------------------------------------------------------------------------------------------