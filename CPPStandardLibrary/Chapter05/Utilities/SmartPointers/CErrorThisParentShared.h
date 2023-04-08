//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include <iostream>
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
			std::wcout << L"METHOD CErrorThisParentShared::SomeMethod() CALLED !" << std::endl;
		}

		void CallChild(void);

	public:
		CErrorThisParentShared(void);

		~CErrorThisParentShared(void)
		{
			std::wcout << L"METHOD CErrorThisParentShared::~CErrorThisParentShared() CALLED ! REFERENCE COUNTER [" << MChild.use_count() << L"] !" << std::endl;
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------