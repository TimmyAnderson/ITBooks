//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// TEMPLATE CLASS.
template<typename TType>
class CClassTemplate2
{
//-------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		TType GetValue(void) const;

		template<typename TMethodType>
		TMethodType Convert(void) const;

	public:
		CClassTemplate2(TType Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! METHODS deklarovane MIMO CLASS TEMPLATE SCOPE musia pouzit KEYWORD [template<typename TType>].
template<typename TType>
// V CLASS TEMPLATE NAME je NUTNE vymenovat vsetky CLASS TEMPLATE PARAMETERS.
TType CClassTemplate2<TType>::GetValue(void) const
{
	return(MValue);
}
//-------------------------------------------------------------------------------------------------------
// !!! METHODS deklarovane MIMO CLASS TEMPLATE SCOPE musia pouzit KEYWORD [template<typename TType>].
// !!! Priklad TEMPLATE METHOD.
template<typename TType>
template<typename TMethodType>
// V CLASS TEMPLATE NAME je NUTNE vymenovat vsetky CLASS TEMPLATE PARAMETERS.
TMethodType CClassTemplate2<TType>::Convert(void) const
{
	TType													Value=MValue;
	TMethodType												ConvertedValue=(TMethodType) Value;

	return(ConvertedValue);
}
//-------------------------------------------------------------------------------------------------------