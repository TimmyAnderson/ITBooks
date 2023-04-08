//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
#include "Int.h"
//-------------------------------------------------------------------------------------------------------
class CIntConversions
{
	private:
		int														MValue;

	public:
		void Print(std::wstring);

	public:
		// Konverzny operator na INT.
		operator int(void);

	public:
		CIntConversions(void);
		CIntConversions(int Value);
		virtual ~CIntConversions(void);
};
//-------------------------------------------------------------------------------------------------------
// !!! Konverzny OPERATOR MUSI byt VZDY MEMBER funkcia.
//operator CInt(CIntConversions& Value);
//-------------------------------------------------------------------------------------------------------