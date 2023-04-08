//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "AccessControlDerivedProtected.h"
//-------------------------------------------------------------------------------------------------------
class CAccessControlMostDerivedProtected : public CAccessControlDerivedProtected
{
	private:
		void MostDerivedProtectedPrivate(void);

	protected:
		void MostDerivedProtectedProtected(void);

	public:
		void MostDerivedProtectedPublic(void);

	public:
		void TestMostDerivedProtected(void);

	public:
		CAccessControlMostDerivedProtected(void);
		virtual ~CAccessControlMostDerivedProtected(void);
};
//-------------------------------------------------------------------------------------------------------