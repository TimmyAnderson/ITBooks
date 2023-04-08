//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------------------------------------------
class CNoCustomAssignmentError
{
	private:
		std::wstring											MStringValue;
		int														MIntValue;

		// !!! Kedze CLASS obsahuje CONST NON-STATIC FIELD, tak DEFAULT KOPIROVANIE VSETKYCH FIELD NEMOZE kompilator GENEROVAT.
		const int												MConst;

	public:
		void PrintValue(void);

	public:
		CNoCustomAssignmentError(void);
		CNoCustomAssignmentError(std::wstring StringValue, int IntValue);
		virtual ~CNoCustomAssignmentError(void);
};
//-------------------------------------------------------------------------------------------------------