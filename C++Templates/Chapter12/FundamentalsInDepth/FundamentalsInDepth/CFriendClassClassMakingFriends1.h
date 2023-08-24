//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFriendClassClassMakingFriends1 final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! NON-TEMPLATE CLASSES NEMUSIA byt DECLARED predtym nez su oznacene ako FRIEND CLASSES.
	// !!!!! Umozni CLASS [CFriendClassFriendClassNonTemplate1] pristupit k PRIVATE MEMBERS TYPE [CFriendClassClassMakingFriends1<TType>].
	friend class CFriendClassFriendClassNonTemplate1;

	// !!!!! TEMPLATE CLASSES NEMUSIA byt DECLARED predtym nez su oznacene ako FRIEND CLASSES.
	// !!!!! Umozni CLASS [CFriendClassFriendClassTemplate<TLocalType>] pristupit k PRIVATE MEMBERS TYPE [CFriendClassClassMakingFriends1<TType>].
	template<typename TLocalType>
	friend class CFriendClassFriendClassTemplate;

	// !!!!! Umozni METHOD [void PrintForDifferentTemplateParameter(const CFriendClassClassMakingFriends1<TLocalType>& Value) const] pristupit k PRIVATE MEMBERS TYPE [CFriendClassClassMakingFriends1<TLocalType>].
	template<typename TLocalType>
	friend class CFriendClassClassMakingFriends1;

	private:
		TType													MField;

	public:
		template<typename TLocalType>
		void PrintForDifferentTemplateParameter(const CFriendClassClassMakingFriends1<TLocalType>& Value) const;

	public:
		CFriendClassClassMakingFriends1(TType Field);
		virtual ~CFriendClassClassMakingFriends1(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendClassClassMakingFriends1<TType>::CFriendClassClassMakingFriends1(TType Field)
	: MField(Field)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendClassClassMakingFriends1<TType>::~CFriendClassClassMakingFriends1(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
template<typename TLocalType>
void CFriendClassClassMakingFriends1<TType>::PrintForDifferentTemplateParameter(const CFriendClassClassMakingFriends1<TLocalType>& Value) const
{
	// !!! METHOD moze pristupvat k PRIVATE FIELDS TYPE [CFriendClassClassMakingFriends1<TLocalType>], pretoze bola DECLARED ako FRIEND.
	std::wcout << L"MAKING FRIEND TEMPLATE CLASS 1 - FIELD [" << MField << L"] VALUE [" << Value.MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------