//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CMultipleVirtualInheritanceSuperBase1.h"
#include "CMultipleVirtualInheritanceSuperBase2.h"
#include "CMultipleVirtualInheritanceSuperBase3.h"
//-------------------------------------------------------------------------------------------------------
class CMultipleVirtualInheritanceBase1 : public virtual CMultipleVirtualInheritanceSuperBase1, public virtual CMultipleVirtualInheritanceSuperBase2, public virtual CMultipleVirtualInheritanceSuperBase3
{
//-------------------------------------------------------------------------------------------------------
	public:
		char													MValueBase1[160];

	public:
		CMultipleVirtualInheritanceBase1(void)
		{
			for(size_t Index=0;Index<sizeof(MValueBase1);Index++)
			{
				MValueBase1[Index]=static_cast<char>(Index+1);
			}
		}

		virtual ~CMultipleVirtualInheritanceBase1(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------