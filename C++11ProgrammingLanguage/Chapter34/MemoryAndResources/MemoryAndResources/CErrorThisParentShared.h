//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <memory>
#include <cstdio>
#include "MyDebug.h"
//-------------------------------------------------------------------------------------------------------
class CErrorThisChildShared;
//-------------------------------------------------------------------------------------------------------
class CErrorThisParentShared
{
//-------------------------------------------------------------------------------------------------------
	private:
		std::shared_ptr<CErrorThisChildShared>						MChild;

	public:
		std::shared_ptr<CErrorThisChildShared>& GetChild(void)
		{
			return(MChild);
		}

		void SetChild(std::shared_ptr<CErrorThisChildShared>& Child)
		{
			MChild=Child;
		}

		long GetReferenceCounter(void)
		{
			return(MChild.use_count());
		}

		void SomeMethod(void)
		{
			wprintf_s(L"METHOD CErrorThisParentShared::SomeMethod() CALLED !\n");
		}

		void CallChild(void);

	public:
		CErrorThisParentShared(void);

		~CErrorThisParentShared(void)
		{
			wprintf_s(L"METHOD CErrorThisParentShared::~CErrorThisParentShared() CALLED ! REFERENCE COUNTER [%d] !\n",MChild.use_count());
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------