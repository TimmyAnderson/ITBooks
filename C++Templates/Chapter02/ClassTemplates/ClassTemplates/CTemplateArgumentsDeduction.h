//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
class CTemplateArgumentsDeduction
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType1													MValue1;
		TType2													MValue2;

	public:
		TType1 Get1(void) const noexcept;
		TType2 Get2(void) const noexcept;

	public:
		CTemplateArgumentsDeduction(void)
			: MValue1(), MValue2()
		{
		}

		// !!! CONSTRUCTOR umoznuje vykonat DEDUCTION TEMPLATE ARGUMENTS pre TEMPLATE CLASS.
		CTemplateArgumentsDeduction(TType1 Value1, TType2 Value2)
			: MValue1(Value1), MValue2(Value2)
		{
		}
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType1 CTemplateArgumentsDeduction<TType1,TType2>::Get1(void) const noexcept
{
	return(MValue1);
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType1, typename TType2>
TType2 CTemplateArgumentsDeduction<TType1,TType2>::Get2(void) const noexcept
{
	return(MValue2);
}
//----------------------------------------------------------------------------------------------------------------------