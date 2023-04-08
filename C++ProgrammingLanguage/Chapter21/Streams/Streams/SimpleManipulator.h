//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <ios>
#include <iostream>
//-------------------------------------------------------------------------------------------------------
// !!! CLASS reprezentuje CUSTOM MANIPULATOR a obsahuje vsetky PROPERTIES, ktore chcem na STREAME pomocou tohto MANIPULATOR nastavit.
class CSimpleManipulator
{
	private:
		int														MWidth;

	friend std::wostream& operator<<(std::wostream& Stream, CSimpleManipulator& Manipulator);

	public:
		CSimpleManipulator(int Width);
		virtual ~CSimpleManipulator(void);
};
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// !!! GLOBALNY OPERATOR<< MUSI mat ako 1. PARAMETER 'wostream' a ako 2. PARAMETER REFERENCIU na CUSTOM MANIPULATOR.
std::wostream& operator<<(std::wostream& Stream, CSimpleManipulator& Manipulator);
//-------------------------------------------------------------------------------------------------------