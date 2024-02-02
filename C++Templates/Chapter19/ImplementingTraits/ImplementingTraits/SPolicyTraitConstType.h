//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <type_traits>
#include "SOtherTraitsIfThenElse.h"
#include "CTypesForPolicyTraitConstTypes.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! POLICY TRAIT vracia povodny TYPE, ak jeho dlzka je kratsia ako 2 nasobok POINTER SIZE a zaroven NEMA USER DEFINED COPY CONSTRUCTOR a USER DEFINED MOVE CONSTRUCTOR.
template<typename TType>
struct SPolicyTraitConstType final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=SOtherTraitsIfThenElse<(sizeof(TType)<=(2*sizeof(void*)) && std::is_trivially_copy_constructible<TType>::value && std::is_trivially_move_constructible<TType>::value),TType,TType const&>::TYPE;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! Pre TYPE [CLongTypeExcluded] sa EXPLICITNE urci vysledny TYPE.
template<>
struct SPolicyTraitConstType<CLongTypeExcluded> final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		using													TYPE=CLongTypeExcluded;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------