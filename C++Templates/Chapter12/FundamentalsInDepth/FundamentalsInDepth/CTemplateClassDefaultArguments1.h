//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
// !!! Druhy TEMPLATE PARAMETER ma definovanu DEFAULT VALUE.
template<typename TType1, typename TType2=int>
class CTemplateClassDefaultArguments1 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MField1;
		TType2													MField2;

	public:
		const TType1& GetField1(void) const noexcept;
		const TType2& GetField2(void) const noexcept;

	public:
		CTemplateClassDefaultArguments1(TType1 Field1, TType2 Field2);
		virtual ~CTemplateClassDefaultArguments1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArguments1<TType1,TType2>::CTemplateClassDefaultArguments1(TType1 Field1, TType2 Field2)
	: MField1(Field1), MField2(Field2)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
CTemplateClassDefaultArguments1<TType1,TType2>::~CTemplateClassDefaultArguments1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType1& CTemplateClassDefaultArguments1<TType1,TType2>::GetField1(void) const noexcept
{
	return(MField1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
const TType2& CTemplateClassDefaultArguments1<TType1,TType2>::GetField2(void) const noexcept
{
	return(MField2);
}
//----------------------------------------------------------------------------------------------------------------------