//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CPointerParameterOperators final
{
//-----------------------------------------------------------------------------
	private:
		int														MValue;

	public:
		// OPERATOR moze mat ako PARAMETER POINTER.
		CPointerParameterOperators operator+(const CPointerParameterOperators* Value) const
		{
			std::wcout << "MEMBER BINARY OPERATOR+ CALLED !" << std::endl;

			return(MValue+Value->MValue);
		}

	public:
		int GetValue(void) const noexcept
		{
			return(MValue);
		}

	public:
		CPointerParameterOperators(int Value)
			: MValue(Value)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// !!! OPERATOR NESMIE mat VSETKY PARAMETERS ako POINTERS.
inline CPointerParameterOperators operator+(const CPointerParameterOperators* Left, const CPointerParameterOperators& Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR+ CALLED !" << std::endl;

	return(Left->GetValue()+Right.GetValue());
}
//-----------------------------------------------------------------------------
/*
// !!! OPERATOR NESMIE mat VSETKY PARAMETERS ako POINTERS.
inline CPointerParameterOperators operator+(const CPointerParameterOperators* Left, const CPointerParameterOperators* Right)
{
	std::wcout << "NON-MEMBER BINARY OPERATOR+ CALLED !" << std::endl;

	return(Left->GetValue()+Right->GetValue());
}
*/
//-----------------------------------------------------------------------------