//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// TEMPLATE CLASS.
template<typename TType>
class CClassOverloading
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
			TType													Value=MValue;
			TMethodType												ConvertedValue=(TMethodType) Value;

			return(ConvertedValue);
		}

	public:
		CClassOverloading(TType Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
/*
// !!!!! COMPILER hodi ERROR, pretoze CLASS OVERLOADING NIE JE MOZNE VYKONAT.
// NON-TEMPLATE CLASS.
class CClassOverloading
{
//-------------------------------------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		int GetValue(void) const
		{
			return(MValue);
		}

	public:
		CClassOverloading(int Value)
			: MValue(Value)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
*/
//-------------------------------------------------------------------------------------------------------