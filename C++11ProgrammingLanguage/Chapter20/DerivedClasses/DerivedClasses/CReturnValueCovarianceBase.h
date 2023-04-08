//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
//-----------------------------------------------------------------------------
class CReturnValueCovarianceBase
{
//-----------------------------------------------------------------------------
	public:
		virtual CReturnValueCovarianceBase* VirtualMethod(void)=0;

	public:
		void DoSomething(void)
		{
			std::wcout << L"METHOD CReturnValueCovarianceBase::DoSomething() CALLED !" << std::endl;
		}

	public:
		CReturnValueCovarianceBase(void)
		{
		}

		virtual ~CReturnValueCovarianceBase(void)
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------