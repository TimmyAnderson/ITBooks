//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include <string>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
extern std::wstring												GlobalValueString;
extern long														GlobalValueInt;
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class CConstructors
{
//-----------------------------------------------------------------------------
	private:
		int														MFieldInt;
		long													MFieldLong;
		std::wstring											MFieldString;

	public:
		void Print(void) const
		{
			std::wcout << L"FIELD INT [" << MFieldInt << L"] FIELD LONG [" << MFieldLong << L"] FIELD STRING [" << MFieldString << L"] !" << std::endl;
		}

	public:
		CConstructors(void)
			: MFieldInt(), MFieldLong(), MFieldString()
		{
			std::wcout << L"DEFAULT CONSTRUCTOR CALLED !" << std::endl;
		}

		CConstructors(int Param)
			: MFieldInt(Param), MFieldLong(), MFieldString()
		{
			std::wcout << L"CONSTRUCTOR(INT) CALLED with PARAMETERS (" << Param << L") !" << std::endl;
		}

		CConstructors(long Param)
			: MFieldInt(), MFieldLong(Param), MFieldString()
		{
			std::wcout << L"CONSTRUCTOR(LONG) CALLED with PARAMETERS (" << Param << L") !" << std::endl;
		}

		CConstructors(const std::wstring& Param)
			: MFieldInt(), MFieldLong(), MFieldString(Param)
		{
			std::wcout << L"CONSTRUCTOR(WSTRING) CALLED with PARAMETERS (" << Param << L") !" << std::endl;
		}

		// Pouziva DEFAULT PARAMETER.
		// !!! Ako DEFAULT PARAMETERS je mozne pouzivat aj VSETKY VARIABLES, ktore su v SCOPE, teda aj GLOBAL VARIABLES.
		CConstructors(const std::wstring& Param1, int Param2, long& Param3=GlobalValueInt)
			: MFieldInt(Param2), MFieldLong(Param3), MFieldString(Param1)
		{
			Param3++;

			std::wcout << L"CONSTRUCTOR(WSTRING,INT,LONG) CALLED with PARAMETERS (" << Param1 << L"," << Param2 << L"," << Param3 << L") !" << std::endl;
		}

		// Pouziva DEFAULT PARAMETER.
		// !!! Ako DEFAULT PARAMETERS je mozne pouzivat aj VSETKY VARIABLES, ktore su v SCOPE, teda aj GLOBAL VARIABLES.
		CConstructors(int Param1, long Param2, std::wstring& Param3=GlobalValueString)
			: MFieldInt(Param1), MFieldLong(Param2), MFieldString(Param3)
		{
			Param3+=L"X";

			std::wcout << L"CONSTRUCTOR(INT,LONG,WSTRING) CALLED with PARAMETERS (" << Param1 << L"," << Param2 << L"," << Param3 << L") !" << std::endl;
		}

		virtual ~CConstructors(void)
		{
			std::wcout << L"DESTRUCTOR CALLED !" << std::endl;
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------