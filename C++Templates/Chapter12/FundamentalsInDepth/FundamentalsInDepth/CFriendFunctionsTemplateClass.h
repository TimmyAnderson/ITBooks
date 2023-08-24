//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFriendFunctionsTemplateClassMakingFriend;
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFriendFunctionsTemplateClass final
{
//----------------------------------------------------------------------------------------------------------------------
	public:
		void Print(const CFriendFunctionsTemplateClassMakingFriend<TType>& Value) const;

	public:
		CFriendFunctionsTemplateClass(void);
		virtual ~CFriendFunctionsTemplateClass(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendFunctionsTemplateClass<TType>::CFriendFunctionsTemplateClass(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendFunctionsTemplateClass<TType>::~CFriendFunctionsTemplateClass(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
// !!!!! Kedze CLASS [CFriendFunctionsTemplateClassMakingFriend<TType>] je TEMPLATE CLASS, tak C++ NEVYKONAVA SEMATICKU KONTROLU CODE [Value.MField] a akcpetuje ho aj BEZ TOHO, aby TYPE [CFriendFunctionsTemplateClassMakingFriend<TType>] bol DEFINED. Staci, ak je DECLARED.
template<typename TType>
void CFriendFunctionsTemplateClass<TType>::Print(const CFriendFunctionsTemplateClassMakingFriend<TType>& Value) const
{
	// !!!!! Ak je METHOD deklarovana ako FRIEND, moze pristupit k PRIVATE MEMBERS.
	std::wcout << L"TEMPLATE METHOD - FIELD [" << Value.MField << L"]." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------