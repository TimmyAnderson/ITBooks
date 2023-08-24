//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
class CFriendClassClassMakingFriends2 final
{
//----------------------------------------------------------------------------------------------------------------------
	// !!!!! Umozni CLASS [TType] pristupit k PRIVATE MEMBERS TYPE [CFriendClassClassMakingFriends2<TType>].
	// !!!!! KEYWORD [class] sa NESMIE pouzit.
	friend TType;

	private:
		void PrivatePrint(void) const;

	public:
		CFriendClassClassMakingFriends2(void);
		virtual ~CFriendClassClassMakingFriends2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendClassClassMakingFriends2<TType>::CFriendClassClassMakingFriends2(void)
{
}
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
CFriendClassClassMakingFriends2<TType>::~CFriendClassClassMakingFriends2(void) noexcept
{
}
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------------
template<typename TType>
void CFriendClassClassMakingFriends2<TType>::PrivatePrint(void) const
{
	std::wcout << L"MAKING FRIEND TEMPLATE CLASS 2 is CALLED." << std::endl;
}
//----------------------------------------------------------------------------------------------------------------------