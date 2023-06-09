//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CClassSizeBase1.h"
#include "CClassSizeBase2.h"
//-------------------------------------------------------------------------------------------------------
class CClassSizeDerived : public CClassSizeBase1, public CClassSizeBase2
{
//-------------------------------------------------------------------------------------------------------
	private:
		char													MValueDerived[32];

	public:
		CClassSizeDerived(void)
		{
			for(size_t Index=0;Index<sizeof(MValueDerived);Index++)
			{
				MValueDerived[Index]=static_cast<char>(Index+1);
			}
		}

		virtual ~CClassSizeDerived(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------