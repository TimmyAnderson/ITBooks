//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <string>
#include <stdio.h>
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// PRIMARY TEMPLATE.
template<typename TType>
class CSpecializations
{
//-------------------------------------------------------------------------------------------------------
	public:
		void Print(void)
		{
			printf_s("CSpecializations<TType>::Print() CALLED ! TYPE PARAMETER [%s] !\n",typeid(TType).name());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// PARTIAL TEMPLATE SPECIALIZATION pre POINTERS.
template<typename TType>
class CSpecializations<TType*>
{
//-------------------------------------------------------------------------------------------------------
	public:
		void Print(void)
		{
			printf_s("CSpecializations<TType*>::Print() CALLED ! TYPE PARAMETER [%s] !\n",typeid(TType).name());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// PARTIAL TEMPLATE SPECIALIZATION pre REFERENCES.
template<typename TType>
class CSpecializations<TType&>
{
//-------------------------------------------------------------------------------------------------------
	public:
		void Print(void)
		{
			printf_s("CSpecializations<TType&>::Print() CALLED ! TYPE PARAMETER [%s] !\n",typeid(TType).name());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// COMPLETE TEMPLATE SPECIALIZATION pre WSTRINGS.
template<>
class CSpecializations<std::wstring>
{
//-------------------------------------------------------------------------------------------------------
	public:
		void Print(void)
		{
			printf_s("CSpecializations<>::Print() CALLED !\n");
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------