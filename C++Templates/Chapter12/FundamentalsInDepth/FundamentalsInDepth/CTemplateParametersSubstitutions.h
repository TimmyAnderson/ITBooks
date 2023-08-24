//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateParametersSubstitutions final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		const TType1& GetValue1(void) const noexcept;
		const TType2& GetValue2(void) const noexcept;

	public:
		// !!!!! Na TEMPLATE CLASS SCOPE v IN CLASS CODE NETREBA pri dotazovani sa na CURRENT TEMPLATE definovat TEMPLATE PARAMETERS, lebo tie su prebrate z TEMPLATE PARAMETERS TEMPLATE CLASS.
		const CTemplateParametersSubstitutions* GetThis(void) const noexcept;

	public:
		CTemplateParametersSubstitutions(const TType1& Value1, const TType2& Value2);
		virtual ~CTemplateParametersSubstitutions(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateParametersSubstitutions<TType1,TType2>::CTemplateParametersSubstitutions(const TType1& Value1, const TType2& Value2)
	: MValue1(Value1), MValue2(Value2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateParametersSubstitutions<TType1,TType2>::~CTemplateParametersSubstitutions(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateParametersSubstitutions<TType1,TType2>::GetValue1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateParametersSubstitutions<TType1,TType2>::GetValue2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Na TEMPLATE CLASS SCOPE v OUT OF CLASS CODE je NUTNE pri dotazovani sa na CURRENT TEMPLATE definovat aj TEMPLATE PARAMETERS.
template<typename TType1, typename TType2>
const CTemplateParametersSubstitutions<TType1,TType2>* CTemplateParametersSubstitutions<TType1,TType2>::GetThis(void) const noexcept
{
	return(this);
}
//----------------------------------------------------------------------------------------------------------------------