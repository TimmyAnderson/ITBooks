//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CFriendMembersClass1.h"
#include "CFriendMembersClass2.h"
//-----------------------------------------------------------------------------
class CFriendMembers
{
//-----------------------------------------------------------------------------
	friend CFriendMembersClass1;

	// FRIEND KEYWORD moze byt aplikovany aj na METHODS.
	friend void CFriendMembersClass2::Test1(void);

	private:
		void PrivateMethod(void);
		
	protected:
		void ProtectedMethod(void);

	public:
		void PublicMethod(void);

	public:
		CFriendMembers(void);
		virtual ~CFriendMembers(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------