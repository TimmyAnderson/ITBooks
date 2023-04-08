//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <type_traits>
#include <utility>
//-------------------------------------------------------------------------------------------------------
struct SSubstitutionFailure
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
struct SSubstitution : public std::true_type
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<>
struct SSubstitution<SSubstitutionFailure> : public std::false_type
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! Toto je POMOCNA STRUCTURE, ktora sluzi iba ako CONTAINER na ulozenie pomocnych METHODS Check().
// !!!!! METHODS Check() NEMAJU ZIADNE BODIES, pretoze sluzia C++ pouziva IBA ICH PROTOTYPE na urcenie, ktory TYPE sa pouzije ako TYPE PARAMETER v STRUCTURE [SHasFunctionXXX]. METHODS Check() umoznuju vracat nasledujuce 2 TYPES.
//   A. Ak FUNCTION Check() vracia TYPE [bool], C++ pouzije TYPE [struct SSubstitution : public std::true_type] ako TYPE PARAMETER pre TEMPLATE [SHasFunctionXXX<>]. Vysledny TYPE teda bude [SHasFunctionXXX<SSubstitution>], ktoreho FIELD [value] obsahuje hodnotu TRUE.
//   B. Ak FUNCTION Check() vracia TYPE [SSubstitutionFailure], C++ pouzije TYPE [struct SSubstitution<SSubstitutionFailure> : public std::false_type] ako TYPE PARAMETER pre TEMPLATE [SHasFunctionXXX<>]. Vysledny TYPE teda bude [SHasFunctionXXX<SSubstitution<SSubstitutionFailure>>], ktoreho FIELD [value] obsahuje hodnotu FALSE.
template<typename TType>
struct SGetFunctionXXXResult
{
//-------------------------------------------------------------------------------------------------------
	private:
		template<typename TLocalType>
		static auto Check(TLocalType Parameter) -> decltype(Parameter.XXX(),true);

		template<typename... TTypes>
		static SSubstitutionFailure Check(TTypes...);

	public:
		using													TYPE=decltype(Check(std::declval<TType>()));
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
template<typename TType>
struct SHasFunctionXXX : public SSubstitution<typename SGetFunctionXXXResult<TType>::TYPE>
{
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------