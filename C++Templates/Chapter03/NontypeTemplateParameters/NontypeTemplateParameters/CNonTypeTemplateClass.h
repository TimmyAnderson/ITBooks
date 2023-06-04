//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <cstdio>
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
// !!! TEMPLATES mozu mat aj NON-TYPE PARAMETERS.
template<typename TType, std::size_t SIZE>
class CNonTypeTemplateClass final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValues[SIZE];

	public:
		static constexpr std::size_t							VALUES_SIZE=SIZE;

	public:
		TType GetValue(std::size_t Index) const;
		void SetValue(std::size_t Index, TType Value);

	public:
		CNonTypeTemplateClass(void);
		virtual ~CNonTypeTemplateClass(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, std::size_t SIZE>
CNonTypeTemplateClass<TType,SIZE>::CNonTypeTemplateClass(void)
	: MValues()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, std::size_t SIZE>
CNonTypeTemplateClass<TType,SIZE>::~CNonTypeTemplateClass(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, std::size_t SIZE>
TType CNonTypeTemplateClass<TType,SIZE>::GetValue(std::size_t Index) const
{
	if (Index<SIZE)
	{
		return(MValues[Index]);
	}
	else
	{
		throw(CException(L"INDEX is OUT of BOUNDS !"));
	}
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, std::size_t SIZE>
void CNonTypeTemplateClass<TType,SIZE>::SetValue(std::size_t Index, TType Value)
{
	if (Index<SIZE)
	{
		MValues[Index]=Value;
	}
	else
	{
		throw(CException(L"INDEX is OUT of BOUNDS !"));
	}
}
//----------------------------------------------------------------------------------------------------------------------