//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CErrorThisParentShared;
//-------------------------------------------------------------------------------------------------------
class CErrorThisChildShared
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::shared_ptr<CErrorThisParentShared>						MParent;

	public:
		std::shared_ptr<CErrorThisParentShared>& GetParent(void)
		{
			return(MParent);
		}

		void SetPointer(std::shared_ptr<CErrorThisParentShared>& Parent)
		{
			MParent=Parent;
		}

		long GetReferenceCounter(void)
		{
			return(MParent.use_count());
		}

		void SomeMethod(void)
		{
			wprintf_s(L"METHOD CErrorThisChildShared::SomeMethod() CALLED !\n");
		}

		void CallParent(void);

	public:
		CErrorThisChildShared(std::shared_ptr<CErrorThisParentShared> Parent);

		~CErrorThisChildShared(void)
		{
			wprintf_s(L"METHOD CErrorThisChildShared::~CErrorThisChildShared() CALLED ! REFERENCE COUNTER [%d] !\n",MParent.use_count());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------