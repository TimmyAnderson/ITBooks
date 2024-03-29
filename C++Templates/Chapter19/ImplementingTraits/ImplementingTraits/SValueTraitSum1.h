//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CBigInt.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION PRIMARY TEMPLATE CLASS.
template<typename TType>
struct SValueTraitSum1;
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION.
template<>
struct SValueTraitSum1<char>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TSum=int;

	public:
		static const TSum										ZERO=0;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION.
template<>
struct SValueTraitSum1<int>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TSum=long;

	public:
		static const TSum										ZERO=0;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION.
template<>
struct SValueTraitSum1<unsigned int>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TSum=unsigned long;

	public:
		static const TSum										ZERO=0;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION.
template<>
struct SValueTraitSum1<float>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TSum=double;

	public:
		// !!!!! Kedze C++ umoznuje IN-CLASS INITIALIZATION IBA pre INTEGRAL TYPES a ENUMERATION TYPES, VARIABLE TYPE [double] MUSI byt oznacena pomocou KEYWORD [constexpr].
		static constexpr TSum									ZERO=0.0;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION.
template<>
struct SValueTraitSum1<double>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TSum=double;

	public:
		// !!!!! Kedze C++ umoznuje IN-CLASS INITIALIZATION IBA pre INTEGRAL TYPES a ENUMERATION TYPES, INITIALIZATION sa robi v SOURCE FILE [.CPP].
		static const TSum										ZERO;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATE CLASS SPECIALIZATION.
template<>
struct SValueTraitSum1<CBigInt>
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TSum=CBigInt;

	public:
		// !!!!! Kedze C++ umoznuje IN-CLASS INITIALIZATION IBA pre INTEGRAL TYPES a ENUMERATION TYPES, INITIALIZATION sa robi v SOURCE FILE [.CPP].
		inline static const TSum								ZERO=TSum(0);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------