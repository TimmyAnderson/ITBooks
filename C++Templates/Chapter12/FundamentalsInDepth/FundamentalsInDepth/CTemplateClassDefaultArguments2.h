//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TEMPLATE CLASS, ktora ma DEFAULT TEMPLATE ARGUMENTS.
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5=wchar_t, typename TType6=bool>
class CTemplateClassDefaultArguments2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Dalsia DECLARATION TEMPLATE CLASS uz DECLARED TEMPLATE CLASS doplnila dalsi DEFAULT TEMPLATE ARGUMENT.
// !!!!! DEFAULT TEMPLATE ARGUMENT moze byt doplneny pre TEMPLATE PARAMETER 'TType4', pretoze DEFAULT TEMPLATE ARGUMENTS pre TEMPLATE PARAMETERS nasledujuce za TEMPLATE PARAMETER 'TType4' boli definovane v predoslej DECLARATION.
template<typename TType1, typename TType2, typename TType3, typename TType4=float, typename TType5, typename TType6>
class CTemplateClassDefaultArguments2;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze uz raz definovany DEFAULT TEMPLATE ARGUMENT NESMIE byt REDEFINED.
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6=bool>
class CTemplateClassDefaultArguments2;
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER CODE AKCEPTUJE, hoci podla knihy by mal hodit ERROR, pretoze DECLARATION definuje DEFAULT TEMPLATE ARGUMENT pre TEMPLATE PARAMETER 'TType2', pricom DEFAULT TEMPLATE ARGUMENT pre nasledujuci TEMPLATE PARAMETER 'TType3' NEBOL DEFINOVANY.
template<typename TType1, typename TType2=int, typename TType3, typename TType4, typename TType5, typename TType6>
class CTemplateClassDefaultArguments2;
*/
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3=double, typename TType4, typename TType5, typename TType6>
class CTemplateClassDefaultArguments2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;
		TType3													MField3;
		TType4													MField4;
		TType5													MField5;
		TType6													MField6;

	public:
		const TType1& GetField1(void) const noexcept;
		const TType2& GetField2(void) const noexcept;
		const TType3& GetField3(void) const noexcept;
		const TType4& GetField4(void) const noexcept;
		const TType5& GetField5(void) const noexcept;
		const TType6& GetField6(void) const noexcept;

	public:
		CTemplateClassDefaultArguments2(TType1 Field1, TType2 Field2, TType3 Field3, TType4 Field4, TType5 Field5, TType6 Field6);
		virtual ~CTemplateClassDefaultArguments2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::CTemplateClassDefaultArguments2(TType1 Field1, TType2 Field2, TType3 Field3, TType4 Field4, TType5 Field5, TType6 Field6)
	: MField1(Field1), MField2(Field2), MField3(Field3), MField4(Field4), MField5(Field5), MField6(Field6)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::~CTemplateClassDefaultArguments2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
const TType1& CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
const TType2& CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
const TType3& CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::GetField3(void) const noexcept
{
	return(MField3);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
const TType4& CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::GetField4(void) const noexcept
{
	return(MField4);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
const TType5& CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::GetField5(void) const noexcept
{
	return(MField5);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2, typename TType3, typename TType4, typename TType5, typename TType6>
const TType6& CTemplateClassDefaultArguments2<TType1,TType2,TType3,TType4,TType5,TType6>::GetField6(void) const noexcept
{
	return(MField6);
}
//----------------------------------------------------------------------------------------------------------------------