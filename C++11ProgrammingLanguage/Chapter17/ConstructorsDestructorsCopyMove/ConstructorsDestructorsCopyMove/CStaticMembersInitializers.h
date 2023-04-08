//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
enum class EEnum
{
//-----------------------------------------------------------------------------
	E_ENUM_1=1000,
	E_ENUM_2=2000
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CStaticMembersInitializers final
{
//-----------------------------------------------------------------------------
	private:
		// STATIC INTEGER CONST VARIABLES je mozne inicializovat pri DEFINICII FIELDS.
		static const int										MValue1=100;
		// STATIC INTEGER CONST VARIABLES je mozne inicializovat pri DEFINICII FIELDS.
		static const EEnum										MValue2=EEnum::E_ENUM_2;
		// STATIC NON-INTEGER CONST VARIABLES NIE je mozne inicializovat pri DEFINICII FIELDS.
		//static const double									MValue3=33.44;
		static const double										MValue3;

	public:
		static int GetValue1(void) noexcept;
		static EEnum GetValue2(void) noexcept;
		static double GetValue3(void) noexcept;
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------