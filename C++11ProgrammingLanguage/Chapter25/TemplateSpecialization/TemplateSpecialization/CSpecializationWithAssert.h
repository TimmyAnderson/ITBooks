//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// PRIMARY TEMPLATE.
template<typename TType>
class CSpecializationWithAssert
{
//-------------------------------------------------------------------------------------------------------
	// !!! STATIC ASSERT sa musi nachadzat v PRIMARY TEMPLATE ako aj vo vsetkych SPECIALIZED TEMPLATES.
	static_assert(std::is_class<TType>::value,"TType MUST be CLASS !");

	public:
		void Print(void)
		{
			printf_s("CSpecializationWithAssert<TType>::Print() CALLED ! TYPE PARAMETER [%s] !\n",typeid(TType).name());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// PARTIAL TEMPLATE SPECIALIZATION pre POINTERS.
template<typename TType>
class CSpecializationWithAssert<TType*>
{
//-------------------------------------------------------------------------------------------------------
	// !!! STATIC ASSERT sa musi nachadzat v PRIMARY TEMPLATE ako aj vo vsetkych SPECIALIZED TEMPLATES.
	static_assert(std::is_class<TType>::value,"TType MUST be CLASS !");

	public:
		void Print(void)
		{
			printf_s("CSpecializationWithAssert<TType*>::Print() CALLED ! TYPE PARAMETER [%s] !\n",typeid(TType).name());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------