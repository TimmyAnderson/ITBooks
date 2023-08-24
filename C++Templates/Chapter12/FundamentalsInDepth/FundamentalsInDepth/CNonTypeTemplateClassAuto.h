//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CException.h"
//----------------------------------------------------------------------------------------------------------------------
// !!! Pre definiciu NON-TYPE TEMPLATE PARAMETER je mozne pouzit aj KEYWORD [auto].
template<typename TType, auto SIZE>
class CNonTypeTemplateClassAuto final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		TType													MValues[SIZE];

	public:
		static constexpr auto									VALUES_SIZE=SIZE;

	public:
		TType GetValue(std::size_t Index) const;
		void SetValue(std::size_t Index, TType Value);

	public:
		CNonTypeTemplateClassAuto(void);
		virtual ~CNonTypeTemplateClassAuto(void);
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, auto SIZE>
CNonTypeTemplateClassAuto<TType,SIZE>::CNonTypeTemplateClassAuto(void)
	: MValues()
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, auto SIZE>
CNonTypeTemplateClassAuto<TType,SIZE>::~CNonTypeTemplateClassAuto(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType, auto SIZE>
TType CNonTypeTemplateClassAuto<TType,SIZE>::GetValue(std::size_t Index) const
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
template<typename TType, auto SIZE>
void CNonTypeTemplateClassAuto<TType,SIZE>::SetValue(std::size_t Index, TType Value)
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