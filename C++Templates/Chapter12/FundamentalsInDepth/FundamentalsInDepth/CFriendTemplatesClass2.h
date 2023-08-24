//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include "CFriendTemplatesClass1.h"
#include "CFriendTemplatesClassMakingFriend.h"
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!!! CODE TEMPLATE CLASS [CFriendTemplatesClass<TType>] MUSEL byt rozdeleny do FILE [CFriendTemplatesClass1.h] a FILE [CFriendTemplatesClass2.h]. Je to preto, lebo vo FILE [CFriendTemplatesClass2.h] sa nachadza pouzitie NON-TEMPLATE CLASS [CFriendTemplatesClassMakingFriend] sposobom, ze vyzaduje DEFINITION danej CLASS. A preto sa vo FILE [CFriendTemplatesClass2.h] robi INCLUDE na FILE [CFriendTemplatesClassMakingFriend.h], kde sa nachadza DEFINITION NON-TEMPLATE CLASS [CFriendTemplatesClassMakingFriend].
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze CLASS [CFriendTemplatesClassMakingFriend] je NON-TEMPLATE CLASS, tak C++ VYKONAVA SEMATICKU KONTROLU CODE [Value.MField] v pripade, ze CLASS [CFriendTemplatesClassMakingFriend] je iba DECLARED, ale NIE DEFINED, COMPILER hodi ERROR.
template<typename TType>
void CFriendTemplatesClass<TType>::Print1(const CFriendTemplatesClassMakingFriend& Value) const
{
	// !!!!! Ak je METHOD deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE METHOD - LOCAL FIELD [" << MField << L"] REMOTE FIELD [" << Value.MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze CLASS [CFriendTemplatesClassMakingFriend] je NON-TEMPLATE CLASS, tak C++ VYKONAVA SEMATICKU KONTROLU CODE [Value.MField] v pripade, ze CLASS [CFriendTemplatesClassMakingFriend] je iba DECLARED, ale NIE DEFINED, COMPILER hodi ERROR.
template<typename TType>
void CFriendTemplatesClass<TType>::Print2(void) const
{
	CFriendTemplatesClassMakingFriend							Value(L"LOCAL");

	// !!!!! Ak je METHOD deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE METHOD - LOCAL FIELD [" << MField << L"] REMOTE FIELD [" << Value.MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------
// !!!!! TEMPLATE SPECIALIZATION je AUTOMATICKY FRIEND, ak je PRIMARY TEMPLATE tiez FRIEND.
// !!!!! Kedze CLASS [CFriendTemplatesClassMakingFriend] je NON-TEMPLATE CLASS, tak C++ VYKONAVA SEMATICKU KONTROLU CODE [Value.MField] v pripade, ze CLASS [CFriendTemplatesClassMakingFriend] je iba DECLARED, ale NIE DEFINED, COMPILER hodi ERROR.
template<>
void CFriendTemplatesClass<int>::Print2(void) const
{
	CFriendTemplatesClassMakingFriend							Value(L"LOCAL");

	// !!!!! Ak je METHOD deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE METHOD SPECIALIZATION <int> - LOCAL FIELD [" << MField << L"] REMOTE FIELD [" << Value.MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------