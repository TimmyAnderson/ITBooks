//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CMultipleVirtualInheritanceBase1.h"
#include "CMultipleVirtualInheritanceBase2.h"
//-------------------------------------------------------------------------------------------------------
class CMultipleVirtualInheritanceDerived : public CMultipleVirtualInheritanceBase1, public CMultipleVirtualInheritanceBase2
{
//-------------------------------------------------------------------------------------------------------
	public:
		char													MValueDerived[240];

	public:
		CMultipleVirtualInheritanceDerived(void)
		{
			for(size_t Index=0;Index<sizeof(MValueDerived);Index++)
			{
				MValueDerived[Index]=static_cast<char>(Index+1);
			}
		}

		virtual ~CMultipleVirtualInheritanceDerived(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------