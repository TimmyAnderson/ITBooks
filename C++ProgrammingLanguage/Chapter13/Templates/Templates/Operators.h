//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
template<typename TType>
class COperators
{
	private:
		TType													MValue;

	public:
		TType GetValue(void);

	public:
		// !!! METHOD TEMPLATE FUNCTION reprezentujuca KONVERZNY OPERATOR.
		template<typename TConvertedType>
		operator COperators<TConvertedType>(void);

	public:
		COperators(TType Value);
		virtual ~COperators(void);
};
//-------------------------------------------------------------------------------------------------------