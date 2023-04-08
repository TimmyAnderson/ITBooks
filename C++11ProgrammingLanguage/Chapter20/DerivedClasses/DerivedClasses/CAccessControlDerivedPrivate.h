//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CAccessControlBase.h"
//-----------------------------------------------------------------------------
class CAccessControlDerivedPrivate : private CAccessControlBase
{
//-----------------------------------------------------------------------------
	private:
		void DerivedPrivatePrivate(void);

	protected:
		void DerivedPrivateProtected(void);

	public:
		void DerivedPrivatePublic(void);

	public:
		void TestDerivedPrivate(void);

	public:
		CAccessControlDerivedPrivate(void);
		virtual ~CAccessControlDerivedPrivate(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------