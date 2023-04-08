//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template <typename TType1, typename TType2>
class CHasOperators
{
//-------------------------------------------------------------------------------------------------------
	private:
		// !!! Pomocne STRUCTURES. Klucove je, ze MUSIA mat ROZLICNU DLZKU, kedze sa testuje ich SIZEOF.
		struct SOperatorYes
		{
			char												MField[1];
		};

		struct SOperatorNo
		{
			char												MField[2];
		};

	private:
		// !!! Ak medzi TYPES [TLocalType1] a [TLocalType2] je definovany OPERATOR+, tak COMPILER vyberie tuto verziu OVERLOADED METHOD.
		template <typename TLocalType1, typename TLocalType2>
		static auto HasOperatorPlus(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1+Value2,SOperatorYes());

		// !!! Ak medzi TYPES [TLocalType1] a [TLocalType2] NIE JE definovany OPERATOR+, tak COMPILER vyberie tuto verziu OVERLOADED METHOD.
		template <typename ...TLocalTypes>
		static SOperatorNo HasOperatorPlus(TLocalTypes...);

		template <typename TLocalType1, typename TLocalType2>
		static auto HasOperatorMinus(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1-Value2,SOperatorYes());

		template <typename ...TLocalTypes>
		static SOperatorNo HasOperatorMinus(TLocalTypes...);

		template <typename TLocalType1, typename TLocalType2>
		static auto HasOperatorMultiple(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1*Value2,SOperatorYes());

		template <typename ...TLocalTypes>
		static SOperatorNo HasOperatorMultiple(TLocalTypes...);

		template <typename TLocalType1, typename TLocalType2>
		static auto HasOperatorDivide(TLocalType1 Value1, TLocalType2 Value2) -> decltype(Value1/Value2,SOperatorYes());

		template <typename ...TLocalTypes>
		static SOperatorNo HasOperatorDivide(TLocalTypes...);

	public:
		// TYPES [TType1] a [TType2] NEMUSIA mat definovany DEFAULT CONSTRUCTOR, pretoze sa instancie tychto TYPES vytvoria pomocou TEMPLATE FUNCTION declval<T>(), ktora umoznuje vytvorit instancie TYPES BEZ volania ich CONSTRUCTORS.
		static const bool										IsOperatorPlusDefined=(sizeof(HasOperatorPlus<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
		static const bool										IsOperatorMinusDefined=(sizeof(HasOperatorMinus<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
		static const bool										IsOperatorMultipleDefined=(sizeof(HasOperatorMultiple<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
		static const bool										IsOperatorDivideDefined=(sizeof(HasOperatorDivide<TType1,TType2>(std::declval<TType1>(),std::declval<TType2>()))==sizeof(SOperatorYes));
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------