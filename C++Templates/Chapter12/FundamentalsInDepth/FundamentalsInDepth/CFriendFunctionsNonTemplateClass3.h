//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CString.h"
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION NON-TEMPLATE FUNCTION.
void FriendFunctions3Function1(int Value1, double Value2);
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions3Function1(TType1 Value1, TType2 Value2);
//----------------------------------------------------------------------------------------------------------------------
// !!! DECLARATION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions3Function2(TType1 Value1, TType2 Value2);
//----------------------------------------------------------------------------------------------------------------------
void FriendFunctions3Function3(int Value1, double Value2);
//----------------------------------------------------------------------------------------------------------------------
class CFriendFunctionsNonTemplateClass3 final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! Za FRIEND je oznacena NON-TEMPLATE FUNCTION [void FriendFunctions3Function1(int Value1, double Value2)].
	friend void ::FriendFunctions3Function1(int Value1, double Value2);

	// !!! Za FRIEND je oznacena NON-TEMPLATE FUNCTION [void FriendFunctions3Function1(TType1 Value1, TType2 Value2)].
	friend void ::FriendFunctions3Function1(bool Value1, double Value2);

	// !!! Za FRIEND je oznacena NON-TEMPLATE FUNCTION [void FriendFunctions3Function2(TType1 Value1, TType2 Value2)].
	friend void ::FriendFunctions3Function2<int,double>(int Value1, double Value2);

	/*
	// !!!!! COMPILED hodi ERROR, pretoze FUNCTION NEMOZE byt DEFINED pri FRIEND DECLARATION, ak FUNCTION NAME JE QUALIFIED pomocou SYNTAX [::].
	friend void ::FriendFunctions3Function3(int Value1, double Value2)
	{
		CFriendFunctionsNonTemplateClass3						Object(L"Timmy");

		// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
		std::wcout << L"TEMPLATE FUNCTION 3 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
	}
	*/

	private:
		CString													MField;

	public:
		CFriendFunctionsNonTemplateClass3(const CString& MField);
		virtual ~CFriendFunctionsNonTemplateClass3(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions3Function1(TType1 Value1, TType2 Value2)
{
	CFriendFunctionsNonTemplateClass3							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE FUNCTION 1 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!! DEFINITION TEMPLATE FUNCTION.
template<typename TType1, typename TType2>
void FriendFunctions3Function2(TType1 Value1, TType2 Value2)
{
	CFriendFunctionsNonTemplateClass3							Object(L"Timmy");

	// !!!!! Ak je FUNCTION deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE FUNCTION 2 - FIELD [" << Object.MField << L"] VALUE 1 [" << Value1 << L"] VALUE 2 [" << Value2 << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------