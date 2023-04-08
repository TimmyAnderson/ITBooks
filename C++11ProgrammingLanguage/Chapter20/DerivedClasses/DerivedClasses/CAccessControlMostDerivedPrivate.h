//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include "CAccessControlDerivedPrivate.h"
//-----------------------------------------------------------------------------
class CAccessControlMostDerivedPrivate : public CAccessControlDerivedPrivate
{
//-----------------------------------------------------------------------------
	private:
		void MostDerivedPrivatePrivate(void);

	protected:
		void MostDerivedPrivateProtected(void);

	public:
		void MostDerivedPrivatePublic(void);

	public:
		void TestMostDerivedPrivate(void);

	public:
		CAccessControlMostDerivedPrivate(void);
		virtual ~CAccessControlMostDerivedPrivate(void);
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------