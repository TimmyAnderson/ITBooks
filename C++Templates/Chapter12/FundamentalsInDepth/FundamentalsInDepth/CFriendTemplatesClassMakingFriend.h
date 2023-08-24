//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "CFriendTemplatesClass1.h"
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFriendTemplatesTemplateClass;
//----------------------------------------------------------------------------------------------------------------------
// !!!!! DECLARATION NON-MEMBER TEMPLATE FUNCTION.
template<typename TType>
void FriendTemplateFunction(TType Value);
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
class CFriendTemplatesClassMakingFriend final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! DECLARATION CLASS ako FRIEND TEMPLATE.
	template<typename TType>
	friend class CFriendTemplatesTemplateClass;

	// !!!!! DECLARATION METHOD ako FRIEND TEMPLATE.
	// !!!!! CLASS [CFriendTemplatesClass<TType>] MUSI byt DEFINED, aby bolo mozne deklarovat FRIEND METHOD. NESTACI, ak je iba DECLARED.
	template<typename TType>
    friend void CFriendTemplatesClass<TType>::Print1(const CFriendTemplatesClassMakingFriend& Value) const;

	// !!!!! DECLARATION METHOD ako FRIEND TEMPLATE.
	// !!!!! CLASS [CFriendTemplatesClass<TType>] MUSI byt DEFINED, aby bolo mozne deklarovat FRIEND METHOD. NESTACI, ak je iba DECLARED.
	template<typename TType>
    friend void CFriendTemplatesClass<TType>::Print2(void) const;

	// !!!!! DECLARATION FUNCTION ako FRIEND TEMPLATE.
	// !!!!! FRIEND TEMPLATE FUNCTIONS mozu obsahovat aj TEMPLATE FUNCTION DEFINITIONS.
	// !!!!! FRIEND TEMPLATE FUNCTIONS MUSIA byt DECLARED.
	template<typename TType>
	friend void FriendTemplateFunction(TType Value)
	{
		CFriendTemplatesClassMakingFriend						Object(L"LOCAL");

		// !!!!! Ak je METHOD deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
		std::wcout << L"TEMPLATE FUNCTION - FIELD [" << Object.MField << L"] VALUE [" << Value << L"]." << std::endl;
	}

	private:
		CString													MField;

	public:
		CFriendTemplatesClassMakingFriend(const CString& Field);
		virtual ~CFriendTemplatesClassMakingFriend(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------