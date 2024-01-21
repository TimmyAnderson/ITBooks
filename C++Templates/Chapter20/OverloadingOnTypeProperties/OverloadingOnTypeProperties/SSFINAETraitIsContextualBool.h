//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <utility>
#include "STypeFunctionBoolConstant.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
struct SSFINAETraitIsContextualBoolType final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		template<typename TLocalType>
		struct SIdentity;

	private:
		// !!!!! METHOD je pouzivana IBA v OPERATOR [OPERATOR decltype()] a tym padom nepotrebuju DEFINITION.
		template<typename TLocalType>
		static TypeFunctionTrueType InternalTest(SIdentity<decltype(std::declval<TLocalType>() ? 0 : 1)>*);

		// !!!!! FALLBACK METHOD.
		// !!!!! METHOD je pouzivana IBA v OPERATOR [OPERATOR decltype()] a tym padom nepotrebuju DEFINITION.
		template<typename TLocalType>
		static TypeFunctionFalseType InternalTest(...);

	public:
		static constexpr bool									VALUE=decltype(InternalTest<TType>(nullptr))::VALUE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
constexpr bool													SSFINAETraitIsContextualBoolAlias=SSFINAETraitIsContextualBoolType<TType>::VALUE;
//----------------------------------------------------------------------------------------------------------------------