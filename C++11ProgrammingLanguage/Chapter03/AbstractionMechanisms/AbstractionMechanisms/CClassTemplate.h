//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// TEMPLATE CLASS.
template<typename TType>
class CClassTemplate
{
//-------------------------------------------------------------------------------------------------------
	private:
		TType													MValue;

	public:
		TType GetValue(void) const
		{
			return(MValue);
		}

		// !!! Priklad TEMPLATE METHOD.
		template<typename TMethodType>
		TMethodType Convert(void) const
		{
			TType												Value=MValue;
			TMethodType											ConvertedValue=(TMethodType) Value;

			return(ConvertedValue);
		}

	public:
		CClassTemplate(TType Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------