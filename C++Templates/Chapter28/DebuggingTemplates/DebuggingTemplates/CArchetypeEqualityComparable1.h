//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CArchetypeConvertibleToBool1.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CArchetypeEqualityComparable1 final
{
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! FUNCTION nemusi mat BODY, ak sa pouziva iba na testovanie v COMPILE TIME.
CArchetypeConvertibleToBool1 operator==(const CArchetypeEqualityComparable1&, const CArchetypeEqualityComparable1&)
{
	CArchetypeConvertibleToBool1								Result;

	return(Result);
}
//----------------------------------------------------------------------------------------------------------------------