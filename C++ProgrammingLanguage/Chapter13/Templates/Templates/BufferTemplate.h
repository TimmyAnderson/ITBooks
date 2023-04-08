//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
// !!! TEMPLATE obsahuje i TEMPLATE PARAMETER a INT PARAMETER.
// !!!!! Ako TEMPLATE PARAMETER, tak i INT PARAMETER su COMPILE-TIME CONSTANTS.
template<typename TType, TType DefaultValue, int SIZE>
class CBufferTemplate
{
	private:
		// !!!!! INT TEMPLATE PARAMETRE su COMPILE-TIME CONSTANTS a teda je ich mozne pouzit na definiciu VELKOSTI POLA, kedze COMPILER uz v COMPILE-TIME vie ich hodnotu.
		TType													MBuffer[SIZE];

	public:
		const TType& GetValue(int Index) const;
		void SetValue(int Index, const TType& Value);

	public:
		CBufferTemplate(void);
		virtual ~CBufferTemplate(void);
};
//-------------------------------------------------------------------------------------------------------