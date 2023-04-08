//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CAccessControlBase.h"
//-----------------------------------------------------------------------------
class CAccessControlDerivedProtected : protected CAccessControlBase
{
//-----------------------------------------------------------------------------
	private:
		void DerivedProtectedPrivate(void);

	protected:
		void DerivedProtectedProtected(void);

	public:
		void DerivedProtectedPublic(void);

	public:
		void TestDerivedProtected(void);

	public:
		CAccessControlDerivedProtected(void);
		virtual ~CAccessControlDerivedProtected(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------