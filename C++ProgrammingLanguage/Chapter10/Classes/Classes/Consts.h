//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CConsts
{
	private:
		const int												INT_CONSTANT;

		// !!! Toto kompilator NEZOBERIE a HODI CHYBU, pretoze NEPOZNA HONODTU INT_CONSTANT, ktora aj ked je KONSTANTNA, tak je definovana DYNAMICKY az v CONSTRUCTOR. KOMPILATOR tak NEVIE VELKOST OBJEKTU a tym padom NEMOZE SKOMPILOVAT PROGRAM.
		//int													MArray[INT_CONSTANT];

		// STATIC INT CONSTANTS je mozne definovat PRIAMO v CLASS.
		static const int										STATIC_INT_CONSTANT=3;

		// !!! Toto uz kompilator ZOBERIE, kedze POZNA VELKOST CONST v COMPILE-TIME.
		int														MArray[STATIC_INT_CONSTANT];

		// !!! DOUBLE premenne NIE JE MOZNE INICIALIZOVAT v CLASS.
		//static const double									STATIC_DOUBLE_CONSTANT=3.0;

		// !!! Musi byt INICIALIZOVANA v .CPP subore.
		static const std::wstring								STATIC_TEXT_CONSTANT;

	public:
		void Print(void);

	public:
		CConsts(void);
		CConsts(int Value);
		virtual ~CConsts(void);
};
//-------------------------------------------------------------------------------------------------------