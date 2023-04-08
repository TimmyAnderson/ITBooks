//-------------------------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------------
#include "CMultipleVirtualInheritanceSuperBase1.h"
#include "CMultipleVirtualInheritanceSuperBase2.h"
#include "CMultipleVirtualInheritanceSuperBase3.h"
//-------------------------------------------------------------------------------------------------------
class CMultipleVirtualInheritanceBase2 : public virtual CMultipleVirtualInheritanceSuperBase1, public virtual CMultipleVirtualInheritanceSuperBase2, public virtual CMultipleVirtualInheritanceSuperBase3
{
//-------------------------------------------------------------------------------------------------------
	public:
		char													MValueBase2[200];

	public:
		CMultipleVirtualInheritanceBase2(void)
		{
			for(size_t Index=0;Index<sizeof(MValueBase2);Index++)
			{
				MValueBase2[Index]=static_cast<char>(Index+1);
			}
		}

		virtual ~CMultipleVirtualInheritanceBase2(void)
		{
		}
//-------------------------------------------------------------------------------------------------------
};
//-------------------------------------------------------------------------------------------------------