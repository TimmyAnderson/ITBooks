//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CFriendFunctionsTemplateClass.h"
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFriendFunctionsTemplateClassMakingFriend final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!! METHOD TEMPLATE CLASS je deklarovana ako FRIEND.
	// !!!!! CLASS [CFriendFunctionsTemplateClass<TType>] MUSI byt DEFINED, aby bolo mozne deklarovat FRIEND METHOD. NESTACI, ak je iba DECLARED.
	friend void CFriendFunctionsTemplateClass<TType>::Print(const CFriendFunctionsTemplateClassMakingFriend<TType>& Value) const;

	// !!!!! DEFINITION FRIEND NON-TEMPLATE FUNCTION. FUNCTION NIE JE METHOD.
	friend void FriendFunctionNotMethod(const CFriendFunctionsTemplateClassMakingFriend<TType>& Value)
	{
		// !!! Kedze FUNCTION je deklarovana ako FRIEND, moze pristupovat k PRIVATE FIELDS CLASS [CFriendFunctionsTemplateClassMakingFriend<TType>].
		std::wcout << L"NON-TEMPLATE FUNCTION NOT METHOD - FIELD [" << Value.MField << L"]." << std::endl;
	}

	private:
		TType													MField;

	public:
		CFriendFunctionsTemplateClassMakingFriend(const TType& Field);
		virtual ~CFriendFunctionsTemplateClassMakingFriend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendFunctionsTemplateClassMakingFriend<TType>::CFriendFunctionsTemplateClassMakingFriend(const TType& Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendFunctionsTemplateClassMakingFriend<TType>::~CFriendFunctionsTemplateClassMakingFriend(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------