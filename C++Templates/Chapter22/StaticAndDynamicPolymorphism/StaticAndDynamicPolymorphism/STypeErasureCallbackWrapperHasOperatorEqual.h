//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include "STypeFunctionBoolConstant.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct STypeErasureCallbackWrapperHasOperatorEqual final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		// !!!!! HELPER METHOD. Nemusi mat BODY, kedze sa pouziva v OPERATOR [OPERATOR decltype()].
		static void* HelperMethod(bool);

	private:
		// !!!!! HELPER METHOD. Nemusi mat BODY, kedze sa pouziva v OPERATOR [OPERATOR decltype()].
		// !!!!! METHOD zistuje ci medzi instanciami TYPE [TLocalType] existuje OPERATOR [OPERATOR==].
		template<typename TLocalType>
		static TypeFunctionTrueType Test(decltype(HelperMethod(std::declval<const TLocalType&>()==std::declval<const TLocalType&>())),decltype(HelperMethod(!(std::declval<const TLocalType&>()==std::declval<const TLocalType&>()))));

	private:
		// !!!!! HELPER METHOD. Nemusi mat BODY, kedze sa pouziva v OPERATOR [OPERATOR decltype()].
		template<typename TLocalType>
		static TypeFunctionFalseType Test(...);

	public:
		// !!!!! Obsahuje VALUE [true], ak TYPE [TType] obsahuje OPERATOR [OPERATOR==]. Inak obsahuje VALUE [false].
		static constexpr bool									VALUE=decltype(Test<TType>(nullptr,nullptr))::VALUE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------