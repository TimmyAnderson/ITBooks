//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateClassDefaultArgumentsOutOfClass final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;

	public:
		const TType1& GetField1(void) const noexcept;
		const TType2& GetField2(void) const noexcept;

	public:
		CTemplateClassDefaultArgumentsOutOfClass(TType1 Field1, TType2 Field2);
		virtual ~CTemplateClassDefaultArgumentsOutOfClass(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsOutOfClass<TType1,TType2>::CTemplateClassDefaultArgumentsOutOfClass(TType1 Field1, TType2 Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArgumentsOutOfClass<TType1,TType2>::~CTemplateClassDefaultArgumentsOutOfClass(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! COMPILER hodi ERROR, pretoze TEMPLATE MEMBERS definovane mimo CLASS NESMU mat pre svoje TEMPLATE PARAMETERS DEFAULT TEMPLATE ARGUMENTS.
//template<typename TType1, typename TType2=double>
template<typename TType1, typename TType2>
const TType1& CTemplateClassDefaultArgumentsOutOfClass<TType1,TType2>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDefaultArgumentsOutOfClass<TType1,TType2>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------