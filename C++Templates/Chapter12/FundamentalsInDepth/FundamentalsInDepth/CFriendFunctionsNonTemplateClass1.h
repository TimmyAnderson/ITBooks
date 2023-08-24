//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions1(TType1 Value1, TType2 Value2);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CFriendFunctionsNonTemplateClass1 final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Deklaracia FRIEND TEMPLATE FUNCTION ma EXPLICITNE definovane oba TEMPALTE ARGUMENTS.
	friend void FriendFunctions1<int,double>(int Value1, double Value2);

	// !!! Deklaracia FRIEND TEMPLATE FUNCTION NEMA EXPLICITNE definovany 2. TEMPALTE ARGUMENT, pretoze ten moze byt DEDUCED.
	friend void FriendFunctions1<bool>(bool Value1, double Value2);

	// !!! Deklaracia FRIEND TEMPLATE FUNCTION NEMA EXPLICITNE definovane TEMPALTE ARGUMENTS, pretoze tie mozu byt DEDUCED.
	friend void FriendFunctions1<>(CString Value1, double Value2);

	/*
	// !!!!! COMPILER hodi ERROR, pretoze EXPLICITNE definovany 1. TEMPLATE ARGUMENT TYPE [long] nezodpoveda 1. TEMPLATE PARAMETER TYPE [bool].
	friend void FriendFunctions1<long>(bool Value1, double Value2);
	*/

	/*
	// !!!! COMPILER hodi ERROR, pretoze TEMPLATE FUNCTION s danym NAME NEBOLA DECLARED.
	friend void FriendFunctionsError<long>(long Value1, double Value2);
	*/

	/*
	// !!!!! COMPILER hodi ERROR, pretoze FRIEND DECLARATION NEMOZE obsahovat TEMPLATE FUNCTION DEFINITION.
	friend void FriendFunctions1<double,int>(double Value1, int Value2)
	{
	}
	*/

	private:
		CString													MField;

	public:
		CFriendFunctionsNonTemplateClass1(const CString& Field);
		virtual ~CFriendFunctionsNonTemplateClass1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions1(TType1 Value1, TType2 Value2)
{
	CFriendFunctionsNonTemplateClass1							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE FUNCTION - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------