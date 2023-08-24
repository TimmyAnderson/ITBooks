//----------------------------------------------------------------------------------------------------------------------
#pragma once
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include "CString.h"
#include "CFriendClassClassMakingFriends2.h"
//----------------------------------------------------------------------------------------------------------------------
class CFriendClassFriendClassNonTemplate2 final
{
//----------------------------------------------------------------------------------------------------------------------
	private:
		CFriendClassClassMakingFriends2<CFriendClassFriendClassNonTemplate2>	MField;

	public:
		void Print(void) const;

	public:
		CFriendClassFriendClassNonTemplate2(const CFriendClassClassMakingFriends2<CFriendClassFriendClassNonTemplate2>& Field);
		virtual ~CFriendClassFriendClassNonTemplate2(void) noexcept;
//----------------------------------------------------------------------------------------------------------------------
};
//----------------------------------------------------------------------------------------------------------------------