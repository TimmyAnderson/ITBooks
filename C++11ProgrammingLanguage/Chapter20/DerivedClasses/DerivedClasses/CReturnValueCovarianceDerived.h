//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <iostream>
#include "CReturnValueCovarianceBase.h"
//-----------------------------------------------------------------------------
class CReturnValueCovarianceDerived : public CReturnValueCovarianceBase
{
//-----------------------------------------------------------------------------
	public:
		// !!!!! Aplikuje sa COVARIANCE. OVERRIDDEN METHOD ma ako RETURN VALUE NAMIESTO POINTER na CLASS 'CReturnValueCovarianceBase' vracia POINTER na CLASS 'CReturnValueCovarianceDerived'.
		virtual CReturnValueCovarianceDerived* VirtualMethod(void) override
		{
			std::wcout << L"METHOD CReturnValueCovarianceDerived::VirtualMethod() CALLED !" << std::endl;

			return(new CReturnValueCovarianceDerived());
		}

	public:
		CReturnValueCovarianceDerived(void)
		{
		}

		virtual ~CReturnValueCovarianceDerived(void) override
		{
		}
//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------